#include "StartupTab.h"
#include <gtkmm/messagedialog.h>
#include <fstream>

StartupTab::StartupTab(const std::string& configDir) : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5), configDir(configDir) {
    set_margin_left(10);
    set_margin_top(10);
    
    auto* title = Gtk::manage(new Gtk::Label());
    title->set_markup("<b>Startup Commands</b>");
    title->set_halign(Gtk::ALIGN_START);
    pack_start(*title, Gtk::PACK_SHRINK);
    
    auto* hbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    
    listStore = Gtk::ListStore::create(cols);
    treeView = Gtk::manage(new Gtk::TreeView(listStore));
    treeView->append_column("Command", cols.name);
    treeView->set_headers_visible(false);
    auto* scrolled = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled->set_min_content_width(200);
    scrolled->add(*treeView);
    hbox->pack_start(*scrolled, Gtk::PACK_SHRINK);
    
    auto* editor = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    editor->set_margin_left(10);
    
    editor->pack_start(*Gtk::manage(new Gtk::Label("Command:")), Gtk::PACK_SHRINK);
    commandEntry = Gtk::manage(new Gtk::Entry());
    commandEntry->set_tooltip_text("Command to run at startup");
    editor->pack_start(*commandEntry, Gtk::PACK_SHRINK);
    
    editor->pack_start(*Gtk::manage(new Gtk::Label("Description:")), Gtk::PACK_SHRINK);
    descriptionEntry = Gtk::manage(new Gtk::Entry());
    editor->pack_start(*descriptionEntry, Gtk::PACK_SHRINK);
    
    enabledCheck = Gtk::manage(new Gtk::CheckButton("Enabled"));
    enabledCheck->set_active(true);
    editor->pack_start(*enabledCheck, Gtk::PACK_SHRINK);
    
    auto* btnBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* addBtn = Gtk::manage(new Gtk::Button("_Add", true));
    auto* removeBtn = Gtk::manage(new Gtk::Button("_Remove", true));
    auto* upBtn = Gtk::manage(new Gtk::Button("_Up", true));
    auto* downBtn = Gtk::manage(new Gtk::Button("_Down", true));
    auto* saveBtn = Gtk::manage(new Gtk::Button("_Save", true));
    auto* loadBtn = Gtk::manage(new Gtk::Button("_Load", true));
    btnBox->pack_start(*addBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*removeBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*upBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*downBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*saveBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*loadBtn, Gtk::PACK_SHRINK);
    editor->pack_start(*btnBox, Gtk::PACK_SHRINK);
    
    hbox->pack_start(*editor, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*hbox, Gtk::PACK_EXPAND_WIDGET);
    
    treeView->get_selection()->signal_changed().connect(sigc::mem_fun(*this, &StartupTab::updateInputs));
    
    addBtn->signal_clicked().connect([this]() {
        StartupCommand cmd;
        cmd.command = commandEntry->get_text();
        cmd.description = descriptionEntry->get_text();
        cmd.enabled = enabledCheck->get_active();
        if (cmd.command.empty()) { Gtk::MessageDialog dlg("Command is required!", false, Gtk::MESSAGE_WARNING); dlg.run(); return; }
        startupCommands.push_back(cmd);
        updateList();
    });
    
    removeBtn->signal_clicked().connect([this]() {
        auto sel = treeView->get_selection()->get_selected();
        if (sel) { int idx = listStore->get_path(sel)[0]; startupCommands.erase(startupCommands.begin() + idx); updateList(); commandEntry->set_text(""); descriptionEntry->set_text(""); }
    });
    
    upBtn->signal_clicked().connect([this]() {
        auto sel = treeView->get_selection()->get_selected();
        if (!sel) return; int idx = listStore->get_path(sel)[0];
        if (idx > 0) { std::swap(startupCommands[idx], startupCommands[idx-1]); updateList(); treeView->get_selection()->select(Gtk::TreePath(std::to_string(idx-1))); }
    });
    
    downBtn->signal_clicked().connect([this]() {
        auto sel = treeView->get_selection()->get_selected();
        if (!sel) return; int idx = listStore->get_path(sel)[0];
        if (idx < (int)startupCommands.size()-1) { std::swap(startupCommands[idx], startupCommands[idx+1]); updateList(); treeView->get_selection()->select(Gtk::TreePath(std::to_string(idx+1))); }
    });
    
    saveBtn->signal_clicked().connect(sigc::mem_fun(*this, &StartupTab::saveStartupFile));
    loadBtn->signal_clicked().connect(sigc::mem_fun(*this, &StartupTab::loadStartupFile));
    
    loadStartupFile();
}

void StartupTab::loadStartupFile() {
    startupCommands.clear();
    std::ifstream file(configDir + "/startup");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (line.empty() || line[0] == '#') continue;
            StartupCommand cmd; cmd.enabled = true;
            if (line.substr(0, 4) == "#\t" || (line.length() > 1 && line[0] == '#' && line[1] != '!')) {
                cmd.enabled = false;
                size_t f = line.find_first_not_of("#\t "); if (f != std::string::npos) line = line.substr(f);
            }
            cmd.command = line;
            size_t cp = line.find('#');
            if (cp != std::string::npos && cp > 0) {
                cmd.description = line.substr(cp + 1);
                cmd.command = line.substr(0, cp);
                size_t end = cmd.command.find_last_not_of(" \t");
                if (end != std::string::npos) cmd.command = cmd.command.substr(0, end + 1);
            }
            startupCommands.push_back(cmd);
        }
    }
    updateList();
}

void StartupTab::saveStartupFile() {
    std::ofstream file(configDir + "/startup");
    if (file.is_open()) {
        file << "#!/bin/bash\n# IceWM startup script\n# Generated by IceWM Control Panel Plus\n\n";
        for (const auto& cmd : startupCommands) {
            if (!cmd.enabled) file << "# ";
            file << cmd.command;
            if (!cmd.description.empty()) file << "  # " << cmd.description;
            file << "\n";
        }
        file.close();
        chmod((configDir + "/startup").c_str(), 0755);
        Gtk::MessageDialog dlg("Startup script saved!", false, Gtk::MESSAGE_INFO); dlg.run();
    } else {
        Gtk::MessageDialog dlg("Failed to save startup file!", false, Gtk::MESSAGE_ERROR); dlg.run();
    }
}

void StartupTab::updateList() {
    listStore->clear();
    for (const auto& cmd : startupCommands) {
        auto row = *listStore->append();
        row[cols.name] = std::string(cmd.enabled ? "[✓] " : "[ ] ") + cmd.command + (cmd.description.empty() ? "" : " - " + cmd.description);
    }
}

void StartupTab::updateInputs() {
    auto sel = treeView->get_selection()->get_selected();
    if (!sel) return;
    int idx = listStore->get_path(sel)[0];
    if (idx >= 0 && idx < (int)startupCommands.size()) {
        const auto& cmd = startupCommands[idx];
        commandEntry->set_text(cmd.command);
        descriptionEntry->set_text(cmd.description);
        enabledCheck->set_active(cmd.enabled);
    }
}

void StartupTab::refresh() { loadStartupFile(); }
