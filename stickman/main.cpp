#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "main_window.h"

int main(void)
{
    {
        stickman::MainWindow window;
        window.set_clear_color(0.0f, 0.0f, 0.0f, 1.0f);
        window.start_loop_fps(120);
    }

    yuanGL::YuanWindow::terminate();
}