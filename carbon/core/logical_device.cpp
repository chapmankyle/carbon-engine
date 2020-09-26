#include "logical_device.hpp"

#include "instance.hpp"
#include "carbon/display/surface.hpp"
#include "physical_device.hpp"

void carbon::LogicalDevice::findQueueFamilyIndices() {
    uint32_t numQueueFamilies{ 0 };

    // get physical device queue family properties
    VkPhysicalDevice physDevice{ m_physical_device->getHandle() };
    vkGetPhysicalDeviceQueueFamilyProperties(physDevice, &numQueueFamilies, nullptr);

    // store queue families
    std::vector<VkQueueFamilyProperties> queueFamilies(numQueueFamilies);
    vkGetPhysicalDeviceQueueFamilyProperties(physDevice, &numQueueFamilies, queueFamilies.data());

    int i{ 0 };

    // find first index of queue family that supports commands
    for (const auto &queueFam : queueFamilies) {
        // check for graphics support
        if (queueFam.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
            m_queue_family_indices.graphicsFamily = i;
        }

        // check for surface support
        VkBool32 presentSupport{ false };
        vkGetPhysicalDeviceSurfaceSupportKHR(m_physical_device->getHandle(), i, m_surface->getHandle(), &presentSupport);

        if (queueFam.queueCount > 0 && presentSupport) {
            m_queue_family_indices.presentFamily = i;
        }

        // check for compute support
        if (queueFam.queueFlags & VK_QUEUE_COMPUTE_BIT) {
            m_queue_family_indices.computeFamily = i;
        }

        // check for transfer support
        if (queueFam.queueFlags & VK_QUEUE_TRANSFER_BIT) {
            m_queue_family_indices.transferFamily = i;
        }

        // check if all families are supported
        if (m_queue_family_indices.hasFamilies()) {
            break;
        }

        i++;
    }

    if (m_queue_family_indices.graphicsFamily == UINT32_MAX) {
        throw std::runtime_error("[ERROR] No graphics family support.");
    }
}


void carbon::LogicalDevice::createDevice() {
    // unique indices for queue families
    std::set<uint32_t> uniqueQueueFamilies = {
        m_queue_family_indices.graphicsFamily,
        m_queue_family_indices.presentFamily
    };

    // createinfo for each queue family
    std::vector<VkDeviceQueueCreateInfo> createInfoQueues(uniqueQueueFamilies.size());

    // priority given to this queue
    float queuePriority{ 1.0f };

    for (const uint32_t queueFam : uniqueQueueFamilies) {
        VkDeviceQueueCreateInfo queueCreateInfo;
        carbon::initStruct(queueCreateInfo, VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO);

        queueCreateInfo.queueFamilyIndex = queueFam;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;
        createInfoQueues.push_back(queueCreateInfo);
    }

    // specify device features to use
    VkPhysicalDeviceFeatures deviceFeats{};
    deviceFeats.samplerAnisotropy = VK_TRUE;
    deviceFeats.sampleRateShading = VK_TRUE;

    std::vector<const char *> deviceExtensions{ m_physical_device->getDeviceExtensions() };
    std::vector<const char *> validationLayers{ m_instance->getEnabledValidationLayers() };

    // start creating device information
    VkDeviceCreateInfo createInfo;
    carbon::initStruct(createInfo, VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO);

    createInfo.queueCreateInfoCount = static_cast<uint32_t>(createInfoQueues.size());
    createInfo.pQueueCreateInfos = createInfoQueues.data();

    createInfo.pEnabledFeatures = &deviceFeats;

    createInfo.enabledExtensionCount = static_cast<uint32_t>(deviceExtensions.size());
    createInfo.ppEnabledExtensionNames = deviceExtensions.data();

    if (m_instance->isValidationEnabled()) {
        createInfo.enabledLayerCount = validationLayers.size();
        createInfo.ppEnabledLayerNames = validationLayers.data();
    } else {
        createInfo.enabledLayerCount = 0;
        createInfo.ppEnabledLayerNames = nullptr;
    }

    // attempt to create logical device
    if (vkCreateDevice(m_physical_device->getHandle(), &createInfo, nullptr, &m_device) != VK_SUCCESS) {
        throw std::runtime_error("[ERROR] Failed to create logical device!");
    }

    // create single graphics queue from device
    vkGetDeviceQueue(m_device, m_queue_family_indices.graphicsFamily, 0, &m_graphics_queue);
    vkGetDeviceQueue(m_device, m_queue_family_indices.presentFamily, 0, &m_present_queue);
}

carbon::LogicalDevice::LogicalDevice(
    carbon::Instance *instance,
    carbon::PhysicalDevice *physicalDevice,
    carbon::Surface *surface
)
    : m_instance(instance)
    , m_physical_device(physicalDevice)
    , m_surface(surface)
{
    // find queue families and then create the logical device
    findQueueFamilyIndices();
    createDevice();
}


carbon::LogicalDevice::~LogicalDevice() {
    destroy();
}


void carbon::LogicalDevice::destroy() {
    if (m_device == VK_NULL_HANDLE) {
        return;
    }

    // wait for asynchronous drawing commands to complete
    vkDeviceWaitIdle(m_device);

    // destroy and reset
    vkDestroyDevice(m_device, nullptr);
    m_device = VK_NULL_HANDLE;

    // m_surface is member class and thus will be destroyed
    // after this class destructor
}


const VkDevice& carbon::LogicalDevice::getHandle() const {
    return m_device;
}


const VkQueue& carbon::LogicalDevice::getGraphicsQueue() const {
    return m_graphics_queue;
}


const VkQueue& carbon::LogicalDevice::getPresentQueue() const {
    return m_present_queue;
}
