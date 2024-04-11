#pragma once

#include "vue_device.hpp"
#include "vue_pipeline.hpp"
#include "vue_window.hpp"
#include "vue_swap_chain.hpp"

// std

#include <memory>

namespace vue {
	class FirstApp {
	public:
		static constexpr int WIDTH = 1600;
		static constexpr int HEIGHT = 900;

		FirstApp();
		~FirstApp();

		FirstApp(const FirstApp&) = delete;
		FirstApp& operator==(const FirstApp) = delete;

		void run();

	private:
		void createPipelineLayout();
		void createPipeline();
		void createCommandBuffers();
		void drawFrame();

		VueWindow vueWindow { WIDTH, HEIGHT, "Sandbox" };
		VueDevice vueDevice {vueWindow};
		VueSwapChain vueSwapChain{vueDevice, vueWindow.getExtent()};
		std::unique_ptr<VuePipeline> vuePipeline;
		VkPipelineLayout pipelineLayout;
		std::vector<VkCommandBuffer> commandBuffers;
	};
}