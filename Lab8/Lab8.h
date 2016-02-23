using namespace std;

class basic
{
	protected:
		int _age;
		string _fio;
		int static _counter;
	public:
		// Конструктор
		basic(int age = 0, string fio = "none"): _age(age), _fio(fio) {_counter++;}
		
		// Конструктор копирования
		basic(const basic &rhs): _age(rhs._age), _fio(rhs._fio){_counter++;}
		
		// Виртуальный метод 
		virtual void status() {
			cout << "ФИО: " << _fio << endl;
			cout << "ГОДЫ: " << _age << endl;
			cout << "КЛАСС: basic" << endl;
		}
		
		virtual void status2() {
			cout << "ВСЕГО ОБЪЕКТОВ: " << _counter << endl;
		}
		
		// Напечатать имя
		void printFIO() {
			cout << "ФИО: " << _fio << endl;
		}
		
		// Напечатать годы
		void printAge() {
			cout << "ГОДЫ: " << _age << endl;
		}
		~basic(){_counter--;}
};

class child:public basic
{
	protected:
		int _islearn;
	public:
		child(int age = 1, string fio = "none", int islearn = 0): basic(age, fio), _islearn(islearn){}
		
		child(const child &rhs):basic(rhs), _islearn(rhs._islearn){}
		
		void status(){
			cout << "ФИО: " << _fio << endl;
			cout << "ГОДЫ: " << _age << endl;
			cout << "ВУЗ: " << _islearn << endl;
			cout << "КЛАСС: child" << endl;
		}
		
		void printIslearn(){
			cout << "УЧИТСЯ: " << _islearn << endl;
			
		}
		
		// Напечатать имя
		void printFIO() {
			cout << "ФИО_РЕБЕНКА: " << _fio << endl;
		}
		~child(){}
};

class parent:public basic
{
	protected:
		int _haveChild;
	public:
		parent(int age = 20, string fio = "none", int haveChild = 0):basic(age, fio), _haveChild(haveChild){}
		
		parent(const parent &rhs): basic(rhs), _haveChild(rhs._haveChild){}
		
		virtual void status(){
			cout << "ФИО: " << _fio << endl;
			cout << "ГОДЫ: " << _age << endl;
			cout << "ДЕТИ: " << _haveChild << endl;
			cout << "КЛАСС: parent" << endl;
		}
		
		void printHaveChild(){
			cout << "Дети: " << _haveChild <<endl;
			
		}
		~parent(){}
};
