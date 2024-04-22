#include "first_app.hpp"

// std
#include <array>
#include <stdexcept>

namespace vue{

	FirstApp::FirstApp() {
		loadModels();
		createPipelineLayout();
		createPipeline();
		createCommandBuffers();
	}

	FirstApp::~FirstApp() {
		vkDestroyPipelineLayout(vueDevice.device(), pipelineLayout, nullptr);
	}

	void FirstApp::run() {
		while (!this->vueWindow.shouldClose()) {
			glfwPollEvents();
			drawFrame();
		}

		vkDeviceWaitIdle(vueDevice.device());
	}

	void FirstApp::loadModels() {
		std::vector<VueModel::Vertex> vertices {
			{{0.0f, -0.5f}},
			{{0.5f, 0.5f}},
			{{-0.5f, 0.5f}}
		};

		vueModel = std::make_unique<VueModel>(vueDevice, vertices);
	}

	void FirstApp::createPipelineLayout() {
		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};
		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = 0;
		pipelineLayoutInfo.pSetLayouts = nullptr;
		pipelineLayoutInfo.pushConstantRangeCount = 0;
		pipelineLayoutInfo.pPushConstantRanges = nullptr; // Effeciently send a small amount of data to our shader programs

		if (vkCreatePipelineLayout(this->vueDevice.device(), &pipelineLayoutInfo, nullptr, &pipelineLayout) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create pipeline layout!");
		}
	}
	
	void FirstApp::createPipeline() {
		PipelineConfigInfo pipelineConfig{};
		VuePipeline::defaultPipelineConfigInfo(
			pipelineConfig, 
			vueSwapChain.width(),
			vueSwapChain.height());
		pipelineConfig.renderPass = vueSwapChain.getRenderPass();
		pipelineConfig.pipelineLayout = pipelineLayout;
		vuePipeline = std::make_unique<VuePipeline>(
			vueDevice,
			"shaders/simple_shader.vert.spv",
			"shaders/simple_shader.frag.spv",
			pipelineConfig
		);
	}

	void FirstApp::createCommandBuffers() {
		commandBuffers.resize(vueSwapChain.imageCount());


		VkCommandBufferAllocateInfo allocateInfo{};
		allocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocateInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocateInfo.commandPool = vueDevice.getCommandPool();
		allocateInfo.commandBufferCount = static_cast<uint32_t>(commandBuffers.size());

		if (vkAllocateCommandBuffers(vueDevice.device(), &allocateInfo, commandBuffers.data()) != VK_SUCCESS) {
			throw std::runtime_error("Failed to allocate command buffers!");
		}

		for (int i = 0; i < commandBuffers.size(); ++i) {
			VkCommandBufferBeginInfo beginInfo{};
			beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
			
			if (vkBeginCommandBuffer(commandBuffers[i], &beginInfo) != VK_SUCCESS) {
				throw std::runtime_error("Failed to begin recording command buffer!");
			}

			VkRenderPassBeginInfo renderPassInfo{};
			renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
			renderPassInfo.renderPass = vueSwapChain.getRenderPass();
			renderPassInfo.framebuffer = vueSwapChain.getFrameBuffer(i);

			renderPassInfo.renderArea.offset = {0, 0};
			renderPassInfo.renderArea.extent = vueSwapChain.getSwapChainExtent();

			std::array<VkClearValue, 2> clearValues{};
			clearValues[0].color = {0.1f, 0.1f, 0.1f, 1.0f};
			clearValues[1].depthStencil = {1.0f, 0};
			renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
			renderPassInfo.pClearValues = clearValues.data();

			vkCmdBeginRenderPass(commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

			vuePipeline->bind(commandBuffers[i]);
			vueModel->bind(commandBuffers[i]);
			vueModel->draw(commandBuffers[i]);

			vkCmdEndRenderPass(commandBuffers[i]);
			if (vkEndCommandBuffer(commandBuffers[i]) != VK_SUCCESS) {
				throw std::runtime_error("failed to record command buffer!");
			}
		}		
	}

	void FirstApp::drawFrame() {
		uint32_t imageIndex;
		auto result = vueSwapChain.acquireNextImage(&imageIndex);

		if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			throw std::runtime_error("failed to acquire swap chain image!");
		}

		result = vueSwapChain.submitCommandBuffers(&commandBuffers[imageIndex], &imageIndex);
		if (result != VK_SUCCESS) {
			throw std::runtime_error("Failed to present swap chain image!");
		}
	}

}