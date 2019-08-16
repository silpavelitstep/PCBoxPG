#include "pcbox.h"
#include <iostream>
#include <fstream>
#include <vector>
#pragma warning(disable:4996)
using namespace std;
Unit::~Unit() {
	if (name) delete[] name;
	//cout << "free Unit\n";
}
Box::~Box() { cout << "free PCBox\n"; }
Power::~Power() { /*cout << "free Power\n";*/ }
MotherBoard::~MotherBoard(){ cout << "free MotherBoard\n"; }
CPU::~CPU() { cout << "free CPU\n"; }
GPU::~GPU(){ cout << "free GPU\n"; }
RAM::~RAM() { cout << "free GPU\n"; }
SATA::~SATA() { cout << "free SATA\n"; }
Drive::~Drive() { cout << "free Drive\n"; }
ROM::~ROM() { cout << "free ROM"; }
//metods
void Box::clear() {
	int x, y;
	for (y = 0; y <= 12; y++)
		for (x = 0; x <= 29; x++)
			maket[y][x] = '.';
	//power
	for (y = 1; y <= 2; y++)
		for (x = 1; x <= 8; x++)
			maket[y][x] = 'X';
	//motherboard
	for(y=4;y<=11;y++)
		for(x=1;x<=18;x++)
			maket[y][x] = 'X';
}
void Box::show() {
	for (int y = 0; y <= 12; y++) {
		for (int x = 0; x <= 29; x++)
			cout<<maket[y][x];
		cout << endl;
	}
}
void Box::newUnit() {
	cout << "select type unit:\n"
		<< "'p' - Power,\n"
		<< "'m' - motherboard,\n"
		<< "'g' - GPU,\n"
		<< "'c' - CPU,\n"
		<< "'r' - RAM,\n"
		<< "'s' - SATA unit,\n"
		<<"any other key for exit:\n";
	char select;
	cin >> select;
	char buf[100];
	cin.getline(buf, 99);
	switch (select) {
	case 'p':Power::newPower(); break;
	case 'm':break;
	case 'g':break;
	case 'c':break;
	case 'r':break;
	case 's':break;
	}
}
void Box::menu() {
	clear();
	char select;
	char buf[100];
	bool menuOn=true;
	do {
		system("cls");
		show();
		cout << "select mode:\n"
			<< "'c' - Clear maket,\n"
			<< "'f' - add new unit to file,\n"
			<< "'m' - add new unit to maket,\n"
			<<"'d' - delete unit from maket,\n"
			<< "'x' - for exit\n";
		cin >> select;
		char buf[100];
		cin.getline(buf, 99);
		switch (select) {
		case 'c':clear(); break;
		case 'f':newUnit(); break;
		case 'm':addUnitToMaket(); break;
		case 'd':delUnitFromMaket(); break;
		case 'x':menuOn = false; break;
		default:
			cout << "Incorrect value!";
			
		}
	} while (menuOn);

}
void Power::newPower() {
	Power pwr;
	char select;
	do {
		cout << "Input name: ";
		char tmp[256];
		cin.getline(tmp, 255);
		pwr.name = new char[strlen(tmp) + 1];
		strcpy(pwr.name, tmp);
		cout << "Input size power: ";
		cin >> pwr.pwr;
		cout << "save to file?\n"
			<< "'y' - yes,\n"
			<< "any char for exit\n"
			<< "'c' - clear,\n"
			<< endl;
		cin >> select;
		char buf[100];
		cin.getline(buf, 99);
		if (select == 'y') {
			ofstream f("power.txt",ios::app);
			f << '#' << pwr.name << '^' << pwr.pwr << endl;
			f.close();
			break;
		}
		else if (select == 'c')
			continue;
		break;
	} while (true);


}
void Box::addUnitToMaket() {
	cout << "select type unit:\n"
		<< "'p' - Power,\n"
		<< "'m' - motherboard,\n";
	if(mb)
		cout<< "'g' - GPU,\n"
			<< "'c' - CPU,\n"
			<< "'r' - RAM,\n"
			<< "'s' - SATA unit,\n";
	// !mb
	cout<< "any other key for exit:\n";
	char select;
	cin >> select;
	char buf[100];
	cin.getline(buf, 99);
	
	switch (select) {
	case 'p':Power::takePower(); break;
	case 'm':break;
	case 'g':break;
	case 'c':break;
	case 'r':break;
	case 's':break;
	}
}
void Box::delUnitFromMaket() {

}
Power::Power(const Power& obj) {
	this->name = new char[strlen(obj.name)+1];
	strcpy(this->name, obj.name);
	this->pwr = obj.pwr;
	
}
Power::Power() {
	pwr = 0;
	name = 0;
}
ostream& operator<<(ostream& out, const Power& pwr) {
	out << pwr.name << '\t' << pwr.pwr << endl;
	return out;
}
void Power::takePower() {
	system("CLS");
	ifstream f("power.txt");
	char bf;
	Power pwr;
	pwr.name = new char[256];
	vector<Power> vPow;
	while (f) {
		f >> bf;//#
		f.getline(pwr.name, 255,'^');
		f >> pwr.pwr;
		if (strcmp(pwr.name, "") != 0) {
			vPow.push_back(pwr);
			cout << pwr;
		}
	}
	cout << "check name:";
	cin.getline(pwr.name, 255);
	bool bingo = false;
	for (Power p : vPow) {
		if (strcmp(p.name, pwr.name) == 0) {
			bingo = true;


		}
		
	}
	system("pause");
	f.close();
}