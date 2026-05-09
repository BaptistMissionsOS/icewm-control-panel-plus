#ifndef PANELTAB_H
#define PANELTAB_H

#include <gtkmm.h>
#include <string>
#include <vector>

struct TaskbarItem {
    std::string name;
    std::string command;
    std::string icon;
    bool enabled;
};

struct ToolbarItem {
    std::string name;
    std::string command;
    std::string icon;
};

class PanelTab : public Gtk::Box {
private:
    std::string configDir;
    std::vector<TaskbarItem> taskbarItems;
    std::vector<ToolbarItem> toolbarItems;
    
    Gtk::Notebook *notebook;
    
    // Taskbar
    class TaskbarColumns : public Gtk::TreeModelColumnRecord {
    public:
        Gtk::TreeModelColumn<Glib::ustring> name;
        TaskbarColumns() { add(name); }
    };
    TaskbarColumns tbCols;
    Glib::RefPtr<Gtk::ListStore> taskbarStore;
    Gtk::TreeView *taskbarView;
    Gtk::Entry *tbNameEntry, *tbCmdEntry, *tbIconEntry;
    Gtk::CheckButton *tbEnabledCheck;
    
    // Toolbar
    class ToolbarColumns : public Gtk::TreeModelColumnRecord {
    public:
        Gtk::TreeModelColumn<Glib::ustring> name;
        ToolbarColumns() { add(name); }
    };
    ToolbarColumns tlCols;
    Glib::RefPtr<Gtk::ListStore> toolbarStore;
    Gtk::TreeView *toolbarView;
    Gtk::Entry *tlNameEntry, *tlCmdEntry, *tlIconEntry;
    
    // Settings
    Gtk::CheckButton *showTaskbarCheck, *showToolbarCheck, *showTrayCheck;
    Gtk::SpinButton *taskbarHeightSpin;
    
    void loadPanelConfig();
    void savePanelConfig();
    void updateTaskbarList();
    void updateToolbarList();
    
public:
    PanelTab(const std::string& configDir);
    void refresh();
};

#endif
