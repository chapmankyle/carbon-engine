// file      : carbon/pipeline/render_pass.hpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#pragma once

#ifndef PIPELINE_RENDER_PASS_HPP
#define PIPELINE_RENDER_PASS_HPP

#include "carbon/backend.hpp"

#include <cassert>
#include <vector>

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
		 * @brief Determines what to do with data before and after rendering.
		 */
		std::vector<VkAttachmentDescription> m_attachment_descriptions;

		/**
		 * @brief Attachment references for the colours.
		 */
		std::vector<VkAttachmentReference> m_attachment_references;

		/**
		 * @brief The description of the subpasses to use.
		 */
		std::vector<VkSubpassDescription> m_subpass_descriptions;

		/**
		 * @brief Dependencies of each subpass.
		 */
		std::vector<VkSubpassDependency> m_subpass_dependencies;

		/**
		 * @brief Sets up defaults for the attachment descriptions.
		 */
		void setupAttachmentDescriptions();

		/**
		 * @brief Sets up defaults for the attachment references.
		 */
		void setupAttachmentReferences();

		/**
		 * @brief Sets up defaults for the subpass descriptions.
		 */
		void setupSubpassDescriptions();

		/**
		 * @brief Sets up defaults for the subpass dependencies.
		 */
		void setupSubpassDependencies();

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
		explicit RenderPass(const class LogicalDevice *device, const VkFormat &imageFormat);

		RenderPass(const RenderPass&) = delete;

		RenderPass& operator=(const RenderPass&) = delete;

		/**
		 * @brief Destructor for the render pass.
		 */
		~RenderPass();

		/**
		 * @brief Destroys the render pass.
		 */
		void destroy();

		/**
		 * @brief Sets the image format to use in the render pass.
		 * @param imageFormat The swapchain image format.
		 */
		void setImageFormat(const VkFormat imageFormat);

		/**
		 * @brief Sets the attachment descriptions to use in the render pass.
		 * @param descs The attachment descriptions to use.
		 */
		void setAttachmentDescriptions(const std::vector<VkAttachmentDescription> descs);

		/**
		 * @brief Sets the attachment references to use in the render pass.
		 * @param refs The attachment references to use.
		 */
		void setAttachmentReferences(const std::vector<VkAttachmentReference> refs);

		/**
		 * @brief Sets the subpass descriptions to use in the render pass.
		 * @param descs The subpass descriptions to use.
		 */
		void setSubpassDescriptions(const std::vector<VkSubpassDescription> descs);

		/**
		 * @brief Sets the subpass dependencies to use in the render pass.
		 * @param deps The subpass dependencies to use.
		 */
		void setSubpassDependencies(const std::vector<VkSubpassDependency> deps);

		/**
		 * @returns The handle on the underlying render pass.
		 */
		const VkRenderPass& getHandle() const {
			return m_render_pass;
		}

		/**
		 * @returns The colour attachment descriptions.
		 */
		const std::vector<VkAttachmentDescription>& getAttachmentDescriptions() const {
			return m_attachment_descriptions;
		}

		/**
		 * @returns The colour attachment references.
		 */
		const std::vector<VkAttachmentReference>& getAttachmentReferences() const {
			return m_attachment_references;
		}

		/**
		 * @returns The description of the subpasses.
		 */
		const std::vector<VkSubpassDescription>& getSubpassDescriptions() const {
			return m_subpass_descriptions;
		}

		/**
		 * @returns The dependencies of each subpass.
		 */
		const std::vector<VkSubpassDependency>& getSubpassDependencies() const {
			return m_subpass_dependencies;
		}

	};

} // namespace carbon

#endif // PIPELINE_RENDER_PASS_HPP
