/*************************************************************************
	Source code for Finny... A linux frontend for the Griffin Radioshark2
	Copyright (C) 2009  John O'Neil
	Email: oneil.code@gmail.com

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

 *************************************************************************/
#include "AudioInterface.h"
#include <math.h>
#include <string.h>
#include <time.h>
#include <gst/interfaces/xoverlay.h>
#include <QApplication>

#include "logging.h"



void AudioInterface::run()
{
	Logger::Write("AudioInterface::run");
	if(!m_pPipeline || !m_pElementIn || !m_pElementOut)
	{
		Logger::Write("ERROR: dangling pointer.");
		return;
	}

	if(gst_element_set_state (GST_ELEMENT (m_pPipeline),GST_STATE_PLAYING)
												==GST_STATE_CHANGE_FAILURE )
	{
		Logger::Write("ERROR: Can't set pipeline to PLAYING.");
		return;
	}

	m_bRunning = true;

}
void AudioInterface::stop()
{
	Logger::Write("AudioInterface::stop");
	if(!m_pPipeline || !m_pElementIn || !m_pElementOut)
	{
		Logger::Write("ERROR: Dangling pointer.");
		return;
	}
	gst_element_set_state (GST_ELEMENT (m_pPipeline),GST_STATE_NULL );
	m_bRunning = false;
}

AudioInterface::AudioInterface()
		:m_pPipeline(NULL)
		,m_pElementIn(NULL)
		,m_pElementOut(NULL)
		,m_pMixer(NULL)
		,m_pTeeOne(NULL)
		,m_pQueue1(NULL)
		,m_pMP3Recorder(NULL)
		,m_pEncoder(NULL)
		,m_pFile(NULL)
		,m_pQueue2(NULL)
		,m_pVisualizationBin(NULL)
		,m_pQueue3(NULL)
		,m_pVisualization(NULL)
		,m_pAppSink(NULL)
		,m_pBus(NULL)
		,m_VisualizationName("monoscope")
{

};
AudioInterface::~AudioInterface()
{

};

bool AudioInterface::Open(const string& capture_dev,const string& output_dev,
						 unsigned int xwindow_id)
{
	Logger::Write("AudioInterface::Open.");
	m_pElementIn = gst_element_factory_make("alsasrc","source");
	if(!m_pElementIn)
	{
		Logger::Write("ERROR: can't create alsasrc.");
		return false;
	}
	//Set the src to the desired device
	g_object_set( G_OBJECT (m_pElementIn ), "device", capture_dev.c_str(),NULL );
	
	//We tee after the input. This point will provide input to visualization
	//AND to any recordings we make.
	m_pTeeOne = gst_element_factory_make("tee", "tee1");
	if(!m_pTeeOne)
	{
		Logger::Write("ERROR: can't create tee one.");
		return false;
	}
	
	//After all tees we require a queue. Without them Gstreamer fails. Go figure.
	m_pQueue1 = gst_element_factory_make("queue", "queue1");
	if(!m_pQueue1)
	{
		Logger::Write("ERROR: can't create queue one.");
		return false;
	}
	
	//Simple volume control. So we don't need a mixer.
	m_pMixer= gst_element_factory_make("volume", "volume");
	if(!m_pMixer)
	{
		Logger::Write("ERROR: can't create volume.");
		return false;
	}
	//Set the volume to a tentative level.
	g_object_set( G_OBJECT ( m_pMixer ), "volume", 0.0,NULL );

	//And our output device.
	if( output_dev  == "PULSE")
	{
		m_pElementOut= gst_element_factory_make("pulsesink","sink");
		if(!m_pElementOut)
		{
			Logger::Write("ERROR: can't create pulsesink.");
			return false;
		}
	}else{
		m_pElementOut= gst_element_factory_make("alsasink","sink");
		if(!m_pElementOut)
		{
			Logger::Write("ERROR: can't create alsasink.");
			return false;
		}
		//Set the sink to the desired device
		g_object_set( G_OBJECT (m_pElementOut ), "device", output_dev.c_str(),NULL );
	}
	
	//We create the pipeline "last" only if all our pipline elements have
	//been successfully created.
	m_pPipeline = gst_pipeline_new ("RADIOSHARK");
	if(!m_pPipeline)
	{
		Logger::Write("ERROR: can't create pipeline.");
		return false;
	}
	m_pBus = gst_pipeline_get_bus (GST_PIPELINE (m_pPipeline));
	if(!m_pBus)
	{
		Logger::Write("ERROR: can't create pipeline bus.");
		return false;
	}
	
	//Add everything to the pipeline
	gst_bin_add_many (GST_BIN (m_pPipeline), m_pElementIn,m_pTeeOne,m_pMixer,
						m_pElementOut,m_pQueue1, NULL);
	//Link the pipeline
	if (!gst_element_link_many (m_pElementIn,m_pTeeOne,m_pQueue1,m_pMixer
									,m_pElementOut , NULL ))
	{
		Logger::Write("ERROR: can't link primary pipeline.");
		return false;
	}

	//Set our visualization
	if( SetVisualization(this->m_VisualizationName,xwindow_id,false)== false)
	{
		Logger::Write("ERROR: problem putting visualization in pipeline.");
	}
	
	//We'lll also construct, but not connect our mp3 recorder
	if(! this->ConstructMP3RecorderBin())
	{
		Logger::Write("ERROR: can't create MP3 recorder bin.");
		return false;
	}
	
	return true;
};
bool AudioInterface::ConstructVisualizationBin(unsigned int xwindow_id )
{
	Logger::Write("AudioInterface::ConstructVisualizationBin.");
	if(m_pVisualizationBin)
	{
		Logger::Write("ERROR: Attempt to create visualization twice.");
		return false;//don't initialize it twice!
	}
	m_pVisualizationBin = gst_bin_new ("VIZ");
	if(!m_pVisualizationBin)
	{
		Logger::Write("ERROR: can't create visualizatio bin bin..");
		return false;
	}
	
	m_pQueue3= gst_element_factory_make("queue", "queue3");
	if(!m_pQueue3)
	{
		Logger::Write("ERROR: Can't create queue 3.");
		return false;
	}
	m_pVisualization =  gst_element_factory_make(m_VisualizationName.c_str(),
													"visualization");
	if(!m_pVisualization)
	{
		Logger::Write("ERROR: Can't create visualzation.");
		Logger::Write(m_VisualizationName.c_str());
		return false;
	}
	m_pAppSink = gst_element_factory_make("ximagesink", "appsink");
	if(!m_pAppSink)
	{
		Logger::Write("ERROR: Can't create ximagesink.");
		return false;
	}
	gst_element_set_state(m_pAppSink, GST_STATE_READY);
	QApplication::syncX();
	gst_x_overlay_set_xwindow_id(GST_X_OVERLAY(m_pAppSink),xwindow_id);
	
	gst_bin_add_many (GST_BIN (m_pVisualizationBin),m_pQueue3,m_pVisualization,
												m_pAppSink,NULL);
	if ( gst_element_link_many (m_pQueue3, m_pVisualization, m_pAppSink,
									 NULL ) == FALSE )
	{
		Logger::Write("ERROR: Can't link visualization bin contents.");
		return false;
	}
	//Conneect src and sink ghost pads up to input and output of bin
	//Need a "ghost pad" on the MP3 recorder sink (input)
	GstPad *pad = gst_element_get_static_pad (m_pQueue3, "sink");
	gst_element_add_pad (m_pVisualizationBin, gst_ghost_pad_new ("sink", pad));
	gst_object_unref (GST_OBJECT (pad));

	return true;
}

bool AudioInterface::ConstructMP3RecorderBin( void )
{
	//Create our MP3 recorder Bin
	Logger::Write("AudioInterface::ConstructMP3RecorderBin.");
	m_pMP3Recorder = gst_bin_new ("MP3");
	if(!m_pMP3Recorder)
	{
		Logger::Write("ERROR: Can't create MP3 recorder bin.");
		return false;
	}
	
	m_pQueue2 = gst_element_factory_make("queue", "queue2");
	if(!m_pQueue2)
	{
		Logger::Write("ERROR: Can't create queue 2.");
		return false;
	}

	m_pEncoder = gst_element_factory_make("lame", "lame");
	if(!m_pEncoder)
	{
		Logger::Write("ERROR: Can't create lame element.");
		return false;
	}
	
	m_pFile = gst_element_factory_make("filesink", "file");
	if(!m_pFile)
	{
		Logger::Write("ERROR: Can't create filesink.");
		return false;
	}
	//Add everything to the bin
	gst_bin_add_many (GST_BIN (m_pMP3Recorder),m_pQueue2,m_pEncoder,
											m_pFile, NULL);
	
	if ( gst_element_link_many (m_pQueue2, m_pEncoder,
									m_pFile, NULL ) == FALSE )
	{
		Logger::Write("ERROR: Can't link MP3 bin contents.");
		return false;
	}
	
	//Need a "ghost pad" on the MP3 recorder sink (input)
	GstPad *pad = gst_element_get_static_pad (m_pQueue2, "sink");
	gst_element_add_pad (m_pMP3Recorder, gst_ghost_pad_new ("sink", pad));
	gst_object_unref (GST_OBJECT (pad));
	
	return true;
}
	
void AudioInterface::Close(void)
{
	Logger::Write("AudioInterface::Close.");
	if( gst_bin_get_by_name( GST_BIN(m_pPipeline),"MP3") == NULL )
	{
		gst_object_unref (GST_OBJECT (m_pMP3Recorder));
	}
	gst_object_unref (GST_OBJECT (m_pPipeline));
};

void AudioInterface::UpdateVolume( int vol )
{
	if(!m_pMixer )
	{
		return;
	}
	double value = ((double)vol)/100.0;
	g_object_set( G_OBJECT ( m_pMixer ), "volume", value,NULL );

}
int AudioInterface::GetVolume(void)
{
	if(!m_pMixer )
	{
		return 0;
	}
	double value = 0.0;
	g_object_get( G_OBJECT ( m_pMixer ), "volume", &value,NULL );
	return (int)(value*100.0);
}
void AudioInterface::Mute(bool muted)
{
	if(!m_pMixer )
	{
		return;
	}
	g_object_set( G_OBJECT ( m_pMixer ), "mute", muted,NULL );

}
void AudioInterface::Record(bool start,MP3Settings* settings )
{
	Logger::Write("AudioInterface::Record.");
	if(!m_pPipeline || !m_pBus || ! m_pMP3Recorder)
	{
		Logger::Write("ERROR: Dangling pointers.");
		return;
	}
	if( gst_bin_get_by_name( GST_BIN(m_pPipeline),"MP3") == NULL )
	{
		if(start == false)
		{
			Logger::Write("ERROR: not recording.");
			return;//Can't stop the recording if we're not recording!
		}
	}else{
		if(start == true)
		{
			Logger::Write("ERROR: already recording.");
			//Can't start the recording if we're already recording!
			return;
		}
	}
	
	//We've got to pause in order to insert the bin into our pipeline
	if(gst_element_set_state (GST_ELEMENT (m_pPipeline),GST_STATE_PAUSED)
								== GST_STATE_CHANGE_FAILURE)
	{
		Logger::Write("ERROR: could not set pipline to PAUSED.");
		return;
	}
	//Wait for the EOS message via gst_bus_poll (blocking)
	GstMessage* pMsg = gst_bus_poll(m_pBus,GST_MESSAGE_ANY,-1);

	if( start && settings != NULL )
	{
		//connect the ghost pad to the tee in the pipeline
		g_object_set( G_OBJECT ( m_pFile ), "location",
								settings->filename.c_str(),NULL );
		g_object_set( G_OBJECT ( m_pEncoder) , "mode"
								,settings->mode
								, NULL);
		g_object_set( G_OBJECT ( m_pEncoder ), "bitrate"
								,settings->bitrate, NULL);
		
		gst_bin_add( GST_BIN(m_pPipeline),m_pMP3Recorder);
		gst_element_link( m_pTeeOne , m_pMP3Recorder);
	}else{
		//disconnect the ghost pad to the tee in the pipeline
		gst_element_unlink( m_pTeeOne , m_pMP3Recorder);
		gst_bin_remove( GST_BIN(m_pPipeline),m_pMP3Recorder);
		gst_element_set_state (GST_ELEMENT (m_pMP3Recorder),GST_STATE_NULL);
	}
	if(gst_element_set_state (GST_ELEMENT (m_pPipeline),GST_STATE_PLAYING)
											==GST_STATE_CHANGE_FAILURE)
	{
		Logger::Write("ERROR: could not set pipeline back to PLAYING.");
	}
}
float AudioInterface::GetAudioLevel(void)
{
	float rms=0.0f;
	if(!m_pAppSink)
	{
		return 0.0f;
	}
	GstBuffer* buffer = gst_app_sink_pull_buffer(GST_APP_SINK(m_pAppSink));
	if(buffer == NULL)
	{
		return 0.0f;
	}

	//We want the root mean square value for (say) even samples
	int nbytes = GST_BUFFER_SIZE(buffer);
	short* pSamples= (short*)GST_BUFFER_DATA(buffer);
	int nsamples = nbytes/4;
	int i = 0;
	for(i = 0; i <  nsamples ; i+=2)
	{
		rms+= ((float)pSamples[i])*((float)pSamples[i]);
	}
	rms/=(float)(i/2);
	rms = sqrt(rms);
	return rms;
}
bool AudioInterface::GetAudioFormat( AudioFormat& format)
{
	if(!m_pElementIn)
	{
		return false;
	}
	GstPad* pad = gst_element_get_pad ( m_pElementIn, "src");
	if(!pad)
	{
		return false;
	}
	GstCaps *caps = gst_pad_get_negotiated_caps(pad);
	if(!caps)
	{
		return false;
	}
	const GstStructure *str = gst_caps_get_structure (caps, 0);
	gboolean is_signed;
	gst_structure_get_boolean (str, "signed", &is_signed);
	if(is_signed)
	{
		format.is_signed = true;
	}else{
		format.is_signed = false;
	}
	gst_structure_get_int (str, "channels", &format.channels);
	gst_structure_get_int (str, "rate", &format.sampling_rate);
	gst_structure_get_int (str, "width", &format.width);
	gst_structure_get_int (str, "depth", &format.depth);
	gst_structure_get_int (str, "endianness", &format.endianness);
	
	gst_caps_unref(caps);
	gst_object_unref(pad);
	return true;
}

void AudioInterface::SetVisualizationName(const string& name)
{
	m_VisualizationName = name;
}
bool AudioInterface::SetVisualization( const string& viz_name, 
										unsigned int xwindow_id,
										bool stop_pipeline)
{
	Logger::Write("AudioInterface::SetVisualization.");
	if(!m_pPipeline)
	{
		Logger::Write("ERROR: Pipeline absent.");
		return false;
	}
	if(this->m_VisualizationName == viz_name && this->m_pVisualizationBin)
	{
		Logger::Write("ERROR: Same visalization.");
		return true;//This one's already playing.
	}
	if(this->m_VisualizationName != viz_name && this->m_pVisualizationBin)
	{
		//we want a new viz, stop everything and create the new one
		if( stop_pipeline )
		{
			if(gst_element_set_state (GST_ELEMENT (m_pPipeline),GST_STATE_READY )
												== GST_STATE_CHANGE_FAILURE)
			{
				return false;
			}
			GstState newstate,pendingstate;
			if( gst_element_get_state (GST_ELEMENT (m_pPipeline),
									 &newstate,
									&pendingstate,
									GST_CLOCK_TIME_NONE )==GST_STATE_CHANGE_FAILURE)
			{
				Logger::Write("ERROR: Failed to set pipeline to READY.");
				return false;
			}
		}
		gst_element_unlink( m_pTeeOne , m_pVisualizationBin);
		gst_bin_remove( GST_BIN(m_pPipeline),m_pVisualizationBin);
		gst_element_set_state (GST_ELEMENT (m_pVisualizationBin),GST_STATE_NULL);
		//gst_object_unref (GST_OBJECT (m_pVisualizationBin));
		m_pVisualizationBin = NULL;
		//We've gotten rid of the old viz bin!
	}
	bool success = false;
	if(!m_pVisualizationBin)
	{
		//Must be the first call, so create our viz_bin
		this->m_VisualizationName = viz_name;
		success = this->ConstructVisualizationBin(xwindow_id);
		if(!success)
		{
			Logger::Write("ERROR: Could not construct new viz bin.");
			return false;
		}
	}

	//Add in the visualization
	gst_bin_add( GST_BIN(m_pPipeline) , m_pVisualizationBin );
	if( gst_element_link( m_pTeeOne, m_pVisualizationBin ) == FALSE )
	{
		Logger::Write("ERROR: can't link visualization to tee one.");
		success = false;
	}
		
	//If we were playing before this call, set playing again.
	if(stop_pipeline )
	{
		if(gst_element_set_state (GST_ELEMENT (m_pPipeline),GST_STATE_PLAYING )
											==GST_STATE_CHANGE_FAILURE )
		{
			Logger::Write("ERROR: can't set pipline back to PLAYING");
			return false;
		}
	}
	
	return success;
}



