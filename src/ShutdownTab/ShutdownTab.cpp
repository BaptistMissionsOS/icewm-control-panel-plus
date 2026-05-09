#include "ShutdownTab.h"
#include <gtkmm/messagedialog.h>
#include <fstream>
#include <sstream>

ShutdownTab::ShutdownTab(const std::string& configDir) : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5), configDir(configDir) {
    set_margin_left(10);
    set_margin_top(10);
    set_margin_right(10);
    
    auto* title = Gtk::manage(new Gtk::Label());
    title->set_markup("<b>Shutdown Configuration</b>");
    title->set_halign(Gtk::ALIGN_START);
    pack_start(*title, Gtk::PACK_SHRINK);
    
    auto* subtitle = Gtk::manage(new Gtk::Label("Shutdown dialog settings (~/.icewm/preferences)"));
    subtitle->set_halign(Gtk::ALIGN_START);
    pack_start(*subtitle, Gtk::PACK_SHRINK);
    
    auto* notebook = Gtk::manage(new Gtk::Notebook());
    optionsTab = Gtk::manage(new ShutdownOptionsTab());
    notebook->append_page(*optionsTab, "Options");
    commandsTab = Gtk::manage(new ShutdownCommandsTab());
    notebook->append_page(*commandsTab, "Commands");
    pack_start(*notebook, Gtk::PACK_EXPAND_WIDGET);
    
    auto* btnBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    saveButton = Gtk::manage(new Gtk::Button("_Save", true));
    loadButton = Gtk::manage(new Gtk::Button("_Load", true));
    resetButton = Gtk::manage(new Gtk::Button("_Reset", true));
    btnBox->pack_start(*saveButton, Gtk::PACK_SHRINK);
    btnBox->pack_start(*loadButton, Gtk::PACK_SHRINK);
    btnBox->pack_start(*resetButton, Gtk::PACK_SHRINK);
    pack_start(*btnBox, Gtk::PACK_SHRINK);
    
    saveButton->signal_clicked().connect(sigc::mem_fun(*this, &ShutdownTab::saveSettings));
    loadButton->signal_clicked().connect(sigc::mem_fun(*this, &ShutdownTab::loadSettings));
    resetButton->signal_clicked().connect([this]() {
        Gtk::MessageDialog dlg("Reset to default values?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
        if (dlg.run() == Gtk::RESPONSE_YES) setDefaults();
    });
    
    loadSettings();
}

void ShutdownTab::loadSettings() {
    std::string filename = configDir + "/preferences";
    std::ifstream file(filename);
    if (!file.is_open()) return;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.find("ConfirmShutdown=") == 0) optionsTab->setConfirmShutdown(line.find("=1") != std::string::npos);
        else if (line.find("ShowLogout=") == 0) optionsTab->setShowLogout(line.find("=1") != std::string::npos);
        else if (line.find("ShowReboot=") == 0) optionsTab->setShowReboot(line.find("=1") != std::string::npos);
        else if (line.find("ShowShutdown=") == 0) optionsTab->setShowShutdown(line.find("=1") != std::string::npos);
        else if (line.find("ShowSuspend=") == 0) optionsTab->setShowSuspend(line.find("=1") != std::string::npos);
        else if (line.find("ShowHibernate=") == 0) optionsTab->setShowHibernate(line.find("=1") != std::string::npos);
        else {
            size_t eq = line.find('=');
            if (eq == std::string::npos) continue;
            std::string key = line.substr(0, eq);
            std::string val = line.substr(eq + 1);
            if (val.length() >= 2 && val[0] == '"' && val.back() == '"') val = val.substr(1, val.length() - 2);
            if (key == "ShutdownCommand") commandsTab->setShutdownCmd(val);
            else if (key == "RebootCommand") commandsTab->setRebootCmd(val);
            else if (key == "LockCommand") commandsTab->setLockCmd(val);
            else if (key == "ClockCommand") commandsTab->setClockCmd(val);
            else if (key == "MailCommand") commandsTab->setMailCmd(val);
            else if (key == "RunCommand") commandsTab->setRunCmd(val);
        }
    }
}

void ShutdownTab::saveSettings() {
    std::string filename = configDir + "/preferences";
    std::ofstream file(filename, std::ios::app);
    if (!file.is_open()) {
        Gtk::MessageDialog dlg("Failed to save settings!", false, Gtk::MESSAGE_ERROR);
        dlg.run(); return;
    }
    file << "\n# Shutdown settings\n";
    file << "ConfirmShutdown=" << (optionsTab->getConfirmShutdown() ? "1" : "0") << "\n";
    file << "ShowLogout=" << (optionsTab->getShowLogout() ? "1" : "0") << "\n";
    file << "ShowReboot=" << (optionsTab->getShowReboot() ? "1" : "0") << "\n";
    file << "ShowShutdown=" << (optionsTab->getShowShutdown() ? "1" : "0") << "\n";
    file << "ShowSuspend=" << (optionsTab->getShowSuspend() ? "1" : "0") << "\n";
    file << "ShowHibernate=" << (optionsTab->getShowHibernate() ? "1" : "0") << "\n";
    file << "ShutdownCommand=\"" << commandsTab->getShutdownCmd() << "\"\n";
    file << "RebootCommand=\"" << commandsTab->getRebootCmd() << "\"\n";
    file << "LockCommand=\"" << commandsTab->getLockCmd() << "\"\n";
    file << "ClockCommand=\"" << commandsTab->getClockCmd() << "\"\n";
    file << "MailCommand=\"" << commandsTab->getMailCmd() << "\"\n";
    file << "RunCommand=\"" << commandsTab->getRunCmd() << "\"\n";
    file.close();
    Gtk::MessageDialog dlg("Settings saved!", false, Gtk::MESSAGE_INFO); dlg.run();
}

void ShutdownTab::setDefaults() { optionsTab->setDefaults(); commandsTab->setDefaults(); }
void ShutdownTab::refresh() { loadSettings(); }
