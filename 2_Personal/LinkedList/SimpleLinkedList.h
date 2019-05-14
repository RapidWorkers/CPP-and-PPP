#pragma once

class Node {
public:
	Node * next;
	int data;
};

class LinkedList {
	public:
		Node * head;

		void push_back(int value);
		void push_front(int value);
		void push_mid(int value, int pos);
		void deleteNode(int pos);
		void showNode(int pos);
		void showFullNode();
	private:
		//Node* createNode();
		//Node* 


};
