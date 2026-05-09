#include "PreferencesTab.FontsTab.h"
#include <gtkmm/messagedialog.h>
#include <fstream>
#include <sstream>

PrefFontsTab::PrefFontsTab() 
    : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5) {
    set_margin_left(10);
    set_margin_top(10);

    auto* title = Gtk::manage(new Gtk::Label());
    title->set_markup("<b>Font Configuration</b>");
    title->set_halign(Gtk::ALIGN_START);
    pack_start(*title, Gtk::PACK_SHRINK);

    auto* scrolled = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled->set_min_content_height(400);

    auto* container = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));

    // Create font rows
    createFontRow(container, "Title Font:", "TitleFontName", "sans 12");
    createFontRow(container, "Title Font (Xft):", "TitleFontNameXft", "DejaVu Sans 12");
    createFontRow(container, "Menu Font:", "MenuFontName", "sans 12");
    createFontRow(container, "Menu Font (Xft):", "MenuFontNameXft", "DejaVu Sans 12");
    createFontRow(container, "Active Button Font:", "ActiveButtonFontName", "sans 12");
    createFontRow(container, "Active Button Font (Xft):", "ActiveButtonFontNameXft", "DejaVu Sans 12");
    createFontRow(container, "Normal Button Font:", "NormalButtonFontName", "sans 12");
    createFontRow(container, "Normal Button Font (Xft):", "NormalButtonFontNameXft", "DejaVu Sans 12");
    createFontRow(container, "Active TaskBar Font:", "ActiveTaskBarFontName", "sans 12");
    createFontRow(container, "Active TaskBar Font (Xft):", "ActiveTaskBarFontNameXft", "DejaVu Sans 12");
    createFontRow(container, "Normal TaskBar Font:", "NormalTaskBarFontName", "sans 12");
    createFontRow(container, "Normal TaskBar Font (Xft):", "NormalTaskBarFontNameXft", "DejaVu Sans 12");
    createFontRow(container, "Active Workspace Font:", "ActiveWorkspaceFontName", "sans 12");
    createFontRow(container, "Active Workspace Font (Xft):", "ActiveWorkspaceFontNameXft", "DejaVu Sans 12");
    createFontRow(container, "Normal Workspace Font:", "NormalWorkspaceFontName", "sans 12");
    createFontRow(container, "Normal Workspace Font (Xft):", "NormalWorkspaceFontNameXft", "DejaVu Sans 12");
    createFontRow(container, "List Box Font:", "ListBoxFontName", "sans 12");
    createFontRow(container, "List Box Font (Xft):", "ListBoxFontNameXft", "DejaVu Sans 12");
    createFontRow(container, "Status Font:", "StatusFontName", "sans 12");
    createFontRow(container, "Status Font (Xft):", "StatusFontNameXft", "DejaVu Sans 12");
    createFontRow(container, "Quick Switch Font:", "QuickSwitchFontName", "sans 12");
    createFontRow(container, "Quick Switch Font (Xft):", "QuickSwitchFontNameXft", "DejaVu Sans 12");
    createFontRow(container, "ToolTip Font:", "ToolTipFontName", "sans 12");
    createFontRow(container, "ToolTip Font (Xft):", "ToolTipFontNameXft", "DejaVu Sans 12");
    createFontRow(container, "Input Font:", "InputFontName", "sans 12");
    createFontRow(container, "Input Font (Xft):", "InputFontNameXft", "DejaVu Sans 12");
    createFontRow(container, "Label Font:", "LabelFontName", "sans 12");
    createFontRow(container, "Label Font (Xft):", "LabelFontNameXft", "DejaVu Sans 12");
    createFontRow(container, "Clock Font:", "ClockFontName", "sans 12");
    createFontRow(container, "Clock Font (Xft):", "ClockFontNameXft", "DejaVu Sans 12");
    createFontRow(container, "APM Font:", "ApmFontName", "sans 12");
    createFontRow(container, "APM Font (Xft):", "ApmFontNameXft", "DejaVu Sans 12");
    createFontRow(container, "Temp Font:", "TempFontName", "sans 12");
    createFontRow(container, "Temp Font (Xft):", "TempFontNameXft", "DejaVu Sans 12");
    createFontRow(container, "Tool Button Font:", "ToolButtonFontName", "sans 12");
    createFontRow(container, "Tool Button Font (Xft):", "ToolButtonFontNameXft", "DejaVu Sans 12");

    scrolled->add(*container);
    pack_start(*scrolled, Gtk::PACK_EXPAND_WIDGET);

    // Buttons
    auto* btnBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* saveBtn = Gtk::manage(new Gtk::Button("_Save Fonts", true));
    auto* loadBtn = Gtk::manage(new Gtk::Button("_Load", true));
    auto* resetBtn = Gtk::manage(new Gtk::Button("_Reset", true));
    
    saveBtn->signal_clicked().connect([this]() {
        // Save fonts to config file
        std::map<std::string, std::string> prefs;
        savePreferences(prefs);
        // Write to file
        std::string filename = configDir + "/preferences";
        std::ofstream file(filename);
        if (file.is_open()) {
            for (const auto& [key, value] : prefs) {
                file << key << "=" << value << "\n";
            }
            file.close();
        }
    });
    loadBtn->signal_clicked().connect([this]() { loadPreferences(); });
    resetBtn->signal_clicked().connect([this]() {
        for (auto& [prop, btn] : fontButtons) {
            btn->set_font_name("sans 12");
        }
    });

    btnBox->pack_start(*saveBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*loadBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*resetBtn, Gtk::PACK_SHRINK);
    pack_start(*btnBox, Gtk::PACK_SHRINK);

    loadPreferences();
}

void PrefFontsTab::createFontRow(Gtk::Box* container, const std::string& label, const std::string& property, const std::string& defaultFont) {
    auto* row = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* lbl = Gtk::manage(new Gtk::Label(label));
    lbl->set_size_request(180, -1);
    lbl->set_halign(Gtk::ALIGN_START);

    auto* btn = Gtk::manage(new Gtk::FontButton());
    btn->set_font_name(defaultFont);
    btn->set_size_request(150, -1);
    btn->signal_font_set().connect([this, property, btn]() {
        onFontChanged(property, btn->get_font_name());
    });

    fontButtons[property] = btn;
    row->pack_start(*lbl, Gtk::PACK_SHRINK);
    row->pack_start(*btn, Gtk::PACK_SHRINK);
    container->pack_start(*row, Gtk::PACK_SHRINK);
}

void PrefFontsTab::onFontChanged(const std::string& property, const Glib::ustring& font) {
    // Font changed - will be saved when Save is clicked
    (void)property; (void)font; // suppress unused warnings
}

void PrefFontsTab::loadPreferences() {
    std::ifstream file(configDir + "/preferences");
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        for (auto& [prop, btn] : fontButtons) {
            if (line.find(prop + "=") == 0) {
                size_t eq = line.find('=');
                if (eq != std::string::npos) {
                    std::string val = line.substr(eq + 1);
                    // Remove surrounding quotes if present
                    if (!val.empty() && val.front() == '"') val.erase(0, 1);
                    if (!val.empty() && val.back() == '"') val.pop_back();
                    btn->set_font_name(val);
                }
            }
        }
    }
}

void PrefFontsTab::loadPreferences(const std::map<std::string, std::string>& prefs) {
    for (auto& [prop, btn] : fontButtons) {
        auto it = prefs.find(prop);
        if (it != prefs.end()) {
            btn->set_font_name(it->second);
        }
    }
}

void PrefFontsTab::savePreferences(std::map<std::string, std::string>& prefs) {
    for (auto& [prop, btn] : fontButtons) {
        prefs[prop] = btn->get_font_name();
    }
}

void PrefFontsTab::resetWidgets() {
    for (auto& [prop, btn] : fontButtons) {
        btn->set_font_name("sans 12");
    }
}