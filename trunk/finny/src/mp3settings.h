#ifndef __MP3SETTINGS_H__
#define __MP3SETTINGS_H__

#include <string>

struct MP3Settings
{
	enum Mode
	{
		Stereo = 0,
		Joint_Steroe = 1,
		Dual_Channel = 2,
		Mono = 3,
		Auto = 4
	};
	
	std::string filename;
	int bitrate; //(8 to 320)
	Mode mode;
	
	MP3Settings()
		:filename("recording.mp3")
		,bitrate(128)
		,mode(MP3Settings::Auto)
	{
		
	};
};

#endif // __MP3SETTINGS_H__
