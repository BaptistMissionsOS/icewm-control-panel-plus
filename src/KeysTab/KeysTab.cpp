#include "KeysTab.h"
#include <gtkmm/messagedialog.h>
#include <fstream>

KeysTab::KeysTab(const std::string& configDir) : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5), configDir(configDir) {
    set_margin_left(10);
    set_margin_top(10);
    
    auto* title = Gtk::manage(new Gtk::Label());
    title->set_markup("<b>Keyboard Shortcuts</b>");
    title->set_halign(Gtk::ALIGN_START);
    pack_start(*title, Gtk::PACK_SHRINK);
    
    auto* hbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    
    listStore = Gtk::ListStore::create(cols);
    treeView = Gtk::manage(new Gtk::TreeView(listStore));
    treeView->append_column("Shortcut", cols.name);
    treeView->set_headers_visible(false);
    auto* scrolled = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled->set_min_content_width(200);
    scrolled->add(*treeView);
    hbox->pack_start(*scrolled, Gtk::PACK_SHRINK);
    
    auto* editor = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    editor->set_margin_left(10);
    
    editor->pack_start(*Gtk::manage(new Gtk::Label("Key:")), Gtk::PACK_SHRINK);
    keyEntry = Gtk::manage(new Gtk::Entry());
    keyEntry->set_tooltip_text("Key combination (e.g., Alt+F2)");
    editor->pack_start(*keyEntry, Gtk::PACK_SHRINK);
    
    editor->pack_start(*Gtk::manage(new Gtk::Label("Action:")), Gtk::PACK_SHRINK);
    actionEntry = Gtk::manage(new Gtk::Entry());
    actionEntry->set_tooltip_text("Command or icesh action");
    editor->pack_start(*actionEntry, Gtk::PACK_SHRINK);
    
    auto* btnBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* addBtn = Gtk::manage(new Gtk::Button("_Add", true));
    auto* removeBtn = Gtk::manage(new Gtk::Button("_Remove", true));
    auto* saveBtn = Gtk::manage(new Gtk::Button("_Save", true));
    auto* loadBtn = Gtk::manage(new Gtk::Button("_Load", true));
    btnBox->pack_start(*addBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*removeBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*saveBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*loadBtn, Gtk::PACK_SHRINK);
    editor->pack_start(*btnBox, Gtk::PACK_SHRINK);
    
    hbox->pack_start(*editor, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*hbox, Gtk::PACK_EXPAND_WIDGET);
    
    treeView->get_selection()->signal_changed().connect(sigc::mem_fun(*this, &KeysTab::updateInputs));
    
    addBtn->signal_clicked().connect([this]() {
        std::string key = keyEntry->get_text(), action = actionEntry->get_text();
        if (key.empty() || action.empty()) { Gtk::MessageDialog dlg("Key and Action are required!", false, Gtk::MESSAGE_WARNING); dlg.run(); return; }
        keyBindings.push_back({key, action});
        updateList(); keyEntry->set_text(""); actionEntry->set_text("");
    });
    
    removeBtn->signal_clicked().connect([this]() {
        auto sel = treeView->get_selection()->get_selected();
        if (sel) { int idx = listStore->get_path(sel)[0]; keyBindings.erase(keyBindings.begin() + idx); updateList(); keyEntry->set_text(""); actionEntry->set_text(""); }
    });
    
    saveBtn->signal_clicked().connect(sigc::mem_fun(*this, &KeysTab::saveKeysFile));
    loadBtn->signal_clicked().connect(sigc::mem_fun(*this, &KeysTab::loadKeysFile));
    
    loadKeysFile();
}

void KeysTab::loadKeysFile() {
    keyBindings.clear();
    std::ifstream file(configDir + "/keys");
    if (!file.is_open()) file.open("/usr/share/icewm/keys");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty() || line[0] == '#') continue;
            std::istringstream iss(line);
            std::string key, action;
            iss >> key;
            std::getline(iss, action);
            if (!action.empty() && action[0] == ' ') action = action.substr(1);
            keyBindings.push_back({key, action});
        }
    }
    updateList();
}

void KeysTab::saveKeysFile() {
    std::ofstream file(configDir + "/keys");
    if (file.is_open()) {
        file << "# IceWM Key Bindings\n";
        for (const auto& kb : keyBindings) file << kb.key << " " << kb.action << "\n";
        file.close();
        Gtk::MessageDialog dlg("Keys saved!", false, Gtk::MESSAGE_INFO); dlg.run();
    } else {
        Gtk::MessageDialog dlg("Failed to save keys!", false, Gtk::MESSAGE_ERROR); dlg.run();
    }
}

void KeysTab::updateList() {
    listStore->clear();
    for (const auto& kb : keyBindings) {
        auto row = *listStore->append();
        row[cols.name] = kb.key + "  " + kb.action;
    }
}

void KeysTab::updateInputs() {
    auto sel = treeView->get_selection()->get_selected();
    if (!sel) return;
    int idx = listStore->get_path(sel)[0];
    if (idx >= 0 && idx < (int)keyBindings.size()) {
        keyEntry->set_text(keyBindings[idx].key);
        actionEntry->set_text(keyBindings[idx].action);
    }
}

void KeysTab::refresh() { loadKeysFile(); }
