#include <iostream>
#include <vector>

/* Наблюдатель - Dependents (подчиненные) - publish-subscribe(издатель подписчик)
 * Определяет между объектами зависимость типа один-ко-многим, так что
 * при изменении состоянии одного объекта все зависящие от него получают
 * извещение и автоматически обновляются.
 * */

using namespace std;

// Базовый класс подписчиков
class SubscriptionBase {
public:
	virtual ~SubscriptionBase() {}
	virtual string get_name_event() { return ""; }
	virtual void call_action() {}
};

// Шаблон наследника базвого класса (для полиморфных вызовов методов)
template<typename ListenType>
class Subscription :public SubscriptionBase {
private:
	string event; 						// Имя события
	ListenType *listener; 				// Указатель на обект, для предупреждения
	
	void (ListenType :: *action) (); 	// Метод вызываемый при событии event
	
	// Переопределяем методы базового класса
	virtual string get_name_event() { return this->event; }
	
	// Вызов метода наблюдателя
	virtual void call_action()
	{
		(this->listener ->* this->action) ();
	}
	
public:
	// в конструкторе принимаем значения
	Subscription(string event, ListenType *listener, void (ListenType :: *action) () )
	{
		this->event = event;			// Имя события
		this->listener = listener;		// Указатель на наблюдателя
		this->action = action;			// Указатель на метод
	}
	
	~Subscription() {}
};


// Диспетчер событий, базовый класс для наблюдаемых
class EventDispatcher {
private:
	// Указатели на подписчиков
	vector <SubscriptionBase*> subscriptions;
public:
	
	template <typename ListenType>
	// Создается подписка на событие и добавляется в вектоп
	void add_listener(string event, ListenType *listener, void (ListenType :: *action) () )
	{
		auto *subscription = new Subscription<ListenType> (event, listener, action);
		subscriptions.push_back(subscription);
	}
	
	//метод, который ищет в векторе подписок переданное название события 
	//и если находит сообщает всем объектам подписанным на него
	void dispatch_event(string event)
	{
		for (auto it = subscriptions.begin(); it != subscriptions.end(); ++it) {
			if ((*it)->get_name_event() == event) 
				(*it)->call_action();
		}
	}
};

// Наблюдемый класс
class A :public EventDispatcher {
public:
	// Отправляет событие
	void event() { dispatch_event("event"); }
};

// Наблюдатель
class B {
public:
	void func() { cout << "Lorem ipsum\n"; }
};

int main()
{
	A *a = new A();
	B *b = new B();

	a->add_listener("event", b, &B :: func);
	a->event();
	
return 0;
}
