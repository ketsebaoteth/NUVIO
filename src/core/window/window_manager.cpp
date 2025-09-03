#include "glad/glad.h"
#include "core/window/window_manager.h"
#include "core/shortcut/registery.h"
#include <iostream>
#include <cassert>
#include "Tracy.hpp"

NUVIO_NAMESPACE_BEGIN

void window_manager::create_window(std::string title, window_flags flags)
{
    m_flags = flags;
    //Initalize GLFW before anything
    glfwInit();

    glfwWindowHint(GLFW_RESIZABLE, flags & WINDOW_FLAG_RESIZABLE ? GLFW_TRUE : GLFW_FALSE);
    glfwWindowHint(GLFW_DECORATED, flags & WINDOW_FLAG_BORDERLESS ? GLFW_FALSE : GLFW_TRUE);
    glfwWindowHint(GLFW_MAXIMIZED, flags & WINDOW_FLAG_MAXIMIZED ? GLFW_TRUE : GLFW_FALSE);
    //TODO: Handle fullscreen flag

    assert(m_size.x > 0 && m_size.y > 0 && "Window size must be set before creating a window");

    GLFWwindow* window = glfwCreateWindow(m_size.x, m_size.y, title.c_str(), nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
    }
    m_window = window;
    glfwMakeContextCurrent(m_window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
    }
    //registers all shortcuts in shortcut registery
    //look at core/shortcut/registery.cpp
    nuvio::register_all_shortcuts();
}

void window_manager::destroy_window() {
    assert(m_window && "Window must be created before it can be destroyed");
    if (m_window) {
        glfwDestroyWindow(m_window);
        m_window = nullptr;
    }
}

bool window_manager::should_close() const {
    assert(m_window && "Window must be created before it can be checked for closing");
    return m_window && glfwWindowShouldClose(m_window);
}

void window_manager::swap_buffers() const {
    ZoneScopedN("window_manager::swap_buffers");
    assert(m_window && "Window must be created before buffers can be swapped");
    if (m_window)
        glfwSwapBuffers(m_window);
}

void window_manager::poll_events() const {
    assert(m_window && "Window must be created before events can be polled");
    if (m_window)
        glfwPollEvents();
}

GLFWwindow* window_manager::get_window() const {
    assert(m_window && "Window must be created before it can be retrieved");
    return m_window;
}

void window_manager::set_window_size(int width, int height) {
    assert(width > 0 && height > 0 && "Width and Height must be positive values and non zero");
    m_size.x = width;
    m_size.y = height;

    if (m_window)
        glfwSetWindowSize(m_window, width, height);
}

vec2<int> window_manager::get_size() const {
    return m_size;
}

window_manager gWindowManager;

NUVIO_NAMESPACE_END
