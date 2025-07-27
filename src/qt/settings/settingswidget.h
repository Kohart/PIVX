// Copyright (c) 2019-2021 The PIVX Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PIVX_QT_SETTINGS_SETTINGSWIDGET_H
#define PIVX_QT_SETTINGS_SETTINGSWIDGET_H

#include <QWidget>

#include "pwidget.h"
#include "settings/backupwallet.h"
#include "settings/bittoolwidget.h"
#include "settings/consolewidget.h"
#include "settings/displayoptionswidget.h"
#include "settings/exportcsv.h"
#include "settings/informationwidget.h"
#include "settings/mainoptionswidget.h"
#include "settings/signmessagewidgets.h"
#include "settings/walletoptionswidget.h"
#include "settings/walletrepairwidget.h"

class PIVXGUI;

QT_BEGIN_NAMESPACE
class QDataWidgetMapper;
QT_END_NAMESPACE

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public PWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(PIVXGUI* parent);
    ~SettingsWidget();

    void loadClientModel() override;
    void loadWalletModel() override;
    void setMapper();
    void showDebugConsole();
    void showInformation();
    void openNetworkMonitor();

Q_SIGNALS:
    /** Get restart command-line parameters and handle restart */
    void handleRestart(QStringList args);

private Q_SLOTS:
    // File
    void onFileClicked();
    void onBackupWalletClicked();
    void onSignMessageClicked();

    // Wallet Configuration
    void onConfigurationClicked();
    void onBipToolClicked();
    void onExportCSVClicked();

    // Options
    void onOptionsClicked();
    void onMainOptionsClicked();
    void onWalletOptionsClicked();
    void onDisplayOptionsClicked();

    void onDiscardChanges();

    // Tools
    void onToolsClicked();
    void onInformationClicked();
    void onDebugConsoleClicked();
    void onWalletRepairClicked();

    // Help
    void onHelpClicked();
    void onAboutClicked();
    void onResetAction();
    void onSaveOptionsClicked();

private:
    Ui::SettingsWidget *ui{nullptr};
    int navAreaBaseHeight{0};

    SettingsBackupWallet *settingsBackupWallet{nullptr};
    SettingsExportCSV *settingsExportCsvWidget{nullptr};
    SettingsBitToolWidget *settingsBitToolWidget{nullptr};
    SettingsSignMessageWidgets *settingsSingMessageWidgets{nullptr};
    SettingsWalletRepairWidget *settingsWalletRepairWidget{nullptr};
    SettingsWalletOptionsWidget *settingsWalletOptionsWidget{nullptr};
    SettingsMainOptionsWidget *settingsMainOptionsWidget{nullptr};
    SettingsDisplayOptionsWidget *settingsDisplayOptionsWidget{nullptr};
    SettingsInformationWidget *settingsInformationWidget{nullptr};
    SettingsConsoleWidget *settingsConsoleWidget{nullptr};

    QDataWidgetMapper* mapper{nullptr};

    QList<QPushButton*> options;
    // Map of: menu button -> sub menu items
    QMap <QPushButton*, QWidget*> menus;

    void selectOption(QPushButton* option);
    bool openStandardDialog(const QString& title = "", const QString& body = "", const QString& okBtn = "OK", const QString& cancelBtn = "");
    void selectMenu(QPushButton* btn);
};

#endif // PIVX_QT_SETTINGS_SETTINGSWIDGET_H
