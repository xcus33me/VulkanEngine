#pragma once

#include "vue_device.hpp"
#include "vue_pipeline.hpp"
#include "vue_window.hpp"
#include "vue_swap_chain.hpp"

namespace vue {
	class FirstApp {
	public:
		static constexpr int WIDTH = 1600;
		static constexpr int HEIGHT = 900;

		void run();
	private:
		VueWindow vueWindow { WIDTH, HEIGHT, "Sandbox" };
		VueDevice vueDevice {vueWindow};
		VueSwapChain vueSwapChain{vueDevice, vueWindow.getExtent()};
		VuePipeline VuePipeline {
			vueDevice,
			"../shaders/simple_shader.vert.spv",
			"../shaders/simple_shader.frag.spv",
			VuePipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
	};
}