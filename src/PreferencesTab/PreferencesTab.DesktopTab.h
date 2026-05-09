#ifndef PREFERENCESTAB_DESKTOPTAB_H
#define PREFERENCESTAB_DESKTOPTAB_H

#include <gtkmm.h>
#include <string>
#include <map>

class PrefDesktopTab : public Gtk::Box {
public:
    PrefDesktopTab(const std::string& configDir);

    // Methods for loading/saving preferences
    void loadPreferences(const std::map<std::string, std::string>& preferences);
    void savePreferences(std::map<std::string, std::string>& preferences);
    void resetWidgets();

private:
    std::string configDir;
    
    // Desktop widgets
    Gtk::Entry* workspaceNameInput;
    Gtk::SpinButton* workspaceCountSpinner;
    Gtk::CheckButton* showTaskbarCheck;
    Gtk::CheckButton* showClockCheck;
    Gtk::CheckButton* showPagerCheck;
    Gtk::Button* desktopBrowseButton;
    Gtk::ComboBoxText* desktopScalingChoice;
    Gtk::ComboBoxText* desktopWorkspaceChoice;
    Gtk::ColorButton* desktopColorButton;
    Gtk::Label* desktopPreviewLabel;
    std::string desktopBackgroundColor;

    // Helper functions
    void browseDesktopBackground();
    void pickDesktopColor();
    void createDesktopControls();
};

#endif