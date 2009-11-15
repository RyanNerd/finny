#include "settingsdialog.h"
#include <QFileDialog>
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
	RecordingPath->setText( settings.RecordingPath.c_str() );
	Bitrate->setValue(settings.MP3.bitrate);
	MP3Format->setCurrentIndex((int)settings.MP3.mode);
	if( settings.AutogenerateRecordingNames )
	{
		AutoGenerateMP3Filenames->setChecked(true);
	}else{
		BrowseMP3Filenames->setChecked(true);
	}
	int index = VisualizationName->findText(settings.VisualizationName.c_str());
	if(index >= 0)
	{
		VisualizationName->setCurrentIndex(index);
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
	settings.RecordingPath = string(RecordingPath->text().toAscii());
	settings.MP3.mode = (MP3Settings::Mode) MP3Format->currentIndex();
	settings.MP3.bitrate = Bitrate->value();
	settings.AutogenerateRecordingNames = AutoGenerateMP3Filenames->isChecked();
	settings.VisualizationName = string(VisualizationName->itemText(
										VisualizationName->currentIndex())
										.toAscii());
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
void SettingsDialog::OnRecordingPathBrowse()
{
	QString newpath= QFileDialog::getExistingDirectory(this,
		tr("MP3 Recording Directory"), RecordingPath->text());
	if(!newpath.isNull())
	{
		RecordingPath->setText(newpath);
	}
}
void SettingsDialog::OnResetDefaultSettings(void)
{
	
}
//

