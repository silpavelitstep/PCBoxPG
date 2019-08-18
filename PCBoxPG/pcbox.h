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
	Power(const Power&);
	Power();
	friend ostream& operator<<(ostream&, const Power&);
};
class CPU :public Unit {
public:
	virtual ~CPU();
	CPU();
	CPU(const CPU&);
	char* soket;
	//RAM support
	int minFreq;//800 - 800MHz
	int maxFreq;//
	int maxVolume;//16 - 16GB
	char type;//'3' - ddr3
	//
	friend ostream& operator<<(ostream&, const CPU&);
	CPU& operator=(const CPU&);
	static void newCPU();
};
class GPU :public Unit {
public:
	virtual ~GPU();
	GPU();
	GPU(const GPU&);
	int memoryVolume;
	int minPower;
	friend ostream& operator<<(ostream&, const GPU&);
	static void newGPU();
};
class RAM :public Unit {
public://data
	int minFreq;//800 - 800MHz
	int maxFreq;//
	int memVolume;//16 - 16GB
	char type;//'3' - ddr3
public://methods
	static void newRAM();
public://staff
	virtual ~RAM();
	RAM();
	RAM(const RAM&);
	friend ostream& operator<<(ostream&, const RAM&);
};
class SATA{
public:
	virtual ~SATA() = 0;//abstract unit
	char typeSataUnit;// s - ssd, h - hdd, r - rom
	string additionInfo;//f.e. ssd or vendor
	string name;
	virtual void inpt();
	virtual void wrt(ofstream f)=0;

	
};
	class Box;
class MotherBoard :public Unit {
public:
	CPU* cpu;
	char* soket;//------f
	GPU* gpu;
	RAM* ram[4];//array
	int curRamUnit;
	int maxCountRAMUnits;//------f
	SATA* sata[4];//array
	int curSATAUnit;
	int maxCountSATAunits;//------f
	//RAM support
	int minFreq;//800 - 800MHz
	int maxFreq;//
	int maxVolume;//16 - 16GB
	char type;//'3' - ddr3
public://methods
	void list();
	void addCPU(Box*);
	void addGPU(Box*);
	void addRAM(Box*);
	static void newMotherBoard();
public://staff
	virtual ~MotherBoard();
	MotherBoard();
	MotherBoard(const MotherBoard&);
	friend ostream& operator<<(ostream&, const MotherBoard&);
};
class Drive : public SATA {//HDD, SSD
public:
	int volume;
	virtual ~Drive();
	static void newDrive(char);
	void inpt() override;
	void wrt(ofstream f) override;
};
class ROM : public SATA {//CD\DVD\BD ROM\RW
public:
	char typeDisk;//'c' -cd, 'd' - dvd+cd, 'b' - BlueRay+dvd+cd
	virtual ~ROM();
	static void newROM(char);
	void inpt() override;
	void wrt(ofstream f) override;
};
class Box{
	friend class MotherBoard;//for box->rect in MotherBoard::addCPU()
public:
	Power* power;
	MotherBoard* mabd;
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

