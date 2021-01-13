// file      : carbon/pipeline/render_pass.cpp
// copyright : Copyright (c) 2020-present, Kyle Chapman
// license   : GPL-3.0; see accompanying LICENSE file

#include "render_pass.hpp"

#include "carbon/common/logger.hpp"
#include "carbon/core/logical_device.hpp"

#include <cassert>

namespace carbon {

	void RenderPass::setupAttachmentDescriptions() {
		// single colour buffer attachment
		VkAttachmentDescription desc{};
		desc.format = m_image_format;
		desc.samples = VK_SAMPLE_COUNT_1_BIT;

		// determine what to do with data in attachment before and after rendering
		desc.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR; // clear values at start
		desc.storeOp = VK_ATTACHMENT_STORE_OP_STORE; // rendered constants will be stored in memory

		// apply colour and depth data
		desc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
		desc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

		// decide on layout of images being rendered
		desc.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
		desc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR; // images to be presented in swap chain

		// put into vector
		m_attachment_descriptions.clear();
		m_attachment_descriptions.push_back(desc);
	}


	void RenderPass::setupAttachmentReferences() {
		m_attachment_references.clear();

		// attachment references for each attachment description
		for (int i = 0; i < m_attachment_descriptions.size(); i++) {
			VkAttachmentReference ref{};
			ref.attachment = 0;
			ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

			// add to vector
			m_attachment_references.push_back(ref);
		}
	}


	void RenderPass::setupSubpassDescriptions() {
		// create the subpass
		VkSubpassDescription desc{};
		desc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

		// add colour attachment to subpass
		desc.colorAttachmentCount = static_cast<uint32_t>(m_attachment_references.size());
		desc.pColorAttachments = m_attachment_references.data();

		// put into vector
		m_subpass_descriptions.clear();
		m_subpass_descriptions.push_back(desc);
	}


	void RenderPass::setupSubpassDependencies() {
		m_subpass_dependencies.clear();

		VkSubpassDependency dep{};
		dep.srcSubpass = VK_SUBPASS_EXTERNAL;
		dep.dstSubpass = 0;

		dep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dep.srcAccessMask = 0;

		dep.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
		dep.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;

		// add to vector
		m_subpass_dependencies.push_back(dep);
	}


	void RenderPass::setup() {
		// setup individual components
		setupAttachmentDescriptions();
		setupAttachmentReferences();
		setupSubpassDescriptions();
		setupSubpassDependencies();
	}


	void RenderPass::create() {
		assert(m_logical_device && "Logical device cannot be null.");

		// describe render pass
		VkRenderPassCreateInfo renderPassInfo;
		initStruct(renderPassInfo, VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO);

		renderPassInfo.attachmentCount = static_cast<uint32_t>(m_attachment_descriptions.size());
		renderPassInfo.pAttachments = m_attachment_descriptions.data();

		renderPassInfo.subpassCount = static_cast<uint32_t>(m_subpass_descriptions.size());
		renderPassInfo.pSubpasses = m_subpass_descriptions.data();

		renderPassInfo.dependencyCount = static_cast<uint32_t>(m_subpass_dependencies.size());
		renderPassInfo.pDependencies = m_subpass_dependencies.data();

		// create render pass
		if (vkCreateRenderPass(m_logical_device->getHandle(), &renderPassInfo, nullptr, &m_render_pass) != VK_SUCCESS) {
			CARBON_LOG_FATAL(carbon::log::To::File, "Failed to create render pass.");
		}
	}


	RenderPass::RenderPass(const LogicalDevice *device, const VkFormat &imageFormat)
		: m_logical_device(device)
		, m_image_format(imageFormat)
	{
		setup();
		create();
	}


	RenderPass::~RenderPass() {
		destroy();
	}


	void RenderPass::destroy() {
		assert(m_logical_device && "Logical device must not be null.");

		if (m_render_pass == VK_NULL_HANDLE) {
			return;
		}

		// destroy render pass
		vkDestroyRenderPass(m_logical_device->getHandle(), m_render_pass, nullptr);
		m_render_pass = VK_NULL_HANDLE;
	}


	void RenderPass::setImageFormat(const VkFormat &imageFormat) {
		m_image_format = imageFormat;

		setupAttachmentDescriptions();
		create();
	}


	void RenderPass::setAttachmentDescriptions(const std::vector<VkAttachmentDescription> &descs) {
		m_attachment_descriptions = descs;
		create();
	}


	void RenderPass::setAttachmentReferences(const std::vector<VkAttachmentReference> &refs) {
		m_attachment_references = refs;

		setupSubpassDescriptions();
		create();
	}


	void RenderPass::setSubpassDescriptions(const std::vector<VkSubpassDescription> &descs) {
		m_subpass_descriptions = descs;

		setupSubpassDependencies();
		create();
	}


	void RenderPass::setSubpassDependencies(const std::vector<VkSubpassDependency> &deps) {
		m_subpass_dependencies = deps;
		create();
	}

} // namespace carbon
