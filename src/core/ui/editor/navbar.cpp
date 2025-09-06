#include "core/ui/editor/navbar.h"
#include "core/nuvio_namespaces.h"
#include "core/ui/components/menu_item.h"
#include "core/ui/components/registery.h"
#include "imgui.h"

NUVIO_UI_NAMESPACE_BEGIN

// "Open from Other source" submenu
menu_item open_from_url_sub_menu = {
    "Open from URL", "", "Open from URL", "Open file from a web link", "url_icon.png",
    {}, []() { /* Open from URL logic */ }, []() { /* Show tooltip */ }
};
menu_item open_from_clipboard_sub_menu = {
    "Open from clipboard", "", "Open from clipboard", "Open file from clipboard data", "clipboard_icon.png",
    {}, []() { /* Open from clipboard logic */ }, []() { /* Show tooltip */ }
};
menu_item open_from_other_source_menu = {
    "Open from Other source", "", "Open from Other source", "Open file from another source", "othersrc_icon.png",
    {open_from_url_sub_menu, open_from_clipboard_sub_menu},
    []() {}, []() {}
};

// "Export As" submenu
menu_item export_as_png = {
    "PNG", "", "Export as PNG", "Export image as PNG", "png_icon.png",
    {}, []() { /* Export as PNG logic */ }, []() { /* Show tooltip */ }
};
menu_item export_as_jpeg = {
    "JPEG", "", "Export as JPEG", "Export image as JPEG", "jpeg_icon.png",
    {}, []() { /* Export as JPEG logic */ }, []() { /* Show tooltip */ }
};
menu_item export_as_bmp = {
    "BMP", "", "Export as BMP", "Export image as BMP", "bmp_icon.png",
    {}, []() { /* Export as BMP logic */ }, []() { /* Show tooltip */ }
};
menu_item export_as_menu = {
    "Export As", "", "Export As", "Export image as another format", "exportas_icon.png",
    {export_as_png, export_as_jpeg, export_as_bmp},
    []() {}, []() {}
};

// Main File Menu Items
menu_item new_file_menu = {
    "New", "⌘CTRL+N", "New File", "Create a new file", "new_icon.png",
    {}, []() { /* New file logic */ }, []() { /* Show tooltip */ }
};
menu_item open_file_menu = {
    "Open", "⌘CTRL+O", "Open File", "Open an existing file", "open_icon.png",
    {}, []() { /* Open file logic */ }, []() { /* Show tooltip */ }
};
menu_item open_from_dropbox_menu = {
    "Open from dropbox", "", "Open from Dropbox", "Open file from Dropbox", "dropbox_icon.png",
    {}, []() { /* Open from Dropbox logic */ }, []() { /* Show tooltip */ }
};
menu_item open_from_drive_menu = {
    "Open from drive", "", "Open from Drive", "Open file from Google Drive", "drive_icon.png",
    {}, []() { /* Open from Drive logic */ }, []() { /* Show tooltip */ }
};
menu_item save_file_menu = {
    "Save", "⌘CTRL+S", "Save File", "Save the current file", "save_icon.png",
    {}, []() { /* Save file logic */ }, []() { /* Show tooltip */ }
};
menu_item save_as_menu = {
    "Save As", "⌘CTRL+SHIFT+N", "Save As", "Save the file under a new name", "saveas_icon.png",
    {}, []() { /* Save As logic */ }, []() { /* Show tooltip */ }
};
menu_item save_as_psd_menu = {
    "Save As PSD", "", "Save As PSD", "Save the file as a PSD document", "psd_icon.png",
    {}, []() { /* Save as PSD logic */ }, []() { /* Show tooltip */ }
};
menu_item export_quick_menu = {
    "Export Quick", "⌘CTRL+E", "Export Quick", "Quick export with last used settings", "exportquick_icon.png",
    {}, []() { /* Export Quick logic */ }, []() { /* Show tooltip */ }
};
menu_item print_menu = {
    "Print", "⌘CTRL+P", "Print", "Print the current document", "print_icon.png",
    {}, []() { /* Print logic */ }, []() { /* Show tooltip */ }
};
menu_item close_menu = {
    "Close", "⌘CTRL+Q", "Close", "Close the current file", "close_icon.png",
    {}, []() { /* Close logic */ }, []() { /* Show tooltip */ }
};

// The File menu with all submenus and items
menu_item file_menu = {
    "File", "", "File Menu", "File operations", "file_icon.png",
    {
        new_file_menu,
        open_file_menu,
        open_from_dropbox_menu,
        open_from_drive_menu,
        open_from_other_source_menu,
        save_file_menu,
        save_as_menu,
        save_as_psd_menu,
        export_quick_menu,
        export_as_menu,
        print_menu,
        close_menu
    },
    []() {}, []() {}
};

// Free Transform submenu
menu_item free_transform_repeat = {
    "Repeat", "", "Repeat", "Repeat last transform", "repeat_icon.png",
    {}, []() { /* Repeat transform logic */ }, []() { /* Show tooltip */ }
};
menu_item free_transform_scale = {
    "Scale", "", "Scale", "Scale the selection", "scale_icon.png",
    {}, []() { /* Scale logic */ }, []() { /* Show tooltip */ }
};
menu_item free_transform_rotate = {
    "Rotate", "", "Rotate", "Rotate the selection", "rotate_icon.png",
    {}, []() { /* Rotate logic */ }, []() { /* Show tooltip */ }
};
menu_item free_transform_skew = {
    "Skew", "", "Skew", "Skew the selection", "skew_icon.png",
    {}, []() { /* Skew logic */ }, []() { /* Show tooltip */ }
};
menu_item free_transform_distort = {
    "Distort", "", "Distort", "Distort the selection", "distort_icon.png",
    {}, []() { /* Distort logic */ }, []() { /* Show tooltip */ }
};
menu_item free_transform_perspective = {
    "Perspective", "", "Perspective", "Apply perspective transform", "perspective_icon.png",
    {}, []() { /* Perspective logic */ }, []() { /* Show tooltip */ }
};
menu_item free_transform_rotate_90_left = {
    "Rotate 90 Left", "", "Rotate 90 Left", "Rotate the selection 90 degrees left", "rotateleft_icon.png",
    {}, []() { /* Rotate 90 left logic */ }, []() { /* Show tooltip */ }
};
menu_item free_transform_rotate_90_right = {
    "Rotate 90 Right", "", "Rotate 90 Right", "Rotate the selection 90 degrees right", "rotateright_icon.png",
    {}, []() { /* Rotate 90 right logic */ }, []() { /* Show tooltip */ }
};
menu_item free_transform_menu = {
    "Free Transform", "", "Free Transform", "Advanced transforms", "freetransform_icon.png",
    {
        free_transform_repeat,
        free_transform_scale,
        free_transform_rotate,
        free_transform_skew,
        free_transform_distort,
        free_transform_perspective,
        free_transform_rotate_90_left,
        free_transform_rotate_90_right
    },
    []() {}, []() {}
};

// Main Edit Menu Items
menu_item undo_menu = {
    "Undo", "⌘CTRL+Z", "Undo", "Undo last action", "undo_icon.png",
    {}, []() { /* Undo logic */ }, []() { /* Show tooltip */ }
};
menu_item redo_menu = {
    "Redo", "⌘CTRL+SHIFT+Z", "Redo", "Redo last undone action", "redo_icon.png",
    {}, []() { /* Redo logic */ }, []() { /* Show tooltip */ }
};
menu_item bring_to_front_menu = {
    "Bring To Front", "⌘]", "Bring To Front", "Bring the selection to the front", "front_icon.png",
    {}, []() { /* Bring to front logic */ }, []() { /* Show tooltip */ }
};
menu_item send_to_back_menu = {
    "Send To Back", "⌘[", "Send To Back", "Send the selection to the back", "back_icon.png",
    {}, []() { /* Send to back logic */ }, []() { /* Show tooltip */ }
};
menu_item cut_menu = {
    "Cut", "⌘CTRL+X", "Cut", "Cut selection", "cut_icon.png",
    {}, []() { /* Cut logic */ }, []() { /* Show tooltip */ }
};
menu_item copy_menu = {
    "Copy", "⌘CTRL+C", "Copy", "Copy selection", "copy_icon.png",
    {}, []() { /* Copy logic */ }, []() { /* Show tooltip */ }
};
menu_item paste_menu = {
    "Paste", "⌘CTRL+V", "Paste", "Paste clipboard", "paste_icon.png",
    {}, []() { /* Paste logic */ }, []() { /* Show tooltip */ }
};
menu_item paste_new_layer_menu = {
    "Paste New Layer", "⌘CTRL+ALT+V", "Paste New Layer", "Paste clipboard as new layer", "pastelayer_icon.png",
    {}, []() { /* Paste new layer logic */ }, []() { /* Show tooltip */ }
};
menu_item clear_menu = {
    "clear", "", "Clear", "Clear selection", "clear_icon.png",
    {}, []() { /* Clear logic */ }, []() { /* Show tooltip */ }
};
menu_item clear_canvas_menu = {
    "Clear Canvas", "⌘CTRL+ALT+X", "Clear Canvas", "Clear the entire canvas", "clearcanvas_icon.png",
    {}, []() { /* Clear canvas logic */ }, []() { /* Show tooltip */ }
};
menu_item fill_menu = {
    "Fill", "", "Fill", "Fill selection with color", "fill_icon.png",
    {}, []() { /* Fill logic */ }, []() { /* Show tooltip */ }
};
menu_item stroke_menu = {
    "Stroke", "", "Stroke", "Stroke around selection", "stroke_icon.png",
    {}, []() { /* Stroke logic */ }, []() { /* Show tooltip */ }
};
menu_item content_aware_scale_menu = {
    "Content Aware Scale", "", "Content Aware Scale", "Scale content intelligently", "contentaware_icon.png",
    {}, []() { /* Content aware scale logic */ }, []() { /* Show tooltip */ }
};
menu_item puppet_wrap_menu = {
    "Puppet Wrap", "", "Puppet Wrap", "Warp image with puppet controls", "puppetwrap_icon.png",
    {}, []() { /* Puppet wrap logic */ }, []() { /* Show tooltip */ }
};
menu_item transform_menu = {
    "Transform", "", "Transform", "General transform operations", "transform_icon.png",
    {}, []() { /* Transform logic */ }, []() { /* Show tooltip */ }
};
menu_item wrap_menu = {
    "wrap", "", "Wrap", "Wrap selection", "wrap_icon.png",
    {}, []() { /* Wrap logic */ }, []() { /* Show tooltip */ }
};

// The Edit menu with all submenus and items
menu_item edit_menu = {
    "Edit", "", "Edit Menu", "Edit operations", "edit_icon.png",
    {
        undo_menu,
        redo_menu,
        bring_to_front_menu,
        send_to_back_menu,
        cut_menu,
        copy_menu,
        paste_menu,
        paste_new_layer_menu,
        clear_menu,
        clear_canvas_menu,
        fill_menu,
        stroke_menu,
        content_aware_scale_menu,
        puppet_wrap_menu,
        transform_menu,
        free_transform_menu,
        wrap_menu
    },
    []() {}, []() {}
};
// View Menu Subitems
menu_item zoom_in_sub_menu = {
    "Zoom In", "⌘+", "Zoom In", "Zoom in the canvas", "zoomin_icon.png",
    {}, []() { /* Zoom In logic */ }, []() { /* Show tooltip */ }
};
menu_item zoom_out_sub_menu = {
    "Zoom Out", "⌘-", "Zoom Out", "Zoom out the canvas", "zoomout_icon.png",
    {}, []() { /* Zoom Out logic */ }, []() { /* Show tooltip */ }
};
menu_item reset_zoom_sub_menu = {
    "Reset Zoom", "⌘0", "Reset Zoom", "Reset zoom to default", "resetzoom_icon.png",
    {}, []() { /* Reset Zoom logic */ }, []() { /* Show tooltip */ }
};
menu_item fullscreen_sub_menu = {
    "Fullscreen", "F11", "Fullscreen", "Toggle fullscreen mode", "fullscreen_icon.png",
    {}, []() { /* Fullscreen logic */ }, []() { /* Show tooltip */ }
};

menu_item view_menu = {
    "View", "", "View Menu", "View settings", "view_icon.png",
    {zoom_in_sub_menu, zoom_out_sub_menu, reset_zoom_sub_menu, fullscreen_sub_menu},
    []() {}, []() {}
};

// Layer Menu Subitems
menu_item new_layer_sub_menu = {
    "New Layer", "⇧⌘N", "New Layer", "Create a new layer", "newlayer_icon.png",
    {}, []() { /* New Layer logic */ }, []() { /* Show tooltip */ }
};
menu_item duplicate_layer_sub_menu = {
    "Duplicate Layer", "⌘D", "Duplicate Layer", "Duplicate current layer", "duplayer_icon.png",
    {}, []() { /* Duplicate Layer logic */ }, []() { /* Show tooltip */ }
};
menu_item merge_down_sub_menu = {
    "Merge Down", "⌘E", "Merge Down", "Merge with layer below", "merge_icon.png",
    {}, []() { /* Merge Down logic */ }, []() { /* Show tooltip */ }
};
menu_item delete_layer_sub_menu = {
    "Delete Layer", "⌫", "Delete Layer", "Delete current layer", "dellayer_icon.png",
    {}, []() { /* Delete Layer logic */ }, []() { /* Show tooltip */ }
};

menu_item layer_menu = {
    "Layer", "", "Layer Menu", "Layer operations", "layer_icon.png",
    {new_layer_sub_menu, duplicate_layer_sub_menu, merge_down_sub_menu, delete_layer_sub_menu},
    []() {}, []() {}
};

// Help Menu Subitems
menu_item about_sub_menu = {
    "About", "", "About", "About this application", "about_icon.png",
    {}, []() { /* About logic */ }, []() { /* Show tooltip */ }
};
menu_item documentation_sub_menu = {
    "Documentation", "F1", "Documentation", "Open documentation", "docs_icon.png",
    {}, []() { /* Documentation logic */ }, []() { /* Show tooltip */ }
};
menu_item report_issue_sub_menu = {
    "Report Issue", "", "Report Issue", "Report a bug or issue", "bug_icon.png",
    {}, []() { /* Issue reporting logic */ }, []() { /* Show tooltip */ }
};

menu_item help_menu = {
    "Help", "", "Help Menu", "Get help", "help_icon.png",
    {about_sub_menu, documentation_sub_menu, report_issue_sub_menu},
    []() {}, []() {}
};

// Top-level Navbar
menu_item gNavbar = {
    "", "", "Navbar", "The main navigation bar", "",
    {file_menu, edit_menu, view_menu, layer_menu, help_menu},
    []() {}, []() {}
};

void draw_subitems(const menu_item& item) {
    if (ImGui::BeginMenu(item.title.c_str())) {
        for (const auto &subitem : item.children) {
            if (!subitem.children.empty()) {
                draw_subitems(subitem);
            } else {
                if (ImGui::MenuItem(subitem.title.c_str(), subitem.shortcut.c_str())) {
                    if (subitem.on_click) subitem.on_click();
                }
            }
            if (ImGui::IsItemHovered() && subitem.on_hover) {
                subitem.on_hover();
                if (!subitem.tooltip_title.empty() || !subitem.tooltip_desc.empty()) {
                    ImGui::SetTooltip("%s\n%s", subitem.tooltip_title.c_str(), subitem.tooltip_desc.c_str());
                }
            }
        }
        ImGui::EndMenu();
    }
}

void render_navbar() {
    if (ImGui::BeginMainMenuBar()) {
        for (const auto &item : gNavbar.children) {
            if (!item.children.empty()) {
                draw_subitems(item);
            } else {
                if (ImGui::MenuItem(item.title.c_str(), item.shortcut.c_str())) {
                    if (item.on_click) item.on_click();
                }
            }
            if (ImGui::IsItemHovered() && item.on_hover) {
                item.on_hover();
                if (!item.tooltip_title.empty() || !item.tooltip_desc.empty()) {
                    ImGui::SetTooltip("%s\n%s", item.tooltip_title.c_str(), item.tooltip_desc.c_str());
                }
            }
        }
        ImGui::EndMainMenuBar();
    }
}

component get_navbar_component() {
    return component{"NavbarComponent", []() { render_navbar(); }};
}

NUVIO_UI_NAMESPACE_END
