// Copyright (c) 2019 The PIVX Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PIVX_QT_CONTACTDROPDOWNROW_H
#define PIVX_QT_CONTACTDROPDOWNROW_H

#include <QWidget>

namespace Ui {
class ContactDropdownRow;
}

class ContactDropdownRow : public QWidget
{
    Q_OBJECT

public:
    explicit ContactDropdownRow(QWidget *parent = nullptr);
    ~ContactDropdownRow();

    void init(bool isLightTheme, bool isHover);
    void update(bool isLightTheme, bool isHover, bool isSelected);
    void setData(QString address, QString label);

private:
    Ui::ContactDropdownRow *ui;
};

#endif // PIVX_QT_CONTACTDROPDOWNROW_H
