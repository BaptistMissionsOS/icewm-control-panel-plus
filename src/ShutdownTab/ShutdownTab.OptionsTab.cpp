#include "ShutdownTab.OptionsTab.h"

ShutdownOptionsTab::ShutdownOptionsTab() : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5) {
    set_margin_left(20);
    set_margin_top(10);
    confirmShutdownCheck = Gtk::manage(new Gtk::CheckButton("Confirm before shutdown"));
    confirmShutdownCheck->set_active(true);
    pack_start(*confirmShutdownCheck, Gtk::PACK_SHRINK);
    showLogoutCheck = Gtk::manage(new Gtk::CheckButton("Show Logout button"));
    showLogoutCheck->set_active(true);
    pack_start(*showLogoutCheck, Gtk::PACK_SHRINK);
    showRebootCheck = Gtk::manage(new Gtk::CheckButton("Show Reboot button"));
    showRebootCheck->set_active(true);
    pack_start(*showRebootCheck, Gtk::PACK_SHRINK);
    showShutdownCheck = Gtk::manage(new Gtk::CheckButton("Show Shutdown button"));
    showShutdownCheck->set_active(true);
    pack_start(*showShutdownCheck, Gtk::PACK_SHRINK);
    showSuspendCheck = Gtk::manage(new Gtk::CheckButton("Show Suspend button"));
    pack_start(*showSuspendCheck, Gtk::PACK_SHRINK);
    showHibernateCheck = Gtk::manage(new Gtk::CheckButton("Show Hibernate button"));
    pack_start(*showHibernateCheck, Gtk::PACK_SHRINK);
}

void ShutdownOptionsTab::setDefaults() {
    confirmShutdownCheck->set_active(true);
    showLogoutCheck->set_active(true);
    showRebootCheck->set_active(true);
    showShutdownCheck->set_active(true);
    showSuspendCheck->set_active(false);
    showHibernateCheck->set_active(false);
}
