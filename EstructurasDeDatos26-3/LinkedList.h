#pragma once
class LinkedList
{
private:
	struct Node
	{
		int data;
		Node* next;
	};

	Node* _first;
	int _size;

public:
	LinkedList();
	void Add(int p_dato);
	int GetAt(int p_index);
	int GetSize();
	void Print();
	void InsertionSort();
	void SelectionSort();
	~LinkedList();
};