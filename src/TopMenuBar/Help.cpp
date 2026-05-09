#include "Help.h"
#include <gtkmm/messagedialog.h>
#include <cstdlib>
#include <string>

namespace TopMenuBar {
namespace Help {

static void on_icehelp() {
    const char* docPaths[] = {
        "/usr/share/doc/icewm/icewm.html",
        "/usr/share/doc/icewm/html/icewm.html",
        "/usr/share/doc/icewm/icewm.html.gz",
        "/usr/share/man/man1/icewm.1.html",
        "/usr/local/share/doc/icewm/icewm.html",
        "/usr/local/share/doc/icewm/html/icewm.html",
        nullptr
    };
    
    std::string docFile;
    for (int i = 0; docPaths[i] != nullptr; ++i) {
        std::string path = docPaths[i];
        if (path.find(".html.gz") != std::string::npos) {
            std::string cmd = "gunzip -c \"" + path + "\" > /tmp/icewm.html 2>/dev/null";
            if (system(cmd.c_str()) == 0) {
                docFile = "/tmp/icewm.html";
                break;
            }
        } else {
            std::string cmd = "test -r \"" + path + "\"";
            if (system(cmd.c_str()) == 0) {
                docFile = path;
                break;
            }
        }
    }
    
    if (docFile.empty()) {
        Gtk::MessageDialog dlg("Local IceWM documentation not found.\nOpen online manual?",
            false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
        if (dlg.run() == Gtk::RESPONSE_YES) {
            system("xdg-open https://ice-wm.org/manual/ &");
        }
        return;
    }
    
    std::string cmd = "icehelp \"" + docFile + "\" &";
    if (system(cmd.c_str()) != 0) {
        Gtk::MessageDialog dlg("Failed to launch icehelp.\nMake sure IceWM is installed.",
            false, Gtk::MESSAGE_ERROR);
        dlg.run();
    }
}

static void on_about() {
    Gtk::MessageDialog dlg("IceWM Control Panel Plus\nVersion 1.0\nA graphical configuration tool for IceWM",
        false, Gtk::MESSAGE_INFO);
    dlg.run();
}

void setupMenu(Gtk::MenuBar* menubar) {
    auto* helpItem = Gtk::manage(new Gtk::MenuItem("_Help", true));
    auto* helpMenu = Gtk::manage(new Gtk::Menu());
    
    auto* icehelpItem = Gtk::manage(new Gtk::MenuItem("_IceHelp", true));
    icehelpItem->signal_activate().connect(sigc::ptr_fun(on_icehelp));
    helpMenu->append(*icehelpItem);
    
    auto* aboutItem = Gtk::manage(new Gtk::MenuItem("_About", true));
    aboutItem->signal_activate().connect(sigc::ptr_fun(on_about));
    helpMenu->append(*aboutItem);
    
    helpItem->set_submenu(*helpMenu);
    menubar->append(*helpItem);
}

} // namespace Help
} // namespace TopMenuBar