#include "SoundTab.EventsTab.h"

SoundEventsTab::SoundEventsTab() : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5) {
    set_margin_left(10);
    set_margin_top(10);
    auto* r = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* l = Gtk::manage(new Gtk::Label("Startup:"));
    l->set_size_request(120, -1);
    startupSoundEntry = Gtk::manage(new Gtk::Entry());
    startupSoundEntry->set_hexpand(true);
    startupSoundEntry->set_tooltip_text("Path to startup sound file");
    r->pack_start(*l, Gtk::PACK_SHRINK);
    r->pack_start(*startupSoundEntry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*r, Gtk::PACK_SHRINK);
    auto* r2 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* l2 = Gtk::manage(new Gtk::Label("Shutdown:"));
    l2->set_size_request(120, -1);
    shutdownSoundEntry = Gtk::manage(new Gtk::Entry());
    shutdownSoundEntry->set_hexpand(true);
    shutdownSoundEntry->set_tooltip_text("Path to shutdown sound file");
    r2->pack_start(*l2, Gtk::PACK_SHRINK);
    r2->pack_start(*shutdownSoundEntry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*r2, Gtk::PACK_SHRINK);
    auto* r3 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* l3 = Gtk::manage(new Gtk::Label("Window Open:"));
    l3->set_size_request(120, -1);
    windowOpenEntry = Gtk::manage(new Gtk::Entry());
    windowOpenEntry->set_hexpand(true);
    windowOpenEntry->set_tooltip_text("Path to window open sound");
    r3->pack_start(*l3, Gtk::PACK_SHRINK);
    r3->pack_start(*windowOpenEntry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*r3, Gtk::PACK_SHRINK);
    auto* r4 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* l4 = Gtk::manage(new Gtk::Label("Window Close:"));
    l4->set_size_request(120, -1);
    windowCloseEntry = Gtk::manage(new Gtk::Entry());
    windowCloseEntry->set_hexpand(true);
    windowCloseEntry->set_tooltip_text("Path to window close sound");
    r4->pack_start(*l4, Gtk::PACK_SHRINK);
    r4->pack_start(*windowCloseEntry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*r4, Gtk::PACK_SHRINK);
    auto* r5 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* l5 = Gtk::manage(new Gtk::Label("Workspace:"));
    l5->set_size_request(120, -1);
    workspaceChangeEntry = Gtk::manage(new Gtk::Entry());
    workspaceChangeEntry->set_hexpand(true);
    workspaceChangeEntry->set_tooltip_text("Path to workspace change sound");
    r5->pack_start(*l5, Gtk::PACK_SHRINK);
    r5->pack_start(*workspaceChangeEntry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*r5, Gtk::PACK_SHRINK);
    auto* r6 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* l6 = Gtk::manage(new Gtk::Label("Alert:"));
    l6->set_size_request(120, -1);
    alertSoundEntry = Gtk::manage(new Gtk::Entry());
    alertSoundEntry->set_hexpand(true);
    alertSoundEntry->set_tooltip_text("Path to alert/error sound");
    r6->pack_start(*l6, Gtk::PACK_SHRINK);
    r6->pack_start(*alertSoundEntry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*r6, Gtk::PACK_SHRINK);
}

void SoundEventsTab::setDefaults() {
    startupSoundEntry->set_text("");
    shutdownSoundEntry->set_text("");
    windowOpenEntry->set_text("");
    windowCloseEntry->set_text("");
    workspaceChangeEntry->set_text("");
    alertSoundEntry->set_text("");
}
