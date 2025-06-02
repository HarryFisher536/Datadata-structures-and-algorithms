// CMP201 AVL Tree
// Harry Fisher, Abertay Universitytree

#include "AVL.h"   		
#include <iostream>
#include <string>
#include <time.h>
#include <chrono>

// Perform a preorder traversal, printing out the values of each node visited in a readable fashionand the correct order[1].
void preOrder(AVL* r)
{
	if (r == NULL)
	{
		return;
	}

	std::cout << r->data << " ";

	preOrder(r->left);

	preOrder(r->right);
}

// Perform an inorder traversal, printing out the values of each node visited in a readable fashionand the correct order[1].
void inOrder(AVL* r)
{
	if (r == NULL)
	{
		return;
	}


	inOrder(r->left);

	std::cout << r->data << " ";

	inOrder(r->right);
}

// This is a helper method you may wish to implement returning the height of a node or 0 if r is a nullptr.
int getHeight(AVL* r)
{
	if (r == nullptr)
	{
		return 0;
	}

	return r->height;
}

// This is a helper method you may wish to implement returning the balance factor of a given node or 0 if r is a nullptr
int getBalance(AVL* r)
{
	if (r == nullptr)
	{
		return 0;
	}

	return getHeight(r->left) - getHeight(r->right);
}

// returns the maximum of the two integer values passed in.
int max(int a, int b)
{
	if (a > b)
	{
		return a;
	}

	else
	{
		return b;
	}
}




// performs a left rotation rooted at the node pointed to by r and updatesheights.[2]
AVL* leftRotate(AVL* r)
{
	AVL* newRoot = r->right;
	AVL* subtreeToTransplant = newRoot->left;

	newRoot->left = r;
	r->right = subtreeToTransplant;

// update height of root (1 + max...)
r->height = max(getHeight(r->left), getHeight(r->right)) + 1;

// update height of NR (1 + max...)
newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;


return newRoot;
}

// performs a right rotation rooted at the node pointed to by r and updates heights.[2]
AVL* rightRotate(AVL* r)
{
	AVL* newRoot = r->left;
	AVL* subtreeToTransplant = newRoot->right;

	newRoot->right = r;
	r->left = subtreeToTransplant;

	// update height of root (1 + max...)
	r->height = max(getHeight(r->left), getHeight(r->right)) + 1;

	// update height of NR (1 + max...)
	newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;

	return newRoot;
}

// inserts into tree, maintains balance, updates heights, returns root or rull pointer if it didnt insert
AVL* insertNode(AVL* r, int key)
{
	
	if (r == NULL)
	{
		return (new AVL(key));
	}

	if (key < r->data)
	{
		r->left = insertNode(r->left, key);
	}

	else if (key > r->data)
	{
		r->right = insertNode(r->right, key);
	}

	else
	{
		return r;
	}


	r->height = 1 + max(getHeight(r->left), getHeight(r->right));

	int balance = getBalance(r);

	if (balance > 1) {

		if (key < r->left->data) {
			return rightRotate(r);
		}

		else if (key > r->left->data) 
		{
			r->left = leftRotate(r->left);
			return rightRotate(r);
		}
	}
	if (balance < -1) 
	{

		if (key > r->right->data) 
		{
			return leftRotate(r);
		}

		else if (key < r->right->data) 
		{
			r->right = rightRotate(r->right);
			return leftRotate(r);
		}
	}

	return r;

}


// removes node from tree, maintains balance, updates hights
AVL* deleteNode(AVL* r, int key)
{
	if (r == NULL)
	{
		return r;
	}

	if (key < r->data)
	{
		r->left = deleteNode(r->left, key);
	}

	else if (key > r->data)
	{
		r->right = deleteNode(r->right, key);
	}

	else
	{
		if ((r->left == NULL) || (r->right == NULL))
		{
			AVL* temp = NULL;

			if (temp = r->left)
			{
				 temp = r->left;
			}

			else
			{
				 temp = r->right;
			}


			if (temp == NULL)
			{
				temp = r;
				r = NULL;
			}
			else
			{
				*r = *temp;
				temp = NULL;
			}
		}

		else
		{
			AVL* minVal = r;

			// loop down to find the leftmost leaf 
			while (minVal->left != NULL)
			{
				minVal = minVal->left;
			}

			AVL* temp = minVal->right;

			r->data = temp->data;

			r->right = deleteNode(r->right, temp->data);
		}
	}

	if (r == NULL)
	{
		return r;
	}

	r->height = 1 + max(getHeight(r->left), getHeight(r->right));


	int balance = getBalance(r);

	if (balance > 1 && getBalance(r->left) >= 0)
	{
		return rightRotate(r);
	}

	if (balance > 1 && getBalance(r->left) < 0)
	{
		r->left = leftRotate(r->left);
		return rightRotate(r);
	}

	if (balance < -1 && getBalance(r->right) <= 0)
	{
		return leftRotate(r);
	}

	if (balance < -1 && getBalance(r->right) > 0)
	{
		r->right = rightRotate(r->right);
		return leftRotate(r);
	}



	return r;
}

// Utility function: Get two time points and return a string of nanoseconds between them.
std::string timeDelta(std::chrono::steady_clock::time_point t, std::chrono::steady_clock::time_point t2)
{
	long timeDelta = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t).count();
	return std::to_string(timeDelta) + " ns";
}


int main()	
{
	std::cout << "You're doing great man, keep it up! \n";


	AVL* t1 = NULL;
	AVL* t2 = NULL;
	AVL* t3 = NULL;

	//t1
	auto time = std::chrono::high_resolution_clock::now();
	for (int i = 1; i < 1001; i++) {
		t1 = insertNode(t1, i);
	}
	auto time2 = std::chrono::high_resolution_clock::now();

	std::cout << "\n Time taken for 1000 inserts into t1 :";
	std::cout << timeDelta(time, time2);
	std::cout << "\n";



	//t2
	auto time3 = std::chrono::high_resolution_clock::now();
	for (int i = 1; i < 10001; i++) {
		t2 = insertNode(t2, i);
	}
	auto time4 = std::chrono::high_resolution_clock::now();

	std::cout << "\n Time taken for 10000 inserts into t2 :";
	std::cout << timeDelta(time3, time4);
	std::cout << "\n";



	//t3
	auto time5 = std::chrono::high_resolution_clock::now();
	for (int i = 1; i < 100001; i++) {
		t3 = insertNode(t3, i);
	}
	auto time6 = std::chrono::high_resolution_clock::now();

	std::cout << "\n Time taken for 100000 inserts into t3 :";
	std::cout << timeDelta(time5, time6);
	std::cout << "\n";



	return 0;
}