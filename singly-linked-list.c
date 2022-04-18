#include<stdio.h>
#include<stdlib.h>


typedef struct Node {
	int key;
	struct Node* link;  //����� ��ũ�� �����Ѵ�.(���� Node��� ����ü Ÿ���� ������� �ʾ����Ƿ� struct ���̴� ������ ������ �߻��Ѵ�.)
}listNode;

typedef struct Head {
	struct Node* first;  //���Ḯ��Ʈ�� ù ��带 ����ų �����͸� �����Ѵ�. 
}headNode;


/* �Լ� ����Ʈ */
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
		printf("              [---------���� 2021041081---------]\n");
		printf("----------------------------------------------------------------\n");  //��� �޴��� ����Ѵ�.
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

		switch(command) {  //Ŀ��忡 ���� �Լ��� ȣ���Ѵ�.
		case 'z': case 'Z':
			headnode = initialize(headnode);  //�޸𸮰� �Ҵ�� listNode�� �ʱ�ȭ�ϴ� �Լ� ȣ��.
			break;
		case 'p': case 'P':
			printList(headnode);  //����Ʈ���� ����ϴ� �Լ� ȣ��.
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);  //�Է¹��� key�� ���� ��带 �߰��� �����ϴ� �Լ� ȣ��.
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);  //�Է¹��� key�� ���� ��带 ����(����)�ϴ� �Լ� ȣ��.
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);  //�� �������� ��带 �߰��ϴ� �Լ� ȣ��.
			break;
		case 'e': case 'E':
			deleteLast(headnode);  //�� ������ ��带 ����(����)�ϴ� �Լ� ȣ��.
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);  //�� ���ʿ� ��带 �߰��ϴ� �Լ� ȣ��.
			break;
		case 't': case 'T':
			deleteFirst(headnode);  //�� ���� ��带 ����(����)�ϴ� �Լ� ȣ��.
			break;
		case 'r': case 'R':
			invertList(headnode);  //������ ��ũ�� ������ �������� ��ũ�ϵ��� �����ϴ� �Լ� ȣ��.
			break;
		case 'q': case 'Q':
			freeList(headnode);  //�Ҵ�� �޸𸮸� ���� �����ϴ� �Լ� ȣ��.
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}

headNode* initialize(headNode* h) {

	if(h != NULL)  //��� ��尡 Null�� �ƴϸ�, �Ҵ�� �޸𸮸� ��� �����ϴ� freeNode�� ȣ���Ѵ�.
		freeList(h);
	
	headNode* temp = (headNode*)malloc(sizeof(headNode));  //headNodeũ���� �޸𸮸� �Ҵ��Ѵ�.
	temp->first = NULL; 
	return temp;
}

int freeList(headNode* h){

	listNode* p = h->first;  //h�� ����, listNode �޸𸮸� �����Ѵ�.

	listNode* prev = NULL;  //previous�� headNode���� �޸𸮸� �����Ѵ�.
	while(p != NULL) {
		prev = p;
		p = p->link;
		free(prev);
	}
	free(h);
	return 0;
}


int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //�޸� �Ҵ��Ͽ� ��带 �����Ѵ�.
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)  //�������� Ȯ���Ѵ�.
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = h->first;

	while(n != NULL) {
		if(n->key >= key) {  //key�� ���� ���ο� ��带 �߰��� ��ġ�� ã��, key���� ū �� �տ� �߰��Ѵ�.
			if(n == h->first) {  //�� ���ʿ� �߰��Ѵ�.
				h->first = node;
				node->link = n;
			} else {  
				node->link = n;
				trail->link = node;
			}
			return 0;
		}

		trail = n;  //���� ����� ��ũ�� �������ش�.
		n = n->link;
	}

	trail->link = node;  //���� key���� ���� ��쿡 ���� ���ʿ� �߰��Ѵ�.
	return 0;
}

/**
 * list�� key�� ���� ����ϳ��� �߰�
 */
int insertLast(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //���ο� ��带 �Ҵ��Ѵ�.
	node->key = key;
	node->link = NULL;

	if (h->first == NULL)  //�������� Ȯ���Ѵ�.
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->link != NULL) {  //�� �������� ��带 �߰��Ѵ�.
		n = n->link;
	}
	n->link = node;
	return 0;
}


int insertFirst(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));  //��带 ���� �ϳ� �Ҵ��Ѵ�.
	node->key = key; 

	node->link = h->first;  //��带 list �� ���ʿ� �߰��Ѵ�.
	h->first = node;

	return 0;
}


int deleteNode(headNode* h, int key) {

	if (h->first == NULL)  //�������� Ȯ���Ѵ�.
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	while(n != NULL) {  //key�� ���� ������ ��带 ã�´�.
		if(n->key == key) {
			if(n == h->first) {  //�� ���� ����� ���.
				h->first = n->link;
			} else { 
				trail->link = n->link;
			}
			free(n);  //�ش� ��带 �����Ѵ�.
			return 0;
		}

		trail = n;  //���� ����� ��ũ�� �������ش�.
		n = n->link;
	}

	printf("cannot find the node for key = %d\n", key);  //key�� ���� ��带 ã�� ���� ��쿡 �������� ����Ѵ�.
	return 0;

}


int deleteLast(headNode* h) {

	if (h->first == NULL)  //�������� Ȯ���Ѵ�.
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	if(n->link == NULL) {  //��尡 �Ѱ��� ����̴�.
		h->first = NULL;
		free(n);
		return 0;
	}

	/* ������ ������ �̵� */
	while(n->link != NULL) {  //�� ������ ��忡 �����Ͽ� ��ü�Ѵ�.
		trail = n;
		n = n->link;
	}

	trail->link = NULL;  //���� ����� ��ũ�� Null�� �����Ѵ�.
	free(n);

	return 0;
}


int deleteFirst(headNode* h) {

	if (h->first == NULL)  //�������� Ȯ���Ѵ�.
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;  //�� ������ ��带 �����Ѵ�.

	h->first = n->link;
	free(n);

	return 0;
}


int invertList(headNode* h) {


	if(h->first == NULL) {  //�������� Ȯ���Ѵ�.
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;  
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){  //���� ����Ʈ�� ��ũ�� ������ �������� ����ǵ��� �Ѵ�. 
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

	if(h == NULL) {  //�������� Ȯ���Ѵ�.
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {  //�� ���ʺ��� ���������� ����Ʈ���� ����Ѵ�.
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->link;
		i++;
	}

	printf("  items = %d\n", i);  //����Ʈ ������ ����Ѵ�.
}

