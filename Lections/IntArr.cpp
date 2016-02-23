// не очень правильный класс для работы с массивами. 

class IntArr {
private:
		int _size;
		int *pia; 
public: 
		// конструктор класса
		IntArr( int sz = 10 ) // метод вызывается при создании массива 
		{					  // конструктор, не возвращает ничего
			_size = sise;
			pia = new int[_size];
			for (int i = 0; i < _size; i++)
				pia[i] = 0; 
		}
		
		// конструктор копирования
		IntArr( const IntArr &rhs )	// 
		{
			_size = rhs._size; 
			pia = new int[_size];
				for (int i = 0; i < _size; i++)
					pia[i] = rhs.pia[i];
		}
		
		// конструктор создания клона
		IntArr( int size, int* ia );		
		~IntArr(); 						// деструктор
		int size(); 
		int min();
		int max();
		int& operator[](int ind);
		IntArr& operator=(const IntArr &rhs)
		{		
		// тут будет много косяков
		// тут используется трюк с выделением одной и той же памяти
		// не корректный код, значения переменных будут те же. 	
			delete[] pia;
			_size = rhs._size;
			pia = new int[_size]; 
			for (int i = 0; i < _size; i++)
				pia[i]=rhs.pia[i]; 
			return *this;
		}
		bool operator == (const IntArr &rhs);
		bool operator != (const IntArr &rhs);
};


// перегрузка функций
// exter "C" позволяет работать с сишными функциями
int 	min ( int 		a, int		b);
double 	min ( double 	a, double 	b);
bool 	min ( bool 		a, bool 	b); 

// эту перегрузку можно заменить шаблоном
template < typename myType > 
myType min (myType a, myType b)
{
	return a < b ? a : b; 
}
