#ifndef PREFOVERRIDETAB_H
#define PREFOVERRIDETAB_H

#include <gtkmm.h>
#include <string>
#include <map>

class PrefOverrideTab : public Gtk::Box {
private:
    std::string configDir;
    std::map<std::string, std::string> overrides;
    
    class OverrideColumns : public Gtk::TreeModelColumnRecord {
    public:
        Gtk::TreeModelColumn<Glib::ustring> key;
        Gtk::TreeModelColumn<Glib::ustring> val;
        OverrideColumns() { add(key); add(val); }
    };
    OverrideColumns cols;
    Glib::RefPtr<Gtk::ListStore> listStore;
    Gtk::TreeView *treeView;
    Gtk::Entry *keyEntry, *valEntry;
    
    void loadOverrides();
    void saveOverrides();
    void updateList();
    void updateInputs();
    
public:
    PrefOverrideTab(const std::string& configDir);
    void refresh();
};

#endif
