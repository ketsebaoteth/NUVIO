#include "core/nuvio.hpp"
#include "core/dna/project.h"
#include "core/dna/project_manager.h"
#include "core/window/window_manager.h"
#include "core/ui/ui.h"
#include "core/ui/theme/theme.h"
#include "core/shortcut/manager.h"

NUVIO_NAMESPACE_BEGIN

NuvioApp::NuvioApp(int argc, char** argv) {
    // handle project loading later:
    char* project_path = argv[0];
    //nuvio::gProjectManager.loadProject(std::string(project_path));
    nuvio::gWindowManager.set_window_size(1280, 720);
    nuvio::gWindowManager.create_window("Nuvio", WINDOW_FLAG_RESIZABLE | WINDOW_FLAG_MAXIMIZED);
    nuvio::gUIManager.init();
    //set default theme for now
    nuvio::ui::gThemeManager.ApplyTheme("Default");
    // for now
    UNUSED(project_path);
    UNUSED(argc);
}

void NuvioApp::run() {
    while(!nuvio::gWindowManager.should_close()){
        nuvio::gUIManager.begin_frame();
        nuvio::gUIManager.render();
        nuvio::gUIManager.end_frame();
        nuvio::gWindowManager.swap_buffers();
        nuvio::gWindowManager.poll_events();
        nuvio::gShortcutManager.update();
    }
    nuvio::gWindowManager.destroy_window();
}

NUVIO_NAMESPACE_END