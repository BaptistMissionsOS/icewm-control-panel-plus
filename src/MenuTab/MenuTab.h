#ifndef MENUTAB_H
#define MENUTAB_H

#include <gtkmm.h>
#include <string>
#include <vector>

struct MenuEntry {
    std::string name;
    std::string icon;
    std::string command;
    std::string type; // "prog", "menu", "separator", "restart", "runonce"
    std::vector<MenuEntry> children;
};

class MenuTab : public Gtk::Box {
private:
    std::string configDir;
    std::vector<MenuEntry> menuEntries;
    
    class MenuColumns : public Gtk::TreeModelColumnRecord {
    public:
        Gtk::TreeModelColumn<Glib::ustring> name;
        Gtk::TreeModelColumn<Glib::ustring> type;
        MenuColumns() { add(name); add(type); }
    };
    MenuColumns cols;
    Glib::RefPtr<Gtk::TreeStore> treeStore;
    Gtk::TreeView *treeView;
    Gtk::Entry *nameEntry;
    Gtk::Entry *iconEntry;
    Gtk::Entry *commandEntry;
    Gtk::ComboBoxText *typeCombo;
    
    void loadMenuFile();
    void saveMenuFile();
    void updateTree();
    void updateInputs();
    
public:
    MenuTab(const std::string& configDir);
    void refresh();
};

#endif
