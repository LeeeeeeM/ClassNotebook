#include "pch.h"
#include "Warlock.h"
#include "Classes.h"
#include "Bases.h"
#include "Units.h"
#include "Map.h"
#include <windows.h>
#include <conio.h>


Magician::Magician(int &x, int &y) : Classe_warlock('M', 50, 6, 4, 100)
{
	XY.x = x;
	XY.y = y;
	_ether = 200;
	for (int i = 0; i < 4; i++)
	{
		nameSkills[i] = nameSkill[i];
	}
}

void Magician::selectSkill(int ch, Map* field, Units **link, Adapter *adapter, bool sLine)
{
	switch (ch)
	{
	case 1: 
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			meteorite(this->getLink(link), field, adapter);
			return;
		}
		else
		{
		cout << endl << "�� ��������� ������ ��� ������!" << endl << "��� �������� ����������, �� ����� ���� ���������!";
		mana -= 1;
		Sleep(10);
		}
	}
		break;
	case 2: 
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{

			storm(this->getLink(link),field,adapter);
			return;
		}
		else 
		{
			cout << endl << "�� ��������� ������ ��� ������!" << endl << "��� �������� ����������, �� ����� ���� ���������!";
			mana -= 1;
			Sleep(10);
		}
	}
		break;
	case 3: 
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			skill_fireball(this->getLink(link), field, adapter);
		}
		else
		{
			cout << endl << "�� ��������� ������ ��� ������!" << endl << "��� �������� ����������, �� ����� ���� ���������!";
			mana -= 1;
			Sleep(10);
		}
	}
		break;
	case 4: {
		ARMAGEDON(field, link,adapter);
		return; 
}
		break;
	}
	if (mana <= 0)
	{
		cout << endl << "���� �������!";
		Sleep(10);
		mana = 0;
	}
}

void Magician::showSkills(Adapter *adapter)
{
	cout << endl << "���������� ����: " << mana     << "\t\t"              << "���������� �����: " << this->_ether;
	cout << endl << "1: <��������> "    << "\t\t\t" << "������� ����: "    << _manacost[2] 
		 << endl << "2: <�����>"        << "\t\t\t" << "������� ����: "    << _manacost[1]
		 << endl << "3: <�������� ���>" << "\t\t"   << "������� ����: "    << _manacost[0]
		 << endl << "4: <����������>"   << "\t\t\t" << "����� �����: "	   << _manacost[3];
	adapter->request("��� ����������� � ��������� ������������");
}

void Magician::ARMAGEDON(Map* field, Units **link, Adapter *adapter)
{
	if (_ether >= _manacost[3]) {
		cout << endl << "���� ����������� ����� �������! �� �� � ��������� � ��������������."
			<< endl << "�� ��� ����� ���������� ����, � � ����� ������ ���������."
			<< endl << "���� � ������� ���� ������, ��� ����� � ������ �������� ��������� � ����."
			<< endl << "������ ����������.";
		adapter->request("��� ���������� ����������� <����������>");
		cout << endl << endl << "������� �� ����� ������, ����� ���������� ����";
		_getch();
		Object* o = new Object('@');
		o->color = colorLand::red;

		// ������ ������ 6
		if ((*field).isUnit(this->XY.x + 1, XY.y))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y;
			Units *un = this->getLink(link);
			this->deleteLink(un, link);
		}
		Sleep(10);
		(*field).addOnMap(this->XY.x + 1, this->XY.y, o);
		system("cls");
		(*field).printMap();
		// ������ ������� ������ 3
		if ((*field).isUnit(this->XY.x + 1, XY.y - 1))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(link);
			this->deleteLink(un, link);
		}
		Sleep(10);
		(*field).addOnMap(this->XY.x + 1, this->XY.y - 1, o);
		system("cls");
		(*field).printMap();
		// ����� ������ 4 
		if ((*field).isUnit(this->XY.x - 1, XY.y))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y;
			Units *un = this->getLink(link);
			this->deleteLink(un, link);
		}
		Sleep(100);
		(*field).addOnMap(this->XY.x - 1, this->XY.y, o);
		system("cls");
		(*field).printMap();
		// ������ ������ ������ 9
		if ((*field).isUnit(this->XY.x + 1, XY.y + 1))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(link);
			this->deleteLink(un, link);
		}
		Sleep(10);
		(*field).addOnMap(this->XY.x + 1, this->XY.y + 1, o);
		system("cls");
		(*field).printMap();
		// ������ ������ 8
		if ((*field).isUnit(this->XY.x, XY.y + 1))
		{
			_xy.x = this->XY.x;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(link);
			this->deleteLink(un, link);
		}
		Sleep(10);
		(*field).addOnMap(this->XY.x, this->XY.y + 1, o);
		system("cls");
		(*field).printMap();
		// ������� ����� ������ 1
		if ((*field).isUnit(this->XY.x - 1, XY.y - 1))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(link);
			this->deleteLink(un, link);
		}
		Sleep(10);
		(*field).addOnMap(this->XY.x - 1, this->XY.y - 1, o);
		system("cls");
		(*field).printMap();
		// ������ ����� ������ 7
		(*field).addOnMap(this->XY.x - 1, this->XY.y + 1, o);
		system("cls");
		(*field).printMap();
		if ((*field).isUnit(this->XY.x - 1, XY.y + 1))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(link);
			this->deleteLink(un, link);
		}
		Sleep(10);
		
		//������� ������ 2
		if ((*field).isUnit(this->XY.x, XY.y - 1))
		{
			_xy.x = this->XY.x;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(link);
			this->deleteLink(un, link);
		}
		Sleep(10);
		(*field).addOnMap(this->XY.x, this->XY.y - 1, o);
		system("cls");
		(*field).printMap();

		// ����������� ������ 5
		(*field).addOnMap(this->XY.x, this->XY.y, o);
		system("cls");
		(*field).printMap();
		Sleep(10);
		_xy.x = this->XY.x;
		_xy.y = this->XY.y;
		Units *un = this->getLink(link);
		this->deleteLink(un, link);
		return;
	}
	else
	{
		cout << endl << "������������ ������ �������!";
		adapter->request("��� �������� �����������, ������������ ����� �������");
	}
}

void Magician::meteorite(Units* unit, Map* field, Adapter *adapter)
{
	if (mana >= _manacost[1])
	{
		cout << endl << "� ���� ����� �������� ��������!";
		adapter->request("��� ���������� ����������� <��������>");
		unit->health.change(-5);
		unit->reaction(field, adapter);
		mana -= _manacost[1];
		_ether += 5;
	}
	else
	{
		cout << endl << "������������ ����!";
		adapter->request("��� �������� �����������, ������������ ����");
	}
}

void Magician::storm(Units* unit, Map* field, Adapter *adapter)
{
	if (mana >= _manacost[2])
	{
		cout << endl << "���� ���������. ������ � ������ ������� �������� ����, �� ���� ������";
		cout << endl << endl << "������� �� ����� ������, ����� ���������� ����";
		adapter->request("��� ���������� ����������� <�����>");
		_getch();
		unit->health.change(-10);
		this->health.change(-4);
		unit->reaction(field, adapter);
		this->reaction(field, adapter);
		mana -= _manacost[2];
		_ether += 10;
	}
	else
	{
		cout << endl << "������������ ����!";
		adapter->request("��� �������� �����������, ������������ ����");
	}
}

Magician::~Magician()
{
	cout << endl << "��� ��� ���������!";
}


void Healer::selectSkill(int ch, Map* field, Units **link, Adapter *adapter, bool sLine)
{
	if (mana <= 0)
	{
		cout << endl << "���� �������!";
		mana = 0;
		return;
	}
	switch (ch)
	{
	case 1:
	{
		cover(adapter);
	} break;
	case 2:
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			heal(this->getLink(link), field, adapter);
		}
		else
		{
			cout << endl << "�� ��������� ������ ��� ������!" << endl << "�������� ������ �������� ��������.";
			cover(adapter);
		}
	} break;
	case 3:
	{
		selectLine(adapter);
		if ((*field).isUnit(this->_xy.x, _xy.y))
		{
			skill_fireball(this->getLink(link), field, adapter);
		}
		else
		{
			cout << endl << "�� ��������� ������ ��� ������!" << endl << "�������� �������� ����������, �� ����� ���� ���������!";
			mana -= 1;
		}
	} break;
	case 4: mass_heal(field, link, adapter);
		break;
	}

}

Healer::Healer(int &x, int &y) : Classe_warlock('H', 40, 8, 2, 80)
{
	XY.x = x;
	XY.y = y;
	_prayer = 10;
	for (int i = 0; i < 4; i++)
	{
		nameSkills[i] = nameSkill[i];
	}
}

void Healer::showSkills(Adapter *adapter)
{
	cout << endl << "���������� ����: " << mana << "\t\t"   << "���� �������: "		    << _prayer;
	cout << endl << "1: <�������> "             << "\t\t\t" << "������� ����: "         << _manacost[2]
		 << endl << "2: <���������>"            << "\t\t\t" << "������� ����: "         << _manacost[1]
		 << endl << "3: <�������� ���>"         << "\t\t"   << "������� ����: "         << _manacost[0]
		 << endl << "4: <�������� ���������>"   << "\t\t"   << "����� ��������� ����: " << _manacost[3];
	adapter->request("�������� ����������� � ��������� ������������");
}


void Healer::heal(Units* unit, Map* field, Adapter *adapter)
{
	if (mana >= _manacost[1])
	{
		cout << endl << "�������� ������ ���������� � ����� � ������� � ���������� � ���������";
		cout << endl << endl << "������� �� ����� ������, ����� ���������� ����";
		_getch();
		adapter->request("��� ���������� ����������� <���������>");
		unit->health.change(2);
		unit->reaction(field, adapter, true);
		mana -= _manacost[1];
	}
	else
	{
		cout << endl << "������������ ����!"; 
		adapter->request("�������� �������� �����������, ������������ ����");
		Sleep(10);
	}
}
void Healer::mass_heal( Map* field, Units **link, Adapter *adapter)
{
	if (_prayer >= _manacost[3])
	{
		cout << endl << "�������� ������� � �������, ����� � ������� 1 ������ ��������";
		cout << endl << endl << "������� �� ����� ������, ����� ���������� ����";
		adapter->request("��� ���������� ����������� <�������� �����������>");
		_getch();
		// ������ ������ 6
		if ((*field).isUnit(this->XY.x + 1, XY.y))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y;
			Units *un = this->getLink(link);
			un->health.change(3);
			un->reaction(field, adapter, true);
		}
		// ������ ������� ������ 3
		if ((*field).isUnit(this->XY.x + 1, XY.y - 1))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(link);
			un->health.change(3);
			un->reaction(field, adapter, true);
		}
		// ����� ������ 4 
		if ((*field).isUnit(this->XY.x - 1, XY.y))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y;
			Units *un = this->getLink(link);
			un->health.change(3);
			un->reaction(field, adapter, true);
		}
		// ������ ������ ������ 9
		if ((*field).isUnit(this->XY.x + 1, XY.y + 1))
		{
			_xy.x = this->XY.x + 1;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(link);
			un->health.change(3);
			un->reaction(field, adapter, true);
		}
		// ������ ������ 8
		if ((*field).isUnit(this->XY.x, XY.y + 1))
		{
			_xy.x = this->XY.x;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(link);
			un->health.change(3);
			un->reaction(field, adapter, true);
		}
		// ������� ����� ������ 1
		if ((*field).isUnit(this->XY.x - 1, XY.y - 1))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(link);
			un->health.change(3);
			un->reaction(field, adapter, true);
		}
		// ������ ����� ������ 7
		if ((*field).isUnit(this->XY.x - 1, XY.y + 1))
		{
			_xy.x = this->XY.x - 1;
			_xy.y = this->XY.y + 1;
			Units *un = this->getLink(link);
			un->health.change(3);
			un->reaction(field, adapter, true);
		}
		//������� ������ 2
		if ((*field).isUnit(this->XY.x, XY.y - 1))
		{
			_xy.x = this->XY.x;
			_xy.y = this->XY.y - 1;
			Units *un = this->getLink(link);
			un->health.change(3);
			un->reaction(field, adapter, true);
		}
		// ����������� ������ 5
		this->health.change(3);
	}	
	else
	{
		cout << endl << "��������� ������� �� �������!";
		adapter->request("�������� �������� �����������, ������������ ��������� �������");
		Sleep(10);
	}
}


void Healer::cover(Adapter *adapter)
{
	if (mana >= _manacost[2])
	{
		cout << endl << "�������� ������ �������, ���������� ��������� ���� �������������";
		cout << endl << endl << "������� �� ����� ������, ����� ���������� ����";
		adapter->request("�������� ������ �������");
		_getch();
		_prayer += 1;
	}
	else
	{
		cout << endl << "������������ ����!";
		adapter->request("�������� �������� �����������, ������������ ����");
		Sleep(10);
	}
}


Healer::~Healer()
{
	cout << endl << "�������� ��� ���������!";
	Sleep(10);
}


