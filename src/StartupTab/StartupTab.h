#ifndef STARTUPTAB_H
#define STARTUPTAB_H

#include <gtkmm.h>
#include <string>
#include <vector>

struct StartupCommand {
    std::string command;
    bool enabled;
    std::string description;
};

class StartupTab : public Gtk::Box {
private:
    std::string configDir;
    std::vector<StartupCommand> startupCommands;
    
    class StartupColumns : public Gtk::TreeModelColumnRecord {
    public:
        Gtk::TreeModelColumn<Glib::ustring> name;
        StartupColumns() { add(name); }
    };
    StartupColumns cols;
    Glib::RefPtr<Gtk::ListStore> listStore;
    Gtk::TreeView *treeView;
    Gtk::Entry *commandEntry;
    Gtk::Entry *descriptionEntry;
    Gtk::CheckButton *enabledCheck;
    
    void loadStartupFile();
    void saveStartupFile();
    void updateList();
    void updateInputs();
    
public:
    StartupTab(const std::string& configDir);
    void refresh();
};

#endif
