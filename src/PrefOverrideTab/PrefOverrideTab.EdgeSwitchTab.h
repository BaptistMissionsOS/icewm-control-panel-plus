#ifndef PREFOVERRIDE_EDGESWITCHTAB_H
#define PREFOVERRIDE_EDGESWITCHTAB_H

#include <gtkmm.h>

class PrefEdgeSwitchTab : public Gtk::Box {
private:
    Gtk::CheckButton *edgeSwitchCheck;
    Gtk::CheckButton *horizontalEdgeSwitchCheck;
    Gtk::CheckButton *verticalEdgeSwitchCheck;
    Gtk::CheckButton *continuousEdgeSwitchCheck;
    Gtk::SpinButton *edgeSwitchDelaySpinner;

public:
    PrefEdgeSwitchTab();
    
    // Getters
    bool getEdgeSwitch() const { return edgeSwitchCheck->get_active(); }
    bool getHorizontalEdgeSwitch() const { return horizontalEdgeSwitchCheck->get_active(); }
    bool getVerticalEdgeSwitch() const { return verticalEdgeSwitchCheck->get_active(); }
    bool getContinuousEdgeSwitch() const { return continuousEdgeSwitchCheck->get_active(); }
    int getEdgeSwitchDelay() const { return (int)edgeSwitchDelaySpinner->get_value(); }
    
    // Setters
    void setEdgeSwitch(bool value) { edgeSwitchCheck->set_active(value); }
    void setHorizontalEdgeSwitch(bool value) { horizontalEdgeSwitchCheck->set_active(value); }
    void setVerticalEdgeSwitch(bool value) { verticalEdgeSwitchCheck->set_active(value); }
    void setContinuousEdgeSwitch(bool value) { continuousEdgeSwitchCheck->set_active(value); }
    void setEdgeSwitchDelay(int value) { edgeSwitchDelaySpinner->set_value(value); }
    
    // Reset to defaults
    void setDefaults();
};

#endif
