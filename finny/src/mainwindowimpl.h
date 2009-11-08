#ifndef MAINWINDOWIMPL_H
#define MAINWINDOWIMPL_H
//
#include <QMainWindow>
#include "ui_mainwindow.h"

#include <stdio.h>
#include <string.h>

#include "AudioInterface.h"
#include "radioshark.h"
#include "finnysettings.h"

#include <QStandardItemModel>
#include <QTimer>
#include <QGraphicsScene>

struct VisualizationFrame
{
	uchar* data;
	int width;
	int height;
	int buffer_size;
	QImage Image;
	VisualizationFrame()
		:data(NULL)
		,width(0)
		,height(0)
		,buffer_size(0)
	{
		
	};
	~VisualizationFrame()
	{
		if(data)
		{
			delete [] data;
		}
	}
};

class MainWindowImpl : public QMainWindow, public Ui::MainWindow
{
Q_OBJECT
public:
	MainWindowImpl( QWidget * parent = 0, Qt::WFlags f = 0 );
	void closeEvent(QCloseEvent *event);

	
protected:

	AudioInterface m_AudioInterface;
	Radioshark2Interface* m_pRadioshark;
	
	//Presets for now
	QStandardItemModel m_Presets;
	
	//Timer to update level indicator
	QTimer m_LevelTimer;
	
	void LoadSettings(void);
	void SaveSettings(void);
	
	void GetAudioFormat(void);
	void UpdateFrequencyDisplay(void);
	
	//A visualization "scene"
	QGraphicsScene m_GraphicsScene;
	VisualizationFrame m_LastFrame;
	
	//Look for the Radioshark! (audio capture device)
	bool FindRadioshark(string& device);
	QTimer m_CheckRadiosharkTimer;
	
private slots:
	void OnFreqUp(void);
	void OnFreqDown(void);
	void OnVolume(int volume );
	void OnMute( bool muted );
	void OnRecord( bool start );
	void OnBandChange(void);
	void OnSavePreset(void);
	void OnPreset(const QModelIndex &index);
	void OnSettings(void);
	void OnLevelTimer(void);
	void OnFastUp(void);
	void OnFastDown(void);
	void OnRemovePreset(void);
	void OnCheckRadiosharkTimer(void);
};
#endif




