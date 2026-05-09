#ifndef PREFOVERRIDE_QUICKSWITCHTAB_H
#define PREFOVERRIDE_QUICKSWITCHTAB_H

#include <gtkmm.h>

class PrefQuickSwitchTab : public Gtk::Box {
private:
    Gtk::CheckButton *quickSwitchCheck;
    Gtk::CheckButton *quickSwitchToMinimizedCheck;
    Gtk::CheckButton *quickSwitchToHiddenCheck;
    Gtk::CheckButton *quickSwitchToUrgentCheck;
    Gtk::CheckButton *quickSwitchToAllWorkspacesCheck;
    Gtk::CheckButton *quickSwitchGroupWorkspacesCheck;
    Gtk::CheckButton *quickSwitchAllIconsCheck;
    Gtk::CheckButton *quickSwitchTextFirstCheck;
    Gtk::CheckButton *quickSwitchSmallWindowCheck;
    Gtk::CheckButton *quickSwitchMaxWidthCheck;
    Gtk::CheckButton *quickSwitchVerticalCheck;
    Gtk::CheckButton *quickSwitchHugeIconCheck;
    Gtk::CheckButton *quickSwitchFillSelectionCheck;

public:
    PrefQuickSwitchTab();
    
    // Getters
    bool getQuickSwitch() const { return quickSwitchCheck->get_active(); }
    bool getQuickSwitchToMinimized() const { return quickSwitchToMinimizedCheck->get_active(); }
    bool getQuickSwitchToHidden() const { return quickSwitchToHiddenCheck->get_active(); }
    bool getQuickSwitchToUrgent() const { return quickSwitchToUrgentCheck->get_active(); }
    bool getQuickSwitchToAllWorkspaces() const { return quickSwitchToAllWorkspacesCheck->get_active(); }
    bool getQuickSwitchGroupWorkspaces() const { return quickSwitchGroupWorkspacesCheck->get_active(); }
    bool getQuickSwitchAllIcons() const { return quickSwitchAllIconsCheck->get_active(); }
    bool getQuickSwitchTextFirst() const { return quickSwitchTextFirstCheck->get_active(); }
    bool getQuickSwitchSmallWindow() const { return quickSwitchSmallWindowCheck->get_active(); }
    bool getQuickSwitchMaxWidth() const { return quickSwitchMaxWidthCheck->get_active(); }
    bool getQuickSwitchVertical() const { return quickSwitchVerticalCheck->get_active(); }
    bool getQuickSwitchHugeIcon() const { return quickSwitchHugeIconCheck->get_active(); }
    bool getQuickSwitchFillSelection() const { return quickSwitchFillSelectionCheck->get_active(); }
    
    // Setters
    void setQuickSwitch(bool value) { quickSwitchCheck->set_active(value); }
    void setQuickSwitchToMinimized(bool value) { quickSwitchToMinimizedCheck->set_active(value); }
    void setQuickSwitchToHidden(bool value) { quickSwitchToHiddenCheck->set_active(value); }
    void setQuickSwitchToUrgent(bool value) { quickSwitchToUrgentCheck->set_active(value); }
    void setQuickSwitchToAllWorkspaces(bool value) { quickSwitchToAllWorkspacesCheck->set_active(value); }
    void setQuickSwitchGroupWorkspaces(bool value) { quickSwitchGroupWorkspacesCheck->set_active(value); }
    void setQuickSwitchAllIcons(bool value) { quickSwitchAllIconsCheck->set_active(value); }
    void setQuickSwitchTextFirst(bool value) { quickSwitchTextFirstCheck->set_active(value); }
    void setQuickSwitchSmallWindow(bool value) { quickSwitchSmallWindowCheck->set_active(value); }
    void setQuickSwitchMaxWidth(bool value) { quickSwitchMaxWidthCheck->set_active(value); }
    void setQuickSwitchVertical(bool value) { quickSwitchVerticalCheck->set_active(value); }
    void setQuickSwitchHugeIcon(bool value) { quickSwitchHugeIconCheck->set_active(value); }
    void setQuickSwitchFillSelection(bool value) { quickSwitchFillSelectionCheck->set_active(value); }
    
    // Reset to defaults
    void setDefaults();
};

#endif
