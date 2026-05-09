#include "PreferencesTab.ColorsTab.h"
#include <gtkmm.h>
#include <sstream>
#include <algorithm>
#include <iomanip>

// Helper to create Gdk::RGBA from double components (0.0-1.0)
static Gdk::RGBA make_rgba(double r, double g, double b, double a = 1.0) {
    Gdk::RGBA c;
    c.set_rgba(r, g, b, a);
    return c;
}

PrefColorsTab::PrefColorsTab() : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10) {
    this->set_border_width(10);
    this->set_spacing(10);

    // Create scroll container
    Gtk::ScrolledWindow* scroll = new Gtk::ScrolledWindow();
    scroll->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scroll->show();

    // Create content area
    Gtk::Box* content = new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10);
    content->set_spacing(10);
    scroll->add(*content);

    // Helper to create a color control
    auto addColor = [&](const char* label_text, Gtk::ColorButton*& btn, const char* key, const Gdk::RGBA& def) {
        Gtk::Box* hbox = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
        
        Gtk::Label* lbl = new Gtk::Label(label_text);
        lbl->set_halign(Gtk::ALIGN_START);
        lbl->set_size_request(200, -1);
        hbox->pack_start(*lbl, Gtk::PACK_SHRINK);
        
        Gtk::ColorButton* colorBtn = new Gtk::ColorButton();
        colorBtn->set_rgba(def);
        colorBtn->set_size_request(50, 25);
        colorBtn->show();
        hbox->pack_start(*colorBtn, Gtk::PACK_SHRINK);
        
        btn = colorBtn;
        content->pack_start(*hbox, Gtk::PACK_SHRINK);
        hbox->show_all();
    };

    // Helper to add category label
    auto addCategory = [&](const char* title) {
        Gtk::Label* cat = new Gtk::Label(title);
        cat->set_halign(Gtk::ALIGN_START);
        Pango::FontDescription font_desc("Bold 12");
        cat->override_font(font_desc);
        content->pack_start(*cat, Gtk::PACK_SHRINK);
        cat->show();
    };

    // === Windows & Dialogs ===
    addCategory("Windows & Dialogs");
    addColor("Dialog:", colorDialog, "ColorDialog", make_rgba(0.5, 0.5, 0.5));
    addColor("Normal Border:", colorNormalBorder, "ColorNormalBorder", make_rgba(0.5, 0.5, 0.5));
    addColor("Active Border:", colorActiveBorder, "ColorActiveBorder", make_rgba(0.8, 0.8, 0.8));

    // === Title Bars ===
    addCategory("Title Bars");
    addColor("Normal TitleBar:", colorNormalTitleBar, "ColorNormalTitleBar", make_rgba(0.5, 0.5, 0.5));
    addColor("Normal TitleTxt:", colorNormalTitleBarText, "ColorNormalTitleBarText", make_rgba(0.0, 0.0, 0.0));
    addColor("Normal TitleShd:", colorNormalTitleBarShadow, "ColorNormalTitleBarShadow", make_rgba(0.3, 0.3, 0.3));
    addColor("Active TitleBar:", colorActiveTitleBar, "ColorActiveTitleBar", make_rgba(0.0, 0.0, 1.0));
    addColor("Active TitleTxt:", colorActiveTitleBarText, "ColorActiveTitleBarText", make_rgba(1.0, 1.0, 1.0));
    addColor("Active TitleShd:", colorActiveTitleBarShadow, "ColorActiveTitleBarShadow", make_rgba(0.3, 0.3, 0.3));

    // === Buttons ===
    addCategory("Buttons");
    addColor("Normal TitleButton:", colorNormalTitleButton, "ColorNormalTitleButton", make_rgba(0.7, 0.7, 0.7));
    addColor("Normal TitleButtonTxt:", colorNormalTitleButtonText, "ColorNormalTitleButtonText", make_rgba(0.0, 0.0, 0.0));
    addColor("Tool Button:", colorToolButton, "ColorToolButton", make_rgba(0.7, 0.7, 0.7));
    addColor("Tool ButtonTxt:", colorToolButtonText, "ColorToolButtonText", make_rgba(0.0, 0.0, 0.0));
    addColor("Normal Button:", colorNormalButton, "ColorNormalButton", make_rgba(0.7, 0.7, 0.7));
    addColor("Normal ButtonTxt:", colorNormalButtonText, "ColorNormalButtonText", make_rgba(0.0, 0.0, 0.0));
    addColor("Active Button:", colorActiveButton, "ColorActiveButton", make_rgba(0.5, 0.5, 1.0));
    addColor("Active ButtonTxt:", colorActiveButtonText, "ColorActiveButtonText", make_rgba(1.0, 1.0, 1.0));

    // === Workspace Switcher ===
    addCategory("Workspace Switcher");
    addColor("Normal WS Button:", colorNormalWorkspaceButton, "ColorNormalWorkspaceButton", make_rgba(0.7, 0.7, 0.7));
    addColor("Normal WS ButtonTxt:", colorNormalWorkspaceButtonText, "ColorNormalWorkspaceButtonText", make_rgba(0.0, 0.0, 0.0));
    addColor("Active WS Button:", colorActiveWorkspaceButton, "ColorActiveWorkspaceButton", make_rgba(0.5, 0.5, 1.0));
    addColor("Active WS ButtonTxt:", colorActiveWorkspaceButtonText, "ColorActiveWorkspaceButtonText", make_rgba(1.0, 1.0, 1.0));

    // === Menu ===
    addCategory("Menu");
    addColor("Normal Menu:", colorNormalMenu, "ColorNormalMenu", make_rgba(0.7, 0.7, 0.7));
    addColor("Normal MenuItemTxt:", colorNormalMenuItemText, "ColorNormalMenuItemText", make_rgba(0.0, 0.0, 0.0));
    addColor("Active MenuItem:", colorActiveMenuItem, "ColorActiveMenuItem", make_rgba(0.5, 0.5, 1.0));
    addColor("Active MenuItemTxt:", colorActiveMenuItemText, "ColorActiveMenuItemText", make_rgba(1.0, 1.0, 1.0));
    addColor("Disabled MenuItemTxt:", colorDisabledMenuItemText, "ColorDisabledMenuItemText", make_rgba(0.5, 0.5, 0.5));
    addColor("Disabled MenuItemShd:", colorDisabledMenuItemShadow, "ColorDisabledMenuItemShadow", make_rgba(0.3, 0.3, 0.3));

    // === TaskBar ===
    addCategory("TaskBar");
    addColor("Default TaskBar:", colorDefaultTaskBar, "ColorDefaultTaskBar", make_rgba(0.7, 0.7, 0.7));
    addColor("Normal TaskBarApp:", colorNormalTaskBarApp, "ColorNormalTaskBarApp", make_rgba(0.7, 0.7, 0.7));
    addColor("Normal TaskBarAppTxt:", colorNormalTaskBarAppText, "ColorNormalTaskBarAppText", make_rgba(0.0, 0.0, 0.0));
    addColor("Active TaskBarApp:", colorActiveTaskBarApp, "ColorActiveTaskBarApp", make_rgba(0.5, 0.5, 1.0));
    addColor("Active TaskBarAppTxt:", colorActiveTaskBarAppText, "ColorActiveTaskBarAppText", make_rgba(1.0, 1.0, 1.0));
    addColor("Minimized TaskBarApp:", colorMinimizedTaskBarApp, "ColorMinimizedTaskBarApp", make_rgba(0.5, 0.5, 0.5));
    addColor("Minimized TaskBarAppTxt:", colorMinimizedTaskBarAppText, "ColorMinimizedTaskBarAppText", make_rgba(0.5, 0.5, 0.5));
    addColor("Invisible TaskBarApp:", colorInvisibleTaskBarApp, "ColorInvisibleTaskBarApp", make_rgba(0.3, 0.3, 0.3));
    addColor("Invisible TaskBarAppTxt:", colorInvisibleTaskBarAppText, "ColorInvisibleTaskBarAppText", make_rgba(0.3, 0.3, 0.3));

    // === Quick Switch ===
    addCategory("Quick Switch");
    addColor("QuickSwitch:", colorQuickSwitch, "ColorQuickSwitch", make_rgba(0.7, 0.7, 0.7));
    addColor("QuickSwitch Border:", colorQuickSwitchBorder, "ColorQuickSwitchBorder", make_rgba(0.5, 0.5, 0.5));
    addColor("QuickSwitch Text:", colorQuickSwitchText, "ColorQuickSwitchText", make_rgba(0.0, 0.0, 0.0));
    addColor("QuickSwitch Active:", colorQuickSwitchActive, "ColorQuickSwitchActive", make_rgba(0.5, 0.5, 1.0));

    // === Move/Size Status ===
    addCategory("Move/Size Status");
    addColor("MoveSize Status:", colorMoveSizeStatus, "ColorMoveSizeStatus", make_rgba(0.7, 0.7, 0.7));
    addColor("MoveSize StatusTxt:", colorMoveSizeStatusText, "ColorMoveSizeStatusText", make_rgba(0.0, 0.0, 0.0));

    // Add scroll to main container
    add(*scroll);
    scroll->show();
    content->show();
    show_all_children();
}

void PrefColorsTab::loadPreferences(const std::map<std::string, std::string>& prefs) {
    auto loadColor = [&](Gtk::ColorButton* btn, const std::string& key, const Gdk::RGBA& defaultColor) {
        auto it = prefs.find(key);
        if (it != prefs.end()) {
            btn->set_rgba(parseColor(it->second));
        } else {
            btn->set_rgba(defaultColor);
        }
    };

    // Load all color preferences
    loadColor(colorDialog, "ColorDialog", make_rgba(0.5, 0.5, 0.5));
    loadColor(colorNormalBorder, "ColorNormalBorder", make_rgba(0.5, 0.5, 0.5));
    loadColor(colorActiveBorder, "ColorActiveBorder", make_rgba(0.8, 0.8, 0.8));
    loadColor(colorNormalTitleBar, "ColorNormalTitleBar", make_rgba(0.5, 0.5, 0.5));
    loadColor(colorNormalTitleBarText, "ColorNormalTitleBarText", make_rgba(0.0, 0.0, 0.0));
    loadColor(colorNormalTitleBarShadow, "ColorNormalTitleBarShadow", make_rgba(0.3, 0.3, 0.3));
    loadColor(colorActiveTitleBar, "ColorActiveTitleBar", make_rgba(0.0, 0.0, 1.0));
    loadColor(colorActiveTitleBarText, "ColorActiveTitleBarText", make_rgba(1.0, 1.0, 1.0));
    loadColor(colorActiveTitleBarShadow, "ColorActiveTitleBarShadow", make_rgba(0.3, 0.3, 0.3));
    // ... continue for all color buttons
}

void PrefColorsTab::savePreferences(std::map<std::string, std::string>& prefs) {
    auto saveColor = [&](Gtk::ColorButton* btn, const std::string& key) {
        prefs[key] = colorToString(btn->get_rgba());
    };

    // Save all color preferences
    saveColor(colorDialog, "ColorDialog");
    saveColor(colorNormalBorder, "ColorNormalBorder");
    saveColor(colorActiveBorder, "ColorActiveBorder");
    saveColor(colorNormalTitleBar, "ColorNormalTitleBar");
    saveColor(colorNormalTitleBarText, "ColorNormalTitleBarText");
    saveColor(colorNormalTitleBarShadow, "ColorNormalTitleBarShadow");
    saveColor(colorActiveTitleBar, "ColorActiveTitleBar");
    saveColor(colorActiveTitleBarText, "ColorActiveTitleBarText");
    saveColor(colorActiveTitleBarShadow, "ColorActiveTitleBarShadow");
    // ... continue for all color buttons
}

void PrefColorsTab::resetWidgets() {
    auto resetColor = [&](Gtk::ColorButton* btn, const Gdk::RGBA& defaultColor) {
        btn->set_rgba(defaultColor);
    };

    // Reset all colors to defaults
    resetColor(colorDialog, make_rgba(0.5, 0.5, 0.5));
    resetColor(colorNormalBorder, make_rgba(0.5, 0.5, 0.5));
    resetColor(colorActiveBorder, make_rgba(0.8, 0.8, 0.8));
    resetColor(colorNormalTitleBar, make_rgba(0.5, 0.5, 0.5));
    resetColor(colorNormalTitleBarText, make_rgba(0.0, 0.0, 0.0));
    resetColor(colorNormalTitleBarShadow, make_rgba(0.3, 0.3, 0.3));
    resetColor(colorActiveTitleBar, make_rgba(0.0, 0.0, 1.0));
    resetColor(colorActiveTitleBarText, make_rgba(1.0, 1.0, 1.0));
    resetColor(colorActiveTitleBarShadow, make_rgba(0.3, 0.3, 0.3));
    // ... continue for all color buttons
}

Gdk::RGBA PrefColorsTab::parseColor(const std::string& colorStr) {
    if (colorStr.empty()) return make_rgba(0.5, 0.5, 0.5);

    // Handle rgb:R/G/B format
    if (colorStr.substr(0, 4) == "rgb:") {
        std::string rgbPart = colorStr.substr(4);
        std::replace(rgbPart.begin(), rgbPart.end(), '/', ' ');
        std::istringstream iss(rgbPart);
        int r, g, b;
        if (iss >> r >> g >> b) {
            return make_rgba(r/255.0, g/255.0, b/255.0);
        }
    }

    // Handle hex format
    if (colorStr.substr(0, 1) == "#") {
        std::string hexPart = colorStr.substr(1);
        if (hexPart.length() == 6) {
            unsigned int color;
            std::stringstream ss;
            ss << std::hex << hexPart;
            ss >> color;
            int r = (color >> 16) & 0xFF;
            int g = (color >> 8) & 0xFF;
            int b = color & 0xFF;
            return make_rgba(r/255.0, g/255.0, b/255.0);
        }
    }

    return make_rgba(0.5, 0.5, 0.5); // Default fallback
}

std::string PrefColorsTab::colorToString(const Gdk::RGBA& color) {
    std::ostringstream oss;
    oss << "rgb:" << (int)(color.get_red() * 255) << "/" 
        << (int)(color.get_green() * 255) << "/" 
        << (int)(color.get_blue() * 255);
    return oss.str();
}

void PrefColorsTab::color_cb(Gtk::Widget* w, void* v) {
    // Color button callback - changes are handled when saving
}