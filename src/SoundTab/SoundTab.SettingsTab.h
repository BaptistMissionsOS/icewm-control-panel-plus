#ifndef SOUNDTAB_SETTINGSTAB_H
#define SOUNDTAB_SETTINGSTAB_H

#include <gtkmm.h>

class SoundSettingsTab : public Gtk::Box {
private:
    Gtk::CheckButton *enableSoundsCheck;
    Gtk::Entry *playerCmdEntry;
    Gtk::ComboBoxText *interfaceCombo;
    Gtk::Entry *ossDeviceEntry;
    Gtk::Entry *alsaDeviceEntry;
    Gtk::SpinButton *snoozeSpin;
    Gtk::CheckButton *verboseCheck;

public:
    SoundSettingsTab();
    
    bool getEnableSounds() const { return enableSoundsCheck->get_active(); }
    Glib::ustring getPlayerCmd() const { return playerCmdEntry->get_text(); }
    int getInterface() const { return interfaceCombo->get_active_row_number(); }
    Glib::ustring getOssDevice() const { return ossDeviceEntry->get_text(); }
    Glib::ustring getAlsaDevice() const { return alsaDeviceEntry->get_text(); }
    int getSnooze() const { return snoozeSpin->get_value_as_int(); }
    bool getVerbose() const { return verboseCheck->get_active(); }
    
    void setEnableSounds(bool v) { enableSoundsCheck->set_active(v); }
    void setPlayerCmd(const Glib::ustring& v) { playerCmdEntry->set_text(v); }
    void setInterface(int v) { interfaceCombo->set_active(v); }
    void setOssDevice(const Glib::ustring& v) { ossDeviceEntry->set_text(v); }
    void setAlsaDevice(const Glib::ustring& v) { alsaDeviceEntry->set_text(v); }
    void setSnooze(int v) { snoozeSpin->set_value(v); }
    void setVerbose(bool v) { verboseCheck->set_active(v); }
    
    void setDefaults();
};

#endif