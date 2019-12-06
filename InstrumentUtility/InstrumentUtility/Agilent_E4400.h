#pragma once

#include "InstrumentUtility.h"


class Agilent_E4400 : public ISignalSource
{

public:
	Agilent_E4400();
	~Agilent_E4400();
	//��ȡ�豸ID��
	virtual char* GetID() ;
	//��ʼ���Ǳ����
	virtual bool Reset() ;
	//�ź�Դ���俪��
	virtual bool SetSignalSourceState(bool state) ;
	// ����Ƶ�ʡ�����
	virtual bool SetFreqAndLevel(FrequencyUnit unit, double freq, double level);
	//����Ƶ��
	virtual bool SetFreq(FrequencyUnit unit, double freq);
	//���ù���
	virtual bool SetLevel(double level) ;
	//�����忪��
	virtual bool SetPulse(bool onOff);
	//�����������
	virtual bool SetPulseWidth(double width);
	//������������
	virtual bool SetPulsePeriod(double period);



};