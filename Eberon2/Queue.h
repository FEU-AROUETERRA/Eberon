#ifndef Queue_H
#define Queue_H
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <iterator>
#include <algorithm>
#include <list>
#include <random>

using namespace std;

class Queue {
	struct node {
		int data;
		node *next;
	};
	node* front = NULL;
	node* rear = NULL;
	node* current;
public:
	Queue();
	void Insert();
};

#endif