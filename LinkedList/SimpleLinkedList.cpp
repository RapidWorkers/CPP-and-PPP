#include "SimpleLinkedList.h"
#include <iostream>

using namespace std;

//Node* LinkedList::createNode() {
//	Node* newNode = new Node();
//	newNode->next = this->head;
//	this->head = newNode;
//}

void LinkedList::push_back(int value) {
	Node* currentNode = this->head;
	int count = 0;

	Node* newNode = new Node();

	if (this->head == NULL) {//노드가 없으면 push_front와 같음
		newNode->next = this->head;
		newNode->data = value;
		this->head = newNode;
		return;
	}

	Node* prevNode = NULL;
	while (currentNode) {
		count++;
		prevNode = currentNode;
		currentNode = currentNode->next;
	}

	//이전 노드와 새 노드 연결
	prevNode->next = newNode;

	newNode->data = value;
	newNode->next = NULL;
	return;
}

void LinkedList::push_front(int value) {
	Node* newNode = new Node();
	newNode->next = this->head;
	newNode->data = value;
	this->head = newNode;
}

void LinkedList::push_mid(int value, int pos) {

	if (this->head == NULL) {//노드가 없으면 push_front와 같음
		Node* newNode = new Node();
		newNode->next = this->head;
		newNode->data = value;
		this->head = newNode;
		return;
	}
	
	int count = 0;
	bool flag = 0;
	Node* currentNode = this->head;
	Node* prevNode = NULL;

	while (currentNode) {
		if (count == pos) {//if we found the node at that position
			Node* newNode = new Node();
			prevNode->next = newNode;
			newNode->next = currentNode;
			newNode->data = value;
			flag = 1;
			break;
		}
		prevNode = currentNode;
		currentNode = currentNode->next;
		count++;
	}

	if (!flag) cout << "Node not Found" << endl;

}

void LinkedList::showNode(int pos) {
	int count = 0;
	bool flag = 0;

	if (this->head == NULL) {
		cout << "No node available" << endl;
		return;
	}

	Node* currentNode = this->head;
	while (currentNode) {
		if (count == pos) {//if we found the node at that position
			cout << "Value: " << currentNode->data << endl;
			cout << "Pos: " << count << endl;
			flag = 1;
			break;
		}
		currentNode = currentNode->next;
		count++;
	}

	if (!flag) cout << "Node not Found" << endl;
	return;
}

void LinkedList::deleteNode(int pos) {
	int count = 0;
	bool flag = 0;

	if (this->head == NULL) {
		cout << "No node available" << endl;
		return;
	}

	Node* currentNode = this->head;
	Node* prevNode = NULL;

	while (currentNode) {
		if (count == pos) {
			//connect node
			if (prevNode != NULL)
				prevNode->next = currentNode->next;
			else//만약에 0번 노드면 헤드와 연결시킴
				this->head = currentNode->next;

			delete currentNode;
			flag = 1;
			break;
		}
		count++;
		prevNode = currentNode;
		currentNode = currentNode->next;
	}

	if (!flag) cout << "Node not Found" << endl;
	return;
}

void LinkedList::showFullNode() {

	if (this->head == NULL) {
		cout << "No node available" << endl;
		return;
	}

	int count = 0;

	Node* currentNode = this->head;
	while (currentNode) {
		cout << "Value: " << currentNode->data << endl;
		cout << "Pos: " << count << endl << endl;
		currentNode = currentNode->next;
		count++;
	}

	return;
}
