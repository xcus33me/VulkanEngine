#pragma once

#define GLFW_INCLUDE_VULKAN
#include "GLFW/glfw3.h"
#include <vulkan/vulkan.h>

#include <string>

namespace vue {

	class VueWindow {
	public:
		VueWindow(int w, int h, std::string name);
		~VueWindow();

		VueWindow(const VueWindow&) = delete;
		VueWindow &operator=(const VueWindow&) = delete;

		bool shouldClose() { return glfwWindowShouldClose(window); }
		VkExtent2D getExtent() { return {static_cast<uint32_t>(width), static_cast<uint32_t>(height)}; }

		void createWindowSurface(VkInstance instance,  VkSurfaceKHR* surface);
	private:
		void initWindow();

		GLFWwindow* window;
		std::string windowName;

		const int width;
		const int height;
	};

}
