#pragma once
#include "Classes.h"

/// ����� �������
class Swordsman : public Classe_warrior
{
	int _zeal;
	int _forcecost[4] = { 1,3,3,10 };
public:
	string nameSkill[4] = { "���� �����", "������������� ����", "�������", "�������� ����" };
	void shield_strike(Units* unit, Map* field, Adapter *adapter);
	void showSkills(Adapter *adapter) override;
	void selectSkill(int ch, Map* field, Units **link, Adapter *adapter, bool sLine = false) override;
	void swepping_blow(Units* unit, Map* field, Adapter *adapter);
	void furious_strike(Units* unit, Map* field, Adapter *adapter);
	Swordsman(int &x, int &y);
	~Swordsman();
};
/// ����� ������
class Spear : public Classe_warrior
{
	int _rage;
	int _forcecost[4] = { 1,4,8,5 };
public:
	string nameSkill[4] = { "���� ������", "�����", "�������", "������ ����" };
	void spear_strike(Units* unit, Map* field, Adapter *adapter);
	void showSkills(Adapter *adapter) override;
	void selectSkill(int ch, Map* field, Units **link, Adapter *adapter, bool sLine = false) override;
	void roll_forward(Units* unit, Map* field, Adapter *adapter);
	void exact_blow(Units* unit, Map* field, Adapter *adapter);
	Spear(int &x, int &y);
	~Spear();
};


