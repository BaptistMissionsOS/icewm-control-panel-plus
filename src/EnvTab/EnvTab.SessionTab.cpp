#include "EnvTab.SessionTab.h"

EnvSessionTab::EnvSessionTab() : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5) {
    set_margin_left(10);
    set_margin_top(10);
    
    auto* row1 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* lbl1 = Gtk::manage(new Gtk::Label("DISPLAY:"));
    lbl1->set_size_request(120, -1);
    displayEntry = Gtk::manage(new Gtk::Entry());
    displayEntry->set_tooltip_text("X display number (e.g., :0)");
    displayEntry->set_hexpand(true);
    row1->pack_start(*lbl1, Gtk::PACK_SHRINK);
    row1->pack_start(*displayEntry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*row1, Gtk::PACK_SHRINK);
    
    auto* row2 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* lbl2 = Gtk::manage(new Gtk::Label("LANG:"));
    lbl2->set_size_request(120, -1);
    langEntry = Gtk::manage(new Gtk::Entry());
    langEntry->set_tooltip_text("System locale (e.g., en_US.UTF-8)");
    langEntry->set_hexpand(true);
    row2->pack_start(*lbl2, Gtk::PACK_SHRINK);
    row2->pack_start(*langEntry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*row2, Gtk::PACK_SHRINK);
    
    auto* row3 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* lbl3 = Gtk::manage(new Gtk::Label("PATH:"));
    lbl3->set_size_request(120, -1);
    pathEntry = Gtk::manage(new Gtk::Entry());
    pathEntry->set_tooltip_text("System executable search path (e.g., ~/bin:$PATH)");
    pathEntry->set_hexpand(true);
    row3->pack_start(*lbl3, Gtk::PACK_SHRINK);
    row3->pack_start(*pathEntry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*row3, Gtk::PACK_SHRINK);
}