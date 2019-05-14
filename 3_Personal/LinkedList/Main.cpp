#include <iostream>
#include "SimpleLinkedList.h"
#include <Windows.h>

using namespace std;

int main() {

	int job;
	int pos;
	int val;

	LinkedList *LList = new LinkedList();

	while (1) {
		system("cls");
		cout << "작업 목록" << endl;
		cout << "1. 노드 보기" << endl;
		cout << "2. 노드 맨 뒤에 삽입" << endl;
		cout << "3. 노드 맨 앞에 삽입" << endl;
		cout << "4. 노드의 중간에 삽입" << endl;
		cout << "5. 노드 삭제" << endl;
		cout << "6. 노드 전체 보기" << endl;
		cout << "7. 종료" << endl;

		cout << "작업: ";
		cin >> job;

		switch (job) {
		case 1:
			cout << "위치 : ";
			cin >> pos;
			LList->showNode(pos);
			system("pause");
			break;
		case 2:
			cout << "넣을 값 : ";
			cin >> val;
			LList->push_back(val);
			break;
		case 3:
			cout << "넣을 값 : ";
			cin >> val;
			LList->push_front(val);
			break;
		case 4:
			cout << "위치 : ";
			cin >> pos;
			cout << "넣을 값 : ";
			cin >> val;
			LList->push_mid(val, pos);
			break;
		case 5:
			cout << "위치 : ";
			cin >> pos;
			LList->deleteNode(pos);
			system("pause");
			break;
		case 6:
			LList->showFullNode();
			system("pause");
			break;
		case 7:
			delete LList;
			exit(0);
			break;
		default:
			cout << "올바르지 않은 입력입니다." << endl;
			Sleep(300);
			break;
		}
	}
}
