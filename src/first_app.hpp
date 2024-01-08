#pragma once

#include "vue_window.hpp"
#include "vue_pipeline.hpp"

namespace vue {
	class FirstApp {
	public:
		static constexpr int WIDTH = 1600;
		static constexpr int HEIGHT = 900;

		void run();
	private:
		VueWindow VueWindow { WIDTH, HEIGHT, "Sandbox" };
		VueDevice VueDevice {VueWindow};
		VuePipeline VuePipeline {
			VueDevice,
			"../shaders/simple_shader.vert.spv",
			"../shaders/simple_shader.frag.spv",
			VuePipeline::defaultPipelineConfigInfo(WIDTH, HEIGHT)};
	};
}