class IntArr 
{
private:
		int _size;			// записываем размер массива
		int *pia; 			// принимаем указатель на массив в конструкторе
public:
		// конструктор класса по умолчанию
		IntArr( int sz = 10 ) // метод вызывается при создании массива 
		{					  // конструктор, не возвращает ничего
			_size = sz;
			pia = new int[_size];
			for (int i = 0; i < _size; i++)
				pia[i] = 0; 
		}// заполняем нулями
		
		
		// конструктор копирования
		IntArr( const IntArr &rhs ){
			_size = rhs._size; 
			pia = new int[_size];
				for (int i = 0; i < _size; i++)
					pia[i] = rhs.pia[i];
		} // заполняем теми же данными
		
		// конструктор создания клона
		IntArr( int size, int* ia ) 
		{
			_size = size; 
			pia = new int[_size];
				for (int i = 0; i < _size; i++)
					pia[i] = ia[i];
		} // заполняем теми же данными
		
		~IntArr() // ПРОВЕРИТЬ
		{
			delete[] pia;	
		}
		
		// согласно моему варианту
		int FindMin();
		int FindMax();
		
		// присваивание массива массиву
		IntArr &operator = (const IntArr &rhs) {
			
			delete[] pia; 					// освобождаем старую память
			_size = rhs._size; 				// меняем размер на размер второго массива
			pia = new int[_size]; 			// выделяем память
			for (int i = 0; i < _size; i++)	// меняем значения 
				pia[i]=rhs.pia[i]; 			
			return *this;					// возвращаем то,что приняли
											// слева от равно
		}
		
		// получаем значение массива по индексу 
		// и заносим значения в массив
		int &operator [] (int index) {
				return pia[index]; 
		}
		
		// возвращем размер
		int GetSize () {
			return _size; 
		}
		
		int GetMin () {
			int min = pia[0]; 
			for ( int i = 1; i < _size; i++ ) {
				if (min > pia[i]) min = pia[i];	
			}
			return min; 
		}
		
		int GetMax () {
			int max = pia[0]; 
			for ( int i = 1; i < _size; i++ ) {
				if (max < pia[i]) max = pia[i];	
			}
			return max; 
		}
		
};

#include <iostream>		// ввод и вывод в терминал 
#include <cstdlib>		// выделение памяти, контроль, итд итп. 	 
#include <string> 		// для работы со строками 
#include <fstream>		// для работы с файлами
#include <cstdio>
#include <limits>

using namespace std;



int main () {
	
	IntArr Array(20);
	
	
	cout << "=============Инициализация=============" << endl;
	// заполняем массив 
	// ДЕМОНСТРАЦИЯ GetSize
	for (int i = 0; i < Array.GetSize() ; i++){
		
		Array[i] = rand() % 500;
		cout << "Значение " << i+1 << " = " << Array[i] << endl;  
		
	} 
	
	cout << "=============Клонирование=============" << endl;
	// ДЕМОНСТРАЦИЯ КЛОНИРОВАНИЯ
	IntArr ArrayClone(Array);
	
	for ( int i = 0; i < ArrayClone.GetSize() ; i++){
		cout << "Значение " << i+1 << " = " << ArrayClone[i] << endl;  
		
	} 
	cout << "=============Минимум и максимум=============" << endl;
	cout << "Введите значения" << endl;
	int ArrayTest[20]; 
	for (int i = 0; i < 20; i++) {
		cin >> ArrayTest[i]; 
	}
	
	IntArr ArrayClone1(20, ArrayTest);
	
	cout << "Минимум" << ArrayClone1.GetMin() << endl;
	cout << "Максимум" << ArrayClone1.GetMax() << endl;
	
	return 0; 
}
