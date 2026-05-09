#pragma once

#include <gtkmm.h>

/**
 * GTKmm implementation of the Windows tab for preference overrides.
 * Provides a set of check‑buttons mirroring the original FLTK UI.
 */
class PrefOverrideTabWindowsTab : public Gtk::Box {
public:
    PrefOverrideTabWindowsTab();
    ~PrefOverrideTabWindowsTab() override = default;

private:
    Gtk::Grid m_grid;
    Gtk::CheckButton m_focusNew;
    Gtk::CheckButton m_focusClick;
    Gtk::CheckButton m_focusMouse;
    Gtk::CheckButton m_focusRaise;
    Gtk::CheckButton m_focusRaiseOnClick;
};
