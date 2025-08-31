#pragma once
#include "core/nuvio_namespaces.h"
#include "core/ui/components/comp.h"
#include <vector>

NUVIO_NAMESPACE_BEGIN

class UIManager {
    public:
        /**
         * Initialize the UI Manager
         */
        void init();
        /**
         * Render UI components that are registered
         */
        void render() const;
        /**
         * Begins a new ImGui frame
         */
        void begin_frame();
        /**
         * Ends the current ImGui frame
         */
        void end_frame();
        /**
         * Register a new UI component
         */
        void RegisterComponent(const nuvio::ui::component comp);
        /**
         * Unregister an existing UI component
         */
        void UnregisterComponent(const nuvio::ui::component comp);

        void Shutdown();
    private:
        // List of registered UI components
        std::vector<nuvio::ui::component> mComponents;
        int m_width, m_height;
        float m_dpi_scale;
        float m_ui_scaler_factor;
};

extern UIManager gUIManager;

NUVIO_NAMESPACE_END
