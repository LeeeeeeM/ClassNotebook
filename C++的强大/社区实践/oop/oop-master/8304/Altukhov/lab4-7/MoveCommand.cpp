#include "MoveCommand.h"

MoveCommand::MoveCommand(Base*& myBase, int arg1, int arg2, int arg3) {
	this->myBase = myBase;
	args.push_back(arg1);
	args.push_back(arg2);
	args.push_back(arg3);
}


void MoveCommand::execute() {//args[id, x, y]

	if (!myBase->getUnit(args[0])) {
		//std::cout << "����� � ����� id �� ����������\n";
		log << (std::string)"����� � ����� id �� ����������!\n";
		return;
	}
	if (myBase->getUnit(args[0])->getMoved()) {
		log << (std::string)"���� ��� ����� � ���� ����!\n";
		return;
	}
	//std::cout << "���� " << args[0] << " ������������� �� ����������� " << args[1] << ", " << args[2] << ".\n";
	log << ("���� " + std::to_string(args[0]) + " ������������� �� ����������� " + std::to_string(args[1]) + ", " + std::to_string(args[2]) + ".\n");
	myBase->getUnit(args[0])->doMove(args[2], args[1]); //��-�� �������� �������� y �������� x, a x - y
	myBase->getParentField()->visualizeField();
}