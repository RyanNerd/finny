#ifndef __AUDIOINTERFACE_H__
#define __AUDIOINTERFACE_H__

/*GSTREAMER INCLUDE*/
#include <gst/gst.h>
#include <gst/interfaces/mixer.h>
#include <gst/app/gstappsink.h>

#include <iostream>
#include <string>

#include "mp3settings.h"

/*
	cat /proc/asound/pcm
	gst-launch-0.10 alsasrc device=hw:1,0 ! audioconvert ! alsasink device=hw:0,0
	--cflags glib-2.0 gstreamer-plugins-base  -lgstinterfaces-0.10 -lgstaudio-0.10
	 gst-launch filesrc location=music.wav ! wavparse ! mpegaudio ! filesink location=music.mp3
	audioconvert
	gst-launch -v audiotestsrc ! goom ! ffmpegcolorspace ! xvimagesink
*/
using namespace std;

struct AudioFormat
{
	bool is_signed;
	int width;
	int depth;
	int sampling_rate;
	int endianness;
	int channels;
	//string type;
};

class AudioInterface //: public QThread
{
public:
	
	AudioInterface();
	~AudioInterface();
	
protected:
	//Gstreamer main pipeline
	GstElement *m_pPipeline;
		GstElement* m_pElementIn;
		GstElement* m_pElementOut;
		GstElement *m_pMixer;
		GstElement *m_pTeeOne;
		GstElement *m_pQueue1;
	
	//MP3 recording bin (branch off Tee above when on)
	bool ConstructMP3RecorderBin( void );
	GstElement *m_pMP3Recorder;
		GstElement *m_pEncoder;
		GstElement *m_pFile;
		GstElement *m_pQueue2;
		
	//Appsink, to allow appliction to get audio visualization data
	bool ConstructVisualizationBin( unsigned int xwindow_id );
	GstElement *m_pVisualizationBin;
		GstElement *m_pQueue3;
		GstElement *m_pVisualization;
		GstElement* m_pAppSink;
		
	//Bus
	GstBus *m_pBus;
	
	bool m_bRunning;
	string m_VisualizationName;

public:
	bool Open(const string& capture_dev,const string& output_dev,
													unsigned int xwindow_id = 0);
	void run();
	void stop();
	void Close(void);
	void UpdateVolume( int vol );
	int GetVolume(void);
	void Mute(bool muted);
	void Record(bool start,MP3Settings* settings = NULL );
	float GetAudioLevel(void);
	bool GetAudioFormat( AudioFormat& format);
	void SetVisualizationName(const string& name);
};

#endif // __AUDIOINTERFACE_H__
