#include <string>
#include <iostream>
#include <vector>

enum class ItemId { EMPTY, FOOD, GUN, AMMO };

struct Item
{
	ItemId Id;
	int Stack;
	Item(ItemId i = ItemId::EMPTY, int s = 0) : Id(i), Stack(s) {}
};

class Inventory
{
	int _invSize, _maxStack;
	std::vector<Item*> _inv;
public:
	Inventory(int size = 10, int stack = 10) : _invSize(size), _maxStack(stack)
	{
		_inv.reserve(size);
		
		while (size--)
		{
			_inv.push_back(new Item{ItemId::EMPTY, 0});
		}
	}
	~Inventory()
	{
		for (auto i : _inv)
		{
			delete i;
		}
	}
	void Print()
	{
		for (auto i : _inv)
		{
			if (i->Stack > 0)
			{
				std::cout << i->Stack << "x #" << (int)i->Id << "\r\n";
			}
		}

		std::cout << "---\r\n";
	}
	void PickUp(Item *item)
	{
		std::cout << "Picking up " << item->Stack << "x #" << (int)item->Id << "...\r\n";

		bool canPickUp = false, incompletePickup = true;

		for(auto invSlot : _inv)
		{ 
			if (invSlot->Id == ItemId::EMPTY || (invSlot->Id == item->Id && invSlot->Stack < _maxStack))
			{
				canPickUp = true;

				if (invSlot->Id == ItemId::EMPTY)
				{
					invSlot->Id = item->Id;
				}

				int canFit = _maxStack - invSlot->Stack;

				if (item->Stack > canFit)
				{
					invSlot->Stack += canFit;
					item->Stack -= canFit;
				}
				else
				{
					incompletePickup = false;
					invSlot->Stack += item->Stack;
					item->Stack = 0;
					break;
				}
			}
		}

		if (!canPickUp)
		{
			std::cout << "Not enough space to pick up the item.\r\n";
		}
		else
		{
			if (incompletePickup)
			{
				std::cout << "Left " << item->Stack << " on the floor.\r\n";
			}
			
			Print();
		}
	}
};

int main() 
{
	Inventory inv{};

	Item *GroundItem0 = new Item{ ItemId::FOOD,  3 };
	Item *GroundItem1 = new Item{ ItemId::GUN,   1 };
	Item *GroundItem2 = new Item{ ItemId::AMMO,  6 };
	Item *GroundItem3 = new Item{ ItemId::AMMO, 10 };
	Item* GroundItem4 = new Item{ ItemId::AMMO,  7 };
	Item* GroundItem5 = new Item{ ItemId::AMMO, 90 };

	inv.PickUp(GroundItem0);
	inv.PickUp(GroundItem1);
	inv.PickUp(GroundItem1); // Try to pick this up again, to show that the ground item is now at 0 stack
	inv.PickUp(GroundItem2);
	inv.PickUp(GroundItem3);
	inv.PickUp(GroundItem4); // Try to pick up something that will fill a stack & generate a new one
	inv.PickUp(GroundItem5); // Try to pick up something that won't fit in inventory
	inv.PickUp(GroundItem5); // Try to pick up leftover of item, with full inventory
}

// OUTPUT:

// Picking up 3x #1...
// 3x #1
// ---
// Picking up 1x #2...
// 3x #1
// 1x #2
// ---
// Picking up 0x #2...
// 3x #1
// 1x #2
// ---
// Picking up 6x #3...
// 3x #1
// 1x #2
// 6x #3
// ---
// Picking up 10x #3...
// 3x #1
// 1x #2
// 10x #3
// 6x #3
// ---
// Picking up 7x #3...
// 3x #1
// 1x #2
// 10x #3
// 10x #3
// 3x #3
// ---
// Picking up 90x #3...
// Left 33 on the floor.
// 3x #1
// 1x #2
// 10x #3
// 10x #3
// 10x #3
// 10x #3
// 10x #3
// 10x #3
// 10x #3
// 10x #3
// ---
// Picking up 33x #3...
// Not enough space to pick up the item.
