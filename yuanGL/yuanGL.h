#pragma once

namespace yuanGL {

	void glfw_use_3_3_core();
	void glfw_print_version();
	void glfw_init();
	void blend_alpha();
	void set_swap_interval(bool v);
	unsigned int createShader(const std::string& vert, const std::string frag);
	unsigned int compileShader(unsigned int type, const std::string& src);

}
