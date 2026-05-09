#ifndef PREFERENCES_COLORS_TAB_H
#define PREFERENCES_COLORS_TAB_H

#include <gtkmm.h>
#include <string>
#include <map>

class PrefColorsTab : public Gtk::Box {
public:
    PrefColorsTab();

    // Preference management
    void loadPreferences(const std::map<std::string, std::string>& prefs);
    void savePreferences(std::map<std::string, std::string>& prefs);
    void resetWidgets();

private:
    // Color buttons for all color preferences
    Gtk::ColorButton* colorDialog;
    Gtk::ColorButton* colorNormalBorder;
    Gtk::ColorButton* colorActiveBorder;
    Gtk::ColorButton* colorNormalTitleBar;
    Gtk::ColorButton* colorNormalTitleBarText;
    Gtk::ColorButton* colorNormalTitleBarShadow;
    Gtk::ColorButton* colorActiveTitleBar;
    Gtk::ColorButton* colorActiveTitleBarText;
    Gtk::ColorButton* colorActiveTitleBarShadow;
    Gtk::ColorButton* colorNormalTitleButton;
    Gtk::ColorButton* colorNormalTitleButtonText;
    Gtk::ColorButton* colorToolButton;
    Gtk::ColorButton* colorToolButtonText;
    Gtk::ColorButton* colorNormalButton;
    Gtk::ColorButton* colorNormalButtonText;
    Gtk::ColorButton* colorActiveButton;
    Gtk::ColorButton* colorActiveButtonText;
    Gtk::ColorButton* colorNormalWorkspaceButton;
    Gtk::ColorButton* colorNormalWorkspaceButtonText;
    Gtk::ColorButton* colorActiveWorkspaceButton;
    Gtk::ColorButton* colorActiveWorkspaceButtonText;
    Gtk::ColorButton* colorNormalMenu;
    Gtk::ColorButton* colorNormalMenuItemText;
    Gtk::ColorButton* colorActiveMenuItem;
    Gtk::ColorButton* colorActiveMenuItemText;
    Gtk::ColorButton* colorDisabledMenuItemText;
    Gtk::ColorButton* colorDisabledMenuItemShadow;
    Gtk::ColorButton* colorDefaultTaskBar;
    Gtk::ColorButton* colorNormalTaskBarApp;
    Gtk::ColorButton* colorNormalTaskBarAppText;
    Gtk::ColorButton* colorActiveTaskBarApp;
    Gtk::ColorButton* colorActiveTaskBarAppText;
    Gtk::ColorButton* colorMinimizedTaskBarApp;
    Gtk::ColorButton* colorMinimizedTaskBarAppText;
    Gtk::ColorButton* colorInvisibleTaskBarApp;
    Gtk::ColorButton* colorInvisibleTaskBarAppText;
    Gtk::ColorButton* colorQuickSwitch;
    Gtk::ColorButton* colorQuickSwitchBorder;
    Gtk::ColorButton* colorQuickSwitchText;
    Gtk::ColorButton* colorQuickSwitchActive;
    Gtk::ColorButton* colorMoveSizeStatus;
    Gtk::ColorButton* colorMoveSizeStatusText;

    // Helper functions
    Gdk::RGBA parseColor(const std::string& colorStr);
    std::string colorToString(const Gdk::RGBA& color);

    // Callback for color selection
    void color_cb(Gtk::Widget* w, void* v);
};

#endif