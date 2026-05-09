#include "PrefOverrideTab.TimingsTab.h"

PrefTimingsTab::PrefTimingsTab() 
    : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10) {
    
    set_margin_left(10);
    set_margin_top(10);
    set_margin_right(10);
    set_margin_bottom(10);

    auto* scrolled = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
    
    auto* grid = Gtk::manage(new Gtk::Grid());
    grid->set_column_spacing(15);
    grid->set_row_spacing(5);

    int row = 0;
    
    grid->attach(*Gtk::manage(new Gtk::Label("Click Motion Distance:")), 0, row, 1, 1);
    clickMotionDistanceSpinner = Gtk::manage(new Gtk::SpinButton());
    clickMotionDistanceSpinner->set_range(0, 50);
    clickMotionDistanceSpinner->set_increments(1, 5);
    grid->attach(*clickMotionDistanceSpinner, 1, row++, 1, 1);
    
    grid->attach(*Gtk::manage(new Gtk::Label("Click Motion Delay (ms):")), 0, row, 1, 1);
    clickMotionDelaySpinner = Gtk::manage(new Gtk::SpinButton());
    clickMotionDelaySpinner->set_range(50, 1000);
    clickMotionDelaySpinner->set_increments(10, 100);
    grid->attach(*clickMotionDelaySpinner, 1, row++, 1, 1);
    
    grid->attach(*Gtk::manage(new Gtk::Label("Multi-Click Time (ms):")), 0, row, 1, 1);
    multiClickTimeSpinner = Gtk::manage(new Gtk::SpinButton());
    multiClickTimeSpinner->set_range(100, 2000);
    multiClickTimeSpinner->set_increments(10, 100);
    grid->attach(*multiClickTimeSpinner, 1, row++, 1, 1);
    
    grid->attach(*Gtk::manage(new Gtk::Label("Menu Activate Delay (ms):")), 0, row, 1, 1);
    menuActivateDelaySpinner = Gtk::manage(new Gtk::SpinButton());
    menuActivateDelaySpinner->set_range(0, 500);
    menuActivateDelaySpinner->set_increments(5, 50);
    grid->attach(*menuActivateDelaySpinner, 1, row++, 1, 1);
    
    grid->attach(*Gtk::manage(new Gtk::Label("Submenu Activate Delay (ms):")), 0, row, 1, 1);
    submenuMenuActivateDelaySpinner = Gtk::manage(new Gtk::SpinButton());
    submenuMenuActivateDelaySpinner->set_range(50, 1000);
    submenuMenuActivateDelaySpinner->set_increments(10, 100);
    grid->attach(*submenuMenuActivateDelaySpinner, 1, row++, 1, 1);
    
    grid->attach(*Gtk::manage(new Gtk::Label("Tooltip Delay (ms):")), 0, row, 1, 1);
    toolTipDelaySpinner = Gtk::manage(new Gtk::SpinButton());
    toolTipDelaySpinner->set_range(0, 10000);
    toolTipDelaySpinner->set_increments(100, 1000);
    grid->attach(*toolTipDelaySpinner, 1, row++, 1, 1);
    
    grid->attach(*Gtk::manage(new Gtk::Label("Tooltip Time (ms):")), 0, row, 1, 1);
    toolTipTimeSpinner = Gtk::manage(new Gtk::SpinButton());
    toolTipTimeSpinner->set_range(0, 120000);
    toolTipTimeSpinner->set_increments(1000, 10000);
    grid->attach(*toolTipTimeSpinner, 1, row++, 1, 1);
    
    grid->attach(*Gtk::manage(new Gtk::Label("Auto Hide Delay (ms):")), 0, row, 1, 1);
    autoHideDelaySpinner = Gtk::manage(new Gtk::SpinButton());
    autoHideDelaySpinner->set_range(100, 2000);
    autoHideDelaySpinner->set_increments(10, 100);
    grid->attach(*autoHideDelaySpinner, 1, row++, 1, 1);
    
    grid->attach(*Gtk::manage(new Gtk::Label("Auto Show Delay (ms):")), 0, row, 1, 1);
    autoShowDelaySpinner = Gtk::manage(new Gtk::SpinButton());
    autoShowDelaySpinner->set_range(100, 2000);
    autoShowDelaySpinner->set_increments(10, 100);
    grid->attach(*autoShowDelaySpinner, 1, row++, 1, 1);
    
    grid->attach(*Gtk::manage(new Gtk::Label("Auto Raise Delay (ms):")), 0, row, 1, 1);
    autoRaiseDelaySpinner = Gtk::manage(new Gtk::SpinButton());
    autoRaiseDelaySpinner->set_range(100, 2000);
    autoRaiseDelaySpinner->set_increments(10, 100);
    grid->attach(*autoRaiseDelaySpinner, 1, row++, 1, 1);
    
    grid->attach(*Gtk::manage(new Gtk::Label("Pointer Focus Delay (ms):")), 0, row, 1, 1);
    pointerFocusDelaySpinner = Gtk::manage(new Gtk::SpinButton());
    pointerFocusDelaySpinner->set_range(50, 1000);
    pointerFocusDelaySpinner->set_increments(10, 100);
    grid->attach(*pointerFocusDelaySpinner, 1, row++, 1, 1);
    
    grid->attach(*Gtk::manage(new Gtk::Label("Workspace Status Time (ms):")), 0, row, 1, 1);
    workspaceStatusTimeSpinner = Gtk::manage(new Gtk::SpinButton());
    workspaceStatusTimeSpinner->set_range(500, 10000);
    workspaceStatusTimeSpinner->set_increments(100, 1000);
    grid->attach(*workspaceStatusTimeSpinner, 1, row++, 1, 1);
    
    grid->attach(*Gtk::manage(new Gtk::Label("Focus Flash Time (sec):")), 0, row, 1, 1);
    focusRequestFlashTimeSpinner = Gtk::manage(new Gtk::SpinButton());
    focusRequestFlashTimeSpinner->set_range(0, 60);
    focusRequestFlashTimeSpinner->set_increments(1, 5);
    grid->attach(*focusRequestFlashTimeSpinner, 1, row++, 1, 1);
    
    grid->attach(*Gtk::manage(new Gtk::Label("Focus Flash Interval (ms):")), 0, row, 1, 1);
    focusRequestFlashIntervalSpinner = Gtk::manage(new Gtk::SpinButton());
    focusRequestFlashIntervalSpinner->set_range(0, 2000);
    focusRequestFlashIntervalSpinner->set_increments(10, 100);
    grid->attach(*focusRequestFlashIntervalSpinner, 1, row++, 1, 1);

    scrolled->add(*grid);
    pack_start(*scrolled, Gtk::PACK_EXPAND_WIDGET);
    
    show_all_children();
}

void PrefTimingsTab::setDefaults() {
    clickMotionDistanceSpinner->set_value(5);
    clickMotionDelaySpinner->set_value(200);
    multiClickTimeSpinner->set_value(400);
    menuActivateDelaySpinner->set_value(40);
    submenuMenuActivateDelaySpinner->set_value(300);
    toolTipDelaySpinner->set_value(5000);
    toolTipTimeSpinner->set_value(60000);
    autoHideDelaySpinner->set_value(300);
    autoShowDelaySpinner->set_value(500);
    autoRaiseDelaySpinner->set_value(400);
    pointerFocusDelaySpinner->set_value(200);
    workspaceStatusTimeSpinner->set_value(2500);
    focusRequestFlashTimeSpinner->set_value(0);
    focusRequestFlashIntervalSpinner->set_value(250);
}
