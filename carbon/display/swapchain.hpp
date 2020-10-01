#pragma once

#ifndef DISPLAY_SWAPCHAIN_HPP
#define DISPLAY_SWAPCHAIN_HPP

#include "carbon/setup.hpp"
#include <cassert>
#include <vector>

namespace carbon {

	// forward-declare classes that would result in circular dependency
	class PhysicalDevice;
	class LogicalDevice;
	class Surface;

	/**
	 * @brief A wrapper for the Vulkan swapchain that queues images to be
	 * rendered on-screen.
	 */
	class Swapchain {

	private:

		/**
		 * @brief Support details for the swapchain.
		 */
		struct SupportDetails {
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;
		};

		/**
		 * @brief The physical device to use in the swapchain.
		 */
		const class PhysicalDevice *m_physical_device;

		/**
		 * @brief The logical device to use in the swapchain.
		 */
		const class LogicalDevice *m_logical_device;

		/**
		 * @brief The surface to use in the swapchain.
		 */
		const class Surface *m_surface;

		/**
		 * @brief Handle on the underlying swapchain.
		 */
		VkSwapchainKHR m_swapchain{ VK_NULL_HANDLE };

		/**
		 * @brief Handle on the surface format for the swapchain.
		 */
		VkSurfaceFormatKHR m_surface_format;

		/**
		 * @brief Handle on the presentation mode.
		 */
		VkPresentModeKHR m_present_mode;

		/**
		 * @brief Handle on the swapchain extent.
		 */
		VkExtent2D m_extent;

		/**
		 * @brief The image format used in the swapchain.
		 */
		VkFormat m_image_format;

		/**
		 * @brief Index of the current image in the swapchain.
		 */
		uint32_t m_curr_image_idx{};

		/**
		 * @brief The support details of the swapchain.
		 */
		SupportDetails m_swapchain_details;

		/**
		 * @brief The images currently in the swapchain.
		 */
		std::vector<VkImage> m_images;

		/**
		 * @brief The image views for the images in the swapchain.
		 */
		std::vector<VkImageView> m_image_views;

		/**
		 * @brief Queries the swapchain support of a device.
		 */
		void querySwapchainSupport();

		/**
		 * @brief Selects the swap surface format.
		 */
		void chooseSwapSurfaceFormat();

		/**
		 * @brief Selects the swap presentation mode.
		 * - VK_PRESENT_MODE_IMMEDIATE_KHR : images submitted are immediately displayed to screen (tearing)
		 * - VK_PRESENT_MODE_FIFO_KHR : display takes image from front of queue and program inserts rendered
		 * images at back of queue. If queue is full, program was to wait. Similar to vertical sync (vsync).
		 * - VK_PRESENT_MODE_FIFO_RELAXED : if queue is empty, instead of waiting for vertcial blank (moment
		 * the display is refreshed), the image is immediately displayed.
		 * - VK_PRESENT_MODE_MAILBOX_KHR : instead of blocking application when queue is full, the images
		 * that are already queued are replaced with newer ones. Can be used to implement triple buffering,
		 * as opposed to double buffering used by vsync.
		 */
		void chooseSwapPresentMode();

		/**
		 * @brief Selects the resolution for the swapchain images. Width and height of image is in
		 * `currentExtent` member, but if set to UINT32_MAX, then we set the resolution to one
		 * that best matches the window within the `minImageExtent` and `maxImageExtent` bounds.
		 */
		void chooseSwapExtent();

		/**
		 * @brief Sets up the swapchain resources.
		 */
		void setup();

		/**
		 * @brief Creates the image views from the images in the swapchain, allowing for
		 * rendering to take place.
		 */
		void createImageViews();

	public:

		/**
		 * @brief Initializes the swapchain.
		 * @param width The width of the swapchain images.
		 * @param height The height of the swapchain images.
		 * @param logiDevice The logical device to use.
		 * @param physDevice The physical device (GPU) to use.
		 * @param surface The device surface.
		 */
		explicit Swapchain(
			uint32_t width,
			uint32_t height,
			class LogicalDevice *logiDevice,
			class PhysicalDevice *physDevice,
			class Surface *surface
		);

		/**
		 * @brief Initializes the swapchain.
		 * @param extent The swapchain image extent.
		 * @param logiDevice The logical device to use.
		 * @param physDevice The physical device (GPU) to use.
		 * @param surface The device surface.
		 */
		explicit Swapchain(
			const VkExtent2D &extent,
			class LogicalDevice *logiDevice,
			class PhysicalDevice *physDevice,
			class Surface *surface
		);

		/**
		 * @brief Destructor for the swapchain.
		 */
		~Swapchain();

		/**
		 * @brief Destroys the swapchain.
		 */
		void destroy();

		/**
		 * @brief Recreates the swapchain using a different extent.
		 * @param extent The extent to use for the swapchain images.
		 */
		void recreate(const VkExtent2D &extent);

		/**
		 * @brief Recreates the swapchain using the same extent used by previous
		 * swapchain.
		 */
		void recreate();

		/**
		 * @brief Acquire the next image from the swapchain.
		 * @param semaphore The semaphore to use for aquiring the next image.
		 * @returns `VK_SUCCESS` if successful.
		 */
		VkResult acquireNextImage(const VkSemaphore &semaphore);

		/**
		 * @brief Present the swapchain queue.
		 * @param presentQueue The presentation queue to show.
		 * @param semaphore The semaphore to use for waiting.
		 * @returns `VK_SUCCESS` if successful.
		 */
		VkResult queuePresent(const VkQueue &presentQueue, const VkSemaphore &semaphore);

		/**
		 * @returns The handle of the underlying swapchain.
		 */
		const VkSwapchainKHR& getHandle() const {
			return m_swapchain;
		}

		/**
		 * @returns The surface format for the swapchain.
		 */
		const VkSurfaceFormatKHR& getSurfaceFormat() const {
			return m_surface_format;
		}

		/**
		 * @returns The presentation mode for the swapchain.
		 */
		const VkPresentModeKHR& getPresentMode() const {
			return m_present_mode;
		}

		/**
		 * @returns The swapchain image extent.
		 */
		const VkExtent2D& getExtent() const {
			return m_extent;
		}

		/**
		 * @returns The image format for the swapchain.
		 */
		const VkFormat& getImageFormat() const {
			return m_image_format;
		}

		/**
		 * @returns The current image in the swapchain.
		 */
		const VkImage& getCurrentImage() const {
			return m_images[m_curr_image_idx];
		}

		/**
		 * @returns The current image view in the swapchain.
		 */
		const VkImageView& getCurrentImageView() const {
			return m_image_views[m_curr_image_idx];
		}

		/**
		 * @returns The index of the current image in the swapchain.
		 */
		const uint32_t getCurrentImageIndex() const {
			return m_curr_image_idx;
		}

		/**
		 * @returns The number of images in the swapchain.
		 */
		const size_t getImageCount() const {
			return m_images.size();
		}

		/**
		 * @returns The number of image views in the swapchain.
		 */
		const size_t getImageViewCount() const {
			return m_image_views.size();
		}

		/**
		 * @returns The images in the swapchain.
		 */
		const std::vector<VkImage>& getImages() const {
			return m_images;
		}

		/**
		 * @returns The image views in the swapchain.
		 */
		const std::vector<VkImageView>& getImageViews() const {
			return m_image_views;
		}

	};

} // namespace carbon

#endif // !DISPLAY_SWAPCHAIN_HPP
