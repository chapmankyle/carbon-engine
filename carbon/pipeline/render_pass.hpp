#pragma once

#ifndef PIPELINE_RENDER_PASS_HPP
#define PIPELINE_RENDER_PASS_HPP

#include "carbon/setup.hpp"
#include <cassert>

namespace carbon {

	// forward-declare classes that would result in circular dependency
	class LogicalDevice;

	/**
	 * @brief A wrapper for the Vulkan render pass that allows objects
	 * to be drawn onto render targets (framebuffer attachments).
	 */
	class RenderPass {

		private:

		/**
		 * @brief The logical device to use in the swapchain.
		 */
		const class LogicalDevice *m_logical_device;

		/**
		 * @brief The format of the swapchain images.
		 */
		VkFormat m_image_format;

		/**
		 * @brief Handle on the underlying render pass.
		 */
		VkRenderPass m_render_pass{ VK_NULL_HANDLE };

		/**
		 * @brief The attachment description to determine what to do
		 * with data before and after rendering.
		 */
		VkAttachmentDescription m_attachment_desc{};

		/**
		 * @brief Attachment reference for the colours.
		 */
		VkAttachmentReference m_attachment_ref{};

		/**
		 * @brief The description of the subpass to use.
		 */
		VkSubpassDescription m_subpass_desc{};

		/**
		 * @brief Dependencies of the subpass.
		 */
		VkSubpassDependency m_subpass_dep{};

		/**
		 * @brief Sets up defaults for the attachment description.
		 */
		void setupAttachmentDescription();

		/**
		 * @brief Sets up defaults for the attachment reference.
		 */
		void setupAttachmentReference();

		/**
		 * @brief Sets up defaults for the subpass description.
		 */
		void setupSubpassDescription();

		/**
		 * @brief Sets up defaults for the subpass dependency.
		 */
		void setupSubpassDependency();

		/**
		 * @brief Sets up the render pass with default parameters.
		 */
		void setup();

		/**
		 * @brief Creates the render pass create info to create the
		 * render pass.
		 */
		void create();

	public:

		/**
		 * @brief Initializes the render pass using the given logical device.
		 * @param device The logical device to use for creating the render pass.
		 * @param imageFormat The format of the swapchain images.
		 */
		explicit RenderPass(class LogicalDevice *device, const VkFormat &imageFormat);

		/**
		 * @brief Destructor for the render pass.
		 */
		~RenderPass();

		/**
		 * @brief Destroys the render pass.
		 */
		void destroy();

		/**
		 * @returns The handle on the underlying render pass.
		 */
		const VkRenderPass& getHandle() const {
			return m_render_pass;
		}

		/**
		 * @returns The colour attachment description.
		 */
		const VkAttachmentDescription& getAttachmentDescription() const {
			return m_attachment_desc;
		}

		/**
		 * @returns The colour attachment reference.
		 */
		const VkAttachmentReference& getAttachmentReference() const {
			return m_attachment_ref;
		}

		/**
		 * @returns The description of the subpass.
		 */
		const VkSubpassDescription& getSubpassDescription() const {
			return m_subpass_desc;
		}

		/**
		 * @returns The dependency of the subpass.
		 */
		const VkSubpassDependency& getSubpassDependency() const {
			return m_subpass_dep;
		}

		/**
		 * @brief Sets the image format to use in the render pass.
		 * @param imageFormat The swapchain image format.
		 */
		void setImageFormat(const VkFormat imageFormat);

		/**
		 * @brief Sets the attachment description to use in the render pass.
		 * @param desc The attachment description to use.
		 */
		void setAttachmentDescription(const VkAttachmentDescription desc);

		/**
		 * @brief Sets the attachment reference to use in the render pass.
		 * @param ref The attachment reference to use.
		 */
		void setAttachmentReference(const VkAttachmentReference ref);

		/**
		 * @brief Sets the subpass description to use in the render pass.
		 * @param desc The subpass description to use.
		 */
		void setSubpassDescription(const VkSubpassDescription desc);

		/**
		 * @brief Sets the subpass dependency to use in the render pass.
		 * @param dependency The subpass dependency to use.
		 */
		void setSubpassDependency(const VkSubpassDependency dependency);

	};

} // namespace carbon

#endif
