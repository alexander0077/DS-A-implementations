#include <iostream>
#include <string.h>

#define MAX_COMMAND_LENGTH 3
#define BEFORE 0
#define AFTER 1
#define AMOUNT_OF_ITERATORS 10

using namespace std;

typedef unsigned long long int oct_b;

typedef struct list {
    oct_b key;
    struct list* next;
    struct list* previous;
} list_t;

void init(list_t* head) {

    head->next = nullptr;
    head->previous = nullptr;
}

char checkFirstCommand(char* command){

    if (strcmp("I", command) == 0) return 0;
    if (strcmp(".A", command) == 0) return 1;
    if (strcmp("P", command) == 0) return 2;
    if (strcmp("A.", command) == 0) return 3;
    if (strcmp("R", command) == 0) return 4;
    if (strcmp("i", command) == 0) return 5;
    if (strcmp("+", command) == 0) return 6;
    if (strcmp("-", command) == 0) return 7;
    else return 'X';
}

void initList(list_t* head, list_t* tail, list_t* new_node){

    head->next = new_node;
    new_node->next = tail;
    new_node->previous = head;
    tail->previous = new_node;
}

void pushFront(list_t* head, list_t* new_node){

    list_t* tmp;
    tmp = head->next;
    head->next = new_node;
    new_node->previous = head;
    new_node->next = tmp;
    tmp->previous = new_node;
}

void pushEnd(list_t* tail, list_t* new_node){

    list_t* tmp;
    tmp = tail->previous;
    tmp->next = new_node;
    new_node->previous = tmp;
    new_node->next = tail;
    tail->previous = new_node;
}

void pushAfterElement(int index, list_t** tab, list_t* new_node, char how){

    list_t* after;
    list_t* tmp;
    if(how == AFTER){
        after = tab[index];
        tmp = after->next;
    }
    else {
        after = tab[index]->previous;
        tmp = after->next;
    }

    after->next = new_node;
    new_node->previous = after;
    new_node->next = tmp;
    tmp->previous = new_node;
}

void push(char how, list_t* head, list_t* tail, list_t **tab) {

    list_t* new_node = (list_t*)malloc(sizeof(list_t));

    char where[MAX_COMMAND_LENGTH];
    oct_b what;
    cin >> where;
    cin >> what;

    new_node->key = what;

    if (head->next == tail) initList(head, tail, new_node); //kiedy lista jest pusta tworzymy od zera nowy node nie wazne czy przed czy po
    else {
        if (strcmp("BEG", where) == 0) pushFront(head, new_node);
        else if (strcmp("END", where) == 0) {
            if(how == BEFORE) pushEnd(tail->previous, new_node);
            else pushEnd(tail, new_node);
        }
        else {
            int index;
            index = atoi(where );
            pushAfterElement(index, tab, new_node, how);
        }

    }
}

void popEnd(list_t* tail){

    list_t* tmp;
    tmp = tail->previous;
    tmp->previous->next = tail;
    tail->previous = tmp->previous;
    free(tmp);
}

void popFront(list_t* head){

    list_t* tmp;
    tmp=head->next;
    head->next=tmp->next;
    tmp->next->previous=head;
    free(tmp);
}

void popByIndex(int index, list_t **tab){
    if(tab[index] != nullptr){
        list_t* tmp;
        tmp=tab[index];

        for(int i = 0; i < 10; i++){
            if(tab[i] == tmp){
                if(tab[i]->next->next == nullptr){
                    if(tab[i]->previous->previous == nullptr) {
                        tab[i]=nullptr;
                    }
                    else tab[i]=tab[i]->previous;
                }
                else tab[i]=tab[i]->next;
            }
        }
        tmp->previous->next=tmp->next;
        tmp->next->previous=tmp->previous;
        free(tmp);
    }

}

void pop(list_t* head, list_t* tail, list_t** tab) {

    char what[MAX_COMMAND_LENGTH];
    cin >> what;
    if(head->next != nullptr){
        if (strcmp("BEG", what) == 0) popFront(head);
        else if (strcmp("END", what) == 0) popEnd(tail);
        else {
            int index;
            index = atoi(what );
            popByIndex(index, tab);
        }

    }
}

void printAll(list_t *head, list_t *tail) {

    list_t* tmp;
    tmp = head->next;
    while ( tmp != tail ) {
        cout << tmp->key << " ";
        tmp = tmp->next;
    }
    cout << endl;
}

void printCommand(list_t *head, list_t **tab, list_t *tail){

    char which[MAX_COMMAND_LENGTH];
    cin >> which;
    if (strcmp("ALL", which) == 0) printAll(head, tail);
    else {
        int index;
        index = atoi(which );
        if(tab[index] != nullptr){
            cout << tab[index]->key << endl;
        }
    }
}

void setIterator(list_t *head, list_t *tail, list_t **tab, int index_of_iterator){

    char where_to_show[MAX_COMMAND_LENGTH];
    cin >> where_to_show;
    if (strcmp("BEG", where_to_show) == 0) tab[index_of_iterator] = head->next;
    else if (strcmp("END", where_to_show) == 0) tab[index_of_iterator] = tail->previous;
    else {
        int index;
        index = atoi(where_to_show );
        tab[index_of_iterator] = tab[index];
    }
}

void moveForward(list_t **tab){

    int index_number;
    cin >> index_number;
    if(tab[index_number]->next->next != nullptr){
        tab[index_number] = tab[index_number]->next;
    }
}

void moveBackward(list_t **tab){

    int index_number;
    cin >> index_number;
    if(tab[index_number]->previous->previous != nullptr){
        tab[index_number] = tab[index_number]->previous;
    }
}

void eventHandler(list_t *head, list_t *tail, list_t **tab){

    char first_command[MAX_COMMAND_LENGTH];
    while(cin >> first_command){
        char buffer;
        buffer = checkFirstCommand(first_command);
        switch(buffer){
            case 0:
                int memory_size;
                cin >> memory_size;
                break;
            case 1:
                push(BEFORE, head, tail, tab);
                break;
            case 2:
                printCommand(head, tab, tail);
                break;
            case 3:
                push(AFTER, head, tail, tab);
                break;
            case 4:
                pop(head, tail, tab);
                break;
            case 5:
                int index;
                cin >> index;
                setIterator(head, tail, tab, index);
                break;
            case 6:
                moveForward(tab);
                break;
            case 7:
                moveBackward(tab);
                break;
            default: break;
        }

    }
}

int main() {

    list_t head;
    list_t tail;
    init(&head);
    init(&tail);

    head.next = &tail;
    tail.previous = &head;

    list_t *tab[AMOUNT_OF_ITERATORS];
    for(int i = 0; i < AMOUNT_OF_ITERATORS; i++){
        tab[i] = nullptr;
    }

    eventHandler(&head, &tail, tab);

    while(head.next != &tail){

        popEnd(&tail);
    }

    return 0;
}