#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H
//
#include <QDialog>
#include "ui_Settings.h"
//
class SettingsDialog : public QDialog, public Ui::Dialog
{
Q_OBJECT
public:
	SettingsDialog( QWidget * parent = 0, Qt::WFlags f = 0 );
private slots:
};
#endif





