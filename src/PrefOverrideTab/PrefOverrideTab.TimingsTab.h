#ifndef PREFOVERRIDE_TIMINGSTAB_H
#define PREFOVERRIDE_TIMINGSTAB_H

#include <gtkmm.h>

class PrefTimingsTab : public Gtk::Box {
private:
    Gtk::SpinButton *clickMotionDistanceSpinner;
    Gtk::SpinButton *clickMotionDelaySpinner;
    Gtk::SpinButton *multiClickTimeSpinner;
    Gtk::SpinButton *menuActivateDelaySpinner;
    Gtk::SpinButton *submenuMenuActivateDelaySpinner;
    Gtk::SpinButton *toolTipDelaySpinner;
    Gtk::SpinButton *toolTipTimeSpinner;
    Gtk::SpinButton *autoHideDelaySpinner;
    Gtk::SpinButton *autoShowDelaySpinner;
    Gtk::SpinButton *autoRaiseDelaySpinner;
    Gtk::SpinButton *pointerFocusDelaySpinner;
    Gtk::SpinButton *workspaceStatusTimeSpinner;
    Gtk::SpinButton *focusRequestFlashTimeSpinner;
    Gtk::SpinButton *focusRequestFlashIntervalSpinner;

public:
    PrefTimingsTab();
    
    // Getters
    int getClickMotionDistance() const { return (int)clickMotionDistanceSpinner->get_value(); }
    int getClickMotionDelay() const { return (int)clickMotionDelaySpinner->get_value(); }
    int getMultiClickTime() const { return (int)multiClickTimeSpinner->get_value(); }
    int getMenuActivateDelay() const { return (int)menuActivateDelaySpinner->get_value(); }
    int getSubmenuMenuActivateDelay() const { return (int)submenuMenuActivateDelaySpinner->get_value(); }
    int getToolTipDelay() const { return (int)toolTipDelaySpinner->get_value(); }
    int getToolTipTime() const { return (int)toolTipTimeSpinner->get_value(); }
    int getAutoHideDelay() const { return (int)autoHideDelaySpinner->get_value(); }
    int getAutoShowDelay() const { return (int)autoShowDelaySpinner->get_value(); }
    int getAutoRaiseDelay() const { return (int)autoRaiseDelaySpinner->get_value(); }
    int getPointerFocusDelay() const { return (int)pointerFocusDelaySpinner->get_value(); }
    int getWorkspaceStatusTime() const { return (int)workspaceStatusTimeSpinner->get_value(); }
    int getFocusRequestFlashTime() const { return (int)focusRequestFlashTimeSpinner->get_value(); }
    int getFocusRequestFlashInterval() const { return (int)focusRequestFlashIntervalSpinner->get_value(); }
    
    // Setters
    void setClickMotionDistance(int value) { clickMotionDistanceSpinner->set_value(value); }
    void setClickMotionDelay(int value) { clickMotionDelaySpinner->set_value(value); }
    void setMultiClickTime(int value) { multiClickTimeSpinner->set_value(value); }
    void setMenuActivateDelay(int value) { menuActivateDelaySpinner->set_value(value); }
    void setSubmenuMenuActivateDelay(int value) { submenuMenuActivateDelaySpinner->set_value(value); }
    void setToolTipDelay(int value) { toolTipDelaySpinner->set_value(value); }
    void setToolTipTime(int value) { toolTipTimeSpinner->set_value(value); }
    void setAutoHideDelay(int value) { autoHideDelaySpinner->set_value(value); }
    void setAutoShowDelay(int value) { autoShowDelaySpinner->set_value(value); }
    void setAutoRaiseDelay(int value) { autoRaiseDelaySpinner->set_value(value); }
    void setPointerFocusDelay(int value) { pointerFocusDelaySpinner->set_value(value); }
    void setWorkspaceStatusTime(int value) { workspaceStatusTimeSpinner->set_value(value); }
    void setFocusRequestFlashTime(int value) { focusRequestFlashTimeSpinner->set_value(value); }
    void setFocusRequestFlashInterval(int value) { focusRequestFlashIntervalSpinner->set_value(value); }
    
    // Reset to defaults
    void setDefaults();
};

#endif
