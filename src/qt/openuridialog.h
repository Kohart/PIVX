// Copyright (c) 2019-2021 The PIVX Core developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PIVX_QT_OPENURIDIALOG_H
#define PIVX_QT_OPENURIDIALOG_H

#include "snackbar.h"
#include <QDialog>

namespace Ui
{
class OpenURIDialog;
}

class OpenURIDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OpenURIDialog(QWidget* parent);
    ~OpenURIDialog();

    QString getURI();
    void showEvent(QShowEvent *event) override;

protected Q_SLOTS:
    void accept() override;

private:
    Ui::OpenURIDialog* ui;
    SnackBar *snackBar = nullptr;
    void inform(const QString& str);
};

#endif // PIVX_QT_OPENURIDIALOG_H
