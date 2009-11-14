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
void Preset::SetBand( Preset::Band bnd)
{
	m_Band = bnd;
}
void Preset::SetFreq(float freq)
{
	this->m_Frequency = freq;
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
	outfile<<bnd<<" "<<m_Frequency<<" "<<m_Description<<endl;
}
void Preset::WritePreset( ofstream& outfile)
{
	outfile<<"PRESET: ";
	this->Write(outfile);
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
void FinnySettings::LoadSetting( FinnySettings& settings, ifstream& infile)
{
	//We've already hit a "SETTING:" tag in the filestream,
	//so now we just parse the rest of the line.
	//It will be of the form "key" and the rest.
	string key;
	infile>>key;
	
	if(key == "StartFreq")
	{
		settings.StartFreq.Read(infile);
	}else if( key == "UpdateStartFreqOnClose")
	{
		FinnySettings::ReadBool(infile,settings.UpdateStartFreqOnClose);
	}else if( key == "StartVolume")
	{
		FinnySettings::ReadFloat(infile,settings.StartVolume);
	}else if(key == "UpdateStartVolumeOnClose")
	{
		FinnySettings::ReadBool(infile,settings.UpdateStartVolumeOnClose);
	}else if(key ==  "RecordingPath")
	{
		getline(infile,settings.RecordingPath);
		settings.RecordingPath = settings.RecordingPath.substr(
						settings.RecordingPath.find_first_not_of(' '));
	}else if( key == "MP3")
	{
		settings.MP3.Read(infile);
	}else if (key == "AutogenerateRecordingNames:")
	{
		FinnySettings::ReadBool(infile,settings.AutogenerateRecordingNames);
	}
}
void FinnySettings::WriteSettings( FinnySettings& settings, ofstream& outfile)
{
	outfile<<"SETTING: StartFreq ";
	settings.StartFreq.Write(outfile);
	outfile<<"SETTING: UpdateStartFreqOnClose ";
	FinnySettings::WriteBool(outfile,settings.UpdateStartFreqOnClose);
	outfile<<"SETTING: StartVolume ";
	FinnySettings::WriteFloat(outfile,settings.StartVolume);
	outfile<<"SETTING: UpdateStartVolumeOnClose ";
	FinnySettings::WriteBool(outfile,settings.UpdateStartVolumeOnClose);
	outfile<<"SETTING: RecordingPath ";
	outfile<<settings.RecordingPath<<endl;
	settings.MP3.Write(outfile);
	outfile<<"SETTING: AutogenerateRecordingNames ";
	FinnySettings::WriteBool(outfile,settings.AutogenerateRecordingNames);
}
void FinnySettings::ReadBool(ifstream& infile, bool& value)
{
	string val;
	infile >> val;
	if( val == "TRUE" || val == "True" || val == "true")
	{
		value = true;
	}else{
		value = false;
	}
}
void FinnySettings::WriteBool(ofstream& outfile, bool value)
{
	if(value == true)
	{
		outfile<<" TRUE"<<endl;
	}else{
		outfile<<" FALSE"<<endl;
	}
}
void FinnySettings::ReadFloat(ifstream& infile, float& value)
{
	infile>>value;
}
void FinnySettings::WriteFloat(ofstream& outfile, float value)
{
	outfile<<value<<endl;
}
