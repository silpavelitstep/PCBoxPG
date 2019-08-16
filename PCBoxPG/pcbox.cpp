#include "pcbox.h"
#include <iostream>
#include <fstream>
#include <vector>
#pragma warning(disable:4996)
using namespace std;
//Unit
Unit::~Unit() {
	if (name) delete[] name;
	//cout << "free Unit\n";
}

//Box
Box::~Box() {
	//cout << "free PCBox\n";
	if (power) delete power;
	if (mabd) delete mabd;
}
void Box::clear() {
	//drow
	rect(0, 0, 29, 12, '.');//box
	rect(1, 1, 8, 2, 'X');//no power
	rect(1,4,18,11,'+');//no motherboard
	
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
	case 'm':MotherBoard::newMotherBoard(); break;
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
			<<"'l' - show units list,\n "
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
		case 'l':list(); break;
		case 'x':menuOn = false; break;
		default:
			cout << "Incorrect value!";
			
		}
		system("pause");
	} while (menuOn);

}
void Box::addPower() {
	system("CLS");
	ifstream f("power.txt");
	char bf;
	Power pwr;
	pwr.name = new char[256];
	vector<Power> vPow;
	//load from file to vector
	while (f) {
		f >> bf;//#
		f.getline(pwr.name, 255, '^');
		f >> pwr.pwr;
		if (strcmp(pwr.name, "") != 0) {
			vPow.push_back(pwr);
			cout << pwr;
		}
	}
	//select name
	cout << "check name:";
	cin.getline(pwr.name, 255);

	for (Power p : vPow) {
		if (strcmp(p.name, pwr.name) == 0) {
			if (power == 0)
				power = new Power();
			//copy
			if (power->name) delete[] power->name;
			power->name = new char[strlen(p.name) + 1];
			strcpy(power->name, p.name);
			power->pwr = p.pwr;
			//drow
			rect(1, 1, 8, 2, '+');
			break;//for vPow
		}

	}
	
	f.close();
}
void Box::addUnitToMaket() {
	cout << "select type unit:\n"
		<< "'p' - Power,\n"
		<< "'m' - motherboard,\n";
	if(mabd)
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
	case 'p':Box::addPower(); break;
	case 'm':Box::addMotherBoard(); break;
	}
	if (mabd) switch (select){
	case 'g':break;
	case 'c':break;
	case 'r':break;
	case 's':break;
	}
}
void Box::delUnitFromMaket() {
	cout << "select unit for delete:\n"
		<< "'p' - Power,\n"
		<< "'m' - motherboard,\n";
	if (mabd)
		cout << "'g' - GPU,\n"
		<< "'c' - CPU,\n"
		<< "'r' - RAM,\n"
		<< "'s' - SATA unit,\n";
	// !mb
	cout << "any other key for exit:\n";
	char select;
	cin >> select;
	char buf[100];
	cin.getline(buf, 99);

	switch (select) {
	case 'p':
		delete power;
		power = 0;
		rect(1,1,8,2,'X');
		break;
	case 'm':; break;
	}
	if (mabd) switch (select) {
	case 'g':break;
	case 'c':break;
	case 'r':break;
	case 's':break;
	}
}
void Box::rect(int x1, int y1, int x2, int y2, char c) {
	for (int y = y1; y <= y2; y++) {
		for (int x = x1; x <= x2; x++)
			maket[y][x] = c;
	}
}
void Box::addMotherBoard() {
	system("CLS");
	ifstream f("mother.txt");
	char bf;
	MotherBoard mb;
	mb.name = new char[256];
	mb.soket = new char[256];
	vector<MotherBoard> vPow;
	//load from file to vector
	while (f) {
		f >> bf;//#
		f.getline(mb.name, 255, '^');
		f.getline(mb.soket, 255, '^');
		f>> mb.maxCountRAMUnits >> mb.maxCountSATAunits
			>> mb.minFreq >> mb.maxFreq >> mb.maxVolume >> mb.type;
		if (strcmp(mb.name, "") != 0) {
			vPow.push_back(mb);
			cout << mb;
		}
	}
	//select name
	cout << "check name:";
	cin.getline(mb.name, 255);
	for (MotherBoard p : vPow) {
		if (strcmp(p.name, mb.name) == 0) {
			if (mabd == 0)
				mabd = new MotherBoard();
			//copy
			if (mabd->name) delete[] mabd->name;
			mabd->name = new char[strlen(p.name) + 1];
			strcpy(mabd->name, p.name);
			if (mabd->soket) delete[] mabd->soket;
			mabd->soket = new char[strlen(p.soket) + 1];
			strcpy(mabd->soket, p.soket);
			mabd->maxCountRAMUnits = p.maxCountRAMUnits;
			mabd->maxCountSATAunits = p.maxCountSATAunits;
			mabd->minFreq = p.minFreq;
			mabd->maxFreq = p.maxFreq;
			mabd->maxVolume = p.maxVolume;
			mabd->type = p.type;
			//drow
			rect(1, 4, 18, 11, '+');//empty motherboard
			rect(3, 5, 5, 6, 'X');//no cpu
			rect(2, 10, 10, 10, '\\');//no vga
			for (int i = 0; i < 4; i++) {//no RAM
				rect(7 + i * 2, 5, 7 + i * 2, 8, '|');
			}
			for (int i = 0; i < 4; i++) {//no SATA
				rect(21, 2 + i * 3, 28, 3 + i * 3, '0');
			}
			break;//for vPow
		}

	}
	f.close();
}
void Box::list() {
	cout << "Box:\n";
	if (power) cout << *power;
	if (mabd) mabd->list();
}

//Power
Power::Power(const Power& obj) {
	this->name = new char[strlen(obj.name)+1];
	strcpy(this->name, obj.name);
	this->pwr = obj.pwr;
	
}
Power::Power() {
	pwr = 0;
	name = 0;
}
Power::~Power() {
	/*cout << "free Power\n";*/
	
}
ostream& operator<<(ostream& out, const Power& pwr) {
	out << pwr.name << '\t' << pwr.pwr << endl;
	return out;
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
			ofstream f("power.txt", ios::app);
			f << '#' << pwr.name << '^' << pwr.pwr << endl;
			f.close();
			break;
		}
		else if (select == 'c')
			continue;
		break;
	} while (true);


}
//MotherBoard
ostream& operator<<(ostream& out, const MotherBoard& mb) {
	out << mb.name << ' ' << mb.soket << ' ' << mb.maxCountRAMUnits << ' '
		<< mb.maxCountSATAunits << ' ' << mb.minFreq << ' '
		<< mb.maxFreq << ' ' << mb.maxVolume << ' ' << mb.type
		<< endl;
	return out;
}
MotherBoard::MotherBoard() {
	//cout << "new MotherBoard\n";
}
MotherBoard::~MotherBoard() {
	cout << "free MotherBoard\n";
}
void MotherBoard::newMotherBoard() {
	MotherBoard mb;
	char select;
	do {
		//name
		cout << "Input name: ";
		char tmp[256];
		cin.getline(tmp, 255);
		mb.name = new char[strlen(tmp) + 1];
		strcpy(mb.name, tmp);
		//soket
		cout << "Input soket: ";
		cin.getline(tmp, 255);
		mb.soket = new char[strlen(tmp) + 1];
		strcpy(mb.soket, tmp);
		//RAM
		cout << "Input RAM. Set throw space:\n"
			<< "count of DRR units, min freq, "
			<< "max freq, max volume,"
			<< "type (f.e. '3' for DDR3):\n";
		cin >> mb.maxCountRAMUnits >> mb.minFreq
			>> mb.maxFreq >> mb.maxVolume >> mb.type;
		//Other
		cout << "input max count SATA units: ";
		cin >> mb.maxCountSATAunits;
				
		//save or not
		cout << "save to file?\n"
			<< "'y' - yes,\n"
			<< "any char for exit\n"
			<< "'c' - clear,\n"
			<< endl;
		cin >> select;
		char buf[100];
		cin.getline(buf, 99);
		if (select == 'y') {
			ofstream f("mother.txt", ios::app);
			if (f) {
				f << '#' << mb.name << '^' << mb.soket << '^'
				<< mb.maxCountRAMUnits << mb.maxCountSATAunits
				<< mb.minFreq << mb.maxFreq << mb.maxVolume << mb.type;
			}
			f.close();
			break;
		}
		else if (select == 'c')
			continue;
		break;
	} while (true);

}

void MotherBoard::list() {}

//
CPU::~CPU() { cout << "free CPU\n"; }
GPU::~GPU() { cout << "free GPU\n"; }
RAM::~RAM() { cout << "free GPU\n"; }
SATA::~SATA() { cout << "free SATA\n"; }
Drive::~Drive() { cout << "free Drive\n"; }
ROM::~ROM() { cout << "free ROM"; }


