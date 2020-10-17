#include "physical_device.hpp"
#include "instance.hpp"

bool carbon::PhysicalDevice::hasDeviceExtensionSupport(const VkPhysicalDevice &device) {
	// query device extension properties
	uint32_t numExtensions{ 0 };
	vkEnumerateDeviceExtensionProperties(device, nullptr, &numExtensions, nullptr);

	// put into vector
	std::vector<VkExtensionProperties> available(numExtensions);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &numExtensions, available.data());

	return carbon::utils::containsRequired(m_device_extensions, available);
}


int32_t carbon::PhysicalDevice::getDeviceScore(const VkPhysicalDevice &device) {
	// get device properties and features
	VkPhysicalDeviceProperties deviceProps;
	VkPhysicalDeviceFeatures deviceFeats;

	vkGetPhysicalDeviceProperties(device, &deviceProps);
	vkGetPhysicalDeviceFeatures(device, &deviceFeats);

	// cannot function without geometry shader
	if (!deviceFeats.geometryShader) {
		return 0;
	}

	// no support for device extensions
	if (!hasDeviceExtensionSupport(device)) {
		return 0;
	}

	int32_t score{ 0 };

	// favour discrete GPU
	if (deviceProps.deviceType == VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU) {
		score += 1000;
	}

	score += deviceProps.limits.maxImageDimension2D;
	return score;
}


VkPhysicalDevice carbon::PhysicalDevice::selectBestPhysicalDevice(const std::vector<VkPhysicalDevice> &devices) {
	int32_t score{ 0 };

	// add all device scores to candidates
	for (const auto &d : devices) {
		score = getDeviceScore(d);
		m_candidates.insert(std::make_pair(score, d));
	}

	// check if best candidate is even suitable
	if (m_candidates.rbegin()->first > 0) {
		return m_candidates.rbegin()->second;
	}

	return VK_NULL_HANDLE;
}


carbon::PhysicalDevice::PhysicalDevice(carbon::Instance *instance)
	: m_instance(instance)
{
	// get number of physical devices available
	uint32_t numDevices{ 0 };
	vkEnumeratePhysicalDevices(m_instance->getHandle(), &numDevices, nullptr);

	// no physical devices found
	if (numDevices == 0) {
		throw std::runtime_error("[ERROR] Failed to find any physical devices!");
	}

	// store all devices in vector
	std::vector<VkPhysicalDevice> devices(numDevices);
	vkEnumeratePhysicalDevices(m_instance->getHandle(), &numDevices, devices.data());

	// select best device
	m_device = selectBestPhysicalDevice(devices);

	if (m_device == VK_NULL_HANDLE) {
		throw std::runtime_error("[ERROR] Failed to choose suitable physical device!");
	}

	// get properties of device
	vkGetPhysicalDeviceProperties(m_device, &m_device_props);
	vkGetPhysicalDeviceFeatures(m_device, &m_device_feats);
	vkGetPhysicalDeviceMemoryProperties(m_device, &m_device_memory_props);
}


void carbon::PhysicalDevice::showProperties() {
	std::cout << "\n[Physical Device] " << m_device_props.deviceName << '\n';
	std::cout << "    Type:                        " << getDeviceType() << '\n';
	std::cout << "    Vendor ID:                   " << m_device_props.vendorID << '\n';
	std::cout << "    Memory heap count:           " << m_device_memory_props.memoryHeapCount << '\n';
	std::cout << "    Maximum clip distances:      " << m_device_props.limits.maxClipDistances << '\n';
	std::cout << "    Maximum cull distances:      " << m_device_props.limits.maxCullDistances << '\n';
	std::cout << "    Maximum number of viewports: " << m_device_props.limits.maxViewports << '\n';
	std::cout << "    Maximum size of 2D textures: " << m_device_props.limits.maxImageDimension2D << '\n';
	std::cout << "    Maximum size of 3D textures: " << m_device_props.limits.maxImageDimension3D << '\n';
}


const char *carbon::PhysicalDevice::getDeviceType() {
	switch (m_device_props.deviceType) {
		case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU:
			return "Integrated GPU";
		case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU:
			return "Discrete GPU";
		case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU:
			return "Virtual GPU";
		case VK_PHYSICAL_DEVICE_TYPE_CPU:
			return "CPU";
		default:
			return "Other";
	}
}
