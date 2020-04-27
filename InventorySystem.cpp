// Simulates a video game inventory
// Solves problems related to picking up stackable items
// Edits the resource being consumed

#include <iostream>
#include <vector>

enum class ItemId { EMPTY, FOOD, GUN, AMMO };

struct Item
{
	ItemId Id;
	int Stack;
	Item(ItemId i = ItemId::EMPTY, int s = 0)
		: Id(i), Stack(s)
	{
	}
};

class Inventory
{
	int _invSize, _maxStack;
	std::vector<Item> _inv;
public:
	Inventory(int size = 10, int stack = 10)
		: _invSize(size), _maxStack(stack)
	{
		_inv = std::vector<Item>(size, Item{ ItemId::EMPTY, 0 });
	}

	void Print()
	{
		for (auto i : _inv)
		{
			if (i.Stack > 0)
			{
				std::cout << '\t' << i.Stack << "x #" << (int)i.Id << "\r\n";
			}
		}
	}

	void PickUp(Item& item)
	{
		std::cout << "Picking up " << item.Stack << "x #" << (int)item.Id << "...\r\n";

		if (item.Stack == 0)
		{
			std::cout << "\tNothing to pick up.\r\n";
			return;
		}

		bool inventoryFull = false, incompletePickup = true;

		for (auto &slot : _inv)
		{
			if (slot.Id == ItemId::EMPTY || (slot.Id == item.Id && slot.Stack < _maxStack))
			{
				inventoryFull = false;

				if (slot.Id == ItemId::EMPTY)
				{
					slot.Id = item.Id;
				}

				int canFit = _maxStack - slot.Stack;

				if (item.Stack > canFit)
				{
					slot.Stack += canFit;
					item.Stack -= canFit;
				}
				else
				{
					incompletePickup = false;
					slot.Stack += item.Stack;
					item.Stack = 0;
					break;
				}
			}
		}
		if (inventoryFull)
		{
			std::cout << "\tNot enough space to pick up the item.\r\n";
		}
		else
		{
			Print();
			if (incompletePickup)
			{
				std::cout << "\tLeft " << item.Stack << " on the floor.\r\n";
			}

		}
	}
};

int main()
{
	Inventory inv;

	Item GroundItem0{ ItemId::FOOD,  3 };
	Item GroundItem1{ ItemId::GUN,   1 };
	Item GroundItem2{ ItemId::AMMO,  6 };
	Item GroundItem3{ ItemId::AMMO, 10 };
	Item GroundItem4{ ItemId::AMMO,  7 };
	Item GroundItem5{ ItemId::AMMO, 90 };

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
//     3x #1
// Picking up 1x #2...
//     3x #1
//     1x #2
// Picking up 0x #2...
//     Nothing to pick up.
// Picking up 6x #3...
//     3x #1
//     1x #2
//     6x #3
// Picking up 10x #3...
//     3x #1
//     1x #2
//     10x #3
//     6x #3
// Picking up 7x #3...
//     3x #1
//     1x #2
//     10x #3
//     10x #3
//     3x #3
// Picking up 90x #3...
//     3x #1
//     1x #2
//     10x #3
//     10x #3
//     10x #3
//     10x #3
//     10x #3
//     10x #3
//     10x #3
//     10x #3
//     Left 33 on the floor.
// Picking up 33x #3...
//     Not enough space to pick up the item.
