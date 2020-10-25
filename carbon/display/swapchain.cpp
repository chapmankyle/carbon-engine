#include "swapchain.hpp"

#include "carbon/core/physical_device.hpp"
#include "carbon/core/logical_device.hpp"
#include "surface.hpp"

void carbon::Swapchain::querySwapchainSupport() {
	assert(m_physical_device && m_surface && "Physical device and surface must not be null.");

	m_swapchain_details = {};

	// get physical device and surface handles
	VkPhysicalDevice physDevice = m_physical_device->getHandle();
	VkSurfaceKHR surf = m_surface->getHandle();

	// get surface capabilities
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physDevice, surf, &m_swapchain_details.capabilities);

	// query supported surface formats
	uint32_t formatCount{ 0 };
	vkGetPhysicalDeviceSurfaceFormatsKHR(physDevice, surf, &formatCount, nullptr);

	if (formatCount != 0) {
		m_swapchain_details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(physDevice, surf, &formatCount, m_swapchain_details.formats.data());
	}

	// query supported presentation modes
	uint32_t presentModeCount{ 0 };
	vkGetPhysicalDeviceSurfacePresentModesKHR(physDevice, surf, &presentModeCount, nullptr);

	if (presentModeCount != 0) {
		m_swapchain_details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(physDevice, surf, &presentModeCount, m_swapchain_details.presentModes.data());
	}
}


void carbon::Swapchain::chooseSwapSurfaceFormat() {
	// B8G8R8A8 -> store as B, G, R and A in that order (as 8 bit unsigned integers, so 32 bits per pixel)
	// SRGB is standard format for textures
	for (const auto &fmt : m_swapchain_details.formats) {
		if (fmt.format == VK_FORMAT_B8G8R8A8_SRGB && fmt.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			m_surface_format = fmt;
			return;
		}
	}

	m_surface_format = m_swapchain_details.formats[0];
}


void carbon::Swapchain::chooseSwapPresentMode() {
	for (const auto &presentMode : m_swapchain_details.presentModes) {
		if (presentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			m_present_mode = presentMode;
			return;
		}
	}

	m_present_mode = VK_PRESENT_MODE_FIFO_KHR;
}


void carbon::Swapchain::chooseSwapExtent() {
	// copy assign so we don't get pointer errors
	VkSurfaceCapabilitiesKHR cap = m_swapchain_details.capabilities;

	if (cap.currentExtent.width != UINT32_MAX) {
		m_extent = cap.currentExtent;
		return;
	}

	// stores width and height of framebuffer
	int width{ 0 };
	int height{ 0 };

	glfwGetFramebufferSize(m_window, &width, &height);

	// create extent based on current extent
	VkExtent2D extent = { static_cast<uint32_t>(width), static_cast<uint32_t>(height) };

	// clamp extent within window bounds
	extent.width = std::max(cap.minImageExtent.width, std::min(cap.maxImageExtent.width, extent.width));
	extent.height = std::max(cap.minImageExtent.height, std::min(cap.maxImageExtent.height, extent.height));

	m_extent = extent;
}


void carbon::Swapchain::setup() {
	assert(m_logical_device && m_surface && "Logical device and surface must not be null.");

	querySwapchainSupport();
	chooseSwapSurfaceFormat();
	chooseSwapPresentMode();
	chooseSwapExtent();

	// get image format
	m_image_format = m_surface_format.format;

	// use one more than minimum so that we don't need to wait for driver
	// to finish before sending another image
	uint32_t imageCount = m_swapchain_details.capabilities.minImageCount + 1;

	if (m_swapchain_details.capabilities.maxImageCount > 0 && imageCount > m_swapchain_details.capabilities.maxImageCount) {
		imageCount = m_swapchain_details.capabilities.maxImageCount;
	}

	// fill in swapchain information
	VkSwapchainCreateInfoKHR createInfo;
	carbon::initStruct(createInfo, VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR);

	// specify surface to which the swapchain is tied
	createInfo.surface = m_surface->getHandle();

	// fill in details of swapchain images
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = m_surface_format.format;
	createInfo.imageColorSpace = m_surface_format.colorSpace;
	createInfo.imageExtent = m_extent;
	createInfo.imageArrayLayers = 1; // specifies number of layers each image consists of
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT; // specifies kind of operations that image will be used for
	// VK_IMAGE_USAGE_TRANSFER_DST_BIT -> used when rendering images to seperate image for post-processing

	// specify how to handle swapchain images that will be used across multiple queue families
	uint32_t graphicsFamily = m_logical_device->getGraphicsFamily();
	uint32_t presentFamily = m_logical_device->getPresentFamily();

	uint32_t queueIndices[] = { graphicsFamily, presentFamily };

	// ways to handle images accessed from multiple queues
	// - VK_SHARING_MODE_EXCLUSIVE : image is owned by one queue family at a time and ownership
	//   must be explicitly transferred before being used by another queue family (best performance)
	// - VK_SHARING_MODE_CONCURRENT : images can be used across multiple queue families without
	//   explicit ownership transfers
	if (graphicsFamily != presentFamily) {
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueIndices;
	} else {
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0;
		createInfo.pQueueFamilyIndices = nullptr;
	}

	// you can apply a transform to the image (set to current transform for no transformation)
	createInfo.preTransform = m_swapchain_details.capabilities.currentTransform;

	// ignore alpha channel (can be used for blending with other windows)
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = m_present_mode;

	// clip objects that are obscured (best performance)
	createInfo.clipped = VK_TRUE;

	// can specify previous swapchain if current one becomes invalid or unoptimized
	createInfo.oldSwapchain = VK_NULL_HANDLE;

	// create swapchain
	if (vkCreateSwapchainKHR(m_logical_device->getHandle(), &createInfo, nullptr, &m_swapchain) != VK_SUCCESS) {
		throw std::runtime_error("[ERROR] Failed to create swapchain!");
	}

	// get images from swapchain and put into vector
	vkGetSwapchainImagesKHR(m_logical_device->getHandle(), m_swapchain, &imageCount, nullptr);
	m_images.resize(imageCount);
	vkGetSwapchainImagesKHR(m_logical_device->getHandle(), m_swapchain, &imageCount, m_images.data());
}


void carbon::Swapchain::createImageViews() {
	assert(m_logical_device && "Logical device must not be null.");

	m_image_views.resize(m_images.size());

	// loop over swapchain images
	for (size_t i = 0; i < m_images.size(); i++) {
		VkImageViewCreateInfo createInfo;
		carbon::initStruct(createInfo, VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO);

		createInfo.image = m_images[i];

		// view type and format specify how image data should be interpreted
		createInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
		createInfo.format = m_image_format;

		// components allow you to map colour channels
		createInfo.components.r = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.g = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.b = VK_COMPONENT_SWIZZLE_IDENTITY;
		createInfo.components.a = VK_COMPONENT_SWIZZLE_IDENTITY;

		// subresourceRange describes what the purpose of the image is
		// and which parts should be accessed
		createInfo.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
		createInfo.subresourceRange.baseMipLevel = 0;
		createInfo.subresourceRange.levelCount = 1;
		createInfo.subresourceRange.baseArrayLayer = 0;
		createInfo.subresourceRange.layerCount = 1;

		// create image views
		if (vkCreateImageView(m_logical_device->getHandle(), &createInfo, nullptr, &m_image_views[i]) != VK_SUCCESS) {
			throw std::runtime_error("[ERROR] Failed to create image views!");
		}
	}
}


carbon::Swapchain::Swapchain(
	GLFWwindow *window,
	LogicalDevice *logiDevice,
	PhysicalDevice *physDevice,
	Surface *surface
)
	: m_window(window)
	, m_logical_device(logiDevice)
	, m_physical_device(physDevice)
	, m_surface(surface)
{
	assert(m_logical_device && m_physical_device && m_surface && "Logical device, physical device and surface must not be null.");
	recreate();
}


carbon::Swapchain::~Swapchain() {
	destroy();
}


void carbon::Swapchain::destroy() {
	assert(m_logical_device && "Logical device must not be null.");
	VkDevice device = m_logical_device->getHandle();

	// destroy image views
	for (size_t i = 0; i < m_image_views.size(); i++) {
		if (m_image_views[i] != VK_NULL_HANDLE) {
			vkDestroyImageView(device, m_image_views[i], nullptr);
			m_image_views[i] = VK_NULL_HANDLE;
		}
	}

	// destroy swapchain
	if (m_swapchain != VK_NULL_HANDLE) {
		vkDestroySwapchainKHR(device, m_swapchain, nullptr);
		m_swapchain = VK_NULL_HANDLE;
	}
}


void carbon::Swapchain::recreate() {
	setup();
	createImageViews();
}


VkResult carbon::Swapchain::acquireNextImage(const VkSemaphore &semaphore) {
	assert(m_logical_device && "Logical device must not be null.");
	return vkAcquireNextImageKHR(
		m_logical_device->getHandle(),
		m_swapchain,
		UINT64_MAX,
		semaphore,
		VK_NULL_HANDLE,
		&m_curr_image_idx
	);
}


VkResult carbon::Swapchain::queuePresent(const VkQueue &presentQueue, const VkSemaphore &semaphore) {
	VkPresentInfoKHR presentInfo;
	carbon::initStruct(presentInfo, VK_STRUCTURE_TYPE_PRESENT_INFO_KHR);

	// present to swapchain
	presentInfo.waitSemaphoreCount = 1;
	presentInfo.pWaitSemaphores = &semaphore;

	VkSwapchainKHR swapchains[]{ m_swapchain };

	presentInfo.swapchainCount = 1;
	presentInfo.pSwapchains = swapchains;
	presentInfo.pImageIndices = &m_curr_image_idx;
	presentInfo.pResults = nullptr;

	return vkQueuePresentKHR(presentQueue, &presentInfo);
}
