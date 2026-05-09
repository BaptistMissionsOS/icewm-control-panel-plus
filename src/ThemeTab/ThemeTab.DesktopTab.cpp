#include "ThemeTab.DesktopTab.h"
#include <gtkmm/messagedialog.h>
#include <gtkmm/filechooserdialog.h>
#include <fstream>

DesktopTab::DesktopTab(const std::string& configDir) : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5), configDir(configDir) {
    set_margin_left(10);
    set_margin_top(10);
    
    auto* title = Gtk::manage(new Gtk::Label());
    title->set_markup("<b>Desktop Background</b>");
    title->set_halign(Gtk::ALIGN_START);
    pack_start(*title, Gtk::PACK_SHRINK);
    
    // Background image section
    auto* imgFrame = Gtk::manage(new Gtk::Frame("Background Image"));
    auto* imgBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    imgBox->set_margin_left(10);
    imgBox->set_margin_top(10);
    imgBox->set_margin_bottom(10);
    
    auto* pathRow = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    backgroundEntry = Gtk::manage(new Gtk::Entry());
    backgroundEntry->set_placeholder_text("Path to background image");
    backgroundEntry->set_hexpand(true);
    auto* browseBtn = Gtk::manage(new Gtk::Button("_Browse...", true));
    browseBtn->signal_clicked().connect(sigc::mem_fun(*this, &DesktopTab::browseBackground));
    pathRow->pack_start(*backgroundEntry, Gtk::PACK_EXPAND_WIDGET);
    pathRow->pack_start(*browseBtn, Gtk::PACK_SHRINK);
    imgBox->pack_start(*pathRow, Gtk::PACK_SHRINK);
    
    // Scaling options
    auto* scaleRow = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    scaleRow->pack_start(*Gtk::manage(new Gtk::Label("Scaling:")), Gtk::PACK_SHRINK);
    scalingCombo = Gtk::manage(new Gtk::ComboBoxText());
    scalingCombo->append("stretch", "Stretch (fill screen)");
    scalingCombo->append("center", "Center (no scaling)");
    scalingCombo->append("tile", "Tile (repeat)");
    scalingCombo->append("fit", "Fit (preserve aspect)");
    scalingCombo->set_active_id("stretch");
    scaleRow->pack_start(*scalingCombo, Gtk::PACK_SHRINK);
    imgBox->pack_start(*scaleRow, Gtk::PACK_SHRINK);
    
    // Workspace selection
    auto* wsRow = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    wsRow->pack_start(*Gtk::manage(new Gtk::Label("Workspace:")), Gtk::PACK_SHRINK);
    workspaceCombo = Gtk::manage(new Gtk::ComboBoxText());
    workspaceCombo->append("all", "All Workspaces");
    for (int i = 1; i <= 9; i++) {
        workspaceCombo->append(std::to_string(i), "Workspace " + std::to_string(i));
    }
    workspaceCombo->set_active_id("all");
    wsRow->pack_start(*workspaceCombo, Gtk::PACK_SHRINK);
    imgBox->pack_start(*wsRow, Gtk::PACK_SHRINK);
    
    imgFrame->add(*imgBox);
    pack_start(*imgFrame, Gtk::PACK_SHRINK);
    
    // Solid color section
    auto* colorFrame = Gtk::manage(new Gtk::Frame("Solid Color Background"));
    auto* colorBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    colorBox->set_margin_left(10);
    colorBox->set_margin_top(10);
    colorBox->set_margin_bottom(10);
    colorBox->pack_start(*Gtk::manage(new Gtk::Label("Color:")), Gtk::PACK_SHRINK);
    colorButton = Gtk::manage(new Gtk::ColorButton());
    colorButton->set_rgba(Gdk::RGBA("#2d2d2d"));
    colorBox->pack_start(*colorButton, Gtk::PACK_SHRINK);
    colorFrame->add(*colorBox);
    pack_start(*colorFrame, Gtk::PACK_SHRINK);
    
    // Preview section
    auto* previewFrame = Gtk::manage(new Gtk::Frame("Preview"));
    auto* previewBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    previewBox->set_margin_left(10);
    previewBox->set_margin_top(10);
    previewBox->set_margin_bottom(10);
    previewBox->set_size_request(-1, 200);
    
    previewLabel = Gtk::manage(new Gtk::Label("No preview available"));
    previewLabel->set_justify(Gtk::JUSTIFY_CENTER);
    previewBox->pack_start(*previewLabel, Gtk::PACK_EXPAND_WIDGET);
    
    previewFrame->add(*previewBox);
    pack_start(*previewFrame, Gtk::PACK_EXPAND_WIDGET);
    
    // Buttons
    auto* btnBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* saveBtn = Gtk::manage(new Gtk::Button("_Save", true));
    auto* applyBtn = Gtk::manage(new Gtk::Button("_Apply", true));
    auto* clearBtn = Gtk::manage(new Gtk::Button("_Clear", true));
    btnBox->pack_start(*saveBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*applyBtn, Gtk::PACK_SHRINK);
    btnBox->pack_start(*clearBtn, Gtk::PACK_SHRINK);
    pack_start(*btnBox, Gtk::PACK_SHRINK);
    
    saveBtn->signal_clicked().connect(sigc::mem_fun(*this, &DesktopTab::saveSettings));
    applyBtn->signal_clicked().connect(sigc::mem_fun(*this, &DesktopTab::updatePreview));
    clearBtn->signal_clicked().connect([this]() {
        backgroundEntry->set_text("");
        scalingCombo->set_active_id("stretch");
        workspaceCombo->set_active_id("all");
        colorButton->set_rgba(Gdk::RGBA("#2d2d2d"));
    });
    
    loadSettings();
}

void DesktopTab::browseBackground() {
    Gtk::FileChooserDialog dialog("Select Background Image", Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*dynamic_cast<Gtk::Window*>(get_toplevel()));
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);
    
    auto filter = Gtk::FileFilter::create();
    filter->set_name("Images");
    filter->add_mime_type("image/png");
    filter->add_mime_type("image/jpeg");
    filter->add_mime_type("image/gif");
    filter->add_mime_type("image/bmp");
    filter->add_pattern("*.png");
    filter->add_pattern("*.jpg");
    filter->add_pattern("*.jpeg");
    filter->add_pattern("*.gif");
    filter->add_pattern("*.bmp");
    filter->add_pattern("*.xpm");
    dialog.add_filter(filter);
    
    if (dialog.run() == Gtk::RESPONSE_OK) {
        backgroundEntry->set_text(dialog.get_filename());
    }
}

void DesktopTab::pickColor() {
    // ColorButton already has built-in picker
}

void DesktopTab::updatePreview() {
    std::string path = backgroundEntry->get_text();
    if (path.empty()) {
        previewLabel->set_text("No background image selected\nUsing solid color");
        return;
    }
    
    try {
        auto pb = Gdk::Pixbuf::create_from_file(path, 300, 180, true);
        if (pb) {
            previewLabel->set_text("");
            // Would set image here if we had an Image widget
        }
    } catch (...) {
        previewLabel->set_text("Failed to load image\n" + path);
    }
}

void DesktopTab::loadSettings() {
    std::ifstream file(configDir + "/preferences");
    if (!file.is_open()) return;
    
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("DesktopBackgroundImage=") == 0) {
            size_t eq = line.find('=');
            if (eq != std::string::npos) {
                std::string val = line.substr(eq + 1);
                // Remove quotes if present
                if (val.size() >= 2 && val.front() == '"' && val.back() == '"') {
                    val = val.substr(1, val.size() - 2);
                }
                backgroundEntry->set_text(val);
            }
        } else if (line.find("DesktopBackgroundCenter=") == 0) {
            if (line.find("=1") != std::string::npos) {
                scalingCombo->set_active_id("center");
            }
        } else if (line.find("DesktopBackgroundScaled=") == 0) {
            if (line.find("=1") != std::string::npos) {
                scalingCombo->set_active_id("fit");
            }
        } else if (line.find("DesktopBackgroundColor=") == 0) {
            size_t eq = line.find('=');
            if (eq != std::string::npos) {
                std::string val = line.substr(eq + 1);
                Gdk::RGBA rgba;
                if (gdk_rgba_parse(rgba.gobj(), val.c_str())) {
                    colorButton->set_rgba(rgba);
                }
            }
        }
    }
}

void DesktopTab::saveSettings() {
    // Read existing preferences
    std::vector<std::string> lines;
    std::ifstream infile(configDir + "/preferences");
    if (infile.is_open()) {
        std::string line;
        while (std::getline(infile, line)) {
            lines.push_back(line);
        }
        infile.close();
    }
    
    auto updateOrAdd = [&lines](const std::string& key, const std::string& val) {
        bool found = false;
        for (auto& line : lines) {
            if (line.find(key + "=") == 0) {
                line = key + "=\"" + val + "\"";
                found = true;
                break;
            }
        }
        if (!found) {
            lines.push_back(key + "=\"" + val + "\"");
        }
    };
    
    updateOrAdd("DesktopBackgroundImage", backgroundEntry->get_text());
    
    std::string scaling = scalingCombo->get_active_id();
    if (scaling == "center") {
        updateOrAdd("DesktopBackgroundCenter", "1");
        updateOrAdd("DesktopBackgroundScaled", "0");
    } else if (scaling == "fit") {
        updateOrAdd("DesktopBackgroundCenter", "0");
        updateOrAdd("DesktopBackgroundScaled", "1");
    } else if (scaling == "tile") {
        updateOrAdd("DesktopBackgroundCenter", "0");
        updateOrAdd("DesktopBackgroundScaled", "0");
    } else {
        updateOrAdd("DesktopBackgroundCenter", "0");
        updateOrAdd("DesktopBackgroundScaled", "1");
    }
    
    Gdk::RGBA rgba = colorButton->get_rgba();
    char buf[32];
    snprintf(buf, sizeof(buf), "rgb:%02X/%02X/%02X",
             (int)(rgba.get_red() * 255),
             (int)(rgba.get_green() * 255),
             (int)(rgba.get_blue() * 255));
    updateOrAdd("DesktopBackgroundColor", buf);
    
    std::ofstream outfile(configDir + "/preferences");
    if (outfile.is_open()) {
        for (const auto& line : lines) {
            outfile << line << "\n";
        }
        outfile.close();
        Gtk::MessageDialog dlg("Desktop settings saved!", false, Gtk::MESSAGE_INFO);
        dlg.run();
    }
}

void DesktopTab::refresh() {
    loadSettings();
}
