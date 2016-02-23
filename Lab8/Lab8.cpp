#include<iostream>
#include<vector>
#include"Lab8.h"

using namespace std;

void StudentName ();
void CheckClass (vector<basic *> &object); 
void CheckClassBasic (vector<basic *> &object);

int basic::_counter = 0; 

int main()
{
	StudentName(); 
	
	// Создаем вектор с указателями на объекты базового класса
	vector<basic *> vector;
	vector.push_back(new basic(22, "Иван Иван Иван"));
	vector.push_back(new child(4, "Сергей Сергей Сергей", 1));
	vector.push_back(new parent(65, "Денис Денис Денис", 1));
	// Итератор для обхода
	//vector<basic *>::iterator it = v.begin();
	
	CheckClass (vector); 
	CheckClassBasic (vector);
	// Напечатать имя
	vector[1]->printFIO();
	vector[1]->status2();
	return 0;
}

// Индентификатор студента
void StudentName () {
	cout 	<< "\t##################\n"
			<< "\t#Лабораторная №8 #\n"
			<< "\t#Горлова Романа  #\n"
			<< "\t#ИУ-423          #\n"
			<< "\t##################\n"
			<< endl; 
}

void CheckClass (vector<basic *> &object) {
	// Выводим классы 
	cout << "========Метод вывода статуса" << endl;
	int idx = 0;  
	vector<basic *>::iterator it = object.begin();
	for(it = object.begin(); it != object.end(); it++)
	{
		cout << "\tЗапись " << idx <<  endl;
		(*it)->status();
		idx++; 
	}
} 

void CheckClassBasic (vector<basic *> &object) {
	// Выводим из Базового
	cout << "========Вызов метода статуса из basic" << endl; 
	int idx = 0; 
	vector<basic *>::iterator it = object.begin();
	for(it = object.begin(); it != object.end(); it++)
	{
		cout << "\tЗапись" << idx << endl;   
		(*it)->basic::status();
		idx++; 
	}
}
