#include "ThemeTab.StylesTab.h"
#include <gtkmm/messagedialog.h>
#include <fstream>

StylesTab::StylesTab(const std::string& configDir) : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5), configDir(configDir) {
    set_margin_left(10);
    set_margin_top(10);
    
    auto* title = Gtk::manage(new Gtk::Label());
    title->set_markup("<b>Window Styles</b>");
    title->set_halign(Gtk::ALIGN_START);
    pack_start(*title, Gtk::PACK_SHRINK);
    
    auto* scrolled = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled->set_min_content_height(400);
    
    auto* container = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    
    // Window Style section
    auto* styleFrame = Gtk::manage(new Gtk::Frame("Window Style"));
    auto* styleBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    styleBox->set_margin_left(10);
    styleBox->set_margin_top(10);
    styleBox->set_margin_bottom(10);
    
    auto* lookRow = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    lookRow->pack_start(*Gtk::manage(new Gtk::Label("Look:")), Gtk::PACK_SHRINK);
    lookCombo = Gtk::manage(new Gtk::ComboBoxText());
    lookCombo->append("default", "Default");
    lookCombo->append("win95", "Win95");
    lookCombo->append("motif", "Motif");
    lookCombo->append("pixmap", "Pixmap");
    lookCombo->append("flat", "Flat");
    lookCombo->set_active_id("default");
    lookRow->pack_start(*lookCombo, Gtk::PACK_SHRINK);
    styleBox->pack_start(*lookRow, Gtk::PACK_SHRINK);
    
    auto* heightRow = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    heightRow->pack_start(*Gtk::manage(new Gtk::Label("Title Height:")), Gtk::PACK_SHRINK);
    titleHeightSpin = Gtk::manage(new Gtk::SpinButton(Gtk::Adjustment::create(20, 10, 50), 1));
    titleHeightSpin->set_size_request(80, -1);
    heightRow->pack_start(*titleHeightSpin, Gtk::PACK_SHRINK);
    styleBox->pack_start(*heightRow, Gtk::PACK_SHRINK);
    
    styleFrame->add(*styleBox);
    container->pack_start(*styleFrame, Gtk::PACK_SHRINK);
    
    // Title Buttons section
    auto* btnFrame = Gtk::manage(new Gtk::Frame("Title Buttons"));
    auto* btnBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    btnBox->set_margin_left(10);
    btnBox->set_margin_top(10);
    btnBox->set_margin_bottom(10);
    
    auto* leftRow = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    leftRow->pack_start(*Gtk::manage(new Gtk::Label("Left Buttons:")), Gtk::PACK_SHRINK);
    titleButtonsLeftEntry = Gtk::manage(new Gtk::Entry());
    titleButtonsLeftEntry->set_text("s");
    titleButtonsLeftEntry->set_tooltip_text("s=menu, x=close, m=maximize, i=minimize, r=roll");
    titleButtonsLeftEntry->set_size_request(150, -1);
    leftRow->pack_start(*titleButtonsLeftEntry, Gtk::PACK_SHRINK);
    btnBox->pack_start(*leftRow, Gtk::PACK_SHRINK);
    
    auto* rightRow = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    rightRow->pack_start(*Gtk::manage(new Gtk::Label("Right Buttons:")), Gtk::PACK_SHRINK);
    titleButtonsRightEntry = Gtk::manage(new Gtk::Entry());
    titleButtonsRightEntry->set_text("xmi");
    titleButtonsRightEntry->set_tooltip_text("x=close, m=maximize, i=minimize, h=hide, r=roll");
    titleButtonsRightEntry->set_size_request(150, -1);
    rightRow->pack_start(*titleButtonsRightEntry, Gtk::PACK_SHRINK);
    btnBox->pack_start(*rightRow, Gtk::PACK_SHRINK);
    
    btnFrame->add(*btnBox);
    container->pack_start(*btnFrame, Gtk::PACK_SHRINK);
    
    // Fonts section
    auto* fontFrame = Gtk::manage(new Gtk::Frame("Fonts"));
    auto* fontBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    fontBox->set_margin_left(10);
    fontBox->set_margin_top(10);
    fontBox->set_margin_bottom(10);
    
    auto* titleFontRow = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    titleFontRow->pack_start(*Gtk::manage(new Gtk::Label("Title Font:")), Gtk::PACK_SHRINK);
    titleFontEntry = Gtk::manage(new Gtk::Entry());
    titleFontEntry->set_text("DejaVu Sans:size=12");
    titleFontEntry->set_size_request(200, -1);
    titleFontRow->pack_start(*titleFontEntry, Gtk::PACK_SHRINK);
    titleFontRow->pack_start(*Gtk::manage(new Gtk::Label("Size:")), Gtk::PACK_SHRINK);
    titleFontSizeSpin = Gtk::manage(new Gtk::SpinButton(Gtk::Adjustment::create(12, 6, 48), 1));
    titleFontSizeSpin->set_size_request(60, -1);
    titleFontRow->pack_start(*titleFontSizeSpin, Gtk::PACK_SHRINK);
    fontBox->pack_start(*titleFontRow, Gtk::PACK_SHRINK);
    
    auto* menuFontRow = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    menuFontRow->pack_start(*Gtk::manage(new Gtk::Label("Menu Font:")), Gtk::PACK_SHRINK);
    menuFontEntry = Gtk::manage(new Gtk::Entry());
    menuFontEntry->set_text("DejaVu Sans:size=10:bold");
    menuFontEntry->set_size_request(200, -1);
    menuFontRow->pack_start(*menuFontEntry, Gtk::PACK_SHRINK);
    menuFontRow->pack_start(*Gtk::manage(new Gtk::Label("Size:")), Gtk::PACK_SHRINK);
    menuFontSizeSpin = Gtk::manage(new Gtk::SpinButton(Gtk::Adjustment::create(10, 6, 48), 1));
    menuFontSizeSpin->set_size_request(60, -1);
    menuFontRow->pack_start(*menuFontSizeSpin, Gtk::PACK_SHRINK);
    fontBox->pack_start(*menuFontRow, Gtk::PACK_SHRINK);
    
    auto* statusFontRow = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    statusFontRow->pack_start(*Gtk::manage(new Gtk::Label("Status Font:")), Gtk::PACK_SHRINK);
    statusFontEntry = Gtk::manage(new Gtk::Entry());
    statusFontEntry->set_text("DejaVu Sans Mono:size=12:bold");
    statusFontEntry->set_size_request(200, -1);
    statusFontRow->pack_start(*statusFontEntry, Gtk::PACK_SHRINK);
    fontBox->pack_start(*statusFontRow, Gtk::PACK_SHRINK);
    
    auto* qsFontRow = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    qsFontRow->pack_start(*Gtk::manage(new Gtk::Label("QuickSwitch Font:")), Gtk::PACK_SHRINK);
    quickSwitchFontEntry = Gtk::manage(new Gtk::Entry());
    quickSwitchFontEntry->set_text("DejaVu Sans:size=12:bold");
    quickSwitchFontEntry->set_size_request(200, -1);
    qsFontRow->pack_start(*quickSwitchFontEntry, Gtk::PACK_SHRINK);
    fontBox->pack_start(*qsFontRow, Gtk::PACK_SHRINK);
    
    fontFrame->add(*fontBox);
    container->pack_start(*fontFrame, Gtk::PACK_SHRINK);
    
    scrolled->add(*container);
    pack_start(*scrolled, Gtk::PACK_EXPAND_WIDGET);
    
    // Buttons
    auto* btnBox2 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* saveBtn = Gtk::manage(new Gtk::Button("_Save", true));
    auto* loadBtn = Gtk::manage(new Gtk::Button("_Load", true));
    btnBox2->pack_start(*saveBtn, Gtk::PACK_SHRINK);
    btnBox2->pack_start(*loadBtn, Gtk::PACK_SHRINK);
    pack_start(*btnBox2, Gtk::PACK_SHRINK);
    
    saveBtn->signal_clicked().connect(sigc::mem_fun(*this, &StylesTab::saveStyles));
    loadBtn->signal_clicked().connect(sigc::mem_fun(*this, &StylesTab::loadStyles));
    
    loadStyles();
}

void StylesTab::loadStyles() {
    std::ifstream file(configDir + "/preferences");
    if (!file.is_open()) return;
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("Look=") == 0) {
            std::string val = line.substr(5);
            if (val.size() >= 2 && val.front() == '"' && val.back() == '"') {
                val = val.substr(1, val.size() - 2);
            }
            lookCombo->set_active_id(val);
        } else if (line.find("TitleBarHeight=") == 0) {
            try {
                size_t eq = line.find('=');
                if (eq != std::string::npos) {
                    try {
                        int val = std::stoi(line.substr(eq + 1));
                        titleHeightSpin->set_value(val);
                    } catch (const std::invalid_argument&) {
                        titleHeightSpin->set_value(0);
                    }
                }
            } catch (...) {}
        } else if (line.find("TitleButtonsLeft=") == 0) {
            size_t eq = line.find('=');
            if (eq != std::string::npos) {
                std::string val = line.substr(eq + 1);
                if (val.size() >= 2 && val.front() == '"' && val.back() == '"') {
                    val = val.substr(1, val.size() - 2);
                }
                titleButtonsLeftEntry->set_text(val);
            }
        } else if (line.find("TitleButtonsRight=") == 0) {
            size_t eq = line.find('=');
            if (eq != std::string::npos) {
                std::string val = line.substr(eq + 1);
                if (val.size() >= 2 && val.front() == '"' && val.back() == '"') {
                    val = val.substr(1, val.size() - 2);
                }
                titleButtonsRightEntry->set_text(val);
            }
        } else if (line.find("TitleFontNameXft=") == 0) {
            size_t eq = line.find('=');
            if (eq != std::string::npos) {
                std::string val = line.substr(eq + 1);
                if (val.size() >= 2 && val.front() == '"' && val.back() == '"') {
                    val = val.substr(1, val.size() - 2);
                }
                titleFontEntry->set_text(val);
            }
        } else if (line.find("MenuFontNameXft=") == 0) {
            size_t eq = line.find('=');
            if (eq != std::string::npos) {
                std::string val = line.substr(eq + 1);
                if (val.size() >= 2 && val.front() == '"' && val.back() == '"') {
                    val = val.substr(1, val.size() - 2);
                }
                menuFontEntry->set_text(val);
            }
        }
    }
}

void StylesTab::saveStyles() {
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
    
    auto updateOrAdd = [&lines](const std::string& key, const std::string& val) {
        bool found = false;
        for (auto& line : lines) {
            if (line.find(key + "=") == 0) {
                line = key + "=\"" + val + "\"";
                found = true;
                break;
            }
        }
        if (!found) {
            lines.push_back(key + "=\"" + val + "\"");
        }
    };
    
    updateOrAdd("Look", lookCombo->get_active_id());
    updateOrAdd("TitleBarHeight", std::to_string((int)titleHeightSpin->get_value()));
    updateOrAdd("TitleButtonsLeft", titleButtonsLeftEntry->get_text());
    updateOrAdd("TitleButtonsRight", titleButtonsRightEntry->get_text());
    updateOrAdd("TitleFontNameXft", titleFontEntry->get_text());
    updateOrAdd("MenuFontNameXft", menuFontEntry->get_text());
    updateOrAdd("StatusFontNameXft", statusFontEntry->get_text());
    updateOrAdd("QuickSwitchFontNameXft", quickSwitchFontEntry->get_text());
    
    std::ofstream outfile(configDir + "/preferences");
    if (outfile.is_open()) {
        for (const auto& line : lines) {
            outfile << line << "\n";
        }
        outfile.close();
        Gtk::MessageDialog dlg("Styles saved!", false, Gtk::MESSAGE_INFO);
        dlg.run();
    }
}

void StylesTab::refresh() {
    loadStyles();
}
