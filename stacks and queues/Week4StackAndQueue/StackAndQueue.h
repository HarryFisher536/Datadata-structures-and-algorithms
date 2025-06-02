#pragma once

class ArrayStack
{
public:
	int capacity = 8;
	int stackTop = -1;
	int* arr;

	ArrayStack();

	int Pop();
	int Peek();
	void Push(int n);
	void Display();
	void DoubleArray();
};

class Node
{
public:
	Node(int n);

	int data;
	Node* next;
};

class QueueList
{
public:
	Node* front;
	Node* back;

	QueueList();
	void Enqueue(int n);
	int Dequeue();
	void Display();
};

