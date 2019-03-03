// Implementing a Hash Table as an array of Linked List queues, where the stored element is a string
// Made the interface as friendly as possible, and the size is set by the user during runtime


#include <iostream>
#include <string>


struct Node
{
	std::string data;
	Node *next;
	Node(std::string s) : data(s), next(0) {}
};

class Queue
{
private:
	Node *head;
public:
	Queue() : head(0) {}
	~Queue();
	void QInsert(const std::string&);
	void QRemove(const std::string&);
	void QClear();
	void QPrint();
};

class HashTable
{
private:
	unsigned int size;
	Queue *Table;
public:
	HashTable(const unsigned int);
	~HashTable();
	void Clear();
	void Print();
	int  Hash(const std::string&);
	// Trying the way below for the sake of a simple interface, but it might be unneccessary & redundant
	// Main looks nicer with everything hid away by calling a parameter-less "Insert", but I don't want to restrict to inserting values from console (or with my console prompt)
	void Insert();
	void Insert(const std::string&);
	void Remove();
	void Remove(const std::string&);
};

int main()
{
	unsigned int size;
	std::cout << "Enter hash table size: ";
	std::cin >> size;
	std::cin.ignore(1000, 10);
	HashTable T(size);

	char choice;
	bool repeat = true;
	while (repeat)
	{
		std::cout << std::endl
			<< "1 - Add item"    << std::endl
			<< "2 - Remove item" << std::endl
			<< "3 - Clear list"  << std::endl
			<< "4 - Print list"  << std::endl
			<< "Q - Quit"        << std::endl
			<< "Enter choice: ";

		std::cin >> choice;
		std::cin.ignore(1000, 10);
		std::cout << std::endl;

		switch (choice)
		{
		case '1':
			T.Insert();
			break;
		case '2':
			T.Remove();
			break;
		case '3':
			T.Clear();
			break;
		case '4':
			T.Print();
			break;
		case 'Q': case'q':
			repeat = false;
			break;
		default:
			std::cout << "Invalid choice." << std::endl;
		}
	}
}


// Queue member function definitions

Queue::~Queue()
{
	QClear();
}

void Queue::QInsert(const std::string &s)
{
	// Performance here could be improved from linear to logarithmic time by inserting in sorted order, and then finding the insert point & duplicate checking via binary search

	// If list is empty, make it the head and you're done
	if (!head)
		head = new Node(s);
	else
	{
		// Otherwise, check if it's already in the list
		Node *trav = head;

		while (trav) // This is functionally the same as "while (1)"/"while (true)", but doesn't look as bad-practice-y. Couldn't figure out how to condense this & lines 125-128 neatly
		{
			// Duplicate check
			if (trav->data == s)
			{
				std::cout << "Not inserting \"" << s << "\"; duplicate entry." << std::endl;
				return;
			}

			// Make it stop on the last element, rather than on the trailing null
			if (trav->next)
				trav = trav->next;
			else
				break;
		}

		trav->next = new Node(s);
	}

	std::cout << "Inserted \"" << s << "\"." << std::endl;
}

void Queue::QRemove(const std::string &s)
{
	// The entries aren't in a sorted order, so any list with collision will be searched in linear time

	// If list is empty, do nothing
	if (!head)
	{
		std::cout << "\"" << s << "\" does not exist here." << std::endl;
		return;
	}

	// If list is one item, check head
	else if (!head->next)
	{
		if (head->data == s)
		{
			delete head;
			head = 0;

			std::cout << "Removed \"" << s << "\"." << std::endl;
			return;
		}
	}

	// If list is two or more items, 
	else
	{
		Node *trav  = head;
		Node *ahead = head;

		while (ahead)
		{
			if (ahead->data == s)
			{
				// If it's the first item in the list
				if (head == ahead) 
				{
					head = ahead->next;
					delete ahead;
				}
				// If it's not the first item
				else 
				{
					// Put the item to delete inbetween trav and ahead
					ahead = ahead->next;
					delete trav->next;
					trav->next = ahead;
				}

				std::cout << "Removed \"" << s << "\"." << std::endl;
				return;
			}

			trav = ahead;
			ahead = ahead->next;
		}
	}

	std::cout << "\"" << s << "\" does not exist here." << std::endl;
}

void Queue::QPrint()
{
	if (head)
	{
		Node *trav = head;
		while (trav)
		{
			std::cout << "\"" << trav->data << "\" ";
			trav = trav->next;
		}
	}

	std::cout << std::endl;
}

void Queue::QClear()
{
	Node *ahead = head;

	while (ahead)
	{
		ahead = ahead->next;
		delete head;
		head = ahead;
	}

	head = 0;
}


// HashTable member function definitions


HashTable::HashTable(const unsigned int _size) 
	: size(_size)
{
	Table = new Queue[size]; // Allocating on heap because size isn't known at compile time
}

HashTable::~HashTable()
{
	delete[] Table;
	Table = 0; // This seems like a "good practice" thing to do? Not sure if it's really needed
}

void HashTable::Clear()
{
	for (unsigned int i = 0; i < size; i++)
		Table[i].QClear();

	std::cout << "Cleared the list." << std::endl;
}

void HashTable::Print()
{
	for (unsigned int i = 0; i < size; i++)
	{
		std::cout << "[" << i << "] ";
		Table[i].QPrint();
	}
}

int  HashTable::Hash(const std::string &s)
{
	// A simple hash function: add the ASCII values of the input string, then mod by table size.
	// While acceptable for the purposes of this exercise, it has the problem of assigning duplicate indices to palindromes.
	
	unsigned int total = 0;
	for (unsigned int i = 0; i < s.length(); i++)
		total += s[i];

	return total % size;
}

void HashTable::Insert()
{
	std::string s;

	std::cout << "Enter string to insert: ";
	std::getline(std::cin, s);

	Insert(s);
}

void HashTable::Insert(const std::string& s)
{
	Table[Hash(s)].QInsert(s);
}

void HashTable::Remove()
{
	std::string s;

	std::cout << "Enter string to remove: ";
	std::getline(std::cin, s);

	Remove(s);
}

void HashTable::Remove(const std::string& s)
{
	Table[Hash(s)].QRemove(s);
}
