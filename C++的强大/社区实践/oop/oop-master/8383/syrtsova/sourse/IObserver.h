#pragma once
#include <string>

/// ��������� ��������
class IObserver   
{
public:
	virtual ~IObserver();
	virtual void update(std::string message) = 0;
};