#include <gtkmm.h>
#include <vector>
#include <string>
#include <cstdlib>
#include <fstream>
#include <map>
#include <array>
#include <sys/stat.h>
#include <dirent.h>
#include <ctime>
#include <cstring>
#include <sstream>

#include "EnvTab/EnvTab.h"
#include "KeysTab/KeysTab.h"
#include "MenuTab/MenuTab.h"
#include "PrefOverrideTab/PrefOverrideTab.h"
#include "PreferencesTab/PreferencesTab.h"
#include "ProgramsTab/ProgramsTab.h"
#include "ShutdownTab/ShutdownTab.h"
#include "SoundTab/SoundTab.h"
#include "StartupTab/StartupTab.h"
#include "PanelTab/PanelTab.h"
#include "ThemeTab/ThemeTab.h"
#include "WinOptionsTab/WinOptionsTab.h"
#include "TopMenuBar/File.h"
#include "TopMenuBar/IceWM.h"
#include "TopMenuBar/Help.h"

static std::string configDir;

class MainWindow : public Gtk::Window {
private:
    std::vector<Gtk::Button*> tabButtons;
    Gtk::Stack* stack;
    std::string configDir;

public:
    MainWindow(const std::string& cfgDir) : configDir(cfgDir) {
        set_title("IceWM Control Panel Plus");
        set_default_size(800, 600);
        
        // Main vertical box
        Gtk::Box* mainBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
        add(*mainBox);
        
        // Menu bar
        Gtk::MenuBar* menubar = Gtk::manage(new Gtk::MenuBar());
        mainBox->pack_start(*menubar, Gtk::PACK_SHRINK);
        
        // Setup menus
        TopMenuBar::File::setupMenu(menubar);
        TopMenuBar::IceWM::setupMenu(menubar);
        TopMenuBar::Help::setupMenu(menubar);
        
        // Horizontal box for nav buttons and content
        Gtk::Box* hbox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL));
        mainBox->pack_start(*hbox, Gtk::PACK_EXPAND_WIDGET);
        
        // Navigation buttons on left
        Gtk::Box* navBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL));
        navBox->set_spacing(5);
        navBox->set_margin_left(5);
        navBox->set_margin_top(5);
        navBox->set_margin_bottom(5);
        hbox->pack_start(*navBox, Gtk::PACK_SHRINK);
        
        const char* tabNames[] = {"Env", "Keys", "Menu", "Panel", "PrefOver", "Preferences", "Programs", "Shutdown", "Sound", "Startup", "Theme", "WinOpts"};
        int tabCount = 12;
        
        for (int i = 0; i < tabCount; i++) {
            Gtk::Button* btn = Gtk::manage(new Gtk::Button(tabNames[i]));
            btn->set_size_request(100, 35);
            if (i == 0) {
                btn->get_style_context()->add_class("suggested-action");
            }
            btn->signal_clicked().connect(sigc::bind(sigc::mem_fun(*this, &MainWindow::onNavButtonClicked), i));
            navBox->pack_start(*btn, Gtk::PACK_SHRINK);
            tabButtons.push_back(btn);
        }
        
        // Content area using Gtk::Stack for proper tab switching
        stack = Gtk::manage(new Gtk::Stack());
        stack->set_margin_left(5);
        stack->set_margin_right(5);
        stack->set_margin_top(5);
        stack->set_margin_bottom(5);
        stack->set_transition_type(Gtk::STACK_TRANSITION_TYPE_SLIDE_LEFT_RIGHT);
        stack->set_transition_duration(200);
        hbox->pack_start(*stack, Gtk::PACK_EXPAND_WIDGET);
        
        // Create tabs and add to stack
        EnvTab* envTab = Gtk::manage(new EnvTab(configDir));
        stack->add(*envTab, tabNames[0], "Environment");
        
        KeysTab* keysTab = Gtk::manage(new KeysTab(configDir));
        stack->add(*keysTab, tabNames[1], "Keys");
        
        MenuTab* menuTab = Gtk::manage(new MenuTab(configDir));
        stack->add(*menuTab, tabNames[2], "Menu");
        
        PanelTab* panelTab = Gtk::manage(new PanelTab(configDir));
        stack->add(*panelTab, tabNames[3], "Panel");
        
        PrefOverrideTab* prefOverrideTab = Gtk::manage(new PrefOverrideTab(configDir));
        stack->add(*prefOverrideTab, tabNames[4], "PrefOverride");
        
        PreferencesTab* preferencesTab = Gtk::manage(new PreferencesTab(configDir));
        stack->add(*preferencesTab, tabNames[5], "Preferences");
        
        ProgramsTab* programsTab = Gtk::manage(new ProgramsTab(configDir));
        stack->add(*programsTab, tabNames[6], "Programs");
        
        ShutdownTab* shutdownTab = Gtk::manage(new ShutdownTab(configDir));
        stack->add(*shutdownTab, tabNames[7], "Shutdown");
        
        SoundTab* soundTab = Gtk::manage(new SoundTab(configDir));
        stack->add(*soundTab, tabNames[8], "Sound");
        
        StartupTab* startupTab = Gtk::manage(new StartupTab(configDir));
        stack->add(*startupTab, tabNames[9], "Startup");
        
        ThemeTab* themeTab = Gtk::manage(new ThemeTab(configDir));
        stack->add(*themeTab, tabNames[10], "Theme");
        // Apply IceWM theme now that the ThemeTab (and GTK screen) exist
        ThemeTab::applyIceWMThemeToUI(configDir);
        
        WinOptionsTab* winOptionsTab = Gtk::manage(new WinOptionsTab(configDir));
        stack->add(*winOptionsTab, tabNames[11], "WinOptions");
        
        show_all_children();
    }
    
    void onNavButtonClicked(int idx) {
        const char* tabNames[] = {"Env", "Keys", "Menu", "Panel", "PrefOver", "Preferences", "Programs", "Shutdown", "Sound", "Startup", "Theme", "WinOpts"};
        const char* targetName = tabNames[idx];
        const std::string currentName = stack->get_visible_child_name();
        
        if (currentName == targetName) return;
        
        // Switch stack page
        stack->set_visible_child(targetName);
        
        // Update button styles
        for (size_t i = 0; i < tabButtons.size(); i++) {
            if (tabNames[i] == currentName) {
                tabButtons[i]->get_style_context()->remove_class("suggested-action");
            }
        }
        tabButtons[idx]->get_style_context()->add_class("suggested-action");
    }
};

int main(int argc, char **argv) {
    auto app = Gtk::Application::create(argc, argv, "org.icewm.control-panel-plus");
    
    // Get IceWM config dir
    const char* xdg = getenv("XDG_CONFIG_HOME");
    if (xdg && *xdg) {
        std::string path = std::string(xdg) + "/icewm";
        struct stat st;
        if (stat(path.c_str(), &st) == 0 && S_ISDIR(st.st_mode)) {
            configDir = path;
        }
    }
    if (configDir.empty()) {
        const char* home = getenv("HOME");
        if (home) configDir = std::string(home) + "/.icewm";
    }
    
    // Apply the current IceWM theme to the GTK UI BEFORE creating any widgets
    // This is similar to FLTK's syncThemeToFLTK being called before widget creation
    ThemeTab::applyIceWMThemeToUI(configDir);
    
    MainWindow window(configDir);
    
    return app->run(window);
}
