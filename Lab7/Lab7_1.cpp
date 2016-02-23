/*
Нужно:

1. 	Дополнить Lab3 автоматизированным универсальным 
	счётчиком копий (reference counter) 
2. 	Всесторонне продемонстрировать работоспособность.
*/

#include <iostream>		// ввод и вывод в терминал 
#include <cstdlib>		// выделение памяти, контроль, итд итп. 	  
#include <cstdio>
#include <new>          // std::bad_alloc
#include <memory>		// Для интелектуальных указателей

//#include "Lab7.h"

using namespace std;

/* Щаблон для создания интелектуального указателя
 * Функционал: 
 * 1. Создание - удаление
 * 2. При инициализации 
 * */
template<class T> 
class SmartPointer {
private:
	T* ptr; 							// Обычный указатель 

	void init() 						// Вызывается конструкторами
	{
		if (ptr == NULL)
			return;
		if (ptr->isShareable() == false) { 
			ptr = new T(*ptr); 
		}
		ptr->addReference();
	}	
	
public:

	// Конструкторы
	SmartPointer(T* realPointer = 0) 
	: ptr(realPointer) { init(); }
	
	SmartPointer(const SmartPointer &sp)
	: ptr(sp.ptr) { init(); }
	
	// Деструктор
	~SmartPointer() {
		if (ptr)
			ptr->removeReference(); 
		}
	
	SmartPointer& operator = (const SmartPointer &sp)
	{
		// Если они не равны
		if (ptr != sp.ptr) {
			// Меняем значение и проверяем возможность совместного пользования
			T* oldPtr = ptr;
			ptr = sp.ptr;
			init();
			
			// У старой ссылку уменьшаем счетчик
			if (oldPtr) {
				oldPtr->removeReference();
			}
		}
		return *this;
	}

	T* operator -> () const { return ptr; }
	T& operator * () const { return *ptr; }
};

/* Базовый класс счетчика ссылок
 * Хранит колличество ссылок и 
 * флаг возможности совместного использования
 * 
 * Функционал:
 * 1. Создание - уничтожение
 * 2. Добавление или удаление ссылок
 * 3. Изменение флага возможности совместного оиспользования
 * */
class ReferenceCounter {
private:
	int refCount;			// Счетчик ссылок 
	bool shareable; 		// совместное использование
		
public:
	void addReference() { 
		++refCount; 
		cout << "~ +1 ссылка" << endl;  
	}
	
	void removeReference() {
		if (--refCount == 0)
			delete this;
	}
	
	// Сделать объект частным
	void markUnshareable() { shareable = false; }
	
	// возвращает возможность совместного использования
	bool isShareable() const { return shareable; }
	
	// Используется ли совместно? 
	bool isShared() const { return (refCount > 1); }
	
	// Возмврат кол-ва ссылок
	int getRefCount() { return refCount; }

	// Конструкторы
	ReferenceCounter()
	: refCount(0), shareable(true) {}
		
	ReferenceCounter(const ReferenceCounter &rco)
	: refCount(0), shareable(true) {}
	
	// Оператор присваивания не используется вообще
	ReferenceCounter &operator = (const ReferenceCounter &rco) 
	{ return *this; }
	
	// Деструктор 
	~ReferenceCounter() {};
};

/* Класс интелектуального массива
 * Хранит указатель на массив и его размер. 
 * Функционал:
 * 1. Создание - удаление
 * 2. Кланирование - Копирование
 * 3. Вывод размера, максимума, минимума 
 * 4. Вывод в терминал 
 * 5. Сортировака элементов массива. 
 * */

template <typename T> 	// создаем шаблон класса с параметром T 
						// везде где нужно меняем тип данных на T
class IntArr
{
private:
		//int _size;						// Записываем размер массива
		//T *pia; 						// Принимаем указатель 
										// на массив в конструкторе
		static int created; 			// Для подсчета количества 
										// созданных объектов 
		// Структура для хранения данных
		struct ArrayValue : public ReferenceCounter {
			T *data; 			// Значение элемента 
			int sizeArrayValue; // Размер значения
			
			ArrayValue (int size) { 	// Выделение памяти под массив
				if ( (size > 0) && (size > 1000000) ) {
					sizeArrayValue = size; 
					data = new T[sizeArrayValue];
					cout << "~ Массив создан" << endl; 
				}
			}
			
			ArrayValue (int size, const T *arr) { // инициализация массивом
				
				if (size > 0 && size <= 1000000) {
					sizeArrayValue = size;
					data = new T[sizeArrayValue];
					for (int i = 0; i < sizeArrayValue; i++) {
						data[i] = arr[i];
					}
					cout << "~ Массив создан и заполнен" << endl; 
				}
			} 
			
			// Конструктор
			~ArrayValue() { delete[] data; }
		};
		SmartPointer<ArrayValue> value; // Указатель на значение 
		
public:
		class myIterator {
		public:
			myIterator(T *itp = 0) 
			: it(itp) {}

			myIterator& operator = (const myIterator &mi)
			{
				if (this == &mi)
					return *this;
				it = mi.it; 
				return *this;
			}

			myIterator& operator ++()
			{
				++it;
				return *this;
			}

			bool operator != (const myIterator &mi)
			{
				if (it == mi.it)
					return false;
				return true;
			}

			myIterator& operator - (int a)
			{
				it = it - a;
				return *this;
			}

			T operator *() { return *it; }

			T* operator ->() { return it; }

		private:
			T* it;
		};
		
		void getRefCountArray () { 
			cout << "Всего копий: " << value->getRefCount() << endl;
		}
		
		myIterator begin() { return myIterator(value->data); }
		
		myIterator end() { return myIterator(value->data + value->sizeArrayValue); }
		
		IntArr ( int sz = 10)
		: value(new ArrayValue(sz) ) { created++; }
			
		IntArr(const IntArr &rhs)
		: value(rhs.value) { created++; }
		
		// Инициализирует встроенным массивом
		IntArr(int size, T *arr)
		: value(new ArrayValue(size, arr)) { created++; }
			
		~IntArr()
		{}
		
		// возвращем размер
		int GetSize () { return value->sizeArrayValue; }
		
		int GetCount() { return created; }
		
		// только для чтения 
		T& operator [] (int index) const
		{
			if (index >= 0 && index < value->sizeArrayValue) {
				return value->data[index];
			} 
			cout << "Ссылок на этот элемент: " << value << endl;
		}
		
		void ShowData () {
			if (value->sizeArrayValue == 0) {
				cout << "~ Массив пустой" << endl; 
			} else {
				short int iter = 0; 
				for (int idx = 0; idx < value->sizeArrayValue; idx++) {
					if (value->sizeArrayValue < 10) {
						cout << iter << ") " << value->data[idx] << endl;
						iter++;
					} else {
						if ((value->data[idx] / 100) >= 1) 
							cout << value->data[idx] << " "; 	
						else if ((value->data[idx] / 10) < 1)
							cout << value->data[idx] << "   ";
						else {
							cout << value->data[idx] << "  ";
						}
						if (((idx + 1)%5 == 0) && (idx != 0)) {
							cout << endl; 
						}	
					}
				} 
				cout 	<< "~ Всего элементов в массиве: " 
						<< value->sizeArrayValue << endl;
				cout 	<< value->getRefCount(); 
			}
		}

		// Для записи, использование копирование при записи
		T& operator [] (int index)
		{
			if (index >= 0 && index < value->sizeArrayValue) {
				if (value->isShared()) {
					value = new ArrayValue(value->sizeArrayValue, value->data); 
				}
				value->markUnshareable();
				return value->data[index];
			} else 	
				throw 1;
		}

		bool operator == (const IntArr &r)
		{
			if (value->sizeArrayValue != r.value->sizeArrayValue) {
				return false;
			}
			for (int i = 0; i < value->sizeArrayValue; i++) {
				if (value->data[i] != r.value->data[i]) {
					return false;
				}
			}
			return true;
		}

		bool operator != (const IntArr &r)
		{
			if (value->sizeArrayValue != r.value->sizeArrayValue) {
				return true;
			}
			for (int i = 0; i < value->sizeArrayValue; i++) {
				if (value->data[i] != r.value->data[i]) {
					return true;
				}
			}
			return false;
		}

		// Присваиваются только смартпоинтеры
		IntArr& operator = (const IntArr &r) 
		{
			// Проверка на самоприсваивание
			if (this == &r) 
				return *this;
		
			value = r.value;
			return *this;
		}

		friend ostream& operator << (ostream &os, IntArr &ar)
		{
			for (int i = 0; i < ar.value->sizeArrayValue; i++) {
				os << ar.value->data[i] << " ";
				// Если произошла ошибка вывода
				if (!os.good()) throw 6;
			}
			return os;
		}

		friend istream& operator >> (istream &is, IntArr &ar)
		{
				if (ar.value->isShared()) { // если на значение указывает больше 1 объекта 
					// Ссылка сама удаляется если была последней 
					ar.value = new ArrayValue(ar.value->sizeArrayValue, ar.value->data); 
				}
				for (int i = 0; i < ar.value->sizeArrayValue; i++) {
					is >> ar.value->data[i];
					if (!is.good()) throw 5;
				}
			return is;
		}
};

// Описание статической переменной класса
template<typename T>
int IntArr<T>:: created;


void CheckTemplate ();
void CheckChanges ();

int main(int argc, char **argv)
{
	try { 
		// Проверяем работоспособность кода после изменений
		CheckTemplate(); 
	}
	
	catch (int message) {
		if (message == 0)
			cout << "~ Ошибка 1" << endl; 
		
	}
	catch(...) { 
		cerr << "~ Unknown error" << endl;
		exit(7);
	}
	
	return 0;
}

void CheckTemplate () {
	
	cout << "Тестирование шаблона класса" << endl; 
	unsigned int size = 0;
	
	// Ввод числа с проверкой
	std::ios::iostate state;
	do {
		int temp; 
        std::cout << "Введите размер массива: ";
        std::cin >> temp;
        if (temp >= 1) {
			state = std::cin.rdstate();
			if (state != std::ios::goodbit) {
				std::cout << "~ Ошибка ввода" << std::endl;
				std::cin.clear(std::ios::goodbit);
				std::cin.ignore(65535, '\n');
			}
		} else {
			std::cout << "~ Ошибка ввода" << std::endl;
			std::cin.clear(std::ios::goodbit);
			std::cin.ignore(65535, '\n');
		}
		size = temp;
	} while (state != std::ios::goodbit);
    std::cout << "~ Вы ввели: " << size << endl;
    
    // Создаем массив размерностью size для заполнения
    int temp[size];
    for (unsigned int idx = 0; idx < size; ++idx) {
		cout << idx << ") ";
		cin >> temp[idx];
	}
	IntArr<int> Arr(size, temp); 
	Arr.ShowData(); 
	
	//cout << "\t" << Arr[0].getRefCount(); << endl; 
	
	IntArr<int> :: myIterator myIt = Arr.begin();
		for ( myIt = Arr.begin(); myIt != Arr.end(); ++myIt) {
			cout << *myIt << endl;
		}
	IntArr<int> Arr1(Arr); 
	//IntArr<int> Arr2(size, temp);
	Arr1.getRefCountArray(); 
	cout << "~ Массив протестирован" << endl;
}

void CheckChanges () {
}



