#include "core/ui/components/registery.h"
#include<vector>
#include "core/ui/ui.h"
#include "core/nuvio_namespaces.h"

//components includes start
#include "core/ui/editor/navbar.h"
#include "core/ui/editor/sidebar.h"
#include "core/ui/editor/layers.h"
#include "core/ui/editor/viewport.h"
//components includes end

NUVIO_UI_NAMESPACE_BEGIN

// Register root UI components here
std::vector<component> allComps = {
    *ui::get_navbar_component(),
    *ui::get_sidebar_component(),
    *ui::get_layers_component(),
    *ui::get_viewport_component()
};

void RegisterAllComponents() {
    for (auto& comp : allComps) {
        nuvio::gUIManager.RegisterComponent(&comp);
    }
}

NUVIO_UI_NAMESPACE_END