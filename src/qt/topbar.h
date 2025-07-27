// Copyright (c) 2019-2021 The PIVX Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PIVX_QT_TOPBAR_H
#define PIVX_QT_TOPBAR_H

#include "amount.h"
#include "lockunlock.h"
#include "pwidget.h"
#include "qt/askpassphrasedialog.h"

#include <QProgressBar>
#include <QTimer>
#include <QWidget>

class BalanceBubble;
class PIVXGUI;
class WalletModel;
class ClientModel;

namespace Ui {
class TopBar;
}

class TopBar : public PWidget
{
    Q_OBJECT

public:
    explicit TopBar(PIVXGUI* _mainWindow, QWidget *parent = nullptr);
    ~TopBar();

    void showTop();
    void showBottom();

    void loadWalletModel() override;
    void loadClientModel() override;

    void openPassPhraseDialog(AskPassphraseDialog::Mode mode, AskPassphraseDialog::Context ctx);
    void encryptWallet();

    void run(int type) override;
    void onError(QString error, int type) override;
    void unlockWallet();

public Q_SLOTS:
    void updateBalances(const interfaces::WalletBalances& newBalance);
    void updateDisplayUnit();

    void setNumConnections(int count);
    void setNumBlocks(int count);
    void setNetworkActive(bool active);
    void setStakingStatusActive(bool fActive);
    void updateStakingStatus();
    void updateHDState(const bool upgraded, const QString& upgradeError);
    void showUpgradeDialog(const QString& message);

Q_SIGNALS:
    void themeChanged(bool isLight);
    void walletSynced(bool isSync);
    void tierTwoSynced(bool isSync);
    void onShowHideColdStakingChanged(bool show);

protected:
    void resizeEvent(QResizeEvent *event) override;
private Q_SLOTS:
    void onBtnReceiveClicked();
    void onBtnBalanceInfoClicked();
    void onThemeClicked();
    void onBtnLockClicked();
    void lockDropdownMouseLeave();
    void lockDropdownClicked(const StateClicked&);
    void refreshStatus();
    void openLockUnlock();
    void onColdStakingClicked();
    void refreshProgressBarSize();
    void expandSync();
private:
    Ui::TopBar *ui;
    LockUnlock *lockUnlockWidget = nullptr;
    QProgressBar* progressBar = nullptr;

    int nDisplayUnit = -1;
    QTimer* timerStakingIcon = nullptr;
    bool isInitializing = true;

    // info popup
    BalanceBubble* balanceBubble = nullptr;

    void updateTorIcon();
    void connectUpgradeBtnAndDialogTimer(const QString& message);
};

#endif // PIVX_QT_TOPBAR_H
