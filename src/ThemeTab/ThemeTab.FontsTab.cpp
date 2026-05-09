#include "ThemeTab.FontsTab.h"
#include <gtkmm/messagedialog.h>
#include <fstream>
#include <sstream>

FontsTab::FontsTab(const std::string& configDir)
    : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5), configDir(configDir) {
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

    // Example font rows – add as needed
    createFontRow(container, "Menu Font:", "FontMenu", "sans 10");
    createFontRow(container, "Title Bar Font:", "FontTitle", "sans 10");
    createFontRow(container, "Tooltip Font:", "FontTooltip", "sans 9");

    scrolled->add(*container);
    pack_start(*scrolled, Gtk::PACK_EXPAND_WIDGET);

    // Buttons
    auto* btnBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* saveBtn = Gtk::manage(new Gtk::Button("_Save Fonts", true));
    auto* loadBtn = Gtk::manage(new Gtk::Button("_Load", true));
    auto* resetBtn = Gtk::manage(new Gtk::Button("_Reset", true));
    btnBox->pack_start(*saveBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*loadBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*resetBtn, Gtk::PACK_SHRINK);
    pack_start(*btnBox, Gtk::PACK_SHRINK);

    saveBtn->signal_clicked().connect(sigc::mem_fun(*this, &FontsTab::saveFonts));
    loadBtn->signal_clicked().connect(sigc::mem_fun(*this, &FontsTab::loadFonts));
    resetBtn->signal_clicked().connect([this]() {
        for (auto& [prop, btn] : fontButtons) {
            btn->set_font_name("sans 10");
        }
    });

    loadFonts();
}

void FontsTab::createFontRow(Gtk::Box* container, const std::string& label, const std::string& property, const std::string& defaultFont) {
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

void FontsTab::onFontChanged(const std::string& property, const Glib::ustring& font) {
    // Font changed – will be saved when Save is clicked
    (void)property; (void)font; // suppress unused warnings
}

void FontsTab::loadFonts() {
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
                    if (!val.empty() && val.front() == '"') val.erase(0,1);
                    if (!val.empty() && val.back() == '"') val.pop_back();
                    btn->set_font_name(val);
                }
            }
        }
    }
}

void FontsTab::saveFonts() {
    // Read existing preferences
    std::vector<std::string> lines;
    std::ifstream infile(configDir + "/preferences");
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            lines.push_back(line);
        }
        infile.close();
    }
    // Update or add font entries
    for (auto& [prop, btn] : fontButtons) {
        std::string newLine = prop + "=\"" + btn->get_font_name() + "\"";
        bool found = false;
        for (auto& line : lines) {
            if (line.find(prop + "=") == 0) {
                line = newLine;
                found = true;
                break;
            }
        }
        if (!found) {
            lines.push_back(newLine);
        }
    }
    // Write back
    std::ofstream outfile(configDir + "/preferences");
    if (outfile.is_open()) {
        for (const auto& line : lines) {
            outfile << line << "\n";
        }
        outfile.close();
        Gtk::MessageDialog dlg("Fonts saved!", false, Gtk::MESSAGE_INFO);
        dlg.run();
    }
}

void FontsTab::refresh() {
    loadFonts();
}
