#include "PreferencesTab.h"
#include "PreferencesTab.AppearanceTab.h"
#include "PreferencesTab.ColorsTab.h"
#include "PreferencesTab.DesktopTab.h"
#include "PreferencesTab.FontsTab.h"
#include "PreferencesTab.KeysTab.h"
#include "PreferencesTab.TaskBarTab.h"
#include "PreferencesTab.WindowsTab.h"
#include <gtkmm.h>
#include <fstream>
#include <sstream>
#include <map>

PreferencesTab::PreferencesTab(const std::string& configDir) : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10) {
    this->configDir = configDir;
    this->set_border_width(10);

    // Title and subtitle
    Gtk::Box* titleBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
    Gtk::Label* title = Gtk::manage(new Gtk::Label("Preferences"));
    title->set_halign(Gtk::ALIGN_START);
    Pango::FontDescription titleFont("Bold 14");
    title->override_font(titleFont);
    titleBox->pack_start(*title, Gtk::PACK_SHRINK);

    Gtk::Label* subtitle = Gtk::manage(new Gtk::Label("IceWM preferences (~/.icewm/preferences)"));
    subtitle->set_halign(Gtk::ALIGN_START);
    titleBox->pack_start(*subtitle, Gtk::PACK_SHRINK);
    this->pack_start(*titleBox, Gtk::PACK_SHRINK);

    // Create notebook for tabs
    Gtk::Notebook* notebook = Gtk::manage(new Gtk::Notebook());
    notebook->set_tab_pos(Gtk::POS_TOP);
    notebook->set_scrollable(true);

    // Create and add tabs
    appearanceTab = Gtk::manage(new PrefAppearanceTab());
    colorsTab = Gtk::manage(new PrefColorsTab());
    desktopTab = Gtk::manage(new PrefDesktopTab(configDir));
    fontsTab = Gtk::manage(new PrefFontsTab());
    keysTab = Gtk::manage(new PrefKeysTab());
    taskBarTab = Gtk::manage(new PrefTaskBarTab(configDir));
    windowsTab = Gtk::manage(new PrefWindowsTab(configDir));

    notebook->append_page(*appearanceTab, "Appearance");
    notebook->append_page(*colorsTab, "Colors");
    notebook->append_page(*desktopTab, "Desktop");
    notebook->append_page(*fontsTab, "Fonts");
    notebook->append_page(*keysTab, "Keys");
    notebook->append_page(*taskBarTab, "TaskBar");
    notebook->append_page(*windowsTab, "Windows");
    
    this->pack_start(*notebook, Gtk::PACK_EXPAND_WIDGET);
    
    // Create button box
    Gtk::ButtonBox* buttonBox = Gtk::manage(new Gtk::ButtonBox(Gtk::ORIENTATION_HORIZONTAL));
    buttonBox->set_layout(Gtk::BUTTONBOX_END);
    buttonBox->set_spacing(10);
    buttonBox->set_margin_top(10);

    saveButton = Gtk::manage(new Gtk::Button("Save"));
    loadButton = Gtk::manage(new Gtk::Button("Load"));
    resetButton = Gtk::manage(new Gtk::Button("Reset"));
    refreshButton = Gtk::manage(new Gtk::Button("Refresh"));
    applyButton = Gtk::manage(new Gtk::Button("Apply"));

    saveButton->signal_clicked().connect(sigc::mem_fun(*this, &PreferencesTab::on_save_clicked));
    loadButton->signal_clicked().connect(sigc::mem_fun(*this, &PreferencesTab::on_load_clicked));
    resetButton->signal_clicked().connect(sigc::mem_fun(*this, &PreferencesTab::on_reset_clicked));
    refreshButton->signal_clicked().connect(sigc::mem_fun(*this, &PreferencesTab::on_refresh_clicked));
    applyButton->signal_clicked().connect(sigc::mem_fun(*this, &PreferencesTab::on_apply_clicked));

    buttonBox->pack_start(*saveButton, Gtk::PACK_SHRINK);
    buttonBox->pack_start(*loadButton, Gtk::PACK_SHRINK);
    buttonBox->pack_start(*resetButton, Gtk::PACK_SHRINK);
    buttonBox->pack_start(*refreshButton, Gtk::PACK_SHRINK);
    buttonBox->pack_start(*applyButton, Gtk::PACK_SHRINK);

    this->pack_start(*buttonBox, false, false, 0);

    // Load preferences
    loadPreferencesFile();
    show_all_children();


}

void PreferencesTab::loadPreferencesFile() {
    std::ifstream file(configDir + "/preferences");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t eqPos = line.find('=');
            if (eqPos != std::string::npos) {
                std::string key = line.substr(0, eqPos);
                std::string value = line.substr(eqPos + 1);
                preferences[key] = value;
            }
        }
        file.close();
    }
    // Apply preferences to tabs
    appearanceTab->loadPreferences(preferences);
    colorsTab->loadPreferences(preferences);
    desktopTab->loadPreferences(preferences);
    fontsTab->loadPreferences(preferences);
    keysTab->loadPreferences(preferences);
    taskBarTab->loadPreferences(preferences);
    windowsTab->loadPreferences(preferences);
}

void PreferencesTab::savePreferencesFile() {
    std::ofstream file(configDir + "/preferences");
    if (file.is_open()) {
        for (const auto& pair : preferences) {
            file << pair.first << "=" << pair.second << std::endl;
        }
        file.close();
    }
}

void PreferencesTab::updateWidgets() {
    appearanceTab->loadPreferences(preferences);
    colorsTab->loadPreferences(preferences);
    desktopTab->loadPreferences(preferences);
    fontsTab->loadPreferences(preferences);
    keysTab->loadPreferences(preferences);
    taskBarTab->loadPreferences(preferences);
    windowsTab->loadPreferences(preferences);
}

void PreferencesTab::on_save_clicked() {
    // Save from widgets to preferences map
    appearanceTab->savePreferences(preferences);
    colorsTab->savePreferences(preferences);
    desktopTab->savePreferences(preferences);
    fontsTab->savePreferences(preferences);
    keysTab->savePreferences(preferences);
    taskBarTab->savePreferences(preferences);
    windowsTab->savePreferences(preferences);
    savePreferencesFile();
}

void PreferencesTab::on_load_clicked() {
    loadPreferencesFile();
}

void PreferencesTab::on_reset_clicked() {
    appearanceTab->resetWidgets();
    colorsTab->resetWidgets();
    desktopTab->resetWidgets();
    fontsTab->resetWidgets();
    keysTab->resetWidgets();
    taskBarTab->resetWidgets();
    windowsTab->resetWidgets();
}

void PreferencesTab::on_refresh_clicked() {
    loadPreferencesFile();
}

void PreferencesTab::on_apply_clicked() {
    on_save_clicked();
}

void PreferencesTab::refresh() {
    loadPreferencesFile();
}
