#pragma once
#include "pch.h"
#include "Object.h"
#include <iostream>

#define MAX 4000

using namespace std;



/// ����� �����

/**
* �����, ���������� ���������� � �����, �������� ��������� ����� ����������� ��� �������������� � ������
*/
class Map {
	int  _width;   //������� ����
	int  _height;   //������� ����
	int  _count_object;//���������� ��������
	int  _mas_x[MAX];  //������ ��������� x ��������� �� ����
	int  _mas_y[MAX];  //������ ��������� y ��������� �� ����
public:
	int getWidth(); // ��������� ������ ����
	int getHeight(); // �������� ������ ����
	Object ***field;    //���� ����
	Map(int &x, int &y); //�����������
	bool isObject(int &x, int &y); // ��������: �������� �� ��������� ������ ��������
	Map(const Map & map); //����������� ����������� ����
	Map &operator=(const Map &map);//�������� ��� ������������ �����������
	Map(Map&& map);
	Map& operator=(Map&& map);
	void refreshMap(int &x, int &y, bool flag, Object *obj = new Object('*'));
	void printMap(); //������� ����
	void addOnMap(int x, int y, Object* object);//��������� ������
	void removeFromMap(int x, int y);//������� � ���� ������
	int isLandscape(int &x, int &y); // ��������: �������� �� ��������� ������ ����������
	int isNeutral(int x, int y);// ��������: �������� �� ��������� ������ ����������� ��������
	bool isUnit(int x, int y); // ��������: �������� �� ��������� ������ ������
	bool isBase(int &x, int &y);// ��������: �������� �� ��������� ������ �����
	bool isLava(int x, int y);// ��������: �������� �� ��������� ������ �����
	Object* getObject(int x, int y);// ��������� ������� �� ��� �����������
	~Map();
};


