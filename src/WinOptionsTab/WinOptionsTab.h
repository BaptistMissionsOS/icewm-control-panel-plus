#ifndef WINOPTIONSTAB_H
#define WINOPTIONSTAB_H

#include <gtkmm.h>
#include <string>
#include <vector>

struct WinOption {
    std::string windowClass;
    std::string option;
    std::string value;
};

class WinOptionsTab : public Gtk::Box {
private:
    std::string configDir;
    std::vector<WinOption> winOptions;
    
    class WinOptionsColumns : public Gtk::TreeModelColumnRecord {
    public:
        Gtk::TreeModelColumn<Glib::ustring> name;
        WinOptionsColumns() { add(name); }
    };
    WinOptionsColumns cols;
    Glib::RefPtr<Gtk::ListStore> listStore;
    Gtk::TreeView *treeView;
    Gtk::Entry *classEntry;
    Gtk::ComboBoxText *optionCombo;
    Gtk::ComboBoxText *valueCombo;
    
    void loadWinOptionsFile();
    void saveWinOptionsFile();
    void updateList();
    void updateInputs();
    void initChoices();
    
public:
    WinOptionsTab(const std::string& configDir);
    void refresh();
};

#endif
