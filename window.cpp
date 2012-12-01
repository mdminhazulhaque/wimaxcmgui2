#include "window.hpp"
#include "ui_window.h"

Window::Window(QWidget *parent) : QMainWindow(parent), ui(new Ui::Window)
{
    // Thanks to Ujjal Vai for this great support!
    WCM_Waiting = WCM_Connected = WCM_Nodevice = false;

    // Build GUI
    ui->setupUi(this);
    //wcmSettings = new QSettings(QDir::home().absoluteFilePath(".wimaxcmgui2.conf"),QSettings::IniFormat);

    //  Icons
    bConnect = QIcon(QPixmap(":/buttons/connect"));
    bDisconnect = QIcon(QPixmap(":/buttons/disconnect"));
    aConnect = QIcon(QPixmap(":/actions/connect"));
    aDisconnect = QIcon(QPixmap(":/actions/disconnect"));

    // Forms
    aboutdialog = new AboutDialog(this);
    accountdialog = new AccountsDialog(this);
    keyboarddialog = new KeyboardDialog(this);
    scheduledialog = new ScheduleDialog(this);
    settingsdialog = new SettingsDialog(this);

    // Timers
    timerProcess = new WCMTimer(this);
    timerUptime = new WCMTimer(this);

    // Tray
    trayIcon = new QSystemTrayIcon;
    trayDisconnected = QIcon(QPixmap(":/systray/disconnected"));
    trayAnalyzing = QIcon(QPixmap(":/systray/analyzing"));
    trayNoDevice = QIcon(QPixmap(":/systray/nodevice"));
    trayHide = QIcon(QPixmap(":/systray/hide"));
    trayRestore = QIcon(QPixmap(":/systray/restore"));
    tray00 = QIcon(QPixmap(":/systray/00"));
    tray25 = QIcon(QPixmap(":/systray/25"));
    tray50 = QIcon(QPixmap(":/systray/50"));
    tray75 = QIcon(QPixmap(":/systray/75"));
    tray100 = QIcon(QPixmap(":/systray/100"));
    trayIcon->setIcon(trayAnalyzing);

    // Tray Actions
    systrayMenu = new QMenu(this);
    systrayMenu->addAction(ui->actionConnect);
    systrayMenu->addAction(ui->actionReconnect);
    systrayMenu->addSeparator();
    systrayMenu->addAction(ui->actionEditDetails);
    systrayMenu->addAction(ui->actionSchedule);
    systrayMenu->addAction(ui->actionConsole);
    systrayMenu->addAction(ui->actionSettings);
    systrayMenu->addSeparator();
    systrayMenu->addAction(ui->actionShowHide);
    systrayMenu->addAction(ui->actionQuit);
    trayIcon->setContextMenu(systrayMenu);

    // Connecting systray click
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)),
            this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    // Timer and Monitor Process
    connect(timerProcess, SIGNAL(timeout()), this, SLOT(monitorWCMProcess()));
    connect(timerUptime, SIGNAL(timeout()), this, SLOT(updateUptime()));
    connect(this, SIGNAL(connectionStatus(bool)), this, SLOT(setConnectionStatus(bool)));
    connect(this, SIGNAL(deviceStatus(bool)), this, SLOT(setDeviceStatus(bool)));

    // Connecting qaction triggers...
    connect(ui->actionAbout, SIGNAL(triggered()), aboutdialog, SLOT(show()));
    connect(ui->actionClear, SIGNAL(triggered()), this, SLOT(DoClearUserData()));
    connect(ui->actionConnect, SIGNAL(triggered()), this, SLOT(InitConnection()));
    connect(ui->actionConnect_to, SIGNAL(triggered()), this, SLOT(InitConnectionManual()));
    connect(ui->actionConsole, SIGNAL(triggered()), this, SLOT(openConsole()));
    connect(ui->actionDevice, SIGNAL(triggered()), this, SLOT(ShowDeviceInfo()));
    connect(ui->actionDocumentation, SIGNAL(triggered()),this , SLOT(ShowDocumentation()));
    connect(ui->actionEditDetails, SIGNAL(triggered()), accountdialog, SLOT(Show()));
    connect(ui->actionHomepage, SIGNAL(triggered()), this, SLOT(OpenHomepage()));
    connect(ui->actionKeyboard, SIGNAL(triggered()), keyboarddialog, SLOT(show()));
    connect(ui->actionReconnect, SIGNAL(triggered()), this, SLOT(InitReconnection()));
    connect(ui->actionSchedule, SIGNAL(triggered()), scheduledialog, SLOT(show()));
    connect(ui->actionSchedule, SIGNAL(triggered()), scheduledialog, SLOT(show()));
    connect(ui->actionSearch, SIGNAL(triggered()), this, SLOT(openSearchConsole()));
    connect(ui->actionSettings, SIGNAL(triggered()), settingsdialog, SLOT(show()));
    connect(ui->actionSettings, SIGNAL(triggered()), settingsdialog, SLOT(show()));
    connect(ui->actionSubmitIssue, SIGNAL(triggered()), this, SLOT(submitIssue()));
    connect(ui->actionShowHide, SIGNAL(triggered()), this, SLOT(toggleWindowVisibility()));
    connect(ui->actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

    // Connecting  qpushbutton signals...
    connect(ui->bConnect, SIGNAL(clicked()), this, SLOT(InitConnection()));
    connect(ui->bAccount, SIGNAL(clicked()), accountdialog, SLOT(Show()));
    connect(ui->bSettings, SIGNAL(clicked()), settingsdialog, SLOT(show()));
    connect(ui->bHide, SIGNAL(clicked()), this, SLOT(closeToTray()));

    // Connecting connection specific actions
    connect(this, SIGNAL(deviceStatus(bool)), ui->actionConnect ,SLOT(setEnabled(bool)));
    connect(this, SIGNAL(deviceStatus(bool)), ui->actionConnect_to ,SLOT(setEnabled(bool)));
    connect(this, SIGNAL(deviceStatus(bool)), ui->actionReconnect ,SLOT(setEnabled(bool)));
    connect(this, SIGNAL(deviceStatus(bool)), ui->actionEditDetails ,SLOT(setEnabled(bool)));
    connect(this, SIGNAL(deviceStatus(bool)), ui->actionSearch ,SLOT(setEnabled(bool)));
    connect(this, SIGNAL(deviceStatus(bool)), ui->actionDevice ,SLOT(setEnabled(bool)));
    connect(this, SIGNAL(deviceStatus(bool)), ui->bConnect, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(deviceStatus(bool)), ui->bAccount, SLOT(setEnabled(bool)));
    connect(this, SIGNAL(readySetIdentity()), accountdialog, SLOT(autoSetIdentity()));

    // There you go...
    trayIcon->show();
    timerProcess->Start(2000);
}

Window::~Window()
{
    delete ui;
    delete aboutdialog;
    delete accountdialog;
    delete keyboarddialog;
    delete scheduledialog;
    delete settingsdialog;
    delete trayIcon;
    delete systrayMenu;
    delete timerProcess;
    delete timerUptime;
    delete wcmSettings;

}

void Window::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch (reason)
    {
    case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        if(isActiveWindow())
        {
            close();
            ui->actionShowHide->setIcon(trayRestore);
            ui->actionShowHide->setText("Restore");
        }
        else
        {
            showNormal();
            ui->actionShowHide->setIcon(trayHide);
            ui->actionShowHide->setText("Hide");
        }
        break;
    case QSystemTrayIcon::MiddleClick:
        accountdialog->show();
        break;
    default:
        ;
    }
}

void Window::toggleWindowVisibility()
{
    if(isHidden())
    {
        show();
        ui->actionShowHide->setText("Hide");
        ui->actionShowHide->setIcon(trayHide);
    }
    else
    {
        hide();
        ui->actionShowHide->setText("Restore");
        ui->actionShowHide->setIcon(trayRestore);
    }
}

void Window::monitorWCMProcess()
{
    scanResult = wcmRead(WCM_SCANALL);
    if(scanResult.contains("LINKUP")) // If Device Is Plugged And Connected
    {
        if(!WCM_Connected)
        {
            WCM_Waiting = false;
            WCM_Connected = true;
            WCM_Nodevice = false;
            //emit deviceStatus(true);
            emit connectionStatus(true);
        }

        cinr = wcmRead(WCM_CINR);
        ui->cinr->setText(cinr);
        ui->rssi->setText(wcmRead(WCM_RSSI));
        ui->upload->setText(wcmRead(WCM_UPLOAD));
        ui->download->setText(wcmRead(WCM_DOWNLOAD));

        if(cinr>"32")
            trayIcon->setIcon(tray100);
        else if(cinr>"24")
            trayIcon->setIcon(tray75);
        else if(cinr>"16")
            trayIcon->setIcon(tray50);
        else if(cinr>"8")
            trayIcon->setIcon(tray25);
        else
            trayIcon->setIcon(tray00);
    }

    else if(scanResult.contains("WAIT")) // If Device Is Plugged In But Not Connected
    {
        if(!WCM_Waiting)
        {
            WCM_Waiting = true;
            WCM_Connected = false;
            WCM_Nodevice = false;
            emit deviceStatus(true);
            emit connectionStatus(false);
        }
    }

    else if(scanResult.contains("NOT")) // If Device Is Unplugged
    {
        if(!WCM_Nodevice)
        {
            WCM_Waiting = false;
            WCM_Connected = false;
            WCM_Nodevice = true;
            emit connectionStatus(false);
            emit deviceStatus(false);
        }
    }
}

void Window::setConnectionStatus(bool isConnected)
{
    WCM_ActiveConnection = isConnected;
    ui->bConnect->setIcon(isConnected?bDisconnect:bConnect);
    ui->actionConnect->setText(isConnected?"Disconnect":"Connect");
    ui->actionConnect->setIcon(isConnected?aDisconnect:aConnect);

    if(isConnected) // Do some isConnected specific jobs
    {
        uptime = \
                QTime::fromString(wcmRead(WCM_UPTIME), "h:m:s");
        timerUptime->Start(1000);

        ui->bsid->setText(wcmRead(WCM_BSID));
        ui->status->setText("Connected ("+wcmRead(WCM_FREQ)+"KHz)");
        ui->ip->setText(wcmRead(WCM_GREPIFCONFIG+wcmRead(WCM_GREPETH+wcmRead(WCM_MAC).replace("-",".")+WCM_CUT)+WCM_GREPINET));
    }
    else
    {
        ui->status->setText("Disconnected");
        timerUptime->stop();
        ui->time->setText("--");
        ui->ip->setText("--");
        ui->bsid->setText("--");
        ui->rssi->setText("--");
        ui->cinr->setText("--");
        ui->upload->setText("--");
        ui->download->setText("--");
        trayIcon->setIcon(trayDisconnected);
    }
}

void Window::setDeviceStatus(bool isPlugged)
{
    if(isPlugged)
        emit readySetIdentity();
    else
    {
        trayIcon->setIcon(trayNoDevice);
        ui->status->setText("No Device");
    }
}

void Window::updateUptime()
{
    uptime = uptime.addSecs(1);
    ui->time->setText(uptime.toString("hh:mm:ss"));
}

void Window::openConsole()
{
    QProcess::startDetached("xterm -e wimaxc -i");
}

void Window::openSearchConsole()
{
    QProcess::startDetached("xterm -e wimaxc -i search");
}

void Window::submitIssue()
{
}

void Window::closeToTray()
{
    ui->actionShowHide->setText("Restore");
    ui->actionShowHide->setIcon(trayRestore);
    hide();
}

void Window::ShowDocumentation()
{
}

void Window::OpenHomepage()
{
}

void Window::ShowDeviceInfo()
{
    QMessageBox::information(this, "Device Info",
                             "MAC Address: <b>"+wcmRead(WCM_MAC)+"</b>",
                             QMessageBox::Ok);
}

void Window::DoClearUserData()
{
    QProcess::startDetached("wimaxc set UserIdentity \"anonymous\"");
    QProcess::startDetached("wimaxc set UserPassword \"anonymous\"");
    QProcess::startDetached("wimaxc set TTLSAnonymousIdentity \"anonymous\"");
    QProcess::startDetached("wimaxc options save");
}

void Window::InitConnection()
{
    if(WCM_ActiveConnection)
        QProcess::startDetached("wimaxc disconnect");
    else
        QProcess::startDetached("wimaxc connect 2600 10");
    return;
}

void Window::InitConnectionManual()
{
    bool ok = false;
    if(WCM_ActiveConnection)
        QProcess::startDetached("wimaxc disconnect");
    int freq = QInputDialog::getInt(this, "Manual Connect", "Enter frequency", PREF_FREQ, MIN_FREQ, MAX_FREQ, STEP_FREQ, &ok);
    if(ok)
    {
    }
    else
    {
    }
}

void Window::InitReconnection()
{
    QProcess::startDetached("wimaxc disconnect");
    QProcess::startDetached("wimaxcmguiautoconnect");
}
