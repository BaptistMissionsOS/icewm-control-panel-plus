#include "SoundTab.SettingsTab.h"

SoundSettingsTab::SoundSettingsTab() : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5) {
    set_margin_left(10);
    set_margin_top(10);
    
    enableSoundsCheck = Gtk::manage(new Gtk::CheckButton("Enable Sounds"));
    enableSoundsCheck->set_active(true);
    pack_start(*enableSoundsCheck, Gtk::PACK_SHRINK);
    
    auto* r1 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* l1 = Gtk::manage(new Gtk::Label("Player:"));
    l1->set_size_request(100, -1);
    playerCmdEntry = Gtk::manage(new Gtk::Entry());
    playerCmdEntry->set_text("aplay");
    playerCmdEntry->set_tooltip_text("Sound player command (aplay, paplay, etc.)");
    playerCmdEntry->set_hexpand(true);
    r1->pack_start(*l1, Gtk::PACK_SHRINK);
    r1->pack_start(*playerCmdEntry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*r1, Gtk::PACK_SHRINK);
    
    auto* r2 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* l2 = Gtk::manage(new Gtk::Label("Interface:"));
    l2->set_size_request(100, -1);
    interfaceCombo = Gtk::manage(new Gtk::ComboBoxText());
    interfaceCombo->append("AO");
    interfaceCombo->append("ALSA");
    interfaceCombo->append("OSS");
    interfaceCombo->set_active(0);
    interfaceCombo->set_tooltip_text("Audio output interface");
    r2->pack_start(*l2, Gtk::PACK_SHRINK);
    r2->pack_start(*interfaceCombo, Gtk::PACK_SHRINK);
    pack_start(*r2, Gtk::PACK_SHRINK);
    
    auto* r3 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* l3 = Gtk::manage(new Gtk::Label("OSS Device:"));
    l3->set_size_request(100, -1);
    ossDeviceEntry = Gtk::manage(new Gtk::Entry());
    ossDeviceEntry->set_text("/dev/dsp");
    ossDeviceEntry->set_tooltip_text("OSS device path");
    ossDeviceEntry->set_hexpand(true);
    r3->pack_start(*l3, Gtk::PACK_SHRINK);
    r3->pack_start(*ossDeviceEntry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*r3, Gtk::PACK_SHRINK);
    
    auto* r4 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* l4 = Gtk::manage(new Gtk::Label("ALSA Device:"));
    l4->set_size_request(100, -1);
    alsaDeviceEntry = Gtk::manage(new Gtk::Entry());
    alsaDeviceEntry->set_text("default");
    alsaDeviceEntry->set_tooltip_text("ALSA device name");
    alsaDeviceEntry->set_hexpand(true);
    r4->pack_start(*l4, Gtk::PACK_SHRINK);
    r4->pack_start(*alsaDeviceEntry, Gtk::PACK_EXPAND_WIDGET);
    pack_start(*r4, Gtk::PACK_SHRINK);
    
    auto* r5 = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    auto* l5 = Gtk::manage(new Gtk::Label("Snooze (ms):"));
    l5->set_size_request(100, -1);
    auto adj = Gtk::Adjustment::create(500, 0, 5000, 50);
    snoozeSpin = Gtk::manage(new Gtk::SpinButton(adj, 50));
    snoozeSpin->set_tooltip_text("Snooze interval between sound events");
    r5->pack_start(*l5, Gtk::PACK_SHRINK);
    r5->pack_start(*snoozeSpin, Gtk::PACK_SHRINK);
    pack_start(*r5, Gtk::PACK_SHRINK);
    
    verboseCheck = Gtk::manage(new Gtk::CheckButton("Verbose Mode"));
    verboseCheck->set_tooltip_text("Enable verbose sound output");
    pack_start(*verboseCheck, Gtk::PACK_SHRINK);
}

void SoundSettingsTab::setDefaults() {
    enableSoundsCheck->set_active(true);
    playerCmdEntry->set_text("aplay");
    interfaceCombo->set_active(0);
    ossDeviceEntry->set_text("/dev/dsp");
    alsaDeviceEntry->set_text("default");
    snoozeSpin->set_value(500);
    verboseCheck->set_active(false);
}
