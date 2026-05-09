#include "PrefOverrideTab.EdgeSwitchTab.h"

PrefEdgeSwitchTab::PrefEdgeSwitchTab() 
    : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10) {
    
    set_margin_left(10);
    set_margin_top(10);
    set_margin_right(10);
    set_margin_bottom(10);

    edgeSwitchCheck = Gtk::manage(new Gtk::CheckButton("Enable edge workspace switching"));
    pack_start(*edgeSwitchCheck, Gtk::PACK_SHRINK);
    
    horizontalEdgeSwitchCheck = Gtk::manage(new Gtk::CheckButton("Left/Right edge switching"));
    pack_start(*horizontalEdgeSwitchCheck, Gtk::PACK_SHRINK);
    
    verticalEdgeSwitchCheck = Gtk::manage(new Gtk::CheckButton("Top/Bottom edge switching"));
    pack_start(*verticalEdgeSwitchCheck, Gtk::PACK_SHRINK);
    
    continuousEdgeSwitchCheck = Gtk::manage(new Gtk::CheckButton("Continuous edge switching"));
    pack_start(*continuousEdgeSwitchCheck, Gtk::PACK_SHRINK);
    
    auto* delayBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 10));
    delayBox->pack_start(*Gtk::manage(new Gtk::Label("Edge Switch Delay (ms):")), Gtk::PACK_SHRINK);
    
    edgeSwitchDelaySpinner = Gtk::manage(new Gtk::SpinButton());
    edgeSwitchDelaySpinner->set_range(100, 2000);
    edgeSwitchDelaySpinner->set_increments(50, 100);
    edgeSwitchDelaySpinner->set_value(600);
    delayBox->pack_start(*edgeSwitchDelaySpinner, Gtk::PACK_SHRINK);
    
    pack_start(*delayBox, Gtk::PACK_SHRINK);
    
    show_all_children();
}

void PrefEdgeSwitchTab::setDefaults() {
    edgeSwitchCheck->set_active(false);
    horizontalEdgeSwitchCheck->set_active(false);
    verticalEdgeSwitchCheck->set_active(false);
    continuousEdgeSwitchCheck->set_active(true);
    edgeSwitchDelaySpinner->set_value(600);
}
