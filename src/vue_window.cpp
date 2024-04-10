#include "vue_window.hpp"
#include <stdexcept>
namespace vue {

	VueWindow::VueWindow(int w, int h, std::string name) : width{ w }, height{ h }, windowName{ name } {
		initWindow();
	}

	VueWindow::~VueWindow() {
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	void VueWindow::initWindow() {
		glfwInit();
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

		window = glfwCreateWindow(width, height, windowName.c_str(), nullptr, nullptr);
	}

	void VueWindow::createWindowSurface(VkInstance instance,  VkSurfaceKHR* surface) {
		if (glfwCreateWindowSurface(instance, window, nullptr, surface) != VK_SUCCESS) {
			throw std::runtime_error("Failed to create window surface");
		}
	}
}