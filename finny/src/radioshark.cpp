#include "radioshark.h"

AbstractRadiosharkInterface::AbstractRadiosharkInterface()
:m_FMFreq(99.5f)
,m_AMFreq(630.0f)
,m_pHid(NULL)
,m_Band(Radioshark::FM)
{
	
}

AbstractRadiosharkInterface::~AbstractRadiosharkInterface()
{
	
}

bool AbstractRadiosharkInterface::Open(void)
{
	hid_return ret =  HID_RET_SUCCESS;
	
	if(m_pHid)
	{
		return false;//already opened.
	}

	//Initialize the hid library
	ret = hid_init();
	if (ret != HID_RET_SUCCESS) {
		return false;
	}

	//Initialize the hid object
	m_pHid = hid_new_HIDInterface();
	if ( !m_pHid ) {
		return false;
	}

	//Open the shark
	ret = hid_force_open(m_pHid, 2, &matcher, 3);
	if (ret != HID_RET_SUCCESS) {
		return false;
	}
	return true;
}
void AbstractRadiosharkInterface::Close(void)
{
	hid_return ret = HID_RET_SUCCESS;
	
	if( !m_pHid)
	{
		return;
	}

	//close
	ret = hid_close(m_pHid);
	if (ret != HID_RET_SUCCESS) {
		return;
	}

	//delete the hid
	hid_delete_HIDInterface(&m_pHid);

	/* Clean up the hid library */
	ret = hid_cleanup();
	if (ret != HID_RET_SUCCESS)
	{
		return;
	}
}

float AbstractRadiosharkInterface::GetFMFreq(void)
{
	return m_FMFreq;
}
float AbstractRadiosharkInterface::GetAMFreq(void)
{
	return m_AMFreq;
}
Radioshark::Band  AbstractRadiosharkInterface::GetBand(void)
{
	return m_Band;
}

Radioshark2Interface::Radioshark2Interface()
	:AbstractRadiosharkInterface()
{
	
}
Radioshark2Interface::~Radioshark2Interface()
{
	
}

void Radioshark2Interface::SetAM(void)
{
	if(!m_pHid)
	{
		return;
	}
	m_Band = Radioshark::AM;
	
	unsigned char PACKET[SEND_PACKET_LENGTH] = { 0xc1, 0x02, 0x00, 0x04, 0x00, 0x00, 0x00 };
	PACKET[0] = 0x81;
	unsigned short encodedFreq  = ((unsigned short)m_AMFreq * 4 ) + 16300;
	PACKET[1] = (encodedFreq >> 8) & 0xFF;
	PACKET[2] = encodedFreq & 0xFF;
	PACKET[3] = 0xF3;
	PACKET[4] = 0x36;
	PACKET[5] = 0x00;
	PACKET[6] = 0x24;
	
	hid_return ret = hid_interrupt_write(m_pHid, WRITE_EP, (char*)PACKET, 
									SEND_PACKET_LENGTH, 10000);
}
void Radioshark2Interface:: SetFM(void)
{
	if(!m_pHid)
	{
		return;
	}
	
	m_Band = Radioshark::FM;
	
	unsigned char PACKET[SEND_PACKET_LENGTH] = { 0xc1, 0x02, 0x00, 0x04, 0x00, 0x00, 0x00 };
 	PACKET[0] = 0x81;
	unsigned short encodedFreq  = ((m_FMFreq * 10 * 2) - 3 );
	PACKET[1] = (encodedFreq >> 8) & 0xff;
	PACKET[2] = encodedFreq & 0xff;
	PACKET[3] = 0x33;
	PACKET[4] = 0x04;
	PACKET[5] = 0x00;
	PACKET[6] = 0x28;
	
	hid_return ret = hid_interrupt_write( m_pHid , WRITE_EP, (char*)PACKET,
											SEND_PACKET_LENGTH, 10000);
}

void Radioshark2Interface::SetFMFreq(float freq )
{
	m_FMFreq = freq;
	
	//TODO: check freq bounds
	
	this->SetFM(); 
}
void Radioshark2Interface::SetAMFreq(float freq )
{
	m_AMFreq = freq;
	
	//TODO: check freq bounds
	
	this->SetAM();
}

void Radioshark2Interface::FMFreqUp( float step/* = 0.1f*/) 
{
	m_FMFreq+=step;
	if(m_FMFreq > 108.0f )
	{
		m_FMFreq = 87.5f;
	}
	this->SetFM();
}
void Radioshark2Interface::FMFreqDown( float step /*= 0.1f*/)
{
	m_FMFreq-=step;
	if(m_FMFreq < 87.5f )
	{
		m_FMFreq = 108.0f;
	}
	this->SetFM();
}
	
void Radioshark2Interface::AMFreqUp( float step /*= 1.0f*/ )
{
	m_AMFreq+=step;
	if(m_AMFreq > 1610.0f)
	{
		m_AMFreq = 520.0f;
	}
	this->SetAM();
}
void Radioshark2Interface::AMFreqDown( float step /*= 1.0f*/ )
{
	m_AMFreq-=step;
	if(m_AMFreq < 520.0f)
	{
		m_AMFreq = 1610.0f;
	}
	this->SetAM();
}

void Radioshark2Interface::SetRedLED( bool on )
{
	
}
void Radioshark2Interface::SetBlueLED( float zero_to_one )
{
	
}
