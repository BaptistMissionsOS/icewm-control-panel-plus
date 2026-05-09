#ifndef KEYSTAB_H
#define KEYSTAB_H

#include <gtkmm.h>
#include <string>
#include <vector>

struct KeyBinding {
    std::string key;
    std::string action;
};

class KeysTab : public Gtk::Box {
private:
    std::string configDir;
    std::vector<KeyBinding> keyBindings;
    
    class KeyColumns : public Gtk::TreeModelColumnRecord {
    public:
        Gtk::TreeModelColumn<Glib::ustring> name;
        KeyColumns() { add(name); }
    };
    KeyColumns cols;
    Glib::RefPtr<Gtk::ListStore> listStore;
    Gtk::TreeView *treeView;
    Gtk::Entry *keyEntry;
    Gtk::Entry *actionEntry;
    
    void loadKeysFile();
    void saveKeysFile();
    void updateList();
    void updateInputs();
    
public:
    KeysTab(const std::string& configDir);
    void refresh();
};

#endif
