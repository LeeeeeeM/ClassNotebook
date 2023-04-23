#pragma once
#include "Tile.h"
#include "Base.h"
#include "ProxyLog.h"
#include "Memento.h"
constexpr auto DEFAULT_W = 8;
constexpr auto DEFAULT_H = 8;
constexpr auto MAX_OBJECTS_AMOUNT = 50;

//enum class UnitTypes {
//	MELEE, RANGE, HORSEMAN
//};
struct Tile;
class Unit;
class Base;
class Memento;

class Field {

	Tile** fieldArr;
	int width;
	int height;
	int amountOfObjects;
	ProxyLog* log;
public:

	Field();
	Field(int w, int h);
	Field(const Field& field);
	~Field();
	void totalCopy(Field*& fToCopy, Field*& fToPaste);//��������� �������� ��� �� �� ����� ��� this ������ �� �����������
	int getW();
	int getH();
	Tile& getTile(int x, int y);

	int getAmountOfObjects() { return amountOfObjects; }
	void raiseAmountOfObjects() { amountOfObjects++; }
	void lowAmountOfObjects() { amountOfObjects--; }
	void visualizeField();
	//Unit* createAndSetUnit(UnitTypes type, int lvl, int x, int y, Field*& f);
	Base* createAndSetBase(Field*& f, int baseNum);
	//NeutralObject* createAndSetNeutralObject(NeutralObjectTypes type, int);
	//void deleteUnit(Unit*& unit);
	void deleteBase(Base*& base);
	void addLog(ProxyLog* log);
	void fillMemento(Memento*& snapshot);
	void newField(Memento*& snapshot);
};

