#ifndef PREFOVERRIDE_THEMETAB_H
#define PREFOVERRIDE_THEMETAB_H

#include <gtkmm.h>
#include <string>

class PrefThemeTab : public Gtk::Box {
private:
    Gtk::Entry *titleFontInput;
    Gtk::Entry *menuFontInput;
    Gtk::SpinButton *titleHeightSpinner;
    Gtk::SpinButton *borderWidthSpinner;

public:
    PrefThemeTab();
    
    // Getters
    std::string getTitleFont() const { return titleFontInput->get_text(); }
    std::string getMenuFont() const { return menuFontInput->get_text(); }
    int getTitleHeight() const { return (int)titleHeightSpinner->get_value(); }
    int getBorderWidth() const { return (int)borderWidthSpinner->get_value(); }
    
    // Setters
    void setTitleFont(const std::string& value) { titleFontInput->set_text(value); }
    void setMenuFont(const std::string& value) { menuFontInput->set_text(value); }
    void setTitleHeight(int value) { titleHeightSpinner->set_value(value); }
    void setBorderWidth(int value) { borderWidthSpinner->set_value(value); }
    
    // Reset to defaults
    void setDefaults();
};

#endif
