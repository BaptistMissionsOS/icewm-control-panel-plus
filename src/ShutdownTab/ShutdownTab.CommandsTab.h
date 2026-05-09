#ifndef SHUTDOWNTAB_COMMANDSTAB_H
#define SHUTDOWNTAB_COMMANDSTAB_H

#include <gtkmm.h>

class ShutdownCommandsTab : public Gtk::Box {
private:
    Gtk::Entry *shutdownCmdEntry;
    Gtk::Entry *rebootCmdEntry;
    Gtk::Entry *suspendCmdEntry;
    Gtk::Entry *hibernateCmdEntry;
    Gtk::Entry *lockCmdEntry;
    Gtk::Entry *clockCmdEntry;
    Gtk::Entry *mailCmdEntry;
    Gtk::Entry *runCmdEntry;

public:
    ShutdownCommandsTab();
    
    Glib::ustring getShutdownCmd() const { return shutdownCmdEntry->get_text(); }
    Glib::ustring getRebootCmd() const { return rebootCmdEntry->get_text(); }
    Glib::ustring getSuspendCmd() const { return suspendCmdEntry->get_text(); }
    Glib::ustring getHibernateCmd() const { return hibernateCmdEntry->get_text(); }
    Glib::ustring getLockCmd() const { return lockCmdEntry->get_text(); }
    Glib::ustring getClockCmd() const { return clockCmdEntry->get_text(); }
    Glib::ustring getMailCmd() const { return mailCmdEntry->get_text(); }
    Glib::ustring getRunCmd() const { return runCmdEntry->get_text(); }
    
    void setShutdownCmd(const Glib::ustring& v) { shutdownCmdEntry->set_text(v); }
    void setRebootCmd(const Glib::ustring& v) { rebootCmdEntry->set_text(v); }
    void setSuspendCmd(const Glib::ustring& v) { suspendCmdEntry->set_text(v); }
    void setHibernateCmd(const Glib::ustring& v) { hibernateCmdEntry->set_text(v); }
    void setLockCmd(const Glib::ustring& v) { lockCmdEntry->set_text(v); }
    void setClockCmd(const Glib::ustring& v) { clockCmdEntry->set_text(v); }
    void setMailCmd(const Glib::ustring& v) { mailCmdEntry->set_text(v); }
    void setRunCmd(const Glib::ustring& v) { runCmdEntry->set_text(v); }
    
    void setDefaults();
};

#endif