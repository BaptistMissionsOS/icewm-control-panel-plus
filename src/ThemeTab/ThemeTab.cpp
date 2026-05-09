#include "ThemeTab.h"
#include <gtkmm/messagedialog.h>
#include <gtkmm/cssprovider.h>
#include <gdkmm/screen.h>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <algorithm>
#include <sstream>

// Static member definition
Glib::RefPtr<Gtk::CssProvider> ThemeTab::cssProvider = Gtk::CssProvider::create();



static std::string getIceWMConfigDir() {
    const char* xdg = getenv("XDG_CONFIG_HOME");
    if (xdg && *xdg) {
        std::string path = std::string(xdg) + "/icewm";
        struct stat st;
        if (stat(path.c_str(), &st) == 0 && S_ISDIR(st.st_mode))
            return path;
    }
    const char* home = getenv("HOME");
    if (!home) return "";
    return std::string(home) + "/.icewm";
}

static std::string convertIceWMColorToCSS(const std::string& icewmColor) {
    std::string color = icewmColor;
    if (color.size() >= 2 && ((color.front() == '"' && color.back() == '"') || (color.front() == '\'' && color.back() == '\''))) {
        color = color.substr(1, color.size() - 2);
    }
    if (color.compare(0, 4, "rgb:") == 0) {
        std::string values = color.substr(4);
        for (char& c : values) {
            if (c == '/') c = ' ';
        }
        std::istringstream iss(values);
        int r, g, b;
        if (iss >> std::hex >> r >> g >> b) {
            char hex[8];
            snprintf(hex, sizeof(hex), "#%02X%02X%02X", r, g, b);
            return hex;
        }
    }
    if (color[0] == '#') return color;
    return color;
}

static std::string convertIceWMFontToCSS(const std::string& icewmFont) {
    std::string font = icewmFont;
    if (font.size() >= 2 && ((font.front() == '"' && font.back() == '"') || (font.front() == '\'' && font.back() == '\''))) {
        font = font.substr(1, font.size() - 2);
    }
    size_t nameEnd = font.find(':');
    if (nameEnd == std::string::npos) return font;
    std::string family = font.substr(0, nameEnd);
    std::string size = "10";
    std::string weight = "normal";
    std::string style = "normal";
    size_t sizePos = font.find("size=");
    if (sizePos != std::string::npos) {
        sizePos += 5;
        size_t sizeEnd = font.find_first_of(":,", sizePos);
        size = font.substr(sizePos, sizeEnd - sizePos);
    }
    if (font.find("bold") != std::string::npos) weight = "bold";
    if (font.find("italic") != std::string::npos) style = "italic";
    return style + " " + weight + " " + size + "pt \"" + family + "\"";
}

static void setGTKThemeFromIceWM(const std::string& configDir, const std::string& themeName) {
    std::string defaultThemePath = configDir + "/themes/" + themeName + "/default.theme";
    std::ifstream dt(defaultThemePath);
    if (!dt.is_open()) {
        defaultThemePath = "/usr/share/icewm/themes/" + themeName + "/default.theme";
        dt.open(defaultThemePath);
    }
    if (!dt.is_open()) return;
    std::string line;
    while (std::getline(dt, line)) {
        if (line.empty() || line[0] == '#') continue;
        size_t eqPos = line.find('=');
        if (eqPos == std::string::npos) continue;
        std::string key = line.substr(0, eqPos);
        if (key == "GtkTheme") {
            std::string gtkTheme = line.substr(eqPos + 1);
            while (!gtkTheme.empty() && (gtkTheme.back() == '\r' || gtkTheme.back() == ' ' || gtkTheme.back() == '\t'))
                gtkTheme.pop_back();
            while (!gtkTheme.empty() && (gtkTheme[0] == ' ' || gtkTheme[0] == '\t'))
                gtkTheme.erase(0, 1);
            if (gtkTheme.size() >= 2 && ((gtkTheme.front() == '"' && gtkTheme.back() == '"') || (gtkTheme.front() == '\'' && gtkTheme.back() == '\''))) {
                gtkTheme = gtkTheme.substr(1, gtkTheme.size() - 2);
            }
            auto settings = Gtk::Settings::get_default();
            if (settings) settings->property_gtk_theme_name() = gtkTheme;
            break;
        }
    }
}

void ThemeTab::applyIceWMThemeToUI(const std::string& configDir, const std::string& themeNameOverride)
{
    std::string themeName = themeNameOverride;
    if (themeName.empty()) {
        std::string themeFile = configDir + "/theme";
        std::ifstream tf(themeFile);
        std::string line;
        while (std::getline(tf, line)) {
            if (line.empty() || line[0] == '#') continue;
            size_t pos = line.find("Theme=");
            themeName = (pos != std::string::npos) ? line.substr(pos + 6) : line;
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
    }
    if (themeName.empty()) return;

    size_t slash = themeName.find("/default.theme");
    if (slash != std::string::npos) themeName = themeName.substr(0, slash);

    setGTKThemeFromIceWM(configDir, themeName);

    auto settings = Gtk::Settings::get_default();
    if (settings) {
        settings->property_gtk_theme_name() = "Raleigh";
        settings->property_gtk_application_prefer_dark_theme() = true;
    }

    // Load colors
    std::string defaultThemePath = configDir + "/themes/" + themeName + "/default.theme";
    std::ifstream dt(defaultThemePath);
    if (!dt.is_open()) {
        defaultThemePath = "/usr/share/icewm/themes/" + themeName + "/default.theme";
        dt.open(defaultThemePath);
    }
    if (!dt.is_open()) return;

    std::map<std::string, std::string> colors;
    std::string line;
    while (std::getline(dt, line)) {
        if (line.empty() || line[0] == '#') continue;
        size_t eq = line.find('=');
        if (eq == std::string::npos) continue;
        std::string key = line.substr(0, eq);
        std::string val = line.substr(eq + 1);
        while (!val.empty() && (val.back() == '\r' || isspace(val.back()))) val.pop_back();
        while (!val.empty() && isspace(val.front())) val.erase(0, 1);
        if (!val.empty() && (val.front() == '"' || val.front() == '\'')) val.erase(0, 1);
        if (!val.empty() && (val.back() == '"' || val.back() == '\'')) val.pop_back();
        colors[key] = val;
    }

    auto getColor = [&](const std::string& key, const std::string& fb) {
        return convertIceWMColorToCSS(colors.count(key) ? colors[key] : fb);
    };

    std::string bg       = getColor("ColorDialog", "#303744");
    std::string fg       = getColor("ColorNormalButtonText", "#ffffff");
    std::string activeBg = getColor("ColorActiveButton", "#2e454a");
    std::string activeFg = getColor("ColorActiveButtonText", "#000000");
    std::string border   = getColor("ColorNormalBorder", "#555555");
    std::string inputBg  = getColor("ColorInput", "#ffffff");
    std::string inputFg  = getColor("ColorInputText", "#000000");

    std::ostringstream css;
    css << "/* Targeted Fix */\n";

    css << "* { color: " << fg << " !important; }\n";
    css << "window, dialog { background-color: " << bg << " !important; }\n";

    // Strong frame rules
    css << "frame, .frame, GtkFrame { "
        << "background-color: " << bg << " !important; "
        << "border: 2px solid " << border << " !important; }\n";

    css << "frame > label { background-color: " << bg << " !important; color: " << fg << " !important; }\n";

    css << "box, GtkBox, scrolledwindow viewport { background-color: transparent !important; }\n";

    // Buttons & inputs
    css << "button { background-color: " << bg << " !important; border: 1px solid " << border << " !important; }\n";
    css << "button:hover, button:active { background-color: " << activeBg << " !important; color: " << activeFg << " !important; }\n";

    css << "entry, treeview, list { background-color: " << inputBg << " !important; color: " << inputFg << " !important; }\n";

    try {
        cssProvider->load_from_data(css.str());
        auto screen = Gdk::Screen::get_default();
        if (screen) {
            Gtk::StyleContext::remove_provider_for_screen(screen, cssProvider);
            Gtk::StyleContext::add_provider_for_screen(screen, cssProvider, 
                GTK_STYLE_PROVIDER_PRIORITY_USER + 200);
        }
    } catch (...) {}

    fprintf(stderr, "Theme applied (frame fix v2): %s\n", themeName.c_str());
}



// ============================================================================
// ThemeTab implementation with theme selector and notebook
// ============================================================================

ThemeTab::ThemeTab(const std::string& configDir) : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5), configDir(configDir), themeLoaded(false) {
    set_margin_left(10);
    set_margin_top(5);
    set_margin_bottom(5);

    // Theme selector bar at top
    Gtk::Box* selectorBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    selectorBox->set_margin_bottom(5);
    selectorBox->pack_start(*Gtk::manage(new Gtk::Label("Theme:")), false, false, 5);

    themeSelector = Gtk::manage(new Gtk::ComboBoxText());
    selectorBox->pack_start(*themeSelector, true, true, 5);

    Gtk::Button* refreshBtn = Gtk::manage(new Gtk::Button("Refresh"));
    Gtk::Button* applyBtn = Gtk::manage(new Gtk::Button("Apply"));
    Gtk::Button* saveBtn = Gtk::manage(new Gtk::Button("Save"));
    Gtk::Button* newBtn = Gtk::manage(new Gtk::Button("New Theme..."));
    Gtk::Button* resetBtn = Gtk::manage(new Gtk::Button("Reset"));
    selectorBox->pack_start(*refreshBtn, false, false, 5);
    selectorBox->pack_start(*applyBtn, false, false, 5);
    selectorBox->pack_start(*saveBtn, false, false, 5);
    selectorBox->pack_start(*newBtn, false, false, 5);
    selectorBox->pack_start(*resetBtn, false, false, 5);

    refreshBtn->signal_clicked().connect(sigc::mem_fun(*this, &ThemeTab::scanThemes));
    applyBtn->signal_clicked().connect(sigc::mem_fun(*this, &ThemeTab::applyTheme));
    saveBtn->signal_clicked().connect(sigc::mem_fun(*this, &ThemeTab::saveTheme));
    newBtn->signal_clicked().connect(sigc::mem_fun(*this, &ThemeTab::onNewTheme));
    resetBtn->signal_clicked().connect(sigc::mem_fun(*this, &ThemeTab::onResetTheme));
    themeSelector->signal_changed().connect(sigc::mem_fun(*this, &ThemeTab::onThemeSelected));

    pack_start(*selectorBox, false, false, 0);

    // Notebook with subtabs below
    notebook = new Gtk::Notebook();
    colorsTab = new ColorsTab(configDir);
    desktopTab = new DesktopTab(configDir);
    exploreTab = new ExploreTab(configDir);
    stylesTab = new StylesTab(configDir);
    toolsTab = new ToolsTab(configDir);
    fontsTab = new FontsTab(configDir);
    iconsTab = new IconsTab(configDir);

    notebook->append_page(*colorsTab, "Colors");
    notebook->append_page(*desktopTab, "Desktop");
    notebook->append_page(*exploreTab, "Explore");
    notebook->append_page(*stylesTab, "Styles");
    notebook->append_page(*toolsTab, "Tools");
    notebook->append_page(*fontsTab, "Fonts");
    notebook->append_page(*iconsTab, "Icons");

    pack_start(*notebook, Gtk::PACK_EXPAND_WIDGET);

    // Initialize
    scanThemes();
    loadCurrentTheme();
    // Apply the current IceWM theme to the UI (like FLTK's syncThemeToFLTK)
    applyIceWMThemeToUI(configDir);
}

ThemeTab::~ThemeTab() {
    delete notebook;
}

void ThemeTab::init_widgets() {
    // Widgets are now created in constructor
}

void ThemeTab::scanThemes() {
    themeSelector->remove_all();
    themeNames.clear();

    std::vector<std::string> themeDirs = {
        configDir + "/themes",
        "/usr/share/icewm/themes",
        "/usr/local/share/icewm/themes"
    };

    for (const auto& dirPath : themeDirs) {
        DIR* dir = opendir(dirPath.c_str());
        if (dir) {
            struct dirent* entry;
            while ((entry = readdir(dir)) != nullptr) {
                if (entry->d_name[0] == '.') continue;
                std::string name = entry->d_name;
                struct stat st;
                std::string full = dirPath + "/" + name;
                if (stat(full.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
                    if (std::find(themeNames.begin(), themeNames.end(), name) == themeNames.end()) {
                        themeNames.push_back(name);
                    }
                }
            }
            closedir(dir);
        }
    }

    std::sort(themeNames.begin(), themeNames.end());

    for (const auto& name : themeNames) {
        themeSelector->append(name);
    }

    if (!themeNames.empty()) {
        themeSelector->set_active(0);
    }
}

void ThemeTab::loadCurrentTheme() {
    themeLoaded = true; // prevent onThemeSelected during load
    std::string themeFile = configDir + "/theme";
    std::ifstream file(themeFile);
    if (!file.is_open()) {
        themeLoaded = false;
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::string themeName;

        size_t pos = line.find("Theme=");
        if (pos != std::string::npos) {
            themeName = line.substr(pos + 6);
            if (themeName.size() >= 2 && themeName.front() == '"' && themeName.back() == '"') {
                themeName = themeName.substr(1, themeName.size() - 2);
            }
        } else {
            themeName = line;
            while (!themeName.empty() && (themeName.back() == '\r' || themeName.back() == ' '))
                themeName.pop_back();
        }

        if (!themeName.empty()) {
            for (size_t i = 0; i < themeNames.size(); i++) {
                if (themeNames[i] == themeName) {
                    themeSelector->set_active(i);
                    // Apply the current theme to UI on load
                    applyIceWMThemeToUI(configDir, themeName);
                    themeLoaded = false;
                    return;
                }
            }
            themeNames.push_back(themeName);
            themeSelector->append(themeName);
            themeSelector->set_active(themeNames.size() - 1);
            applyIceWMThemeToUI(configDir, themeName);
            themeLoaded = false;
            return;
        }
    }
    themeLoaded = false;
}

void ThemeTab::applyTheme() {
    if (themeSelector->get_active_row_number() < 0) {
        Gtk::MessageDialog dlg("No theme selected.", false, Gtk::MESSAGE_WARNING);
        dlg.run();
        return;
    }

    std::string selectedTheme = themeSelector->get_active_text();

    // First apply the theme to the UI (icewm-control-panel-gtk skin)
    applyIceWMThemeToUI(configDir, selectedTheme);

    std::string themeFile = configDir + "/theme";
    std::ofstream file(themeFile);
    if (!file.is_open()) {
        Gtk::MessageDialog dlg("Failed to write theme file: " + themeFile, false, Gtk::MESSAGE_ERROR);
        dlg.run();
        return;
    }

    file << "Theme=\"" << selectedTheme << "\"" << std::endl;
    file.close();

    system("icesh restart &");

    Gtk::MessageDialog dlg("Theme '" + selectedTheme + "' applied! IceWM will restart.", false, Gtk::MESSAGE_INFO);
    dlg.run();
}

// Save the selected theme without restarting IceWM
void ThemeTab::saveTheme() {
    if (themeSelector->get_active_row_number() < 0) {
        Gtk::MessageDialog dlg("No theme selected.", false, Gtk::MESSAGE_WARNING);
        dlg.run();
        return;
    }

    std::string selectedTheme = themeSelector->get_active_text();

    // First apply the theme to the UI (icewm-control-panel-gtk skin)
    applyIceWMThemeToUI(configDir, selectedTheme);

    std::string themeFile = configDir + "/theme";
    std::ofstream file(themeFile);
    if (!file.is_open()) {
        Gtk::MessageDialog dlg("Failed to write theme file: " + themeFile, false, Gtk::MESSAGE_ERROR);
        dlg.run();
        return;
    }

    file << "Theme=\"" << selectedTheme << "\"" << std::endl;
    file.close();

    Gtk::MessageDialog dlg("Theme '" + selectedTheme + "' saved.", false, Gtk::MESSAGE_INFO);
    dlg.run();
}

void ThemeTab::onThemeSelected() {
    if (themeLoaded) return; // Prevent recursive updates during initialization
    std::string selectedTheme = themeSelector->get_active_text();
    if (!selectedTheme.empty()) {
        // Apply the theme to the UI immediately when selected
        applyIceWMThemeToUI(configDir, selectedTheme);
    }
}

// Load theme properties from preferences file into map
void ThemeTab::loadThemeProperties() {
    themeProperties.clear();
    std::ifstream file(configDir + "/preferences");
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        size_t eq = line.find('=');
        if (eq == std::string::npos) continue;
        std::string key = line.substr(0, eq);
        std::string val = line.substr(eq + 1);
        // Trim quotes
        if (!val.empty() && (val.front() == '"' || val.front() == '\'')) val.erase(0, 1);
        if (!val.empty() && (val.back() == '"' || val.back() == '\'')) val.pop_back();
        themeProperties[key] = val;
    }
}

// Save theme properties map back to preferences file
void ThemeTab::saveThemeProperties() {
    std::vector<std::string> lines;
    std::ifstream infile(configDir + "/preferences");
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            lines.push_back(line);
        }
        infile.close();
    }
    for (const auto& [key, val] : themeProperties) {
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
    }
    std::ofstream outfile(configDir + "/preferences");
    if (outfile.is_open()) {
        for (const auto& l : lines) outfile << l << "\n";
        outfile.close();
    }
}

void ThemeTab::updateEditorFromProperties() {
    // Propagate map values to sub-tabs if needed (simple stub)
    if (colorsTab) colorsTab->refresh();
    if (desktopTab) desktopTab->refresh();
    if (fontsTab) fontsTab->refresh();
    if (stylesTab) stylesTab->refresh();
}

void ThemeTab::updatePropertiesFromEditor() {
    // Collect values from sub-tabs back into map (simple stub)
    // Each sub-tab already writes directly to preferences, so we just reload.
    loadThemeProperties();
}

void ThemeTab::resetToDefaults() {
    // Clear map and reload defaults from theme files
    themeProperties.clear();
    // Remove user theme file to fallback to defaults
    std::string themeFile = configDir + "/theme";
    std::remove(themeFile.c_str());
    loadCurrentTheme();
}

// New Theme creation dialog
void ThemeTab::onNewTheme() {
    Gtk::Dialog dlg("Create New Theme", *dynamic_cast<Gtk::Window*>(get_toplevel()));
    dlg.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dlg.add_button("_Create", Gtk::RESPONSE_OK);
    auto* entry = Gtk::manage(new Gtk::Entry());
    entry->set_placeholder_text("New theme name");
    dlg.get_content_area()->pack_start(*entry);
    dlg.show_all();
    if (dlg.run() == Gtk::RESPONSE_OK) {
        std::string name = entry->get_text();
        if (!name.empty()) {
            std::string dir = configDir + "/themes/" + name;
            mkdir(dir.c_str(), 0755);
            themeSelector->append(name);
            themeSelector->set_active_text(name);
            // Save theme file
            std::ofstream tf(configDir + "/theme");
            tf << "Theme=\"" << name << "\"" << std::endl;
        }
    }
}

// Reset button handler
void ThemeTab::onResetTheme() {
    resetToDefaults();
    Gtk::MessageDialog dlg("Theme reset to defaults.", false, Gtk::MESSAGE_INFO);
    dlg.run();
}

void ThemeTab::refresh() {
    scanThemes();
    loadCurrentTheme();
    loadThemeProperties();
    updateEditorFromProperties();
    if (colorsTab) colorsTab->refresh();
    if (desktopTab) desktopTab->refresh();
    if (exploreTab) exploreTab->refresh();
    if (stylesTab) stylesTab->refresh();
    if (toolsTab) toolsTab->refresh();
    if (fontsTab) fontsTab->refresh();
    if (iconsTab) iconsTab->refresh();
}
