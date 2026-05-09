#ifndef ENVTAB_SESSIONTAB_H
#define ENVTAB_SESSIONTAB_H

#include <gtkmm.h>

class EnvSessionTab : public Gtk::Box {
private:
    Gtk::Entry *displayEntry;
    Gtk::Entry *langEntry;
    Gtk::Entry *pathEntry;

public:
    EnvSessionTab();
    
    Glib::ustring getDisplay() const { return displayEntry->get_text(); }
    Glib::ustring getLang() const { return langEntry->get_text(); }
    Glib::ustring getPath() const { return pathEntry->get_text(); }
    
    void setDisplay(const Glib::ustring& v) { displayEntry->set_text(v); }
    void setLang(const Glib::ustring& v) { langEntry->set_text(v); }
    void setPath(const Glib::ustring& v) { pathEntry->set_text(v); }
};

#endif