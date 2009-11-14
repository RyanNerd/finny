#ifndef __MP3SETTINGS_H__
#define __MP3SETTINGS_H__

#include <string>
#include <fstream>

using namespace std;

struct MP3Settings
{
	enum Mode
	{
		Stereo = 0,
		Joint_Stereo = 1,
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
	//Some helpers
	static string mode2string(MP3Settings::Mode md);
	static MP3Settings::Mode string2mode( const string& md);
	
	//File IO
	void Read(ifstream& infile);
	void Write(ofstream& outfile);
};

#endif // __MP3SETTINGS_H__
