#include "WinOptionsTab.h"
#include <gtkmm/messagedialog.h>
#include <fstream>

WinOptionsTab::WinOptionsTab(const std::string& configDir) : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5), configDir(configDir) {
    set_margin_left(10);
    set_margin_top(10);
    
    auto* title = Gtk::manage(new Gtk::Label());
    title->set_markup("<b>Window Options</b>");
    title->set_halign(Gtk::ALIGN_START);
    pack_start(*title, Gtk::PACK_SHRINK);
    
    auto* hbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    
    listStore = Gtk::ListStore::create(cols);
    treeView = Gtk::manage(new Gtk::TreeView(listStore));
    treeView->append_column("Option", cols.name);
    treeView->set_headers_visible(false);
    auto* scrolled = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled->set_min_content_width(200);
    scrolled->add(*treeView);
    hbox->pack_start(*scrolled, Gtk::PACK_SHRINK);
    
    auto* editor = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    editor->set_margin_left(10);
    
    editor->pack_start(*Gtk::manage(new Gtk::Label("Class:")), Gtk::PACK_SHRINK);
    classEntry = Gtk::manage(new Gtk::Entry());
    classEntry->set_tooltip_text("Window class name (e.g., xterm, firefox)");
    editor->pack_start(*classEntry, Gtk::PACK_SHRINK);
    
    editor->pack_start(*Gtk::manage(new Gtk::Label("Option:")), Gtk::PACK_SHRINK);
    optionCombo = Gtk::manage(new Gtk::ComboBoxText());
    editor->pack_start(*optionCombo, Gtk::PACK_SHRINK);
    
    editor->pack_start(*Gtk::manage(new Gtk::Label("Value:")), Gtk::PACK_SHRINK);
    valueCombo = Gtk::manage(new Gtk::ComboBoxText());
    editor->pack_start(*valueCombo, Gtk::PACK_SHRINK);
    
    initChoices();
    
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
    
    treeView->get_selection()->signal_changed().connect(sigc::mem_fun(*this, &WinOptionsTab::updateInputs));
    
    addBtn->signal_clicked().connect([this]() {
        WinOption opt;
        opt.windowClass = classEntry->get_text();
        if (opt.windowClass.empty()) { Gtk::MessageDialog dlg("Window class is required!", false, Gtk::MESSAGE_WARNING); dlg.run(); return; }
        int oi = optionCombo->get_active_row_number();
        int vi = valueCombo->get_active_row_number();
        if (oi >= 0) opt.option = optionCombo->get_active_text();
        if (vi >= 0) opt.value = valueCombo->get_active_text();
        winOptions.push_back(opt);
        updateList();
    });
    
    removeBtn->signal_clicked().connect([this]() {
        auto sel = treeView->get_selection()->get_selected();
        if (sel) { int idx = listStore->get_path(sel)[0]; winOptions.erase(winOptions.begin() + idx); updateList(); classEntry->set_text(""); }
    });
    
    saveBtn->signal_clicked().connect(sigc::mem_fun(*this, &WinOptionsTab::saveWinOptionsFile));
    loadBtn->signal_clicked().connect(sigc::mem_fun(*this, &WinOptionsTab::loadWinOptionsFile));
    
    loadWinOptionsFile();
}

void WinOptionsTab::initChoices() {
    const char* opts[] = {"workspace","layer","geometry","icon","function","ignoreTaskBar","ignoreQuickSwitch","ignoreWinList","ignoreAutoReload","focusable","focusedOpacity","unfocusedOpacity",nullptr};
    for (int i = 0; opts[i]; i++) optionCombo->append(opts[i]);
    optionCombo->set_active(0);
    
    const char* vals[] = {"0","1","2","3","all","Desktop","Below","Normal","OnTop","Dock","AboveDock","Menu",nullptr};
    for (int i = 0; vals[i]; i++) valueCombo->append(vals[i]);
    valueCombo->set_active(0);
}

void WinOptionsTab::loadWinOptionsFile() {
    winOptions.clear();
    std::ifstream file(configDir + "/winoptions");
    if (!file.is_open()) file.open("/usr/share/icewm/winoptions");
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t dot = line.find('.'), colon = line.find(':');
            if (dot != std::string::npos && colon != std::string::npos) {
                WinOption opt;
                opt.windowClass = line.substr(0, dot);
                opt.option = line.substr(dot+1, colon-dot-1);
                opt.value = line.substr(colon+1);
                size_t s = opt.value.find_first_not_of(" \t");
                if (s != std::string::npos) opt.value = opt.value.substr(s);
                winOptions.push_back(opt);
            }
        }
    }
    updateList();
}

void WinOptionsTab::saveWinOptionsFile() {
    std::ofstream file(configDir + "/winoptions");
    if (file.is_open()) {
        for (const auto& opt : winOptions) file << opt.windowClass << "." << opt.option << ": " << opt.value << "\n";
        file.close();
        Gtk::MessageDialog dlg("WinOptions saved!", false, Gtk::MESSAGE_INFO); dlg.run();
    } else {
        Gtk::MessageDialog dlg("Failed to save!", false, Gtk::MESSAGE_ERROR); dlg.run();
    }
}

void WinOptionsTab::updateList() {
    listStore->clear();
    for (const auto& opt : winOptions) {
        auto row = *listStore->append();
        row[cols.name] = opt.windowClass + "." + opt.option + ": " + opt.value;
    }
}

void WinOptionsTab::updateInputs() {
    auto sel = treeView->get_selection()->get_selected();
    if (!sel) return;
    int idx = listStore->get_path(sel)[0];
    if (idx >= 0 && idx < (int)winOptions.size()) {
        const auto& opt = winOptions[idx];
        classEntry->set_text(opt.windowClass);
        // Try to match option in combo
        for (int i = 0; i < optionCombo->get_model()->children().size(); i++) {
            optionCombo->set_active(i);
            if (optionCombo->get_active_text() == opt.option) break;
        }
        for (int i = 0; i < valueCombo->get_model()->children().size(); i++) {
            valueCombo->set_active(i);
            if (valueCombo->get_active_text() == opt.value) break;
        }
    }
}

void WinOptionsTab::refresh() { loadWinOptionsFile(); }
