// Sample.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "visa.h"
#include <stdlib.h>
#include  <iostream>
#include "InstrumentControl.h"

//#pragma comment(lib,"InstrumentControl.lib")
using namespace std;
char* err;

int main()
{
	//char instrDescriptor[VI_FIND_BUFLEN];
	InstrumentControl instrumentControl;
	ISpectropgraph* spectropgraph = instrumentControl.GetInstance(SpectrographType::_Agilent_856x);
	bool res = spectropgraph->OpenInstrument("GPIB0::14:INSTR");
	if (res)
		cout << "���Ǳ�ɹ�!" + SpectrographType::_Agilent_856x << endl;
	else
	{
		cout << "���Ǳ�ʧ��!" << endl;
		system("pause");
		//return -1;
	}
	cout << "��ȡID..." << endl;
	char* id = spectropgraph->GetID();
	if(id!= nullptr)
     	cout << id << endl;
	else
		cout << "��ȡIDʧ�ܣ�" << endl;
	cout << "���òο���ƽ��-10dBm!" << endl;
	 res = spectropgraph->SetRefLevel(-10);
	if (!res)
		cout << "����ʧ��" << endl;
	spectropgraph->CloseInstrument();
	/*SignalSourceType signalSourceType  = SignalSourceType::_HP_8360;
	ISignalSource* signalSource = instrumentControl.GetInstance(signalSourceType);
	err = instrumentControl.GetCurrentError();
	cout << err;
	bool res = false;
	res = signalSource->WriteString("IDN?");
    res = signalSource->OpenInstrument("GPIB0::14:INSTR");
    signalSource->CloseInstrument();
 
	ViStatus  status = instrumentControl.FindRsrc("?*", instrDescriptor);
	if (status < 0)
	{
		err = instrumentControl.GetCurrentError();
		cout<<err;
	}
	status = instrumentControl.Open(instrDescriptor);
	if (status < 0)
	{
		err = instrumentControl.GetCurrentError();
		cout << err;
	}*/
	system("pause");
	return 0;
}

