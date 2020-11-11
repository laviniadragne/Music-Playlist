// Copyright 2020 Dragne Lavinia-Stefana 314CA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./tema1.h"

/*
 * Functie care trebuie apelata dupa alocarea unei liste, pentru a o initializa.
 * (Setare valori initiale pentru campurile specifice structurii LinkedList).
 */
void init_list(struct DoublyLinkedList *list) {
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->cursor = NULL;
}

// functie care calculeaza pozitia cursorului

int pozitie_cursor(struct DoublyLinkedList *list){
    // nu exista cursorul daca lista e nula sau nu exista lista
    if (list->head == NULL || list == NULL) return -1;
    struct Node *curr = list->head;
    int i = 0;
    // daca nu exista cursor in lista
    if (list->cursor == NULL) {
        return -1;
    }
    while (curr != list->cursor && i < list->size) {
        curr = curr->next;
        i++;
    }
    // daca s-a gasit pozitia cursorului
    if (i <= list->size){
        return i;
    } else {
        return -1;
      }
}

// functie care verifica daca un nod (melodie) e deja in lista si returneaza
// pe ce pozitie e

int melody_exist(struct DoublyLinkedList *list, struct Node *Node) {
    // daca lista e goala sau nu exista lista
    if (list->head == NULL || list == NULL) {
        return -1;
    }

    struct Node *curr = list->head;
    int poz = 0;
    // curr se opreste pe ultimul element (tail) daca nu se gaseste melodia
    while (strcmp(curr->nume_fisier, Node->nume_fisier) != 0
            && curr->next != NULL) {
        curr = curr->next;
        poz++;
    }
    // am gasit melodia in lista
    if (strcmp(curr->nume_fisier, Node->nume_fisier) == 0) {
        return poz;
    // melodia nu e in lista deja
    }   else {
            return -1;
        }
}

/*
 * Pe baza datelor trimise prin pointerul la o structura Node, se creeaza un nou nod care
   e adaugat pe pozitia n a listei reprezentata de pointerul list.
   Pozitiile din lista sunt indexate incepand cu 0.
 * Daca n < 0, eroare.
 */
void add_nth_node(struct DoublyLinkedList *list, int n, struct Node *Node) {
    // daca lista e goala sau e invalida pozitia
    if (list == NULL || n < 0) {
        return;
    }
    struct Node * new;
    new = (struct Node*)malloc(sizeof(struct Node));

    struct Node *first, *last;
    // initializez nodul
    snprintf(new->nume_fisier, sizeof(Node->nume_fisier),
            "%s", Node->nume_fisier);
    snprintf(new->title, sizeof(Node->title), "%s", Node->title);
    snprintf(new->album, sizeof(Node->album), "%s", Node->album);
    snprintf(new->year, sizeof(Node->year), "%s", Node->year);
    snprintf(new->artist, sizeof(Node->artist), "%s", Node->artist);
    new->next = NULL;
    new->prev = NULL;

    // daca lista e goala
    if (list->size == 0) {
        list->head = new;
        list->tail = new;
        list->cursor = new;
        list->head->next = NULL;
        list->head->prev = NULL;
        list->size++;
        return;
    }
    first = list->head;
    last = list->tail;
    // daca trebuie adaugat ca primul element
    if (n == 0) {
        // legatura primul-al doilea
        new->next = first;
        // legatura al doilea-primul
        first->prev = new;
        // legatura primul-NULL
        new->prev = NULL;
        list->head = new;
        list->size++;
        return;
    }
    // daca il adaug la final
    if (n >= list->size) {
        n = list->size;
        // ultimul-primul si primul-ultimul
        last->next = new;
        new->prev = last;
        // ultimul-NULL
        new->next = NULL;
        list->tail = new;
        list->size++;
        return;
    }
    // daca il adaug aleator
    if (n < list->size) {
        int i;
        // first pointeaza pe pozitia i+1
        for (i = 0; i < n-1; i++) {
            first = first->next;
        }
        // first va pointa pe pozitia n-1
        // legatura new - nodul de pe pozitia n
        new->next = first->next;
        first->next->prev = new;
        // legatura new - first (nodul de pe pozitia n - 1)
        first->next = new;
        new->prev = first;
        list->size++;
        return;
    }
}

/*
 * Elimina nodul de pe pozitia n din lista al carei pointer este trimis ca parametru.
 * Pozitiile din lista se indexeaza de la 0.
 * Daca n < 0, eroare.
 */

void remove_nth_node(struct DoublyLinkedList *list, int n) {
    // daca lista nu exista sau e goala nu pot sterge din ea
    if (list == NULL || list->head == NULL || n < 0) {
        return;
    }
    struct Node* first = list->head;
    struct Node* last = list->tail;
    // daca trebuie sa sterg primul nod
    if (n == 0) {
        // daca am un singur element lista va deveni goala
        if (list->size == 1) {
            free(list->head);
            list->head = NULL;
            list->tail = NULL;
            list->cursor = NULL;
        } else {
            // mut inceputul listei pe a 2-a pozitie
            if (list->cursor == list->head) {
                list->cursor = list->head->next;
            }
            list->head = list->head->next;
            // fac legatrura primul-ultimul
            free(list->head->prev);
            list->head->prev = NULL;
            }
            list->size--;
            return;
    }
    struct Node *curr;
    // daca trebuie sa sterg ultimul element
    if ((n+1) >= list->size) {
        // daca cursorul este pe ultimul element il mut
        if (list->cursor == list->tail) {
            list->cursor = list->tail->prev;
        }
        // legatura dintre penultimul si NULL
        last->prev->next = NULL;
        list->tail = last->prev;
        list->size--;
        free(last);
        return;
    }
    curr = list->head->next;
    // sterg aleator din lista
    if ((n+1) < list->size) {
        int i;
        for (i = 0; i < n - 1; i++) {
            first = curr;
            curr = curr->next;
        }
        // daca cursorul este pe nodul ce trebuie sters il mut
        if (list->cursor == curr){
            list->cursor = curr->next;
        }
        // sar un nod
        first->next = curr->next;
        // refac si legatura inapoi
        curr->next->prev = first;
        list->size--;
        free(curr);
        return;
    }
    return;
}

/*
 * Procedura elibereaza memoria folosita de toate nodurile din lista, iar la sfarsit,
   elibereaza memoria folosita de structura lista.
 */
void free_list(struct DoublyLinkedList **pp_list) {
    if ((*pp_list) == NULL) return;
    if ((*pp_list)->head == NULL) {
             free(*pp_list);
           * pp_list = NULL;
            return;
    }
    struct Node *curr, *new;
    new = (*pp_list)->head;
    while (new) {
      curr = new;
      new = new->next;
      free(curr);
    }
    free(*pp_list);
    * pp_list = NULL;
}


// printez un nod

void print_node(struct Node *currNode, FILE *g) {
    fprintf(g, "Title: %.30s\n", currNode->title);
    fprintf(g, "Artist: %.30s\n", currNode->artist);
    fprintf(g, "Album: %.30s\n", currNode->album);
    fprintf(g, "Year: %.4s\n", currNode->year);
}

void SHOW_PLAYLIST(struct DoublyLinkedList *list, FILE *g) {
    struct Node *curr;
    // daca lista e goala sau nu exista
    if (list == NULL || list->head == NULL) {
        fprintf(g, "[]");
        return;
    }
    curr = list->head;
    while (curr != NULL) {
        // daca e prima melodie
        if (curr == list->head){
            fprintf(g, "[");
        }
        // daca nu e ultima melodie
        if (curr->next != NULL) {
            fprintf(g, "%.30s; ", curr->title);
        // daca e ultima
        } else {
            fprintf(g, "%.30s]\n", curr->title);
        }
        curr = curr->next;
    }
}

void move_next(struct DoublyLinkedList *list, FILE *g) {
    // daca nu exista cursorul
     if (list->cursor == NULL) {
        fprintf(g, "Error: no track playing\n");
        return;
    }
    // daca lista e goala sau nu exista sau e cursorul deja la final ignor
    if (list == NULL || list->head == NULL || list->cursor == list->tail) {
        return;
    }
    list->cursor = list->cursor->next;
}

void move_prev(struct DoublyLinkedList *list, FILE *g) {
    // daca nu exista cursorul
    if (list->cursor == NULL) {
        fprintf(g, "Error: no track playing\n");
        return;
    }
    // daca lista e goala sau nu exista sau e cursorul deja la inceput ignor
    if (list == NULL || list->head == NULL || list->cursor == list->head) {
        return;
    }
    list->cursor = list->cursor->prev;
}

// functie de parsat continutul din fisierul de intrare

struct Node* pars_content_file(struct Node *new, FILE *h) {
    // parsez anul
    fseek(h, -4, SEEK_END);
    fread(new->year, 1, 4, h);
    new->year[strlen(new->year)] = '\0';
    // parsez albumul
    fseek(h, -34, SEEK_END);
    fread(new->album, 1, 30, h);
    new->album[strlen(new->album)] = '\0';
    // parsez artistul
    fseek(h, -64, SEEK_END);
    fread(new->artist, 1, 30, h);
    new->artist[strlen(new->artist)] = '\0';
    // parsez title-ul
    fseek(h, -94, SEEK_END);
    fread(new->title, 1, 30, h);
    new->title[strlen(new->title)] = '\0';

    return new;
}

int main(int argc, char *argv[]) {
    // daca nu sunt date bine fisierele .in .out
    if (argc != 3) {
        exit(-1);
    }
    // f = pointer la fisierul .in
    // g = pointer la fisierul .out
    FILE * f = fopen(argv[1], "rt");
    FILE * g = fopen(argv[2], "wt");
    if (f == NULL || g == NULL) {
        exit(-1);
    }
    char comanda[N_LUN], *p, name_song[N_LUN], comanda1[N_LUN];
    char comanda2[N_LUN], name_file_song[N_LUN];
    struct DoublyLinkedList *list;
    struct Node *currNode;
    currNode = calloc(1, sizeof(struct Node));
    // aloc lista
    list = malloc(sizeof(struct DoublyLinkedList));
    // initializez lista
    init_list(list);
    // citesc q-ul, dar nu il folosesc
    fgets(comanda, N_LUN, f);
    // cat timp exista comenzi in fisierul media.in
    while (fgets(comanda, N_LUN, f )) {
        char *rest = NULL;
        p = strtok_r(comanda, "_", &rest);
        snprintf(comanda1, N_LUN, "%s", p);
        p = strtok_r(NULL, " \n", &rest);
        snprintf(comanda2, N_LUN, "%s", p);
        name_song[0] = '\0';

        // daca comanda admite name_song in structura, il extrag
        if (strcmp(comanda1, "ADD") == 0 || strcmp(comanda2, "SONG") == 0) {
            p = strtok_r(NULL, "\n", &rest);
            snprintf(name_song, N_LUN, "%s", p);
            snprintf(currNode->nume_fisier, sizeof(name_song), "%s", name_song);
        }

        if (name_song[0] != '\0') {
            // imi formez calea catre fisierul cu date de intrare
            snprintf(name_file_song, sizeof(name_song), "songs/%s", name_song);
            FILE * h = fopen(name_file_song, "rb");
            // deschid fisierul
            if (h == NULL){
                exit(-1);
                 // daca am reusit deschiderea fisierului
            } else {
                currNode = pars_content_file(currNode, h);
                int poz_anterior, poz_cursor;
                if (strcmp(comanda1, "ADD") == 0){
                    // verific daca melodia exista deja in lista
                        poz_anterior = melody_exist(list, currNode);
                        // aflu si pozitia cursorului
                        poz_cursor = pozitie_cursor(list);
                        if (strcmp(comanda2, "FIRST") == 0) {
                            // adaug nodul pe prima pozitie
                            add_nth_node(list, 0, currNode);
                            // daca s-a mai regasit in lista il sterg
                            if (poz_anterior != -1) {
                                remove_nth_node(list, poz_anterior + 1);
                            }
                        }
                        if (strcmp(comanda2, "LAST") == 0) {
                            // adaug nodul pe ultima pozitie din lista
                            add_nth_node(list, list->size, currNode);
                            // daca nodul deja exista in lista il sterg
                            // de pe pozitia anterioara
                            if (poz_anterior != -1) {
                                remove_nth_node(list, poz_anterior);
                            }
                        }
                        if (strcmp(comanda2, "AFTER") == 0) {
                            // daca exista cursorul si nu este pe melodia
                            // ce vreau sa o adaug dupa el
                             if ((poz_cursor != -1)
                                && (poz_anterior != poz_cursor)) {
                                    add_nth_node(list, poz_cursor+1, currNode);
                                    // daca exista in lista inainte il sterg
                                    if (poz_anterior != -1) {
                                         if (poz_cursor > poz_anterior){
                                            remove_nth_node(list, poz_anterior);
                                         }
                                         if (poz_cursor < poz_anterior) {
                                            remove_nth_node(list,
                                                poz_anterior + 1);
                                        }
                                    }
                             }
                        }
                }
                // daca am de dat delete la un song
                if (strcmp(comanda2, "SONG") == 0){
                    // aflu pe ce pozitie e acel cantec in lista
                    int poz_anterior = melody_exist(list, currNode);
                    // daca nu exista melodia in lista
                    if (poz_anterior == -1) {
                        fprintf(g, "Error: no song found to delete\n");
                    } else {
                            remove_nth_node(list, poz_anterior);
                    }
                }
                fclose(h);
            }
        }
                if (strcmp(comanda1, "DEL") == 0) {
                    int poz_cursor = pozitie_cursor(list);
                    if (strcmp(comanda2, "FIRST") == 0) {
                        // daca lista e goala
                        if (list->head == NULL || list == NULL) {
                            fprintf(g, "Error: delete from empty playlist\n");
                        } else {
                            // daca exista lista sterg nodul de pe pozitia 0
                            remove_nth_node(list, 0);
                           }
                    }
                    if (strcmp(comanda2, "LAST") == 0) {
                        // daca lista e goala
                        if (list->head == NULL || list == NULL) {
                            fprintf(g, "Error: delete from empty playlist\n");
                            } else {
                                // sterg nodul de pe ultima pozitie din lista
                                remove_nth_node(list, list->size-1);
                              }
                    }
                    if (strcmp(comanda2, "CURR") == 0) {
                        // daca nu exista lista sau e goala sau nu exista
                        // cursorul nu pot sterge curenta
                        if (list->head == NULL || list == NULL
                            || list->cursor == NULL) {
                                fprintf(g, "Error: no track playing\n");
                        } else {
                            // sterg melodia la care e cursorul
                                remove_nth_node(list, poz_cursor);
                        }
                    }
                }
                if (strcmp(comanda1, "MOVE") == 0) {
                    if (strcmp(comanda2, "NEXT") == 0) {
                        move_next(list , g);
                    }
                    if (strcmp(comanda2, "PREV") == 0) {
                        move_prev(list, g);
                    }
                }
                if (strcmp(comanda1, "SHOW") == 0){
                    if (strcmp(comanda2, "FIRST") == 0) {
                        // daca lista e goala
                        if (list->head == NULL) {
                            fprintf(g, "Error: show empty playlist\n");
                        // printez melodia de pe prima pozitie
                        } else {
                            print_node(list->head, g);
                        }
                    }
                    if (strcmp(comanda2, "LAST") == 0) {
                        // daca lista e goala
                        if (list->tail == NULL) {
                            fprintf(g, "Error: show empty playlist\n");
                            // printez melodia de pe ultima pozitie
                        } else {
                            print_node(list->tail, g);
                        }
                    }
                    if (strcmp(comanda2, "CURR") == 0) {
                        // daca nu exista cursorul
                        if (list->cursor == NULL) {
                            fprintf(g, "Error: show empty playlist\n");
                            // printez melodia de pe pozitia
                            // curenta a cursorului
                        } else {
                         print_node(list->cursor, g);
                     }
                    }
                    if (strcmp(comanda2, "PLAYLIST") == 0) {
                        SHOW_PLAYLIST(list, g);
                    }
                }
    }
    fclose(f);
    fclose(g);
    free(currNode);
    free_list(&list);
    return 0;
}
