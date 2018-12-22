#include <stdio.h>
#include <stdlib.h> // для  malloc


typedef struct Node {
	int value;
	struct Node *next;
} Node; // Чтобы не писать каждый раз struct мы определили новый тип.


void push(Node **head, int data); // добавление в начало
int pop(Node **head);  // удалени с головы
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
	// Так как указатель head изменяется, то необходимо передавать указатель на указатель.
	Node *tmp = (Node *)malloc(sizeof(Node));  // Создали новый узел, на который ссылается локальная переменная tmp
	tmp->value = data; // Присвоили ему значение
	tmp->next = (*head); // Перекинули указатель tmp на предыдущий узел
	(*head) = tmp;  // Перекинули указатель head на вновь созданный узел tmp
}

int pop(Node **head) {
	// функция pop: она удаляет элемент, на который указывает head и возвращает его значение
	// Перекинули указатель head на следующий элемент и удалили узел
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
	// возвращает указатель на n-й элемент списка
	// Так как мы знаем адрес только первого элемента,
	// то единственным способом добраться до n-го будет последовательный перебор всех элементов списка.
	// Для того, чтобы получить следующий элемент, нужно перейти к нему через указатель next текущего узла
	int counter = 0;
	while (counter < n && head) {
		head = head->next;
		counter++;
	}
	return head;
}

Node *getLast(Node *head) {
	// Для нахождение последнего элемента будем передирать друг за другом элементы до тех пор,
	// пока указатель next одного из элементов не станет равным NULL
	if (head == NULL) {
		return NULL;
	}
	while (head->next) {
		head = head->next;
	}
	return head;
}

void pushBack(Node *head, int value) {
	// добавляет новый элемент в конец списка
	// Для вставки нового элемента в конец сначала получаем указатель на последний элемент,
	// затем создаём новый элемент, присваиваем ему значение и перекидываем указатель next старого элемента на новый
	Node *last = getLast(head);
	Node *tmp = (Node *)malloc(sizeof(Node));
	tmp->value = value;
	tmp->next = NULL;
	last->next = tmp;
}

Node *getLastButOne(Node *head) {
	// функция getLastButOne, возвращает указатель на предпоследний элемент
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
	//Получили NULL
	if (!head) {
		exit(-1);
	}
	//Список пуст
	if (!(*head)) {
		exit(-1);
	}
	lastbn = getLastButOne(*head);
	//Если в списке один элемент
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

// Удаление последнего элемента и вставка в конец имеют сложность O(n).

void insert(Node *head, unsigned n, int val) {
	// функция insert, которая вставляет после n-го эл-та индексы начинаются с 0
	unsigned i = 0;
	Node *tmp = NULL;
	//Находим нужный элемент. Если вышли за пределы списка, то выходим из цикла,
	//ошибка выбрасываться не будет, произойдёт вставка в конец
	while (i < n && head->next) {
		head = head->next;
		i++;
	}
	tmp = (Node *)malloc(sizeof(Node));
	tmp->value = val;
	//Если это не последний элемент, то next перекидываем на следующий узел
	if (head->next) {
		tmp->next = head->next;
		//иначе на NULL
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
	// создать список из массива
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