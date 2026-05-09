#include "IceWM.h"
#include <gtkmm/messagedialog.h>
#include <cstdlib>
#include <string>
#include <sys/stat.h>
#include <dirent.h>
#include <ctime>
#include <cstring>
#include <fstream>

namespace TopMenuBar {
namespace IceWM {

void icesh_run(const std::string& cmd) {
    std::string fullCmd = std::string("icesh ") + cmd;
    int ret = system(fullCmd.c_str());
    if (ret != 0) {
        Gtk::MessageDialog dlg("Failed to run: icesh " + cmd, false, Gtk::MESSAGE_ERROR);
        dlg.run();
    }
}

static bool confirm_action(const Glib::ustring& msg) {
    Gtk::MessageDialog dlg(msg, false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
    return dlg.run() == Gtk::RESPONSE_YES;
}

void setupMenu(Gtk::MenuBar* menubar) {
    auto* icewmItem = Gtk::manage(new Gtk::MenuItem("_IceWM", true));
    auto* icewmMenu = Gtk::manage(new Gtk::Menu());
    
    auto addMenuItem = [&](const Glib::ustring& label, const std::string& cmd) {
        auto* item = Gtk::manage(new Gtk::MenuItem(label, true));
        item->signal_activate().connect([cmd]() { icesh_run(cmd); });
        icewmMenu->append(*item);
    };
    
    addMenuItem("List _Windows", "list");
    addMenuItem("_Activate Window", "activate");
    icewmMenu->append(*Gtk::manage(new Gtk::SeparatorMenuItem()));
    
    // Window submenu
    auto* windowItem = Gtk::manage(new Gtk::MenuItem("_Window", true));
    auto* windowMenu = Gtk::manage(new Gtk::Menu());
    auto addWinItem = [&](const Glib::ustring& label, const std::string& cmd) {
        auto* item = Gtk::manage(new Gtk::MenuItem(label, true));
        item->signal_activate().connect([cmd]() { icesh_run(cmd); });
        windowMenu->append(*item);
    };
    addWinItem("_Close", "close"); addWinItem("_Kill", "kill");
    addWinItem("Minimi_ze", "minimize"); addWinItem("Maximi_ze", "maximize");
    addWinItem("_Restore", "restore"); addWinItem("_Raise", "raised");
    addWinItem("_Lower", "lowered"); addWinItem("_Fullscreen", "fullscreen");
    windowItem->set_submenu(*windowMenu);
    icewmMenu->append(*windowItem);
    
    // Workspace submenu
    auto* wsItem = Gtk::manage(new Gtk::MenuItem("_Workspace", true));
    auto* wsMenu = Gtk::manage(new Gtk::Menu());
    auto addWsItem = [&](const Glib::ustring& label, const std::string& cmd) {
        auto* item = Gtk::manage(new Gtk::MenuItem(label, true));
        item->signal_activate().connect([cmd]() { icesh_run(cmd); });
        wsMenu->append(*item);
    };
    addWsItem("_Next", "nextWorkspace"); addWsItem("_Previous", "prevWorkspace");
    addWsItem("_Sysinfo", "sysinfo");
    wsItem->set_submenu(*wsMenu);
    icewmMenu->append(*wsItem);
    
    // System submenu
    auto* sysItem = Gtk::manage(new Gtk::MenuItem("S_ystem", true));
    auto* sysMenu = Gtk::manage(new Gtk::Menu());
    auto* checkItem = Gtk::manage(new Gtk::MenuItem("Check IceWM", true));
    checkItem->signal_activate().connect([]() {
        int ret = system("pgrep -x icewm > /dev/null 2>&1");
        Gtk::MessageDialog dlg(ret == 0 ? "IceWM is currently running" : "IceWM is not running",
            false, ret == 0 ? Gtk::MESSAGE_INFO : Gtk::MESSAGE_WARNING);
        dlg.run();
    });
    sysMenu->append(*checkItem);
    auto* restartItem = Gtk::manage(new Gtk::MenuItem("_Restart IceWM", true));
    restartItem->signal_activate().connect([]() { if (confirm_action("Restart IceWM?")) icesh_run("restart"); });
    sysMenu->append(*restartItem);
    auto* logoutItem = Gtk::manage(new Gtk::MenuItem("Log_out", true));
    logoutItem->signal_activate().connect([]() { if (confirm_action("Logout?")) icesh_run("logout"); });
    sysMenu->append(*logoutItem);
    sysMenu->append(*Gtk::manage(new Gtk::SeparatorMenuItem()));
    auto* rebootItem = Gtk::manage(new Gtk::MenuItem("Re_boot", true));
    rebootItem->signal_activate().connect([]() { if (confirm_action("Reboot system?")) icesh_run("reboot"); });
    sysMenu->append(*rebootItem);
    auto* shutdownItem = Gtk::manage(new Gtk::MenuItem("_Shutdown", true));
    shutdownItem->signal_activate().connect([]() { if (confirm_action("Shutdown system?")) icesh_run("shutdown"); });
    sysMenu->append(*shutdownItem);
    sysItem->set_submenu(*sysMenu);
    icewmMenu->append(*sysItem);
    
    // Tools submenu
    auto* toolsItem = Gtk::manage(new Gtk::MenuItem("_Tools", true));
    auto* toolsMenu = Gtk::manage(new Gtk::Menu());
    auto* themesItem = Gtk::manage(new Gtk::MenuItem("_Themes...", true));
    themesItem->signal_activate().connect([]() { system("xterm -e 'icewm --list-themes; echo \"Press Enter to close...\"; read' &"); });
    toolsMenu->append(*themesItem);
    auto* prefsItem = Gtk::manage(new Gtk::MenuItem("_Preferences...", true));
    prefsItem->signal_activate().connect([]() { system("xterm -e 'icewm --postpreferences | less' &"); });
    toolsMenu->append(*prefsItem);
    auto* dirsItem = Gtk::manage(new Gtk::MenuItem("_Directories...", true));
    dirsItem->signal_activate().connect([]() { system("xterm -e 'icewm --directories; echo \"Press Enter to close...\"; read' &"); });
    toolsMenu->append(*dirsItem);
    toolsMenu->append(*Gtk::manage(new Gtk::SeparatorMenuItem()));
    auto* backupItem = Gtk::manage(new Gtk::MenuItem("_Backup Manager...", true));
    backupItem->signal_activate().connect([]() { backup_manager_dialog(false); });
    toolsMenu->append(*backupItem);
    toolsMenu->append(*Gtk::manage(new Gtk::SeparatorMenuItem()));
    auto* shellItem = Gtk::manage(new Gtk::MenuItem("_Shell...", true));
    shellItem->signal_activate().connect([]() { shell_cmd_dialog(); });
    toolsMenu->append(*shellItem);
    toolsItem->set_submenu(*toolsMenu);
    icewmMenu->append(*toolsItem);
    
    icewmItem->set_submenu(*icewmMenu);
    menubar->append(*icewmItem);
}

void backup_manager_dialog(bool themeOnly) {
    const char* home = getenv("HOME");
    if (!home) return;
    std::string configDir = std::string(home) + "/.icewm";
    std::string backupDir = configDir + "/backups";
    system(("mkdir -p \"" + backupDir + "\"").c_str());
    
    Gtk::Dialog dlg(themeOnly ? "Theme Backup Manager" : "IceWM Backup Manager", true);
    dlg.set_default_size(550, 400);
    dlg.add_button("_Close", Gtk::RESPONSE_CLOSE);
    
    auto* content = dlg.get_content_area();
    auto* title = Gtk::manage(new Gtk::Label());
    title->set_markup("<b>" + Glib::ustring(themeOnly ? "Theme Backup Manager" : "IceWM Backup Manager") + "</b>");
    content->pack_start(*title, Gtk::PACK_SHRINK);
    
    // List store for backups
    class BackupColumns : public Gtk::TreeModelColumnRecord {
    public:
        Gtk::TreeModelColumn<Glib::ustring> name;
        BackupColumns() { add(name); }
    };
    BackupColumns cols;
    Glib::RefPtr<Gtk::ListStore> listStore = Gtk::ListStore::create(cols);
    
    auto* treeView = Gtk::manage(new Gtk::TreeView(listStore));
    treeView->append_column("Backup", cols.name);
    treeView->set_headers_visible(false);
    
    DIR* dir = opendir(backupDir.c_str());
    if (dir) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_name[0] == '.') continue;
            std::string name = entry->d_name;
            if (name.find(".tar.gz") != std::string::npos) {
                bool isThemeBackup = (name.find("_backup_") != std::string::npos &&
                                     name.find("icewm_config_backup_") == std::string::npos);
                if (!themeOnly || isThemeBackup) {
                    auto row = *listStore->append();
                    row[cols.name] = name;
                }
            }
        }
        closedir(dir);
    }
    
    auto* scrolled = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled->set_min_content_height(250);
    scrolled->add(*treeView);
    content->pack_start(*scrolled, Gtk::PACK_EXPAND_WIDGET);
    
    auto* btnBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* createBtn = Gtk::manage(new Gtk::Button("_Create", true));
    auto* restoreBtn = Gtk::manage(new Gtk::Button("_Restore", true));
    auto* deleteBtn = Gtk::manage(new Gtk::Button("_Delete", true));
    btnBox->pack_start(*createBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*restoreBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*deleteBtn, Gtk::PACK_SHRINK);
    content->pack_start(*btnBox, Gtk::PACK_SHRINK);
    
    createBtn->signal_clicked().connect([&, configDir, backupDir, themeOnly]() {
        time_t now = time(nullptr);
        char timestamp[64];
        strftime(timestamp, sizeof(timestamp), "%Y%m%d_%H%M%S", localtime(&now));
        std::string backupName, cmd;
        if (themeOnly) {
            std::ifstream file(configDir + "/theme");
            std::string currentTheme;
            if (file.is_open()) { std::getline(file, currentTheme); file.close(); }
            if (currentTheme.empty()) {
                Gtk::MessageDialog e("No theme selected!", false, Gtk::MESSAGE_ERROR); e.run(); return;
            }
            backupName = currentTheme + "_backup_" + std::string(timestamp) + ".tar.gz";
            cmd = "cd \"" + configDir + "/themes/" + currentTheme + "\" && tar -czf \"" + backupDir + "/" + backupName + "\" .";
        } else {
            backupName = "icewm_config_backup_" + std::string(timestamp) + ".tar.gz";
            cmd = "cd \"" + configDir + "/..\" && tar -czf \"" + backupDir + "/" + backupName + "\" $(basename \"" + configDir + "\")";
        }
        if (system(cmd.c_str()) == 0) {
            auto row = *listStore->append(); row[cols.name] = backupName;
            Gtk::MessageDialog m("Backup created: " + backupName, false, Gtk::MESSAGE_INFO); m.run();
        } else {
            Gtk::MessageDialog e("Failed to create backup!", false, Gtk::MESSAGE_ERROR); e.run();
        }
    });
    
    restoreBtn->signal_clicked().connect([&, configDir, backupDir, themeOnly]() {
        auto sel = treeView->get_selection();
        if (!sel->get_selected()) {
            Gtk::MessageDialog w("Please select a backup!", false, Gtk::MESSAGE_WARNING); w.run(); return;
        }
        std::string backupName = sel->get_selected()->get_value(cols.name);
        std::string backupPath = backupDir + "/" + backupName;
        bool isThemeBackup = (backupName.find("_backup_") != std::string::npos &&
                             backupName.find("icewm_config_backup_") == std::string::npos);
        if (themeOnly && !isThemeBackup) {
            Gtk::MessageDialog w("This is not a theme backup!", false, Gtk::MESSAGE_WARNING); w.run(); return;
        }
        if (isThemeBackup) {
            std::string themeName = backupName;
            size_t bp = themeName.find("_backup_"); if (bp != std::string::npos) themeName = themeName.substr(0, bp);
            bp = themeName.find(".tar.gz"); if (bp != std::string::npos) themeName = themeName.substr(0, bp);
            Gtk::Dialog nameDlg("Restore Theme", true);
            nameDlg.add_button("Cancel", Gtk::RESPONSE_CANCEL);
            nameDlg.add_button("Restore", Gtk::RESPONSE_OK);
            auto* entry = Gtk::manage(new Gtk::Entry()); entry->set_text(themeName);
            nameDlg.get_content_area()->pack_start(*entry);
            nameDlg.show_all_children();
            if (nameDlg.run() != Gtk::RESPONSE_OK) return;
            themeName = entry->get_text();
            std::string themeDir = configDir + "/themes/" + themeName;
            struct stat st;
            if (stat(themeDir.c_str(), &st) == 0) {
                Gtk::MessageDialog c("Theme '" + themeName + "' exists. Overwrite?",
                    false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
                if (c.run() != Gtk::RESPONSE_YES) return;
            }
            system(("mkdir -p \"" + themeDir + "\" && rm -rf \"" + themeDir + "\"/*").c_str());
            if (system(("tar -xzf \"" + backupPath + "\" -C \"" + themeDir + "\"").c_str()) == 0) {
                Gtk::MessageDialog m("Theme restored!", false, Gtk::MESSAGE_INFO); m.run();
            } else {
                Gtk::MessageDialog e("Failed to restore!", false, Gtk::MESSAGE_ERROR); e.run();
            }
        } else {
            Gtk::MessageDialog c("Restore entire config from '" + backupName + "'?\nCurrent settings will be overwritten.",
                false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
            if (c.run() != Gtk::RESPONSE_YES) return;
            if (system(("tar -xzf \"" + backupPath + "\" -C \"" + configDir + "/..\"").c_str()) == 0) {
                Gtk::MessageDialog m("Config restored!", false, Gtk::MESSAGE_INFO); m.run();
            } else {
                Gtk::MessageDialog e("Failed to restore!", false, Gtk::MESSAGE_ERROR); e.run();
            }
        }
    });
    
    deleteBtn->signal_clicked().connect([&, backupDir]() {
        auto sel = treeView->get_selection();
        if (!sel->get_selected()) return;
        std::string backupName = sel->get_selected()->get_value(cols.name);
        Gtk::MessageDialog c("Delete '" + backupName + "'?",
            false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
        if (c.run() == Gtk::RESPONSE_YES) {
            if (::remove((backupDir + "/" + backupName).c_str()) == 0)
                listStore->erase(sel->get_selected());
        }
    });
    
    dlg.show_all_children();
    dlg.run();
}

void shell_cmd_dialog() {
    Gtk::Dialog dlg("IceWM Command Center", true);
    dlg.set_default_size(500, 200);
    dlg.add_button("_Close", Gtk::RESPONSE_CLOSE);
    dlg.add_button("_Run", Gtk::RESPONSE_OK);
    
    auto* content = dlg.get_content_area();
    auto* box = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    
    auto* cmdEntry = Gtk::manage(new Gtk::Entry());
    cmdEntry->set_placeholder_text("Enter icesh command (e.g., list, close, minimize)");
    box->pack_start(*Gtk::manage(new Gtk::Label("Command:")), Gtk::PACK_SHRINK);
    box->pack_start(*cmdEntry, Gtk::PACK_SHRINK);
    
    auto* combo = Gtk::manage(new Gtk::ComboBoxText());
    combo->append("", "-- Select command --");
    const char* cmds[] = {
        "list", "activate", "close", "kill", "minimize", "maximize", "restore",
        "raise", "lower", "fullscreen", "nextWorkspace", "prevWorkspace",
        "logout", "reboot", "shutdown", "restart", "sysinfo", "clients",
        "windows", "shown", "workspaceNext", "workspacePrev", nullptr
    };
    for (int i = 0; cmds[i]; i++) combo->append(cmds[i], cmds[i]);
    combo->signal_changed().connect([combo, cmdEntry]() {
        Glib::ustring sel = combo->get_active_id();
        if (!sel.empty()) cmdEntry->set_text(sel);
    });
    box->pack_start(*combo, Gtk::PACK_SHRINK);
    
    content->pack_start(*box);
    dlg.show_all_children();
    
    while (dlg.run() == Gtk::RESPONSE_OK) {
        std::string cmd = cmdEntry->get_text();
        if (!cmd.empty()) icesh_run(cmd);
    }
}

} // namespace IceWM
} // namespace TopMenuBar