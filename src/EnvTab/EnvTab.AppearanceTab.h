#ifndef ENVTAB_APPEARANCETAB_H
#define ENVTAB_APPEARANCETAB_H

#include <gtkmm.h>

class EnvAppearanceTab : public Gtk::Box {
private:
    Gtk::Entry *gtkThemeEntry;
    Gtk::Entry *qtStyleEntry;
    Gtk::Entry *qtQpaPlatformThemeEntry;

public:
    EnvAppearanceTab();
    
    Glib::ustring getGtkTheme() const { return gtkThemeEntry->get_text(); }
    Glib::ustring getQtStyle() const { return qtStyleEntry->get_text(); }
    Glib::ustring getQtQpaPlatformTheme() const { return qtQpaPlatformThemeEntry->get_text(); }
    
    void setGtkTheme(const Glib::ustring& v) { gtkThemeEntry->set_text(v); }
    void setQtStyle(const Glib::ustring& v) { qtStyleEntry->set_text(v); }
    void setQtQpaPlatformTheme(const Glib::ustring& v) { qtQpaPlatformThemeEntry->set_text(v); }
};

#endif