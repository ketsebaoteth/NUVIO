#include "core/ui/components/registery.h"
#include<vector>
#include "core/ui/ui.h"
#include "core/nuvio_namespaces.h"

//components includes start
#include "core/ui/test.h"
//components includes end

NUVIO_UI_NAMESPACE_BEGIN

// List of all UI components
// add new components here for them to get added to
std::vector<nuvio::ui::component> allComps = {
    ui::get_test_component()
};

void RegisterAllComponents() {
    for (auto comp : allComps) {
        nuvio::gUIManager.RegisterComponent(comp);
    }
}

NUVIO_UI_NAMESPACE_END