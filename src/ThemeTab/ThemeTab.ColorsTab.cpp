#include "ThemeTab.ColorsTab.h"
#include <gtkmm/messagedialog.h>
#include <fstream>
#include <sstream>

ColorsTab::ColorsTab(const std::string& configDir) : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5), configDir(configDir) {
    set_margin_left(10);
    set_margin_top(10);
    
    auto* title = Gtk::manage(new Gtk::Label());
    title->set_markup("<b>Color Configuration</b>");
    title->set_halign(Gtk::ALIGN_START);
    pack_start(*title, Gtk::PACK_SHRINK);
    
    scrolled = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled->set_min_content_height(400);
    
    container = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    
    // Windows & Dialogs
    winFrame = Gtk::manage(new Gtk::Frame("Windows & Dialogs"));
    auto* winBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 3));
    winBox->set_margin_left(10);
    winBox->set_margin_top(5);
    winBox->set_margin_bottom(5);
    createColorRow(winBox, "Dialog:", "ColorDialog", Gdk::RGBA("#808080"));
    createColorRow(winBox, "Normal Border:", "ColorNormalBorder", Gdk::RGBA("#808080"));
    createColorRow(winBox, "Active Border:", "ColorActiveBorder", Gdk::RGBA("#c0c0c0"));
    winFrame->add(*winBox);
    container->pack_start(*winFrame, Gtk::PACK_SHRINK);
    
    // Title Bars
    titleFrame = Gtk::manage(new Gtk::Frame("Title Bars"));
    auto* titleBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 3));
    titleBox->set_margin_left(10);
    titleBox->set_margin_top(5);
    titleBox->set_margin_bottom(5);
    createColorRow(titleBox, "Normal TitleBar:", "ColorNormalTitleBar", Gdk::RGBA("#808080"));
    createColorRow(titleBox, "Normal Title Text:", "ColorNormalTitleBarText", Gdk::RGBA("#000000"));
    createColorRow(titleBox, "Normal Title Shadow:", "ColorNormalTitleBarShadow", Gdk::RGBA("#404040"));
    createColorRow(titleBox, "Active TitleBar:", "ColorActiveTitleBar", Gdk::RGBA("#0000ff"));
    createColorRow(titleBox, "Active Title Text:", "ColorActiveTitleBarText", Gdk::RGBA("#ffffff"));
    createColorRow(titleBox, "Active Title Shadow:", "ColorActiveTitleBarShadow", Gdk::RGBA("#404040"));
    titleFrame->add(*titleBox);
    container->pack_start(*titleFrame, Gtk::PACK_SHRINK);
    
    // Buttons
    btnFrame = Gtk::manage(new Gtk::Frame("Buttons"));
    auto* btnBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 3));
    btnBox->set_margin_left(10);
    btnBox->set_margin_top(5);
    btnBox->set_margin_bottom(5);
    createColorRow(btnBox, "Normal Title Button:", "ColorNormalTitleButton", Gdk::RGBA("#808080"));
    createColorRow(btnBox, "Normal Title Btn Text:", "ColorNormalTitleButtonText", Gdk::RGBA("#000000"));
    createColorRow(btnBox, "Tool Button:", "ColorToolButton", Gdk::RGBA("#808080"));
    createColorRow(btnBox, "Tool Btn Text:", "ColorToolButtonText", Gdk::RGBA("#000000"));
    createColorRow(btnBox, "Normal Button:", "ColorNormalButton", Gdk::RGBA("#808080"));
    createColorRow(btnBox, "Normal Btn Text:", "ColorNormalButtonText", Gdk::RGBA("#000000"));
    createColorRow(btnBox, "Active Button:", "ColorActiveButton", Gdk::RGBA("#c0c0c0"));
    createColorRow(btnBox, "Active Btn Text:", "ColorActiveButtonText", Gdk::RGBA("#000000"));
    btnFrame->add(*btnBox);
    container->pack_start(*btnFrame, Gtk::PACK_SHRINK);
    
    // TaskBar
    taskFrame = Gtk::manage(new Gtk::Frame("TaskBar"));
    auto* taskBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 3));
    taskBox->set_margin_left(10);
    taskBox->set_margin_top(5);
    taskBox->set_margin_bottom(5);
    createColorRow(taskBox, "Default TaskBar:", "ColorDefaultTaskBar", Gdk::RGBA("#808080"));
    createColorRow(taskBox, "Normal TaskApp:", "ColorNormalTaskBarApp", Gdk::RGBA("#808080"));
    createColorRow(taskBox, "Normal App Text:", "ColorNormalTaskBarAppText", Gdk::RGBA("#000000"));
    createColorRow(taskBox, "Active TaskApp:", "ColorActiveTaskBarApp", Gdk::RGBA("#c0c0c0"));
    createColorRow(taskBox, "Active App Text:", "ColorActiveTaskBarAppText", Gdk::RGBA("#000000"));
    createColorRow(taskBox, "Minimized App:", "ColorMinimizedTaskBarApp", Gdk::RGBA("#404040"));
    createColorRow(taskBox, "Min App Text:", "ColorMinimizedTaskBarAppText", Gdk::RGBA("#000000"));
    createColorRow(taskBox, "Invisible App:", "ColorInvisibleTaskBarApp", Gdk::RGBA("#404040"));
    createColorRow(taskBox, "Inv App Text:", "ColorInvisibleTaskBarAppText", Gdk::RGBA("#000000"));
    taskFrame->add(*taskBox);
    container->pack_start(*taskFrame, Gtk::PACK_SHRINK);
    
    // Menu
    menuFrame = Gtk::manage(new Gtk::Frame("Menu"));
    auto* menuBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 3));
    menuBox->set_margin_left(10);
    menuBox->set_margin_top(5);
    menuBox->set_margin_bottom(5);
    createColorRow(menuBox, "Normal Menu:", "ColorNormalMenu", Gdk::RGBA("#808080"));
    createColorRow(menuBox, "Menu Item Text:", "ColorNormalMenuItemText", Gdk::RGBA("#000000"));
    createColorRow(menuBox, "Active Menu:", "ColorActiveMenuItem", Gdk::RGBA("#0000ff"));
    createColorRow(menuBox, "Active Menu Text:", "ColorActiveMenuItemText", Gdk::RGBA("#ffffff"));
    createColorRow(menuBox, "Disabled Menu Text:", "ColorDisabledMenuItemText", Gdk::RGBA("#404040"));
    createColorRow(menuBox, "Disabled Menu Shadow:", "ColorDisabledMenuItemShadow", Gdk::RGBA("#404040"));
    menuFrame->add(*menuBox);
    container->pack_start(*menuFrame, Gtk::PACK_SHRINK);
    
    // Workspace
    wsFrame = Gtk::manage(new Gtk::Frame("Workspace Switcher"));
    auto* wsBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 3));
    wsBox->set_margin_left(10);
    wsBox->set_margin_top(5);
    wsBox->set_margin_bottom(5);
    createColorRow(wsBox, "Normal Wks Button:", "ColorNormalWorkspaceButton", Gdk::RGBA("#808080"));
    createColorRow(wsBox, "Normal Wks Text:", "ColorNormalWorkspaceButtonText", Gdk::RGBA("#000000"));
    createColorRow(wsBox, "Active Wks Button:", "ColorActiveWorkspaceButton", Gdk::RGBA("#c0c0c0"));
    createColorRow(wsBox, "Active Wks Text:", "ColorActiveWorkspaceButtonText", Gdk::RGBA("#000000"));
    wsFrame->add(*wsBox);
    container->pack_start(*wsFrame, Gtk::PACK_SHRINK);
    
    // Input & ListBox
    inputFrame = Gtk::manage(new Gtk::Frame("Input & List"));
    auto* inputBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 3));
    inputBox->set_margin_left(10);
    inputBox->set_margin_top(5);
    inputBox->set_margin_bottom(5);
    createColorRow(inputBox, "Input Background:", "ColorInput", Gdk::RGBA("#ffffff"));
    createColorRow(inputBox, "Input Text:", "ColorInputText", Gdk::RGBA("#000000"));
    createColorRow(inputBox, "Input Selection:", "ColorInputSelection", Gdk::RGBA("#0000ff"));
    createColorRow(inputBox, "ListBox:", "ColorListBox", Gdk::RGBA("#ffffff"));
    createColorRow(inputBox, "ListBox Text:", "ColorListBoxText", Gdk::RGBA("#000000"));
    createColorRow(inputBox, "ListBox Selection:", "ColorListBoxSelection", Gdk::RGBA("#0000ff"));
    inputFrame->add(*inputBox);
    container->pack_start(*inputFrame, Gtk::PACK_SHRINK);
    
    // Clock & Tooltip
    clockFrame = Gtk::manage(new Gtk::Frame("Clock & Tooltip"));
    auto* clockBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 3));
    clockBox->set_margin_left(10);
    clockBox->set_margin_top(5);
    clockBox->set_margin_bottom(5);
    createColorRow(clockBox, "Clock:", "ColorClock", Gdk::RGBA("#808080"));
    createColorRow(clockBox, "Clock Text:", "ColorClockText", Gdk::RGBA("#000000"));
    createColorRow(clockBox, "Tooltip:", "ColorToolTip", Gdk::RGBA("#ffffc0"));
    createColorRow(clockBox, "Tooltip Text:", "ColorToolTipText", Gdk::RGBA("#000000"));
    clockFrame->add(*clockBox);
    container->pack_start(*clockFrame, Gtk::PACK_SHRINK);
    
    // ScrollBar
    scrollFrame = Gtk::manage(new Gtk::Frame("ScrollBar"));
    auto* scrollBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 3));
    scrollBox->set_margin_left(10);
    scrollBox->set_margin_top(5);
    scrollBox->set_margin_bottom(5);
    createColorRow(scrollBox, "ScrollBar:", "ColorScrollBar", Gdk::RGBA("#c0c0c0"));
    createColorRow(scrollBox, "ScrollBar Slider:", "ColorScrollBarSlider", Gdk::RGBA("#808080"));
    createColorRow(scrollBox, "ScrollBar Button:", "ColorScrollBarButton", Gdk::RGBA("#c0c0c0"));
    scrollFrame->add(*scrollBox);
    container->pack_start(*scrollFrame, Gtk::PACK_SHRINK);
    
    scrolled->add(*container);
    pack_start(*scrolled, Gtk::PACK_EXPAND_WIDGET);
    
    // Buttons
    auto* btnBox2 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* saveBtn = Gtk::manage(new Gtk::Button("_Save Colors", true));
    auto* loadBtn = Gtk::manage(new Gtk::Button("_Load", true));
    auto* resetBtn = Gtk::manage(new Gtk::Button("_Reset", true));
    btnBox2->pack_start(*saveBtn, Gtk::PACK_SHRINK);
    btnBox2->pack_start(*loadBtn, Gtk::PACK_SHRINK);
    btnBox2->pack_start(*resetBtn, Gtk::PACK_SHRINK);
    pack_start(*btnBox2, Gtk::PACK_SHRINK);
    
    saveBtn->signal_clicked().connect(sigc::mem_fun(*this, &ColorsTab::saveColors));
    loadBtn->signal_clicked().connect(sigc::mem_fun(*this, &ColorsTab::loadColors));
    resetBtn->signal_clicked().connect([this]() {
        for (auto& [prop, btn] : colorButtons) {
            btn->set_rgba(Gdk::RGBA("#808080"));
        }
    });
    
    loadColors();

    // Force fix for this tab
    Glib::RefPtr<Gtk::StyleContext> ctx = get_style_context();
    ctx->add_class("icewm-colors-tab");

    Gdk::RGBA bg;
    gdk_rgba_parse(bg.gobj(), "#303744");
    scrolled->override_background_color(bg);
}

void ColorsTab::createColorRow(Gtk::Box* container, const std::string& label, const std::string& property, const Gdk::RGBA& defaultColor) {
    auto* row = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* lbl = Gtk::manage(new Gtk::Label(label));
    lbl->set_size_request(180, -1);
    lbl->set_halign(Gtk::ALIGN_START);
    
    auto* btn = Gtk::manage(new Gtk::ColorButton());
    btn->set_rgba(defaultColor);
    btn->set_size_request(60, 25);
    btn->signal_color_set().connect([this, property, btn]() {
        onColorChanged(property, btn->get_rgba());
    });
    
    colorButtons[property] = btn;
    
    row->pack_start(*lbl, Gtk::PACK_SHRINK);
    row->pack_start(*btn, Gtk::PACK_SHRINK);
    container->pack_start(*row, Gtk::PACK_SHRINK);
}

void ColorsTab::onColorChanged(const std::string& property, const Gdk::RGBA& color) {
    // Color changed - will be saved when Save is clicked
}

void ColorsTab::loadColors() {
    // First try to load from current IceWM theme
    std::string themeName;
    std::string themeFile = configDir + "/theme";
    std::ifstream tf(themeFile);
    std::string line;
    while (std::getline(tf, line)) {
        if (line.empty() || line[0] == '#') continue;
        size_t pos = line.find("Theme=");
        if (pos != std::string::npos) {
            themeName = line.substr(pos + 6);
        } else {
            themeName = line;
        }
        // Clean quotes and whitespace
        if (themeName.size() >= 2 && ((themeName.front() == '"' && themeName.back() == '"') ||
                                      (themeName.front() == '\'' && themeName.back() == '\''))) {
            themeName = themeName.substr(1, themeName.size() - 2);
        }
        while (!themeName.empty() && (themeName.back() == '\r' || isspace(themeName.back())))
            themeName.pop_back();
        while (!themeName.empty() && isspace(themeName.front()))
            themeName.erase(0, 1);
        if (!themeName.empty()) break;
    }
    
    // Remove /default.theme if present
    size_t slash = themeName.find("/default.theme");
    if (slash != std::string::npos) themeName = themeName.substr(0, slash);
    
    // Load colors from theme file
    std::map<std::string, std::string> themeColors;
    if (!themeName.empty()) {
        std::string defaultThemePath = configDir + "/themes/" + themeName + "/default.theme";
        std::ifstream dt(defaultThemePath);
        if (!dt.is_open()) {
            defaultThemePath = "/usr/share/icewm/themes/" + themeName + "/default.theme";
            dt.open(defaultThemePath);
        }
        if (dt.is_open()) {
            std::string line;
            while (std::getline(dt, line)) {
                if (line.empty() || line[0] == '#') continue;
                size_t eq = line.find('=');
                if (eq == std::string::npos) continue;
                
                std::string key = line.substr(0, eq);
                std::string val = line.substr(eq + 1);
                // trim whitespace and quotes
                while (!val.empty() && (val.back() == '\r' || isspace(val.back()))) val.pop_back();
                while (!val.empty() && isspace(val.front())) val.erase(0, 1);
                if (!val.empty() && (val.front() == '"' || val.front() == '\'')) val.erase(0, 1);
                if (!val.empty() && (val.back() == '"' || val.back() == '\'')) val.pop_back();
                
                themeColors[key] = val;
            }
        }
    }
    
    // Also load from preferences (these override theme defaults)
    std::ifstream file(configDir + "/preferences");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            for (auto& [prop, btn] : colorButtons) {
                if (line.find(prop + "=") == 0) {
                    size_t eq = line.find('=');
                    if (eq != std::string::npos) {
                        std::string val = line.substr(eq + 1);
                        // Clean quotes
                        while (!val.empty() && (val.back() == '\r' || isspace(val.back()))) val.pop_back();
                        while (!val.empty() && isspace(val.front())) val.erase(0, 1);
                        if (!val.empty() && (val.front() == '"' || val.front() == '\'')) val.erase(0, 1);
                        if (!val.empty() && (val.back() == '"' || val.back() == '\'')) val.pop_back();
                        themeColors[prop] = val;
                    }
                }
            }
        }
    }
    
    // Now set the colors on the buttons
    for (auto& [prop, btn] : colorButtons) {
        auto it = themeColors.find(prop);
        if (it != themeColors.end()) {
            Gdk::RGBA rgba;
            // Try to parse IceWM color format (rgb:RR/GG/BB)
            const std::string& val = it->second;
            if (val.find("rgb:") == 0) {
                // Parse rgb:RR/GG/BB format
                std::string hex = val.substr(4); // Remove "rgb:"
                // Replace / with spaces for sscanf
                std::string fmt = hex;
                for (char& c : fmt) if (c == '/') c = ' ';
                int r, g, b;
                if (sscanf(fmt.c_str(), "%x %x %x", &r, &g, &b) == 3) {
                    rgba.set_red(r / 255.0);
                    rgba.set_green(g / 255.0);
                    rgba.set_blue(b / 255.0);
                    rgba.set_alpha(1.0);
                    btn->set_rgba(rgba);
                }
            } else if (val[0] == '#') {
                // Parse #RRGGBB format
                if (gdk_rgba_parse(rgba.gobj(), val.c_str())) {
                    btn->set_rgba(rgba);
                }
            }
        }
    }
}

void ColorsTab::saveColors() {
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
    
    // Update or add color entries
    for (auto& [prop, btn] : colorButtons) {
        Gdk::RGBA rgba = btn->get_rgba();
        char buf[32];
        snprintf(buf, sizeof(buf), "rgb:%02X/%02X/%02X",
                 (int)(rgba.get_red() * 255),
                 (int)(rgba.get_green() * 255),
                 (int)(rgba.get_blue() * 255));
        std::string newLine = prop + "=\"" + buf + "\"";
        
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
        Gtk::MessageDialog dlg("Colors saved!", false, Gtk::MESSAGE_INFO);
        dlg.run();
    }
}

void ColorsTab::refresh() {
    loadColors();

    // === FORCE FRAME VISIBILITY ===
    // Extract background color from loaded colors or default
    Gdk::RGBA bg;
    gdk_rgba_parse(bg.gobj(), "#303744");

    auto applyFrameFix = [this, bg](Gtk::Widget* w) {
        if (!w) return;
        w->override_background_color(bg);
        auto ctx = w->get_style_context();
        ctx->add_class("icewm-frame");
    };

    // Apply to all frames
    for (auto* frame : {winFrame, titleFrame, btnFrame, taskFrame, menuFrame, 
                        wsFrame, inputFrame, clockFrame, scrollFrame}) {
        applyFrameFix(frame);
        // Also force child box
        if (auto* box = dynamic_cast<Gtk::Box*>(frame->get_child())) {
            box->override_background_color(bg);
        }
    }

    // Force main containers
    container->override_background_color(bg);
    scrolled->override_background_color(bg);
}
