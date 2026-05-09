#ifndef THEMETAB_ICONSTAB_H
#define THEMETAB_ICONSTAB_H

#include <gtkmm.h>

class IconsTab : public Gtk::Box {
private:
    std::string configDir;
    
    // Icon file entries map: property name -> Entry
    std::map<std::string, Gtk::Entry*> iconEntries;
    
    void loadIcons();
    void saveIcons();
    void onIconChanged(const std::string& property, const Glib::ustring& path);
    void createIconRow(Gtk::Box* container, const std::string& label, const std::string& property, const std::string& defaultPath);
    
public:
    IconsTab(const std::string& configDir);
    void refresh();
};

#endif