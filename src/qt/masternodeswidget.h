// Copyright (c) 2019-2022 The PIVX Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PIVX_QT_MASTERNODESWIDGET_H
#define PIVX_QT_MASTERNODESWIDGET_H

#include "coincontroldialog.h"
#include "furabstractlistitemdelegate.h"
#include "pwidget.h"
#include "tooltipmenu.h"

#include <atomic>

#include <QTimer>
#include <QWidget>

class PIVXGUI;
class MNModel;

namespace Ui {
class MasterNodesWidget;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

class MasterNodesWidget : public PWidget
{
    Q_OBJECT

public:

    explicit MasterNodesWidget(PIVXGUI *parent = nullptr);
    ~MasterNodesWidget();
    void resetCoinControl();
    void setMNModel(MNModel* _mnModel);

    void run(int type) override;
    void onError(QString error, int type) override;

    void showEvent(QShowEvent *event) override;
    void hideEvent(QHideEvent *event) override;

private Q_SLOTS:
    void onCoinControlClicked();
    void onCreateMNClicked();
    void onStartAllClicked(int type);
    void changeTheme(bool isLightTheme, QString &theme) override;
    void onMNClicked(const QModelIndex &index);
    void onEditMNClicked();
    void onDeleteMNClicked();
    void onInfoMNClicked();
    void updateListState();
    void updateModelAndInform(const QString& informText);

private:
    Ui::MasterNodesWidget *ui;
    FurAbstractListItemDelegate *delegate;
    MNModel *mnModel = nullptr;
    TooltipMenu* menu = nullptr;
    QModelIndex index;
    QTimer *timer = nullptr;
    CoinControlDialog* coinControlDialog = nullptr;

    std::atomic<bool> isLoading;

    bool checkMNsNetwork();
    void startAlias(const QString& strAlias);
    bool startAll(QString& failedMN, bool onlyMissing);
};

#endif // PIVX_QT_MASTERNODESWIDGET_H
