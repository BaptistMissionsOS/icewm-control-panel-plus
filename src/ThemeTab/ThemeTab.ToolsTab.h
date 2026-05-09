#ifndef THEMETAB_TOOLSTAB_H
#define THEMETAB_TOOLSTAB_H

#include <gtkmm.h>

class ToolsTab : public Gtk::Box {
private:
    std::string configDir;
    
    Gtk::Entry* sourceThemeEntry;
    Gtk::Entry* targetThemeEntry;
    Gtk::ProgressBar* progressBar;
    Gtk::TextView* logView;
    
    void browseSource();
    void browseTarget();
    void copyTheme();
    void exportTheme();
    void importTheme();
    void resetTheme();
    void log(const std::string& msg);
    
public:
    ToolsTab(const std::string& configDir);
    void refresh();
};

#endif
