#include <iostream>
#include <memory>
#include <string>

const unsigned int nHashTableSize = 100;

int hash(std::string);

struct Node
{
	std::string sValue;
	Node *ptrNext;
	Node(std::string s = "") { sValue = s; ptrNext = nullptr; }
};

class Queue
{
public:
	Node *ptrHead, *ptrTail;
	Queue() { ptrHead = ptrTail = nullptr; }
	void Insert(std::string);
	void Print();
};

int main() {
	std::unique_ptr<Queue[]> HashTable(new Queue[nHashTableSize]);

	char cChoice;
	std::string sInput;
	bool bRepeat = true;

	while (bRepeat)
	{
		std::cout
			<< "\r\n"
			<< "   1. Print\r\n"
			<< "   2. Insert\r\n"
			<< "   Q. Quit\r\n"
			<< "      Enter Selection: ";

		std::cin >> cChoice;
		std::cout << "\r\n";

		switch (cChoice)
		{
		case '1': // Print
			for (int i = 0; i < nHashTableSize; i++)
			{
				std::cout << "[" << i << "] ";
				HashTable[i].Print();
			}
			break;
		
		case '2': // Insert
			std::cin.ignore();
			std::cout << "      Enter value: ";
			std::getline(std::cin, sInput);
			HashTable[hash(sInput)].Insert(sInput); // Insert the input at array index of hash result
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


int hash(std::string s)
{
	// Total of the ASCII values, mod by size
	int nTotal = 0;

	for (unsigned short i = 0; i < s.length(); i++)
		nTotal += s[i];
	
	return nTotal % nHashTableSize;
}

void Queue::Insert(std::string s)
{
	std::cout << "Inserting " << s << "\r\n";

	Node *ptrNode = new Node(s);

	if (!ptrNode) // If memory allocation failed
	{ 
		std::cout << "No memory available.\r\n";
		return;
	}

	if (ptrHead == nullptr) // Check if this is the new head
		ptrHead = ptrNode;
	else
		ptrTail->ptrNext = ptrNode;

	ptrTail = ptrNode;
}

void Queue::Print()
{
	if (ptrHead != nullptr)
	{
		Node *trav = ptrHead;

		// Traverse through the list, printing each item inside of square brackets
		while (trav) 
		{
			std::cout << '[' << trav->sValue << ']';

			if (trav->ptrNext)
				trav = trav->ptrNext;
			else
				break;
		}
		std::cout << "\r\n";
	}
	else
		std::cout << "\r\n";
}
