#include "PreferencesTab.DesktopTab.h"
#include <gtkmm/messagedialog.h>
#include <gtkmm/filechooserdialog.h>
#include <fstream>
#include <sstream>

PrefDesktopTab::PrefDesktopTab(const std::string& configDir) 
    : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5), configDir(configDir) {
    set_margin_left(10);
    set_margin_top(10);

    auto* title = Gtk::manage(new Gtk::Label());
    title->set_markup("<b>Desktop Settings</b>");
    title->set_halign(Gtk::ALIGN_START);
    pack_start(*title, Gtk::PACK_SHRINK);

    auto* scrolled = Gtk::manage(new Gtk::ScrolledWindow());
    scrolled->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled->set_min_content_height(400);

    auto* container = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));

    // Workspace settings
    auto* wsFrame = Gtk::manage(new Gtk::Frame("Workspace Settings"));
    auto* wsBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    wsBox->set_margin_left(10);
    wsBox->set_margin_top(10);
    wsBox->set_margin_bottom(10);

    // Workspace name
    auto* nameRow = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    nameRow->pack_start(*Gtk::manage(new Gtk::Label("Workspace Name:")), Gtk::PACK_SHRINK);
    workspaceNameInput = Gtk::manage(new Gtk::Entry());
    workspaceNameInput->set_placeholder_text("Default workspace name");
    workspaceNameInput->set_hexpand(true);
    nameRow->pack_start(*workspaceNameInput, Gtk::PACK_EXPAND_WIDGET);
    wsBox->pack_start(*nameRow, Gtk::PACK_SHRINK);

    // Workspace count
    auto* countRow = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    countRow->pack_start(*Gtk::manage(new Gtk::Label("Workspace Count:")), Gtk::PACK_SHRINK);
    workspaceCountSpinner = Gtk::manage(new Gtk::SpinButton());
    workspaceCountSpinner->set_range(1, 12);
    workspaceCountSpinner->set_value(4);
    workspaceCountSpinner->set_increments(1, 1);
    countRow->pack_start(*workspaceCountSpinner, Gtk::PACK_SHRINK);
    wsBox->pack_start(*countRow, Gtk::PACK_SHRINK);

    // Checkboxes
    showTaskbarCheck = Gtk::manage(new Gtk::CheckButton("Show Taskbar"));
    showTaskbarCheck->set_active(true);
    wsBox->pack_start(*showTaskbarCheck, Gtk::PACK_SHRINK);

    showClockCheck = Gtk::manage(new Gtk::CheckButton("Show Clock"));
    showClockCheck->set_active(true);
    wsBox->pack_start(*showClockCheck, Gtk::PACK_SHRINK);

    showPagerCheck = Gtk::manage(new Gtk::CheckButton("Show Pager"));
    showPagerCheck->set_active(true);
    wsBox->pack_start(*showPagerCheck, Gtk::PACK_SHRINK);

    wsFrame->add(*wsBox);
    container->pack_start(*wsFrame, Gtk::PACK_SHRINK);

    // Background settings
    auto* bgFrame = Gtk::manage(new Gtk::Frame("Background Settings"));
    auto* bgBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    bgBox->set_margin_left(10);
    bgBox->set_margin_top(10);
    bgBox->set_margin_bottom(10);

    // Background image
    auto* imgRow = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    imgRow->pack_start(*Gtk::manage(new Gtk::Label("Background Image:")), Gtk::PACK_SHRINK);
    // We'll use a temporary entry since header doesn't have one
    auto* bgEntry = Gtk::manage(new Gtk::Entry());
    bgEntry->set_placeholder_text("Path to background image");
    bgEntry->set_hexpand(true);
    imgRow->pack_start(*bgEntry, Gtk::PACK_EXPAND_WIDGET);
    desktopBrowseButton = Gtk::manage(new Gtk::Button("_Browse...", true));
    desktopBrowseButton->signal_clicked().connect(sigc::mem_fun(*this, &PrefDesktopTab::browseDesktopBackground));
    imgRow->pack_start(*desktopBrowseButton, Gtk::PACK_SHRINK);
    bgBox->pack_start(*imgRow, Gtk::PACK_SHRINK);

    // Scaling options
    auto* scaleRow = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    scaleRow->pack_start(*Gtk::manage(new Gtk::Label("Scaling:")), Gtk::PACK_SHRINK);
    desktopScalingChoice = Gtk::manage(new Gtk::ComboBoxText());
    desktopScalingChoice->append("stretch", "Stretch (fill screen)");
    desktopScalingChoice->append("center", "Center (no scaling)");
    desktopScalingChoice->append("tile", "Tile (repeat)");
    desktopScalingChoice->append("fit", "Fit (preserve aspect)");
    desktopScalingChoice->set_active_id("stretch");
    scaleRow->pack_start(*desktopScalingChoice, Gtk::PACK_SHRINK);
    bgBox->pack_start(*scaleRow, Gtk::PACK_SHRINK);

    // Workspace selection for background
    auto* wsBgRow = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    wsBgRow->pack_start(*Gtk::manage(new Gtk::Label("Apply to Workspace:")), Gtk::PACK_SHRINK);
    desktopWorkspaceChoice = Gtk::manage(new Gtk::ComboBoxText());
    desktopWorkspaceChoice->append("all", "All Workspaces");
    for (int i = 1; i <= 12; i++) {
        desktopWorkspaceChoice->append(std::to_string(i), "Workspace " + std::to_string(i));
    }
    desktopWorkspaceChoice->set_active_id("all");
    wsBgRow->pack_start(*desktopWorkspaceChoice, Gtk::PACK_SHRINK);
    bgBox->pack_start(*wsBgRow, Gtk::PACK_SHRINK);

    // Solid color
    auto* colorRow = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    colorRow->pack_start(*Gtk::manage(new Gtk::Label("Solid Color:")), Gtk::PACK_SHRINK);
    desktopColorButton = Gtk::manage(new Gtk::ColorButton());
    Gdk::RGBA defaultColor;
    defaultColor.set_rgba(0.1, 0.1, 0.1, 1.0);
    desktopColorButton->set_rgba(defaultColor);
    colorRow->pack_start(*desktopColorButton, Gtk::PACK_SHRINK);
    bgBox->pack_start(*colorRow, Gtk::PACK_SHRINK);

    bgFrame->add(*bgBox);
    container->pack_start(*bgFrame, Gtk::PACK_SHRINK);

    // Preview
    auto* previewFrame = Gtk::manage(new Gtk::Frame("Preview"));
    auto* previewBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    previewBox->set_margin_left(10);
    previewBox->set_margin_top(10);
    previewBox->set_margin_bottom(10);
    previewBox->set_size_request(-1, 200);
    
    desktopPreviewLabel = Gtk::manage(new Gtk::Label("No preview available"));
    previewBox->pack_start(*desktopPreviewLabel, Gtk::PACK_EXPAND_WIDGET);
    
    previewFrame->add(*previewBox);
    container->pack_start(*previewFrame, Gtk::PACK_EXPAND_WIDGET);

    scrolled->add(*container);
    pack_start(*scrolled, Gtk::PACK_EXPAND_WIDGET);

    show_all_children();
}

void PrefDesktopTab::browseDesktopBackground() {
    Gtk::FileChooserDialog dialog(*dynamic_cast<Gtk::Window*>(get_toplevel()),
                                "Select Background Image", Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_ACCEPT);

    auto filter = Gtk::FileFilter::create();
    filter->set_name("Image files");
    filter->add_mime_type("image/*");
    dialog.add_filter(filter);

    if (dialog.run() == Gtk::RESPONSE_ACCEPT) {
        desktopBackgroundColor = dialog.get_filename();
        // Update preview if needed
    }
}

void PrefDesktopTab::pickDesktopColor() {
    Gtk::ColorChooserDialog dialog("Select Desktop Color",
                                 *dynamic_cast<Gtk::Window*>(get_toplevel()));
    Gdk::RGBA currentColor = desktopColorButton->get_rgba();
    dialog.set_rgba(currentColor);

    if (dialog.run() == Gtk::RESPONSE_ACCEPT) {
        Gdk::RGBA rgba = dialog.get_rgba();
        desktopColorButton->set_rgba(rgba);
        desktopBackgroundColor = rgba.to_string();
    }
}

void PrefDesktopTab::loadPreferences(const std::map<std::string, std::string>& preferences) {
    auto it = preferences.find("DesktopBackgroundColor");
    if (it != preferences.end()) {
        desktopBackgroundColor = it->second;
    }
    
    it = preferences.find("WorkspaceName");
    if (it != preferences.end() && workspaceNameInput) {
        workspaceNameInput->set_text(it->second);
    }
    
    it = preferences.find("WorkspaceCount");
    if (it != preferences.end() && workspaceCountSpinner) {
        try {
            int count = std::stoi(it->second);
            workspaceCountSpinner->set_value(count);
        } catch (...) {}
    }
}

void PrefDesktopTab::savePreferences(std::map<std::string, std::string>& preferences) {
    if (!desktopBackgroundColor.empty()) {
        preferences["DesktopBackgroundColor"] = desktopBackgroundColor;
    }
    
    if (workspaceNameInput) {
        preferences["WorkspaceName"] = workspaceNameInput->get_text();
    }
    
    if (workspaceCountSpinner) {
        preferences["WorkspaceCount"] = std::to_string((int)workspaceCountSpinner->get_value());
    }
}

void PrefDesktopTab::resetWidgets() {
    if (workspaceNameInput) workspaceNameInput->set_text("");
    if (workspaceCountSpinner) workspaceCountSpinner->set_value(4);
    if (showTaskbarCheck) showTaskbarCheck->set_active(true);
    if (showClockCheck) showClockCheck->set_active(true);
    if (showPagerCheck) showPagerCheck->set_active(true);
    if (desktopScalingChoice) desktopScalingChoice->set_active_id("stretch");
    if (desktopWorkspaceChoice) desktopWorkspaceChoice->set_active_id("all");
    
    Gdk::RGBA defaultColor;
    defaultColor.set_rgba(0.1, 0.1, 0.1, 1.0);
    if (desktopColorButton) desktopColorButton->set_rgba(defaultColor);
    desktopBackgroundColor = "";
}
