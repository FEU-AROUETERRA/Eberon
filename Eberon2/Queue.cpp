#include "Queue.h"

Queue::Queue() {}



void Queue::Insert() {
	int val;
	cout << "Insert the element in queue : " << endl;
	cin >> val;
	if (rear == NULL) {
		
		rear->next = NULL;
		rear->data = val;
		front = rear;
	}
	else {
		rear->next = current;
		current->data = val;
		current->next = NULL;
		rear = current;
	}
}


//void Delete() {
//	temp = front;
//	if (front == NULL) {
//		cout << "Underflow" << endl;
//		return;
//	}
//	else
//		if (temp->next != NULL) {
//			temp = temp->next;
//			cout << "Element deleted from queue is : " << front->data << endl;
//			free(front);
//			front = temp;
//		}
//		else {
//			cout << "Element deleted from queue is : " << front->data << endl;
//			free(front);
//			front = NULL;
//			rear = NULL;
//		}
//}
