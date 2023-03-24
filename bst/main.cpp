#include <iostream>

using namespace std;

typedef struct node {
    int key;
    struct node* left_child = nullptr;
    struct node* right_child = nullptr;
} node_t;

node_t* newNode(int new_key){
    node_t* tmp = new node_t;
    tmp->key = new_key;
    tmp->left_child = tmp->right_child = NULL;
    return tmp;
}

node_t* addElement(node_t* node, int new_key){
    if (node == NULL)
        return newNode(new_key);

    if (new_key < node->key)
        node->left_child = addElement(node->left_child, new_key);
    else
        node->right_child = addElement(node->right_child, new_key);

    return node;
}

void search(node_t* root, int what_to_find){
    node_t* tmp = root;
    while(tmp != NULL){
        if(tmp->key == what_to_find) {
            cout << "1" << endl;
            return;
        }
        else if(tmp->key > what_to_find){
            tmp = tmp->left_child;
        }
        else tmp = tmp->right_child;
    }
    cout << "0" << endl;
}

void findMax(node_t* root){
    node_t* tmp = root;
    while(tmp->right_child != NULL){
        tmp = tmp->right_child;
    }
    cout << tmp->key << endl;
}

void findMin(node_t* root){
    node_t* tmp = root;
    while(tmp->left_child != NULL){
        tmp = tmp->left_child;
    }
    cout << tmp->key << endl;
}

node_t* minValueNode(node_t* node){
    node_t* current = node;

    while (current && current->left_child != NULL){
        current = current->left_child;
    }

    return current;
}

node_t* deleteElement(node_t* root, int what_to_delete){
    if (root == NULL)
        return root;

    if (what_to_delete < root->key)
        root->left_child = deleteElement(root->left_child, what_to_delete);

    else if (what_to_delete > root->key)
        root->right_child = deleteElement(root->right_child, what_to_delete);

    else {
        if (root->left_child==NULL and root->right_child==NULL)
            return NULL;

        else if (root->left_child == NULL) {
            struct node* temp = root->right_child;
            delete root;
            return temp;
        }
        else if (root->right_child == NULL) {
            struct node* temp = root->left_child;
            delete root;
            return temp;
        }

        node_t* tmp = minValueNode(root->right_child);
        root->key = tmp->key;
        root->right_child = deleteElement(root->right_child, tmp->key);
    }
    return root;
}

int main() {
    bool does_game_end = false;
    char command;
    node_t* root = nullptr;
    while(!does_game_end){
        cin >> command;
        if(command == 'q') does_game_end = true;
        else if (command == '+') {
            int new_key;
            cin >> new_key;
            root = addElement(root, new_key);
        }
        else if (command == '?') {
            int what_to_find;
            cin >> what_to_find;
            search(root, what_to_find);
        }
        else if (command == 'M') {
            findMax(root);
        }
        else if (command == 'm') {
            findMin(root);
        }
        else if (command == '-') {
            int what_to_delete;
            cin >> what_to_delete;
            deleteElement(root, what_to_delete);
        }
    }
    return 0;
}
