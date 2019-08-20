#include <iostream>
#include "pcbox.h"
#include <fstream>
using namespace std;
class A {
public:
	string str;
	int i;
	char tp;
	virtual string print() const { return ""; };
	friend ostream& operator<<(ostream&, const A&);
};
ostream& operator<<(ostream& out, const A& obj) {
	out << obj.tp << ' ' << obj.str << ' '
		<< obj.i <<' '<< obj.print();
	return out;
}
void test() {
	A aout, ain;
	aout.str = "test string";
	aout.i = 10;
	aout.tp = 'y';
	//write
	ofstream f("test.txt", ios::binary);
	f.write(&aout.tp, 1);//type
	int lenght= aout.str.length();//take namelen
	f.write((char*)& lenght, sizeof(int));//namelen
	f.write(aout.str.c_str(), lenght);//name
	f.write((char*)& aout.i, sizeof(int));
	f.close();
	//read
	ifstream in("test.txt",ios::binary);
	in.read(&ain.tp, 1);
	char ch[500];
	in.read((char*)& lenght, sizeof(int));
	in.read(ch, lenght);
	ch[lenght] = '\0';
	ain.str = ch;
	in.read((char*)& ain.i, sizeof(int));
	//show
	cout << aout << endl;
	cout << ain << endl;
	f.close();
	system("pause");
}
int main() {
	Box bx;
	//bx.menu();
	test();
	//system("pause");
	return 0;
}