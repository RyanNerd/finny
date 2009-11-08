#ifndef __FINNYSETTINGS_H__
#define __FINNYSETTINGS_H__

#include <string>
#include <list>
#include <fstream>

using namespace std;

//Helper function
void GetToken(string& input,string& token,string& leftover);


class Preset
{
public:
	Preset();
	Preset(bool am, float f);
	~Preset();
	
	enum Band
	{
		FM = 0,
		AM = 1
	};
	
	Preset::Band GetBand();
	float GetFreq();
	string& GetDescription();
	void SetDescription( string& desc);
	
	void Write( ofstream& outfile);
	void WritePreset( ofstream& outfile);
	static void Write( ofstream& outfile, bool AM, float freq, string& desc);
	bool Read( ifstream& infile);
	static void Read( ifstream& infile, bool& AM, float& freq, string& desc);
	
protected:
	Band m_Band;
	float m_Frequency;
	string m_Description;
	
};

struct FinnySettings
{
	Preset StartFreq;
	bool UpdateStartFreqOnClose;
	float StartVolume;
	bool UpdateStartVolumeOnClose;
	
	FinnySettings()
		:StartFreq(false,99.5f)
		,UpdateStartFreqOnClose(true)
		,StartVolume(0.0f)
		,UpdateStartVolumeOnClose(false)
	{
		
	};
	//General helpers
	static void LoadSetting( FinnySettings& settings, ifstream& infile);
	static void WriteSettings( FinnySettings& settings, ofstream& outfile);
	static void ReadBool(ifstream& infile, bool& value);
	static void WriteBool(ofstream& outfile, bool value);
	static void ReadFloat(ifstream& infile, float& value);
	static void WriteFloat(ofstream& outfile, float value);
};

#endif // __FINNYSETTINGS_H__
