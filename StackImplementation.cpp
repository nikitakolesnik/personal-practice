#include <iostream>
#include <memory> // std::unique_ptr


struct Node
{
	int Value;
	Node *Next;
	Node(int n = 0) : Value(n) { Next = 0; }
};

class Stack
{
	Node *head;
public:
	Stack() { head = 0; }
	~Stack() { Clear(); }

	void Insert(const int&);
	void Delete();
	void Clear();
	void Print();
};


int main() {
	char cChoice;
	int  nInput;
	bool bRepeat = true;
	std::unique_ptr<Stack> S(new Stack());

	while (bRepeat)
	{
		std::cout
			<< "\r\n"
			<< "   1. Print\r\n"
			<< "   2. Insert\r\n"
			<< "   3. Delete front\r\n"
			<< "   4. Delete all\r\n"
			<< "   Q. Quit\r\n"
			<< "      Enter Selection: ";

		std::cin >> cChoice;
		std::cin.ignore(1000, 10);
		std::cout << "\r\n";

		switch (cChoice)
		{
		case '1':
			S->Print();
			break;
		case '2':
			std::cout << "      Enter value: ";
			std::cin >> nInput;
			std::cin.ignore(1000, 10);
			S->Insert(nInput);
			break;
		case '3':
			S->Delete();
			break;
		case '4':
			S->Clear();
			break;
		case 'Q': case 'q':
			bRepeat = false;
			break;
		default:
			std::cout << "Invalid input\r\n";
			break;
		}
	}
}


void Stack::Insert(const int& n)
{
	std::cout << "Inserting " << n << "\r\n";

	Node *node = new Node(n);

	node->Next = head;
    head = node;
}

void Stack::Delete() {
	// 0 items
	if (!head)
		std::cout << "Nothing to delete\r\n";
	
	// 1 item
	else if (!head->Next)
	{
		std::cout << "Deleting " << head->Value;
		
		delete head;
        head = 0;
		
		std::cout << ", list is now empty\r\n";
	}

	// 2+ items
	else
	{
		std::cout << "Deleting " << head->Value << "\r\n";

		Node *temp = head->Next;
		delete head;
        head = temp;
	}
}

void Stack::Clear() 
{
	if (!head)
		std::cout << "Nothing to delete; list is already empty\r\n";
	else
	{
		std::cout << "Deleting list\r\n";

		if (head->Next == nullptr)
			delete head;
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

    head = 0;
}

void Stack::Print() 
{
	if (head)
	{
		Node* trav = head;
		std::cout << "List: ";

		while (trav) {
			std::cout << trav->Value << ' ';

			if (trav->Next)
				trav = trav->Next;
			else
				break;
		}
		std::cout << "\r\n";
	}
	else
		std::cout << "List is empty\r\n";
}
