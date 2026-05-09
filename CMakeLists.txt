cmake_minimum_required(VERSION 3.16)
project(IceWMControlPanelPlus VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find gtkmm-3.0
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM REQUIRED gtkmm-3.0)

# Source files
set(SOURCES
    src/main.cpp
    src/TopMenuBar/File.cpp
    src/TopMenuBar/IceWM.cpp
    src/TopMenuBar/Help.cpp
    src/EnvTab/EnvTab.cpp
    src/EnvTab/EnvTab.SessionTab.cpp
    src/EnvTab/EnvTab.AppearanceTab.cpp
    src/EnvTab/EnvTab.SessionTab.InputMethodTab.cpp
    src/EnvTab/EnvTab.ProgramsTab.cpp
    src/EnvTab/EnvTab.CustomTab.cpp
    src/KeysTab/KeysTab.cpp
    src/MenuTab/MenuTab.cpp
    src/PrefOverrideTab/PrefOverrideTab.cpp
    src/PrefOverrideTab/PrefOverrideTab.EdgeSwitchTab.cpp
    src/PrefOverrideTab/PrefOverrideTab.FocusTab.cpp
    src/PrefOverrideTab/PrefOverrideTab.QuickSwitchTab.cpp
    src/PrefOverrideTab/PrefOverrideTab.TaskbarTab.cpp
    src/PrefOverrideTab/PrefOverrideTab.ThemeTab.cpp
    src/PrefOverrideTab/PrefOverrideTab.TimingsTab.cpp
    src/PrefOverrideTab/PrefOverrideTab.WindowsTab.cpp
    src/PreferencesTab/PreferencesTab.cpp
    src/PreferencesTab/PreferencesTab.AppearanceTab.cpp
    src/PreferencesTab/PreferencesTab.ColorsTab.cpp
    src/PreferencesTab/PreferencesTab.DesktopTab.cpp
    src/PreferencesTab/PreferencesTab.FontsTab.cpp
    src/PreferencesTab/PreferencesTab.KeysTab.cpp
    src/PreferencesTab/PreferencesTab.TaskBarTab.cpp
    src/PreferencesTab/PreferencesTab.WindowsTab.cpp
    src/ProgramsTab/ProgramsTab.cpp
    src/ShutdownTab/ShutdownTab.cpp
    src/ShutdownTab/ShutdownTab.OptionsTab.cpp
    src/ShutdownTab/ShutdownTab.CommandsTab.cpp
    src/SoundTab/SoundTab.cpp
    src/SoundTab/SoundTab.EventsTab.cpp
    src/SoundTab/SoundTab.SettingsTab.cpp
    src/StartupTab/StartupTab.cpp
    src/PanelTab/PanelTab.cpp
    src/ThemeTab/ThemeTab.cpp
    src/ThemeTab/ThemeTab.ColorsTab.cpp
    src/ThemeTab/ThemeTab.DesktopTab.cpp
    src/ThemeTab/ThemeTab.ExploreTab.cpp
    src/ThemeTab/ThemeTab.StylesTab.cpp
    src/ThemeTab/ThemeTab.ToolsTab.cpp
    src/WinOptionsTab/WinOptionsTab.cpp
    src/ThemeTab/ThemeTab.FontsTab.cpp
    src/ThemeTab/ThemeTab.IconsTab.cpp
)

# Header files
set(HEADERS
    src/TopMenuBar/File.h
    src/TopMenuBar/IceWM.h
    src/TopMenuBar/Help.h
    src/EnvTab/EnvTab.h
    src/EnvTab/EnvTab.SessionTab.h
    src/EnvTab/EnvTab.AppearanceTab.h
    src/EnvTab/EnvTab.SessionTab.InputMethodTab.h
    src/EnvTab/EnvTab.ProgramsTab.h
    src/EnvTab/EnvTab.CustomTab.h
    src/KeysTab/KeysTab.h
    src/MenuTab/MenuTab.h
    src/PrefOverrideTab/PrefOverrideTab.h
    src/PreferencesTab/PreferencesTab.h
    src/PreferencesTab/PreferencesTab.AppearanceTab.h
    src/PreferencesTab/PreferencesTab.ColorsTab.h
    src/PreferencesTab/PreferencesTab.DesktopTab.h
    src/PreferencesTab/PreferencesTab.FontsTab.h
    src/PreferencesTab/PreferencesTab.KeysTab.h
    src/PreferencesTab/PreferencesTab.TaskBarTab.h
    src/PreferencesTab/PreferencesTab.WindowsTab.h
    src/ProgramsTab/ProgramsTab.h
    src/ShutdownTab/ShutdownTab.h
    src/ShutdownTab/ShutdownTab.OptionsTab.h
    src/ShutdownTab/ShutdownTab.CommandsTab.h
    src/SoundTab/SoundTab.h
    src/SoundTab/SoundTab.EventsTab.h
    src/SoundTab/SoundTab.SettingsTab.h
    src/StartupTab/StartupTab.h
    src/PanelTab/PanelTab.h
    src/ThemeTab/ThemeTab.h
    src/ThemeTab/ThemeTab.ColorsTab.h
    src/ThemeTab/ThemeTab.DesktopTab.h
    src/ThemeTab/ThemeTab.ExploreTab.h
    src/ThemeTab/ThemeTab.StylesTab.h
    src/ThemeTab/ThemeTab.ToolsTab.h
    src/WinOptionsTab/WinOptionsTab.h
)

# Create executable
add_executable(icewm-control-panel-plus ${SOURCES} ${HEADERS})

target_include_directories(icewm-control-panel-plus PRIVATE ${GTKMM_INCLUDE_DIRS})
target_link_libraries(icewm-control-panel-plus PRIVATE ${GTKMM_LIBRARIES})

# Install target
install(TARGETS icewm-control-panel-plus DESTINATION bin)
install(FILES icewm-control-panel-plus.desktop DESTINATION /usr/local/share/applications)
