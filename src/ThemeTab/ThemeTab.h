#ifndef THEMETAB_H
#define THEMETAB_H

#include <gtkmm.h>
#include <string>
#include <vector>
#include <map>

// Include subtab headers
#include "ThemeTab.ColorsTab.h"
#include "ThemeTab.DesktopTab.h"
#include "ThemeTab.ExploreTab.h"
#include "ThemeTab.FontsTab.h"
#include "ThemeTab.IconsTab.h"
#include "ThemeTab.StylesTab.h"
#include "ThemeTab.ToolsTab.h"

class ThemeTab : public Gtk::Box {
private:
    std::string configDir;
    Gtk::Notebook *notebook;

    // Theme selector widgets
    Gtk::ComboBoxText *themeSelector;
    std::vector<std::string> themeNames;

    // Theme properties map and flag
    std::map<std::string, std::string> themeProperties;
    bool themeLoaded = false;

    // Subtab pointers
    ColorsTab *colorsTab;
    DesktopTab *desktopTab;
    ExploreTab *exploreTab;
    StylesTab *stylesTab;
    ToolsTab *toolsTab;
    FontsTab *fontsTab;
    IconsTab *iconsTab;

    // Private helper methods
    void init_widgets();
    void scanThemes();
    void loadCurrentTheme();
    void applyTheme();
    void saveTheme();
    void onThemeSelected();

    // Theme property management
    void loadThemeProperties();
    void saveThemeProperties();
    void updateEditorFromProperties();
    void updatePropertiesFromEditor();
    void resetToDefaults();

    // Theme creation
    void onNewTheme();
    void onResetTheme();

public:
    ThemeTab(const std::string& configDir);
    ~ThemeTab();
    void refresh();
    static void applyIceWMThemeToUI(const std::string& configDir, const std::string& themeNameOverride = "");
    
private:
    static Glib::RefPtr<Gtk::CssProvider> cssProvider;
};

#endif
