#include "core/ui/editor/navbar.h"
#include "core/canvas/manager.h"
#include "core/nuvio_namespaces.h"
#include "core/ui/components/menu_item.h"
#include "core/ui/components/registery.h"
#include "imgui.h"
#include <cstdio>



NUVIO_UI_NAMESPACE_BEGIN

// "Open from Other source" submenu
menu_item open_from_url_sub_menu = {
    .title = "Open from URL",
    .shortcut = "",
    .tooltip_title = "Open from URL",
    .tooltip_desc = "Open file from a web link",
    .sd = separator_direction::NONE,
    .icon = "url_icon.png",
    .children = {},
    .on_click = []() { /* Open from URL logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item open_from_clipboard_sub_menu = {
    .title = "Open from clipboard",
    .shortcut = "",
    .tooltip_title = "Open from clipboard",
    .tooltip_desc = "Open file from clipboard data",
    .sd = separator_direction::NONE,
    .icon = "clipboard_icon.png",
    .children = {},
    .on_click = []() { /* Open from clipboard logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item open_from_other_source_menu = {
    .title = "Open from Other source",
    .shortcut = "",
    .tooltip_title = "Open from Other source",
    .tooltip_desc = "Open file from another source",
    .sd = separator_direction::NONE,
    .icon = "othersrc_icon.png",
    .children = {open_from_url_sub_menu, open_from_clipboard_sub_menu},
    .on_click = []() {},
    .on_hover = []() {}
};

// "Export As" submenu
menu_item export_as_png = {
    .title = "PNG",
    .shortcut = "",
    .tooltip_title = "Export as PNG",
    .tooltip_desc = "Export image as PNG",
    .sd = separator_direction::NONE,
    .icon = "png_icon.png",
    .children = {},
    .on_click = []() { 
      std::string path = "output.png";
      gCanvasManager.WriteImage(path);
    },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item export_as_jpeg = {
    .title = "JPEG",
    .shortcut = "",
    .tooltip_title = "Export as JPEG",
    .tooltip_desc = "Export image as JPEG",
    .sd = separator_direction::NONE,
    .icon = "jpeg_icon.png",
    .children = {},
    .on_click = []() { /* Export as JPEG logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item export_as_bmp = {
    .title = "BMP",
    .shortcut = "",
    .tooltip_title = "Export as BMP",
    .tooltip_desc = "Export image as BMP",
    .sd = separator_direction::NONE,
    .icon = "bmp_icon.png",
    .children = {},
    .on_click = []() { /* Export as BMP logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item export_as_menu = {
    .title = "Export As",
    .shortcut = "",
    .tooltip_title = "Export As",
    .tooltip_desc = "Export image as another format",
    .sd = separator_direction::NONE,
    .icon = "exportas_icon.png",
    .children = {export_as_png, export_as_jpeg, export_as_bmp},
    .on_click = []() {},
    .on_hover = []() {}
};

// Main File Menu Items
menu_item new_file_menu = {
    .title = "New",
    .shortcut = "⌘CTRL+N",
    .tooltip_title = "New File",
    .tooltip_desc = "Create a new file",
    .sd = separator_direction::NONE,
    .icon = "new_icon.png",
    .children = {},
    .on_click = []() { /* New file logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item open_file_menu = {
    .title = "Open",
    .shortcut = "⌘CTRL+O",
    .tooltip_title = "Open File",
    .tooltip_desc = "Open an existing file",
    .sd = separator_direction::UP,
    .icon = "open_icon.png",
    .children = {},
    .on_click = []() { /* Open file logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item open_from_dropbox_menu = {
    .title = "Open from dropbox",
    .shortcut = "",
    .tooltip_title = "Open from Dropbox",
    .tooltip_desc = "Open file from Dropbox",
    .sd = separator_direction::NONE,
    .icon = "dropbox_icon.png",
    .children = {},
    .on_click = []() { /* Open from Dropbox logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item open_from_drive_menu = {
    .title = "Open from drive",
    .shortcut = "",
    .tooltip_title = "Open from Drive",
    .tooltip_desc = "Open file from Google Drive",
    .sd = separator_direction::NONE,
    .icon = "drive_icon.png",
    .children = {},
    .on_click = []() { /* Open from Drive logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item save_file_menu = {
    .title = "Save",
    .shortcut = "⌘CTRL+S",
    .tooltip_title = "Save File",
    .tooltip_desc = "Save the current file",
    .sd = separator_direction::UP,
    .icon = "save_icon.png",
    .children = {},
    .on_click = []() { /* Save file logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item save_as_menu = {
    .title = "Save As",
    .shortcut = "⌘CTRL+SHIFT+N",
    .tooltip_title = "Save As",
    .tooltip_desc = "Save the file under a new name",
    .sd = separator_direction::NONE,
    .icon = "saveas_icon.png",
    .children = {},
    .on_click = []() { /* Save As logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item save_as_psd_menu = {
    .title = "Save As PSD",
    .shortcut = "",
    .tooltip_title = "Save As PSD",
    .tooltip_desc = "Save the file as a PSD document",
    .sd = separator_direction::NONE,
    .icon = "psd_icon.png",
    .children = {},
    .on_click = []() { /* Save as PSD logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item export_quick_menu = {
    .title = "Export Quick",
    .shortcut = "⌘CTRL+E",
    .tooltip_title = "Export Quick",
    .tooltip_desc = "Quick export with last used settings",
    .sd = separator_direction::UP,
    .icon = "exportquick_icon.png",
    .children = {},
    .on_click = []() { /* Export Quick logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item print_menu = {
    .title = "Print",
    .shortcut = "⌘CTRL+P",
    .tooltip_title = "Print",
    .tooltip_desc = "Print the current document",
    .sd = separator_direction::UP,
    .icon = "print_icon.png",
    .children = {},
    .on_click = []() { /* Print logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item close_menu = {
    .title = "Close",
    .shortcut = "⌘CTRL+Q",
    .tooltip_title = "Close",
    .tooltip_desc = "Close the current file",
    .sd = separator_direction::NONE,
    .icon = "close_icon.png",
    .children = {},
    .on_click = []() { /* Close logic */ },
    .on_hover = []() { /* Show tooltip */ }
};

// The File menu with all submenus and items
menu_item file_menu = {
    .title = "File",
    .shortcut = "",
    .tooltip_title = "File Menu",
    .tooltip_desc = "File operations",
    .sd = separator_direction::NONE,
    .icon = "file_icon.png",
    .children = {
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
    .on_click = []() {},
    .on_hover = []() {}
};

// Free Transform submenu
menu_item free_transform_repeat = {
    .title = "Repeat",
    .shortcut = "",
    .tooltip_title = "Repeat",
    .tooltip_desc = "Repeat last transform",
    .sd = separator_direction::NONE,
    .icon = "repeat_icon.png",
    .children = {},
    .on_click = []() { /* Repeat transform logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item free_transform_scale = {
    .title = "Scale",
    .shortcut = "",
    .tooltip_title = "Scale",
    .tooltip_desc = "Scale the selection",
    .sd = separator_direction::NONE,
    .icon = "scale_icon.png",
    .children = {},
    .on_click = []() { /* Scale logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item free_transform_rotate = {
    .title = "Rotate",
    .shortcut = "",
    .tooltip_title = "Rotate",
    .tooltip_desc = "Rotate the selection",
    .sd = separator_direction::NONE,
    .icon = "rotate_icon.png",
    .children = {},
    .on_click = []() { /* Rotate logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item free_transform_skew = {
    .title = "Skew",
    .shortcut = "",
    .tooltip_title = "Skew",
    .tooltip_desc = "Skew the selection",
    .sd = separator_direction::NONE,
    .icon = "skew_icon.png",
    .children = {},
    .on_click = []() { /* Skew logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item free_transform_distort = {
    .title = "Distort",
    .shortcut = "",
    .tooltip_title = "Distort",
    .tooltip_desc = "Distort the selection",
    .sd = separator_direction::NONE,
    .icon = "distort_icon.png",
    .children = {},
    .on_click = []() { /* Distort logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item free_transform_perspective = {
    .title = "Perspective",
    .shortcut = "",
    .tooltip_title = "Perspective",
    .tooltip_desc = "Apply perspective transform",
    .sd = separator_direction::NONE,
    .icon = "perspective_icon.png",
    .children = {},
    .on_click = []() { /* Perspective logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item free_transform_rotate_90_left = {
    .title = "Rotate 90 Left",
    .shortcut = "",
    .tooltip_title = "Rotate 90 Left",
    .tooltip_desc = "Rotate the selection 90 degrees left",
    .sd = separator_direction::NONE,
    .icon = "rotateleft_icon.png",
    .children = {},
    .on_click = []() { /* Rotate 90 left logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item free_transform_rotate_90_right = {
    .title = "Rotate 90 Right",
    .shortcut = "",
    .tooltip_title = "Rotate 90 Right",
    .tooltip_desc = "Rotate the selection 90 degrees right",
    .sd = separator_direction::NONE,
    .icon = "rotateright_icon.png",
    .children = {},
    .on_click = []() { /* Rotate 90 right logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item free_transform_menu = {
    .title = "Free Transform",
    .shortcut = "",
    .tooltip_title = "Free Transform",
    .tooltip_desc = "Advanced transforms",
    .sd = separator_direction::NONE,
    .icon = "freetransform_icon.png",
    .children = {
        free_transform_repeat,
        free_transform_scale,
        free_transform_rotate,
        free_transform_skew,
        free_transform_distort,
        free_transform_perspective,
        free_transform_rotate_90_left,
        free_transform_rotate_90_right
    },
    .on_click = []() {},
    .on_hover = []() {}
};

// Main Edit Menu Items
menu_item undo_menu = {
    .title = "Undo",
    .shortcut = "⌘CTRL+Z",
    .tooltip_title = "Undo",
    .tooltip_desc = "Undo last action",
    .sd = separator_direction::NONE,
    .icon = "undo_icon.png",
    .children = {},
    .on_click = []() { /* Undo logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item redo_menu = {
    .title = "Redo",
    .shortcut = "⌘CTRL+SHIFT+Z",
    .tooltip_title = "Redo",
    .tooltip_desc = "Redo last undone action",
    .sd = separator_direction::DOWN,
    .icon = "redo_icon.png",
    .children = {},
    .on_click = []() { /* Redo logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item bring_to_front_menu = {
    .title = "Bring To Front",
    .shortcut = "⌘]",
    .tooltip_title = "Bring To Front",
    .tooltip_desc = "Bring the selection to the front",
    .sd = separator_direction::NONE,
    .icon = "front_icon.png",
    .children = {},
    .on_click = []() { /* Bring to front logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item send_to_back_menu = {
    .title = "Send To Back",
    .shortcut = "⌘[",
    .tooltip_title = "Send To Back",
    .tooltip_desc = "Send the selection to the back",
    .sd = separator_direction::DOWN,
    .icon = "back_icon.png",
    .children = {},
    .on_click = []() { /* Send to back logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item cut_menu = {
    .title = "Cut",
    .shortcut = "⌘CTRL+X",
    .tooltip_title = "Cut",
    .tooltip_desc = "Cut selection",
    .sd = separator_direction::NONE,
    .icon = "cut_icon.png",
    .children = {},
    .on_click = []() { /* Cut logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item copy_menu = {
    .title = "Copy",
    .shortcut = "⌘CTRL+C",
    .tooltip_title = "Copy",
    .tooltip_desc = "Copy selection",
    .sd = separator_direction::NONE,
    .icon = "copy_icon.png",
    .children = {},
    .on_click = []() { /* Copy logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item paste_menu = {
    .title = "Paste",
    .shortcut = "⌘CTRL+V",
    .tooltip_title = "Paste",
    .tooltip_desc = "Paste clipboard",
    .sd = separator_direction::NONE,
    .icon = "paste_icon.png",
    .children = {},
    .on_click = []() { /* Paste logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item paste_new_layer_menu = {
    .title = "Paste New Layer",
    .shortcut = "⌘CTRL+ALT+V",
    .tooltip_title = "Paste New Layer",
    .tooltip_desc = "Paste clipboard as new layer",
    .sd = separator_direction::DOWN,
    .icon = "pastelayer_icon.png",
    .children = {},
    .on_click = []() { /* Paste new layer logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item clear_menu = {
    .title = "clear",
    .shortcut = "",
    .tooltip_title = "Clear",
    .tooltip_desc = "Clear selection",
    .sd = separator_direction::NONE,
    .icon = "clear_icon.png",
    .children = {},
    .on_click = []() { /* Clear logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item clear_canvas_menu = {
    .title = "Clear Canvas",
    .shortcut = "⌘CTRL+ALT+X",
    .tooltip_title = "Clear Canvas",
    .tooltip_desc = "Clear the entire canvas",
    .sd = separator_direction::NONE,
    .icon = "clearcanvas_icon.png",
    .children = {},
    .on_click = []() { /* Clear canvas logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item fill_menu = {
    .title = "Fill",
    .shortcut = "",
    .tooltip_title = "Fill",
    .tooltip_desc = "Fill selection with color",
    .sd = separator_direction::UP,
    .icon = "fill_icon.png",
    .children = {},
    .on_click = []() { /* Fill logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item stroke_menu = {
    .title = "Stroke",
    .shortcut = "",
    .tooltip_title = "Stroke",
    .tooltip_desc = "Stroke around selection",
    .sd = separator_direction::NONE,
    .icon = "stroke_icon.png",
    .children = {},
    .on_click = []() { /* Stroke logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item content_aware_scale_menu = {
    .title = "Content Aware Scale",
    .shortcut = "",
    .tooltip_title = "Content Aware Scale",
    .tooltip_desc = "Scale content intelligently",
    .sd = separator_direction::UP,
    .icon = "contentaware_icon.png",
    .children = {},
    .on_click = []() { /* Content aware scale logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item puppet_wrap_menu = {
    .title = "Puppet Wrap",
    .shortcut = "",
    .tooltip_title = "Puppet Wrap",
    .tooltip_desc = "Warp image with puppet controls",
    .sd = separator_direction::NONE,
    .icon = "puppetwrap_icon.png",
    .children = {},
    .on_click = []() { /* Puppet wrap logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item transform_menu = {
    .title = "Transform",
    .shortcut = "",
    .tooltip_title = "Transform",
    .tooltip_desc = "General transform operations",
    .sd = separator_direction::NONE,
    .icon = "transform_icon.png",
    .children = {},
    .on_click = []() { /* Transform logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item wrap_menu = {
    .title = "wrap",
    .shortcut = "",
    .tooltip_title = "Wrap",
    .tooltip_desc = "Wrap selection",
    .sd = separator_direction::NONE,
    .icon = "wrap_icon.png",
    .children = {},
    .on_click = []() { /* Wrap logic */ },
    .on_hover = []() { /* Show tooltip */ }
};

// The Edit menu with all submenus and items
menu_item edit_menu = {
    .title = "Edit",
    .shortcut = "",
    .tooltip_title = "Edit Menu",
    .tooltip_desc = "Edit operations",
    .sd = separator_direction::NONE,
    .icon = "edit_icon.png",
    .children = {
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
    .on_click = []() {},
    .on_hover = []() {}
};
// View Menu Subitems
menu_item zoom_in_sub_menu = {
    .title = "Zoom In",
    .shortcut = "⌘+",
    .tooltip_title = "Zoom In",
    .tooltip_desc = "Zoom in the canvas",
    .sd = separator_direction::NONE,
    .icon = "zoomin_icon.png",
    .children = {},
    .on_click = []() { /* Zoom In logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item zoom_out_sub_menu = {
    .title = "Zoom Out",
    .shortcut = "⌘-",
    .tooltip_title = "Zoom Out",
    .tooltip_desc = "Zoom out the canvas",
    .sd = separator_direction::NONE,
    .icon = "zoomout_icon.png",
    .children = {},
    .on_click = []() { /* Zoom Out logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item reset_zoom_sub_menu = {
    .title = "Reset Zoom",
    .shortcut = "⌘0",
    .tooltip_title = "Reset Zoom",
    .tooltip_desc = "Reset zoom to default",
    .sd = separator_direction::NONE,
    .icon = "resetzoom_icon.png",
    .children = {},
    .on_click = []() { /* Reset Zoom logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item fullscreen_sub_menu = {
    .title = "Fullscreen",
    .shortcut = "F11",
    .tooltip_title = "Fullscreen",
    .tooltip_desc = "Toggle fullscreen mode",
    .sd = separator_direction::NONE,
    .icon = "fullscreen_icon.png",
    .children = {},
    .on_click = []() { /* Fullscreen logic */ },
    .on_hover = []() { /* Show tooltip */ }
};

menu_item view_menu = {
    .title = "View",
    .shortcut = "",
    .tooltip_title = "View Menu",
    .tooltip_desc = "View settings",
    .sd = separator_direction::NONE,
    .icon = "view_icon.png",
    .children = {zoom_in_sub_menu, zoom_out_sub_menu, reset_zoom_sub_menu, fullscreen_sub_menu},
    .on_click = []() {},
    .on_hover = []() {}
};

// Layer Menu Subitems
menu_item new_layer_sub_menu = {
    .title = "New Layer",
    .shortcut = "⇧⌘N",
    .tooltip_title = "New Layer",
    .tooltip_desc = "Create a new layer",
    .sd = separator_direction::NONE,
    .icon = "newlayer_icon.png",
    .children = {},
    .on_click = []() { /* New Layer logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item duplicate_layer_sub_menu = {
    .title = "Duplicate Layer",
    .shortcut = "⌘D",
    .tooltip_title = "Duplicate Layer",
    .tooltip_desc = "Duplicate current layer",
    .sd = separator_direction::NONE,
    .icon = "duplayer_icon.png",
    .children = {},
    .on_click = []() { /* Duplicate Layer logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item merge_down_sub_menu = {
    .title = "Merge Down",
    .shortcut = "⌘E",
    .tooltip_title = "Merge Down",
    .tooltip_desc = "Merge with layer below",
    .sd = separator_direction::NONE,
    .icon = "merge_icon.png",
    .children = {},
    .on_click = []() { /* Merge Down logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item delete_layer_sub_menu = {
    .title = "Delete Layer",
    .shortcut = "⌫",
    .tooltip_title = "Delete Layer",
    .tooltip_desc = "Delete current layer",
    .sd = separator_direction::NONE,
    .icon = "dellayer_icon.png",
    .children = {},
    .on_click = []() { /* Delete Layer logic */ },
    .on_hover = []() { /* Show tooltip */ }
};

menu_item layer_menu = {
    .title = "Layer",
    .shortcut = "",
    .tooltip_title = "Layer Menu",
    .tooltip_desc = "Layer operations",
    .sd = separator_direction::NONE,
    .icon = "layer_icon.png",
    .children = {new_layer_sub_menu, duplicate_layer_sub_menu, merge_down_sub_menu, delete_layer_sub_menu},
    .on_click = []() {},
    .on_hover = []() {}
};

// Help Menu Subitems
menu_item about_sub_menu = {
    .title = "About",
    .shortcut = "",
    .tooltip_title = "About",
    .tooltip_desc = "About this application",
    .sd = separator_direction::NONE,
    .icon = "about_icon.png",
    .children = {},
    .on_click = []() { /* About logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item documentation_sub_menu = {
    .title = "Documentation",
    .shortcut = "F1",
    .tooltip_title = "Documentation",
    .tooltip_desc = "Open documentation",
    .sd = separator_direction::NONE,
    .icon = "docs_icon.png",
    .children = {},
    .on_click = []() { /* Documentation logic */ },
    .on_hover = []() { /* Show tooltip */ }
};
menu_item report_issue_sub_menu = {
    .title = "Report Issue",
    .shortcut = "",
    .tooltip_title = "Report Issue",
    .tooltip_desc = "Report a bug or issue",
    .sd = separator_direction::NONE,
    .icon = "bug_icon.png",
    .children = {},
    .on_click = []() { /* Issue reporting logic */ },
    .on_hover = []() { /* Show tooltip */ }
};

menu_item help_menu = {
    .title = "Help",
    .shortcut = "",
    .tooltip_title = "Help Menu",
    .tooltip_desc = "Get help",
    .sd = separator_direction::NONE,
    .icon = "help_icon.png",
    .children = {about_sub_menu, documentation_sub_menu, report_issue_sub_menu},
    .on_click = []() {},
    .on_hover = []() {}
};

// Top-level Navbar
menu_item gNavbar = {
    .title = "",
    .shortcut = "",
    .tooltip_title = "Navbar",
    .tooltip_desc = "The main navigation bar",
    .sd = separator_direction::NONE,
    .icon = "",
    .children = {file_menu, edit_menu, view_menu, layer_menu, help_menu},
    .on_click = []() {},
    .on_hover = []() {}
};

void draw_subitems(const menu_item& item) {
    if (ImGui::BeginMenu(item.title.c_str())) {
        for (const auto &subitem : item.children) {
            if(subitem.sd == separator_direction::UP){
              ImGui::Separator();
}
            if (!subitem.children.empty()) {
                draw_subitems(subitem);
            } else {
                if (ImGui::MenuItem(subitem.title.c_str(), subitem.shortcut.c_str())) {
                    if (subitem.on_click) subitem.on_click();
                }
            }
            if(subitem.sd == separator_direction::DOWN){
              ImGui::Separator();
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
