#include "EnvTab.SessionTab.InputMethodTab.h"

EnvInputMethodTab::EnvInputMethodTab() : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5) {
    set_margin_left(10);
    set_margin_top(10);
    
    auto* row1 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* lbl1 = Gtk::manage(new Gtk::Label("XIM:"));
    lbl1->set_size_request(120, -1);
    ximEntry = Gtk::manage(new Gtk::Entry());
    ximEntry->set_tooltip_text("X Input Method server");
    ximEntry->set_hexpand(true);
    row1->pack_start(*lbl1, Gtk::PACK_SHRINK);
    row1->pack_start(*ximEntry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*row1, Gtk::PACK_SHRINK);
    
    auto* row2 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* lbl2 = Gtk::manage(new Gtk::Label("XIM_PROGRAM:"));
    lbl2->set_size_request(120, -1);
    ximProgramEntry = Gtk::manage(new Gtk::Entry());
    ximProgramEntry->set_tooltip_text("XIM program to start (ibus, fcitx, uim)");
    ximProgramEntry->set_hexpand(true);
    row2->pack_start(*lbl2, Gtk::PACK_SHRINK);
    row2->pack_start(*ximProgramEntry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*row2, Gtk::PACK_SHRINK);
}