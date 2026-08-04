#pragma once
class LinkedList
{
private:
	int _size;

public:
	LinkedList();
	void Add(int dato);
	int GetAt(int index);
	int GetSize();
	void Print();
	void InsertionSort();
	void SelectionSort();
	~LinkedList();
};

