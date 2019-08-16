#pragma once
#include <iostream>
using namespace std;
#ifndef PCBOX_H
#define PCBOX_H
class Unit {
public:
	char* name;
	virtual ~Unit()=0;
	
};
class Power :public Unit {
public:
	int pwr;//watt
	virtual ~Power();
public:
	static void newPower();
	static void takePower();
	Power(const Power&);
	Power();
	friend ostream& operator<<(ostream&, const Power&);
};
class CPU :public Unit {
public:
	virtual ~CPU();
	string soket;
	//RAM support
	int minFreq;//800 - 800MHz
	int maxFreq;//
	int maxVolume;//16 - 16GB
	char type;//'3' - ddr3
};
class GPU :public Unit {
public:
	virtual ~GPU();
	int memoryVolume;
};
class RAM :public Unit {
public:
	int minFreq;//800 - 800MHz
	int maxFreq;//
	int memVolume;//16 - 16GB
	char type;//'3' - ddr3
	virtual ~RAM();
};
class SATA :public Unit {
public:
	virtual ~SATA() = 0;//abstract unit
	char typeSata;// '2' - sata2
};
class MotherBoard :public Unit {
public:
	virtual ~MotherBoard();
	CPU* cpu;
	char* soket;
	GPU* gpu;
	RAM* ram[4];
	int curRamUnit = 0;
	SATA* sata[6];
	int curSATAUnit = 0;
	//RAM support
	int minFreq;//800 - 800MHz
	int maxFreq;//
	int maxVolume;//16 - 16GB
	char type;//'3' - ddr3
public:
	void list();
};

class Drive : public SATA {//HDD, SSD
	int volume;
	char typeDrive;//'h' - hdd, 's' - ssd
	virtual ~Drive();
};
class ROM : public SATA {//CD\DVD\BD ROM\RW
	char typeDisk;//'c' -cd, 'd' - dvd+cd, 'b' - BlueRay+dvd+cd
	virtual ~ROM();
};
class Box{
public:
	Power* power;
	MotherBoard* mb;
	char maket[13][30];
public:
	virtual ~Box();
public:
	void clear();
	void show();
	void menu();
	void list();
private:
	void newUnit();
	void addUnitToMaket();
	void addPower();
	void addMotherBoard();
	void delUnitFromMaket();
	void rect(int, int, int, int, char);
	
};

#endif //! PCBOX_H

