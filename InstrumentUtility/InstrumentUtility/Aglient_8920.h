#pragma once
#include "InstrumentUtility.h"

class Aglient_8920 : public ISynthesizeMeter
{
public:
	Aglient_8920();
	~Aglient_8920();
	//��ȡ�豸ID��
	virtual char* GetID() ;
	//��ʼ���Ǳ����
	virtual bool Reset() ;
	//��������Ƶ��  
	virtual bool SetCenterFreq(FrequencyUnit unit, double value) ;
	//���òο���ƽ  ���ȱ��  
	virtual bool SetRefLevel(double value);
	//��ȡ����Ƶ��
	virtual double GetCenterFreq();
	//���ý������
	virtual bool SetAfgState(bool onOff) ;
};

