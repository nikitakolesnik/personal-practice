#include <iostream>
#include <memory>
#include <cstdlib>
#include <string>
#include <vector>

const unsigned int nHashTableSize = 100;

int hash(std::string);

struct Node
{
	std::string sValue;
	Node *ptrNext;
	Node() { sValue = ""; ptrNext = nullptr; }
	Node(std::string s) { sValue = s; ptrNext = nullptr; }
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
		case '1':
			for (int i = 0; i < nHashTableSize; i++)
			{
				std::cout << "[" << i << "] ";
				HashTable[i].Print();
			}
			break;
		case '2':
			std::cout << "      Enter value: ";
			std::cin >> sInput;
			std::cin.ignore(1000, 10);
			HashTable[hash(sInput)].Insert(sInput);
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
	int nTotal = 0;

	for (unsigned short i = 0; i < s.length(); i++)
		nTotal += s[i];

	return nTotal % nHashTableSize;
}

void Queue::Insert(std::string s)
{
	std::cout << "Inserting " << s << "\r\n";

	Node *ptrNode = new Node(s);

	if (!ptrNode) {
		std::cout << "No memory available.\r\n";
		return;
	}

	if (ptrHead == nullptr)
		ptrHead = ptrNode;
	else
		ptrTail->ptrNext = ptrNode;

	ptrTail = ptrNode;
}

void Queue::Print()
{
	if (ptrHead != nullptr)
	{
		Node* trav = ptrHead;

		while (trav) {
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
