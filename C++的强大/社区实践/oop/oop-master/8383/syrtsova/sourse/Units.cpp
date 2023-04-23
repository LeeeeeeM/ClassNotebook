#include "pch.h"
#include <iostream>
#include <windows.h>
#include "Attribute.h"
#include "Units.h"
#include "Map.h"
#include "Error.h"
#include <conio.h>
#include "Neutral.h"


Units::Units(char N, const int &h, const int &ar, const int &at, const int &r) 
{
	name.setAtrib(N);
	health.setAtrib(h);
	armor.setAtrib(ar);
	attack.setAtrib(at);
	radius.setAtrib(r);
	object = name.returnName();
}



Units* Units::getLink(Units **link)
{
	Units *un;
	for (int i = 0; link[i] != NULL; ++i)
	{
		un = link[i];
		if (un->XY.x == this->_xy.x && un->XY.y == this->_xy.y)
		{
			return un;
		}
	}
}

void Units::deleteLink(Units *un, Units **link)
{
	for (int i = 0; link[i] != NULL; i++)
	{
		if (un->XY.x == link[i]->_xy.x && un->XY.y == link[i]->_xy.y)
		{
			for (int j = i; link[j] != NULL; j++)
			{
				link[j] = link[j+1];
			}
			delete un;
			return;
		}
	}
}


void Units::printStats(Adapter *adapter)
{
	cout << endl << "����������� �� �����: " << name.returnName() 
		 << endl << "���������� HP: " << health.returnHealth() << '\t' << '\t'
		 <<			"�������� �����: " << armor.returnArmor() 
		 << endl << "���� �����: " << attack.returnAttack() << '\t' << '\t' << '\t'
		 <<			"���� ������������: " << radius.returnRadius() << endl;
	adapter->request("���� ����������� ���������� � ����");
}


bool Units::rules(Map *field, int x, int y)
{
	if ((*field).isUnit(x, y)) return false;
	int type = (*field).isLandscape(x, y);
	if (((type != 2)  && (type != 0)) || (type == 4)) return false;
	if ((*field).isBase(x, y)) return false;
	return true;
}


void Units::managment(Map *field, Units **link, Creating *neutral, Adapter *adapter)
{
	state.is_active = true;
	cout <<  "���� " << this->name.returnName() << " ����� � �������!"<< endl;
	char select = ' ';
	if (state.is_movie)
		movie(field, neutral, adapter);
	else if (state.is_skills)
		if (state.is_direction)
			selectSkill(state.skill, field, link, adapter, state.is_direction);
		else
		selectSkill(state.skill, field, link, adapter);
	 
		
	while (int(select - '0') < 1 || int(select - '0') > 5)
	{
		try {
			string event[5] = { "�����������","������������� �����������","�������� ����� � �����", "��������� ����", "��������� ����" };
			for (int i = 0; i < 5; i++)
			{
				cout << (i + 1) << " - " << event[i] << endl;
			}
			cout << "����� ��������: "; 
			cin >> select;
			if (isdigit(select)) {
				if (int(select - '0') > 0 && int(select - '0') < 6) {
					string message = "������������ ������ " + event[int(select - '0') - 1];
					adapter->request(message);
					message = "���� " + this->message + " ������ �������";
					adapter->request(message);
				}
				switch (int(select - '0'))
				{
				case 1: {
					cin.clear();
					while (cin.get() != '\n');
					cout << endl << endl << "���� ���������� � ����. ������� �� ����� ������� ��� ���������� ����!";
					message = "���� " + this->message + " ���������� � ����";
					adapter->request(message);
					_getch();
					adapter->request("������������ ����� �� ����� �������");
					movie(field, neutral, adapter);
				}break;
				case 2: {
					cin.clear();
					while (cin.get() != '\n');
					message = "���� " + this->message + " ���������� ������������ �����������";
					adapter->request(message);
					useSkill(field, link, adapter);
					state.is_active = false;
					return;
				} break;
				case 3: {
					state.is_active = false;
					return;
				}
				case 4:
				{
					state.is_save = true;
					return;
				} break;
				case 5:
				{
					state.is_loading = true;
					return;
				}
				default: throw error2(select);
					break;
				}
			}
			else throw error1(select);
		}
		catch (error1& e)
		{
			cout << e.what();
			e.printErr();
			continue;
		}
		catch (error2& e)
		{
			cout << e.what();
			e.printErr();
			continue;
		}
	}

		
}

void Units::useSkill(Map *field, Units **link, Adapter *adapter)
{
	state.is_skills = true;
	int solution;
	printStats(adapter);
	this->showSkills(adapter);
	cout << endl << "����� �����������: "; cin >> solution;
	message = "������������ �������� ����������� " + nameSkills[solution-1];
	adapter->request(message);
	while (true)
	{
		if (solution == 1)
		{
			
			this->selectSkill(1, field, link, adapter);
			_getch();
			state.skill = solution;
			state.is_skills = false;
			return;
		}
		if (solution == 2)
		{
			this->selectSkill(2, field, link, adapter);
			state.skill = solution;
			state.is_skills = false;
			_getch();
			return;
		}
		if (solution == 3)
		{
			this->selectSkill(3, field, link, adapter);
			state.skill = solution;
			_getch();
			state.is_skills = false;
			return;
		}
		if (solution == 4)
		{
			this->selectSkill(4, field, link, adapter);
			state.skill = solution;
			_getch();
			state.is_skills = false;
			return;
		}

		Sleep(10);
		if (GetAsyncKeyState(VK_SPACE))
		{
			cin.clear();
			state.is_skills = false;
			return;
		}
	}
	state.is_skills = false;
}


void Units::selectLine(Adapter *adapter)
{
	state.is_direction = true;
	string direction[9] = { "�������� ����� ������", "�������� ������", "�������� ������ ������", "����� ������", " ����������� ������", "������ ������", "������ ����� ������", "������ ������", "������ ������ ������" };
	cout << endl << "����� �����������: "
		<< endl << "1. �������� ����� ������: " << '\t'  
		<< "2. �������� ������: " << '\t' << '\t'
		<< "3. �������� ������ ������: "
		<< endl << "4. ����� ������: " << '\t' << '\t' 
		<< "5. ����������� ������: " << '\t' << '\t'
		<< "6. ������ ������: "
		<< endl << "7. ������ ����� ������: " << '\t' 
		<< "8. ������ ������: " << '\t'
		<< "9. ������ ������ ������: " << '\t';
	cout << "10. ��������� ����" << 't';
	cout << "11. ��������� ����" << 't';
	int choice = 0;
	cout << endl << "����� �����������: "; cin >> choice;
	if (choice != 0 && choice <= 9)
	{
		message = "������������ �������� " + direction[choice + 1];
		adapter->request(message);
	}
	switch (choice) {
	case 1: {
		_xy.x = XY.x - 1;
		_xy.y = XY.y - 1;
	}break;
	case 2: {
		_xy.x = XY.x;
		_xy.y = XY.y - 1;
	}break;
	case 3: {
		_xy.x = XY.x + 1;
		_xy.y = XY.y - 1;
	}break;
	case 4: {
		_xy.x = XY.x - 1;
		_xy.y = XY.y;
	}break;
	case 5: {
		_xy.x = XY.x;
		_xy.y = XY.y;
	}break;
	case 6:{
		_xy.x = XY.x + 1;
		_xy.y = XY.y;
	}break;
	case 7:
	{
		_xy.x = XY.x - 1;
		_xy.y = XY.y + 1;
	}break;
	case 8: {
		_xy.x = XY.x;
		_xy.y = XY.y + 1;
	}break;
	case 9: {
		_xy.x = XY.x + 1;
		_xy.y = XY.y + 1;
	}break;
	case 10: {
		state.is_save = true;
		return;
	}break;
	case 11: {
		state.is_loading = true;
		return;
	}break;
	default: cout << endl << "������������ ����!";
		break;
	}
	state.is_direction = false;
}
			

void Units::reaction(Map *field, Adapter *adapter, bool effect)
{
	this->health.change(-5);
	if (!effect){
		this->color = this->colorLand::red;
		string message = "���� " + this->message + " �������� ����";
	}
	else {
		this->color = this->colorLand::green;
		string message = "���� " + this->message + " ���������� ����";
	}
	adapter->request(message);
	(*field).refreshMap(this->XY.x, this->XY.y, false, this);
	Sleep(1000);
	this->color = this->colorLand::white;
	(*field).refreshMap(this->XY.x, this->XY.y,false, this);
}



void Units::action(int &act, Creating *neutral)
{
	//char list[] = { 'P', 'T', 'C', 'R' };
	switch (act)
	{
	case 1:
	{
		neutral->pab->message();
		this->armor.change(2);
		this->attack.change(2);
		this->health.change(2);
		this->spr.changeSp1(2);
		this->spr.changeSp2(2);
	}break;
	case 2:
	{
		neutral->tablet->message();

	}break;
	case 3:
	{
		neutral->cave->message();
		if (dragonblade)
			std::cout << "������ ��� ���� ����� ������ �������������. ��� ������! ��� ����� ����� ��������. ";
		else
			neutral->cave->dragon->hel -= this->attack.returnAttack();
		if (neutral->cave->dragon->hel == 0)
			std::cout << "�������� �������� ������ ��� ����. ��� ������! ��� ����� ����� ��������.";
		else
		{
			std::cout << "������ ������� �������� ����, ���� ��������, �� ����� ������ �������";
			delete this;
			return;
		}
		
	}break;
	case 4:
	{
		neutral->ruin->message();
		dragonblade = neutral->ruin->passage();
		if (!dragonblade)
		{
			delete this;
			return;
		}
	}break;
	}
}


void Units::movie(Map *field, Creating *neutral, Adapter *adapter)
{
	system("cls");
	(*field).printMap();
	cout << "����������� ������� ��� �����������!" << endl;
	printStats(adapter);
	while (radius.returnRadius() != 0)
	{
		Sleep(100);
		if (GetAsyncKeyState(VK_UP))
		{
			adapter->request("������������ ����� �� ������� <������� �����>");
			if(rules(field, XY.x, (XY.y - 1)))
				if (!field->isNeutral((XY.x), (XY.y - 1))) {
					if (field->isLava((XY.x), (XY.y - 1)))
						reaction(field, adapter);
					else {
						radius.change(-1);
						(*field).removeFromMap(this->XY.x, this->XY.y);
						(*field).refreshMap(this->XY.x, this->XY.y, true);
						this->XY.y = this->XY.y - 1;
						(*field).addOnMap(this->XY.x, this->XY.y, this);
						(*field).refreshMap(this->XY.x, this->XY.y, false, this);
						string message = "���� " + this->message + " �������� �����";
						adapter->request(message);
					}
				}
				else
				{
					system("cls");
					(*field).printMap();
					int act = (*field).isNeutral((XY.x), (XY.y - 1));
					action(act, neutral);
				}
		}
		if (GetAsyncKeyState(VK_DOWN))
		{
			adapter->request("������������ ����� �� ������� <������� �����>");
			if(rules(field, XY.x, (XY.y + 1)))
				if (!field->isNeutral((XY.x), (XY.y + 1))) {
					if (field->isLava((XY.x), (XY.y + 1)))
						reaction(field, adapter);
					else {
						radius.change(-1);
						(*field).removeFromMap(this->XY.x, this->XY.y);
						(*field).refreshMap(this->XY.x, this->XY.y, true);
						this->XY.y = this->XY.y + 1;
						(*field).addOnMap(this->XY.x, this->XY.y, this);
						(*field).refreshMap(this->XY.x, this->XY.y, false, this);
						string message = "���� " + this->message + " �������� ����";
						adapter->request(message);
					}

				}
				else
				{
					system("cls");
					(*field).printMap();
					int act = (*field).isNeutral((XY.x), (XY.y - 1));
					action(act, neutral);
				}
		}
		if (GetAsyncKeyState(VK_LEFT))
		{
			adapter->request("������������ ����� �� ������� <������� �����>");
			if(rules(field, (XY.x - 1), XY.y))
				if (!field->isNeutral((XY.x-1), XY.y)) {
					if (field->isLava((XY.x - 1), XY.y))
						reaction(field, adapter);
					else {
						radius.change(-1);
						(*field).removeFromMap(this->XY.x, this->XY.y);
						(*field).refreshMap(this->XY.x, this->XY.y, true);
						this->XY.x = this->XY.x - 1;
						(*field).addOnMap(this->XY.x, this->XY.y, this);
						(*field).refreshMap(this->XY.x, this->XY.y, false, this);
						string message = "���� " + this->message + " �������� ����";
						adapter->request(message);
					}
				}
				else
				{
					system("cls");
					(*field).printMap();
					int act = (*field).isNeutral((XY.x), (XY.y - 1));
					action(act, neutral);
				}
		}
		if (GetAsyncKeyState(VK_RIGHT))
		{
			adapter->request("������������ ����� �� ������� <������� ������>");
			if(rules(field, (XY.x + 1), XY.y))
				if (!field->isNeutral((XY.x + 1), XY.y)){
					if (field->isLava((XY.x + 1), XY.y))
						reaction(field, adapter);
					else	{
						radius.change(-1);
						(*field).removeFromMap(this->XY.x, this->XY.y);
						(*field).refreshMap(this->XY.x, this->XY.y, true);
						this->XY.x = this->XY.x + 1;
						(*field).addOnMap(this->XY.x, this->XY.y, this);
						(*field).refreshMap(this->XY.x, this->XY.y, false, this);
						string message = "���� " + this->message + " �������� ������";
						adapter->request(message);
					}
				}
				else
				{
					system("cls");
					(*field).printMap();
					int act = (*field).isNeutral((XY.x), (XY.y - 1));
					action(act, neutral);
				}
		}
		if (GetAsyncKeyState(VK_SPACE))
		{
			adapter->request("������������ ����� �� ������� <������>");
			cin.clear();
			system("cls");
			(*field).printMap();
			string message = "���� " + this->message + " ���������� ������������";
			adapter->request(message);
			return;
		}
	}
	cin.clear();
	system("cls");
	(*field).printMap();
	string message = "���� " + this->message + " ���������� ������������";
	adapter->request(message);
	cout << message << ". " << "����������� ���� ������������";
}


void Units::operator+ (Units* unit) {
	cout << "���� ����� ������� �����, ���������, ����� � ���� ���������?";
}



void Units::selected(Map *field, Adapter *adapter)
{
	if (move(field))
		return;
}



Units::~Units()
{
}


