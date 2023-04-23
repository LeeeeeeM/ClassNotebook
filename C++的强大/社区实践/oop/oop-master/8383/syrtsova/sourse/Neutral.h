#pragma once
#include "Object.h"
#include "Map.h"
#include "Dragon.h"

/// ����� ����������� ��������

/**
* �����, ���������� ���������� � ����������� ��������
*/
class Neutral : public Object
{
	Neutral *link[4]; // ��������� �� ����������� �������
	int _x_max; //������������ ������ ���� �� �
	int _y_max; //������������ ������ ���� �� Y
protected:
	char name; // ������������ ������������ �������
/// ���������� ������������ �������
	struct Coordinates {
		int x, y;
	}XY;
public:
	/// ����������� ������������ �������
	Neutral(char n, string message, int x_, int y_, int col);
	/// ����������� ������� ������ ��������� 
	virtual void message() =  0;
	///������� ��������� ������������ �������
	Neutral* returnThis(int x, int y);
	///������� ��������� ��������� �� ����� 
	void setLoc(int x, int y);
	///������� ��������� ���������� �� ��� X
	int getX();
	///������� ��������� ���������� �� ��� Y
	int getY();
	Neutral* getLink(int &x, int &y);
};


/// ����� �������

/**
* �����, ���������� ���������� � �������
*/
class Pab : public Neutral
{
public:
	Pab(int x, int y);
	void message() override; 
	~Pab();
};

/// ����� ��������

/**
* �����, ���������� ���������� � ��������
*/
class Tablet : public Neutral
{
public:
	Tablet(int x, int y);
	void message() override;
	~Tablet();
};

/// ����� �����

/**
* �����, ���������� ���������� � �����
*/
class Cave : public Neutral
{
public:
	Dragon* dragon;
	Cave(int x, int y);
	void message() override;
	~Cave();
};
/// ����� ����

/**
* �����, ���������� ���������� � ������
*/
class Ruin : public Neutral
{
	bool trap_1, trap_2, trap_3, trap_4, trap_5;
	int strength_1, strength_2, strength_3, strength_4, strength_5;
	bool state;
public:
	bool passage();
	void printMessage(string message);
	Ruin(int x, int y);
	void message() override;
	~Ruin();
};

/// ����� �������� ����������� ��������

/**
* �����, �������� ��������� �� ��� ����������� ������� � ���������� �� �� ��������
*/
class Creating 
{
public:
	Pab *pab;
	Tablet *tablet;
	Cave *cave;
	Ruin *ruin;
	Creating(int x_max, int y_max, Map* field);
	Creating(int x_max, int y_max, Map* field, bool state);
};