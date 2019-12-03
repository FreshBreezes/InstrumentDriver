// InstrmentControl.cpp : ���� DLL Ӧ�ó���ĵ���������
//
#include "stdafx.h"
#include  <iostream>
#include "InstrumentControl.h"
#include <stdlib.h>
#include "Agilent_856x.h"
#include "Agilent_E4400.h"
#include "RS_NRT.h"
#include "Aglient_8920.h"

using namespace std;

InstrumentControl instrumentControl;
 

InstrumentControl::InstrumentControl()
{
 
}

InstrumentControl::~InstrumentControl()
{
	 
}

/*************************************************
Function: yhFindRsrc
Description: Ѱ��Visa��Դ
Input: str ƥ��������ʽ
Output: descriptor �����ʶ�豸λ�õ��ַ�����
Return: 
*************************************************/
ViStatus InstrumentControl::FindRsrc(ViConstString str, ViChar* descriptor)
{
	ViStatus status = viOpenDefaultRM(&defaultRM);//ViSession,OUT Ĭ����Դ�������Ự��Ψһ�߼���ʶ����
	if (status < VI_SUCCESS)
	{
		errorInfo =  "�޷���VISA��Դ�������򿪻Ự��\n";
		return status;
	}
	  /*Interface         Expression
		--------------------------------------
		GPIB              "GPIB[0-9]*::?*INSTR"
		VXI               "VXI?*INSTR"
		GPIB - VXI        "GPIB-VXI?*INSTR"
		Any VXI           "?*VXI[0-9]*::?*INSTR"
		Serial            "ASRL[0-9]*::?*INSTR"
		PXI               "PXI?*INSTR"
		All instruments   "?*INSTR"
		All resources     "?*"
		* /*/
	//(ViSession sesn, ViConstString expr, ViPFindList vi,ViPUInt32 retCnt, ViChar _VI_FAR desc[]);
	 status = viFindRsrc(defaultRM,  //ViSession,IN ��Դ�������Ự(Ӧ�����Ǵ�viOpenDefaultRM()���صĻỰ
						 str,        //ViConstString,IN ����һ��������ʽ���������һ����ѡ���߼����ʽ���鿴����ע�͡�
						 &findList,  //ViPFindList,OUT ���ر�ʶ�������Ự�ľ����������������viFindNext()�е�����  
						 &numInstrs, //ViPUInt32,OUT ƥ�������
						 descriptor  //ViChar,OUT ���ر�ʶ�豸λ�õ��ַ�����Ȼ����Խ��ַ������ݸ�viOpen()���Խ����������豸�ĻỰ
						 );
	 if (status < VI_SUCCESS)
		 errorInfo = "Ѱ����Դ��������\n";
	 
	 status = viFindNext(findList, descriptor);


	 return status;
}

//��ָ��ָ����Դ�ĻỰ
ViStatus InstrumentControl::Open(ViChar*  descriptor)
{
	ViStatus status = viOpen(defaultRM,  //ViSession,IN ��Դ�������Ự(Ӧ�����Ǵ�viOpenDefaultRM()���صĻỰ
					descriptor, //ViConstRsrc,IN ��Դ��Ψһ������������TCPIP0::ftp.ni.com::21::SOCKET��VXI0::0::INSTR��GPIB0::14::INSTR
					VI_NULL,    //ViAccessMode,IN ָ��������Դ��ģʽ���й���Чֵ�������˵�����֡��������ֵ��VI_NULL����Ựʹ��visa�ṩ��Ĭ��ֵ��
					VI_NULL,    //ViUInt32,IN ָ���˲����ڷ��ش���֮ǰ�ȴ������ʱ���(�Ժ���Ϊ��λ)���Ⲣû������I/O��ʱ��Ϊ�ˣ�������ʹ������VI_ATTR_TMO_VALUE����viSetAttribute()��
		     		 &instr     //ViPSession,OUT ���ûỰ��Ψһ�߼���ʶ��
	                 );
	if (status < VI_SUCCESS)
	{
		errorInfo = "����Դ��������\n" ;
		Close(defaultRM);
	}
	return status;
}

//�����豸
ViStatus InstrumentControl::Clear(ViSession vi)
{
	ViStatus status = viClear(vi);  //ViSession �Ự��Ψһ�߼���ʶ��
	if (status < VI_SUCCESS)
	{
		errorInfo = "�����豸��Դ����\n";
	}
	return status;
}


//�ر���Դ
ViStatus InstrumentControl::Close(ViObject  vi)
{
	ViStatus status = viClose(vi); //ViSession �Ự��Ψһ�߼���ʶ��
	if (status < VI_SUCCESS)
	{
		errorInfo = "�ر���Դ����\n";
	}
	return status;
}

//��������
ViStatus InstrumentControl::SetAttribute(ViObject vi, ViAttr attribute, ViAttrState attrState)
{
	ViStatus status = viSetAttribute( vi,        //IN �Ự��Ψһ�߼���ʶ����
							attribute,  //IN Ҫ�޸���״̬�����ԡ�
							attrState   //IN Ϊָ���������õ����Ե�״̬����������ֵ�Ľ����ɶ����塣
						   );
	if (status < VI_SUCCESS)
	{
		errorInfo = "���������������\n";
	}
	return status;
}


//��ȡ����
ViStatus InstrumentControl::Read(ViSession vi, ViPBuf buf, ViUInt32 count, ViPUInt32 retCount)
{
	ViStatus status = viRead(vi,      //ViSession IN �Ự��Ψһ�߼���ʶ��
					buf,     //ViBuf OUT Ҫ���͵��豸�����ݿ��λ��
					count,   //ViUInt32 IN Ҫ��ȡ���ֽ���
					retCount //ViPUInt32 OUT ʵ�ʴ�����ֽ���
					);
	if (status < VI_SUCCESS)
	{
		errorInfo = "��ȡ�������\n";
	}
	return status;
}

//���ò���
ViStatus InstrumentControl::Write(ViSession vi, ViBuf buf, ViUInt32 count, ViPUInt32 retCount)
{
	ViStatus	status = viWrite(vi,      //ViSession IN �Ự��Ψһ�߼���ʶ��
					 buf,     //ViBuf IN Ҫ���͵��豸�����ݿ��λ��
					 count,   // ViUInt32 IN Ҫд����ֽ���
					 retCount //ViPUInt32 OUT ʵ�ʴ�����ֽ���
				   );
	if (status < VI_SUCCESS)
	{
		errorInfo = "д���������\n";
	}
	return status;
}

 


//��ȡ���һ��������Ϣ
char* InstrumentControl::GetCurrentError()
{
	if (errorInfo != NULL)
		return errorInfo;
	else
		return "û�д�����Ϣ\n";

} 


ISpectropgraph* InstrumentControl::GetInstance(SpectrographType spectrographType)
{
	switch (spectrographType)
	{
	case _Agilent_856x:
		return  new Agilent_856x();
		break;
	case _Agilent_ESA_E:
		break;
	case _Agilent_E4407B:
		break;
	case _RS_FSU:
		break;
	case _RS_FSW:
		break;
	default:
		break;
	}
	return new Agilent_856x();
}

ISignalSource*  InstrumentControl::GetInstance(SignalSourceType signalSourceType)
{
	switch (signalSourceType)
	{
	case _Agilent_E4400:
		return new Agilent_E4400();
	case _HP_8360:
		break;
	case _RS_SMHU:
		break;
	case _RS_SMA100A:
		break;
	case _RS_SMBV100A:
		break;
	default:
		break;
	}
	return new Agilent_E4400();
}

 

IPowerMeter* InstrumentControl::GetInstance( PowerMeterType powerMeterType)
{
	switch (powerMeterType)
	{
	case _RS_NRT:
		return new RS_NRT();
	default:
		break;
	}
	return new RS_NRT();
}

ISynthesizeMeter* InstrumentControl::GetInstance(SynthesizeMeterType synthesizeMeterType)
{
	switch (synthesizeMeterType)
	{
	case _Aglient_8920:
		return new Aglient_8920();
	case _Ceyear_AV4957:
		break;
	default:
		break;
	}
	return new Aglient_8920();
}

bool InstrumentBaseCommand::OpenInstrument(char * address)
{
	ViStatus  status = instrumentControl.Open(address);
	if(status<VI_SUCCESS)
	    return false;
	else
		return true;
}

bool InstrumentBaseCommand::CloseInstrument()
{
	ViStatus  status = instrumentControl.Close(instr);
	if (status<VI_SUCCESS)
		return false;
	else
		return true;
}


bool InstrumentBaseCommand::WriteString(char * command)
{ 
	static ViUInt32 retCount;
	ViStatus status = instrumentControl.Write(instr,(ViBuf)command, (ViUInt32)strlen(command),&retCount);
	if (status<VI_SUCCESS)
		return false;
	else
		return true;
}
bool InstrumentBaseCommand::ReadString(char * outData)
{
	static ViUInt32 retCount;
	 ViStatus status = instrumentControl.Read(instr, (ViBuf)outData, 100, &retCount);
	if (status<VI_SUCCESS)
		return false;
	else
		return true;
}
bool InstrumentBaseCommand::WriteAndReadString(char* command, char* retValue)
{
	bool res = WriteString(command);
	res = ReadString(retValue);
	return res;
}

