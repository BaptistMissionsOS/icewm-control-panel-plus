#ifndef PREFERENCES_KEYS_TAB_H
#define PREFERENCES_KEYS_TAB_H

#include <gtkmm.h>
#include <string>
#include <map>

class PrefKeysTab : public Gtk::Box {
public:
    PrefKeysTab();

    // Preference management
    void loadPreferences(const std::map<std::string, std::string>& prefs);
    void savePreferences(std::map<std::string, std::string>& prefs);
    void resetWidgets();

private:
    // Key entry fields
    Gtk::Entry* keySysAddressBar;
    Gtk::Entry* keySysArrange;
    Gtk::Entry* keySysArrangeIcons;
    Gtk::Entry* keySysCascade;
    Gtk::Entry* keySysCollapseTaskBar;
    Gtk::Entry* keySysDialog;
    Gtk::Entry* keySysHideAll;
    Gtk::Entry* keySysKeyboardNext;
    Gtk::Entry* keySysMenu;
    Gtk::Entry* keySysMinimizeAll;
    Gtk::Entry* keySysShowDesktop;
    Gtk::Entry* keySysSwitchClass;
    Gtk::Entry* keySysSwitchLast;
    Gtk::Entry* keySysSwitchNext;
    Gtk::Entry* keySysTileHorizontal;
    Gtk::Entry* keySysTileVertical;
    Gtk::Entry* keySysUndoArrange;
    Gtk::Entry* keySysWinListMenu;
    Gtk::Entry* keySysWinMenu;
    Gtk::Entry* keySysWinNext;
    Gtk::Entry* keySysWinPrev;
    Gtk::Entry* keySysWindowList;

    // Workspace keys (1-12)
    Gtk::Entry* keySysWorkspace1;
    Gtk::Entry* keySysWorkspace2;
    Gtk::Entry* keySysWorkspace3;
    Gtk::Entry* keySysWorkspace4;
    Gtk::Entry* keySysWorkspace5;
    Gtk::Entry* keySysWorkspace6;
    Gtk::Entry* keySysWorkspace7;
    Gtk::Entry* keySysWorkspace8;
    Gtk::Entry* keySysWorkspace9;
    Gtk::Entry* keySysWorkspace10;
    Gtk::Entry* keySysWorkspace11;
    Gtk::Entry* keySysWorkspace12;

    // Workspace take window keys (1-12)
    Gtk::Entry* keySysWorkspace1TakeWin;
    Gtk::Entry* keySysWorkspace2TakeWin;
    Gtk::Entry* keySysWorkspace3TakeWin;
    Gtk::Entry* keySysWorkspace4TakeWin;
    Gtk::Entry* keySysWorkspace5TakeWin;
    Gtk::Entry* keySysWorkspace6TakeWin;
    Gtk::Entry* keySysWorkspace7TakeWin;
    Gtk::Entry* keySysWorkspace8TakeWin;
    Gtk::Entry* keySysWorkspace9TakeWin;
    Gtk::Entry* keySysWorkspace10TakeWin;
    Gtk::Entry* keySysWorkspace11TakeWin;
    Gtk::Entry* keySysWorkspace12TakeWin;

    // Additional workspace navigation
    Gtk::Entry* keySysWorkspaceLast;
    Gtk::Entry* keySysWorkspaceLastTakeWin;
    Gtk::Entry* keySysWorkspaceNext;
    Gtk::Entry* keySysWorkspaceNextTakeWin;
    Gtk::Entry* keySysWorkspacePrev;
    Gtk::Entry* keySysWorkspacePrevTakeWin;

    // Taskbar keys
    Gtk::Entry* keyTaskBarMoveNext;
    Gtk::Entry* keyTaskBarMovePrev;
    Gtk::Entry* keyTaskBarSwitchNext;
    Gtk::Entry* keyTaskBarSwitchPrev;

    // Window management keys
    Gtk::Entry* keyWinArrangeC;
    Gtk::Entry* keyWinArrangeE;
    Gtk::Entry* keyWinArrangeN;
    Gtk::Entry* keyWinArrangeNE;
    Gtk::Entry* keyWinArrangeNW;
    Gtk::Entry* keyWinArrangeS;
    Gtk::Entry* keyWinArrangeSE;
    Gtk::Entry* keyWinArrangeSW;
    Gtk::Entry* keyWinArrangeW;
    Gtk::Entry* keyWinClose;
    Gtk::Entry* keyWinFullscreen;
    Gtk::Entry* keyWinHide;
    Gtk::Entry* keyWinLower;
    Gtk::Entry* keyWinMaximize;
    Gtk::Entry* keyWinMaximizeHoriz;
    Gtk::Entry* keyWinMaximizeVert;
    Gtk::Entry* keyWinMenu;
    Gtk::Entry* keyWinMinimize;
    Gtk::Entry* keyWinMove;
    Gtk::Entry* keyWinNext;
    Gtk::Entry* keyWinOccupyAll;
    Gtk::Entry* keyWinPrev;
    Gtk::Entry* keyWinRaise;
    Gtk::Entry* keyWinRestore;
    Gtk::Entry* keyWinRollup;
    Gtk::Entry* keyWinSize;
    Gtk::Entry* keyWinSmartPlace;

    // Window tiling keys
    Gtk::Entry* keyWinTileBottom;
    Gtk::Entry* keyWinTileBottomLeft;
    Gtk::Entry* keyWinTileBottomRight;
    Gtk::Entry* keyWinTileCenter;
    Gtk::Entry* keyWinTileLeft;
    Gtk::Entry* keyWinTileRight;
    Gtk::Entry* keyWinTileTop;
    Gtk::Entry* keyWinTileTopLeft;
    Gtk::Entry* keyWinTileTopRight;

    // Callbacks (no longer needed with lambda connections)
    void key_cb(Gtk::Widget* w, void* v);
    void capture_key_cb(Gtk::Widget* w, void* v);
    void reset_key_cb(Gtk::Widget* w, void* v);
};

#endif