#include <iostream>		// ввод и вывод в терминал 
#include <cstdlib>		// выделение памяти, контроль, итд итп. 	  
#include <cstdio>
#include <new>          // std::bad_alloc

using namespace std;

template <typename T> 	// создаем шаблон класса с параметром T 
						// везде где нужно меняем тип данных на T
class IntArr
{
private:
		int _size;		// записываем размер массива
		T *pia; 		// принимаем указатель на массив в конструкторе
		
public:
		// конструктор класса по умолчанию
		IntArr( int sz = 10 ) // метод вызывается при создании массива 
		{					  // конструктор, не возвращает ничего
			try { if (sz > 1000000) throw 1; }
			catch(int a){
			if (a == 1){		
				_size = 50;
				pia = new T[_size];
				for (int i = 0; i < _size; i++)
					pia[i] = 0;
				}
				return;	
			}
			_size = sz;
			try { pia = new T[_size]; }
			catch (std::bad_alloc& ba) 
			{ std::cerr << "bad_alloc caught: " << ba.what() << '\n'; }
			for (int i = 0; i < _size; i++)
				pia[i] = 0;
		}// заполняем нулями
		
		// конструктор копирования
		IntArr( const IntArr &rhs ){
			_size = rhs._size;
			
			try { if (_size > 1000000) throw 1; } 
			catch(int a){
				if (a == 1)
					_size = 50; 
			}
			try { pia = new T[_size]; }
			catch (std::bad_alloc& ba) 
			{ std::cerr << "bad_alloc caught: " << ba.what() << '\n'; }
				for (int i = 0; i < _size; i++)
					pia[i] = rhs.pia[i];
		} // заполняем теми же данными
		
		// конструктор создания клона
		IntArr( int size, T* ia ) 
		{
			_size = size;
			try { if (_size > 1000000) throw 1; } 
			catch(int a)
			{ if (a == 1) _size = 50; } 
			try { pia = new T[_size]; }
			catch (std::bad_alloc& ba) 
			{ std::cerr << "bad_alloc caught: " << ba.what() << '\n'; }
				for (int i = 0; i < _size; i++)
					pia[i] = ia[i];
		} // заполняем теми же данными
		
		// деструктор
		~IntArr() { delete[] pia; }
		
		// возвращем размер
		int GetSize () { return _size; }
		
		// получение минимума
		T GetMin () {
			T min = pia[0]; 
			for ( int i = 1; i < _size; i++ ) {
				if (min > pia[i]) min = pia[i];	
			}
			return min; 
		}
		
		// получение максимума
		T GetMax () {
			T max = pia[0]; 
			for ( int i = 1; i < _size; i++ ) {
				if (max < pia[i]) max = pia[i];	
			}
			return max; 
		}
		
		// вывод данных в терминал. 
		void ShowData() {
			for (int i = 0; i < _size; i++) {
				cout << pia[i] << "  "; 
				if (((i + 1)%5 == 0) && (i != 0)) {
					cout << "\n"; 
				}
			}
			cout << endl; 
		}
		
		// Сортировка массива методом выбора
		// если передана 1 - от меньшего к большему
		// если 0 - от большего к меньшему
		void Sort(bool a) {
			if (a == 1) {
			for (int repeat_counter = 0; repeat_counter < _size; repeat_counter++)
			{
				int temp = pia[0]; 
				for (int element_counter = repeat_counter + 1; element_counter < _size; element_counter++)
				{
					if (pia[repeat_counter] > pia[element_counter])
					{
						temp = pia[repeat_counter];
						pia[repeat_counter] = pia[element_counter];
						pia[element_counter] = temp;
					}
				}
			}
			} else {
				for (int repeat_counter = 0; repeat_counter < _size; repeat_counter++)
				{
					int temp = pia[0]; 
					for (int element_counter = repeat_counter + 1; element_counter < _size; element_counter++)
					{
						if (pia[repeat_counter] < pia[element_counter])
						{
							temp = pia[repeat_counter];
							pia[repeat_counter] = pia[element_counter];
							pia[element_counter] = temp;
						}
					}
				}
			}
		}
		
		T &operator [] (int index) {
			try 
			{
				if (index > _size)
					throw 1; 
				if (index < 0)	
					throw 2; 
			}
			catch(int a)
			{
				if (a == 1)
					return pia[_size-1];
				if (a == 2)
					return pia[0]; 
			}
			return pia[index]; 
		}
		
		T &operator == (const IntArr &rhs) {
			if (_size != rhs._size) {
				return 0; 
			}
			for (int i = 0 ; i < _size ; i++) {
				if (pia[i] != rhs[i]){
					return 0; 
				} else return 1;
			} 		 
		}
		
		// присваивание массива массиву
		IntArr &operator = (const IntArr &rhs) {
			
			// проверка на разный размер массива
			try { if (_size != rhs._size) throw 1; } 
			catch(int a){ if (a == 1) cout << "Warning! Массивы не совпадают по размеру" << endl; }
			
			delete[] pia; 					// освобождаем старую память
			_size = rhs._size; 				// меняем размер на размер второго массива
			pia = new T[_size]; 			// выделяем память
			for (int i = 0; i < _size; i++)	// меняем значения 
				pia[i]=rhs.pia[i]; 			
			return *this;					// возвращаем то,что приняли
		}									// слева от равно
		
		bool &operator!= (IntArr &array) {
			if (_size != array.GetSize()) { return 0; } 
			else {
				for (int i = 0; i < _size; i++ ){
					if (pia[i] != array[i])
						return 0;
				}
			}
			return 1;
		}
		
};

void IntCheck () {
	// ввод инта
	IntArr <int> Array(20);		
	for (int i = 0; i < 20; i++) {
		cout << i + 1 << ") ";
		for (;;) {
			cin >> Array[i];
			if (cin.fail())
			{// на случай неверного ввода	
				cout << "Не записалось, повторите." << endl;
				cin.clear();
				char c;
				cin >> c;
			} else {
				break;
			}
		}
		}
	cout << "================================" << endl;
	cout << "Минимальный элемент: " << Array.GetMin() << endl;
	cout << "Максимальный элемент: " << Array.GetMax() << endl;
	cout << "Размер массива: " << Array.GetSize() << endl;
	cout << "Массив до копирования" << endl;  
	Array.ShowData (); 
	cout << "Массив после копирования" << endl; 
	int temp = rand() % 20; 
	IntArr <int> Array2(temp);
	for (int i = 0; i < temp; i++) {
		Array2[i] = rand() % 500;
	}
	Array = Array2; 
	Array.ShowData(); 
	
	cout << "================================" << endl;
	cout << "Минимальный элемент: " << Array.GetMin() << endl;
	cout << "Максимальный элемент: " << Array.GetMax() << endl;
	cout << "Размер массива: " << Array.GetSize() << endl;
	
	cout << "При попытке Выхода за пределы массива при доступе к его элементам." << endl;
	temp = Array[100]; 
	cout << "Если индекс больше размера массива - последний  " << temp << endl; 
	temp = Array[-1]; 
	cout << "Если индекс меньше размера массива - первый  " << temp << endl;
	
	cout << "Если массив слишком большой,\nто конструктор не даст создать его,\nс размером больше 50"<< endl;
	IntArr <int> Array3(1000001);
	for (int i = 0; i < 1000001; i++) {
		Array3[i] = rand() % 500;
	}
	Array3.ShowData();
	cout << "Отсортируем"<< endl;
	Array3.Sort(1);
	Array3.ShowData();
	cout << "Отсортируем в обратную сторону"<< endl;
	Array3.Sort(0);
	Array3.ShowData();
}



void CharCheck () {
	
	IntArr <char> Array(20);
	for (int i = 0; i < 20; i++) {
		cout << i + 1 << ") ";
		cin >> Array[i]; 
	}
	cout << "Минимум  " << Array.GetMin() << endl;
	cout << "Максимум  " << Array.GetMax() << endl;	
	cout << "Размер  " << Array.GetSize() << endl;
	Array.ShowData();
}

void FloatCheck () {
	IntArr <float> Array(20);
	for (int i = 0; i < 20; i++) {
		cout << i + 1 << ") ";
		for (;;) {
			cin >> Array[i];
			if (cin.fail())
			{// на случай неверного ввода	
				cout << "Не записалось, повторите." << endl;
				cin.clear();
				char c;
				cin >> c;
			} else {
				break;
			}
		}
	}
	cout << "Минимум  " << Array.GetMin() << endl;
	cout << "Максимум  " << Array.GetMax() << endl;
	cout << "Размер  " << Array.GetSize() << endl;
	Array.ShowData();
}

void DoubleCheck () {
	IntArr <double> Array(20);
	for (int i = 0; i < 20; i++) {
		cout << i + 1 << ") ";
		for (;;) {
			cin >> Array[i];
			if (cin.fail())
			{// на случай неверного ввода
				cout << "Не записалось, повторите." << endl;
				cin.clear();
				char c;
				cin >> c;
			} else {
				break;
			}
		}
	}
	cout << "Минимум  " << Array.GetMin() << endl;
	cout << "Максимум  " << Array.GetMax() << endl;
	cout << "Размер  " << Array.GetSize() << endl; 
	Array.ShowData();
}


int main () {
while (true){
	
	// ввод данных
	cout << "=======НАЧАЛО======" << endl; 
	cout << "Какой тип данных?" << " 1 - int" << " 2 - char" 
								<< " 3 - float" << " 4 - double" << endl;
	int variable = 0; 
	cin >> variable;
	if (cin.fail())
	{
		cin.clear();
		char c;
		cin >> c;
	} 
	cin.clear();
	
	// проверка ввода
	for ( ; ; ) {
	    if ((variable < 1) || (variable > 4)) {
			cout << "Не правильный ввод" << endl; 
			cin >> variable;
			if (cin.fail())
			{
				cin.clear();
				char c;
				cin >> c;
			} 
			cin.clear(); 
		} else {
		break; 
		}
	}
	
	cout << "Введите значения" << endl;
	// выбор варианта
	switch (variable)
	{
		case 1: { IntCheck (); break; }
		case 2: { CharCheck (); break; }	
		case 3: { FloatCheck(); break; }
		case 4: { DoubleCheck (); break; }
	}
}
	return 0;
}
