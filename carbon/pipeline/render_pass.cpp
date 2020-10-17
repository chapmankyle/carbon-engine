#include "render_pass.hpp"

#include "carbon/core/logical_device.hpp"

void carbon::RenderPass::setupAttachmentDescription() {
	// single colour buffer attachment
	m_attachment_desc.format = m_image_format;
	m_attachment_desc.samples = VK_SAMPLE_COUNT_1_BIT;

	// determine what to do with data in attachment before and after rendering
	m_attachment_desc.loadOp = VK_ATTACHMENT_LOAD_OP_CLEAR; // clear values at start
	m_attachment_desc.storeOp = VK_ATTACHMENT_STORE_OP_STORE; // rendered constants will be stored in memory

	// apply colour and depth data
	m_attachment_desc.stencilLoadOp = VK_ATTACHMENT_LOAD_OP_DONT_CARE;
	m_attachment_desc.stencilStoreOp = VK_ATTACHMENT_STORE_OP_DONT_CARE;

	// decide on layout of images being rendered
	m_attachment_desc.initialLayout = VK_IMAGE_LAYOUT_UNDEFINED;
	m_attachment_desc.finalLayout = VK_IMAGE_LAYOUT_PRESENT_SRC_KHR; // images to be presented in swap chain
}


void carbon::RenderPass::setupAttachmentReference() {
	// attachment reference for colours
	m_attachment_ref.attachment = 0;
	m_attachment_ref.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;
}


void carbon::RenderPass::setupSubpassDescription() {
	// create the subpass
	m_subpass_desc.pipelineBindPoint = VK_PIPELINE_BIND_POINT_GRAPHICS;

	// add colour attachment to subpass
	m_subpass_desc.colorAttachmentCount = 1;
	m_subpass_desc.pColorAttachments = &m_attachment_ref;
}


void carbon::RenderPass::setupSubpassDependency() {
	// specify dependency for subpass
	m_subpass_dep.srcSubpass = VK_SUBPASS_EXTERNAL;
	m_subpass_dep.dstSubpass = 0;

	m_subpass_dep.srcStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	m_subpass_dep.srcAccessMask = 0;

	m_subpass_dep.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	m_subpass_dep.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;
}


void carbon::RenderPass::setup() {
	// setup individual components
	setupAttachmentDescription();
	setupAttachmentReference();
	setupSubpassDescription();
	setupSubpassDependency();
}


void carbon::RenderPass::create() {
	// describe render pass
	VkRenderPassCreateInfo renderPassInfo;
	carbon::initStruct(renderPassInfo, VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO);

	renderPassInfo.attachmentCount = 1;
	renderPassInfo.pAttachments = &m_attachment_desc;
	renderPassInfo.subpassCount = 1;
	renderPassInfo.pSubpasses = &m_subpass_desc;
	renderPassInfo.dependencyCount = 1;
	renderPassInfo.pDependencies = &m_subpass_dep;

	// create render pass
	if (vkCreateRenderPass(m_logical_device->getHandle(), &renderPassInfo, nullptr, &m_render_pass) != VK_SUCCESS) {
		throw std::runtime_error("[ERROR] Failed to create render pass!");
	}
}


carbon::RenderPass::RenderPass(carbon::LogicalDevice *device, const VkFormat &imageFormat)
	: m_logical_device(device)
	, m_image_format(imageFormat)
{
	setup();
	create();
}


carbon::RenderPass::~RenderPass() {
	destroy();
}


void carbon::RenderPass::destroy() {
	assert(m_logical_device && "Logical device must not be null.");

	if (m_render_pass == VK_NULL_HANDLE) {
		return;
	}

	// destroy render pass
	vkDestroyRenderPass(m_logical_device->getHandle(), m_render_pass, nullptr);
	m_render_pass = VK_NULL_HANDLE;
}


void carbon::RenderPass::setImageFormat(const VkFormat imageFormat) {
	m_image_format = imageFormat;

	setupAttachmentDescription();
	create();
}


void carbon::RenderPass::setAttachmentDescription(const VkAttachmentDescription desc) {
	m_attachment_desc = desc;
	create();
}


void carbon::RenderPass::setAttachmentReference(const VkAttachmentReference ref) {
	m_attachment_ref = ref;

	setupSubpassDescription();
	create();
}


void carbon::RenderPass::setSubpassDescription(const VkSubpassDescription desc) {
	m_subpass_desc = desc;
	create();
}


void carbon::RenderPass::setSubpassDependency(const VkSubpassDependency dependency) {
	m_subpass_dep = dependency;
	create();
}
