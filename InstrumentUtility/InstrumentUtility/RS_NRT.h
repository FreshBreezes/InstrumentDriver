#pragma once
#include "InstrumentControl.h"

class RS_NRT : public IPowerMeter
{
public:
	RS_NRT();
	~RS_NRT();
	//��ȡ�豸ID��
	virtual char* GetID() ;
	//��ʼ���Ǳ����
	virtual bool Reset() ;
	//��λ�л�
	virtual bool PowerUnitChange(PowerUnit unit) ;
	//��ȡ���ʼ�DATA ����AVG��פ����SWR ���ʼ� 
	virtual bool GetPower(int sensorNum, double* avg, double* swr) ;

};

