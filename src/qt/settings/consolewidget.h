// Copyright (c) 2019-2021 The PIVX Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PIVX_QT_SETTINGS_CONSOLEWIDGET_H
#define PIVX_QT_SETTINGS_CONSOLEWIDGET_H

#include "guiutil.h"
#include "net.h"
#include "pwidget.h"
#include <QCompleter>
#include <QWidget>

class ClientModel;
class RPCTimerInterface;

namespace Ui {
class SettingsConsoleWidget;
}

QT_BEGIN_NAMESPACE
class QMenu;
class QItemSelection;
QT_END_NAMESPACE

class SettingsConsoleWidget : public PWidget
{
    Q_OBJECT

public:
    explicit SettingsConsoleWidget(PIVXGUI* _window, QWidget *parent = nullptr);
    ~SettingsConsoleWidget();

    void loadClientModel() override;
    void showEvent(QShowEvent *event) override;

public Q_SLOTS:
    void clear(bool clearHistory = true);
    void response(int category, const QString &message) { messageInternal(category, message); };
    void messageInternal(int category, const QString &message, bool html = false);
    /** Go forward or back in history */
    void browseHistory(int offset);
    /** Scroll console view to end */
    void scrollToEnd();
    void onCommandsClicked();

protected:
    virtual bool eventFilter(QObject* obj, QEvent* event) override;

protected Q_SLOTS:
    void changeTheme(bool isLightTheme, QString &theme) override;

Q_SIGNALS:
    // For RPC command executor
    void stopExecutor();
    void cmdCommandRequest(const QString& command);

private:
    Ui::SettingsConsoleWidget *ui;

    QStringList history;
    int historyPtr;
    RPCTimerInterface *rpcTimerInterface;
    QCompleter *autoCompleter;

    void startExecutor();

private Q_SLOTS:
    void on_lineEdit_returnPressed();


};

#endif // PIVX_QT_SETTINGS_CONSOLEWIDGET_H
