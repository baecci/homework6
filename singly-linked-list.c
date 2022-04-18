#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
	int key;
	struct Node* link;  //노드의 링크를 선언한다.(아직 Node라는 구조체 타입이 선언되지 않았으므로 struct 없이는 컴파일 오류가 발생한다.)
}listNode;

typedef struct Head {
	struct Node* first;  //연결리스트의 첫 노드를 가리킬 포인터를 선언한다. 
}headNode;


/* 함수 리스트 */
headNode* initialize(headNode* h);
int freeList(headNode* h);

int insertFirst(headNode* h, int key);
int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);

int deleteFirst(headNode* h);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);

int main()
{
	char command;
	int key;
	headNode* headnode=NULL;  

	do{
		printf("              [---------배기원 2021041081---------]\n");
		printf("----------------------------------------------------------------\n");  //기능 메뉴를 출력한다.
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {  //커멘드에 따라 함수를 호출한다.
		case 'z': case 'Z':
			headnode = initialize(headnode);  //메모리가 할당된 listNode를 초기화하는 함수 호출.
			break;
		case 'p': case 'P':
			printList(headnode);  //리스트들을 출력하는 함수 호출.
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);  //입력받은 key에 대한 노드를 중간에 삽입하는 함수 호출.
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);  //입력받은 key에 대한 노드를 해제(삭제)하는 함수 호출.
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);  //맨 마지막에 노드를 추가하는 함수 호출.
			break;
		case 'e': case 'E':
			deleteLast(headnode);  //맨 마지막 노드를 해제(삭제)하는 함수 호출.
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);  //맨 앞쪽에 노드를 추가하는 함수 호출.
			break;
		case 't': case 'T':
			deleteFirst(headnode);  //맨 앞쪽 노드를 해제(삭제)하는 함수 호출.
			break;
		case 'r': case 'R':
			invertList(headnode);  //원래의 링크를 순서를 역순으로 링크하도록 변경하는 함수 호출.
			break;
		case 'q': case 'Q':
			freeList(headnode);  //할당된 메모리를 전부 해제하는 함수 호출.
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	if(h != NULL)  //헤드 노드가 Null이 아니면, 할당된 메모리를 모두 해제하는 freeNode를 호출한다.
		freeList(h);
	
	headNode* temp = (headNode*)malloc(sizeof(headNode));  //headNode크기의 메모리를 할당한다.
	temp->first = NULL; 
	return temp;
}

int freeList(headNode* h){

	listNode* p = h->first;  //h를 통해, listNode 메모리를 해제한다.

	listNode* prev = NULL;  //previous로 headNode까지 메모리를 해제한다.
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}


int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //메모리 할당하여 노드를 생성한다.
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)  //공백인지 확인한다.
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = h->first;

	while(n != NULL) {
		if(n->key >= key) {  //key를 통해 새로운 노드를 추가할 위치를 찾고, key보다 큰 값 앞에 추가한다.
			if(n == h->first) {  //맨 앞쪽에 추가한다.
				h->first = node;
				node->link = n;
			} else {  
				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		trail = n;  //이전 노드의 링크를 변경해준다.
		n = n->link;
	}

	trail->link = node;  //전부 key보다 작은 경우에 가장 뒤쪽에 추가한다.
	return 0;
}

/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //새로운 노드를 할당한다.
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)  //공백인지 확인한다.
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->link != NULL) {  //맨 마지막에 노드를 추가한다.
		n = n->link;
	}
	n->link = node;
	return 0;
}


int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //노드를 새로 하나 할당한다.
	node->key = key; 

	node->link = h->first;  //노드를 list 맨 앞쪽에 추가한다.
	h->first = node;

	return 0;
}


int deleteNode(headNode* h, int key) {

	if (h->first == NULL)  //공백인지 확인한다.
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	while(n != NULL) {  //key를 통해 해제할 노드를 찾는다.
		if(n->key == key) {
			if(n == h->first) {  //맨 앞쪽 노드일 경우.
				h->first = n->link;
			} else { 
				trail->link = n->link;
			}
			free(n);  //해당 노드를 해제한다.
			return 0;
		}

		trail = n;  //이전 노드의 링크를 변경해준다.
		n = n->link;
	}

	printf("cannot find the node for key = %d\n", key);  //key에 대해 노드를 찾지 못한 경우에 오류문을 출력한다.
	return 0;

}


int deleteLast(headNode* h) {

	if (h->first == NULL)  //공백인지 확인한다.
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	if(n->link == NULL) {  //노드가 한개인 경우이다.
		h->first = NULL;
		free(n);
		return 0;
	}

	/* 마지막 노드까지 이동 */
	while(n->link != NULL) {  //맨 마지막 노드에 접근하여 해체한다.
		trail = n;
		n = n->link;
	}

	trail->link = NULL;  //이전 노드의 링크를 Null로 변경한다.
	free(n);

	return 0;
}


int deleteFirst(headNode* h) {

	if (h->first == NULL)  //공백인지 확인한다.
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;  //맨 앞쪽의 노드를 해제한다.

	h->first = n->link;
	free(n);

	return 0;
}


int invertList(headNode* h) {


	if(h->first == NULL) {  //공백인지 확인한다.
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;  
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){  //연결 리스트의 링크가 원래와 역순으로 연결되도록 한다. 
		trail = middle;
		middle = n;
		n = n->link;
		middle->link = trail;
	}

	h->first = middle;

	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {  //공백인지 확인한다.
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {  //맨 앞쪽부터 마지막까지 리스트들을 출력한다.
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);  //리스트 개수를 출력한다.
}

