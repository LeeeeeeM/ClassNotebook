#pragma once
#include <vector>
#include "GameRules.h"
#include "User.h"
// ����� ��������� 4 ���������: 1 - ������ �������, 2 - ��������� �� �����, 3 - ���, 4 - ���, 5 - ���. ��������
template <std::vector<User*>* users, Board* board, int turnChangeType, int endCriteriaType, std::vector<int>* boardInitArgs>
class GameRulesCustom : public GameRules
{
public:
	GameRulesCustom();
	int changeTurn() override; // ���������. � �������� ����. �-���
	int checkForEnd() override;
	void initBoard() override;
protected:
	int currentTurn = 0; // �������� ��� ������ � ����������
};

