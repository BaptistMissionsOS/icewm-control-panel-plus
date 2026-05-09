#ifndef PREFERENCESTAB_H
#define PREFERENCESTAB_H

#include <gtkmm.h>
#include <string>
#include <map>

// Forward declarations for internal tabs
class PrefAppearanceTab;
class PrefColorsTab;
class PrefDesktopTab;
class PrefFontsTab;
class PrefKeysTab;
class PrefTaskBarTab;
class PrefWindowsTab;

class PreferencesTab : public Gtk::Box {
private:
    std::string configDir;
    std::map<std::string, std::string> preferences;
    
    // Tab instances with unique names
    PrefAppearanceTab *appearanceTab;
    PrefColorsTab *colorsTab;
    PrefDesktopTab *desktopTab;
    PrefFontsTab *fontsTab;
    PrefKeysTab *keysTab;
    PrefTaskBarTab *taskBarTab;
    PrefWindowsTab *windowsTab;
    
    Gtk::Button *saveButton;
    Gtk::Button *loadButton;
    Gtk::Button *resetButton;
    Gtk::Button *refreshButton;
    Gtk::Button *applyButton;
    
    void loadPreferencesFile();
    void savePreferencesFile();
    void updateWidgets();
    
    // Callbacks
    void on_save_clicked();
    void on_load_clicked();
    void on_reset_clicked();
    void on_refresh_clicked();
    void on_apply_clicked();
    
public:
    PreferencesTab(const std::string& configDir);
    void refresh();
};

#endif
