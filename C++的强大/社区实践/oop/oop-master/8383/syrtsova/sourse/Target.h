#pragma once
#include <string>

/// ����

/**
* ������� �����, ��������� ���������, � ������� ����� �������� ��������� ���
*/
 
class Target
{
public:
	virtual ~Target() = default;
	virtual bool request(std::string str){
		return true;
	}
};
