#include <iostream>

class Rectangle{
    friend bool operator < (const Rectangle&a, const Rectangle&b);
public:
    std::ostream& print(std::ostream&);
};

struct node {
	node* prev;
	node* next;
	Rectangle* data;
};

class List {
public:
	List();
	~List();
	void append(Rectangle*);
	Rectangle pop(int);
	std::ostream& print(std::ostream& os);
	size_t size();

private:
	node* head, * tail;
	size_t _size;
};

inline List::List() { //construction
	this->head = new node();
	this->tail = new node();
	this->head->next = tail;
	this->tail->prev = head;
	this->head->prev = nullptr;
	this->tail->next = nullptr;
	this->_size = 0;
}

inline List::~List() {
	if (this->_size == 0) {
		delete this->head;
		delete this->tail;
		this->head = this->tail = nullptr;
		return;
	}
	while (this->head->next != this->tail) {
		//delte all nodes between head and tail
		node* tmp = this->head;
		this->head = this->head->next;
		delete tmp->data;
		delete tmp;
	}
	delete this->head;
	this->head = nullptr;
}

inline size_t List::size() {
	return this->_size;
}

inline void List::append(Rectangle* data) {
	node* cur = this->head;
	while (cur != this->tail) {
		if (cur->next == this->tail || *data < *cur->next->data) {
			//if next = tail or *data < *next->data append rectangle
			// < is overloaded
			node* tmp = new node(); //create a new node
			tmp->prev = cur;
			tmp->next = cur->next;
			cur->next->prev = tmp;
			cur->next = tmp;
			//change pointers
			tmp->data = data;
			this->_size++;
			break;
		}
		cur = cur->next;
	}
}

inline Rectangle List::pop(int index) {
	if (!this->size() || index > this->size()) { //check size of list
		std::cerr << "runtime err, list is empty!" << std::endl;
		delete this;
		exit(1);
	}
	node* cur = this->head;
	int cnt(0);
	while (cur != this->tail && cnt != index) {
		cur = cur->next;
		cnt++;
	}
	// delete this node and change the pointers of next & prev
	cur->prev->next = cur->next;
	cur->next->prev = cur->prev;
	Rectangle data = *cur->data; //copy the popped rectangle
	this->_size--;
	delete cur->data;
	delete cur;
	return data;
}

inline std::ostream& List::print(std::ostream& os) { //print the last rectangle
	if (!this->size()) {
		std::cerr << "list is empty!" << std::endl;
		delete this;
		exit(1);
	}
	return this->tail->prev->data->print(os);
}