#ifndef SOUNDTAB_EVENTSTAB_H
#define SOUNDTAB_EVENTSTAB_H

#include <gtkmm.h>

class SoundEventsTab : public Gtk::Box {
private:
    Gtk::Entry *startupSoundEntry;
    Gtk::Entry *shutdownSoundEntry;
    Gtk::Entry *windowOpenEntry;
    Gtk::Entry *windowCloseEntry;
    Gtk::Entry *workspaceChangeEntry;
    Gtk::Entry *alertSoundEntry;

public:
    SoundEventsTab();
    
    Glib::ustring getStartupSound() const { return startupSoundEntry->get_text(); }
    Glib::ustring getShutdownSound() const { return shutdownSoundEntry->get_text(); }
    Glib::ustring getWindowOpenSound() const { return windowOpenEntry->get_text(); }
    Glib::ustring getWindowCloseSound() const { return windowCloseEntry->get_text(); }
    Glib::ustring getWorkspaceChangeSound() const { return workspaceChangeEntry->get_text(); }
    Glib::ustring getAlertSound() const { return alertSoundEntry->get_text(); }
    
    void setStartupSound(const Glib::ustring& v) { startupSoundEntry->set_text(v); }
    void setShutdownSound(const Glib::ustring& v) { shutdownSoundEntry->set_text(v); }
    void setWindowOpenSound(const Glib::ustring& v) { windowOpenEntry->set_text(v); }
    void setWindowCloseSound(const Glib::ustring& v) { windowCloseEntry->set_text(v); }
    void setWorkspaceChangeSound(const Glib::ustring& v) { workspaceChangeEntry->set_text(v); }
    void setAlertSound(const Glib::ustring& v) { alertSoundEntry->set_text(v); }
    
    void setDefaults();
};

#endif