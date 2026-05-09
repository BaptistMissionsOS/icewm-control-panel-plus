#include "ProgramsTab.h"
#include <gtkmm/messagedialog.h>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <sys/stat.h>

ProgramsTab::ProgramsTab(const std::string& configDir) : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5), configDir(configDir) {
    set_margin_left(10);
    set_margin_top(10);
    
    auto* title = Gtk::manage(new Gtk::Label());
    title->set_markup("<b>Quick Launch Programs</b>");
    title->set_halign(Gtk::ALIGN_START);
    pack_start(*title, Gtk::PACK_SHRINK);
    
    auto* hbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    
    // Left: program list
    listStore = Gtk::ListStore::create(cols);
    treeView = Gtk::manage(new Gtk::TreeView(listStore));
    treeView->append_column("Program", cols.name);
    treeView->set_headers_visible(false);
    auto* scrolled = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled->set_min_content_width(200);
    scrolled->add(*treeView);
    hbox->pack_start(*scrolled, Gtk::PACK_SHRINK);
    
    // Right: editor
    auto* editor = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    editor->set_margin_left(10);
    
    auto* lbl1 = Gtk::manage(new Gtk::Label("Name:"));
    lbl1->set_halign(Gtk::ALIGN_START);
    nameEntry = Gtk::manage(new Gtk::Entry());
    nameEntry->set_hexpand(true);
    editor->pack_start(*lbl1, Gtk::PACK_SHRINK);
    editor->pack_start(*nameEntry, Gtk::PACK_SHRINK);
    
    auto* lbl2 = Gtk::manage(new Gtk::Label("Icon:"));
    lbl2->set_halign(Gtk::ALIGN_START);
    iconEntry = Gtk::manage(new Gtk::Entry());
    editor->pack_start(*lbl2, Gtk::PACK_SHRINK);
    editor->pack_start(*iconEntry, Gtk::PACK_SHRINK);
    
    auto* lbl3 = Gtk::manage(new Gtk::Label("Command:"));
    lbl3->set_halign(Gtk::ALIGN_START);
    commandEntry = Gtk::manage(new Gtk::Entry());
    editor->pack_start(*lbl3, Gtk::PACK_SHRINK);
    editor->pack_start(*commandEntry, Gtk::PACK_SHRINK);
    
    runOnceCheck = Gtk::manage(new Gtk::CheckButton("Run once (prevent multiple instances)"));
    editor->pack_start(*runOnceCheck, Gtk::PACK_SHRINK);
    
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
    
    // Signals
    treeView->get_selection()->signal_changed().connect(sigc::mem_fun(*this, &ProgramsTab::updateInputs));
    
    addBtn->signal_clicked().connect([this]() {
        std::string name = nameEntry->get_text(), cmd = commandEntry->get_text();
        if (name.empty() || cmd.empty()) {
            Gtk::MessageDialog dlg("Name and Command are required!", false, Gtk::MESSAGE_WARNING);
            dlg.run(); return;
        }
        programs.emplace_back(name, iconEntry->get_text(), cmd, runOnceCheck->get_active());
        updateList(); clearInputs();
    });
    
    removeBtn->signal_clicked().connect([this]() {
        auto sel = treeView->get_selection()->get_selected();
        if (sel) { int idx = listStore->get_path(sel)[0]; programs.erase(programs.begin() + idx); updateList(); clearInputs(); }
    });
    
    upBtn->signal_clicked().connect([this]() {
        auto sel = treeView->get_selection()->get_selected();
        if (!sel) return;
        int idx = listStore->get_path(sel)[0];
        if (idx > 0) { std::swap(programs[idx], programs[idx-1]); updateList(); treeView->get_selection()->select(Gtk::TreePath(std::to_string(idx-1))); }
    });
    
    downBtn->signal_clicked().connect([this]() {
        auto sel = treeView->get_selection()->get_selected();
        if (!sel) return;
        int idx = listStore->get_path(sel)[0];
        if (idx < (int)programs.size()-1) { std::swap(programs[idx], programs[idx+1]); updateList(); treeView->get_selection()->select(Gtk::TreePath(std::to_string(idx+1))); }
    });
    
    saveBtn->signal_clicked().connect(sigc::mem_fun(*this, &ProgramsTab::saveProgramsFile));
    loadBtn->signal_clicked().connect(sigc::mem_fun(*this, &ProgramsTab::loadProgramsFile));
    
    loadProgramsFile();
}

void ProgramsTab::loadProgramsFile() {
    programs.clear();
    std::string filename = configDir + "/programs";
    std::ifstream file(filename);
    if (!file.is_open()) file.open("/usr/share/icewm/programs");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty() || line[0] == '#') continue;
            std::istringstream iss(line);
            std::string type; iss >> type;
            if (type == "prog") {
                std::string name, icon, command;
                std::getline(iss, name, '"'); std::getline(iss, name, '"');
                std::getline(iss, icon, '"'); std::getline(iss, icon, '"');
                std::getline(iss, command);
                if (!command.empty() && command[0] == ' ') command = command.substr(1);
                programs.emplace_back(name, icon, command, false);
            } else if (type == "runonce") {
                std::string name, icon, nameclass, command;
                std::getline(iss, name, '"'); std::getline(iss, name, '"');
                std::getline(iss, icon, '"'); std::getline(iss, icon, '"');
                std::getline(iss, nameclass, '"'); std::getline(iss, nameclass, '"');
                std::getline(iss, command);
                if (!command.empty() && command[0] == ' ') command = command.substr(1);
                programs.emplace_back(name, icon, command, true);
            }
        }
    }
    updateList();
}

void ProgramsTab::saveProgramsFile() {
    std::string filename = configDir + "/programs";
    std::string backup = filename + ".backup";
    std::ifstream src(filename, std::ios::binary);
    if (src.is_open()) { std::ofstream dst(backup, std::ios::binary); dst << src.rdbuf(); }
    std::ofstream file(filename);
    if (!file.is_open()) { Gtk::MessageDialog dlg("Failed to save!", false, Gtk::MESSAGE_ERROR); dlg.run(); return; }
    for (const auto& prog : programs) {
        if (prog.runOnce) {
            std::string nc = prog.name; std::replace(nc.begin(), nc.end(), ' ', '.');
            file << "runonce \"" << prog.name << "\" \"" << prog.icon << "\" \"" << nc << "\" " << prog.command << "\n";
        } else {
            file << "prog \"" << prog.name << "\" \"" << prog.icon << "\" " << prog.command << "\n";
        }
    }
    file.close();
    Gtk::MessageDialog dlg("Programs saved!", false, Gtk::MESSAGE_INFO); dlg.run();
}

void ProgramsTab::updateList() {
    listStore->clear();
    for (const auto& prog : programs) {
        auto row = *listStore->append();
        row[cols.name] = prog.name + (prog.runOnce ? " [once]" : "");
    }
}

void ProgramsTab::updateInputs() {
    auto sel = treeView->get_selection()->get_selected();
    if (!sel) return;
    int idx = listStore->get_path(sel)[0];
    if (idx >= 0 && idx < (int)programs.size()) {
        const auto& prog = programs[idx];
        nameEntry->set_text(prog.name);
        iconEntry->set_text(prog.icon);
        commandEntry->set_text(prog.command);
        runOnceCheck->set_active(prog.runOnce);
    }
}

void ProgramsTab::clearInputs() { nameEntry->set_text(""); iconEntry->set_text(""); commandEntry->set_text(""); runOnceCheck->set_active(false); }
void ProgramsTab::refresh() { loadProgramsFile(); }
