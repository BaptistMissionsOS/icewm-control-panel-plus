#include "PrefOverrideTab.QuickSwitchTab.h"

PrefQuickSwitchTab::PrefQuickSwitchTab() 
    : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10) {
    
    set_margin_left(10);
    set_margin_top(10);
    set_margin_right(10);
    set_margin_bottom(10);

    auto* scrolled = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled->set_policy(Gtk::POLICY_NEVER, Gtk::POLICY_AUTOMATIC);
    
    auto* container = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));

    quickSwitchCheck = Gtk::manage(new Gtk::CheckButton("Enable Alt+Tab window switcher"));
    container->pack_start(*quickSwitchCheck, Gtk::PACK_SHRINK);
    
    quickSwitchToMinimizedCheck = Gtk::manage(new Gtk::CheckButton("Switch to minimized windows"));
    container->pack_start(*quickSwitchToMinimizedCheck, Gtk::PACK_SHRINK);
    
    quickSwitchToHiddenCheck = Gtk::manage(new Gtk::CheckButton("Switch to hidden windows"));
    container->pack_start(*quickSwitchToHiddenCheck, Gtk::PACK_SHRINK);
    
    quickSwitchToUrgentCheck = Gtk::manage(new Gtk::CheckButton("Prioritize urgent windows"));
    container->pack_start(*quickSwitchToUrgentCheck, Gtk::PACK_SHRINK);
    
    quickSwitchToAllWorkspacesCheck = Gtk::manage(new Gtk::CheckButton("Switch to any workspace"));
    container->pack_start(*quickSwitchToAllWorkspacesCheck, Gtk::PACK_SHRINK);
    
    quickSwitchGroupWorkspacesCheck = Gtk::manage(new Gtk::CheckButton("Group current workspace windows"));
    container->pack_start(*quickSwitchGroupWorkspacesCheck, Gtk::PACK_SHRINK);
    
    quickSwitchAllIconsCheck = Gtk::manage(new Gtk::CheckButton("Show all reachable icons"));
    container->pack_start(*quickSwitchAllIconsCheck, Gtk::PACK_SHRINK);
    
    quickSwitchTextFirstCheck = Gtk::manage(new Gtk::CheckButton("Show window title above icons"));
    container->pack_start(*quickSwitchTextFirstCheck, Gtk::PACK_SHRINK);
    
    quickSwitchSmallWindowCheck = Gtk::manage(new Gtk::CheckButton("Use small switcher window"));
    container->pack_start(*quickSwitchSmallWindowCheck, Gtk::PACK_SHRINK);
    
    quickSwitchMaxWidthCheck = Gtk::manage(new Gtk::CheckButton("Use max width for switcher"));
    container->pack_start(*quickSwitchMaxWidthCheck, Gtk::PACK_SHRINK);
    
    quickSwitchVerticalCheck = Gtk::manage(new Gtk::CheckButton("Vertical icon layout"));
    container->pack_start(*quickSwitchVerticalCheck, Gtk::PACK_SHRINK);
    
    quickSwitchHugeIconCheck = Gtk::manage(new Gtk::CheckButton("Show huge active icon"));
    container->pack_start(*quickSwitchHugeIconCheck, Gtk::PACK_SHRINK);
    
    quickSwitchFillSelectionCheck = Gtk::manage(new Gtk::CheckButton("Fill selection rectangle"));
    container->pack_start(*quickSwitchFillSelectionCheck, Gtk::PACK_SHRINK);

    scrolled->add(*container);
    pack_start(*scrolled, Gtk::PACK_EXPAND_WIDGET);
    
    show_all_children();
}

void PrefQuickSwitchTab::setDefaults() {
    quickSwitchCheck->set_active(true);
    quickSwitchToMinimizedCheck->set_active(true);
    quickSwitchToHiddenCheck->set_active(true);
    quickSwitchToUrgentCheck->set_active(true);
    quickSwitchToAllWorkspacesCheck->set_active(true);
    quickSwitchGroupWorkspacesCheck->set_active(true);
    quickSwitchAllIconsCheck->set_active(true);
    quickSwitchTextFirstCheck->set_active(false);
    quickSwitchSmallWindowCheck->set_active(false);
    quickSwitchMaxWidthCheck->set_active(false);
    quickSwitchVerticalCheck->set_active(true);
    quickSwitchHugeIconCheck->set_active(false);
    quickSwitchFillSelectionCheck->set_active(false);
}
