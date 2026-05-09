#ifndef PREFERENCES_FONTS_TAB_H
#define PREFERENCES_FONTS_TAB_H

#include <gtkmm.h>
#include <string>
#include <map>

class PrefFontsTab : public Gtk::Box {
public:
    PrefFontsTab();

    // Preference management
    void loadPreferences(const std::map<std::string, std::string>& prefs);
    void savePreferences(std::map<std::string, std::string>& prefs);
    void resetWidgets();

private:
    std::string configDir;
    
    // Map of property name to font button
    std::map<std::string, Gtk::FontButton*> fontButtons;

    // Helper functions
    void createFontRow(Gtk::Box* container, const std::string& label, 
                       const std::string& property, const std::string& defaultFont);
    void onFontChanged(const std::string& property, const Glib::ustring& font);
    void loadPreferences();  // Load from file
};

#endif