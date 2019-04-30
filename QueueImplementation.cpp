#include <iostream>
#include <memory> // std::unique_ptr


struct Node
{
	int Value;
	Node *Next;
	Node(int n = 0) : Value(n), Next(0) {}
};

class  Queue
{
	Node *head, *tail;
public:
	Queue() { head = tail = 0; }
	~Queue() { Clear(); }

	void Insert(const int&);
	void Delete();
	void Clear();
	void Print();
};


int main() {
	std::unique_ptr<Queue> Q(new Queue());
	char choice;
	int  input;
	bool repeat = true;

	while (repeat)
	{
		std::cout
			<< "\r\n"
			<< "   1. Print\r\n"
			<< "   2. Insert\r\n"
			<< "   3. Delete end\r\n"
			<< "   4. Delete all\r\n"
			<< "   Q. Quit\r\n"
			<< "      Enter Selection: ";

		std::cin >> choice;
		std::cin.ignore(1000, 10);
		std::cout << "\r\n";

		switch (choice)
		{
		case '1':
			Q->Print();
			break;
		case '2':
			std::cout << "      Enter value: ";
			std::cin >> input;
			std::cin.ignore(1000, 10);
			Q->Insert(input);
			break;
		case '3':
			Q->Delete();
			break;
		case '4':
			Q->Clear();
			break;
		case 'Q': case 'q':
			repeat = false;
			break;
		default:
			std::cout << "Invalid input\r\n";
			break;
		}
	}
}


void Queue::Insert(const int& n)
{
	std::cout << "Inserting " << n << "\r\n";

	Node *node = new Node(n);

	if (!node) {
		std::cout << "No memory available.\r\n";
		return;
	}

	if (!head)
		head = node;
	else
		tail->Next = node;

	tail = node;
}

void Queue::Delete()
{
	// If the list is empty
	if (!head)
		std::cout << "Deleting nothing; list is empty\r\n";

	// If the list has one item
	else if (head == tail && head != nullptr)
	{
		std::cout << "Deleting " << tail->Value << ", list is now empty\r\n";
		delete tail;
		head = tail = 0;
	}

	// List has two or more items
	else
	{
		std::cout << "Deleting " << tail->Value;

		Node *curr = head;

		// Find the second-to-last node
		while (curr->Next != tail)
			curr = curr->Next;

		delete tail;
		tail = curr;
		tail->Next = 0;

		std::cout << ", new tail is " << tail->Value << "\r\n";
	}
}

void Queue::Clear()
{
	if (!head)
		std::cout << "Nothing to delete; list is already empty\r\n";
	else
	{
		std::cout << "Deleting list\r\n";

		if (head == tail)
		{
			delete head;
			delete tail;
		}
		else
		{
			Node *curr = head, *ahead = head->Next;

			while (true)
			{
				delete curr;
				curr = ahead;

				if (ahead->Next)
					ahead = ahead->Next;
				else
					break;
			}
		}
	}

	head = tail = 0;
}

void Queue::Print()
{
	if (head)
	{
		Node* curr = head;
		std::cout << "List: ";

		while (curr) {
			std::cout << curr->Value << ' ';

			if (curr->Next)
				curr = curr->Next;
			else
				break;
		}
		std::cout << "\r\n";
	}
	else
		std::cout << "List is empty\r\n";
}
