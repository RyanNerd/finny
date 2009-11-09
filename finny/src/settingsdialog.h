#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H
//
#include <QDialog>
#include "ui_Settings.h"
#include "finnysettings.h"
//
class SettingsDialog : public QDialog, public Ui::Dialog
{
Q_OBJECT
public:
	SettingsDialog( QWidget * parent = 0, Qt::WFlags f = 0 );
	
	//Set with the current application settings:
	void Set( FinnySettings& settings);
	//Get the current settings
	void Get( FinnySettings& settings);
private slots:

public slots:
	void OnBandChange(int band);
};
#endif





