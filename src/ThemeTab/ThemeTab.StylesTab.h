#ifndef THEMETAB_STYLESTAB_H
#define THEMETAB_STYLESTAB_H

#include <gtkmm.h>

class StylesTab : public Gtk::Box {
private:
    std::string configDir;
    
    Gtk::ComboBoxText* lookCombo;
    Gtk::SpinButton* titleHeightSpin;
    Gtk::Entry* titleButtonsLeftEntry;
    Gtk::Entry* titleButtonsRightEntry;
    Gtk::Entry* titleFontEntry;
    Gtk::SpinButton* titleFontSizeSpin;
    Gtk::Entry* menuFontEntry;
    Gtk::SpinButton* menuFontSizeSpin;
    Gtk::Entry* statusFontEntry;
    Gtk::Entry* quickSwitchFontEntry;
    
    void loadStyles();
    void saveStyles();
    
public:
    StylesTab(const std::string& configDir);
    void refresh();
};

#endif
