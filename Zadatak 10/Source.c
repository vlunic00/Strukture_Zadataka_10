#include<stdio.h>
#include<stdlib.h>

struct tree;
typedef struct tree* Node;
typedef struct tree {
	int num;
	char op;
	Node right;
	Node left;
}_tree;

struct stack;
typedef struct stack* Position;
typedef struct stack {
	Node treeNode;
	Position next;
}_stack;

void createTree(char[20], Position, Node);
void push(Position, Node);
Position newPosition(a);
void putInTree(Position, Node, char);
Node newNode(char, int);
void pop(Position);
void printInfix(Node);

int main() {
	_tree root;
	root.num = 0;
	root.op = '\0';
	root.left = NULL;
	root.right = NULL;

	_stack head;
	head.next = NULL;

	createTree("postfix.txt", &head, &root);
	printInfix(&root);

	return 0;
}

void createTree(char fname[20], Position p, Node n) {

	FILE* fp = fopen(fname, "r");

	if (fp == NULL) {
		printf("Greska pri otvaranju datoteke!\n");
		return;
	}

	char temp = '\0';
	int i = 0;

	while (!feof(fp)) {
		fscanf(fp, "%c", &temp);	//getline funkcija nije radila zbog problema sa libraryom,
		i++;						//popravit u buducnosti
	}

	char* buffer = NULL;

	buffer = (char*)malloc(sizeof(char) * i);

	if (buffer == NULL) {
		printf("Problem pri alokaciji!\n");
		return;
	}

	i = 0;
	rewind(fp);

	while (!feof(fp)) {
		fscanf(fp, "%c", (buffer + i));
		i++;
	}

	fclose(fp);

	int returnValue = 1;
	int lenght = 0;
	int read = 0;
	int number = 0;
	char op = '\0';
	Node q = NULL;

	while (returnValue) {

		returnValue = sscanf(buffer + lenght, "%d%n", &number, &read);

		if (returnValue == 0) {
			returnValue = sscanf(buffer + lenght, " %c%n", &op, &read);
			putInTree(p, n, op);
		}
		else {
			q = newNode('\0', number);
			push(p, q);
		}
	}
}

void push(Position p, Node n) {

	Position q = newPosition(n);
	q->next = p->next;
	p->next = q;
}

Position newPosition(Node n) {
	Position q = NULL;

	q = (Position)malloc(sizeof(Position));
	
	if (q == NULL)
		printf("Greska pri alokaciji\n");

	q->treeNode = n;

		return q;
}

void putInTree(Position p, Node n, char c) {
	Node q = newNode(c, 0);

	q->right = p->next->treeNode;
	pop(p);
	q->left = p->next->treeNode;
	pop(p);

	push(p,q);

	if (p->next->next == NULL)
		n = p->next->treeNode;
}

Node newNode(char c, int a) {
	Node p = NULL;

	p = (Node)malloc(sizeof(Node));
	if (p == NULL)
		printf("Greska pri alokaciji\n");

	p->op = c;
	p->num = a;
	p->left = NULL;
	p->right = NULL;

	return p;
}

void pop(Position p) {
	Position temp = p->next;

	p->next = temp->next;
	temp->next = NULL;
	free(temp);
}

void printInfix(Node n) {

	if (n != NULL) {

		if (n->left != NULL && n->right != NULL)
			printf("(");

		if (n->left != NULL)
			printInfix(n->left);

		if (n->op != '\0')
			printf("%d", n->num);
		else
			printf("%c", n->op);

		if (n->right != NULL)
			printInfix(n->right);

		if (n->left != NULL && n->right != NULL)
			printf(")");
	}
}