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
	static void Write( ofstream& outfile, bool AM, float freq, string& desc);
	bool Read( ifstream& infile);
	static void Read( ifstream& infile, bool& AM, float& freq, string& desc);
	
protected:
	Band m_Band;
	float m_Frequency;
	string m_Description;
	
};

/*class FinnySettings
{
public:
	FinnySettings();
	~FinnySettings();
	
protected:
	Preset m_LastFreq;
	bool m_bReadLastAsDefault;
	
	list< Preset* > m_Presets;
	
};*/

#endif // __FINNYSETTINGS_H__
