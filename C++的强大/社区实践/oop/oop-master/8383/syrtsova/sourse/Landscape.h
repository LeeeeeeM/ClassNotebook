#pragma once
#include "Object.h"
#include "Map.h"

/// ����� ���������

/**
* �����, ���������� ���������� � ���������
* �������� ������������ ����� �������� � ������� ���������� ��������
*/

class Land : public Object {
protected:
	/// ������������
	char name;
	/// ������������ ������ �����
	int max_size;
	/// ������������ ����
	int max_water;
	/// ������������ ����� 
	int max_grass;
	/// ������������ ���
	int max_stones;
	/// ������ � ����� ����
	int  width, height;
	/// ���������� ���������
	int x, y;
public:
	/// ����������� �������� ����������� ���������
	Land(char N, int width, int height, int color);
	/// ������� ��������� ���������
	void generation(Map* field);
	/// ���������� ������
	~Land(){}
};
/// ����� ����

/**
* �����, ���������� ���������� � ������ �������� �����
*/
class Water : public Land {
	
public:
	Water(int width, int height, Map *field);
	~Water() {}
};

/// ����� �����

/**
* �����, ���������� ���������� � ������ �������� �����
*/
class Grass : public Land {
public:
	Grass(int width, int height, Map *field);
	~Grass() {}
};

/// ����� ���

/**
* �����, ���������� ���������� � ������ �������� �����
*/
class Stones : public Land {
public:
	Stones(int width, int height, Map *field);
	~Stones() {}
};

/// ����� �������� ���������� ��������� � ���������� �� ���������� ��� ��������� 

/**
* �����, ���������� ���������� � ���������
* �������� ������������ ����� �������� � ������� ���������� ��������
*/

class Landscape 
{
	Grass *grass;
	Water *water;
	Stones *stones;
public:
	Landscape(int x_max, int y_max, Map* field);
	~Landscape() {}
};