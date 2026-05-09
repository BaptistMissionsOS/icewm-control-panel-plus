#ifndef PREFOVERRIDE_FOCUSTAB_H
#define PREFOVERRIDE_FOCUSTAB_H

#include <gtkmm.h>

class PrefFocusTab : public Gtk::Box {
private:
    Gtk::CheckButton *clickToFocusCheck;
    Gtk::CheckButton *raiseOnFocusCheck;
    Gtk::CheckButton *autoRaiseCheck;
    Gtk::CheckButton *opaqueMoveCheck;
    Gtk::CheckButton *opaqueResizeCheck;
    Gtk::CheckButton *focusOnClickClientCheck;
    Gtk::CheckButton *raiseOnClickClientCheck;
    Gtk::CheckButton *raiseOnClickTitleBarCheck;
    Gtk::CheckButton *raiseOnClickButtonCheck;
    Gtk::CheckButton *raiseOnClickFrameCheck;
    Gtk::CheckButton *lowerOnClickWhenRaisedCheck;
    Gtk::CheckButton *passFirstClickToClientCheck;
    Gtk::CheckButton *focusChangesWorkspaceCheck;
    Gtk::CheckButton *strongPointerFocusCheck;
    Gtk::CheckButton *focusOnMapCheck;
    Gtk::CheckButton *focusOnMapTransientCheck;
    Gtk::CheckButton *focusOnMapTransientActiveCheck;
    Gtk::CheckButton *focusOnAppRaiseCheck;
    Gtk::CheckButton *requestFocusOnAppRaiseCheck;

public:
    PrefFocusTab();
    
    // Getters
    bool getClickToFocus() const { return clickToFocusCheck->get_active(); }
    bool getRaiseOnFocus() const { return raiseOnFocusCheck->get_active(); }
    bool getAutoRaise() const { return autoRaiseCheck->get_active(); }
    bool getOpaqueMove() const { return opaqueMoveCheck->get_active(); }
    bool getOpaqueResize() const { return opaqueResizeCheck->get_active(); }
    bool getFocusOnClickClient() const { return focusOnClickClientCheck->get_active(); }
    bool getRaiseOnClickClient() const { return raiseOnClickClientCheck->get_active(); }
    bool getRaiseOnClickTitleBar() const { return raiseOnClickTitleBarCheck->get_active(); }
    bool getRaiseOnClickButton() const { return raiseOnClickButtonCheck->get_active(); }
    bool getRaiseOnClickFrame() const { return raiseOnClickFrameCheck->get_active(); }
    bool getLowerOnClickWhenRaised() const { return lowerOnClickWhenRaisedCheck->get_active(); }
    bool getPassFirstClickToClient() const { return passFirstClickToClientCheck->get_active(); }
    bool getFocusChangesWorkspace() const { return focusChangesWorkspaceCheck->get_active(); }
    bool getStrongPointerFocus() const { return strongPointerFocusCheck->get_active(); }
    bool getFocusOnMap() const { return focusOnMapCheck->get_active(); }
    bool getFocusOnMapTransient() const { return focusOnMapTransientCheck->get_active(); }
    bool getFocusOnMapTransientActive() const { return focusOnMapTransientActiveCheck->get_active(); }
    bool getFocusOnAppRaise() const { return focusOnAppRaiseCheck->get_active(); }
    bool getRequestFocusOnAppRaise() const { return requestFocusOnAppRaiseCheck->get_active(); }
    
    // Setters
    void setClickToFocus(bool value) { clickToFocusCheck->set_active(value); }
    void setRaiseOnFocus(bool value) { raiseOnFocusCheck->set_active(value); }
    void setAutoRaise(bool value) { autoRaiseCheck->set_active(value); }
    void setOpaqueMove(bool value) { opaqueMoveCheck->set_active(value); }
    void setOpaqueResize(bool value) { opaqueResizeCheck->set_active(value); }
    void setFocusOnClickClient(bool value) { focusOnClickClientCheck->set_active(value); }
    void setRaiseOnClickClient(bool value) { raiseOnClickClientCheck->set_active(value); }
    void setRaiseOnClickTitleBar(bool value) { raiseOnClickTitleBarCheck->set_active(value); }
    void setRaiseOnClickButton(bool value) { raiseOnClickButtonCheck->set_active(value); }
    void setRaiseOnClickFrame(bool value) { raiseOnClickFrameCheck->set_active(value); }
    void setLowerOnClickWhenRaised(bool value) { lowerOnClickWhenRaisedCheck->set_active(value); }
    void setPassFirstClickToClient(bool value) { passFirstClickToClientCheck->set_active(value); }
    void setFocusChangesWorkspace(bool value) { focusChangesWorkspaceCheck->set_active(value); }
    void setStrongPointerFocus(bool value) { strongPointerFocusCheck->set_active(value); }
    void setFocusOnMap(bool value) { focusOnMapCheck->set_active(value); }
    void setFocusOnMapTransient(bool value) { focusOnMapTransientCheck->set_active(value); }
    void setFocusOnMapTransientActive(bool value) { focusOnMapTransientActiveCheck->set_active(value); }
    void setFocusOnAppRaise(bool value) { focusOnAppRaiseCheck->set_active(value); }
    void setRequestFocusOnAppRaise(bool value) { requestFocusOnAppRaiseCheck->set_active(value); }
    
    // Reset to defaults
    void setDefaults();
};

#endif
