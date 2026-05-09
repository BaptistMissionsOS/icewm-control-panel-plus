#include "ThemeTab.ToolsTab.h"
#include <gtkmm/messagedialog.h>
#include <gtkmm/filechooserdialog.h>
#include <fstream>
#include <cstdlib>

ToolsTab::ToolsTab(const std::string& configDir) : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5), configDir(configDir) {
    set_margin_left(10);
    set_margin_top(10);
    
    auto* title = Gtk::manage(new Gtk::Label());
    title->set_markup("<b>Theme Tools</b>");
    title->set_halign(Gtk::ALIGN_START);
    pack_start(*title, Gtk::PACK_SHRINK);
    
    // Copy Theme section
    auto* copyFrame = Gtk::manage(new Gtk::Frame("Copy Theme"));
    auto* copyBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    copyBox->set_margin_left(10);
    copyBox->set_margin_top(10);
    copyBox->set_margin_bottom(10);
    
    auto* srcRow = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    srcRow->pack_start(*Gtk::manage(new Gtk::Label("Source:")), Gtk::PACK_SHRINK);
    sourceThemeEntry = Gtk::manage(new Gtk::Entry());
    sourceThemeEntry->set_hexpand(true);
    auto* srcBrowse = Gtk::manage(new Gtk::Button("Browse..."));
    srcBrowse->signal_clicked().connect(sigc::mem_fun(*this, &ToolsTab::browseSource));
    srcRow->pack_start(*sourceThemeEntry, Gtk::PACK_EXPAND_WIDGET);
    srcRow->pack_start(*srcBrowse, Gtk::PACK_SHRINK);
    copyBox->pack_start(*srcRow, Gtk::PACK_SHRINK);
    
    auto* tgtRow = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    tgtRow->pack_start(*Gtk::manage(new Gtk::Label("Target:")), Gtk::PACK_SHRINK);
    targetThemeEntry = Gtk::manage(new Gtk::Entry());
    targetThemeEntry->set_hexpand(true);
    auto* tgtBrowse = Gtk::manage(new Gtk::Button("Browse..."));
    tgtBrowse->signal_clicked().connect(sigc::mem_fun(*this, &ToolsTab::browseTarget));
    tgtRow->pack_start(*targetThemeEntry, Gtk::PACK_EXPAND_WIDGET);
    tgtRow->pack_start(*tgtBrowse, Gtk::PACK_SHRINK);
    copyBox->pack_start(*tgtRow, Gtk::PACK_SHRINK);
    
    auto* copyBtn = Gtk::manage(new Gtk::Button("_Copy Theme", true));
    copyBtn->signal_clicked().connect(sigc::mem_fun(*this, &ToolsTab::copyTheme));
    copyBox->pack_start(*copyBtn, Gtk::PACK_SHRINK);
    
    copyFrame->add(*copyBox);
    pack_start(*copyFrame, Gtk::PACK_SHRINK);
    
    // Export/Import section
    auto* eiFrame = Gtk::manage(new Gtk::Frame("Export / Import"));
    auto* eiBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    eiBox->set_margin_left(10);
    eiBox->set_margin_top(10);
    eiBox->set_margin_bottom(10);
    
    auto* exportBtn = Gtk::manage(new Gtk::Button("_Export Theme...", true));
    exportBtn->signal_clicked().connect(sigc::mem_fun(*this, &ToolsTab::exportTheme));
    eiBox->pack_start(*exportBtn, Gtk::PACK_SHRINK);
    
    auto* importBtn = Gtk::manage(new Gtk::Button("_Import Theme...", true));
    importBtn->signal_clicked().connect(sigc::mem_fun(*this, &ToolsTab::importTheme));
    eiBox->pack_start(*importBtn, Gtk::PACK_SHRINK);
    
    eiFrame->add(*eiBox);
    pack_start(*eiFrame, Gtk::PACK_SHRINK);
    
    // Reset section
    auto* resetFrame = Gtk::manage(new Gtk::Frame("Reset Theme"));
    auto* resetBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    resetBox->set_margin_left(10);
    resetBox->set_margin_top(10);
    resetBox->set_margin_bottom(10);
    
    auto* resetLabel = Gtk::manage(new Gtk::Label("Reset to default IceWM theme"));
    resetBox->pack_start(*resetLabel, Gtk::PACK_SHRINK);
    
    auto* resetBtn = Gtk::manage(new Gtk::Button("_Reset to Default", true));
    resetBtn->get_style_context()->add_class("destructive-action");
    resetBtn->signal_clicked().connect(sigc::mem_fun(*this, &ToolsTab::resetTheme));
    resetBox->pack_start(*resetBtn, Gtk::PACK_SHRINK);
    
    resetFrame->add(*resetBox);
    pack_start(*resetFrame, Gtk::PACK_SHRINK);
    
    // Progress bar
    progressBar = Gtk::manage(new Gtk::ProgressBar());
    progressBar->set_show_text(true);
    progressBar->set_text("Ready");
    pack_start(*progressBar, Gtk::PACK_SHRINK);
    
    // Log output
    auto* logFrame = Gtk::manage(new Gtk::Frame("Log"));
    logView = Gtk::manage(new Gtk::TextView());
    logView->set_editable(false);
    logView->get_buffer()->set_text("Theme tools ready.\n");
    auto* logScroll = Gtk::manage(new Gtk::ScrolledWindow());
    logScroll->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    logScroll->set_min_content_height(150);
    logScroll->add(*logView);
    logFrame->add(*logScroll);
    pack_start(*logFrame, Gtk::PACK_EXPAND_WIDGET);
    
    // Clear log button
    auto* clearBtn = Gtk::manage(new Gtk::Button("_Clear Log", true));
    clearBtn->signal_clicked().connect([this]() {
        logView->get_buffer()->set_text("");
    });
    pack_start(*clearBtn, Gtk::PACK_SHRINK);
}

void ToolsTab::browseSource() {
    Gtk::FileChooserDialog dialog("Select Source Theme", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    dialog.set_transient_for(*dynamic_cast<Gtk::Window*>(get_toplevel()));
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Select", Gtk::RESPONSE_OK);
    
    if (dialog.run() == Gtk::RESPONSE_OK) {
        sourceThemeEntry->set_text(dialog.get_filename());
    }
}

void ToolsTab::browseTarget() {
    Gtk::FileChooserDialog dialog("Select Target Directory", Gtk::FILE_CHOOSER_ACTION_SELECT_FOLDER);
    dialog.set_transient_for(*dynamic_cast<Gtk::Window*>(get_toplevel()));
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Select", Gtk::RESPONSE_OK);
    
    if (dialog.run() == Gtk::RESPONSE_OK) {
        targetThemeEntry->set_text(dialog.get_filename());
    }
}

void ToolsTab::copyTheme() {
    std::string src = sourceThemeEntry->get_text();
    std::string tgt = targetThemeEntry->get_text();
    
    if (src.empty() || tgt.empty()) {
        log("Error: Source and target must be specified");
        return;
    }
    
    progressBar->set_fraction(0.5);
    progressBar->set_text("Copying...");
    
    // Would implement actual recursive copy here
    log("Copying theme from: " + src);
    log("To: " + tgt);
    log("Copy completed (simulated)");
    
    progressBar->set_fraction(1.0);
    progressBar->set_text("Done");
}

void ToolsTab::exportTheme() {
    Gtk::FileChooserDialog dialog("Export Theme", Gtk::FILE_CHOOSER_ACTION_SAVE);
    dialog.set_transient_for(*dynamic_cast<Gtk::Window*>(get_toplevel()));
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Export", Gtk::RESPONSE_OK);
    
    auto filter = Gtk::FileFilter::create();
    filter->set_name("Tar Archives");
    filter->add_pattern("*.tar.gz");
    filter->add_mime_type("application/gzip");
    dialog.add_filter(filter);
    
    dialog.set_current_name("mytheme.tar.gz");
    
    if (dialog.run() == Gtk::RESPONSE_OK) {
        std::string filename = dialog.get_filename();
        log("Exporting theme to: " + filename);
        // Would create tar.gz here
        log("Export completed (simulated)");
    }
}

void ToolsTab::importTheme() {
    Gtk::FileChooserDialog dialog("Import Theme", Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*dynamic_cast<Gtk::Window*>(get_toplevel()));
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Import", Gtk::RESPONSE_OK);
    
    auto filter = Gtk::FileFilter::create();
    filter->set_name("Theme Archives");
    filter->add_pattern("*.tar.gz");
    filter->add_pattern("*.zip");
    dialog.add_filter(filter);
    
    if (dialog.run() == Gtk::RESPONSE_OK) {
        std::string filename = dialog.get_filename();
        std::string targetDir = configDir + "/themes";
        log("Importing from: " + filename);
        log("Target: " + targetDir);
        // Would extract archive here
        log("Import completed (simulated)");
    }
}

void ToolsTab::resetTheme() {
    Gtk::MessageDialog dlg("Reset to default theme?", false, Gtk::MESSAGE_QUESTION, Gtk::BUTTONS_YES_NO);
    if (dlg.run() == Gtk::RESPONSE_YES) {
        // Remove theme file to use defaults
        std::string themeFile = configDir + "/theme";
        std::remove(themeFile.c_str());
        log("Theme reset to default");
        log("Theme file removed: " + themeFile);
        
        system("icesh restart &");
        Gtk::MessageDialog info("Theme reset! IceWM will restart.", false, Gtk::MESSAGE_INFO);
        info.run();
    }
}

void ToolsTab::log(const std::string& msg) {
    auto buffer = logView->get_buffer();
    buffer->insert(buffer->end(), msg + "\n");
    // Scroll to end
    auto endIter = buffer->end();
    logView->scroll_to(endIter);
}

void ToolsTab::refresh() {
    // Nothing to refresh
}
