#include "PanelTab.h"
#include <gtkmm/messagedialog.h>
#include <fstream>

PanelTab::PanelTab(const std::string& configDir) : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5), configDir(configDir) {
    set_margin_left(10);
    set_margin_top(10);
    
    auto* title = Gtk::manage(new Gtk::Label());
    title->set_markup("<b>Panel Configuration</b>");
    title->set_halign(Gtk::ALIGN_START);
    pack_start(*title, Gtk::PACK_SHRINK);
    
    notebook = Gtk::manage(new Gtk::Notebook());
    
    // Settings tab
    auto* settingsTab = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    settingsTab->set_margin_left(10);
    settingsTab->set_margin_top(10);
    showTaskbarCheck = Gtk::manage(new Gtk::CheckButton("Show Taskbar"));
    showTaskbarCheck->set_active(true);
    settingsTab->pack_start(*showTaskbarCheck, Gtk::PACK_SHRINK);
    showToolbarCheck = Gtk::manage(new Gtk::CheckButton("Show Toolbar"));
    showToolbarCheck->set_active(true);
    settingsTab->pack_start(*showToolbarCheck, Gtk::PACK_SHRINK);
    showTrayCheck = Gtk::manage(new Gtk::CheckButton("Show System Tray"));
    showTrayCheck->set_active(true);
    settingsTab->pack_start(*showTrayCheck, Gtk::PACK_SHRINK);
    auto* hRow = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    hRow->pack_start(*Gtk::manage(new Gtk::Label("Taskbar Height:")), Gtk::PACK_SHRINK);
    auto adj = Gtk::Adjustment::create(30, 20, 80, 1);
    taskbarHeightSpin = Gtk::manage(new Gtk::SpinButton(adj, 1));
    hRow->pack_start(*taskbarHeightSpin, Gtk::PACK_SHRINK);
    settingsTab->pack_start(*hRow, Gtk::PACK_SHRINK);
    notebook->append_page(*settingsTab, "Settings");
    
    // Taskbar tab
    auto* tbTab = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    tbTab->set_margin_left(10);
    tbTab->set_margin_top(10);
    taskbarStore = Gtk::ListStore::create(tbCols);
    taskbarView = Gtk::manage(new Gtk::TreeView(taskbarStore));
    taskbarView->append_column("Item", tbCols.name);
    taskbarView->set_headers_visible(false);
    auto* tbScroll = Gtk::manage(new Gtk::ScrolledWindow());
    tbScroll->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    tbScroll->add(*taskbarView);
    tbScroll->set_min_content_height(150);
    tbTab->pack_start(*tbScroll, Gtk::PACK_EXPAND_WIDGET);
    
    auto* tbEditor = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* tbFields = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 3));
    tbNameEntry = Gtk::manage(new Gtk::Entry()); tbNameEntry->set_placeholder_text("Name");
    tbCmdEntry = Gtk::manage(new Gtk::Entry()); tbCmdEntry->set_placeholder_text("Command");
    tbIconEntry = Gtk::manage(new Gtk::Entry()); tbIconEntry->set_placeholder_text("Icon");
    tbEnabledCheck = Gtk::manage(new Gtk::CheckButton("Enabled")); tbEnabledCheck->set_active(true);
    tbFields->pack_start(*tbNameEntry, Gtk::PACK_SHRINK);
    tbFields->pack_start(*tbCmdEntry, Gtk::PACK_SHRINK);
    tbFields->pack_start(*tbIconEntry, Gtk::PACK_SHRINK);
    tbFields->pack_start(*tbEnabledCheck, Gtk::PACK_SHRINK);
    auto* tbBtns = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 3));
    auto* tbAdd = Gtk::manage(new Gtk::Button("Add"));
    auto* tbRem = Gtk::manage(new Gtk::Button("Remove"));
    tbBtns->pack_start(*tbAdd, Gtk::PACK_SHRINK);
    tbBtns->pack_start(*tbRem, Gtk::PACK_SHRINK);
    tbEditor->pack_start(*tbFields, Gtk::PACK_EXPAND_WIDGET);
    tbEditor->pack_start(*tbBtns, Gtk::PACK_SHRINK);
    tbTab->pack_start(*tbEditor, Gtk::PACK_SHRINK);
    notebook->append_page(*tbTab, "Taskbar");
    
    tbAdd->signal_clicked().connect([this]() {
        TaskbarItem item;
        item.name = tbNameEntry->get_text();
        item.command = tbCmdEntry->get_text();
        item.icon = tbIconEntry->get_text();
        item.enabled = tbEnabledCheck->get_active();
        if (item.name.empty()) return;
        taskbarItems.push_back(item);
        updateTaskbarList();
    });
    tbRem->signal_clicked().connect([this]() {
        auto sel = taskbarView->get_selection()->get_selected();
        if (sel) { int idx = taskbarStore->get_path(sel)[0]; taskbarItems.erase(taskbarItems.begin()+idx); updateTaskbarList(); }
    });
    
    // Toolbar tab
    auto* tlTab = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    tlTab->set_margin_left(10);
    tlTab->set_margin_top(10);
    toolbarStore = Gtk::ListStore::create(tlCols);
    toolbarView = Gtk::manage(new Gtk::TreeView(toolbarStore));
    toolbarView->append_column("Item", tlCols.name);
    toolbarView->set_headers_visible(false);
    auto* tlScroll = Gtk::manage(new Gtk::ScrolledWindow());
    tlScroll->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    tlScroll->add(*toolbarView);
    tlScroll->set_min_content_height(150);
    tlTab->pack_start(*tlScroll, Gtk::PACK_EXPAND_WIDGET);
    
    auto* tlEditor = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* tlFields = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 3));
    tlNameEntry = Gtk::manage(new Gtk::Entry()); tlNameEntry->set_placeholder_text("Name");
    tlCmdEntry = Gtk::manage(new Gtk::Entry()); tlCmdEntry->set_placeholder_text("Command");
    tlIconEntry = Gtk::manage(new Gtk::Entry()); tlIconEntry->set_placeholder_text("Icon");
    tlFields->pack_start(*tlNameEntry, Gtk::PACK_SHRINK);
    tlFields->pack_start(*tlCmdEntry, Gtk::PACK_SHRINK);
    tlFields->pack_start(*tlIconEntry, Gtk::PACK_SHRINK);
    auto* tlBtns = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 3));
    auto* tlAdd = Gtk::manage(new Gtk::Button("Add"));
    auto* tlRem = Gtk::manage(new Gtk::Button("Remove"));
    tlBtns->pack_start(*tlAdd, Gtk::PACK_SHRINK);
    tlBtns->pack_start(*tlRem, Gtk::PACK_SHRINK);
    tlEditor->pack_start(*tlFields, Gtk::PACK_EXPAND_WIDGET);
    tlEditor->pack_start(*tlBtns, Gtk::PACK_SHRINK);
    tlTab->pack_start(*tlEditor, Gtk::PACK_SHRINK);
    notebook->append_page(*tlTab, "Toolbar");
    
    tlAdd->signal_clicked().connect([this]() {
        ToolbarItem item;
        item.name = tlNameEntry->get_text();
        item.command = tlCmdEntry->get_text();
        item.icon = tlIconEntry->get_text();
        if (item.name.empty()) return;
        toolbarItems.push_back(item);
        updateToolbarList();
    });
    tlRem->signal_clicked().connect([this]() {
        auto sel = toolbarView->get_selection()->get_selected();
        if (sel) { int idx = toolbarStore->get_path(sel)[0]; toolbarItems.erase(toolbarItems.begin()+idx); updateToolbarList(); }
    });
    
    pack_start(*notebook, Gtk::PACK_EXPAND_WIDGET);
    
    auto* btnBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* saveBtn = Gtk::manage(new Gtk::Button("_Save", true));
    auto* loadBtn = Gtk::manage(new Gtk::Button("_Load", true));
    btnBox->pack_start(*saveBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*loadBtn, Gtk::PACK_SHRINK);
    pack_start(*btnBox, Gtk::PACK_SHRINK);
    
    saveBtn->signal_clicked().connect(sigc::mem_fun(*this, &PanelTab::savePanelConfig));
    loadBtn->signal_clicked().connect(sigc::mem_fun(*this, &PanelTab::loadPanelConfig));
    
    loadPanelConfig();
}

void PanelTab::loadPanelConfig() {
    std::ifstream file(configDir + "/preferences");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.find("TaskBarShow=") == 0) showTaskbarCheck->set_active(line.find("=1") != std::string::npos);
            else if (line.find("TaskBarShowToolbar=") == 0) showToolbarCheck->set_active(line.find("=1") != std::string::npos);
            else if (line.find("TaskBarShowTray=") == 0) showTrayCheck->set_active(line.find("=1") != std::string::npos);
            else if (line.find("TaskBarHeight=") == 0) {
                size_t eq = line.find('=');
                if (eq != std::string::npos && eq + 1 < line.length()) {
                    try {
                        int h = 0;
                        try {
                            h = std::stoi(line.substr(eq+1));
                        } catch (const std::invalid_argument&) {
                            // fallback to default height 0
                        }
                        taskbarHeightSpin->set_value(h);
                    } catch (...) { }
                }
            }
        }
    }
    // Load toolbar
    toolbarItems.clear();
    std::ifstream tb(configDir + "/toolbar");
    if (!tb.is_open()) tb.open("/usr/share/icewm/toolbar");
    if (tb.is_open()) {
        std::string line;
        while (std::getline(tb, line)) {
            if (line.empty() || line[0] == '#') continue;
            std::istringstream iss(line);
            std::string type; iss >> type;
            if (type == "prog") {
                ToolbarItem item;
                std::getline(iss, item.name, '"'); std::getline(iss, item.name, '"');
                std::getline(iss, item.icon, '"'); std::getline(iss, item.icon, '"');
                std::getline(iss, item.command);
                if (!item.command.empty() && item.command[0] == ' ') item.command = item.command.substr(1);
                toolbarItems.push_back(item);
            }
        }
    }
    updateToolbarList();
}

void PanelTab::savePanelConfig() {
    // Save toolbar
    std::ofstream tb(configDir + "/toolbar");
    if (tb.is_open()) {
        for (const auto& item : toolbarItems)
            tb << "prog \"" << item.name << "\" \"" << item.icon << "\" " << item.command << "\n";
        tb.close();
    }
    Gtk::MessageDialog dlg("Panel config saved!", false, Gtk::MESSAGE_INFO); dlg.run();
}

void PanelTab::updateTaskbarList() {
    taskbarStore->clear();
    for (const auto& item : taskbarItems) {
        auto row = *taskbarStore->append();
        row[tbCols.name] = item.name;
    }
}

void PanelTab::updateToolbarList() {
    toolbarStore->clear();
    for (const auto& item : toolbarItems) {
        auto row = *toolbarStore->append();
        row[tlCols.name] = item.name;
    }
}

void PanelTab::refresh() { loadPanelConfig(); }
