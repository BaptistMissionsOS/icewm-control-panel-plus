#include "File.h"
#include <gtkmm/messagedialog.h>

namespace TopMenuBar {
namespace File {

void setupMenu(Gtk::MenuBar* menubar) {
    auto* fileItem = Gtk::manage(new Gtk::MenuItem("_File", true));
    auto* fileMenu = Gtk::manage(new Gtk::Menu());
    
    auto* saveItem = Gtk::manage(new Gtk::MenuItem("_Save", true));
    saveItem->signal_activate().connect([]() {
        Gtk::MessageDialog dlg("Configuration saved!", false, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK);
        dlg.run();
    });
    fileMenu->append(*saveItem);
    
    auto* quitItem = Gtk::manage(new Gtk::MenuItem("_Quit", true));
    quitItem->signal_activate().connect([]() {
        Gtk::MessageDialog dlg("Quit without saving?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
        if (dlg.run() == Gtk::RESPONSE_YES)
            exit(0);
    });
    fileMenu->append(*quitItem);
    
    fileItem->set_submenu(*fileMenu);
    menubar->append(*fileItem);
}

} // namespace File
} // namespace TopMenuBar