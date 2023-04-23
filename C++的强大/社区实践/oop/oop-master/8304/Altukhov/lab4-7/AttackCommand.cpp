#include "AttackCommand.h"

AttackCommand::AttackCommand(Base*& myBase, Base*& enemyBase, int arg1, int arg2) {
	this->myBase = myBase; 
	this->enemyBase = enemyBase;
	args.push_back(arg1); 
	args.push_back(arg2); 
}


void AttackCommand::execute() {//args[attackerId, targetId]

	Unit* unit1 = myBase->getUnit(args[0]);

	if (unit1 && unit1->getAttacked()) {
		log << (std::string)"���� ��� �������� � ���� ����!\n";
		return;
	}

	if (args[1] == 0) {//����� ����
		if (!unit1 ) {
			//std::cout << "����� � ����� id �� ����������!\n";
			log << (std::string)"����� � ����� id �� ����������!\n";
			return;
		}
		log << ("���� " + std::to_string(args[0]) + " ������� ����!\n");
		unit1->doAttackOnBase(enemyBase);
		myBase->getParentField()->visualizeField();
		return;
	}
	
	Unit* unit2 = enemyBase->getUnit(args[1]);
	if (!unit1 || !unit2) {
		//std::cout << "����� � ����� id �� ����������!\n";
		log << (std::string)"����� � ����� id �� ����������!\n";
		return;
	}
	//std::cout << "���� " << args[0] << " ������� ����� " << args[1] << "!\n";
	log << ("���� " + std::to_string(args[0]) + " ������� ����� " + std::to_string(args[1]) + "!\n");
	//myBase->getUnit(args[0])->doAttack(myBase->getUnit(args[1]));
	unit1->doAttack(unit2);
	myBase->getParentField()->visualizeField();
}