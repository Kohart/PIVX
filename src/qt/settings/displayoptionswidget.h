// Copyright (c) 2019 The PIVX Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef PIVX_QT_SETTINGS_DISPLAYOPTIONSWIDGET_H
#define PIVX_QT_SETTINGS_DISPLAYOPTIONSWIDGET_H

#include "pwidget.h"
#include <QDataWidgetMapper>
#include <QWidget>

namespace Ui {
class SettingsDisplayOptionsWidget;
}

class SettingsDisplayOptionsWidget : public PWidget
{
    Q_OBJECT

public:
    explicit SettingsDisplayOptionsWidget(PIVXGUI* _window = nullptr, QWidget *parent = nullptr);
    ~SettingsDisplayOptionsWidget();

    void setMapper(QDataWidgetMapper *mapper);
    void initLanguages();
    void loadClientModel() override;

public Q_SLOTS:
    void onResetClicked();

Q_SIGNALS:
    void saveSettings();
    void discardSettings();

private:
    Ui::SettingsDisplayOptionsWidget *ui;
};

#endif // PIVX_QT_SETTINGS_DISPLAYOPTIONSWIDGET_H
