#ifndef WINDOW_H
#define WINDOW_H

#include "defines.hpp"
#include "aboutdialog.hpp"
#include "accountsdialog.hpp"
#include "keyboarddialog.hpp"
#include "scheduledialog.hpp"
#include "settingsdialog.hpp"
#include "wcmtimer.hpp"

#include <QDebug>
#include <QInputDialog>
#include <QMainWindow>
#include <QMessageBox>
#include <QProcess>
#include <QTime>
#include <QSystemTrayIcon>
//#include <QDesktopServices>
//#include <QToolTip>

namespace Ui {
class Window;
}

class Window : public QMainWindow
{
    Q_OBJECT

public:
    explicit Window(QWidget *parent = 0);
    ~Window();

public slots:
    void DoClearUserData();
    void InitConnection();
    void InitConnectionManual();
    void InitReconnection();
    void OpenHomepage();
    void ShowDeviceInfo();
    void ShowDocumentation();

    void monitorWCMProcess();
    void updateUptime();
    void openConsole();
    void openSearchConsole();
    void submitIssue();
    void closeToTray();
    void iconActivated(QSystemTrayIcon::ActivationReason reason);
    void toggleWindowVisibility();
    void setConnectionStatus(bool isConnected);
    void setDeviceStatus(bool isPlugged);

signals:
    void connectionStatus(bool);
    void deviceStatus(bool);
    void readySetIdentity();

private:
    // Forms
    AboutDialog *aboutdialog;
    AccountsDialog *accountdialog;
    KeyboardDialog *keyboarddialog;
    ScheduleDialog *scheduledialog;
    SettingsDialog *settingsdialog;
    Ui::Window *ui;

    // Tray Icons
    QSystemTrayIcon *trayIcon;
    QIcon trayDisconnected;
    QIcon trayAnalyzing;
    QIcon trayNoDevice;
    QIcon trayHide;
    QIcon trayRestore;
    QIcon tray00;
    QIcon tray25;
    QIcon tray50;
    QIcon tray75;
    QIcon tray100;
    QMenu *systrayMenu;

    // Button Icons
    QIcon bConnect;
    QIcon bDisconnect;
    QIcon aConnect;
    QIcon aDisconnect;

    // Other items
    QTime uptime;
    WCMTimer *timerProcess;
    WCMTimer *timerUptime;
    bool WCM_Waiting;
    bool WCM_Connected;
    bool WCM_Nodevice;
    bool WCM_ActiveConnection;
    QString cinr;
    QString scanResult;

    // Settings
    QSettings *wcmSettings;
};

#endif // WINDOW_H
