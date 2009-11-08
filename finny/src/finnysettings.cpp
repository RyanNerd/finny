#include "finnysettings.h"

void GetToken(string& input,string& token)
{
	token = input.substr(0,input.find_first_of(' '));
	input = input.substr(input.find_first_of(' ')+1);
}

Preset::Preset()
	:m_Band(Preset::AM)
	,m_Frequency(0.0)
	,m_Description("NULL")
{
	
}
Preset::Preset(bool am, float f)
	:m_Frequency(f)
	,m_Description("NULL")
{
	if( am )
	{
		m_Band = Preset::AM;
	}else{
		m_Band = Preset::FM;
	}
}
Preset::~Preset()
{
	
}

Preset::Band Preset::GetBand()
{
	return m_Band;
}
float Preset::GetFreq()
{
	return m_Frequency;
}
string& Preset::GetDescription()
{
	return m_Description;
}
void Preset::SetDescription( string& desc)
{
	m_Description = desc;
}

void Preset::Write( ofstream& outfile)
{
	string bnd;
	if(m_Band == Preset::AM)
	{
		bnd = "AM";
	}else{
		bnd = "FM";
	}
	outfile<<"PRESET: "<<bnd<<" "<<m_Frequency<<" "<<m_Description<<endl;
}
void Preset::Write( ofstream& outfile, bool AM, float freq, string& desc)
{
	string bnd;
	if(AM)
	{
		bnd = "AM";
	}else{
		bnd = "FM";
	}
	outfile<<"PRESET: "<<bnd<<" "<<freq<<" "<< desc <<endl;
}
bool Preset::Read( ifstream& infile)
{
	string bnd;
	infile>>bnd;
	if(bnd == "AM")
	{
		m_Band = Preset::AM;
	}else{
		m_Band = Preset::FM;
	}
	infile>>m_Frequency;
	getline(infile,m_Description);
	//Let's strip any leading spaces
	m_Description = m_Description.substr(m_Description.find_first_not_of(' '));
	return true;
}
void Preset::Read( ifstream& infile, bool& AM, float& freq, string& desc)
{
	string bnd;
	infile>>bnd;
	if(bnd == "AM")
	{
		AM = true;
	}else{
		AM = false;
	}
	infile>>freq;
	getline(infile, desc);
	desc = desc.substr(desc.find_first_not_of(' '));
}
