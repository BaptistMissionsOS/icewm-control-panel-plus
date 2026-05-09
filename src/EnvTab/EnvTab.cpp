#include "EnvTab.h"
#include <gtkmm/messagedialog.h>
#include <fstream>
#include <sstream>
#include <map>

EnvTab::EnvTab(const std::string& configDir) : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5), configDir(configDir) {
    set_margin_left(10);
    set_margin_top(10);
    set_margin_right(10);
    
    // Title
    auto* title = Gtk::manage(new Gtk::Label());
    title->set_markup("<b>Environment Variables</b>");
    title->set_halign(Gtk::ALIGN_START);
    pack_start(*title, Gtk::PACK_SHRINK);
    
    auto* subtitle = Gtk::manage(new Gtk::Label("Settings are sourced by icewm-session on startup (~/.icewm/env)"));
    subtitle->set_halign(Gtk::ALIGN_START);
    subtitle->get_style_context()->add_class("dim-label");
    pack_start(*subtitle, Gtk::PACK_SHRINK);
    
    // Notebook for subtabs
    auto* notebook = Gtk::manage(new Gtk::Notebook());
    
    sessionTab = Gtk::manage(new EnvSessionTab());
    notebook->append_page(*sessionTab, "Session");
    
    appearanceTab = Gtk::manage(new EnvAppearanceTab());
    notebook->append_page(*appearanceTab, "Appearance");
    
    inputMethodTab = Gtk::manage(new EnvInputMethodTab());
    notebook->append_page(*inputMethodTab, "Input Method");
    
    programsTab = Gtk::manage(new EnvProgramsTab());
    notebook->append_page(*programsTab, "Programs");
    
    customTab = Gtk::manage(new EnvCustomTab());
    notebook->append_page(*customTab, "Custom");
    
    pack_start(*notebook, Gtk::PACK_EXPAND_WIDGET);
    
    // Buttons
    auto* btnBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    saveButton = Gtk::manage(new Gtk::Button("_Save", true));
    loadButton = Gtk::manage(new Gtk::Button("_Load", true));
    btnBox->pack_start(*saveButton, Gtk::PACK_SHRINK);
    btnBox->pack_start(*loadButton, Gtk::PACK_SHRINK);
    pack_start(*btnBox, Gtk::PACK_SHRINK);
    
    saveButton->signal_clicked().connect(sigc::mem_fun(*this, &EnvTab::saveEnv));
    loadButton->signal_clicked().connect(sigc::mem_fun(*this, &EnvTab::loadEnv));
    
    loadEnv();
}

void EnvTab::loadEnv() {
    std::string filename = configDir + "/env";
    std::ifstream file(filename);
    if (!file.is_open()) return;
    
    std::map<std::string, std::string> vars;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty() || line[0] == '#') continue;
        size_t eq = line.find('=');
        if (eq == std::string::npos) continue;
        std::string key = line.substr(0, eq);
        std::string value = line.substr(eq + 1);
        if (value.length() >= 2 && value[0] == '"' && value.back() == '"')
            value = value.substr(1, value.length() - 2);
        vars[key] = value;
    }
    file.close();
    
    auto it = vars.find("DISPLAY");
    if (it != vars.end()) sessionTab->setDisplay(it->second);
    it = vars.find("LANG");
    if (it != vars.end()) sessionTab->setLang(it->second);
    it = vars.find("PATH");
    if (it != vars.end()) sessionTab->setPath(it->second);
    it = vars.find("GTK_THEME");
    if (it != vars.end()) appearanceTab->setGtkTheme(it->second);
    it = vars.find("QT_STYLE_OVERRIDE");
    if (it != vars.end()) appearanceTab->setQtStyle(it->second);
    it = vars.find("QT_QPA_PLATFORMTHEME");
    if (it != vars.end()) appearanceTab->setQtQpaPlatformTheme(it->second);
    it = vars.find("XIM");
    if (it != vars.end()) inputMethodTab->setXim(it->second);
    it = vars.find("XIM_PROGRAM");
    if (it != vars.end()) inputMethodTab->setXimProgram(it->second);
    it = vars.find("TERM");
    if (it != vars.end()) programsTab->setTerm(it->second);
    it = vars.find("BROWSER");
    if (it != vars.end()) programsTab->setBrowser(it->second);
    it = vars.find("EDITOR");
    if (it != vars.end()) programsTab->setEditor(it->second);
}

void EnvTab::saveEnv() {
    std::string filename = configDir + "/env";
    std::ofstream file(filename);
    if (!file.is_open()) {
        Gtk::MessageDialog dlg("Failed to save env file!", false, Gtk::MESSAGE_ERROR);
        dlg.run(); return;
    }
    
    file << "# IceWM Environment Variables\n";
    file << "# These are sourced by icewm-session on startup\n\n";
    
    if (!sessionTab->getDisplay().empty()) file << "DISPLAY=\"" << sessionTab->getDisplay() << "\"\n";
    if (!sessionTab->getLang().empty()) file << "LANG=\"" << sessionTab->getLang() << "\"\n";
    if (!sessionTab->getPath().empty()) file << "PATH=\"" << sessionTab->getPath() << "\"\n";
    if (!appearanceTab->getGtkTheme().empty()) file << "GTK_THEME=\"" << appearanceTab->getGtkTheme() << "\"\n";
    if (!appearanceTab->getQtStyle().empty()) file << "QT_STYLE_OVERRIDE=\"" << appearanceTab->getQtStyle() << "\"\n";
    if (!appearanceTab->getQtQpaPlatformTheme().empty()) file << "QT_QPA_PLATFORMTHEME=\"" << appearanceTab->getQtQpaPlatformTheme() << "\"\n";
    if (!inputMethodTab->getXim().empty()) file << "XIM=\"" << inputMethodTab->getXim() << "\"\n";
    if (!inputMethodTab->getXimProgram().empty()) file << "XIM_PROGRAM=\"" << inputMethodTab->getXimProgram() << "\"\n";
    if (!programsTab->getTerm().empty()) file << "TERM=\"" << programsTab->getTerm() << "\"\n";
    if (!programsTab->getBrowser().empty()) file << "BROWSER=\"" << programsTab->getBrowser() << "\"\n";
    if (!programsTab->getEditor().empty()) file << "EDITOR=\"" << programsTab->getEditor() << "\"\n";
    
    if (!customTab->getCustom1().empty() && customTab->getCustom1().find('=') != std::string::npos)
        file << "\n# Custom variable\n" << customTab->getCustom1() << "\n";
    if (!customTab->getCustom2().empty() && customTab->getCustom2().find('=') != std::string::npos)
        file << "\n# Custom variable\n" << customTab->getCustom2() << "\n";
    
    file.close();
    Gtk::MessageDialog dlg("Environment configuration saved!", false, Gtk::MESSAGE_INFO);
    dlg.run();
}

void EnvTab::refresh() { loadEnv(); }
