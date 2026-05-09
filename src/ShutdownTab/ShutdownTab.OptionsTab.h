#ifndef SHUTDOWNTAB_OPTIONSTAB_H
#define SHUTDOWNTAB_OPTIONSTAB_H

#include <gtkmm.h>

class ShutdownOptionsTab : public Gtk::Box {
private:
    Gtk::CheckButton *confirmShutdownCheck;
    Gtk::CheckButton *showLogoutCheck;
    Gtk::CheckButton *showRebootCheck;
    Gtk::CheckButton *showShutdownCheck;
    Gtk::CheckButton *showSuspendCheck;
    Gtk::CheckButton *showHibernateCheck;

public:
    ShutdownOptionsTab();
    
    bool getConfirmShutdown() const { return confirmShutdownCheck->get_active(); }
    bool getShowLogout() const { return showLogoutCheck->get_active(); }
    bool getShowReboot() const { return showRebootCheck->get_active(); }
    bool getShowShutdown() const { return showShutdownCheck->get_active(); }
    bool getShowSuspend() const { return showSuspendCheck->get_active(); }
    bool getShowHibernate() const { return showHibernateCheck->get_active(); }
    
    void setConfirmShutdown(bool v) { confirmShutdownCheck->set_active(v); }
    void setShowLogout(bool v) { showLogoutCheck->set_active(v); }
    void setShowReboot(bool v) { showRebootCheck->set_active(v); }
    void setShowShutdown(bool v) { showShutdownCheck->set_active(v); }
    void setShowSuspend(bool v) { showSuspendCheck->set_active(v); }
    void setShowHibernate(bool v) { showHibernateCheck->set_active(v); }
    
    void setDefaults();
};

#endif