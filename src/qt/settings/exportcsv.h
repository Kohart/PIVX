// Copyright (c) 2019-2020 The PIVX Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PIVX_QT_SETTINGS_EXPORTCSV_H
#define PIVX_QT_SETTINGS_EXPORTCSV_H

#include "pwidget.h"
#include "transactionfilterproxy.h"
#include <QSortFilterProxyModel>
#include <QWidget>

namespace Ui {
class SettingsExportCSV;
}

class SettingsExportCSV : public PWidget
{
    Q_OBJECT

public:
    explicit SettingsExportCSV(PIVXGUI* _window, QWidget *parent = nullptr);
    ~SettingsExportCSV();

private Q_SLOTS:
    void selectFileOutput(const bool isTxExport);
    void exportTxes(const QString& filename);
    void exportAddrs(const QString& filename);

private:
    Ui::SettingsExportCSV *ui;
    TransactionFilterProxy* txFilter{nullptr};
    QSortFilterProxyModel* addressFilter{nullptr};
};

#endif // PIVX_QT_SETTINGS_EXPORTCSV_H
