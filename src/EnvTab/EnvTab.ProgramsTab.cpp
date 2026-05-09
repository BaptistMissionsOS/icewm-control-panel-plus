#include "EnvTab.ProgramsTab.h"

EnvProgramsTab::EnvProgramsTab() : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5) {
    set_margin_left(10);
    set_margin_top(10);
    
    auto* row1 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* lbl1 = Gtk::manage(new Gtk::Label("TERM:"));
    lbl1->set_size_request(120, -1);
    termEntry = Gtk::manage(new Gtk::Entry());
    termEntry->set_tooltip_text("Terminal emulator command");
    termEntry->set_hexpand(true);
    row1->pack_start(*lbl1, Gtk::PACK_SHRINK);
    row1->pack_start(*termEntry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*row1, Gtk::PACK_SHRINK);
    
    auto* row2 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* lbl2 = Gtk::manage(new Gtk::Label("BROWSER:"));
    lbl2->set_size_request(120, -1);
    browserEntry = Gtk::manage(new Gtk::Entry());
    browserEntry->set_tooltip_text("Default web browser command");
    browserEntry->set_hexpand(true);
    row2->pack_start(*lbl2, Gtk::PACK_SHRINK);
    row2->pack_start(*browserEntry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*row2, Gtk::PACK_SHRINK);
    
    auto* row3 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* lbl3 = Gtk::manage(new Gtk::Label("EDITOR:"));
    lbl3->set_size_request(120, -1);
    editorEntry = Gtk::manage(new Gtk::Entry());
    editorEntry->set_tooltip_text("Default text editor command");
    editorEntry->set_hexpand(true);
    row3->pack_start(*lbl3, Gtk::PACK_SHRINK);
    row3->pack_start(*editorEntry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*row3, Gtk::PACK_SHRINK);
}