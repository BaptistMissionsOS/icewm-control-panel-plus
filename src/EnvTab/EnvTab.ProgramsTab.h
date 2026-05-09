#ifndef ENVTAB_PROGRAMSTAB_H
#define ENVTAB_PROGRAMSTAB_H

#include <gtkmm.h>

class EnvProgramsTab : public Gtk::Box {
private:
    Gtk::Entry *termEntry;
    Gtk::Entry *browserEntry;
    Gtk::Entry *editorEntry;

public:
    EnvProgramsTab();
    
    Glib::ustring getTerm() const { return termEntry->get_text(); }
    Glib::ustring getBrowser() const { return browserEntry->get_text(); }
    Glib::ustring getEditor() const { return editorEntry->get_text(); }
    
    void setTerm(const Glib::ustring& v) { termEntry->set_text(v); }
    void setBrowser(const Glib::ustring& v) { browserEntry->set_text(v); }
    void setEditor(const Glib::ustring& v) { editorEntry->set_text(v); }
};

#endif