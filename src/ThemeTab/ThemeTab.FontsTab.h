#ifndef THEMETAB_FONTSTAB_H
#define THEMETAB_FONTSTAB_H

#include <gtkmm.h>

class FontsTab : public Gtk::Box {
private:
    std::string configDir;
    
    // Font buttons map: property name -> FontButton
    std::map<std::string, Gtk::FontButton*> fontButtons;
    
    void loadFonts();
    void saveFonts();
    void onFontChanged(const std::string& property, const Glib::ustring& font);
    void createFontRow(Gtk::Box* container, const std::string& label, const std::string& property, const std::string& defaultFont);
    
public:
    FontsTab(const std::string& configDir);
    void refresh();
};

#endif
