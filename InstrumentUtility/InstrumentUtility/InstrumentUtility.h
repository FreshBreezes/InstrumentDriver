#pragma once
#include "stdafx.h"
#include "visa.h"
#include <stdio.h>


#ifdef InstrumentUtility_EXPORTS
#define InstrumentUtility_API __declspec(dllimport)   //���뵼������д���ᱨdll���Ӵ���
#else 
#define InstrumentUtility_API __declspec(dllexport)
#endif // InstrumentManager_EXPORTS


enum SpectrographType
{
	_Agilent_856x,
	_Agilent_ESA_E,
	_Agilent_E4407B,
	_RS_FSU,
	_RS_FSW
};


enum SignalSourceType
{
	_Agilent_E4400,
	_HP_8360,
	_RS_SMHU,
	_RS_SMA100A,
	_RS_SMBV100A
};


enum PowerMeterType
{
	_RS_NRT
};


enum SynthesizeMeterType
{
	_Aglient_8920,
	_Ceyear_AV4957
};

enum FrequencyUnit
{
	Hz,
	KHz,
	MHz,
	GHz
};

enum PowerUnit
{
	DBM,
	W
};

class InstrumentBaseCommand
{
public:
	//�����Ǳ�
	virtual bool OpenInstrument(char* address);
	//�Ͽ�����
	virtual bool CloseInstrument();
	//д����
	virtual bool WriteString(char* command);
	//������
	virtual bool ReadString(char* command);
	//д��������
	virtual bool WriteAndReadString(char* command, char* retValue);
 
};


//Ƶ���ǽӿ���
class ISpectropgraph :public InstrumentBaseCommand
{
public:
	//��ȡ�豸ID��
	virtual  char* GetID() = 0;
	//��ʼ���Ǳ����
	virtual bool Reset() = 0;
	//��ȡ����Ƶ��  
	virtual double GetCenterFreq() = 0;
	//��ȡMKA  ��ֵ��ƽ
	virtual double GetMKA()=0;
	//��������Ƶ��  
	virtual bool SetCenterFreq(FrequencyUnit unit, double value) = 0;
	//����RBW  
	virtual bool SetRBW(bool isAuto, double value = 0) = 0;
	//���òο���ƽ
	virtual bool SetRefLevel(double value) = 0;
	//�����ǲ�������ֵ  
	virtual bool MarkPeak() = 0;
	//����˥��
	virtual bool SetAttenuation(bool isAuto, double value) = 0;
	//����SPAN
	virtual bool SetSpan(double value, FrequencyUnit unit) = 0;
};


class ISignalSource :public InstrumentBaseCommand
{
public:
	//��ȡ�豸ID��
	virtual char* GetID() = 0;
	//��ʼ���Ǳ����
	virtual bool Reset() = 0;
	//�ź�Դ���俪��
	virtual bool SetSignalSourceState(bool state) = 0;
	// ����Ƶ�ʡ�����
	virtual bool SetFreqAndLevel(FrequencyUnit unit, double freq, double level) = 0;
	//����Ƶ��
	virtual bool SetFreq(FrequencyUnit unit, double freq) = 0;
	//���ù���
	virtual bool SetLevel(double level) = 0;
	//�����忪��
	virtual bool SetPulse(bool onOff) = 0;
	//�����������
	virtual bool SetPulseWidth(double width) = 0;
	//������������
	virtual bool SetPulsePeriod(double period) = 0;
};

class IPowerMeter :public InstrumentBaseCommand
{
public:
	//��ȡ�豸ID��
	virtual char* GetID() = 0;
	//��ʼ���Ǳ����
	virtual bool Reset() = 0;
	//��λ�л�
	virtual bool PowerUnitChange(PowerUnit unit) = 0;
	//��ȡ���ʼ�DATA ����AVG��פ����SWR ���ʼ� 
	virtual bool GetPower(int sensorNum, double* avg,   double* swr) = 0;
};

class ISynthesizeMeter:public InstrumentBaseCommand
{
public:
	//��ȡ�豸ID��
	virtual char* GetID() = 0;
	//��ʼ���Ǳ����
	virtual bool Reset() = 0;
	//��������Ƶ��  
	virtual bool SetCenterFreq(FrequencyUnit unit, double value) = 0;
	//���òο���ƽ  ���ȱ��  
	virtual bool SetRefLevel(double value) = 0;
	//��ȡ����Ƶ��
	virtual double GetCenterFreq() = 0;
	//���ý������
	virtual bool SetAfgState(bool onOff) = 0;

};




class InstrumentUtility_API InstrumentUtility
{
public:
	InstrumentUtility();
	~InstrumentUtility();

	//TODO:�ڴ˴���д���ķ���

	char* GetCurrentError();
    ViStatus FindRsrc(ViConstString str, ViChar* descriptor);
	ViStatus Open(ViChar*  descriptor);
	ViStatus Close(ViObject  vi);
	ViStatus Clear(ViSession vi);
	ViStatus SetAttribute(ViObject vi, ViAttr attribute, ViAttrState attrState);
	ViStatus Read(ViSession vi, ViPBuf buf, ViUInt32 count, ViPUInt32 retCount);
	ViStatus Write(ViSession vi, ViBuf buf, ViUInt32 count, ViPUInt32 retCount);
	//ViStatus yhReadAsync();
	//ViStatus yhWriteAsync();

	ISpectropgraph*  GetInstance(SpectrographType spectrographType);
	ISignalSource*  GetInstance(SignalSourceType signalSourceType);
	IPowerMeter*  GetInstance(PowerMeterType powerMeterType);
	ISynthesizeMeter*  GetInstance(SynthesizeMeterType synthesizeMeterType);
	
private:
	  char instrDescriptor[VI_FIND_BUFLEN];
	  ViUInt32 numInstrs;
	  ViFindList findList;
	  ViSession defaultRM;
	  char* errorInfo ;
};
 

static	ViSession instr;