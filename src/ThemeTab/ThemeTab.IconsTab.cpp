#include "ThemeTab.IconsTab.h"
#include <gtkmm/messagedialog.h>
#include <fstream>
#include <sstream>

IconsTab::IconsTab(const std::string& configDir)
    : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5), configDir(configDir) {
    set_margin_left(10);
    set_margin_top(10);

    auto* title = Gtk::manage(new Gtk::Label());
    title->set_markup("<b>Icon Configuration</b>");
    title->set_halign(Gtk::ALIGN_START);
    pack_start(*title, Gtk::PACK_SHRINK);

    auto* scrolled = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled->set_min_content_height(400);

    auto* container = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));

    // Example icon rows – add as needed
    createIconRow(container, "Menu Icon:", "IconMenu", "default.png");
    createIconRow(container, "Title Bar Icon:", "IconTitle", "default.png");
    createIconRow(container, "Tooltip Icon:", "IconTooltip", "default.png");

    scrolled->add(*container);
    pack_start(*scrolled, Gtk::PACK_EXPAND_WIDGET);

    // Buttons
    auto* btnBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* saveBtn = Gtk::manage(new Gtk::Button("_Save Icons", true));
    auto* loadBtn = Gtk::manage(new Gtk::Button("_Load", true));
    auto* resetBtn = Gtk::manage(new Gtk::Button("_Reset", true));
    btnBox->pack_start(*saveBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*loadBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*resetBtn, Gtk::PACK_SHRINK);
    pack_start(*btnBox, Gtk::PACK_SHRINK);

    saveBtn->signal_clicked().connect(sigc::mem_fun(*this, &IconsTab::saveIcons));
    loadBtn->signal_clicked().connect(sigc::mem_fun(*this, &IconsTab::loadIcons));
    resetBtn->signal_clicked().connect([this]() {
        for (auto& [prop, entry] : iconEntries) {
            entry->set_text("default.png");
        }
    });

    loadIcons();
}

void IconsTab::createIconRow(Gtk::Box* container, const std::string& label, const std::string& property, const std::string& defaultPath) {
    auto* row = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* lbl = Gtk::manage(new Gtk::Label(label));
    lbl->set_size_request(180, -1);
    lbl->set_halign(Gtk::ALIGN_START);

    auto* entry = Gtk::manage(new Gtk::Entry());
    entry->set_text(defaultPath);
    entry->set_size_request(150, -1);
    entry->signal_changed().connect([this, property, entry]() {
        onIconChanged(property, entry->get_text());
    });

    iconEntries[property] = entry;
    row->pack_start(*lbl, Gtk::PACK_SHRINK);
    row->pack_start(*entry, Gtk::PACK_SHRINK);
    container->pack_start(*row, Gtk::PACK_SHRINK);
}

void IconsTab::onIconChanged(const std::string& property, const Glib::ustring& path) {
    // Icon changed – will be saved when Save is clicked
    (void)property; (void)path; // suppress unused warnings
}

void IconsTab::loadIcons() {
    std::ifstream file(configDir + "/preferences");
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        for (auto& [prop, entry] : iconEntries) {
            if (line.find(prop + "=") == 0) {
                size_t eq = line.find('=');
                if (eq != std::string::npos) {
                    std::string val = line.substr(eq + 1);
                    // Remove surrounding quotes if present
                    if (!val.empty() && val.front() == '"') val.erase(0,1);
                    if (!val.empty() && val.back() == '"') val.pop_back();
                    entry->set_text(val);
                }
            }
        }
    }
}

void IconsTab::saveIcons() {
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
    // Update or add icon entries
    for (auto& [prop, entry] : iconEntries) {
        std::string newLine = prop + "=\"" + entry->get_text() + "\"";
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
        Gtk::MessageDialog dlg("Icons saved!", false, Gtk::MESSAGE_INFO);
        dlg.run();
    }
}

void IconsTab::refresh() {
    loadIcons();
}
