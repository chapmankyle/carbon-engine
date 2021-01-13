// file      : carbon/display/swapchain.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef DISPLAY_SWAPCHAIN_HPP
#define DISPLAY_SWAPCHAIN_HPP

#include "carbon/backend.hpp"

#include <vector>

namespace carbon {

	// forward-declare classes that would result in circular dependency
	class PhysicalDevice;
	class LogicalDevice;
	class RenderPass;
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
		 * @brief The render pass used for drawing.
		 */
		const class RenderPass *m_render_pass;

		/**
		 * @brief The surface to use in the swapchain.
		 */
		const class Surface *m_surface;

		/**
		 * @brief The window to use when creating the swapchain.
		 */
		GLFWwindow *m_window;

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
		u32 m_curr_image_idx{};

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
		 * @brief The framebuffers for the swapchain images.
		 */
		std::vector<VkFramebuffer> m_framebuffers;

		/**
		 * @brief Queries the swapchain support of a device.
		 * @returns The `SupportDetails` struct containing support information for the swapchain.
		 */
		SupportDetails querySwapchainSupport();

		/**
		 * @brief Selects the swap surface format from the given formats.
		 * @param availableFormats The formats to choose from.
		 * @param format The format to look for.
		 * @param colourSpace The colour space to look for.
		 * @returns The surface format that has the given format and colour space, otherwise
		 * the first entry in the `availableFormats` vector.
		 */
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(
			const std::vector<VkSurfaceFormatKHR> &availableFormats,
			const VkFormat &format,
			const VkColorSpaceKHR &colourSpace
		);

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
		 * @param availableModes The presentation modes to choose from.
		 * @param mode The desired presentation mode.
		 * @returns The desired presentation mode if it exists in `availableModes`, otherwise `VK_PRESENT_MODE_FIFO_KHR`.
		 */
		VkPresentModeKHR chooseSwapPresentMode(
			const std::vector<VkPresentModeKHR> &availableModes,
			const VkPresentModeKHR &mode
		);

		/**
		 * @brief Selects the resolution for the swapchain images using the given capabilities.
		 * @param capabilities The surface capabilities.
		 * @returns The extent to use for swapchain images.
		 */
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR &capabilities);

		/**
		 * @brief Sets up the swapchain resources.
		 */
		void setup();

		/**
		 * @brief Creates the image views from the images in the swapchain, allowing for
		 * rendering to take place.
		 */
		void createImageViews();

		/**
		 * @brief Creates the render pass that specifies information about the framebuffer
		 * attachments and how many colour and depth buffers there will be.
		 */
		void createRenderPass();

		/**
		 * @brief Creates the framebuffers that will be used for rendering the
		 * swapchain images. We have to create a framebuffer for each image in
		 * the swapchain and use the one that corresponds to the retrieved image
		 * at draw time.
		 */
		void createFramebuffers();

	public:

		/**
		 * @brief Initializes the swapchain using the current window.
		 * @param width The width of the swapchain images.
		 * @param height The height of the swapchain images.
		 * @param logiDevice The logical device to use.
		 * @param physDevice The physical device (GPU) to use.
		 * @param surface The device surface.
		 */
		explicit Swapchain(
			GLFWwindow *window,
			class LogicalDevice *logiDevice,
			class PhysicalDevice *physDevice,
			class Surface *surface
		);

		Swapchain(const Swapchain&) = delete;

		Swapchain& operator=(const Swapchain&) = delete;

		/**
		 * @brief Destructor for the swapchain.
		 */
		~Swapchain();

		/**
		 * @brief Destroys the swapchain.
		 */
		void destroy();

		/**
		 * @brief Recreates the swapchain by checking the size of the framebuffer.
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
		 * @returns The window used when creating the swapchain.
		 */
		GLFWwindow* getWindow() const {
			return m_window;
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
		const u32 getCurrentImageIndex() const {
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

#endif // DISPLAY_SWAPCHAIN_HPP
