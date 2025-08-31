#pragma once
#include "core/nuvio_namespaces.h"
#include "GLFW/glfw3.h"
#include <string>
#include "core/utils/vector.h"

NUVIO_NAMESPACE_BEGIN

enum window_flags
{
    WINDOW_FLAG_RESIZABLE = 1 << 0,
    WINDOW_FLAG_FULLSCREEN = 1 << 1,
    WINDOW_FLAG_BORDERLESS = 1 << 2,
    WINDOW_FLAG_MAXIMIZED = 1 << 3
};

inline window_flags operator|(window_flags a, window_flags b)
{
    return static_cast<window_flags>(static_cast<int>(a) | static_cast<int>(b));
}

class window_manager
{
public:
    /**
     * Creates a new window.
     * @param title The title of the window.
     * @param flags The flags for the window.
     */
    void create_window(std::string title, window_flags flags = static_cast<window_flags>(WINDOW_FLAG_BORDERLESS | WINDOW_FLAG_RESIZABLE | WINDOW_FLAG_FULLSCREEN));
    void destroy_window();
    void set_window_size(int width, int height);
    bool should_close() const;
    void swap_buffers() const;
    void poll_events() const;
    vec2<int> get_size() const;
    GLFWwindow* get_window() const;
    private:
        GLFWwindow* m_window;
        vec2<int> m_size;
        std::string m_title;
        window_flags m_flags;
};

extern window_manager gWindowManager;

NUVIO_NAMESPACE_END
