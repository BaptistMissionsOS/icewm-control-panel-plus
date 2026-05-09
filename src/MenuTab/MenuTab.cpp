#include "MenuTab.h"
#include <gtkmm/messagedialog.h>
#include <fstream>

MenuTab::MenuTab(const std::string& configDir) : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5), configDir(configDir) {
    set_margin_left(10);
    set_margin_top(10);
    
    auto* title = Gtk::manage(new Gtk::Label());
    title->set_markup("<b>Menu Configuration</b>");
    title->set_halign(Gtk::ALIGN_START);
    pack_start(*title, Gtk::PACK_SHRINK);
    
    auto* hbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    
    treeStore = Gtk::TreeStore::create(cols);
    treeView = Gtk::manage(new Gtk::TreeView(treeStore));
    
    // Configure tree view appearance
    treeView->append_column("Name", cols.name);
    treeView->get_column(0)->set_expand(true);
    treeView->get_column(0)->set_sizing(Gtk::TREE_VIEW_COLUMN_AUTOSIZE);
    treeView->set_headers_visible(false);
    treeView->set_enable_tree_lines(true);
    treeView->set_grid_lines(Gtk::TREE_VIEW_GRID_LINES_HORIZONTAL);
    treeView->set_rules_hint(true);
    treeView->set_show_expanders(true);
    treeView->set_level_indentation(12);
    treeView->get_selection()->set_mode(Gtk::SELECTION_SINGLE);
    treeView->set_activate_on_single_click(false);
    
    // Add CSS styling for better appearance
    auto cssProvider = Gtk::CssProvider::create();
    cssProvider->load_from_data(
        "treeview {\n"
        "  -GtkTreeView-grid-line-width: 1px;\n"
        "  -GtkTreeView-horizontal-separator: 8;\n"
        "  -GtkTreeView-vertical-separator: 4;\n"
        "}\n"
        "treeview row {\n"
        "  padding: 4px 8px;\n"
        "  min-height: 24px;\n"
        "}\n"
        "treeview row:selected {\n"
        "  background-color: @theme_selected_bg_color;\n"
        "  color: @theme_selected_fg_color;\n"
        "}\n"
        "treeview row:hover {\n"
        "  background-color: alpha(@theme_fg_color, 0.1);\n"
        "}\n");
    treeView->get_style_context()->add_provider(cssProvider, GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    
    auto* scrolled = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled->set_min_content_width(280);
    scrolled->set_min_content_height(350);
    scrolled->add(*treeView);
    hbox->pack_start(*scrolled, Gtk::PACK_EXPAND_WIDGET);
    
    auto* editor = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    editor->set_margin_left(10);
    
    editor->pack_start(*Gtk::manage(new Gtk::Label("Name:")), Gtk::PACK_SHRINK);
    nameEntry = Gtk::manage(new Gtk::Entry());
    editor->pack_start(*nameEntry, Gtk::PACK_SHRINK);
    
    editor->pack_start(*Gtk::manage(new Gtk::Label("Icon:")), Gtk::PACK_SHRINK);
    iconEntry = Gtk::manage(new Gtk::Entry());
    editor->pack_start(*iconEntry, Gtk::PACK_SHRINK);
    
    editor->pack_start(*Gtk::manage(new Gtk::Label("Command:")), Gtk::PACK_SHRINK);
    commandEntry = Gtk::manage(new Gtk::Entry());
    editor->pack_start(*commandEntry, Gtk::PACK_SHRINK);
    
    editor->pack_start(*Gtk::manage(new Gtk::Label("Type:")), Gtk::PACK_SHRINK);
    typeCombo = Gtk::manage(new Gtk::ComboBoxText());
    typeCombo->append("prog");
    typeCombo->append("menu");
    typeCombo->append("separator");
    typeCombo->append("restart");
    typeCombo->append("runonce");
    typeCombo->set_active(0);
    editor->pack_start(*typeCombo, Gtk::PACK_SHRINK);
    
    auto* btnBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* addBtn = Gtk::manage(new Gtk::Button("_Add", true));
    auto* removeBtn = Gtk::manage(new Gtk::Button("_Remove", true));
    auto* saveBtn = Gtk::manage(new Gtk::Button("_Save", true));
    auto* loadBtn = Gtk::manage(new Gtk::Button("_Load", true));
    auto* toolsBtn = Gtk::manage(new Gtk::Button("_Tools", true));
    btnBox->pack_start(*addBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*removeBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*saveBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*loadBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*toolsBtn, Gtk::PACK_SHRINK);
    editor->pack_start(*btnBox, Gtk::PACK_SHRINK);
    
    hbox->pack_start(*editor, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*hbox, Gtk::PACK_EXPAND_WIDGET);
    
    treeView->get_selection()->signal_changed().connect(sigc::mem_fun(*this, &MenuTab::updateInputs));
    
    addBtn->signal_clicked().connect([this]() {
        MenuEntry entry;
        entry.name = nameEntry->get_text();
        entry.icon = iconEntry->get_text();
        entry.command = commandEntry->get_text();
        entry.type = typeCombo->get_active_text();
        if (entry.name.empty() && entry.type != "separator") {
            Gtk::MessageDialog dlg("Name is required!", false, Gtk::MESSAGE_WARNING); dlg.run(); return;
        }
        menuEntries.push_back(entry);
        updateTree();
    });
    
    removeBtn->signal_clicked().connect([this]() {
        auto sel = treeView->get_selection()->get_selected();
        if (sel) {
            Gtk::TreePath path = treeStore->get_path(sel);
            if (path.size() == 1) {
                int idx = path[0];
                if (idx >= 0 && idx < (int)menuEntries.size()) { menuEntries.erase(menuEntries.begin() + idx); updateTree(); }
            }
        }
    });
    
    saveBtn->signal_clicked().connect(sigc::mem_fun(*this, &MenuTab::saveMenuFile));
    loadBtn->signal_clicked().connect(sigc::mem_fun(*this, &MenuTab::loadMenuFile));
    toolsBtn->signal_clicked().connect([]() {
        Gtk::MessageDialog dlg("Menu Tools: Use the command line tools icewm-menu-fdo to scan desktop files.", false, Gtk::MESSAGE_INFO);
        dlg.run();
    });
    
    loadMenuFile();
}

void MenuTab::loadMenuFile() {
    menuEntries.clear();
    std::ifstream file(configDir + "/menu");
    if (!file.is_open()) file.open("/usr/share/icewm/menu");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty() || line[0] == '#') continue;
            std::istringstream iss(line);
            std::string type; iss >> type;
            MenuEntry entry; entry.type = type;
            if (type == "prog" || type == "runonce") {
                std::string name, icon, cmd;
                std::getline(iss, name, '"'); std::getline(iss, name, '"');
                std::getline(iss, icon, '"'); std::getline(iss, icon, '"');
                std::getline(iss, cmd);
                if (!cmd.empty() && cmd[0] == ' ') cmd = cmd.substr(1);
                entry.name = name; entry.icon = icon; entry.command = cmd;
            } else if (type == "menu") {
                std::string name, icon;
                std::getline(iss, name, '"'); std::getline(iss, name, '"');
                std::getline(iss, icon, '"'); std::getline(iss, icon, '"');
                entry.name = name; entry.icon = icon;
            } else if (type == "separator") {
                entry.name = "---";
            } else if (type == "restart") {
                std::string name, icon, cmd;
                std::getline(iss, name, '"'); std::getline(iss, name, '"');
                std::getline(iss, icon, '"'); std::getline(iss, icon, '"');
                std::getline(iss, cmd);
                entry.name = name; entry.icon = icon; entry.command = cmd;
            }
            menuEntries.push_back(entry);
        }
    }
    updateTree();
}

void MenuTab::saveMenuFile() {
    std::ofstream file(configDir + "/menu");
    if (file.is_open()) {
        file << "# IceWM Menu\n";
        for (const auto& entry : menuEntries) {
            if (entry.type == "separator") { file << "separator\n"; continue; }
            if (entry.type == "prog") file << "prog \"" << entry.name << "\" \"" << entry.icon << "\" " << entry.command << "\n";
            else if (entry.type == "runonce") file << "runonce \"" << entry.name << "\" \"" << entry.icon << "\" " << entry.command << "\n";
            else if (entry.type == "menu") file << "menu \"" << entry.name << "\" \"" << entry.icon << "\" {\n}\n";
            else if (entry.type == "restart") file << "restart \"" << entry.name << "\" \"" << entry.icon << "\" " << entry.command << "\n";
        }
        file.close();
        Gtk::MessageDialog dlg("Menu saved!", false, Gtk::MESSAGE_INFO); dlg.run();
    } else {
        Gtk::MessageDialog dlg("Failed to save menu!", false, Gtk::MESSAGE_ERROR); dlg.run();
    }
}

void MenuTab::updateTree() {
    treeStore->clear();
    for (const auto& entry : menuEntries) {
        auto row = *treeStore->append();
        row[cols.name] = entry.name.empty() ? entry.type : entry.name;
        row[cols.type] = entry.type;
    }
}

void MenuTab::updateInputs() {
    auto sel = treeView->get_selection()->get_selected();
    if (!sel) return;
    Gtk::TreePath path = treeStore->get_path(sel);
    if (path.size() == 1) {
        int idx = path[0];
        if (idx >= 0 && idx < (int)menuEntries.size()) {
            const auto& entry = menuEntries[idx];
            nameEntry->set_text(entry.name);
            iconEntry->set_text(entry.icon);
            commandEntry->set_text(entry.command);
            for (int i = 0; i < 5; i++) { typeCombo->set_active(i); if (typeCombo->get_active_text() == entry.type) break; }
        }
    }
}

void MenuTab::refresh() { loadMenuFile(); }
