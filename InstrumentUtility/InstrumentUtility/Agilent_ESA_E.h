#pragma once
#include "InstrumentUtility.h"

class Agilent_ESA_E : public ISpectropgraph
{
public:
	Agilent_ESA_E();
	~Agilent_ESA_E();
	//��ȡ�豸ID��
	//virtual  char* GetID();
	////��ʼ���Ǳ����
	//virtual bool Reset();
	////��ȡ����Ƶ��  
	//virtual double GetCenterFreq();
	////��ȡMKA  ��ֵ��ƽ
	//virtual double GetMKA();
	////��������Ƶ��  
	//virtual bool SetCenterFreq(FrequencyUnit unit, double value);
	////����RBW  
	//virtual bool SetRBW(bool isAuto, double value = 0);
	////���òο���ƽ
	//virtual bool SetRefLevel(double value);
	////�����ǲ�������ֵ  
	//virtual bool MarkPeak();
	////����˥��
	//virtual bool SetAttenuation(bool isAuto, double value);
	////����SPAN
	//virtual bool SetSpan(double value, FrequencyUnit unit);
};

