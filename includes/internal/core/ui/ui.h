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
        void RegisterComponent(nuvio::ui::component* comp);
        /**
         * Unregister an existing UI component
         */
        void UnregisterComponent(nuvio::ui::component* comp);
        /**
         * writes imgui config for docking positions if none exists
         */
        void WriteLayoutConfig();

        void Shutdown();
    private:
        // List of registered UI components
        std::vector<nuvio::ui::component*> mComponents;
        int m_width, m_height;
        float m_dpi_scale;
        float m_ui_scaler_factor;
        std::string m_ini_path = "nuvio_ui.ini";
};

extern UIManager gUIManager;

NUVIO_NAMESPACE_END
