#include "PreferencesTab.AppearanceTab.h"
#include <gtkmm.h>
#include <string>
#include <map>

PrefAppearanceTab::PrefAppearanceTab() : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10) {
    this->set_border_width(10);

    // Create scroll container
    Gtk::ScrolledWindow* scroll = new Gtk::ScrolledWindow();
    scroll->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scroll->show();

    // Create content area
    Gtk::Box* content = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10);
    content->set_spacing(10);
    scroll->add(*content);

    // Font selection
    Gtk::Box* fontBox = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
    fontBox->pack_start(*new Gtk::Label("Font:"), Gtk::PACK_SHRINK);
    fontNameInput = new Gtk::Entry();
    fontNameInput->set_width_chars(30);
    fontBox->pack_start(*fontNameInput, Gtk::PACK_SHRINK);
    fontBox->pack_start(*new Gtk::Label("XFT:"), Gtk::PACK_SHRINK);
    fontNameXft = new Gtk::Entry();
    fontNameXft->set_width_chars(30);
    fontBox->pack_start(*fontNameXft, Gtk::PACK_SHRINK);
    content->pack_start(*fontBox, Gtk::PACK_SHRINK);
    fontBox->show_all();

    // Title Height
    Gtk::Box* heightBox = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
    heightBox->pack_start(*new Gtk::Label("Title Height:"), Gtk::PACK_SHRINK);
    titleHeightSpinner = new Gtk::SpinButton();
    titleHeightSpinner->set_range(10, 50);
    titleHeightSpinner->set_increments(1, 5);
    heightBox->pack_start(*titleHeightSpinner, Gtk::PACK_SHRINK);
    heightBox->pack_start(*new Gtk::Label("px"), Gtk::PACK_SHRINK);
    content->pack_start(*heightBox, Gtk::PACK_SHRINK);
    heightBox->show_all();

    // Button Layout
    Gtk::Box* layoutBox = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
    layoutBox->pack_start(*new Gtk::Label("Button Layout:"), Gtk::PACK_SHRINK);
    buttonLayoutChoice = new Gtk::ComboBoxText();
    buttonLayoutChoice->append("MS");
    buttonLayoutChoice->append("SM");
    buttonLayoutChoice->append("M");
    buttonLayoutChoice->append("S");
    layoutBox->pack_start(*buttonLayoutChoice, Gtk::PACK_SHRINK);
    content->pack_start(*layoutBox, Gtk::PACK_SHRINK);
    layoutBox->show_all();

    // Add scroll to main container
    add(*scroll);
    scroll->show();
    content->show();
    show_all_children();
}

void PrefAppearanceTab::loadPreferences(const std::map<std::string, std::string>& preferences) {
    auto it = preferences.find("TitleFontName");
    if (it != preferences.end())
        fontNameInput->set_text(it->second);
    
    it = preferences.find("TitleFontNameXft");
    if (it != preferences.end())
        fontNameXft->set_text(it->second);
    
    it = preferences.find("TitleBarHeight");
    if (it != preferences.end()) {
        try {
            titleHeightSpinner->set_value(std::stoi(it->second));
        } catch (const std::invalid_argument&) {
            titleHeightSpinner->set_value(0);
        }
    }
    
    it = preferences.find("ButtonLayout");
    if (it != preferences.end()) {
        std::string layout = it->second;
        if (layout == "MS") buttonLayoutChoice->set_active(0);
        else if (layout == "SM") buttonLayoutChoice->set_active(1);
        else if (layout == "M") buttonLayoutChoice->set_active(2);
        else if (layout == "S") buttonLayoutChoice->set_active(3);
    }
}

void PrefAppearanceTab::savePreferences(std::map<std::string, std::string>& preferences) {
    preferences["TitleFontName"] = fontNameInput->get_text();
    preferences["TitleFontNameXft"] = fontNameXft->get_text();
    preferences["TitleBarHeight"] = std::to_string((int)titleHeightSpinner->get_value());
    preferences["ButtonLayout"] = buttonLayoutChoice->get_active_text();
}

void PrefAppearanceTab::resetWidgets() {
    fontNameInput->set_text("sans-serif:size=12");
    fontNameXft->set_text("DejaVu Sans:size=12,Sans:size=12");
    titleHeightSpinner->set_value(20);
    buttonLayoutChoice->set_active(0);
}