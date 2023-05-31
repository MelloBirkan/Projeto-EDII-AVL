// mainAVL.cpp
#include <iostream>
#include <string>
#include "AVL.h"

void Insert(AVL* avl)
{
	int num;
	std::cout << "Insert number: ";
	std::cin >> num;
	NodeAVL* node = avl->Insert(num, std::to_string(num));
	if (node)
		std::cout << "Node inserted!\n";
	else
		std::cout << "*** ERROR! Couldn't insert node!\n";
}

void Remove(AVL* avl)
{
	int num;
	std::cout << "Remove number: ";
	std::cin >> num;
	avl->Remove(num);
}

void Search(AVL* avl)
{
	int num;
	std::cout << "Search number: ";
	std::cin >> num;
	NodeAVL* node = avl->Search(num);
	if (node)
		std::cout << "Node found:\n" << node->ToString();
	else
		std::cout << "*** ERROR! Couldn't find node!\n";
}

void Predecessor(AVL* avl)
{
	int num;
	std::cout << "Find predecessor of: ";
	std::cin >> num;
	NodeAVL* node = avl->Predecessor(num);
	if (node)
		std::cout << "Predecessor of " << num << ":\n" << node->ToString();
	else
		std::cout << "*** ERROR! There is no predecessor of " << num << "!\n";
}

void Successor(AVL* avl)
{
	int num;
	std::cout << "Find successor of: ";
	std::cin >> num;
	NodeAVL* node = avl->Successor(num);
	if (node)
		std::cout << "Successor of " << num << ":\n" << node->ToString();
	else
		std::cout << "*** ERROR! There is no successor of " << num << "!\n";
}

void FindMin(AVL* avl)
{
	NodeAVL* node = avl->FindMin();
	if (node)
		std::cout << "Minimum:\n" << node->ToString();
	else
		std::cout << "*** ERROR! Couldn't find minimum (tree is probably empty...)\n";
}

void FindMax(AVL* avl)
{
	NodeAVL* node = avl->FindMax();
	if (node)
		std::cout << "Maximum:\n" << node->ToString();
	else
		std::cout << "*** ERROR! Couldn't find maximum (tree is probably empty...)\n";
}

void TraverseInOrder(AVL* avl)
{
	std::cout << avl->TraverseInOrder() << '\n';
}

void TraversePreOrder(AVL* avl)
{
	std::cout << avl->TraversePreOrder() << '\n';
}

void TraversePostOrder(AVL* avl)
{
	std::cout << avl->TraversePostOrder() << '\n';
}

void Clear(AVL* avl)
{
	avl->Clear();
}

int main()
{

	AVL* avl = new AVL();

	const int SIZE = 9;
	int ids[SIZE] = { 5, 4, 3, 1, 2, 6, 7, 9, 8 };
	for (int i = 0; i < SIZE; ++i)
		avl->Insert(ids[i], std::to_string(ids[i]));

	int option = 0;
	do
	{
		std::cout << "*** AVL Tree ***\n"
			<< "[1] Insert\n"
			<< "[2] Remove\n"
			<< "[3] Search\n"
			<< "[4] Predecessor\n"
			<< "[5] Successor\n"
			<< "[6] Find minimum\n"
			<< "[7] Find maximum\n"
			<< "[8] Traverse in-order\n"
			<< "[9] Traverse pre-order\n"
			<< "[10] Traverse post-order\n"
			<< "[11] Clear\n"
			<< "[0] Exit\n"
			<< "Option: ";
		std::cin >> option;
		std::cout << '\n';

		switch (option)
		{
		case 1: Insert(avl); break;
		case 2: Remove(avl); break;
		case 3: Search(avl); break;
		case 4: Predecessor(avl); break;
		case 5: Successor(avl); break;
		case 6: FindMin(avl); break;
		case 7: FindMax(avl); break;
		case 8: TraverseInOrder(avl); break;
		case 9: TraversePreOrder(avl); break;
		case 10: TraversePostOrder(avl); break;
		case 11: Clear(avl); break;
		}

		std::cout << '\n';
	} while (option != 0);

	delete avl;
}
//#endif
