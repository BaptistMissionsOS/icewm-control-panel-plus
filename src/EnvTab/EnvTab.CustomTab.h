#ifndef ENVTAB_CUSTOMTAB_H
#define ENVTAB_CUSTOMTAB_H

#include <gtkmm.h>

class EnvCustomTab : public Gtk::Box {
private:
    Gtk::Entry *custom1Entry;
    Gtk::Entry *custom2Entry;

public:
    EnvCustomTab();
    
    Glib::ustring getCustom1() const { return custom1Entry->get_text(); }
    Glib::ustring getCustom2() const { return custom2Entry->get_text(); }
    
    void setCustom1(const Glib::ustring& v) { custom1Entry->set_text(v); }
    void setCustom2(const Glib::ustring& v) { custom2Entry->set_text(v); }
};

#endif