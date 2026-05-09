#ifndef PREFERENCESTAB_WINDOWSTAB_H
#define PREFERENCESTAB_WINDOWSTAB_H

#include <gtkmm.h>
#include <string>
#include <map>

class PrefWindowsTab : public Gtk::Box {
public:
    PrefWindowsTab(const std::string& configDir);

    // Preference management
    void loadPreferences(const std::map<std::string, std::string>& preferences);
    void savePreferences(std::map<std::string, std::string>& preferences);
    void resetWidgets();

private:
    std::string configDir;
    
    // Windows widgets
    Gtk::ComboBoxText* focusModelChoice;
    Gtk::CheckButton* clickToFocusCheck;
    Gtk::CheckButton* raiseOnClickCheck;
    Gtk::SpinButton* edgeResistanceSpinner;

    // Helper functions
    void createWindowControls();
    void addComboBox(Gtk::Widget*& combo, const char* key);
    void addCheckButton(Gtk::Widget*& btn, const char* key);
    void addSpinButton(Gtk::Widget*& spin, const char* key, double min, double max, double step);
};

#endif