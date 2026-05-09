#ifndef ENVTAB_INPUTMETHODTAB_H
#define ENVTAB_INPUTMETHODTAB_H

#include <gtkmm.h>

class EnvInputMethodTab : public Gtk::Box {
private:
    Gtk::Entry *ximEntry;
    Gtk::Entry *ximProgramEntry;

public:
    EnvInputMethodTab();
    
    Glib::ustring getXim() const { return ximEntry->get_text(); }
    Glib::ustring getXimProgram() const { return ximProgramEntry->get_text(); }
    
    void setXim(const Glib::ustring& v) { ximEntry->set_text(v); }
    void setXimProgram(const Glib::ustring& v) { ximProgramEntry->set_text(v); }
};

#endif