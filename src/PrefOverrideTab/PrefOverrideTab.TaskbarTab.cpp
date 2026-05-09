#include "PrefOverrideTab.TaskbarTab.h"

PrefTaskbarTab::PrefTaskbarTab() 
    : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10) {
    
    set_margin_left(10);
    set_margin_top(10);
    set_margin_right(10);
    set_margin_bottom(10);

    taskBarAtTopCheck = Gtk::manage(new Gtk::CheckButton("Taskbar at top"));
    pack_start(*taskBarAtTopCheck, Gtk::PACK_SHRINK);
    
    taskBarAutoHideCheck = Gtk::manage(new Gtk::CheckButton("Auto-hide taskbar"));
    pack_start(*taskBarAutoHideCheck, Gtk::PACK_SHRINK);
    
    taskBarShowClockCheck = Gtk::manage(new Gtk::CheckButton("Show clock"));
    pack_start(*taskBarShowClockCheck, Gtk::PACK_SHRINK);
    
    taskBarShowWorkspacesCheck = Gtk::manage(new Gtk::CheckButton("Show workspaces"));
    pack_start(*taskBarShowWorkspacesCheck, Gtk::PACK_SHRINK);
    
    taskBarShowWindowsCheck = Gtk::manage(new Gtk::CheckButton("Show windows"));
    pack_start(*taskBarShowWindowsCheck, Gtk::PACK_SHRINK);
    
    show_all_children();
}

void PrefTaskbarTab::setDefaults() {
    taskBarAtTopCheck->set_active(false);
    taskBarAutoHideCheck->set_active(false);
    taskBarShowClockCheck->set_active(true);
    taskBarShowWorkspacesCheck->set_active(true);
    taskBarShowWindowsCheck->set_active(true);
}
