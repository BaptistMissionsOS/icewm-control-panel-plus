#include "PreferencesTab.KeysTab.h"
#include <gtkmm.h>
#include <map>
#include <string>

PrefKeysTab::PrefKeysTab() 
    : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5) {
    set_margin_left(10);
    set_margin_top(10);

    auto* title = Gtk::manage(new Gtk::Label());
    title->set_markup("<b>Key Bindings</b>");
    title->set_halign(Gtk::ALIGN_START);
    pack_start(*title, Gtk::PACK_SHRINK);

    auto* scrolled = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled->set_min_content_height(400);

    auto* container = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));

    // Helper to create a key control row
    auto add_key_row = [&](const std::string& label, Gtk::Entry*& entry, const std::string& key, 
                          const std::string& default_val = "") {
        auto* row = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
        auto* lbl = Gtk::manage(new Gtk::Label(label));
        lbl->set_size_request(200, -1);
        lbl->set_halign(Gtk::ALIGN_START);
        
        entry = Gtk::manage(new Gtk::Entry());
        if (!default_val.empty()) entry->set_text(default_val);
        entry->set_size_request(150, -1);
        
        // Store key in widget data
        entry->set_data("pref_key", new std::string(key));
        
        auto* captureBtn = Gtk::manage(new Gtk::Button("Capture"));
        captureBtn->signal_clicked().connect([entry]() {
            // Placeholder for key capture
            Gtk::MessageDialog dialog(*dynamic_cast<Gtk::Window*>(entry->get_toplevel()),
                                    "Key Capture", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
            dialog.set_secondary_text("Click this dialog and press the key combination you want to capture.\n\nFeature not yet implemented - please enter the key combination manually.\n\nExample formats:\nAlt+F4\nCtrl+Alt+Delete\nAlt+Shift+Tab");
            dialog.run();
        });
        
        auto* resetBtn = Gtk::manage(new Gtk::Button("Reset"));
        resetBtn->signal_clicked().connect([entry, default_val]() {
            if (!default_val.empty()) entry->set_text(default_val);
        });
        
        row->pack_start(*lbl, Gtk::PACK_SHRINK);
        row->pack_start(*entry, Gtk::PACK_SHRINK);
        row->pack_start(*captureBtn, Gtk::PACK_SHRINK);
        row->pack_start(*resetBtn, Gtk::PACK_SHRINK);
        container->pack_start(*row, Gtk::PACK_SHRINK);
    };

    // System keys
    add_key_row("Address Bar:", keySysAddressBar, "KeySysAddressBar", "Alt+Ctrl+space");
    add_key_row("Arrange Windows:", keySysArrange, "KeySysArrange", "Alt+Shift+F5");
    add_key_row("Arrange Icons:", keySysArrangeIcons, "KeySysArrangeIcons", "Alt+Shift+F8");
    add_key_row("Cascade Windows:", keySysCascade, "KeySysCascade", "Alt+Shift+F4");
    add_key_row("Collapse TaskBar:", keySysCollapseTaskBar, "KeySysCollapseTaskBar", "Alt+Ctrl+h");
    add_key_row("Dialog:", keySysDialog, "KeySysDialog", "Alt+Ctrl+Del");
    add_key_row("Hide All Windows:", keySysHideAll, "KeySysHideAll", "Alt+Shift+F11");
    add_key_row("Keyboard Next Layout:", keySysKeyboardNext, "KeySysKeyboardNext", "");
    add_key_row("Menu:", keySysMenu, "KeySysMenu", "Ctrl+Esc");
    add_key_row("Minimize All:", keySysMinimizeAll, "KeySysMinimizeAll", "Alt+Shift+F2");
    add_key_row("Show Desktop:", keySysShowDesktop, "KeySysShowDesktop", "Alt+Ctrl+d");
    add_key_row("Switch Class:", keySysSwitchClass, "KeySysSwitchClass", "Alt+`");
    add_key_row("Switch Last:", keySysSwitchLast, "KeySysSwitchLast", "Alt+Shift+Tab");
    add_key_row("Switch Next:", keySysSwitchNext, "KeySysSwitchNext", "Alt+Tab");
    add_key_row("Tile Horizontal:", keySysTileHorizontal, "KeySysTileHorizontal", "Alt+F6");
    add_key_row("Tile Vertical:", keySysTileVertical, "KeySysTileVertical", "Alt+F5");
    add_key_row("Undo Arrange:", keySysUndoArrange, "KeySysUndoArrange", "Alt+Shift+F7");
    add_key_row("Win List Menu:", keySysWinListMenu, "KeySysWinListMenu", "Alt+Ctrl+Esc");
    add_key_row("Win Menu:", keySysWinMenu, "KeySysWinMenu", "Alt+Space");
    add_key_row("Win Next:", keySysWinNext, "KeySysWinNext", "Alt+Esc");
    add_key_row("Win Prev:", keySysWinPrev, "KeySysWinPrev", "Alt+Shift+Esc");
    add_key_row("Window List:", keySysWindowList, "KeySysWindowList", "Alt+Ctrl+0");

    // Workspace keys (1-12)
    add_key_row("Workspace 1:", keySysWorkspace1, "KeySysWorkspace1", "Alt+1");
    add_key_row("Workspace 2:", keySysWorkspace2, "KeySysWorkspace2", "Alt+2");
    add_key_row("Workspace 3:", keySysWorkspace3, "KeySysWorkspace3", "Alt+3");
    add_key_row("Workspace 4:", keySysWorkspace4, "KeySysWorkspace4", "Alt+4");
    add_key_row("Workspace 5:", keySysWorkspace5, "KeySysWorkspace5", "Alt+5");
    add_key_row("Workspace 6:", keySysWorkspace6, "KeySysWorkspace6", "Alt+6");
    add_key_row("Workspace 7:", keySysWorkspace7, "KeySysWorkspace7", "Alt+7");
    add_key_row("Workspace 8:", keySysWorkspace8, "KeySysWorkspace8", "Alt+8");
    add_key_row("Workspace 9:", keySysWorkspace9, "KeySysWorkspace9", "Alt+9");
    add_key_row("Workspace 10:", keySysWorkspace10, "KeySysWorkspace10", "Alt+0");
    add_key_row("Workspace 11:", keySysWorkspace11, "KeySysWorkspace11", "");
    add_key_row("Workspace 12:", keySysWorkspace12, "KeySysWorkspace12", "");

    // Workspace take window keys
    add_key_row("Workspace 1 Take Win:", keySysWorkspace1TakeWin, "KeySysWorkspace1TakeWin", "Alt+Shift+1");
    // ... (add others similarly)

    // Additional navigation
    add_key_row("Workspace Last:", keySysWorkspaceLast, "KeySysWorkspaceLast", "Alt+Shift+`");
    add_key_row("Workspace Last Take Win:", keySysWorkspaceLastTakeWin, "KeySysWorkspaceLastTakeWin", "");
    add_key_row("Workspace Next:", keySysWorkspaceNext, "KeySysWorkspaceNext", "Alt+Ctrl+Right");
    add_key_row("Workspace Next Take Win:", keySysWorkspaceNextTakeWin, "KeySysWorkspaceNextTakeWin", "");
    add_key_row("Workspace Prev:", keySysWorkspacePrev, "KeySysWorkspacePrev", "Alt+Ctrl+Left");
    add_key_row("Workspace Prev Take Win:", keySysWorkspacePrevTakeWin, "KeySysWorkspacePrevTakeWin", "");

    // Taskbar keys
    add_key_row("TaskBar Move Next:", keyTaskBarMoveNext, "KeyTaskBarMoveNext", "");
    add_key_row("TaskBar Move Prev:", keyTaskBarMovePrev, "KeyTaskBarMovePrev", "");
    add_key_row("TaskBar Switch Next:", keyTaskBarSwitchNext, "KeyTaskBarSwitchNext", "");
    add_key_row("TaskBar Switch Prev:", keyTaskBarSwitchPrev, "KeyTaskBarSwitchPrev", "");

    // Window management keys (abbreviated for brevity)
    // ... (similar pattern for all keySysWin* entries)

    scrolled->add(*container);
    pack_start(*scrolled, Gtk::PACK_EXPAND_WIDGET);
    show_all_children();
}

void PrefKeysTab::loadPreferences(const std::map<std::string, std::string>& prefs) {
    // Load all key preferences from map
    auto load_key = [&](Gtk::Entry* entry, const std::string& key) {
        auto it = prefs.find(key);
        if (it != prefs.end() && entry) {
            entry->set_text(it->second);
        }
    };

    load_key(keySysAddressBar, "KeySysAddressBar");
    load_key(keySysArrange, "KeySysArrange");
    // ... load all other keys similarly
}

void PrefKeysTab::savePreferences(std::map<std::string, std::string>& prefs) {
    auto save_key = [&](Gtk::Entry* entry, const std::string& key) {
        if (entry && !entry->get_text().empty()) {
            prefs[key] = entry->get_text();
        }
    };

    save_key(keySysAddressBar, "KeySysAddressBar");
    save_key(keySysArrange, "KeySysArrange");
    // ... save all other keys
}

void PrefKeysTab::resetWidgets() {
    // Reset to defaults
    keySysAddressBar->set_text("Alt+Ctrl+space");
    keySysArrange->set_text("Alt+Shift+F5");
    // ... reset all others
}

// Callbacks no longer needed with lambda connections
void PrefKeysTab::key_cb(Gtk::Widget* w, void* v) {}
void PrefKeysTab::capture_key_cb(Gtk::Widget* w, void* v) {}
void PrefKeysTab::reset_key_cb(Gtk::Widget* w, void* v) {}
