#include <stdio.h>
#include <stdlib.h> // ���  malloc


typedef struct Node {
	int value;
	struct Node *next;
} Node; // ����� �� ������ ������ ��� struct �� ���������� ����� ���.


void push(Node **head, int data); // ���������� � ������
int pop(Node **head);  // ������� � ������
Node *getNth(Node *head, int n);
Node *getLast(Node *head);
void pushBack(Node *head, int value);
Node *getLastButOne(Node *head);
int popBack(Node **head);
void insert(Node *head, unsigned n, int val);
void printLinkedList(const Node *head);
int getLen(Node *head);
int deleteNth(Node **head, int n);
void fromArray(Node **head, int *arr, size_t size);

void main() {
	Node* head = NULL;
	int arr[] = { 1,2,3,4,5,6,7,8,9,10,11 };
	fromArray(&head, arr, sizeof(arr)/sizeof(arr[0]));
	printLinkedList(head);
	int l = getLen(head);
	int i = 0;
	while (i < l) {
		deleteNth(&head, i);
		i++;
		l--;
	}
	printLinkedList(head);
	getch();
}






void push(Node **head, int data) {
	// ��� ��� ��������� head ����������, �� ���������� ���������� ��������� �� ���������.
	Node *tmp = (Node *)malloc(sizeof(Node));  // ������� ����� ����, �� ������� ��������� ��������� ���������� tmp
	tmp->value = data; // ��������� ��� ��������
	tmp->next = (*head); // ���������� ��������� tmp �� ���������� ����
	(*head) = tmp;  // ���������� ��������� head �� ����� ��������� ���� tmp
}

int pop(Node **head) {
	// ������� pop: ��� ������� �������, �� ������� ��������� head � ���������� ��� ��������
	// ���������� ��������� head �� ��������� ������� � ������� ����
	Node *prev = NULL;
	int val;
	if (head == NULL) {
		exit(-1);
	}
	prev = (*head);
	val = prev->value;
	(*head) = (*head)->next;
	free(prev);
	return val;
}

Node *getNth(Node *head, int n) {
	// ���������� ��������� �� n-� ������� ������
	// ��� ��� �� ����� ����� ������ ������� ��������,
	// �� ������������ �������� ��������� �� n-�� ����� ���������������� ������� ���� ��������� ������.
	// ��� ����, ����� �������� ��������� �������, ����� ������� � ���� ����� ��������� next �������� ����
	int counter = 0;
	while (counter < n && head) {
		head = head->next;
		counter++;
	}
	return head;
}

Node *getLast(Node *head) {
	// ��� ���������� ���������� �������� ����� ���������� ���� �� ������ �������� �� ��� ���,
	// ���� ��������� next ������ �� ��������� �� ������ ������ NULL
	if (head == NULL) {
		return NULL;
	}
	while (head->next) {
		head = head->next;
	}
	return head;
}

void pushBack(Node *head, int value) {
	// ��������� ����� ������� � ����� ������
	// ��� ������� ������ �������� � ����� ������� �������� ��������� �� ��������� �������,
	// ����� ������ ����� �������, ����������� ��� �������� � ������������ ��������� next ������� �������� �� �����
	Node *last = getLast(head);
	Node *tmp = (Node *)malloc(sizeof(Node));
	tmp->value = value;
	tmp->next = NULL;
	last->next = tmp;
}

Node *getLastButOne(Node *head) {
	// ������� getLastButOne, ���������� ��������� �� ������������� �������
	if (head == NULL) {
		exit(-2);
	}
	if (head->next == NULL) {
		return NULL;
	}
	while (head->next->next) {
		head = head->next;
	}
	return head;
}

int popBack(Node **head) {
	Node *lastbn = NULL;
	//�������� NULL
	if (!head) {
		exit(-1);
	}
	//������ ����
	if (!(*head)) {
		exit(-1);
	}
	lastbn = getLastButOne(*head);
	//���� � ������ ���� �������
	if (lastbn == NULL) {
		int r = (*head)->value;
		free(*head);
		*head = NULL;
		return r;
	}
	else {
		int r = (lastbn->next)->value;
		free(lastbn->next);
		lastbn->next = NULL;
		return r;
	}
}

// �������� ���������� �������� � ������� � ����� ����� ��������� O(n).

void insert(Node *head, unsigned n, int val) {
	// ������� insert, ������� ��������� ����� n-�� ��-�� ������� ���������� � 0
	unsigned i = 0;
	Node *tmp = NULL;
	//������� ������ �������. ���� ����� �� ������� ������, �� ������� �� �����,
	//������ ������������� �� �����, ��������� ������� � �����
	while (i < n && head->next) {
		head = head->next;
		i++;
	}
	tmp = (Node *)malloc(sizeof(Node));
	tmp->value = val;
	//���� ��� �� ��������� �������, �� next ������������ �� ��������� ����
	if (head->next) {
		tmp->next = head->next;
		//����� �� NULL
	}
	else {
		tmp->next = NULL;
	}
	head->next = tmp;
}

void printLinkedList(const Node *head) {
	while (head) {
		printf("%d ", head->value);
		head = head->next;
	}
	printf("\n");
}

int deleteNth(Node **head, int n) {
	if (n == 0) {
		return pop(head);
	}
	else {
		Node *prev = getNth(*head, n - 1);
		Node *elm = prev->next;
		int val = elm->value;

		prev->next = elm->next;
		free(elm);
		return val;
	}
}

void deleteList(Node **head) {
	Node *prev = NULL;
	while ((*head)->next) {
		prev = (*head);
		(*head) = (*head)->next;
		free(prev);
	}
	free(*head);
}

void fromArray(Node **head, int *arr, size_t size) {
	// ������� ������ �� �������
	size_t i = size - 1;
	if (arr == NULL || size == 0) {
		return;
	}
	do {
		push(head, arr[i]);
	} while (i-- != 0);
}

int getLen(Node *head) {
	int l = 0;
	while (head) {
		l++;
		head = head->next;
	}
	return l;
}