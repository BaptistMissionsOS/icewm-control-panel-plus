#include "PrefOverrideTab.FocusTab.h"

PrefFocusTab::PrefFocusTab() 
    : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10) {
    
    set_margin_left(10);
    set_margin_top(10);
    set_margin_right(10);
    set_margin_bottom(10);

    auto* grid = Gtk::manage(new Gtk::Grid());
    grid->set_column_spacing(20);
    grid->set_row_spacing(5);

    int row = 0;
    clickToFocusCheck = Gtk::manage(new Gtk::CheckButton("Click to focus"));
    grid->attach(*clickToFocusCheck, 0, row++, 1, 1);
    
    raiseOnFocusCheck = Gtk::manage(new Gtk::CheckButton("Raise on focus"));
    grid->attach(*raiseOnFocusCheck, 0, row++, 1, 1);
    
    autoRaiseCheck = Gtk::manage(new Gtk::CheckButton("Auto raise"));
    grid->attach(*autoRaiseCheck, 0, row++, 1, 1);
    
    strongPointerFocusCheck = Gtk::manage(new Gtk::CheckButton("Strong pointer focus"));
    grid->attach(*strongPointerFocusCheck, 0, row++, 1, 1);
    
    focusOnClickClientCheck = Gtk::manage(new Gtk::CheckButton("Focus on client click"));
    grid->attach(*focusOnClickClientCheck, 0, row++, 1, 1);
    
    raiseOnClickClientCheck = Gtk::manage(new Gtk::CheckButton("Raise on client click"));
    grid->attach(*raiseOnClickClientCheck, 0, row++, 1, 1);
    
    raiseOnClickTitleBarCheck = Gtk::manage(new Gtk::CheckButton("Raise on titlebar click"));
    grid->attach(*raiseOnClickTitleBarCheck, 0, row++, 1, 1);
    
    raiseOnClickButtonCheck = Gtk::manage(new Gtk::CheckButton("Raise on button click"));
    grid->attach(*raiseOnClickButtonCheck, 0, row++, 1, 1);
    
    raiseOnClickFrameCheck = Gtk::manage(new Gtk::CheckButton("Raise on frame click"));
    grid->attach(*raiseOnClickFrameCheck, 0, row++, 1, 1);
    
    lowerOnClickWhenRaisedCheck = Gtk::manage(new Gtk::CheckButton("Lower when raised clicked"));
    grid->attach(*lowerOnClickWhenRaisedCheck, 0, row++, 1, 1);
    
    passFirstClickToClientCheck = Gtk::manage(new Gtk::CheckButton("Pass first click to client"));
    grid->attach(*passFirstClickToClientCheck, 0, row++, 1, 1);

    row = 0;
    focusChangesWorkspaceCheck = Gtk::manage(new Gtk::CheckButton("Focus changes workspace"));
    grid->attach(*focusChangesWorkspaceCheck, 1, row++, 1, 1);
    
    focusOnMapCheck = Gtk::manage(new Gtk::CheckButton("Focus on map"));
    grid->attach(*focusOnMapCheck, 1, row++, 1, 1);
    
    focusOnMapTransientCheck = Gtk::manage(new Gtk::CheckButton("Focus on transient map"));
    grid->attach(*focusOnMapTransientCheck, 1, row++, 1, 1);
    
    focusOnMapTransientActiveCheck = Gtk::manage(new Gtk::CheckButton("Focus transient if owner active"));
    grid->attach(*focusOnMapTransientActiveCheck, 1, row++, 1, 1);
    
    focusOnAppRaiseCheck = Gtk::manage(new Gtk::CheckButton("Focus on app raise"));
    grid->attach(*focusOnAppRaiseCheck, 1, row++, 1, 1);
    
    requestFocusOnAppRaiseCheck = Gtk::manage(new Gtk::CheckButton("Request focus on app raise"));
    grid->attach(*requestFocusOnAppRaiseCheck, 1, row++, 1, 1);
    
    opaqueMoveCheck = Gtk::manage(new Gtk::CheckButton("Opaque move"));
    grid->attach(*opaqueMoveCheck, 1, row++, 1, 1);
    
    opaqueResizeCheck = Gtk::manage(new Gtk::CheckButton("Opaque resize"));
    grid->attach(*opaqueResizeCheck, 1, row++, 1, 1);

    pack_start(*grid, Gtk::PACK_SHRINK);
    
    show_all_children();
}

void PrefFocusTab::setDefaults() {
    clickToFocusCheck->set_active(true);
    raiseOnFocusCheck->set_active(true);
    autoRaiseCheck->set_active(false);
    strongPointerFocusCheck->set_active(false);
    focusOnClickClientCheck->set_active(true);
    raiseOnClickClientCheck->set_active(true);
    raiseOnClickTitleBarCheck->set_active(true);
    raiseOnClickButtonCheck->set_active(true);
    raiseOnClickFrameCheck->set_active(true);
    lowerOnClickWhenRaisedCheck->set_active(false);
    passFirstClickToClientCheck->set_active(true);
    focusChangesWorkspaceCheck->set_active(false);
    focusOnMapCheck->set_active(true);
    focusOnMapTransientCheck->set_active(true);
    focusOnMapTransientActiveCheck->set_active(true);
    focusOnAppRaiseCheck->set_active(true);
    requestFocusOnAppRaiseCheck->set_active(true);
    opaqueMoveCheck->set_active(true);
    opaqueResizeCheck->set_active(true);
}
