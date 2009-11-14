#include "mp3settings.h"
string MP3Settings::mode2string(MP3Settings::Mode md)
{
	switch(md)
	{
		case Stereo:
			return string("Stereo");
			break;
		case Joint_Stereo:
			return string("Joint_Stereo");
			break;
		case Dual_Channel:
			return string("Dual_Channel");
			break;
		case Mono:
			return string("Mono");
			break;
		case Auto:
			return string("Auto");
			break;
	}
	return string("Auto");
}
MP3Settings::Mode MP3Settings::string2mode( const string& md)
{
	if( md == "Stereo")
	{
		return MP3Settings::Stereo;
	}else if(md == "Joint_Stereo")
	{
		return MP3Settings::Joint_Stereo;
	}else if( md == "Dual_Channel" )
	{
		return MP3Settings::Dual_Channel;
	}else if( md == "Mono")
	{
		return MP3Settings::Mono;
	}else if( md == "Auto")
	{
		return MP3Settings::Auto;
	}else{
		return MP3Settings::Auto;
	}
}
void MP3Settings::Read(ifstream& infile)
{
	string md;
	infile>>bitrate;
	infile>>md;//mode;
	mode = MP3Settings::string2mode(md);
	
}
void MP3Settings::Write(ofstream& outfile)
{
	string md = MP3Settings::mode2string(mode);
	outfile<<"SETTING: MP3 "<<bitrate<<" "<<md<<endl;
}
