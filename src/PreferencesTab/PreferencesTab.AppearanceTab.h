#ifndef PREFERENCESTAB_APPEARANCETAB_H
#define PREFERENCESTAB_APPEARANCETAB_H

#include <gtkmm.h>
#include <string>
#include <map>

class PrefAppearanceTab : public Gtk::Box {
public:
    PrefAppearanceTab();

    // Preference management
    void loadPreferences(const std::map<std::string, std::string>& preferences);
    void savePreferences(std::map<std::string, std::string>& preferences);
    void resetWidgets();

private:
    // Appearance widgets
    Gtk::Entry* fontNameInput;
    Gtk::Entry* fontNameXft;
    Gtk::SpinButton* titleHeightSpinner;
    Gtk::ComboBoxText* buttonLayoutChoice;
    
    // Helper functions
    void createFontControls();
    void addFontControl(Gtk::Widget*& input1, Gtk::Widget*& input2, const char* key1, const char* key2);
    void addCategory(const char* title);
};

#endif