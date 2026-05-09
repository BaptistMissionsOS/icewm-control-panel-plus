#ifndef SOUNDTAB_H
#define SOUNDTAB_H

#include <gtkmm.h>
#include <string>

#include "SoundTab.EventsTab.h"
#include "SoundTab.SettingsTab.h"

class SoundTab : public Gtk::Box {
private:
    std::string configDir;
    
    SoundEventsTab *eventsTab;
    SoundSettingsTab *settingsTab;
    
    Gtk::Button *saveButton;
    Gtk::Button *loadButton;
    
    void loadSounds();
    void saveSounds();
    
public:
    SoundTab(const std::string& configDir);
    void refresh();
};

#endif
