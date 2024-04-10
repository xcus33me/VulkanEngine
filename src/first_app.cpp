#include "first_app.hpp"

namespace vue{

	void FirstApp::run() {
		while (!this->vueWindow.shouldClose()) {
			glfwPollEvents();
		}
	}

}