#pragma once
#include "Board.h"
class GameRules	//����
{
public:
	virtual int changeTurn() = 0;	//������� ���
	virtual int checkForEnd() = 0;	//�������� �� �������� ��� �������
	virtual void initBoard() = 0;	//����. �����
protected:
	GameRules();
};
//std::vector<User> ���. ��� ��������
