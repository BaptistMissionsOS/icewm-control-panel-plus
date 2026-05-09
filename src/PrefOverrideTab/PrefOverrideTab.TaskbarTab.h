#ifndef PREFOVERRIDE_TASKBARTAB_H
#define PREFOVERRIDE_TASKBARTAB_H

#include <gtkmm.h>

class PrefTaskbarTab : public Gtk::Box {
private:
    Gtk::CheckButton *taskBarAtTopCheck;
    Gtk::CheckButton *taskBarAutoHideCheck;
    Gtk::CheckButton *taskBarShowClockCheck;
    Gtk::CheckButton *taskBarShowWorkspacesCheck;
    Gtk::CheckButton *taskBarShowWindowsCheck;

public:
    PrefTaskbarTab();
    
    // Getters
    bool getTaskBarAtTop() const { return taskBarAtTopCheck->get_active(); }
    bool getTaskBarAutoHide() const { return taskBarAutoHideCheck->get_active(); }
    bool getTaskBarShowClock() const { return taskBarShowClockCheck->get_active(); }
    bool getTaskBarShowWorkspaces() const { return taskBarShowWorkspacesCheck->get_active(); }
    bool getTaskBarShowWindows() const { return taskBarShowWindowsCheck->get_active(); }
    
    // Setters
    void setTaskBarAtTop(bool value) { taskBarAtTopCheck->set_active(value); }
    void setTaskBarAutoHide(bool value) { taskBarAutoHideCheck->set_active(value); }
    void setTaskBarShowClock(bool value) { taskBarShowClockCheck->set_active(value); }
    void setTaskBarShowWorkspaces(bool value) { taskBarShowWorkspacesCheck->set_active(value); }
    void setTaskBarShowWindows(bool value) { taskBarShowWindowsCheck->set_active(value); }
    
    // Reset to defaults
    void setDefaults();
};

#endif
