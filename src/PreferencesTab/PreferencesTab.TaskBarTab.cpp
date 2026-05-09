#include "PreferencesTab.TaskBarTab.h"
#include <gtkmm.h>
#include <string>
#include <map>
#include <sigc++/sigc++.h>

PrefTaskBarTab::PrefTaskBarTab(const std::string& configDir) : Gtk::Box(Gtk::ORIENTATION_VERTICAL, 10) {
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

    // === TaskBar Position and Appearance ===
    Gtk::Box* positionBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    auto* posLabel = Gtk::manage(new Gtk::Label("TaskBar Position and Appearance"));
    posLabel->set_halign(Gtk::ALIGN_START);
    positionBox->pack_start(*posLabel, Gtk::PACK_SHRINK);
    positionBox->set_halign(Gtk::ALIGN_START);
    positionBox->show();
    content->pack_start(*positionBox, Gtk::PACK_SHRINK);

    // Show TaskBar
    showTaskBar = new Gtk::CheckButton("Show TaskBar");
    showTaskBar->set_active(true);
    showTaskBar->show();
    positionBox->pack_start(*showTaskBar, Gtk::PACK_SHRINK);

    // TaskBar at Top
    taskBarAtTop = new Gtk::CheckButton("TaskBar at Top");
    taskBarAtTop->show();
    positionBox->pack_start(*taskBarAtTop, Gtk::PACK_SHRINK);

    // Auto Hide TaskBar
    taskBarAutoHide = new Gtk::CheckButton("Auto Hide TaskBar");
    taskBarAutoHide->show();
    positionBox->pack_start(*taskBarAutoHide, Gtk::PACK_SHRINK);

    // Double Height TaskBar
    taskBarDoubleHeight = new Gtk::CheckButton("Double Height TaskBar");
    taskBarDoubleHeight->show();
    positionBox->pack_start(*taskBarDoubleHeight, Gtk::PACK_SHRINK);

    // Keep TaskBar Below
    taskBarKeepBelow = new Gtk::CheckButton("Keep TaskBar Below");
    taskBarKeepBelow->show();
    positionBox->pack_start(*taskBarKeepBelow, Gtk::PACK_SHRINK);

    // Width Percentage
    Gtk::Frame* widthFrame = Gtk::manage(new Gtk::Frame("Width Percentage:"));
    Gtk::Box* widthBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    taskBarWidthPercentage = Gtk::manage(new Gtk::SpinButton());
    taskBarWidthPercentage->set_range(0, 100);
    taskBarWidthPercentage->set_increments(1, 5);
    widthBox->pack_start(*taskBarWidthPercentage, Gtk::PACK_SHRINK);
    widthFrame->add(*widthBox);
    positionBox->pack_start(*widthFrame, Gtk::PACK_SHRINK);

    // Workspaces on Left/Top
    Gtk::Box* workspaceBox = new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5);
    taskBarWorkspacesLeft = new Gtk::CheckButton("Workspaces on Left");
    taskBarWorkspacesTop = new Gtk::CheckButton("Workspaces on Top");
    workspaceBox->pack_start(*taskBarWorkspacesLeft, Gtk::PACK_SHRINK);
    workspaceBox->pack_start(*taskBarWorkspacesTop, Gtk::PACK_SHRINK);
    positionBox->pack_start(*workspaceBox, Gtk::PACK_SHRINK);

    // Workspaces Limit
    Gtk::Frame* limitFrame = Gtk::manage(new Gtk::Frame("Workspaces Limit:"));
    Gtk::Box* limitBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    taskBarWorkspacesLimit = Gtk::manage(new Gtk::Entry());
    taskBarWorkspacesLimit->set_max_width_chars(10);
    limitBox->pack_start(*taskBarWorkspacesLimit, Gtk::PACK_SHRINK);
    limitFrame->add(*limitBox);
    positionBox->pack_start(*limitFrame, Gtk::PACK_SHRINK);

    // Button Width Divisor
    Gtk::Frame* divisorFrame = Gtk::manage(new Gtk::Frame("Button Width Divisor:"));
    Gtk::Box* divisorBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    taskbarButtonWidthDivisor = Gtk::manage(new Gtk::SpinButton());
    taskbarButtonWidthDivisor->set_range(1, 50);
    taskbarButtonWidthDivisor->set_increments(1, 5);
    divisorBox->pack_start(*taskbarButtonWidthDivisor, Gtk::PACK_SHRINK);
    divisorFrame->add(*divisorBox);
    positionBox->pack_start(*divisorFrame, Gtk::PACK_SHRINK);

    // Icon Offset
    Gtk::Frame* offsetFrame = Gtk::manage(new Gtk::Frame("Icon Offset:"));
    Gtk::Box* offsetBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    taskbuttonIconOffset = Gtk::manage(new Gtk::SpinButton());
    taskbuttonIconOffset->set_range(0, 16);
    taskbuttonIconOffset->set_increments(1, 5);
    offsetBox->pack_start(*taskbuttonIconOffset, Gtk::PACK_SHRINK);
    offsetFrame->add(*offsetBox);
    positionBox->pack_start(*offsetFrame, Gtk::PACK_SHRINK);

    // === TaskBar Visibility Options ===
    Gtk::Frame* visibilityFrame = Gtk::manage(new Gtk::Frame("TaskBar Visibility Options"));
    Gtk::Box* visibilityBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    visibilityBox->set_halign(Gtk::ALIGN_START);
    visibilityFrame->add(*visibilityBox);
    content->pack_start(*visibilityFrame, Gtk::PACK_SHRINK);

    // Fullscreen Auto Show
    taskBarFullscreenAutoShow = new Gtk::CheckButton("Fullscreen Auto Show");
    taskBarFullscreenAutoShow->show();
    visibilityBox->pack_start(*taskBarFullscreenAutoShow, Gtk::PACK_SHRINK);

    // Show All Windows
    taskBarShowAllWindows = new Gtk::CheckButton("Show All Windows");
    taskBarShowAllWindows->show();
    visibilityBox->pack_start(*taskBarShowAllWindows, Gtk::PACK_SHRINK);

    // Show Window Icons
    taskBarShowWindowIcons = new Gtk::CheckButton("Show Window Icons");
    taskBarShowWindowIcons->show();
    visibilityBox->pack_start(*taskBarShowWindowIcons, Gtk::PACK_SHRINK);

    // Show Window Titles
    taskBarShowWindowTitles = new Gtk::CheckButton("Show Window Titles");
    taskBarShowWindowTitles->show();
    visibilityBox->pack_start(*taskBarShowWindowTitles, Gtk::PACK_SHRINK);

    // Show Transient Windows
    taskBarShowTransientWindows = new Gtk::CheckButton("Show Transient Windows");
    taskBarShowTransientWindows->show();
    visibilityBox->pack_start(*taskBarShowTransientWindows, Gtk::PACK_SHRINK);

    // Show Clock
    taskBarShowClock = new Gtk::CheckButton("Show Clock");
    taskBarShowClock->show();
    visibilityBox->pack_start(*taskBarShowClock, Gtk::PACK_SHRINK);

    // Clock LEDs
    taskBarClockLeds = new Gtk::CheckButton("Clock LEDs");
    taskBarClockLeds->show();
    visibilityBox->pack_start(*taskBarClockLeds, Gtk::PACK_SHRINK);

    // Show Show Desktop Button
    taskBarShowShowDesktopButton = new Gtk::CheckButton("Show Desktop Button");
    taskBarShowShowDesktopButton->show();
    visibilityBox->pack_start(*taskBarShowShowDesktopButton, Gtk::PACK_SHRINK);

    // Show Start Menu
    taskBarShowStartMenu = new Gtk::CheckButton("Show Start Menu");
    taskBarShowStartMenu->show();
    visibilityBox->pack_start(*taskBarShowStartMenu, Gtk::PACK_SHRINK);

    // Show Window List Menu
    taskBarShowWindowListMenu = new Gtk::CheckButton("Show Window List Menu");
    taskBarShowWindowListMenu->show();
    visibilityBox->pack_start(*taskBarShowWindowListMenu, Gtk::PACK_SHRINK);

    // Show Collapse Button
    taskBarShowCollapseButton = new Gtk::CheckButton("Show Collapse Button");
    taskBarShowCollapseButton->show();
    visibilityBox->pack_start(*taskBarShowCollapseButton, Gtk::PACK_SHRINK);

    // Show Workspaces
    taskBarShowWorkspaces = new Gtk::CheckButton("Show Workspaces");
    taskBarShowWorkspaces->show();
    visibilityBox->pack_start(*taskBarShowWorkspaces, Gtk::PACK_SHRINK);

    // Show Pager
    taskBarShowPager = new Gtk::CheckButton("Show Pager");
    taskBarShowPager->show();
    visibilityBox->pack_start(*taskBarShowPager, Gtk::PACK_SHRINK);

    // Show Tray
    taskBarShowTray = new Gtk::CheckButton("Show Tray");
    taskBarShowTray->show();
    visibilityBox->pack_start(*taskBarShowTray, Gtk::PACK_SHRINK);

    // Enable System Tray
    taskBarEnableSystemTray = new Gtk::CheckButton("Enable System Tray");
    taskBarEnableSystemTray->show();
    visibilityBox->pack_start(*taskBarEnableSystemTray, Gtk::PACK_SHRINK);

    // === TaskBar Behavior ===
    Gtk::Frame* behaviorFrame = Gtk::manage(new Gtk::Frame("TaskBar Behavior"));
    Gtk::Box* behaviorBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    behaviorBox->set_halign(Gtk::ALIGN_START);
    behaviorFrame->add(*behaviorBox);
    content->pack_start(*behaviorFrame, Gtk::PACK_SHRINK);

    // Launch on Single Click
    taskBarLaunchOnSingleClick = new Gtk::CheckButton("Launch on Single Click");
    taskBarLaunchOnSingleClick->show();
    behaviorBox->pack_start(*taskBarLaunchOnSingleClick, Gtk::PACK_SHRINK);

    // Use Mouse Wheel
    taskBarUseMouseWheel = new Gtk::CheckButton("Use Mouse Wheel");
    taskBarUseMouseWheel->show();
    behaviorBox->pack_start(*taskBarUseMouseWheel, Gtk::PACK_SHRINK);

    // Task Grouping
    Gtk::Frame* groupingFrame = Gtk::manage(new Gtk::Frame("Task Grouping:"));
    Gtk::Box* groupingBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    taskBarTaskGrouping = Gtk::manage(new Gtk::SpinButton());
    taskBarTaskGrouping->set_range(0, 3);
    taskBarTaskGrouping->set_increments(1, 1);
    groupingBox->pack_start(*taskBarTaskGrouping, Gtk::PACK_SHRINK);
    groupingFrame->add(*groupingBox);
    behaviorBox->pack_start(*groupingFrame, Gtk::PACK_SHRINK);

    // === Status Monitoring ===
    Gtk::Frame* statusFrame = Gtk::manage(new Gtk::Frame("Status Monitoring"));
    Gtk::Box* statusBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    statusBox->set_halign(Gtk::ALIGN_START);
    statusFrame->add(*statusBox);
    content->pack_start(*statusFrame, Gtk::PACK_SHRINK);

    // Show CPU Status
    taskBarShowCPUStatus = new Gtk::CheckButton("Show CPU Status");
    taskBarShowCPUStatus->show();
    statusBox->pack_start(*taskBarShowCPUStatus, Gtk::PACK_SHRINK);

    // CPU Delay
    Gtk::Frame* cpuDelayFrame = Gtk::manage(new Gtk::Frame("CPU Delay (ms):"));
    Gtk::Box* cpuDelayBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    taskBarCPUdelay = Gtk::manage(new Gtk::SpinButton());
    taskBarCPUdelay->set_range(0, 10000);
    taskBarCPUdelay->set_increments(100, 500);
    cpuDelayBox->pack_start(*taskBarCPUdelay, Gtk::PACK_SHRINK);
    cpuDelayFrame->add(*cpuDelayBox);
    statusBox->pack_start(*cpuDelayFrame, Gtk::PACK_SHRINK);

    // CPU Samples
    Gtk::Frame* cpuSamplesFrame = Gtk::manage(new Gtk::Frame("CPU Samples:"));
    Gtk::Box* cpuSamplesBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    taskBarCPUsamples = Gtk::manage(new Gtk::SpinButton());
    taskBarCPUsamples->set_range(0, 1000);
    taskBarCPUsamples->set_increments(10, 100);
    cpuSamplesBox->pack_start(*taskBarCPUsamples, Gtk::PACK_SHRINK);
    cpuSamplesFrame->add(*cpuSamplesBox);
    statusBox->pack_start(*cpuSamplesFrame, Gtk::PACK_SHRINK);

    // Show MEM Status
    taskBarShowMEMStatus = new Gtk::CheckButton("Show MEM Status");
    taskBarShowMEMStatus->show();
    statusBox->pack_start(*taskBarShowMEMStatus, Gtk::PACK_SHRINK);

    // MEM Delay
    Gtk::Frame* memDelayFrame = Gtk::manage(new Gtk::Frame("MEM Delay (ms):"));
    Gtk::Box* memDelayBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    taskBarMEMDelay = Gtk::manage(new Gtk::SpinButton());
    taskBarMEMDelay->set_range(0, 10000);
    taskBarMEMDelay->set_increments(100, 500);
    memDelayBox->pack_start(*taskBarMEMDelay, Gtk::PACK_SHRINK);
    memDelayFrame->add(*memDelayBox);
    taskBarMEMDelay->set_range(10, 3600000);
    memDelayBox->pack_start(*taskBarMEMDelay, Gtk::PACK_SHRINK);
    statusBox->pack_start(*memDelayBox, Gtk::PACK_SHRINK);

    // MEM Samples
    Gtk::Frame* memSamplesFrame = Gtk::manage(new Gtk::Frame("MEM Samples:"));
    Gtk::Box* memSamplesBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    taskBarMEMsamples = Gtk::manage(new Gtk::SpinButton());
    taskBarMEMsamples->set_range(0, 1000);
    taskBarMEMsamples->set_increments(10, 100);
    memSamplesBox->pack_start(*taskBarMEMsamples, Gtk::PACK_SHRINK);
    memSamplesFrame->add(*memSamplesBox);
    statusBox->pack_start(*memSamplesFrame, Gtk::PACK_SHRINK);

    // Show Net Status
    taskBarShowNetStatus = new Gtk::CheckButton("Show Net Status");
    taskBarShowNetStatus->show();
    statusBox->pack_start(*taskBarShowNetStatus, Gtk::PACK_SHRINK);

    // Net Delay
    Gtk::Frame* netDelayFrame = Gtk::manage(new Gtk::Frame("Net Delay (ms):"));
    Gtk::Box* netDelayBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    taskBarNetDelay = Gtk::manage(new Gtk::SpinButton());
    taskBarNetDelay->set_range(0, 10000);
    taskBarNetDelay->set_increments(100, 500);
    netDelayBox->pack_start(*taskBarNetDelay, Gtk::PACK_SHRINK);
    netDelayFrame->add(*netDelayBox);
    taskBarNetDelay->set_range(10, 3600000);
    netDelayBox->pack_start(*taskBarNetDelay, Gtk::PACK_SHRINK);
    statusBox->pack_start(*netDelayBox, Gtk::PACK_SHRINK);

    // Net Samples
    Gtk::Frame* netSamplesFrame = Gtk::manage(new Gtk::Frame("Net Samples:"));
    Gtk::Box* netSamplesBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    taskBarNetSamples = Gtk::manage(new Gtk::SpinButton());
    taskBarNetSamples->set_range(0, 1000);
    taskBarNetSamples->set_increments(10, 100);
    netSamplesBox->pack_start(*taskBarNetSamples, Gtk::PACK_SHRINK);
    netSamplesFrame->add(*netSamplesBox);
    taskBarNetSamples->set_range(2, 1000);
    netSamplesBox->pack_start(*taskBarNetSamples, Gtk::PACK_SHRINK);
    statusBox->pack_start(*netSamplesBox, Gtk::PACK_SHRINK);

    // Show APM Auto
    taskBarShowAPMTime = new Gtk::CheckButton("Show APM Auto");
    taskBarShowAPMTime->show();
    statusBox->pack_start(*taskBarShowAPMTime, Gtk::PACK_SHRINK);

    // Show APM Graph
    taskBarShowAPMGraph = new Gtk::CheckButton("Show APM Graph");
    taskBarShowAPMGraph->show();
    statusBox->pack_start(*taskBarShowAPMGraph, Gtk::PACK_SHRINK);

    // Show APM Status
    taskBarShowAPMStatus = new Gtk::CheckButton("Show APM Status");
    taskBarShowAPMStatus->show();
    statusBox->pack_start(*taskBarShowAPMStatus, Gtk::PACK_SHRINK);

    // Show APM Time
    taskBarShowAPMTime = new Gtk::CheckButton("Show APM Time");
    taskBarShowAPMTime->show();
    statusBox->pack_start(*taskBarShowAPMTime, Gtk::PACK_SHRINK);

    // APM Graph Width
    Gtk::Frame* apmWidthFrame = Gtk::manage(new Gtk::Frame("APM Graph Width:"));
    Gtk::Box* apmWidthBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    taskBarApmGraphWidth = Gtk::manage(new Gtk::SpinButton());
    taskBarApmGraphWidth->set_range(0, 1000);
    taskBarApmGraphWidth->set_increments(10, 100);
    apmWidthBox->pack_start(*taskBarApmGraphWidth, Gtk::PACK_SHRINK);
    apmWidthFrame->add(*apmWidthBox);
    taskBarApmGraphWidth->set_range(1, 1000);
    apmWidthBox->pack_start(*taskBarApmGraphWidth, Gtk::PACK_SHRINK);
    statusBox->pack_start(*apmWidthBox, Gtk::PACK_SHRINK);

    // === Mail Status ===
    Gtk::Frame* mailFrame = Gtk::manage(new Gtk::Frame("Mail Status"));
    Gtk::Box* mailBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    mailBox->set_halign(Gtk::ALIGN_START);
    mailFrame->add(*mailBox);
    content->pack_start(*mailFrame, Gtk::PACK_SHRINK);

    // Show Mailbox Status
    taskBarShowMailboxStatus = new Gtk::CheckButton("Show Mailbox Status");
    taskBarShowMailboxStatus->show();
    mailBox->pack_start(*taskBarShowMailboxStatus, Gtk::PACK_SHRINK);

    // Beep on New Mail
    taskBarMailboxStatusBeepOnNewMail = new Gtk::CheckButton("Beep on New Mail");
    taskBarMailboxStatusBeepOnNewMail->show();
    mailBox->pack_start(*taskBarMailboxStatusBeepOnNewMail, Gtk::PACK_SHRINK);

    // Count Messages
    taskBarMailboxStatusCountMessages = new Gtk::CheckButton("Count Messages");
    taskBarMailboxStatusCountMessages->show();
    mailBox->pack_start(*taskBarMailboxStatusCountMessages, Gtk::PACK_SHRINK);

    // Mail Check Delay
    Gtk::Frame* mailDelayFrame = Gtk::manage(new Gtk::Frame("Mail Check Delay (s):"));
    Gtk::Box* mailDelayBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    mailCheckDelay = Gtk::manage(new Gtk::SpinButton());
    mailCheckDelay->set_range(0, 3600);
    mailCheckDelay->set_increments(10, 60);
    mailDelayBox->pack_start(*mailCheckDelay, Gtk::PACK_SHRINK);
    mailDelayFrame->add(*mailDelayBox);
    mailCheckDelay->set_range(0, 86400);
    mailDelayBox->pack_start(*mailCheckDelay, Gtk::PACK_SHRINK);
    mailBox->pack_start(*mailDelayBox, Gtk::PACK_SHRINK);

    // Mailbox Path
    Gtk::Frame* mailPathFrame = Gtk::manage(new Gtk::Frame("Mailbox Path:"));
    Gtk::Box* mailPathBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    mailBoxPath = Gtk::manage(new Gtk::Entry());
    mailBoxPath->set_max_width_chars(30);
    mailPathBox->pack_start(*mailBoxPath, Gtk::PACK_SHRINK);
    mailPathFrame->add(*mailPathBox);
    mailPathBox->pack_start(*mailPathBox, Gtk::PACK_SHRINK);
    mailBox->pack_start(*mailPathBox, Gtk::PACK_SHRINK);

    // === Network Status ===
    Gtk::Frame* networkFrame = Gtk::manage(new Gtk::Frame("Network Status"));
    Gtk::Box* networkBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    networkBox->set_halign(Gtk::ALIGN_START);
    networkFrame->add(*networkBox);
    content->pack_start(*networkFrame, Gtk::PACK_SHRINK);

    // Network Device
    Gtk::Frame* netDeviceFrame = Gtk::manage(new Gtk::Frame("Network Device:"));
    Gtk::Box* netDeviceBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    networkStatusDevice = Gtk::manage(new Gtk::Entry());
    networkStatusDevice->set_max_width_chars(20);
    netDeviceBox->pack_start(*networkStatusDevice, Gtk::PACK_SHRINK);
    netDeviceFrame->add(*netDeviceBox);
    netDeviceBox->pack_start(*networkStatusDevice, Gtk::PACK_SHRINK);
    networkBox->pack_start(*netDeviceBox, Gtk::PACK_SHRINK);

    // Show Only Running
    netStatusShowOnlyRunning = new Gtk::CheckButton("Show Only Running");
    netStatusShowOnlyRunning->show();
    networkBox->pack_start(*netStatusShowOnlyRunning, Gtk::PACK_SHRINK);

    // === CPU Status Advanced ===
    Gtk::Frame* cpuAdvFrame = Gtk::manage(new Gtk::Frame("CPU Status Advanced"));
    Gtk::Box* cpuAdvBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    cpuAdvBox->set_halign(Gtk::ALIGN_START);
    cpuAdvFrame->add(*cpuAdvBox);
    content->pack_start(*cpuAdvFrame, Gtk::PACK_SHRINK);

    // Show ACPI Temp
    cpuStatusShowAcpiTemp = new Gtk::CheckButton("Show ACPI Temp");
    cpuStatusShowAcpiTemp->show();
    cpuAdvBox->pack_start(*cpuStatusShowAcpiTemp, Gtk::PACK_SHRINK);

    // Show ACPI Temp in Graph
    cpuStatusShowAcpiTempInGraph = new Gtk::CheckButton("Show ACPI Temp in Graph");
    cpuStatusShowAcpiTempInGraph->show();
    cpuAdvBox->pack_start(*cpuStatusShowAcpiTempInGraph, Gtk::PACK_SHRINK);

    // Show CPU Freq
    cpuStatusShowCpuFreq = new Gtk::CheckButton("Show CPU Freq");
    cpuStatusShowCpuFreq->show();
    cpuAdvBox->pack_start(*cpuStatusShowCpuFreq, Gtk::PACK_SHRINK);

    // Show RAM Usage
    cpuStatusShowRamUsage = new Gtk::CheckButton("Show RAM Usage");
    cpuStatusShowRamUsage->show();
    cpuAdvBox->pack_start(*cpuStatusShowRamUsage, Gtk::PACK_SHRINK);

    // Show Swap Usage
    cpuStatusShowSwapUsage = new Gtk::CheckButton("Show Swap Usage");
    cpuStatusShowSwapUsage->show();
    cpuAdvBox->pack_start(*cpuStatusShowSwapUsage, Gtk::PACK_SHRINK);

    // CPU Class Hint
    Gtk::Frame* cpuClassFrame = Gtk::manage(new Gtk::Frame("CPU Class Hint:"));
    Gtk::Box* cpuClassBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    cpuStatusClassHint = Gtk::manage(new Gtk::Entry());
    cpuStatusClassHint->set_max_width_chars(30);
    cpuClassBox->pack_start(*cpuStatusClassHint, Gtk::PACK_SHRINK);
    cpuClassFrame->add(*cpuClassBox);
    cpuAdvBox->pack_start(*cpuClassFrame, Gtk::PACK_SHRINK);

    // CPU Command
    Gtk::Frame* cpuCommandFrame = Gtk::manage(new Gtk::Frame("CPU Command:"));
    Gtk::Box* cpuCommandBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    cpuStatusCommand = Gtk::manage(new Gtk::Entry());
    cpuStatusCommand->set_max_width_chars(30);
    cpuCommandBox->pack_start(*cpuStatusCommand, Gtk::PACK_SHRINK);
    cpuCommandFrame->add(*cpuCommandBox);
    cpuAdvBox->pack_start(*cpuCommandFrame, Gtk::PACK_SHRINK);

    // Combine CPU Status
    cpuStatusCombine = new Gtk::CheckButton("Combine CPU Status");
    cpuStatusCombine->show();
    cpuAdvBox->pack_start(*cpuStatusCombine, Gtk::PACK_SHRINK);

    // === Graph Appearance ===
    Gtk::Frame* graphFrame = Gtk::manage(new Gtk::Frame("Graph Appearance"));
    Gtk::Box* graphBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    graphBox->set_halign(Gtk::ALIGN_START);
    graphFrame->add(*graphBox);
    content->pack_start(*graphFrame, Gtk::PACK_SHRINK);

    // Graph Height
    Gtk::Frame* graphHeightFrame = Gtk::manage(new Gtk::Frame("Graph Height:"));
    Gtk::Box* graphHeightBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_HORIZONTAL, 5));
    taskBarGraphHeight = Gtk::manage(new Gtk::SpinButton());
    taskBarGraphHeight->set_range(16, 1000);
    taskBarGraphHeight->set_increments(1, 10);
    graphHeightBox->pack_start(*taskBarGraphHeight, Gtk::PACK_SHRINK);
    graphHeightFrame->add(*graphHeightBox);
    graphBox->pack_start(*graphHeightFrame, Gtk::PACK_SHRINK);

    // === TaskBar Justification ===
    Gtk::Frame* justifyFrame = Gtk::manage(new Gtk::Frame("TaskBar Justification"));
    Gtk::Box* justifyBox = Gtk::manage(new Gtk::Box(Gtk::ORIENTATION_VERTICAL, 5));
    justifyBox->set_halign(Gtk::ALIGN_START);
    justifyFrame->add(*justifyBox);
    content->pack_start(*justifyFrame, Gtk::PACK_SHRINK);

    // Justification Choice
    taskBarJustify = new Gtk::ComboBoxText();
    taskBarJustify->append("left");
    taskBarJustify->append("center");
    taskBarJustify->append("right");
    taskBarJustify->set_active(0);
    justifyBox->pack_start(*taskBarJustify, Gtk::PACK_SHRINK);

    // Add scroll to main container
    add(*scroll);
    scroll->show();
    content->show();
    show_all_children();
}

void PrefTaskBarTab::loadPreferences(const std::map<std::string, std::string>& prefs) {
    auto loadBool = [&](Gtk::CheckButton* btn, const std::string& key, bool defaultValue = false) {
        auto it = prefs.find(key);
        if (it != prefs.end()) {
            btn->set_active(it->second == "1");
        } else {
            btn->set_active(defaultValue);
        }
    };

    auto loadString = [&](Gtk::Entry* entry, const std::string& key, const char* defaultValue = "") {
        auto it = prefs.find(key);
        if (it != prefs.end()) {
            entry->set_text(it->second);
        } else {
            entry->set_text(defaultValue);
        }
    };

    auto loadInt = [&](Gtk::SpinButton* spin, const std::string& key, int defaultValue = 0) {
        auto it = prefs.find(key);
        if (it != prefs.end()) {
            try {
                spin->set_value(std::stoi(it->second));
            } catch (const std::invalid_argument&) {
                spin->set_value(0);
            }
        } else {
            spin->set_value(defaultValue);
        }
    };

    auto loadChoice = [&](Gtk::ComboBoxText* combo, const std::string& key, const char* defaultValue = "left") {
        auto it = prefs.find(key);
        if (it != prefs.end()) {
            // Try to set active text directly
            combo->set_active_text(it->second);
        } else {
            combo->set_active_text(defaultValue);
        }
    };

    // Load all preferences
    loadBool(showTaskBar, "ShowTaskBar", true);
    loadBool(taskBarAtTop, "TaskBarAtTop");
    loadBool(taskBarAutoHide, "TaskBarAutoHide");
    loadBool(taskBarDoubleHeight, "TaskBarDoubleHeight");
    loadBool(taskBarKeepBelow, "TaskBarKeepBelow");
    loadInt(taskBarWidthPercentage, "TaskBarWidthPercentage", 100);
    loadBool(taskBarWorkspacesLeft, "TaskBarWorkspacesLeft", true);
    loadBool(taskBarWorkspacesTop, "TaskBarWorkspacesTop");
    loadString(taskBarWorkspacesLimit, "TaskBarWorkspacesLimit");
    loadInt(taskbarButtonWidthDivisor, "TaskbarButtonWidthDivisor", 3);
    loadInt(taskbuttonIconOffset, "TaskbuttonIconOffset");

    loadBool(taskBarFullscreenAutoShow, "TaskBarFullscreenAutoShow", true);
    loadBool(taskBarShowAllWindows, "TaskBarShowAllWindows");
    loadBool(taskBarShowWindowIcons, "TaskBarShowWindowIcons", true);
    loadBool(taskBarShowWindowTitles, "TaskBarShowWindowTitles", true);
    loadBool(taskBarShowTransientWindows, "TaskBarShowTransientWindows", true);
    loadBool(taskBarShowClock, "TaskBarShowClock", true);
    loadBool(taskBarClockLeds, "TaskBarClockLeds");
    loadBool(taskBarShowShowDesktopButton, "TaskBarShowShowDesktopButton", true);
    loadBool(taskBarShowStartMenu, "TaskBarShowStartMenu", true);
    loadBool(taskBarShowWindowListMenu, "TaskBarShowWindowListMenu", true);
    loadBool(taskBarShowCollapseButton, "TaskBarShowCollapseButton");
    loadBool(taskBarShowWorkspaces, "TaskBarShowWorkspaces", true);
    loadBool(taskBarShowPager, "TaskBarShowPager", true);
    loadBool(taskBarShowTray, "TaskBarShowTray", true);
    loadBool(taskBarEnableSystemTray, "TaskBarEnableSystemTray", true);

    loadBool(taskBarLaunchOnSingleClick, "TaskBarLaunchOnSingleClick", true);
    loadBool(taskBarUseMouseWheel, "TaskBarUseMouseWheel", true);
    loadInt(taskBarTaskGrouping, "TaskBarTaskGrouping");

    loadBool(taskBarShowCPUStatus, "TaskBarShowCPUStatus", true);
    loadInt(taskBarCPUdelay, "TaskBarCPUDelay", 500);
    loadInt(taskBarCPUsamples, "TaskBarCPUSamples", 20);
    loadBool(taskBarShowMEMStatus, "TaskBarShowMEMStatus", true);
    loadInt(taskBarMEMDelay, "TaskBarMEMDelay", 500);
    loadInt(taskBarMEMsamples, "TaskBarMEMSamples", 20);
    loadBool(taskBarShowNetStatus, "TaskBarShowNetStatus", true);
    loadInt(taskBarNetDelay, "TaskBarNetDelay", 500);
    loadInt(taskBarNetSamples, "TaskBarNetSamples", 20);
    loadBool(taskBarShowAPMTime, "TaskBarShowAPMAuto", true);
    loadBool(taskBarShowAPMGraph, "TaskBarShowAPMGraph", true);
    loadBool(taskBarShowAPMStatus, "TaskBarShowAPMStatus");
    loadBool(taskBarShowAPMTime, "TaskBarShowAPMTime", true);
    loadInt(taskBarApmGraphWidth, "TaskBarApmGraphWidth", 10);

    loadBool(taskBarShowMailboxStatus, "TaskBarShowMailboxStatus", true);
    loadBool(taskBarMailboxStatusBeepOnNewMail, "TaskBarMailboxStatusBeepOnNewMail");
    loadBool(taskBarMailboxStatusCountMessages, "TaskBarMailboxStatusCountMessages");
    loadInt(mailCheckDelay, "MailCheckDelay", 30);
    loadString(mailBoxPath, "MailBoxPath");

    loadString(networkStatusDevice, "NetworkStatusDevice", "[ew]*");
    loadBool(netStatusShowOnlyRunning, "NetStatusShowOnlyRunning");

    loadBool(cpuStatusShowAcpiTemp, "CPUStatusShowAcpiTemp", true);
    loadBool(cpuStatusShowAcpiTempInGraph, "CPUStatusShowAcpiTempInGraph");
    loadBool(cpuStatusShowCpuFreq, "CPUStatusShowCpuFreq", true);
    loadBool(cpuStatusShowRamUsage, "CPUStatusShowRamUsage", true);
    loadBool(cpuStatusShowSwapUsage, "CPUStatusShowSwapUsage", true);
    loadString(cpuStatusClassHint, "CPUStatusClassHint", "top.XTerm");
    loadString(cpuStatusCommand, "CPUStatusCommand", "x-terminal-emulator -T 'Process Status' -e top");
    loadBool(cpuStatusCombine, "CPUStatusCombine", true);

    loadInt(taskBarGraphHeight, "TaskBarGraphHeight", 20);
    loadChoice(taskBarJustify, "TaskBarJustify", "left");
}

void PrefTaskBarTab::savePreferences(std::map<std::string, std::string>& prefs) {
    auto saveBool = [&](Gtk::CheckButton* btn, const std::string& key) {
        if (btn) {
            prefs[key] = btn->get_active() ? "1" : "0";
        }
    };

    auto saveString = [&](Gtk::Entry* entry, const std::string& key) {
        if (entry && entry->get_text_length() > 0) {
            prefs[key] = entry->get_text();
        }
    };

    auto saveInt = [&](Gtk::SpinButton* spin, const std::string& key) {
        if (spin) {
            prefs[key] = std::to_string((int)spin->get_value());
        }
    };

    auto saveChoice = [&](Gtk::ComboBoxText* combo, const std::string& key) {
        if (combo) {
            Glib::ustring text = combo->get_active_text();
            if (!text.empty()) {
                prefs[key] = text;
            }
        }
    };

    // Save all preferences
    saveBool(showTaskBar, "ShowTaskBar");
    saveBool(taskBarAtTop, "TaskBarAtTop");
    saveBool(taskBarAutoHide, "TaskBarAutoHide");
    saveBool(taskBarDoubleHeight, "TaskBarDoubleHeight");
    saveBool(taskBarKeepBelow, "TaskBarKeepBelow");
    saveInt(taskBarWidthPercentage, "TaskBarWidthPercentage");
    saveBool(taskBarWorkspacesLeft, "TaskBarWorkspacesLeft");
    saveBool(taskBarWorkspacesTop, "TaskBarWorkspacesTop");
    saveString(taskBarWorkspacesLimit, "TaskBarWorkspacesLimit");
    saveInt(taskbarButtonWidthDivisor, "TaskbarButtonWidthDivisor");
    saveInt(taskbuttonIconOffset, "TaskbuttonIconOffset");

    saveBool(taskBarFullscreenAutoShow, "TaskBarFullscreenAutoShow");
    saveBool(taskBarShowAllWindows, "TaskBarShowAllWindows");
    saveBool(taskBarShowWindowIcons, "TaskBarShowWindowIcons");
    saveBool(taskBarShowWindowTitles, "TaskBarShowWindowTitles");
    saveBool(taskBarShowTransientWindows, "TaskBarShowTransientWindows");
    saveBool(taskBarShowClock, "TaskBarShowClock");
    saveBool(taskBarClockLeds, "TaskBarClockLeds");
    saveBool(taskBarShowShowDesktopButton, "TaskBarShowShowDesktopButton");
    saveBool(taskBarShowStartMenu, "TaskBarShowStartMenu");
    saveBool(taskBarShowWindowListMenu, "TaskBarShowWindowListMenu");
    saveBool(taskBarShowCollapseButton, "TaskBarShowCollapseButton");
    saveBool(taskBarShowWorkspaces, "TaskBarShowWorkspaces");
    saveBool(taskBarShowPager, "TaskBarShowPager");
    saveBool(taskBarShowTray, "TaskBarShowTray");
    saveBool(taskBarEnableSystemTray, "TaskBarEnableSystemTray");

    saveBool(taskBarLaunchOnSingleClick, "TaskBarLaunchOnSingleClick");
    saveBool(taskBarUseMouseWheel, "TaskBarUseMouseWheel");
    saveInt(taskBarTaskGrouping, "TaskBarTaskGrouping");

    saveBool(taskBarShowCPUStatus, "TaskBarShowCPUStatus");
    saveInt(taskBarCPUdelay, "TaskBarCPUDelay");
    saveInt(taskBarCPUsamples, "TaskBarCPUSamples");
    saveBool(taskBarShowMEMStatus, "TaskBarShowMEMStatus");
    saveInt(taskBarMEMDelay, "TaskBarMEMDelay");
    saveInt(taskBarMEMsamples, "TaskBarMEMSamples");
    saveBool(taskBarShowNetStatus, "TaskBarShowNetStatus");
    saveInt(taskBarNetDelay, "TaskBarNetDelay");
    saveInt(taskBarNetSamples, "TaskBarNetSamples");
    saveBool(taskBarShowAPMTime, "TaskBarShowAPMAuto");
    saveBool(taskBarShowAPMGraph, "TaskBarShowAPMGraph");
    saveBool(taskBarShowAPMStatus, "TaskBarShowAPMStatus");
    saveBool(taskBarShowAPMTime, "TaskBarShowAPMTime");
    saveInt(taskBarApmGraphWidth, "TaskBarApmGraphWidth");

    saveBool(taskBarShowMailboxStatus, "TaskBarShowMailboxStatus");
    saveBool(taskBarMailboxStatusBeepOnNewMail, "TaskBarMailboxStatusBeepOnNewMail");
    saveBool(taskBarMailboxStatusCountMessages, "TaskBarMailboxStatusCountMessages");
    saveInt(mailCheckDelay, "MailCheckDelay");
    saveString(mailBoxPath, "MailBoxPath");

    saveString(networkStatusDevice, "NetworkStatusDevice");
    saveBool(netStatusShowOnlyRunning, "NetStatusShowOnlyRunning");

    saveBool(cpuStatusShowAcpiTemp, "CPUStatusShowAcpiTemp");
    saveBool(cpuStatusShowAcpiTempInGraph, "CPUStatusShowAcpiTempInGraph");
    saveBool(cpuStatusShowCpuFreq, "CPUStatusShowCpuFreq");
    saveBool(cpuStatusShowRamUsage, "CPUStatusShowRamUsage");
    saveBool(cpuStatusShowSwapUsage, "CPUStatusShowSwapUsage");
    saveString(cpuStatusClassHint, "CPUStatusClassHint");
    saveString(cpuStatusCommand, "CPUStatusCommand");
    saveBool(cpuStatusCombine, "CPUStatusCombine");

    saveInt(taskBarGraphHeight, "TaskBarGraphHeight");
    saveChoice(taskBarJustify, "TaskBarJustify");
}

void PrefTaskBarTab::resetWidgets() {
    // Reset to defaults
    showTaskBar->set_active(true);
    taskBarAtTop->set_active(false);
    taskBarAutoHide->set_active(false);
    taskBarDoubleHeight->set_active(false);
    taskBarKeepBelow->set_active(false);
    taskBarWidthPercentage->set_value(100);
    taskBarWorkspacesLeft->set_active(true);
    taskBarWorkspacesTop->set_active(false);
    taskBarWorkspacesLimit->set_text("");
    taskbarButtonWidthDivisor->set_value(3);
    taskbuttonIconOffset->set_value(0);

    taskBarFullscreenAutoShow->set_active(true);
    taskBarShowAllWindows->set_active(false);
    taskBarShowWindowIcons->set_active(true);
    taskBarShowWindowTitles->set_active(true);
    taskBarShowTransientWindows->set_active(true);
    taskBarShowClock->set_active(true);
    taskBarClockLeds->set_active(false);
    taskBarShowShowDesktopButton->set_active(true);
    taskBarShowStartMenu->set_active(true);
    taskBarShowWindowListMenu->set_active(true);
    taskBarShowCollapseButton->set_active(false);
    taskBarShowWorkspaces->set_active(true);
    taskBarShowPager->set_active(true);
    taskBarShowTray->set_active(true);
    taskBarEnableSystemTray->set_active(true);

    taskBarLaunchOnSingleClick->set_active(true);
    taskBarUseMouseWheel->set_active(true);
    taskBarTaskGrouping->set_value(0);

    taskBarShowCPUStatus->set_active(true);
    taskBarCPUdelay->set_value(500);
    taskBarCPUsamples->set_value(20);
    taskBarShowMEMStatus->set_active(true);
    taskBarMEMDelay->set_value(500);
    taskBarMEMsamples->set_value(20);
    taskBarShowNetStatus->set_active(true);
    taskBarNetDelay->set_value(500);
    taskBarNetSamples->set_value(20);
    taskBarShowAPMTime->set_active(true);
    taskBarShowAPMGraph->set_active(true);
    taskBarShowAPMStatus->set_active(false);
    taskBarShowAPMTime->set_active(true);
    taskBarApmGraphWidth->set_value(10);

    taskBarShowMailboxStatus->set_active(true);
    taskBarMailboxStatusBeepOnNewMail->set_active(false);
    taskBarMailboxStatusCountMessages->set_active(false);
    mailCheckDelay->set_value(30);
    mailBoxPath->set_text("");

    networkStatusDevice->set_text("[ew]*");
    netStatusShowOnlyRunning->set_active(false);

    cpuStatusShowAcpiTemp->set_active(true);
    cpuStatusShowAcpiTempInGraph->set_active(false);
    cpuStatusShowCpuFreq->set_active(true);
    cpuStatusShowRamUsage->set_active(true);
    cpuStatusShowSwapUsage->set_active(true);
    cpuStatusClassHint->set_text("top.XTerm");
    cpuStatusCommand->set_text("x-terminal-emulator -T 'Process Status' -e top");
    cpuStatusCombine->set_active(true);

    taskBarGraphHeight->set_value(20);
    taskBarJustify->set_active(0);
}

void PrefTaskBarTab::checkbox_cb(Gtk::Widget* w, void* v) {
    // Checkbox changes are handled when saving
}

void PrefTaskBarTab::input_cb(Gtk::Widget* w, void* v) {
    // Input changes are handled when saving
}

void PrefTaskBarTab::spinbutton_cb(Gtk::Widget* w, void* v) {
    // Spinbutton changes are handled when saving
}

void PrefTaskBarTab::combo_box_cb(Gtk::Widget* w, void* v) {
    // Combo box changes are handled when saving
}