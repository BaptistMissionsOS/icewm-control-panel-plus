#ifndef PROGRAMSTAB_H
#define PROGRAMSTAB_H

#include <gtkmm.h>
#include <string>
#include <vector>

struct ProgramEntry {
    std::string name;
    std::string icon;
    std::string command;
    bool runOnce;
    ProgramEntry(const std::string& n, const std::string& i, const std::string& c, bool once = false)
        : name(n), icon(i), command(c), runOnce(once) {}
};

class ProgramsTab : public Gtk::Box {
private:
    std::string configDir;
    std::vector<ProgramEntry> programs;
    
    class ProgramColumns : public Gtk::TreeModelColumnRecord {
    public:
        Gtk::TreeModelColumn<Glib::ustring> name;
        ProgramColumns() { add(name); }
    };
    ProgramColumns cols;
    Glib::RefPtr<Gtk::ListStore> listStore;
    Gtk::TreeView *treeView;
    Gtk::Entry *nameEntry;
    Gtk::Entry *iconEntry;
    Gtk::Entry *commandEntry;
    Gtk::CheckButton *runOnceCheck;
    
    void loadProgramsFile();
    void saveProgramsFile();
    void updateList();
    void updateInputs();
    void clearInputs();
    
public:
    ProgramsTab(const std::string& configDir);
    void refresh();
};

#endif
