#pragma once
#include "Recorder.h"

#include "iostream"


/// ������

/**
* ������������� � ������� �������� "������" ��� ������������ ����� ������ ������������ (� ����, � ��������, ��� �����������).
*/

class Proxy
{
public:
	/// ������ ������
	Recorder* write;
	/// ��������� ������ � ����
	bool logToFile;
	/// ��������� ������ � ��������
	bool logToTerminal;
	/// ��������� ��������� ������
	bool withoutLog;
	/// ����������� Proxy
	Proxy(Recorder* write, bool logToFile, bool logToTerminal, bool withoutLog);
	/// �������� ������������ ������ ������
	bool specificRequest(std::string str);
};