#include <iostream>		

/*  Iterator - Cursor
 * Дает возможность последовательно обойти все элементы составного
 * объекта, не раскрывая его внутреннего представления.
*/

using namespace std;

// Шаблон массива
template <typename ArrayType>
class templateArray {
	private:
		ArrayType *array;
		int arraySize;
	public:
		
		// Контрукторы и деструктор
		templateArray(int size = 5) {
			array = new ArrayType[size];
			arraySize = size;
		}
		templateArray(int size, ArrayType array[]) {
			arraySize = size;
			this->array = new ArrayType[size];
			for (int i = 0; i < size; ++i) {
				this->array[i] = array[i];
			}
		}
		~templateArray() { delete[] array; }

		// Перегружаем вывод 
		friend ostream& operator << (ostream &os, templateArray &obj) {
			for (int i = 0; i < obj.arraySize; ++i) {
				os << obj.array[i] << " ";
			}
			os << endl;
			return os;
		}
		
		
		class MyIterator {
			private:
				ArrayType *ptr; 
			public:
				MyIterator(ArrayType *pointer = NULL) 
				{ ptr = pointer; }

				MyIterator& operator = (const MyIterator &rvalue)
				{
					if (this == &rvalue)
						return *this;
					ptr = rvalue.ptr;

					return *this;
				}
				MyIterator& operator ++()
				{
					++ptr;
					return *this;
				}
				
				MyIterator& operator --()
				{
					--ptr;
					return *this;
				} 

				bool operator != (const MyIterator &rvalue)
				{
					if (ptr == rvalue.ptr)
						return false;
					else
						return true;
				}
				
				bool operator == (const MyIterator &rvalue)
				{
					if (ptr == rvalue.ptr)
						return true;
					else
						return false;
				}
				
				ArrayType& operator *()  { return *ptr; }
				ArrayType* operator ->() { return ptr; }
		};		
		
		// Возвращают итераторы начала и конца
		MyIterator begin() { return MyIterator(array); }
		MyIterator end() { return MyIterator(array + arraySize); } 	
};


int main()
{
	int arr[5] = {55, 22, 111, 33, 666};
	templateArray<int> a(5, arr);
	cout << a;

	//templateArray<int> :: MyIterator it1;
	for (auto it = a.begin(); it != a.end(); ++it) {
		if (*it == 33)
			(*it) = 999;
		if (it == a.begin()) 
			cout << "Прямой обход" << endl;  
		cout << *(it) << " ";
		if (it == (--a.end())) 
			cout << endl; 
	}
	//templateArray<int> :: MyIterator it1;
	for (auto it = --a.end(); it != a.begin(); --it) {
		if (*it == 22)
			(*it) = 888;
		if (it == --a.end()) 
			cout << "Обратный обход" << endl;
		cout << *(it) << " ";
		if (it == --a.begin()) 
			cout << endl;
	}

	char arr2[5] = {'1', '2', '3', '4', '5'};
	templateArray<char> a2(5, arr2);
	cout << "\n" << a2;
	
	//templateArray<char> :: MyIterator it2;
	for (auto it2 = a2.begin(); it2 != a2.end(); ++it2) {
		if (*it2 == '3' ) 
			(*it2) = 'X';
	}
	cout << a2; 

	return 0;
}
