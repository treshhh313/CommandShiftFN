#include "keypresscatcher.h"

#include "constants.h"

#include <QActionGroup>
#include <QApplication>
#include <QDesktopServices>
#include <QMenu>
#include <QMessageBox>
#include <QSettings>
#include <QStandardPaths>
#include <QSystemTrayIcon>
#include <QUrl>
#include <QDir>

namespace
{
    constexpr static auto s_hide_tray_icon_setting_name = "tray_icon/hide";
    constexpr static auto s_change_language_on_release_setting_name = "language/trigger_on_key_release";
    constexpr static auto s_white_tray_icon_preference_setting_name = "tray_icon/white_tray_icon";
    constexpr static auto s_fn_screenshot_enabled_setting_name = "fn_screenshot/enabled";
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QMenu menu;

    auto homePath = QDir::homePath();
    // Using QDir to construct path compatibly across platforms/versions
    auto settingsPath = QDir(homePath).filePath(".config/commandShift.ini");
    auto settings = new QSettings(settingsPath, QSettings::Format::IniFormat, &a);

    auto prefer_white_tray_icon = settings->value(s_white_tray_icon_preference_setting_name, false).toBool();
    auto systemTrayIcon = new QSystemTrayIcon(prefer_white_tray_icon ? QIcon(":/icons/trayicon_white.png") : QIcon(":/icons/trayicon.png"), &menu);

    systemTrayIcon->setContextMenu(&menu);
    systemTrayIcon->setToolTip("CommandShift (1.0) - developed by Vasyl Baran");

    auto hide_tray_icon = settings->value(s_hide_tray_icon_setting_name, false).toBool();
    if (!hide_tray_icon)
    {
        systemTrayIcon->show();
    }

    auto showMessageCallback = [systemTrayIcon](const QString& title, const QString& message)
    {
        if (title.contains("Accessibility")) {
            QMessageBox::warning(nullptr, title, message);
        } else {
            systemTrayIcon->showMessage(title,
                                        message,
                                        QIcon(),
                                        30000);
        }
    };

    KeyPressCatcher catcher(showMessageCallback);
    auto authorAction = menu.addAction("Visit CommandShift page");
    QObject::connect(authorAction, &QAction::triggered, [] { QDesktopServices::openUrl(QUrl("https://github.com/VasylBaran/CommandShift")); });

    /* Group of shortcuts (mutually exclusive) that should be used to change language
       i.e. we allow user to chose between different shortcuts */
    auto secondShortcutKeyGroup = new QActionGroup(&menu);
    secondShortcutKeyGroup->setExclusive(true);

    // 'Shift + Control' action
    auto controlAction = new QAction("Shift + Control", secondShortcutKeyGroup);
    controlAction->setCheckable(true);
    // 'Shift + Option' action
    auto optionAction = new QAction("Shift + Option", secondShortcutKeyGroup);
    optionAction->setCheckable(true);
    // 'Shift + Command' action
    auto commandAction = new QAction("Shift + Command", secondShortcutKeyGroup);
    commandAction->setCheckable(true);
    // 'Shift' action
    auto shiftAction = new QAction("Shift", secondShortcutKeyGroup);
    shiftAction->setCheckable(true);

    auto secondShortcutKey = catcher.getSecondShortcutKey();
    // Toggling currently selected shortcut
    if (secondShortcutKey == CS::SecondShortcutKeyEnum::Control)
        controlAction->toggle();
    else if (secondShortcutKey == CS::SecondShortcutKeyEnum::Option)
        optionAction->toggle();
    else if (secondShortcutKey == CS::SecondShortcutKeyEnum::Command)
        commandAction->toggle();
    else if (secondShortcutKey == CS::SecondShortcutKeyEnum::Nothing)
        shiftAction->toggle();

    // Connections
    QObject::connect(controlAction, &QAction::triggered, [&catcher] (bool checked) { if (checked) { catcher.setSecondShortcutKey(CS::Control); } });
    QObject::connect(optionAction, &QAction::triggered, [&catcher] (bool checked) { if (checked) { catcher.setSecondShortcutKey(CS::Option); } });
    QObject::connect(commandAction, &QAction::triggered, [&catcher] (bool checked) { if (checked) {  catcher.setSecondShortcutKey(CS::Command); } });
    QObject::connect(shiftAction, &QAction::triggered, [&catcher] (bool checked) { if (checked) {  catcher.setSecondShortcutKey(CS::Nothing); } });

    // Adding actions to the group to make them mutually exclusive (group already owns them)
    secondShortcutKeyGroup->addAction(controlAction);
    secondShortcutKeyGroup->addAction(optionAction);
    secondShortcutKeyGroup->addAction(commandAction);
    secondShortcutKeyGroup->addAction(shiftAction);

    // Adding actions to drop-down menu
    auto secondShortcutKeyDropDownActionMenu = menu.addMenu("Change language with...");
    secondShortcutKeyDropDownActionMenu->addAction(controlAction);
    secondShortcutKeyDropDownActionMenu->addAction(optionAction);
    secondShortcutKeyDropDownActionMenu->addAction(commandAction);
    secondShortcutKeyDropDownActionMenu->addAction(shiftAction);

    auto change_language_on_release = settings->value(s_change_language_on_release_setting_name, false).toBool();
    catcher.setChangeLanguageOnRelease(change_language_on_release);

    auto changeLanguageOnKeyReleasedAction = menu.addAction("Change language after Shift release");
    changeLanguageOnKeyReleasedAction->setCheckable(true);
    changeLanguageOnKeyReleasedAction->setChecked(change_language_on_release);
    QObject::connect(changeLanguageOnKeyReleasedAction, &QAction::triggered, changeLanguageOnKeyReleasedAction, [&catcher, settings] { catcher.setChangeLanguageOnRelease(!catcher.changeLanguageOnRelease()); settings->setValue(s_change_language_on_release_setting_name, catcher.changeLanguageOnRelease()); });

    // Fn screenshot shortcuts feature toggle
    auto fn_screenshot_enabled = settings->value(s_fn_screenshot_enabled_setting_name, true).toBool();
    catcher.setFnScreenshotEnabled(fn_screenshot_enabled);

    auto fnScreenshotAction = menu.addAction("Enable Fn screenshot shortcuts");
    fnScreenshotAction->setCheckable(true);
    fnScreenshotAction->setChecked(fn_screenshot_enabled);
    QObject::connect(fnScreenshotAction, &QAction::triggered, fnScreenshotAction, [&catcher, settings] { catcher.setFnScreenshotEnabled(!catcher.fnScreenshotEnabled()); settings->setValue(s_fn_screenshot_enabled_setting_name, catcher.fnScreenshotEnabled()); });

    auto trayIconGroup = new QActionGroup(&menu);
    trayIconGroup->setExclusive(false);

    auto hideTrayIconActionPermanently = new QAction("Hide icon permanently", trayIconGroup);
    hideTrayIconActionPermanently->setCheckable(true);
    auto hideTrayIconActionUtilRestart = new QAction("Hide icon until restart", trayIconGroup);
    hideTrayIconActionUtilRestart->setCheckable(true);
    auto changeIconsColor = new QAction("Make it white", trayIconGroup);
    changeIconsColor->setCheckable(true);
    changeIconsColor->setChecked(prefer_white_tray_icon);

    // Adding actions to (hide tray icon) drop-down menu
    auto trayMenuIconDropDownActionMenu = menu.addMenu("Tray menu icon...");
    trayMenuIconDropDownActionMenu->addAction(hideTrayIconActionPermanently);
    trayMenuIconDropDownActionMenu->addAction(hideTrayIconActionUtilRestart);
    trayMenuIconDropDownActionMenu->addAction(changeIconsColor);

    QObject::connect(hideTrayIconActionPermanently, &QAction::triggered, systemTrayIcon, [systemTrayIcon, settings] { systemTrayIcon->hide(); settings->setValue(s_hide_tray_icon_setting_name, true); });
    QObject::connect(hideTrayIconActionUtilRestart, &QAction::triggered, systemTrayIcon, [systemTrayIcon] { systemTrayIcon->hide(); });
    QObject::connect(changeIconsColor, &QAction::triggered, systemTrayIcon, [systemTrayIcon, settings] (bool checked) { systemTrayIcon->setIcon(checked ? QIcon(":/icons/trayicon_white.png") : QIcon(":/icons/trayicon.png")); settings->setValue(s_white_tray_icon_preference_setting_name, checked); });

    auto quitAction = menu.addAction("Quit");
    QObject::connect(quitAction, &QAction::triggered, &a, [&a] { a.quit(); });

    return a.exec();
}
