// Copyright 2020 Dragne Lavinia-Stefana 314CA

#ifndef TEMA1_H__
#define TEMA1_H__

#define N_LUN 100
#define N_LUN1 61
#define N_LUN2 31
#define N_LUN3 5

struct Node {
	char nume_fisier[N_LUN1];
    char title[N_LUN2];
    char artist[N_LUN2];
    char album[N_LUN2];
    char year[N_LUN3];
    struct Node *next, *prev;
};

struct DoublyLinkedList {
	struct Node *head, *tail, *cursor;
	int size;
};

void init_list(struct DoublyLinkedList *list);

int pozitie_cursor(struct DoublyLinkedList *list);

int melody_exist(struct DoublyLinkedList *list, struct Node *Node);

void add_nth_node(struct DoublyLinkedList *list, int n, struct Node *Node);

void remove_nth_node(struct DoublyLinkedList *list, int n);

void free_list(struct DoublyLinkedList **pp_list);

void print_node(struct Node *currNode, FILE *g);

void SHOW_PLAYLIST(struct DoublyLinkedList *list, FILE *g);

void move_next(struct DoublyLinkedList *list, FILE *g);

void move_prev(struct DoublyLinkedList *list, FILE *g);

struct Node* pars_content_file (struct Node *new, FILE *h);

#endif  // TEMA1_H_
