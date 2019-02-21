#include <iostream>


struct Node 
{
	int nValue;
	Node *ptrNext;
};

class Queue 
{
public:
	Node *ptrHead, *ptrTail;
	Queue() { ptrHead = ptrTail = 0; }
	~Queue() { Clear(); }

	void Insert(int);
	void Delete();
	void Clear();
	void Print();
};


int main() {
	std::unique_ptr<Queue> Q(new Queue());
	char cChoice;
	int  nInput;
	bool bRepeat = true;

	while (bRepeat)
	{
		std::cout
			<< "\r\n"
			<< "   1. Print\r\n"
			<< "   2. Insert\r\n"
			<< "   3. Delete end\r\n"
			<< "   4. Delete all\r\n"
			<< "   Q. Quit\r\n"
			<< "      Enter Selection: ";

		std::cin >> cChoice;
		std::cin.ignore(1000, 10);
		std::cout << "\r\n";

		switch (cChoice)
		{
		case '1':
			Q->Print();
			break;
		case '2':
			std::cout << "      Enter value: ";
			std::cin >> nInput;
			std::cin.ignore(1000, 10);
			Q->Insert(nInput);
			break;
		case '3':
			Q->Delete();
			break;
		case '4':
			Q->Clear();
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


void Queue::Insert(int n) 
{
	std::cout << "Inserting " << n << "\r\n";

	Node *ptrNode = new Node();
	ptrNode->nValue = n;

	if (!ptrNode) {
		std::cout << "No memory available.\r\n";
		return;
	}

	if (!ptrHead)
		ptrHead = ptrNode;
	else
		ptrTail->ptrNext = ptrNode;

	ptrTail = ptrNode;
}

void Queue::Delete() 
{
	// If the list is empty
	if (!ptrHead) 
		std::cout << "Deleting nothing; list is empty\r\n";
	
	// If the list has one item
	else if (ptrHead == ptrTail && ptrHead != nullptr) 
	{
		std::cout << "Deleting " << ptrTail->nValue << ", list is now empty\r\n";

		delete ptrHead;
		delete ptrTail;
		ptrHead = ptrTail = 0;
	}
	
	// List has two or more items
	else 
	{
		std::cout << "Deleting " << ptrTail->nValue;
		
		Node *ptrTrav = ptrHead;
		
		// Find the second-to-last node
		while (ptrTrav->ptrNext != ptrTail) 
			ptrTrav = ptrTrav->ptrNext;
		
		delete ptrTail;
		ptrTail = ptrTrav;
		ptrTail->ptrNext = 0;

		std::cout << ", new tail is " << ptrTail->nValue << "\r\n";
	}
}

void Queue::Clear() 
{
	if (!ptrHead)
		std::cout << "Nothing to delete; list is already empty\r\n";
	else
	{
		std::cout << "Deleting list\r\n";

		if (ptrHead == ptrTail)
		{
			delete ptrHead;
			delete ptrTail;
		}
		else
		{
			Node *ptrTrav0 = ptrHead, *ptrTrav1 = ptrHead->ptrNext;

			while (true)
			{
				delete ptrTrav0;
				ptrTrav0 = ptrTrav1;

				if (ptrTrav1->ptrNext)
					ptrTrav1 = ptrTrav1->ptrNext;
				else
					break;
			}
		}
	}

	ptrHead = ptrTail = 0;
}

void Queue::Print() 
{
	if (ptrHead != nullptr)
	{
		Node* trav = ptrHead;
		std::cout << "List: ";

		while (trav) {
			std::cout << trav->nValue << ' ';

			if (trav->ptrNext)
				trav = trav->ptrNext;
			else
				break;
		}
		std::cout << "\r\n";
	}
	else
		std::cout << "List is empty\r\n";
}
