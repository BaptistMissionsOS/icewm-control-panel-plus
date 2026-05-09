#ifndef PREFERENCES_TASKBAR_TAB_H
#define PREFERENCES_TASKBAR_TAB_H

#include <gtkmm.h>
#include <string>
#include <map>

class PrefTaskBarTab : public Gtk::Box {
public:
    PrefTaskBarTab(const std::string& configDir);

    // Preference management
    void loadPreferences(const std::map<std::string, std::string>& prefs);
    void savePreferences(std::map<std::string, std::string>& prefs);
    void resetWidgets();

private:
    std::string configDir;
    
    // TaskBar Position and Appearance
    Gtk::CheckButton* showTaskBar;
    Gtk::CheckButton* taskBarAtTop;
    Gtk::CheckButton* taskBarAutoHide;
    Gtk::CheckButton* taskBarDoubleHeight;
    Gtk::CheckButton* taskBarKeepBelow;
    Gtk::SpinButton* taskBarWidthPercentage;
    Gtk::CheckButton* taskBarWorkspacesLeft;
    Gtk::CheckButton* taskBarWorkspacesTop;
    Gtk::Entry* taskBarWorkspacesLimit;
    Gtk::SpinButton* taskbarButtonWidthDivisor;
    Gtk::SpinButton* taskbuttonIconOffset;

    // TaskBar Visibility Options
    Gtk::CheckButton* taskBarFullscreenAutoShow;
    Gtk::CheckButton* taskBarShowAllWindows;
    Gtk::CheckButton* taskBarShowWindowIcons;
    Gtk::CheckButton* taskBarShowWindowTitles;
    Gtk::CheckButton* taskBarShowTransientWindows;
    Gtk::CheckButton* taskBarShowClock;
    Gtk::CheckButton* taskBarClockLeds;
    Gtk::CheckButton* taskBarShowShowDesktopButton;
    Gtk::CheckButton* taskBarShowStartMenu;
    Gtk::CheckButton* taskBarShowWindowListMenu;
    Gtk::CheckButton* taskBarShowCollapseButton;
    Gtk::CheckButton* taskBarShowWorkspaces;
    Gtk::CheckButton* taskBarShowPager;
    Gtk::CheckButton* taskBarShowTray;
    Gtk::CheckButton* taskBarEnableSystemTray;

    // TaskBar Behavior
    Gtk::CheckButton* taskBarLaunchOnSingleClick;
    Gtk::CheckButton* taskBarUseMouseWheel;
    Gtk::SpinButton* taskBarTaskGrouping;

    // Status Monitoring
    Gtk::CheckButton* taskBarShowCPUStatus;
    Gtk::SpinButton* taskBarCPUdelay;
    Gtk::SpinButton* taskBarCPUsamples;
    Gtk::CheckButton* taskBarShowMEMStatus;
    Gtk::SpinButton* taskBarMEMDelay;
    Gtk::SpinButton* taskBarMEMsamples;
    Gtk::CheckButton* taskBarShowNetStatus;
    Gtk::SpinButton* taskBarNetDelay;
    Gtk::SpinButton* taskBarNetSamples;
    Gtk::CheckButton* taskBarShowAPMStatus;
    Gtk::CheckButton* taskBarShowAPMGraph;
    Gtk::CheckButton* taskBarShowAPMTime;
    Gtk::SpinButton* taskBarApmGraphWidth;

    // Mail Status
    Gtk::CheckButton* taskBarShowMailboxStatus;
    Gtk::CheckButton* taskBarMailboxStatusBeepOnNewMail;
    Gtk::CheckButton* taskBarMailboxStatusCountMessages;
    Gtk::SpinButton* mailCheckDelay;
    Gtk::Entry* mailBoxPath;

    // Network Status
    Gtk::Entry* networkStatusDevice;
    Gtk::CheckButton* netStatusShowOnlyRunning;

    // CPU Status Advanced
    Gtk::CheckButton* cpuStatusShowAcpiTemp;
    Gtk::CheckButton* cpuStatusShowAcpiTempInGraph;
    Gtk::CheckButton* cpuStatusShowCpuFreq;
    Gtk::CheckButton* cpuStatusShowRamUsage;
    Gtk::CheckButton* cpuStatusShowSwapUsage;
    Gtk::Entry* cpuStatusClassHint;
    Gtk::Entry* cpuStatusCommand;
    Gtk::CheckButton* cpuStatusCombine;

    // Graph Appearance
    Gtk::SpinButton* taskBarGraphHeight;

    // TaskBar Justification
    Gtk::ComboBoxText* taskBarJustify;

    // Callbacks
    void checkbox_cb(Gtk::Widget* w, void* v);
    void input_cb(Gtk::Widget* w, void* v);
    void spinbutton_cb(Gtk::Widget* w, void* v);
    void combo_box_cb(Gtk::Widget* w, void* v);

    // Helper functions
    void createTaskBarControls();
    void addCheckbox(Gtk::Widget*& btn, const char* key);
    void addInput(Gtk::Widget*& input, const char* key);
    void addSpinButton(Gtk::Widget*& spin, const char* key, double min, double max, double step);
    void addComboBox(Gtk::Widget*& combo, const char* key);
    void addCategory(const char* title);
};

#endif