#include "EnvTab.AppearanceTab.h"

EnvAppearanceTab::EnvAppearanceTab() : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5) {
    set_margin_left(10);
    set_margin_top(10);
    
    auto* row1 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* lbl1 = Gtk::manage(new Gtk::Label("GTK_THEME:"));
    lbl1->set_size_request(160, -1);
    gtkThemeEntry = Gtk::manage(new Gtk::Entry());
    gtkThemeEntry->set_tooltip_text("GTK theme name (e.g., Adwaita, Breeze)");
    gtkThemeEntry->set_hexpand(true);
    row1->pack_start(*lbl1, Gtk::PACK_SHRINK);
    row1->pack_start(*gtkThemeEntry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*row1, Gtk::PACK_SHRINK);
    
    auto* row2 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* lbl2 = Gtk::manage(new Gtk::Label("QT_STYLE:"));
    lbl2->set_size_request(160, -1);
    qtStyleEntry = Gtk::manage(new Gtk::Entry());
    qtStyleEntry->set_tooltip_text("Qt style override (gtk, fusion, windows)");
    qtStyleEntry->set_hexpand(true);
    row2->pack_start(*lbl2, Gtk::PACK_SHRINK);
    row2->pack_start(*qtStyleEntry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*row2, Gtk::PACK_SHRINK);
    
    auto* row3 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* lbl3 = Gtk::manage(new Gtk::Label("QT_QPA_PLATFORMTHEME:"));
    lbl3->set_size_request(160, -1);
    qtQpaPlatformThemeEntry = Gtk::manage(new Gtk::Entry());
    qtQpaPlatformThemeEntry->set_tooltip_text("Qt platform theme (e.g., qt5ct, qt6ct, gtk2)");
    qtQpaPlatformThemeEntry->set_hexpand(true);
    row3->pack_start(*lbl3, Gtk::PACK_SHRINK);
    row3->pack_start(*qtQpaPlatformThemeEntry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*row3, Gtk::PACK_SHRINK);
}