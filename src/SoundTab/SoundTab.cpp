#include "SoundTab.h"
#include <gtkmm/messagedialog.h>
#include <fstream>
#include <sstream>
#include <map>

SoundTab::SoundTab(const std::string& configDir) : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5), configDir(configDir) {
    set_margin_left(10);
    set_margin_top(10);
    set_margin_right(10);
    
    auto* title = Gtk::manage(new Gtk::Label());
    title->set_markup("<b>Sound Configuration</b>");
    title->set_halign(Gtk::ALIGN_START);
    pack_start(*title, Gtk::PACK_SHRINK);
    
    auto* subtitle = Gtk::manage(new Gtk::Label("IceWM sound events and player settings (~/.icewm/sounds)"));
    subtitle->set_halign(Gtk::ALIGN_START);
    pack_start(*subtitle, Gtk::PACK_SHRINK);
    
    auto* notebook = Gtk::manage(new Gtk::Notebook());
    eventsTab = Gtk::manage(new SoundEventsTab());
    notebook->append_page(*eventsTab, "Events");
    settingsTab = Gtk::manage(new SoundSettingsTab());
    notebook->append_page(*settingsTab, "Settings");
    pack_start(*notebook, Gtk::PACK_EXPAND_WIDGET);
    
    auto* btnBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    saveButton = Gtk::manage(new Gtk::Button("_Save", true));
    loadButton = Gtk::manage(new Gtk::Button("_Load", true));
    btnBox->pack_start(*saveButton, Gtk::PACK_SHRINK);
    btnBox->pack_start(*loadButton, Gtk::PACK_SHRINK);
    pack_start(*btnBox, Gtk::PACK_SHRINK);
    
    saveButton->signal_clicked().connect(sigc::mem_fun(*this, &SoundTab::saveSounds));
    loadButton->signal_clicked().connect(sigc::mem_fun(*this, &SoundTab::loadSounds));
    
    loadSounds();
}

void SoundTab::loadSounds() {
    std::string filename = configDir + "/sounds";
    std::ifstream file(filename);
    if (!file.is_open()) return;
    std::map<std::string, std::string> settings;
    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && line.back() == '\r') line.pop_back();
        if (line.empty() || line[0] == '#') continue;
        size_t eq = line.find('=');
        if (eq == std::string::npos) continue;
        std::string key = line.substr(0, eq), value = line.substr(eq + 1);
        if (value.length() >= 2 && value[0] == '"' && value.back() == '"') value = value.substr(1, value.length() - 2);
        settings[key] = value;
    }
    auto it = settings.find("EnableSounds");
    if (it != settings.end()) settingsTab->setEnableSounds(it->second == "1");
    it = settings.find("SoundStartup"); if (it != settings.end()) eventsTab->setStartupSound(it->second);
    it = settings.find("SoundShutdown"); if (it != settings.end()) eventsTab->setShutdownSound(it->second);
    it = settings.find("SoundWindowOpen"); if (it != settings.end()) eventsTab->setWindowOpenSound(it->second);
    it = settings.find("SoundWindowClose"); if (it != settings.end()) eventsTab->setWindowCloseSound(it->second);
    it = settings.find("SoundWorkspaceChange"); if (it != settings.end()) eventsTab->setWorkspaceChangeSound(it->second);
    it = settings.find("SoundAlert"); if (it != settings.end()) eventsTab->setAlertSound(it->second);
    it = settings.find("SoundPlayer"); if (it != settings.end()) settingsTab->setPlayerCmd(it->second);
    it = settings.find("SoundInterface"); if (it != settings.end()) {
        if (it->second == "AO") settingsTab->setInterface(0);
        else if (it->second == "ALSA") settingsTab->setInterface(1);
        else if (it->second == "OSS") settingsTab->setInterface(2);
        else settingsTab->setInterface(0);
    }
    it = settings.find("SoundOssDevice"); if (it != settings.end()) settingsTab->setOssDevice(it->second);
    it = settings.find("SoundAlsaDevice"); if (it != settings.end()) settingsTab->setAlsaDevice(it->second);
    it = settings.find("SoundSnooze"); 
    if (it != settings.end() && !it->second.empty()) {
        try {
            settingsTab->setSnooze(std::stoi(it->second));
        } catch (...) { }
    }
    it = settings.find("SoundVerbose"); if (it != settings.end()) settingsTab->setVerbose(it->second == "1");
}

void SoundTab::saveSounds() {
    std::string filename = configDir + "/sounds";
    std::ofstream file(filename);
    if (!file.is_open()) {
        Gtk::MessageDialog dlg("Failed to save sounds file!", false, Gtk::MESSAGE_ERROR);
        dlg.run(); return;
    }
    file << "# IceWM Sound Configuration\n\n";
    file << "EnableSounds=" << (settingsTab->getEnableSounds() ? "1" : "0") << "\n";
    file << "\n# Sound files\n";
    if (!eventsTab->getStartupSound().empty()) file << "SoundStartup=\"" << eventsTab->getStartupSound() << "\"\n";
    if (!eventsTab->getShutdownSound().empty()) file << "SoundShutdown=\"" << eventsTab->getShutdownSound() << "\"\n";
    if (!eventsTab->getWindowOpenSound().empty()) file << "SoundWindowOpen=\"" << eventsTab->getWindowOpenSound() << "\"\n";
    if (!eventsTab->getWindowCloseSound().empty()) file << "SoundWindowClose=\"" << eventsTab->getWindowCloseSound() << "\"\n";
    if (!eventsTab->getWorkspaceChangeSound().empty()) file << "SoundWorkspaceChange=\"" << eventsTab->getWorkspaceChangeSound() << "\"\n";
    if (!eventsTab->getAlertSound().empty()) file << "SoundAlert=\"" << eventsTab->getAlertSound() << "\"\n";
    file << "\n# Sound player\n";
    if (!settingsTab->getPlayerCmd().empty()) file << "SoundPlayer=\"" << settingsTab->getPlayerCmd() << "\"\n";
    file << "\n# Sound interface\n";
    const char* ifaces[] = {"AO", "ALSA", "OSS"};
    file << "SoundInterface=\"" << ifaces[settingsTab->getInterface()] << "\"\n";
    if (!settingsTab->getOssDevice().empty()) file << "SoundOssDevice=\"" << settingsTab->getOssDevice() << "\"\n";
    if (!settingsTab->getAlsaDevice().empty()) file << "SoundAlsaDevice=\"" << settingsTab->getAlsaDevice() << "\"\n";
    file << "SoundSnooze=" << settingsTab->getSnooze() << "\n";
    file << "SoundVerbose=" << (settingsTab->getVerbose() ? "1" : "0") << "\n";
    file.close();
    Gtk::MessageDialog dlg("Sound configuration saved!", false, Gtk::MESSAGE_INFO); dlg.run();
}

void SoundTab::refresh() { loadSounds(); }
