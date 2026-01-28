#include <stdlib.h>
#include "list.h"

/* lstcreate: Creates an empty linked list. */
List *lstcreate() {
    List *lst = (List *)malloc(sizeof(List));

    lst->head = NULL;
    lst->size = 0;

    return lst;
}

/* lstdestroy: Destroys an existing linked list. */
void lstdestroy(List *lst) {
    Node *cur = lst->head;

    while (cur != NULL) {
        Node *next = cur->next;
        free(cur);
        cur = next;
    }

    free(lst);
}

/* lstget: Gets an element in a linked list. */
void *lstget(List *lst, int idx) {
    return NULL;
}

/* lstset: Sets an element in a linked list. */
int lstset(List *lst, int idx, void *val) {
    return 0;
}

/* lstadd: Adds an element to a linked list. */
int lstadd(List *lst, int idx, void *val) {
    Node *node = (Node *)malloc(sizeof(Node));

    node->val = val;
    node->next = NULL;

    if (idx == 0) {
        node->next = lst->head;
        lst->head = node;
    }
    else {
        Node *cur = lst->head;
        int i;

        for (i = 0; i < idx - 1; i++) {
            cur = cur->next;
        }

        node->next = cur->next;
        cur->next = node;
    }

    (lst->size)++;

    return 0;
}

/* lstremove: Removes an element from a linked list. */
void *lstremove(List *lst, int idx) {
    return NULL;
}
