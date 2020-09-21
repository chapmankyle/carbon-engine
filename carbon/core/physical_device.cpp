#include "physical_device.hpp"

bool carbon::PhysicalDevice::hasDeviceExtensionSupport(const VkPhysicalDevice &device) {
	// query device extension properties
	uint32_t numExtensions{ 0 };
	vkEnumerateDeviceExtensionProperties(device, nullptr, &numExtensions, nullptr);

	// put into vector
	std::vector<VkExtensionProperties> available(numExtensions);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &numExtensions, available.data());

	std::set<const char *> required(m_device_extensions.begin(), m_device_extensions.end());

	// remove each found extension
	for (const auto& ext : available) {
		required.erase(ext.extensionName);
	}

	// empty if all extensions were found and removed
	return required.empty();
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


const VkPhysicalDevice& carbon::PhysicalDevice::getHandle() const {
	return m_device;
}


const VkPhysicalDeviceProperties& carbon::PhysicalDevice::getProperties() const {
	return m_device_props;
}


const VkPhysicalDeviceFeatures& carbon::PhysicalDevice::getFeatures() const {
	return m_device_feats;
}


const VkPhysicalDeviceMemoryProperties& carbon::PhysicalDevice::getMemoryProperties() const {
	return m_device_memory_props;
}


const std::multimap<int, VkPhysicalDevice> carbon::PhysicalDevice::getCandidates() const {
	return m_candidates;
}
