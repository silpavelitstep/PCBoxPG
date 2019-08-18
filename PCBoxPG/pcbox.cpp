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
	rect(1, 1, 8, 2, 'x');//no power
	rect(1,4,18,11,'x');//no motherboard
	
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
	case 'g':GPU::newGPU(); break;
	case 'c':CPU::newCPU(); break;
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
			cout << pwr<<endl;
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
	case 'p':addPower(); break;
	case 'm':addMotherBoard(); break;
	}
	if (mabd) switch (select){
	case 'g':mabd->addGPU(this); break;
	case 'c':mabd->addCPU(this); break;
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
	case 'm':
		delete mabd;
		mabd = 0;
		clear();//clear all
		if(power)
			rect(1, 1, 8, 2, '+');//add power
		break;
	}
	if (mabd) switch (select) {
	case 'g':
		delete mabd->gpu;
		mabd->gpu = 0;
		rect(2, 10, 10, 10, '\\');
		break;
	case 'c':
		delete mabd->cpu;
		mabd->cpu = 0;
		rect(3, 5, 5, 6, 'X');
		break;
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
		f >> mb.maxCountRAMUnits;
		f >> mb.maxCountSATAunits;
		f >> mb.minFreq;
		f >> mb.maxFreq;
		f >> mb.maxVolume;
		f >> mb.type;
		if (strcmp(mb.name, "") != 0) {
			vPow.push_back(mb);
			cout << mb << endl;
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
	if (power) cout << *power << endl;
	if (mabd) mabd->list();
	cout << endl;
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
	out << pwr.name << '\t' << pwr.pwr<<" Watt";
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
		<< mb.maxFreq << ' ' << mb.maxVolume << "GB DDR" << mb.type;
	return out;
}
MotherBoard::MotherBoard() {
	curRamUnit = curSATAUnit = 0;
	cpu = 0;
	gpu = 0;
	
	//cout << "new MotherBoard\n";
}
MotherBoard::MotherBoard(const MotherBoard& obj) {
	this->name = new char[strlen(obj.name) + 1];
	strcpy(this->name, obj.name);
	this->soket = new char[strlen(obj.soket) + 1];
	strcpy(this->soket, obj.soket);
	cpu = 0;
	gpu = 0;
	maxCountRAMUnits = obj.maxCountRAMUnits;
	maxCountSATAunits = obj.maxCountSATAunits;
	minFreq = obj.minFreq;
	maxFreq = obj.maxFreq;
	maxVolume = obj.maxVolume;
	type = obj.type;
	
}
MotherBoard::~MotherBoard() {
	//cout << "free MotherBoard\n";
	delete cpu;
	if (soket) delete[] soket;
	delete gpu;
	/*
	int i;
	for (i = 0; i < 4; i++)
		if (ram[i]) delete ram[i];
	for (i = 0; i < 4; i++)
		if (sata[i]) delete sata[i];
	*/

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
					<< mb.maxCountRAMUnits <<' '<< mb.maxCountSATAunits<<' '
					<< mb.minFreq <<' '<< mb.maxFreq<<' ' << mb.maxVolume<<' '
					<< mb.type << endl;
			}
			f.close();
			break;
		}
		else if (select == 'c')
			continue;
		break;
	} while (true);

}
void MotherBoard::list() {
	cout << "MotherBoard: " << *this << endl;
	if (this->cpu) cout << "CPU: " << *cpu << endl;;
	if (this->gpu) cout<<"GPU: "<<*gpu<<endl;
	int i;
	for (i = 0; i < curRamUnit; i++)
		cout << (*ram[i]) << endl;
	/*
	for (i = 0; i < curSATAUnit; i++)
		cout << (*sata[i]) << endl;
		*/
}
void MotherBoard::addCPU(Box* box) {
	system("CLS");
	ifstream f("cpu.txt");
	char bf;
	CPU cput;
	cput.name = new char[256];
	cput.soket = new char[256];
	vector<CPU> vPow;
	//load from file to vector
	while (f) {
		f >> bf;//#
		f.getline(cput.name, 255, '^');
		f.getline(cput.soket, 255, '^');
		f >> cput.minFreq;
		f >> cput.maxFreq;
		f >> cput.maxVolume;
		f >> cput.type;
		if (strcmp(cput.name, "") != 0) {
			vPow.push_back(cput);
			cout << cput << endl;
		}
	}
	//select name
	cout << "check name:";
	cin.getline(cput.name, 255);
	for (CPU p : vPow) {
		//find
		if (strcmp(p.name, cput.name) == 0) {
			if (cpu == 0)
				cpu = new CPU();
			//check soket (fisical key)
			if (strcmp(this->soket, p.soket) != 0) {
				cout << "Incorrect soket!\n";
				break;
			}
			//copy
			if (cpu->name) delete[] cpu->name;
			cpu->name = new char[strlen(p.name) + 1];
			strcpy(cpu->name, p.name);
			if (cpu->soket) delete[] cpu->soket;
			cpu->soket = new char[strlen(p.soket) + 1];
			strcpy(cpu->soket, p.soket);
			cpu->minFreq = p.minFreq;
			cpu->maxFreq = p.maxFreq;
			cpu->maxVolume = p.maxVolume;
			cpu->type = p.type;
			//drow
			box->rect(3, 5, 5, 6, '1');
			//end 
			break;//for vPow
		}

	}
	f.close();
}
void MotherBoard::addGPU(Box* box) {
	system("CLS");
	ifstream f("gpu.txt");
	char bf;
	GPU gtmp;
	gtmp.name = new char[256];
	vector<GPU> vPow;
	//load from file to vector
	while (f) {
		f >> bf;//#
		f.getline(gtmp.name, 255, '^');
		f >> gtmp.memoryVolume >> gtmp.minPower;
		if (strcmp(gtmp.name, "") != 0) {
			vPow.push_back(gtmp);
			cout << gtmp << endl;
		}
	}
	//select name
	cout << "check name:";
	cin.getline(gtmp.name, 255);
	for (GPU p : vPow) {
		//find
		if (strcmp(p.name, gtmp.name) == 0) {
			if (gpu == 0)
				gpu = new GPU();
			//copy
			if (gpu->name) delete[] gpu->name;
			gpu->name = new char[strlen(p.name) + 1];
			strcpy(gpu->name, p.name);
			gpu->memoryVolume = p.memoryVolume;
			gpu->minPower = p.minPower;
			//drow
			box->rect(2, 10, 10, 10, '1');
			//end 
			break;//for vPow
		}

	}
	f.close();
}
//CPU
CPU::~CPU() {
	//cout << "free CPU\n";
	if (soket) delete[] soket;
}
CPU::CPU() {
	name = 0;
	soket = 0;
}
CPU::CPU(const CPU& obj) {
	name = new char[strlen(obj.name) + 1];
	strcpy(name, obj.name);
	soket = new char[strlen(obj.soket) + 1];
	strcpy(soket, obj.soket);
	minFreq = obj.minFreq;
	maxFreq = obj.maxFreq;
	maxVolume = obj.maxVolume;
	type = obj.type;

}
ostream& operator<<(ostream& out, const CPU& cpu) {
	out << cpu.name << ' ' << cpu.soket << ' ' << cpu.minFreq << ' '
		<< cpu.maxFreq << ' ' << cpu.maxVolume << "GB DDR" << cpu.type;
	return out;
}
CPU& CPU::operator=(const CPU& obj) {
	name = new char[strlen(obj.name) + 1];
	strcpy(name, obj.name);
	soket = new char[strlen(obj.soket) + 1];
	strcpy(soket, obj.soket);
	minFreq = obj.minFreq;
	maxFreq = obj.maxFreq;
	maxVolume = obj.maxVolume;
	type = obj.type;
	return *this;
}
void CPU::newCPU() {
	CPU cpu;
	char select;
	do {
		//name
		cout << "Input name: ";
		char tmp[256];
		cin.getline(tmp, 255);
		cpu.name = new char[strlen(tmp) + 1];
		strcpy(cpu.name, tmp);
		//soket
		cout << "Input soket: ";
		cin.getline(tmp, 255);
		cpu.soket = new char[strlen(tmp) + 1];
		strcpy(cpu.soket, tmp);
		//RAM
		cout << "Input RAM. Set throw space:\n"
			<<" min freq, "
			<< "max freq, max volume,"
			<< "type (f.e. '3' for DDR3):\n";
		cin >>  cpu.minFreq>> cpu.maxFreq 
			>> cpu.maxVolume >> cpu.type;
		
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
			ofstream f("cpu.txt", ios::app);
			if (f) {
				f << '#' << cpu.name << '^' << cpu.soket << '^'
					<< cpu.minFreq << ' ' << cpu.maxFreq << ' '
					<< cpu.maxVolume << ' '<< cpu.type << endl;
			}
			f.close();
			break;
		}
		else if (select == 'c')
			continue;
		break;
	} while (true);
}
//GPU
GPU::~GPU() {/*cout << "free GPU\n";*/ }
GPU::GPU() {
	name = 0;
}
GPU::GPU(const GPU& obj) {
	name = new char[strlen(obj.name)+1];
	strcpy(name,obj.name);
	memoryVolume = obj.memoryVolume;
	minPower = obj.minPower;
}
ostream& operator<<(ostream& out, const GPU& gpu) {
	out << gpu.name << ' ' << gpu.memoryVolume<<"GB";
	return out;
}
void GPU::newGPU() {
	GPU gpu;
	char select;
	do {
		//name
		cout << "Input name: ";
		char tmp[256];
		cin.getline(tmp, 255);
		gpu.name = new char[strlen(tmp) + 1];
		strcpy(gpu.name, tmp);
		//RAM and power
		cout << "Input RAM volume: ";
		cin >> gpu.memoryVolume;
		cout << "Input min power of Power: ";
		cin >> gpu.minPower;
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
			ofstream f("gpu.txt", ios::app);
			if (f) {
				f << '#' << gpu.name << '^'
				<<gpu.memoryVolume<<' '<<gpu.minPower << endl;
			}
			f.close();
			break;
		}
		else if (select == 'c')
			continue;
		break;
	} while (true);
}
//RAM
RAM::~RAM() { cout << "free GPU\n"; }
ostream& operator<<(ostream& out, const RAM& ram) {
	out << ram.name << ' ' << ram.minFreq << ' ' << ram.maxFreq << ' '
		<< ram.memVolume << "GB DDR" << ram.type;
	return out;
}
//SATA
SATA::~SATA() { cout << "free SATA\n"; }
//DRIVE
Drive::~Drive() { cout << "free Drive\n"; }
//ROM
ROM::~ROM() { cout << "free ROM"; }


