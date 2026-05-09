#ifndef THEMETAB_EXPLORETAB_H
#define THEMETAB_EXPLORETAB_H

#include <gtkmm.h>

class ExploreTab : public Gtk::Box {
private:
    std::string configDir;
    
    class ThemeColumns : public Gtk::TreeModelColumnRecord {
    public:
        Gtk::TreeModelColumn<Glib::ustring> name;
        Gtk::TreeModelColumn<Glib::ustring> path;
        Gtk::TreeModelColumn<Glib::ustring> description;
        ThemeColumns() { add(name); add(path); add(description); }
    };
    ThemeColumns cols;
    Glib::RefPtr<Gtk::ListStore> listStore;
    Gtk::TreeView* treeView;
    Gtk::TextView* detailsView;
    
    void scanAllThemes();
    void onSelectionChanged();
    void installTheme();
    void deleteTheme();
    
public:
    ExploreTab(const std::string& configDir);
    void refresh();
};

#endif
