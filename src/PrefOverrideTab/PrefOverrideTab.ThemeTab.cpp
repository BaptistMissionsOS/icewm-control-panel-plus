#include "PrefOverrideTab.ThemeTab.h"

PrefThemeTab::PrefThemeTab() 
    : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10) {
    
    set_margin_left(10);
    set_margin_top(10);
    set_margin_right(10);
    set_margin_bottom(10);

    auto* grid = Gtk::manage(new Gtk::Grid());
    grid->set_column_spacing(10);
    grid->set_row_spacing(10);

    int row = 0;
    grid->attach(*Gtk::manage(new Gtk::Label("Title Font:")), 0, row, 1, 1);
    titleFontInput = Gtk::manage(new Gtk::Entry());
    titleFontInput->set_tooltip_text("Override theme title font (empty = use theme)");
    grid->attach(*titleFontInput, 1, row++, 1, 1);
    
    grid->attach(*Gtk::manage(new Gtk::Label("Menu Font:")), 0, row, 1, 1);
    menuFontInput = Gtk::manage(new Gtk::Entry());
    menuFontInput->set_tooltip_text("Override theme menu font (empty = use theme)");
    grid->attach(*menuFontInput, 1, row++, 1, 1);
    
    grid->attach(*Gtk::manage(new Gtk::Label("Title Height:")), 0, row, 1, 1);
    titleHeightSpinner = Gtk::manage(new Gtk::SpinButton());
    titleHeightSpinner->set_range(0, 50);
    titleHeightSpinner->set_increments(1, 5);
    titleHeightSpinner->set_tooltip_text("0 = use theme value");
    grid->attach(*titleHeightSpinner, 1, row++, 1, 1);
    
    grid->attach(*Gtk::manage(new Gtk::Label("Border Width:")), 0, row, 1, 1);
    borderWidthSpinner = Gtk::manage(new Gtk::SpinButton());
    borderWidthSpinner->set_range(0, 10);
    borderWidthSpinner->set_increments(1, 2);
    borderWidthSpinner->set_tooltip_text("0 = use theme value");
    grid->attach(*borderWidthSpinner, 1, row++, 1, 1);
    
    pack_start(*grid, Gtk::PACK_SHRINK);
    
    show_all_children();
}

void PrefThemeTab::setDefaults() {
    titleFontInput->set_text("");
    menuFontInput->set_text("");
    titleHeightSpinner->set_value(0);
    borderWidthSpinner->set_value(0);
}
