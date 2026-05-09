#ifndef THEMETAB_COLORSTAB_H
#define THEMETAB_COLORSTAB_H

#include <gtkmm.h>

class ColorsTab : public Gtk::Box {
private:
    std::string configDir;
    
    // Color buttons map: property name -> ColorButton
    std::map<std::string, Gtk::ColorButton*> colorButtons;
    Gtk::ScrolledWindow* scrolled;
    Gtk::Frame *winFrame, *titleFrame, *btnFrame, *taskFrame, *menuFrame, 
               *wsFrame, *inputFrame, *clockFrame, *scrollFrame;
    Gtk::Box* container;

    void loadColors();
    void saveColors();
    void onColorChanged(const std::string& property, const Gdk::RGBA& color);
    void createColorRow(Gtk::Box* container, const std::string& label, const std::string& property, const Gdk::RGBA& defaultColor);
    
public:
    ColorsTab(const std::string& configDir);
    void refresh();
};

#endif
