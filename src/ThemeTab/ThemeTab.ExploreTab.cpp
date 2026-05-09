#include "ThemeTab.ExploreTab.h"
#include <gtkmm/messagedialog.h>
#include <dirent.h>
#include <sys/stat.h>
#include <fstream>

ExploreTab::ExploreTab(const std::string& configDir) : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5), configDir(configDir) {
    set_margin_left(10);
    set_margin_top(10);
    
    auto* title = Gtk::manage(new Gtk::Label());
    title->set_markup("<b>Theme Explorer</b>");
    title->set_halign(Gtk::ALIGN_START);
    pack_start(*title, Gtk::PACK_SHRINK);
    
    auto* hbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    
    // Left: Theme list
    auto* leftFrame = Gtk::manage(new Gtk::Frame("Available Themes"));
    auto* leftBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    leftBox->set_margin_left(5);
    leftBox->set_margin_top(5);
    leftBox->set_margin_bottom(5);
    
    listStore = Gtk::ListStore::create(cols);
    treeView = Gtk::manage(new Gtk::TreeView(listStore));
    treeView->append_column("Theme", cols.name);
    treeView->append_column("Location", cols.path);
    treeView->set_headers_visible(true);
    treeView->get_selection()->signal_changed().connect(sigc::mem_fun(*this, &ExploreTab::onSelectionChanged));
    
    auto* scrolled = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled->set_min_content_width(300);
    scrolled->set_min_content_height(300);
    scrolled->add(*treeView);
    leftBox->pack_start(*scrolled, Gtk::PACK_EXPAND_WIDGET);
    
    // Filter buttons
    auto* filterBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 3));
    auto* allBtn = Gtk::manage(new Gtk::Button("All"));
    auto* userBtn = Gtk::manage(new Gtk::Button("User"));
    auto* sysBtn = Gtk::manage(new Gtk::Button("System"));
    filterBox->pack_start(*allBtn, Gtk::PACK_SHRINK);
    filterBox->pack_start(*userBtn, Gtk::PACK_SHRINK);
    filterBox->pack_start(*sysBtn, Gtk::PACK_SHRINK);
    leftBox->pack_start(*filterBox, Gtk::PACK_SHRINK);
    
    leftFrame->add(*leftBox);
    hbox->pack_start(*leftFrame, Gtk::PACK_EXPAND_WIDGET);
    
    // Right: Details
    auto* rightFrame = Gtk::manage(new Gtk::Frame("Theme Details"));
    auto* rightBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    rightBox->set_margin_left(5);
    rightBox->set_margin_top(5);
    rightBox->set_margin_bottom(5);
    
    detailsView = Gtk::manage(new Gtk::TextView());
    detailsView->set_editable(false);
    detailsView->set_wrap_mode(Gtk::WRAP_WORD);
    auto* detailsScroll = Gtk::manage(new Gtk::ScrolledWindow());
    detailsScroll->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    detailsScroll->set_min_content_width(250);
    detailsScroll->set_min_content_height(200);
    detailsScroll->add(*detailsView);
    rightBox->pack_start(*detailsScroll, Gtk::PACK_EXPAND_WIDGET);
    
    // Action buttons
    auto* btnBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* installBtn = Gtk::manage(new Gtk::Button("_Install", true));
    auto* deleteBtn = Gtk::manage(new Gtk::Button("_Delete", true));
    auto* refreshBtn = Gtk::manage(new Gtk::Button("_Refresh", true));
    btnBox->pack_start(*installBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*deleteBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*refreshBtn, Gtk::PACK_SHRINK);
    rightBox->pack_start(*btnBox, Gtk::PACK_SHRINK);
    
    installBtn->signal_clicked().connect(sigc::mem_fun(*this, &ExploreTab::installTheme));
    deleteBtn->signal_clicked().connect(sigc::mem_fun(*this, &ExploreTab::deleteTheme));
    refreshBtn->signal_clicked().connect(sigc::mem_fun(*this, &ExploreTab::scanAllThemes));
    
    allBtn->signal_clicked().connect(sigc::mem_fun(*this, &ExploreTab::scanAllThemes));
    userBtn->signal_clicked().connect([this, configDir = this->configDir]() {
        // Show only user themes
        listStore->clear();
        std::string userThemes = configDir + "/themes";
        DIR* dir = opendir(userThemes.c_str());
        if (dir) {
            struct dirent* entry;
            while ((entry = readdir(dir)) != nullptr) {
                if (entry->d_name[0] == '.') continue;
                std::string name = entry->d_name;
                struct stat st;
                std::string full = userThemes + "/" + name;
                if (stat(full.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
                    auto row = *listStore->append();
                    row[cols.name] = name;
                    row[cols.path] = "~/.icewm/themes";
                }
            }
            closedir(dir);
        }
    });
    sysBtn->signal_clicked().connect([this]() {
        // Show only system themes
        listStore->clear();
        std::vector<std::string> dirs = {"/usr/share/icewm/themes", "/usr/local/share/icewm/themes"};
        for (const auto& d : dirs) {
            DIR* dir = opendir(d.c_str());
            if (dir) {
                struct dirent* entry;
                while ((entry = readdir(dir)) != nullptr) {
                    if (entry->d_name[0] == '.') continue;
                    std::string name = entry->d_name;
                    struct stat st;
                    std::string full = d + "/" + name;
                    if (stat(full.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
                        auto row = *listStore->append();
                        row[cols.name] = name;
                        row[cols.path] = d;
                    }
                }
                closedir(dir);
            }
        }
    });
    
    rightFrame->add(*rightBox);
    hbox->pack_start(*rightFrame, Gtk::PACK_EXPAND_WIDGET);
    
    pack_start(*hbox, Gtk::PACK_EXPAND_WIDGET);
    
    scanAllThemes();
}

void ExploreTab::scanAllThemes() {
    listStore->clear();
    
    std::vector<std::pair<std::string, std::string>> locations = {
        {configDir + "/themes", "~/.icewm/themes"},
        {"/usr/share/icewm/themes", "/usr/share/icewm/themes"},
        {"/usr/local/share/icewm/themes", "/usr/local/share/icewm/themes"}
    };
    
    for (const auto& [dirPath, label] : locations) {
        DIR* dir = opendir(dirPath.c_str());
        if (dir) {
            struct dirent* entry;
            while ((entry = readdir(dir)) != nullptr) {
                if (entry->d_name[0] == '.') continue;
                std::string name = entry->d_name;
                struct stat st;
                std::string full = dirPath + "/" + name;
                if (stat(full.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
                    auto row = *listStore->append();
                    row[cols.name] = name;
                    row[cols.path] = label;
                }
            }
            closedir(dir);
        }
    }
}

void ExploreTab::onSelectionChanged() {
    auto sel = treeView->get_selection()->get_selected();
    if (!sel) return;
    
    Glib::ustring name = sel->get_value(cols.name);
    Glib::ustring path = sel->get_value(cols.path);
    
    std::string fullPath;
    if (path == "~/.icewm/themes") {
        fullPath = configDir + "/themes/" + name;
    } else {
        fullPath = path + "/" + name;
    }
    
    // Read theme description
    std::string info = "Theme: " + name + "\n";
    info += "Location: " + fullPath + "\n\n";
    
    // Check for theme files
    std::ifstream pref(fullPath + "/default.theme");
    if (pref.is_open()) {
        info += "Contains: default.theme\n";
        std::string line;
        while (std::getline(pref, line)) {
            if (line.find("ThemeDescription=") == 0) {
                info += "Description: " + line.substr(17) + "\n";
            }
        }
        pref.close();
    }
    
    struct stat st;
    if (stat((fullPath + "/taskbar").c_str(), &st) == 0) {
        info += "Contains: taskbar pixmaps\n";
    }
    if (stat((fullPath + "/titlebar").c_str(), &st) == 0) {
        info += "Contains: titlebar pixmaps\n";
    }
    if (stat((fullPath + "/menu").c_str(), &st) == 0) {
        info += "Contains: menu pixmaps\n";
    }
    
    detailsView->get_buffer()->set_text(info);
}

void ExploreTab::installTheme() {
    Gtk::FileChooserDialog dialog("Select Theme Archive or Directory", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    dialog.set_transient_for(*dynamic_cast<Gtk::Window*>(get_toplevel()));
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Install", Gtk::RESPONSE_OK);
    
    if (dialog.run() == Gtk::RESPONSE_OK) {
        std::string src = dialog.get_filename();
        std::string dest = configDir + "/themes/" + Glib::path_get_basename(src);
        
        // Simple copy (would need proper implementation with recursive copy)
        Gtk::MessageDialog dlg("Theme would be installed from:\n" + src + "\nto:\n" + dest, false, Gtk::MESSAGE_INFO);
        dlg.run();
        scanAllThemes();
    }
}

void ExploreTab::deleteTheme() {
    auto sel = treeView->get_selection()->get_selected();
    if (!sel) {
        Gtk::MessageDialog dlg("Select a theme to delete", false, Gtk::MESSAGE_WARNING);
        dlg.run();
        return;
    }
    
    Glib::ustring name = sel->get_value(cols.name);
    Glib::ustring path = sel->get_value(cols.path);
    
    // Only allow deleting user themes
    if (path.find("/usr/") == 0) {
        Gtk::MessageDialog dlg("Cannot delete system themes!", false, Gtk::MESSAGE_ERROR);
        dlg.run();
        return;
    }
    
    Gtk::MessageDialog dlg("Delete theme '" + name + "'?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
    if (dlg.run() == Gtk::RESPONSE_YES) {
        std::string fullPath = configDir + "/themes/" + name;
        // Would need recursive delete here
        Gtk::MessageDialog info("Theme deleted (simulated)", false, Gtk::MESSAGE_INFO);
        info.run();
        scanAllThemes();
    }
}

void ExploreTab::refresh() {
    scanAllThemes();
}
