#include "Unit.h"
#include "Field.h"
#include <iostream>
#include <cmath>
#include <algorithm>
#include <map>
Unit::~Unit() {
	if (this->getParentField()) {
		Field* f = this->getParentField();
		if (this->getX() >= 0) {
			f->getTile(this->getX(), this->getY()).isOccupied = false;
			f->getTile(this->getX(), this->getY()).occupiedBy = nullptr;

		}

	}
}

int Unit::getId() {
	return id;
}

int Unit::getPlayer()
{
	return player;
}

int Unit::getAttack() {
	return attack - attackDebuff + attackBuff;
}
int Unit::getHp() {
	return hp;
}
int Unit::getArmor() {
	return armor + armorBuff;
}
int Unit::getHaste() {
	return haste;
}
int Unit::getRange() {
	return range + rangeBuff;
}
int Unit::getLevel() {
	return level;
}
int Unit::getCost() {
	return cost;
}
UnitTypes Unit::getUnitType() {
	return type;
}


Field* Unit::getParentField() {
	return parentField;
}
int Unit::getX() {
	return x;
}
int Unit::getY() {

	return y;
}


std::string Unit::getUnitName() {
	if (this->getUnitType() == UnitTypes::MELEE && this->getLevel() == 1)
		return "����������";
	if (this->getUnitType() == UnitTypes::MELEE && this->getLevel() == 2)
		return "������";
	if (this->getUnitType() == UnitTypes::RANGE && this->getLevel() == 1)
		return "������";
	if (this->getUnitType() == UnitTypes::RANGE && this->getLevel() == 2)
		return "����������";
	if (this->getUnitType() == UnitTypes::HORSEMAN && this->getLevel() == 1)
		return "������ ����������";
	if (this->getUnitType() == UnitTypes::HORSEMAN && this->getLevel() == 2)
		return "������� ����������";
}
void Unit::setId(int val) {
	id = val;
}

void Unit::setAttack(int val) {
	attack = val;
}
void Unit::setHp(int val) {
	hp = val;
}
void Unit::setArmor(int val) {
	armor = val;
}
void Unit::setHaste(int val) {
	haste = val;
}
void Unit::setRange(int val) {
	range = val;
}
void Unit::setLevel(int val) {
	level = val;
}
void Unit::setCost(int val) {
	cost = val;
}
void Unit::setUnitType(UnitTypes val) {
	type = val;
}




void Unit::setParentField(Field*& field){
	parentField = field;
}

void Unit::setParentBase(Base*& base, int player)
{
	parentBase = base;
	this->player = player;
}

void Unit::addLog(ProxyLog* log)
{
	this->log = log;
}

bool Unit::tryToDie(Unit*& unit) {
	
	if (hp <= 0) {
		parentBase->deleteUnit(unit);
		return true;
	}
	return false;
}

bool Unit::doAttack(Unit*& target) {

	if (this->player == target->getPlayer()) {
		log << (std::string)"������ ��������� �����!\n";
		return false;
	}

	int localRange = this->range + this->rangeBuff;
	if (abs(this->x - target->x) > localRange || abs(this->y - target->y) > localRange) {
		//std::cout << "������ ��������� ������ ��� �� " << localRange << " ������!\n";
		log << "������ ��������� ������ ��� �� " + std::to_string(localRange) + " ������!\n";
		return false;
	}
	int attackPower = this->attack + attackBuff - attackDebuff - target->getArmor() - target->getArmorBuff();
	if (attackPower > 0) {
		target->setHp(target->getHp() - attackPower);
	}
	log << "���� �����: " + std::to_string(std::max(attackPower, 0)) + "\n";
	attacked = true;
	return target->tryToDie(target);
}
void Unit::doMove(int x, int y) {

	if ((x >= parentField->getW()) || (y >= parentField->getH()) || x<0 || y<0) {
		//std::cout << "����� �� ������� ����!\n";
		log << (std::string)"����� �� ������� ����!\n";
		return;
	}
	if (parentField->getTile(x, y).isOccupied || parentField->getTile(x, y).isOccupiedByBase) {
		//std::cout << "������ ��� ������!\n";
		log << (std::string)"������ ��� ������!\n";
		return;
	}
	int haste = this->getHaste();
	if (this->x >= 0 && (abs(this->x - x) > haste || abs(this->y - y) > haste)) {
		//std::cout << "������ ������������� ������ ��� �� " << haste <<" ������!\n";
		log << "������ ������������� ������ ��� �� " + std::to_string(haste) + " ������!\n";
		return;
	}
	if (this->x >= 0) {
		
		if (parentField->getTile(this->x, this->y).isOccupiedByNeutral) {
			Unit* target = const_cast<Unit*>(this);
			parentField->getTile(this->x, this->y).occupiedByNeutral->removeEffect(target);
		}

		parentField->getTile(this->x, this->y).isOccupied = false;
		parentField->getTile(this->x, this->y).occupiedBy = nullptr;
	}
	this->x = x;
	this->y = y;
	parentField->getTile(x, y).isOccupied = true;

	parentField->getTile(x, y).occupiedBy = this;
	parentField->getTile(x, y).capturedBy = player;

	moved = true;

	Unit* target = const_cast<Unit*>(this);
	parentField->getTile(x, y).terrain->doTerrainEffect(target);

	if (parentField->getTile(x, y).isOccupiedByNeutral) {
		parentField->getTile(x, y).occupiedByNeutral->applyEffect(target);
	}
}

bool Unit::doAttackOnBase(Base*& target)
{
	int localRange = this->range + this->rangeBuff;
	if (abs(this->x - target->getX()) > localRange || abs(this->y - target->getY()) > localRange) {
		//std::cout << "������ ��������� ������ ��� �� " << localRange << " ������!\n";
		log << "������ ��������� ������ ��� �� " + std::to_string(localRange) + " ������!\n";
		return false;
	}
	int attackPower = this->attack + attackBuff - attackDebuff;
	if (attackPower > 0) {
		target->setHp(target->getHp() - attackPower);
	}
	log << "���� �����: " + std::to_string(std::max(attackPower, 0)) + "\n";
	log << "��������� ����: " + std::to_string(target->getHp()) + "\n";
	return target->tryToDie();

}



int Unit::getAttackDebuff() {
	return attackDebuff;
}

void Unit::setAttackDebuff(int val) {
	attackDebuff = val;
}

int Unit::getArmorBuff() {
	return armorBuff;
}

void Unit::setArmorBuff(int val) {
	armorBuff = val;
}

int Unit::getAttackBuff() {
	return attackBuff;
}

void Unit::setAttackBuff(int val) {
	attackBuff = val;
}

int Unit::getRangeBuff() {
	return rangeBuff;
}

bool Unit::getAttacked()
{
	return attacked;
}

bool Unit::getMoved()
{
	return moved;
}

void Unit::setRangeBuff(int val) {
	rangeBuff = val;
}

void Unit::resetAttacked()
{
	attacked = false;
}

void Unit::resetMoved()
{
	moved = false;
}

void Unit::setAttacked(bool val)
{
	attacked = val;
}

void Unit::setMoved(bool val)
{
	moved = val;
}
