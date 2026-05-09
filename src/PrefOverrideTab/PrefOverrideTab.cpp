#include "PrefOverrideTab.h"
#include <gtkmm/messagedialog.h>
#include <fstream>

PrefOverrideTab::PrefOverrideTab(const std::string& configDir) : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5), configDir(configDir) {
    set_margin_left(10);
    set_margin_top(10);
    
    auto* title = Gtk::manage(new Gtk::Label());
    title->set_markup("<b>Preference Overrides</b>");
    title->set_halign(Gtk::ALIGN_START);
    pack_start(*title, Gtk::PACK_SHRINK);
    
    auto* subtitle = Gtk::manage(new Gtk::Label("Override specific preferences for window classes (~/.icewm/prefoverride)"));
    subtitle->set_halign(Gtk::ALIGN_START);
    pack_start(*subtitle, Gtk::PACK_SHRINK);
    
    listStore = Gtk::ListStore::create(cols);
    treeView = Gtk::manage(new Gtk::TreeView(listStore));
    treeView->append_column("Key", cols.key);
    treeView->append_column("Value", cols.val);
    auto* scrolled = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled->add(*treeView);
    pack_start(*scrolled, Gtk::PACK_EXPAND_WIDGET);
    
    auto* editor = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    keyEntry = Gtk::manage(new Gtk::Entry());
    keyEntry->set_placeholder_text("Key");
    valEntry = Gtk::manage(new Gtk::Entry());
    valEntry->set_placeholder_text("Value");
    valEntry->set_hexpand(true);
    auto* addBtn = Gtk::manage(new Gtk::Button("_Set", true));
    auto* removeBtn = Gtk::manage(new Gtk::Button("_Remove", true));
    auto* saveBtn = Gtk::manage(new Gtk::Button("_Save", true));
    auto* loadBtn = Gtk::manage(new Gtk::Button("_Load", true));
    auto* resetBtn = Gtk::manage(new Gtk::Button("_Reset", true));
    editor->pack_start(*keyEntry, Gtk::PACK_SHRINK);
    editor->pack_start(*valEntry, Gtk::PACK_EXPAND_WIDGET);
    editor->pack_start(*addBtn, Gtk::PACK_SHRINK);
    editor->pack_start(*removeBtn, Gtk::PACK_SHRINK);
    editor->pack_start(*saveBtn, Gtk::PACK_SHRINK);
    editor->pack_start(*loadBtn, Gtk::PACK_SHRINK);
    editor->pack_start(*resetBtn, Gtk::PACK_SHRINK);
    pack_start(*editor, Gtk::PACK_SHRINK);
    
    treeView->get_selection()->signal_changed().connect(sigc::mem_fun(*this, &PrefOverrideTab::updateInputs));
    
    addBtn->signal_clicked().connect([this]() {
        std::string k = keyEntry->get_text(), v = valEntry->get_text();
        if (k.empty()) return;
        overrides[k] = v;
        updateList();
    });
    
    removeBtn->signal_clicked().connect([this]() {
        auto sel = treeView->get_selection()->get_selected();
        if (sel) { overrides.erase(sel->get_value(cols.key)); updateList(); keyEntry->set_text(""); valEntry->set_text(""); }
    });
    
    saveBtn->signal_clicked().connect(sigc::mem_fun(*this, &PrefOverrideTab::saveOverrides));
    loadBtn->signal_clicked().connect(sigc::mem_fun(*this, &PrefOverrideTab::loadOverrides));
    resetBtn->signal_clicked().connect([this]() {
        Gtk::MessageDialog dlg("Clear all overrides?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
        if (dlg.run() == Gtk::RESPONSE_YES) { overrides.clear(); updateList(); }
    });
    
    loadOverrides();
}

void PrefOverrideTab::loadOverrides() {
    overrides.clear();
    std::ifstream file(configDir + "/prefoverride");
    if (!file.is_open()) file.open("/usr/share/icewm/prefoverride");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty() && line.back() == '\r') line.pop_back();
            if (line.empty() || line[0] == '#') continue;
            size_t eq = line.find('=');
            if (eq == std::string::npos) continue;
            std::string key = line.substr(0, eq);
            std::string val = line.substr(eq + 1);
            if (val.length() >= 2 && val[0] == '"' && val.back() == '"') val = val.substr(1, val.length() - 2);
            overrides[key] = val;
        }
    }
    updateList();
}

void PrefOverrideTab::saveOverrides() {
    std::ofstream file(configDir + "/prefoverride");
    if (file.is_open()) {
        file << "# IceWM Preference Overrides\n";
        for (const auto& [k, v] : overrides) {
            if (v.find(' ') != std::string::npos || v.empty()) file << k << "=\"" << v << "\"\n";
            else file << k << "=" << v << "\n";
        }
        file.close();
        Gtk::MessageDialog dlg("Overrides saved!", false, Gtk::MESSAGE_INFO); dlg.run();
    } else {
        Gtk::MessageDialog dlg("Failed to save!", false, Gtk::MESSAGE_ERROR); dlg.run();
    }
}

void PrefOverrideTab::updateList() {
    listStore->clear();
    for (const auto& [k, v] : overrides) {
        auto row = *listStore->append();
        row[cols.key] = k;
        row[cols.val] = v;
    }
}

void PrefOverrideTab::updateInputs() {
    auto sel = treeView->get_selection()->get_selected();
    if (!sel) return;
    keyEntry->set_text(sel->get_value(cols.key));
    valEntry->set_text(sel->get_value(cols.val));
}

void PrefOverrideTab::refresh() { loadOverrides(); }
