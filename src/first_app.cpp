#include "first_app.hpp"

namespace vue{

	void FirstApp::run() {


		while (!VueWindow.shouldClose()) {
			glfwPollEvents();
		}
	}

}