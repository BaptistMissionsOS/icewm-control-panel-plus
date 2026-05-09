#include "PrefOverrideTab.WindowsTab.h"

PrefOverrideTabWindowsTab::PrefOverrideTabWindowsTab()
    : Gtk::Box(Gtk::ORIENTATION_VERTICAL),
      m_focusNew("Focus New Windows"),
      m_focusClick("Focus Click"),
      m_focusMouse("Focus Mouse"),
      m_focusRaise("Focus Raise"),
      m_focusRaiseOnClick("Focus Raise On Click") {
    set_spacing(10);

    m_grid.set_row_spacing(5);
    m_grid.set_column_spacing(10);
    m_grid.set_margin_start(10);
    m_grid.set_margin_end(10);
    m_grid.set_margin_top(10);
    m_grid.set_margin_bottom(10);

    m_grid.attach(m_focusNew, 0, 0, 1, 1);
    m_grid.attach(m_focusClick, 1, 0, 1, 1);
    m_grid.attach(m_focusMouse, 0, 1, 1, 1);
    m_grid.attach(m_focusRaise, 1, 1, 1, 1);
    m_grid.attach(m_focusRaiseOnClick, 0, 2, 2, 1);

    pack_start(m_grid, Gtk::PACK_SHRINK);
    show_all_children();
}
