#ifndef SHUTDOWNTAB_H
#define SHUTDOWNTAB_H

#include <gtkmm.h>
#include <string>

#include "ShutdownTab.OptionsTab.h"
#include "ShutdownTab.CommandsTab.h"

class ShutdownTab : public Gtk::Box {
private:
    std::string configDir;
    
    ShutdownOptionsTab *optionsTab;
    ShutdownCommandsTab *commandsTab;
    
    Gtk::Button *saveButton;
    Gtk::Button *loadButton;
    Gtk::Button *resetButton;
    
    void loadSettings();
    void saveSettings();
    void setDefaults();
    
public:
    ShutdownTab(const std::string& configDir);
    void refresh();
};

#endif
