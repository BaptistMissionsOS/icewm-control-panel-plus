#ifndef ENVTAB_H
#define ENVTAB_H

#include <gtkmm.h>
#include <string>

#include "EnvTab.SessionTab.h"
#include "EnvTab.AppearanceTab.h"
#include "EnvTab.SessionTab.InputMethodTab.h"
#include "EnvTab.ProgramsTab.h"
#include "EnvTab.CustomTab.h"

class EnvTab : public Gtk::Box {
private:
    std::string configDir;
    
    EnvSessionTab *sessionTab;
    EnvAppearanceTab *appearanceTab;
    EnvInputMethodTab *inputMethodTab;
    EnvProgramsTab *programsTab;
    EnvCustomTab *customTab;
    
    Gtk::Button *saveButton;
    Gtk::Button *loadButton;
    
    void loadEnv();
    void saveEnv();
    
public:
    EnvTab(const std::string& configDir);
    void refresh();
};

#endif
