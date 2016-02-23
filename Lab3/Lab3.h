template <typename T> 	// создаем шаблон класса с параметром T встроенного типа
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
			_size = sz;
			pia = new T[_size];
			for (int i = 0; i < _size; i++)
				pia[i] = 0;
		}// заполняем нулями
		
		
		// конструктор копирования
		IntArr( const IntArr &rhs ){
			_size = rhs._size; 
			pia = new T[_size];
				for (int i = 0; i < _size; i++)
					pia[i] = rhs.pia[i];
		} // заполняем теми же данными
		
		// конструктор создания клона
		IntArr( int size, T* ia ) 
		{
			_size = size; 
			pia = new T[_size];
				for (int i = 0; i < _size; i++)
					pia[i] = ia[i];
		} // заполняем теми же данными
		
		~IntArr() // ПРОВЕРИТЬ
		{
			delete[] pia;	
		}
		
		// присваивание массива массиву
		IntArr &operator = (const IntArr &rhs) {
			
			delete[] pia; 					// освобождаем старую память
			_size = rhs._size; 				// меняем размер на размер второго массива
			pia = new T[_size]; 			// выделяем память
			for (int i = 0; i < _size; i++)	// меняем значения 
				pia[i]=rhs.pia[i]; 			
			return *this;					// возвращаем то,что приняли
											// слева от равно
		}
		// возвращем размер
		int GetSize () {
			return _size; 
		}
		
		T GetMin () {
			T min = pia[0]; 
			for ( int i = 1; i < _size; i++ ) {
				if (min > pia[i]) min = pia[i];	
			}
			return min; 
		}
		
		T GetMax () {
			T max = pia[0]; 
			for ( int i = 1; i < _size; i++ ) {
				if (max < pia[i]) max = pia[i];	
			}
			return max; 
		}
		
////////////////////OPERATORS

		T &operator [] (int index) {	
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
		
		T &operator= (IntArr &array) {
			delete [] pia; 
			
			
		}
		
};
