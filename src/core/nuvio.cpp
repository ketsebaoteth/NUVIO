#include "core/nuvio.hpp"
#include "core/canvas/components/rectangle.h"
#include "core/canvas/irenderable.h"
#include "core/dna/project.h"
#include "core/dna/project_manager.h"
#include "core/canvas/manager.h"
#include "core/undo/manager.h"
#include "core/window/window_manager.h"
#include "core/ui/ui.h"
#include "core/ui/theme/theme.h"
#include "core/shortcut/manager.h"
//profiling
#include "Tracy.hpp"
#include <memory>

NUVIO_NAMESPACE_BEGIN

NuvioApp::NuvioApp(int argc, char** argv) {
    // handle project loading later:
    char* project_path = argv[0];
    //nuvio::gProjectManager.loadProject(std::string(project_path));
    nuvio::gWindowManager.set_window_size(1280, 720);
    nuvio::gWindowManager.create_window("Nuvio", WINDOW_FLAG_RESIZABLE | WINDOW_FLAG_MAXIMIZED);
    //initalizaers
    nuvio::gUIManager.init();
    nuvio::gCanvasManager.Init(1000,600);
    nuvio::gCanvasManager.SetCanvasBackgroundColor({1.0f,1.0f,1.0f,1.0f});
    nuvio::canvas::Rectangle* testrect = new canvas::Rectangle({0.0f,0.0f},{1.0f,1.0f});
    std::vector<nuvio::canvas::Irenderable*> l1;
    nuvio::gCanvasManager.AppendLayer(l1);
    auto action = std::make_unique<canvas::AddRenderableAction>(testrect,0);
    action->execute();
    gUndoManager.add_action(std::move(action));
    //set default theme for now
    nuvio::ui::gThemeManager.ApplyTheme("Default");

    // for now
    UNUSED(project_path);
    UNUSED(argc);
}

void NuvioApp::run() {
    while(!nuvio::gWindowManager.should_close()){
	ZoneScopedN("main_render");
        nuvio::gUIManager.begin_frame();
        nuvio::gUIManager.render();
        nuvio::gUIManager.end_frame();
        nuvio::gWindowManager.swap_buffers();
        nuvio::gWindowManager.poll_events();
        nuvio::gShortcutManager.process();
	FrameMark;
    }
    nuvio::gWindowManager.destroy_window();
}

NUVIO_NAMESPACE_END
