#include "settingsdialog.h"
//
SettingsDialog::SettingsDialog( QWidget * parent, Qt::WFlags f) 
	: QDialog(parent, f)
{
	setupUi(this);
}

//Set with the current application settings:
void SettingsDialog::Set( FinnySettings& settings)
{
	if(settings.StartFreq.GetBand() == Preset::AM )
	{
		StartBand->setCurrentIndex(0);
		OnBandChange(0);
	}else{
		StartBand->setCurrentIndex(1);
		OnBandChange(1);
	}
	StartFreq->setValue(settings.StartFreq.GetFreq());
	FixedVolume->setValue(settings.StartVolume);
	
	if(settings.UpdateStartFreqOnClose)
	{
		StartAtLastFrequency->setChecked(true);
		StartFrequencyPanel->setDisabled(true);
	}else{
		StartAtFixedFrequency->setChecked(true);
	}
	if(settings.UpdateStartVolumeOnClose)
	{
		StartAtLastVolume->setChecked(true);
		StartVolumePanel->setDisabled(true);
	}else{
		StartAtVolume->setChecked(true);
	}
}
//Get the current settings
void SettingsDialog::Get( FinnySettings& settings)
{
	if( StartAtLastFrequency->isChecked())
	{
		settings.UpdateStartFreqOnClose = true;
	}else{
		settings.UpdateStartFreqOnClose = false;
		if(StartBand->currentIndex() == 0)
		{
			settings.StartFreq.SetBand(Preset::AM);
		}else{
			settings.StartFreq.SetBand(Preset::FM);
		}
		settings.StartFreq.SetFreq((float)StartFreq->value());
	}
	if(StartAtLastVolume->isChecked())
	{
		settings.UpdateStartVolumeOnClose = true;
	}else{
		settings.UpdateStartVolumeOnClose = false;
		settings.StartVolume = (float)FixedVolume->value();
	}
}
void SettingsDialog::OnBandChange(int band)
{
	if(band == 0)
	{
		StartFreq->setMinimum(520.0);
		StartFreq->setMaximum(1610.0);
		StartFreq->setSingleStep(1.0);
		StartFreq->setValue(630.0);
	}else{
		StartFreq->setMinimum(87.5);
		StartFreq->setMaximum(108.0);
		StartFreq->setSingleStep(0.1);
		StartFreq->setValue(99.5);
	}
}
//

