#ifndef THEMETAB_DESKTOPTAB_H
#define THEMETAB_DESKTOPTAB_H

#include <gtkmm.h>

class DesktopTab : public Gtk::Box {
private:
    std::string configDir;
    
    Gtk::Entry* backgroundEntry;
    Gtk::ComboBoxText* scalingCombo;
    Gtk::ComboBoxText* workspaceCombo;
    Gtk::ColorButton* colorButton;
    Gtk::Image* previewImage;
    Gtk::Label* previewLabel;
    
    void browseBackground();
    void pickColor();
    void updatePreview();
    void loadSettings();
    void saveSettings();
    
public:
    DesktopTab(const std::string& configDir);
    void refresh();
};

#endif
