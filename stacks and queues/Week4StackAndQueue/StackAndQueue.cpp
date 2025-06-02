// William Kavanagh, CMP201.2022
// AX1.2 Partial Implementation

#include <iostream>
#include "StackAndQueue.h"

// Default constructor, init array
ArrayStack::ArrayStack()
{
    arr = new int[capacity];
}

// Remove first element, return value.
int ArrayStack::Pop()
{
    // TODO: ASSESSED [1]
    if (stackTop <= -1)
        std::cout << "empty stack" << std::endl;
    else {
        arr[stackTop];
        stackTop--;
    }
    return 0;
}

// Check first element, return value.
int ArrayStack::Peek()
{
    // TODO: ASSESSED [0.5]
 
    return arr[stackTop];
    
}

// Add element to top of stack, 
// calls DoubleArray() where appropriate
void ArrayStack::Push(int n)
{
    // TODO: ASSESSED [1]
    // [0.5] if correct without resizing.
    if (stackTop >= capacity - 1)
    {
        DoubleArray();
    }
    else
    {
        stackTop++;
        arr[stackTop] = n;
    }
    
    
}

// Print elements in Stack neatly
// DO NOT CHANGE: used for testing and assessment
void ArrayStack::Display()
{
    std::cout << arr[0] << "\t<- head" << std::endl;
    for (int i = 1; i < stackTop + 1; i++)
    {
        std::cout << arr[i] << std::endl;
    }
}

// Updates array pointer to new array of double the size
// elements are copied in from old array with position preserved.
void ArrayStack::DoubleArray()
{
    capacity *= 2;
    int* new_arr = new int[capacity];
    for (int i = 0; i < stackTop + 1; i++)
    {
        new_arr[i] = arr[i];
    }
    arr = new_arr;
}

// Node constructor
Node::Node(int n)
{
    next = nullptr;
    data = n;
}

// QL constructor
QueueList::QueueList()
{
    // TODO: ASSESSED [0.5]
    front = nullptr;
    back = nullptr;
}

// Add item to back of queue
void QueueList::Enqueue(int n)
{
     // TODO: ASSESSED [1]
    if (front == nullptr)
    { 
        front = new Node(n);
        back = front;
        return;
    }

    back->next = new Node(n);
    back = back->next;
}

// Remove item from front of queue
int QueueList::Dequeue()
{
    if (front == nullptr) {
        return nullptr;
    }
    // TODO: ASSESSED [1]
    int temp = front->data;
    front = front->next;

    if (front == nullptr)
    {
        front = nullptr;
        back = nullptr;
    }

    return temp;
}

// Print elements in Stack neatly
// DO NOT CHANGE: used for testing and assessment
void QueueList::Display()
{
    if (!front)
    {
        std::cout << "[]";
        return;
    }
    Node* n = front;
    std::cout << "f: ";
    while (n != back)
    {
        std::cout << n->data << ",\t";
        n = n->next;
    }
    std::cout << "b: " << n->data << std::endl;
}

int main()
{
   // Stack test.

   ArrayStack* stack = new ArrayStack();
   stack->Push(20);
   stack->Push(30);
   stack->Push(40);
   std::cout << "Testing stack, expecting: \nh:20,\t30,\t40.\nGot: \n";
   stack->Display();
   std::cout << "\n";
   stack->Pop();
   stack->Push(50);
   std::cout << "Show me 50: " << stack->Peek() << "\n";
   std::cout << "Testing stack, expecting: \nh:20,\t30,\t50\nGot: \n";
   stack->Display();

   // Check Overflow

   ArrayStack* bigStack = new ArrayStack();
   for (int i = 0; i < 100; i++)
   {
       bigStack->Push(i);
   }
   std::cout << "Expecting stack of 0..99:\n";
   bigStack->Display();
   std::cout << "Expecting stack capacity of 2^7. capacity is actually: " << bigStack->capacity << "\n";


   // Queue test.

   QueueList* q = new QueueList();
   q->Enqueue(25);
   q->Enqueue(40);
   q->Enqueue(7);
   std::cout << "Testing queue, expecting: \nf: 25,\t40,\tb: 7\nGot: \n";
   q->Display();

   q->Dequeue();           // remove 25 from queue, do nothing with it.
   q->Enqueue(45);
   std::cout << "Testing queue, expecting: \nf: 40,\t7,\tb: 45\nGot: \n";
   q->Display();

   return 0;
}