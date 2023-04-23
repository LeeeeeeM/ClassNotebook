#include "pch.h"
#include "Neutral.h"
#include "Object.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <conio.h>
#include "ctime"

Neutral::Neutral(char n, string message_, int x_, int y_, int col) {
	name = n; 
	object = name;
	color = col;
	XY.x = x_;
	XY.y = y_;
}

void Neutral::setLoc(int x, int y)
{
	XY.x = x;
	XY.y = y;
}


Neutral* Neutral::getLink(int &x, int &y)
{
	for (int i = 0; i < 4; i++)
	{
		if(link[i]->getX() == x && link[i]->getY() == y)
		return link[i];
	}
}

int Neutral::getX()
{
	return XY.x;
}


int Neutral::getY()
{
	return XY.y;
}


Neutral* Neutral::returnThis(int x, int y)
{
	if (x == this->XY.x && y == this->XY.y)
		return this;
}



Pab::Pab(int x, int y) : Neutral('P', "This is PAB!", x, y, colorLand::red){
	
}

void Pab::message (){
	string message[] = { "����� ������ ������ ����� �������. �� ������ �������, � ������� � ������� ����� �����. ������ ������ ������� �������� ��������. �����, ��������� �������, ���������: ��� ��̻. \n ���� �������������� ������ ���� �������� �� �������� ������ � ���������� ���� �� �������. ��������� ���� ������ ����������� ���� � ������� ������. \n����� ������, ������ ������� ��������� ���������� ��� � ��������� ������, ����������� ������� � ��������, ��� ������� �������� �������������� ���. \n �����������, ���� ����� ����� � ����� ����, � ������ �� �������� ���� � ���������������. ������ �������� ��������, ��� ��� � ������� ����� ����� �� ���� ��� ������ � �������, � �� � ������. \n � �� ������, ��������� � �����, �� ������� ����������� ������. ������ �� ������, ��� ���������� ������� � �������� �� ������������ ��������� � ������ ����� ����� ����. \n������ ��� ���� �� �������� ����, ���� �� �������� �����, �� ���������. �� �� ������� ������� ��� - �� ������� � �����, ����, ��� ��� ���������� ���� � ������ ����, � �� �������������� ������ ��������� ������� �������� ������� �� ��������� �����.������ �� ��� ������� ������ ������ � ��� ������� ������ ���� ������, ��� ��������.��� ������� ��� �������� �������� �� �����, ����� ������ ��������� ��������. \n����� ��� �� �����, ��� �� ���� ���������." };
	for (int i = 0; i != message->length(); i++)
	{
		cout << message[i];
		Sleep(1);
	}
	Sleep(10);
	for (int i = 0; i != message->length(); i++)
	{
		cout << message[i];
		Sleep(1);
	}
	Sleep(10);
	cout << endl;
	string message_2[] = { "���� ��������� ����������� ���� ����. ����� ����, ��������� �������� ���� ������� ��� �������� ����������: �������, ����� � �����. /n. ���������� ����� ��� ������������ ����� �����������. ���� ������� � ����� �������������! " };
	for (int i = 0; i != message_2->length(); i++)
	{
		cout << message[i];
		Sleep(1);
	}
}

Pab::~Pab() {
	cout << endl << "�, ���! �� ���?!";
}

Tablet::Tablet(int x, int y) : Neutral('T', "This is Tablet", x, y, colorLand::cyan) {
}

void Tablet::message(){
	cout << "���� ������ �������� �����, ������� ��������� ����������!";
}
Tablet::~Tablet() {
	cout << endl << "������ ��������� ������ ����� ���������� =(";
}


Cave::Cave(int x, int y) : Neutral('C', "This is Cave", x, y, colorLand::yellow) {
	dragon = new Dragon;
}


void Cave::message(){
	cout << endl << "���� ������ �����. ����� ����� ������� ���������� � ��������. ���� ������ ��. ��� ��� ���� �������� ������.";
}

Cave::~Cave() {
	cout << endl << "����� ���������!";
}


Ruin::Ruin(int x, int y) : Neutral('R', "This is Ruin", x, y, colorLand::lightBlue) {
	trap_1 = true;
	strength_1 = 100;
	trap_2 = true;
	strength_2 = 100;
	trap_3 = true;
	strength_3 = 100;
	trap_4 = true;
	strength_4 = 100;
	trap_5 = true;
	strength_5 = 100;
	state = true;
}


void Ruin::printMessage(string message)
{
	for (int i = 0; i != message.length(); i++)
	{
		cout << message[i];
		Sleep(1);
	}
}


bool Ruin::passage()
{
	if (state)
	{
		string message = "���� ������� � �����, �� ��� ����� ����������. ����� ������ �������. ���� �������� �������� �� �� �� �����. �� ������ ���, ���-�� ������� ������������ �������� � ����, ������ �� �� �������� �� ���������� �������?";
		int chance = 0;
		srand(time(0));
		if (trap_1)
		{
			printMessage(message);
			chance = 0 + rand() % strength_1;
			if (chance <= 50)
			{
				message = "���� ���� �������� �� ���������� ��������. �� ����������� �� �� ���� ���������?";
				
				strength_1 -= 20;
				if (strength_1 == 0)
					trap_1 = false;
				printMessage(message);
			}
			else
			{
				message = "���� �� ���� �������� �� ���������� ��������. �������� ����� �������� �������. ����� ������ ������";
				printMessage(message);
				strength_1 -= 20;
				if (strength_1 == 0)
					trap_1 = false;
				return false;
			}
		}
		if (trap_2)
		{
			message = "�� ��������� ���� ����� �������� �����������. �� ������� �� �����, ��� � ������. ��, ��� �, ��������� �� �����.";
			printMessage(message);
			chance = 0 + rand() % strength_2;
			if (chance <= 50)
			{
				message = "�����������, �� ���� ������� ���� � ����� �������������!";
				strength_2 -= 20;
				if (strength_2 == 0)
					trap_2 = false;
				printMessage(message);
			}
			else
			{
				message = "��������� ���� �� ����� �� ��������. ���� ������� �� ����. �� ��������� �������� ����������� ������. ���� ����.";
				printMessage(message);
				strength_1 -= 20;
				if (strength_1 == 0)
					trap_1 = false;
				return false;
			}
		}
		if (trap_3 == true)
		{
			message = "�� ������ ���� ����� ��������� �������. �� �� ���������, ��� �� ���� ��������, � ������� �������. ����� �� ���� �� �� �����?";
			printMessage(message);
			chance = 0 + rand() % strength_3;
			if (chance <= 50)
			{
				message = "���� ���������, ��� ������ ������ ������� � ������� ����. �� ����� ��������: �����������. ����� ���� ������ �������� �� ������ ���� ������.";
				strength_3 -= 20;
				if (strength_3 == 0)
					trap_3 = false;
				printMessage(message);
			}
			else
			{
				message = "���� �� ����� ������ � �������: �������������. � �� �� ��������� �� �������� ��� ������. ";
				printMessage(message);
				if (strength_3 != 0)
					strength_3 -= 20;
				return false;
			}
		}
		if (trap_4 == true)
		{
			message = "���� ������� � �������� ������� ���. ������ �������� ������ ����. ������ �� ���� ����� �����? ";
			printMessage(message);
			chance = 0 + rand() % strength_1;
			if (chance <= 50)
			{
				message = "���� ����� �����. �� ��������� �� �����, ������� ��������� �� ��� ����. ����� �������, ����� ��� ��� �����������.";
				if (strength_1 != 0)
					strength_1 -= 20;
				printMessage(message);
			}
			else
			{
				message = "���� �� ���� ����� ����� � ����������. �� �������� �� �������: ��������, ��� ��� ������. ���������� ������";
				printMessage(message);
				if (strength_1 != 0)
					strength_1 -= 20;
				return false;
			}
		}
		if (trap_5 == true)
		{
			message = "���� ������� � ����� ������������. �� ����� ������ � �����. �� ��� �������� �������� ����. ���� ����� ���� ����� ������ ��������, �� ������ � ���� �� ���� � ����. ��������� ������ ���� � �����: �� ������ ����� ���� ���, �� � ���� ����� ���� �������.";
			printMessage(message);
			chance = 0 + rand() % strength_1;
			if (chance <= 50)
			{
				message = "���� ����� �����, ��� ��� �����-�� ������. �� ��������� � ������ ������� �������, �� ������� �������� ��������� ��������������� ����. �� ����� �������, ����� ���� ����� ���� ���, � ������ ��� ��� ����������� � ����.";
				printMessage(message);
				state = false;
				return true;
			}
			else
			{
				message = "���� �������� ��������� �� �����, �� ��� ������ ��� ��� ��������, ���� ����������� � ����.";
				printMessage(message);
				if (strength_1 != 0)
					strength_1 -= 20;
				return false;
			}
		}
	}
	else
	{
		string message = "���� ������ ���������� �� ������. �������� ���, �� ��� ������ ������ ������.";
		printMessage(message);
	}
}

void Ruin::message(){
	cout << "���� ����� ������� ����� ������� �������������� �����������. /n�� ����� ��������� �������, ������� �������� ������� ���������, ������������� ����� �� 100 ������. /n ������ �� ���� � ����� ������� �������?/n";
}
Ruin::~Ruin() {
	cout << endl <<"����� ���� ����������";
}



Creating::Creating(int x_max, int y_max, Map* field)
{
	pab = new Pab(x_max - 2, 1);
	tablet = new Tablet(x_max / 2, y_max / 2);
	cave = new Cave(x_max, y_max);
	ruin = new Ruin(x_max / 2, y_max - 3);
	(*field).addOnMap(pab->getX(), pab->getY(), pab);
	(*field).addOnMap(tablet->getX(), tablet->getY(), tablet);
	(*field).addOnMap(cave->getX(), cave->getY(), cave);
	(*field).addOnMap(ruin->getX(), ruin->getY(), ruin);
}


Creating::Creating(int x_max, int y_max, Map* field, bool state)
{
	pab = new Pab(x_max, y_max);
	tablet = new Tablet(x_max, y_max);
	cave = new Cave(x_max, y_max);
	ruin = new Ruin(x_max, y_max);
}

//int x_p, int y_p, int x_t, int y_t, int x_c, int y_c, int x_r, int y_r