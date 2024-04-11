#include "first_app.hpp"

// std
#include <stdexcept>

namespace vue{

	void FirstApp::run() {
		while (!this->vueWindow.shouldClose()) {
			glfwPollEvents();
		}
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
		auto pipelineConfig = VuePipeline::defaultPipelineConfigInfo(vueSwapChain.width(), vueSwapChain.height());
		pipelineConfig.renderPass = vueSwapChain.getRenderPass();
	}

	void FirstApp::createCommandBuffer() {

	}

	void FirstApp::drawFrame() {

	}

}