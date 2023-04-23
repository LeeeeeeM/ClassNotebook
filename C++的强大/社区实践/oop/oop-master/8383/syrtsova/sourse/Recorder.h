#pragma once
#include <string>
#include <iostream>
#include <fstream>

/// ����� ������

/**
* ������������ �����, �������� ������� ������ � �������� � � ����
*/

class Recorder
{
public:
	/// ����� ������
	std::ofstream out;
	/// ����������� ������ ������
	Recorder();
	/// ���������� ������ ������ 
	~Recorder();
	/// ������������� �������� ������ � �����
	friend std::ostream& operator << (std::ostream& out, std::string str);
	/// ������� ������ � ����
	bool writeToFile(std::string str);
	/// ������� ������ � ��������
	bool writeToTerminal(std::string str);
};