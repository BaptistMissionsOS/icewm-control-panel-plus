#include "PreferencesTab.WindowsTab.h"
#include <gtkmm.h>
#include <string>
#include <map>

PrefWindowsTab::PrefWindowsTab(const std::string& configDir) : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10) {
    this->set_border_width(10);
    this->set_spacing(10);

    // Create scroll container
    Gtk::ScrolledWindow* scroll = new Gtk::ScrolledWindow();
    scroll->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scroll->show();

    // Create content area
    Gtk::Box* content = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10);
    content->set_spacing(10);
    scroll->add(*content);

    // Focus Model
    Gtk::Box* focusBox = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
    focusBox->pack_start(*new Gtk::Label("Focus Model:"), Gtk::PACK_SHRINK);
    focusModelChoice = new Gtk::ComboBoxText();
    focusModelChoice->append("ClickToFocus");
    focusModelChoice->append("SloppyFocus");
    focusModelChoice->append("ExplicitFocus");
    focusModelChoice->set_active(0);
    focusBox->pack_start(*focusModelChoice, Gtk::PACK_SHRINK);
    content->pack_start(*focusBox, Gtk::PACK_SHRINK);
    focusBox->show_all();

    // Click to Focus
    clickToFocusCheck = new Gtk::CheckButton("Click to Focus");
    clickToFocusCheck->set_active(true);
    content->pack_start(*clickToFocusCheck, Gtk::PACK_SHRINK);
    clickToFocusCheck->show();

    // Raise on Click
    raiseOnClickCheck = new Gtk::CheckButton("Raise on Click");
    raiseOnClickCheck->set_active(true);
    content->pack_start(*raiseOnClickCheck, Gtk::PACK_SHRINK);
    raiseOnClickCheck->show();

    // Edge Resistance
    Gtk::Box* edgeBox = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
    edgeBox->pack_start(*new Gtk::Label("Edge Resistance:"), Gtk::PACK_SHRINK);
    edgeResistanceSpinner = new Gtk::SpinButton();
    edgeResistanceSpinner->set_range(0, 50);
    edgeResistanceSpinner->set_increments(1, 5);
    edgeResistanceSpinner->set_value(5);
    edgeBox->pack_start(*edgeResistanceSpinner, Gtk::PACK_SHRINK);
    edgeBox->pack_start(*new Gtk::Label("px"), Gtk::PACK_SHRINK);
    content->pack_start(*edgeBox, Gtk::PACK_SHRINK);
    edgeBox->show_all();

    // Add some padding at bottom
    Gtk::Box* bottomPadding = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 0);
    bottomPadding->set_size_request(0, 20);
    content->pack_end(*bottomPadding, Gtk::PACK_SHRINK);

    // Add scroll to main container
    add(*scroll);
    scroll->show();
    content->show();
    show_all_children();
}

void PrefWindowsTab::loadPreferences(const std::map<std::string, std::string>& preferences) {
    auto it = preferences.find("FocusMode");
    if (it != preferences.end()) {
        focusModelChoice->set_active_text(it->second);
    }

    it = preferences.find("ClickToFocus");
    if (it != preferences.end())
        clickToFocusCheck->set_active(it->second == "1");

    it = preferences.find("RaiseOnClick");
    if (it != preferences.end())
        raiseOnClickCheck->set_active(it->second == "1");

    it = preferences.find("EdgeResistance");
    if (it != preferences.end()) {
        try {
            edgeResistanceSpinner->set_value(std::stoi(it->second));
        } catch (const std::invalid_argument&) {
            edgeResistanceSpinner->set_value(0); // default fallback
        }
    }
}

void PrefWindowsTab::savePreferences(std::map<std::string, std::string>& preferences) {
    {
        Glib::ustring text = focusModelChoice->get_active_text();
        if (!text.empty())
            preferences["FocusMode"] = text;
    }
    preferences["ClickToFocus"] = clickToFocusCheck->get_active() ? "1" : "0";
    preferences["RaiseOnClick"] = raiseOnClickCheck->get_active() ? "1" : "0";
    preferences["EdgeResistance"] = std::to_string((int)edgeResistanceSpinner->get_value());
}

void PrefWindowsTab::resetWidgets() {
    focusModelChoice->set_active(0);
    clickToFocusCheck->set_active(true);
    raiseOnClickCheck->set_active(true);
    edgeResistanceSpinner->set_value(5);
}