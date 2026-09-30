#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "demo_window.h"

int main(void)
{
    {
        stickman::DemoWindow window(960, 540, "stickman");
        window.print_gl_version();
        window.set_swap_interval(true);
        window.set_clear_color(0.f, 0.3f, 0.8f, 1.0f);
        window.start_loop();
    }

    yuanGL::YuanWindow::terminate();
}