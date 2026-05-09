#include "EnvTab.CustomTab.h"

EnvCustomTab::EnvCustomTab() : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5) {
    set_margin_left(10);
    set_margin_top(10);
    
    auto* hint = Gtk::manage(new Gtk::Label("VAR=value format (e.g., MY_VAR=hello)"));
    hint->set_halign(Gtk::ALIGN_START);
    pack_start(*hint, Gtk::PACK_SHRINK);
    
    auto* row1 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* lbl1 = Gtk::manage(new Gtk::Label("Variable 1:"));
    lbl1->set_size_request(100, -1);
    custom1Entry = Gtk::manage(new Gtk::Entry());
    custom1Entry->set_tooltip_text("Custom environment variable");
    custom1Entry->set_hexpand(true);
    row1->pack_start(*lbl1, Gtk::PACK_SHRINK);
    row1->pack_start(*custom1Entry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*row1, Gtk::PACK_SHRINK);
    
    auto* row2 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* lbl2 = Gtk::manage(new Gtk::Label("Variable 2:"));
    lbl2->set_size_request(100, -1);
    custom2Entry = Gtk::manage(new Gtk::Entry());
    custom2Entry->set_tooltip_text("Custom environment variable");
    custom2Entry->set_hexpand(true);
    row2->pack_start(*lbl2, Gtk::PACK_SHRINK);
    row2->pack_start(*custom2Entry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*row2, Gtk::PACK_SHRINK);
}