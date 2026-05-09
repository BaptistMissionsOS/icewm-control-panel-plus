#ifndef TOPMENUBAR_ICWM_H
#define TOPMENUBAR_ICWM_H

#include <gtkmm.h>

namespace TopMenuBar {
namespace IceWM {
    void setupMenu(Gtk::MenuBar* menubar);
    void icesh_run(const std::string& cmd);
    void backup_manager_dialog(bool themeOnly = false);
    void shell_cmd_dialog();
}
}

#endif