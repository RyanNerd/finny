
#include "AudioInterface.h"
#include <math.h>
#include <string.h>
#include <time.h>
#include <gst/interfaces/xoverlay.h>
#include <QApplication>



void AudioInterface::run()
{
	if(!m_pPipeline || !m_pElementIn || !m_pElementOut)
	{
		return;
	}
	if(gst_element_set_state (GST_ELEMENT (m_pPipeline),GST_STATE_READY)
												!=GST_STATE_CHANGE_SUCCESS )
	{
		return;
	}
	if(gst_element_set_state (GST_ELEMENT (m_pPipeline),GST_STATE_PLAYING)
												!=GST_STATE_CHANGE_SUCCESS )
	{
		return;
	}

	m_bRunning = true;

}
void AudioInterface::stop()
{
	if(!m_pPipeline || !m_pElementIn || !m_pElementOut)
	{
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
	//Pipeline first
	m_pPipeline = gst_pipeline_new ("RADIOSHARK");
	if(!m_pPipeline)
	{
		return false;
	}
	m_pBus = gst_pipeline_get_bus (GST_PIPELINE (m_pPipeline));
	if(!m_pBus)
	{
		return false;
	}
	
	m_pElementIn = gst_element_factory_make("alsasrc","source");
	if(!m_pElementIn)
	{
		return false;
	}
	//Set the src to the desired device
	g_object_set( G_OBJECT (m_pElementIn ), "device", capture_dev.c_str(),NULL );
	
	//We tee after the input. This point will provide input to visualization
	//AND to any recordings we make.
	m_pTeeOne = gst_element_factory_make("tee", "tee1");
	if(!m_pTeeOne)
	{
		return false;
	}
	
	//After all tees we require a queue. Without them Gstreamer fails. Go figure.
	m_pQueue1 = gst_element_factory_make("queue", "queue1");
	if(!m_pQueue1)
	{
		return false;
	}
	
	//Simple volume control. So we don't need a mixer.
	m_pMixer= gst_element_factory_make("volume", "volume");
	if(!m_pMixer)
	{
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
			return false;
		}
	}else{
		m_pElementOut= gst_element_factory_make("alsasink","sink");
		if(!m_pElementOut)
		{
			return false;
		}
		//Set the sink to the desired device
		g_object_set( G_OBJECT (m_pElementOut ), "device", output_dev.c_str(),NULL );
	}

	//Add everything to the pipeline
	gst_bin_add_many (GST_BIN (m_pPipeline), m_pElementIn,m_pTeeOne,m_pMixer,
						m_pElementOut,m_pQueue1, NULL);
	//Link the pipeline
	if (!gst_element_link_many (m_pElementIn,m_pTeeOne,m_pQueue1,m_pMixer
									,m_pElementOut , NULL ))
	{
		return false;
	}
	
	//We need to add the visualization too.
	if( this->ConstructVisualizationBin(xwindow_id) == false)
	{
		return false;
	}
	
	//Add in the visualization
	gst_bin_add( GST_BIN(m_pPipeline) , m_pVisualizationBin );
	if( gst_element_link( m_pTeeOne, m_pVisualizationBin ) == FALSE )
	{
		return false;
	}
	
	//We'lll also construct, but not connect our mp3 recorder
	if(! this->ConstructMP3RecorderBin())
	{
		return false;
	}
	
	return true;
};
bool AudioInterface::ConstructVisualizationBin(unsigned int xwindow_id )
{
	if(m_pVisualizationBin)
	{
		return false;//don't initialize it twice!
	}
	m_pVisualizationBin = gst_bin_new ("VIZ");
	if(!m_pVisualizationBin)
	{
		return false;
	}
	
	m_pQueue3= gst_element_factory_make("queue", "queue3");
	if(!m_pQueue3)
	{
		return false;
	}
	m_pVisualization =  gst_element_factory_make(m_VisualizationName.c_str(),
													"visualization");
	if(!m_pVisualization)
	{
		return false;
	}
	m_pAppSink = gst_element_factory_make("ximagesink", "appsink");
	if(!m_pAppSink)
	{
		return false;
	}
	gst_element_set_state(m_pAppSink, GST_STATE_READY);
	QApplication::syncX();
	gst_x_overlay_set_xwindow_id(GST_X_OVERLAY(m_pAppSink),xwindow_id);
	//gst_app_sink_set_drop(GST_APP_SINK(m_pAppSink),TRUE);
	//gst_app_sink_set_max_buffers (GST_APP_SINK(m_pAppSink),1);
	
	gst_bin_add_many (GST_BIN (m_pVisualizationBin),m_pQueue3,m_pVisualization,
												m_pAppSink,NULL);
	if ( gst_element_link_many (m_pQueue3, m_pVisualization, m_pAppSink,
									 NULL ) == FALSE )
	{
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
	m_pMP3Recorder = gst_bin_new ("MP3");
	if(!m_pMP3Recorder)
	{
		return false;
	}
	
	m_pQueue2 = gst_element_factory_make("queue", "queue2");
	if(!m_pQueue2)
	{
		return false;
	}

	m_pEncoder = gst_element_factory_make("lame", "lame");
	if(!m_pEncoder)
	{
		return false;
	}
	
	m_pFile = gst_element_factory_make("filesink", "file");
	if(!m_pFile)
	{
		return false;
	}
	//Add everything to the bin
	gst_bin_add_many (GST_BIN (m_pMP3Recorder),m_pQueue2,m_pEncoder,
											m_pFile, NULL);

	
	if ( gst_element_link_many (m_pQueue2, m_pEncoder,
									m_pFile, NULL ) == FALSE )
	{
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
	if(!m_pPipeline || !m_pBus || ! m_pMP3Recorder)
	{
		return;
	}
	if( gst_bin_get_by_name( GST_BIN(m_pPipeline),"MP3") == NULL )
	{
		if(start == false)
		{
			return;//Can't stop the recording if we're not recording!
		}
	}else{
		if(start == true)
		{
			//Can't start the recording if we're already recording!
			return;
		}
	}
	
	//We've got to pause in order to insert the bin into our pipeline
	gst_element_set_state (GST_ELEMENT (m_pPipeline),GST_STATE_PAUSED);
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
	gst_element_set_state (GST_ELEMENT (m_pPipeline),GST_STATE_PLAYING);
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



