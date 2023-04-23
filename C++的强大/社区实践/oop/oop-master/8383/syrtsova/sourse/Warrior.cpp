#include "pch.h"
#include "Warrior.h"
#include "Classes.h"


void Swordsman::selectSkill(int ch, Map* field, Units **link, Adapter *adapter, bool sLine)
{
	switch (ch)
	{
	case 1:
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			shield_strike(this->getLink(link), field, adapter);
		}
		else
		{
			cout << endl << "�� ��������� ������ ��� ������!" << endl << "������ ��� �������� ����!";
			force -= 1;
		}
	} break;
	case 2:
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			swepping_blow(this->getLink(link), field,adapter);
		}
		else
		{
			cout << endl << "�� ��������� ������ ��� ������!" << endl << "������ ��� �������� ����!";
			force -= 1;
		}
	} break;
	case 3: skill_berserk(field,adapter);
		break;
	case 4: 
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			furious_strike(this->getLink(link), field,adapter);
		}
		else
		{
			cout << endl << "�� ��������� ������ ��� ������!" << endl << "������ ��� �������� ����!";
			force -= 1;
		}
	} break;
	}
	if (force <= 0)
	{
		cout << endl << "���� �������";
		force = 0;
	}	
}

void Swordsman::showSkills(Adapter *adapter) {
	cout << endl << "���������� ����: "       << force    << "��������: "           << _zeal
		 << endl << "1: <���� �����>"         << "\t\t"   << "������� ����: "       << _forcecost[0]
		 << endl << "2: <������������� ����>" << "\t\t"   << "������� ����: "       << _forcecost[1]
		 << endl << "3: <�������>"            << "\t\t\t" << "������� ����: "       << _forcecost[3]
		 << endl << "4: <�������� ����>"      << "\t\t"   << "��������� ��������: " << _forcecost[2];
	adapter->request("������ ����������� � ��������� ������������");
}

Swordsman::Swordsman(int &x, int &y) : Classe_warrior('F', 50, 8, 10)
{
	XY.x = x;
	XY.y = y;
	_zeal = 10;
	spr.setAtrib(_zeal);
	for (int i = 0; i < 4; i++)
	{
		nameSkills[i] = nameSkill[i];
	}
}
void Swordsman::furious_strike(Units* unit, Map* field, Adapter *adapter)
{
	if (_zeal >= _forcecost[2])
	{
		cout << endl << "������ ��������� �������� ����! ��������� ������ ����� �����.";
		adapter->request("������ ��������� �������� ����");
		unit->health.change(-8);
		unit->reaction(field, adapter);
		force -= 3;
		_zeal -= _forcecost[2];
	}
	else
	{
		cout << endl << "������������ ���������!";
		adapter->request("������ �������� �����������, ������������ ��������");
	}
}
void Swordsman::shield_strike(Units* unit, Map* field, Adapter *adapter)
{
	if (force >= _forcecost[0])
	{
		cout << endl << "������ ��������� ���� �����!";
		adapter->request("������ ��������� ���� �����");
		unit->health.change(-3);
		unit->reaction(field, adapter);
		force -= _forcecost[0];
		_zeal += 1;
	}
	else
	{
		cout << endl << "������������ ����!";
		adapter->request("������ �������� �����������, ������������ ����");
	}
}

void Swordsman::swepping_blow(Units* unit, Map* field, Adapter *adapter)
{
	if (force >= _forcecost[1])
	{
		cout << endl << "������ ������� ������������� ����! ��������� �� �������� ���������� � �������� ����.";
		adapter->request("������ ������� ������������� ����");
		unit->health.change(-5);
		unit->reaction(field, adapter);
		force -= _forcecost[1];
		_zeal += 2;
	}
	else
	{
		cout << endl << "������������ ����!";
		adapter->request("������ �������� �����������, ������������ ����");
	}
}

Swordsman::~Swordsman()
{
	cout << endl << "������ ��� ���������!";
}


Spear::Spear(int &x, int &y) : Classe_warrior('G', 40, 10, 8)
{
	XY.x = x;
	XY.y = y;
	_rage = 10;
	spr.setAtrib(_rage);
	for (int i = 0; i < 4; i++)
	{
		nameSkills[i] = nameSkill[i];
	}
}



void Spear::selectSkill(int ch, Map* field, Units **link, Adapter *adapter, bool sLine)
{
	switch (ch)
	{
	case 1:
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			exact_blow(this->getLink(link), field, adapter);
		}
		else
		{
			cout << endl << "�� ��������� ������ ��� ������!" << endl << "������ ��� �������� ����!";
			force -= 1;
		}
	} break;
	case 2:
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			roll_forward(this->getLink(link), field, adapter);
		}
		else
		{
			cout << endl << "�� ��������� ������ ��� ������!" << endl << "������ ��� �������� ����!";
			force -= 1;
		}
	} break;
	case 3: skill_berserk(field, adapter);
		break;
	case 4:
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			spear_strike(this->getLink(link), field, adapter);
		}
		else
		{
			cout << endl << "�� ��������� ������ ��� ������!" << endl << "������ ��� �������� ����!";
			force -= 1;
		}
	} break;
	}
	if (force <= 0)
	{
		cout << endl << "���� �������";
		force = 0;
	}
}
void Spear::showSkills(Adapter *adapter) {
	cout << endl << "���������� ����: "   << force    << "������: "            << _rage
		 << endl << "1: <���� ������>"    << "\t\t"   << "������� ����: "      << _forcecost[0]//1
		 << endl << "2: <�����>"          << "\t\t\t" << "������� ����: "      << _forcecost[1]//4
		 << endl << "3: <�������>"        << "\t\t\t" << "������� ����: "      << _forcecost[2]//10
		 << endl << "4: <������ ����>"    << "\t\t"   << "���������� ������: " << _forcecost[3];//5
	adapter->request("������ ����������� � ��������� ������������");
}

void Spear::exact_blow(Units* unit, Map *field, Adapter *adapter)
{
	if (force >= _forcecost[0])
	{
		cout << endl << "������ ������� ���� ������.";
		adapter->request("������ ������� ���� ������");
		unit->health.change(-3);
		unit->reaction(field, adapter);
		force -= _forcecost[0];
		_rage += 1;
	}
	else
	{
		cout << endl << "������������ ����!";
		adapter->request("������ �������� �����������, ������������ ����");
	}
}
void Spear::roll_forward(Units* unit, Map *field, Adapter *adapter)
{
	if (force >= _forcecost[1])
	{
		cout << endl << "������ ������ ����� ������.";
		adapter->request("������ ������ ����� ������");
		unit->health.change(-2);
		unit->reaction(field, adapter);
		force -= _forcecost[1];
		_rage += 2;
	}
	else
	{
		cout << endl << "������������ ����!";
		adapter->request("������ �������� �����������, ������������ ����");
	}
}
void Spear::spear_strike(Units* unit, Map *field, Adapter *adapter)
{
	if (_rage >= _forcecost[3])
	{
		cout << endl << "������ ������� ������ ����! ��������� �� �������� ���������� � �������� ����.";
		adapter->request("������ ������� ������ ����");
		unit->health.change(-5);
		unit->reaction(field,adapter);
		_rage -= _forcecost[3];
		force -= 3;
	}
	else
	{
		cout << endl << "������������ ������!";
		adapter->request("������ �������� �����������, ������������ ������");
	}
}
Spear::~Spear()
{
	cout << endl << "������ ��� ���������!";
}


