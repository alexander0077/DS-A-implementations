#include <iostream>
#include <string.h>

#define SYMBOL_OF_PLAYER_ONE '1'
#define SYMBOL_OF_PLAYER_TWO '2'
#define SYMBOL_OF_DRAW '0'
#define EMPTY_POLES '0'
#define SYMBOL_OF_NOT_FINISHED '3'
#define MODE_ONE 1
#define MODE_TWO 2
#define MODE_THREE 3
#define MAX_COMMAND_LENGTH 50

using namespace std;

typedef struct tree {
    int amount_of_children;
    char** board;
    char player;
    struct tree** children;
    char result;
} node;

void freeMemory(node* current_node){
    delete [] current_node->board;
}

short checkCommand(char* command){
    if(strcmp("GEN_ALL_POS_MOV", command) == 0) return 1;
    else if(strcmp("GEN_ALL_POS_MOV_CUT_IF_GAME_OVER", command) == 0) return 2;
    else if(strcmp("SOLVE_GAME_STATE", command) == 0) return 3;
    else return 0;
}

int countPoles(char** board, int n, int m, char pawn){
    int poles = 0;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            cin >> board[i][j];
            if(board[i][j] == pawn) poles++;
        }
    }
    return poles;
}

char checkStatusOfGame(char** board, int n, int m, int k, int mode){
    char pawn;

    for(int i = 0; i < n; i++){
        for(int j = 0; j <= m - k; j++){ //horizontal check
            pawn = board[i][j];
            if(pawn != EMPTY_POLES){
                int tmp = 1;
                for(int z = 1; z + j < m; z++){
                    if(board[i][j + z] == pawn) tmp++;
                    else break;
                }
                if(tmp >= k) return pawn;
            }
        }
    }

    for(int j = 0; j < m; j++){
        for(int i = 0; i <= n - k; i++){ //vertical check
            pawn = board[i][j];
            if(pawn != EMPTY_POLES){
                int tmp = 1;
                for(int z = 1; z + i < n; z++){
                    if(board[i + z][j] == pawn) tmp++;
                    else break;
                }
                if(tmp >= k) return pawn;

            }
        }
    }

    for(int i = n - 1; i + 1 >= k; i--){
        for(int j = 0; j <= (m - k); j++){ //cross check up and right
            pawn = board[i][j];
            if(pawn != EMPTY_POLES){
                int tmp = 1;
                for(int z = 1; (z + j < m) && (i - z > -1); z++){
                    if(board[i - z][j + z] == pawn) tmp++;
                    else break;
                }
                if(tmp >= k) return pawn;
            }
        }
    }

    for(int i = n - 1; i + 1 >= k; i--){
        for(int j = m - 1; j + 1 >= k; j--){ //cross check up and left
            pawn = board[i][j];
            if(pawn != EMPTY_POLES){
                int tmp = 1;
                for(int z = 1; (j - z > -1) && (i - z > -1); z++){
                    if(board[i - z][j - z] == pawn) tmp++;
                    else break;
                }

                if(tmp >= k) return pawn;
            }
        }
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(board[i][j] == EMPTY_POLES) return SYMBOL_OF_NOT_FINISHED;
        }
    }

    return SYMBOL_OF_DRAW;
}


node* createNewNode(node* new_node, node* parent, char pawn, int n, int m, int k, int iterator, int mode){
    if(parent->player == SYMBOL_OF_PLAYER_ONE) new_node->player = SYMBOL_OF_PLAYER_TWO;
    else new_node->player = SYMBOL_OF_PLAYER_ONE;

    int counter_of_zeros = 0;

    new_node->children = new node *[parent->amount_of_children - 1];
    new_node->amount_of_children = parent->amount_of_children - 1;


    char** new_board = new char * [n];
    for(int i = 0; i < n; i++){
        new_board[i] = new char [m];
    }

    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(parent->board[i][j] == EMPTY_POLES) {
                if(counter_of_zeros == iterator) {
                    if(mode == MODE_THREE) new_board[i][j] = new_node->player;
                    else new_board[i][j] = pawn;
                }
                else new_board[i][j] = parent->board[i][j];
                counter_of_zeros++;
            }
            else new_board[i][j] = parent->board[i][j];
        }
    }

    new_node->board = new_board;
    new_node->result = checkStatusOfGame(new_board, n, m, k, mode);

    return new_node;
}

void printBoard(char** board, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            printf("%c ",board[i][j]);
        }
        printf("\n");
    }
}


void generateAllPossibleMoves(int option){
    int n, m, k, non_used_poles;
    char player;
    bool if_printed = false;
    cin >> n;
    cin >> m;
    cin >> k;
    cin >> player;

    node root;
    if(player == SYMBOL_OF_PLAYER_ONE) root.player = SYMBOL_OF_PLAYER_TWO;
    else root.player = SYMBOL_OF_PLAYER_ONE;
    root.player = player;

    char** board = new char * [n];
    for(int i = 0; i < n; i++){
        board[i] = new char [m];
    }

    non_used_poles = countPoles(board, n, m, EMPTY_POLES);
    root.children = new node *[non_used_poles];

    if((checkStatusOfGame(board, n, m, k, option) == SYMBOL_OF_NOT_FINISHED) && (non_used_poles!=0)){
        root.board = board;
        root.amount_of_children = non_used_poles;

        for(int i = 0; i < non_used_poles; i++){
            root.children[i] = new node;
            root.children[i] = createNewNode(root.children[i], &root, root.player, n, m, k, i, 1);
        }

        if(option == MODE_TWO){

            if(non_used_poles == 1){
                if_printed = true;
                printf("1\n");
                printBoard(root.children[0]->board,  n, m); //if all poles are filled
            }
            else{
                for(int i = 0; i < root.amount_of_children; i++){
                    if(checkStatusOfGame(root.children[i]->board, n, m, k, option) != SYMBOL_OF_NOT_FINISHED){
                        if_printed = true;
                        printf("1\n");
                        printBoard(root.children[i]->board, n, m);
                        break;
                    }
                }
            }
        }

        if(!if_printed){
            printf("%i\n", non_used_poles);
            for(int z = 0; z < non_used_poles; z++){
                printBoard(root.children[z]->board,  n, m);
            }
        }
    }
    else printf("0\n");

}

char pushMinMax(node* current_node, int n, int m, int k){
    for(int i = 0; i < current_node->amount_of_children; i++){
        if(current_node->children[i]->result == current_node->children[i]->player){
            return current_node->children[i]->player;
        }
    }
    for(int i = 0; i < current_node->amount_of_children; i++){
        if(current_node->children[i]->result == SYMBOL_OF_DRAW) return SYMBOL_OF_DRAW;
    }
    return current_node->player;
}


void determineWinner(node* current_node, node* root, int n, int m, int k){
    for(int i = 0; i < current_node->amount_of_children; i++){
        if(root->result != SYMBOL_OF_NOT_FINISHED) break;
        if(current_node->children[i] != nullptr){
            if(current_node->children[i]->result == SYMBOL_OF_NOT_FINISHED) {
                determineWinner(current_node->children[i], root, n, m, k);
            }
        }
    }
    current_node->result = pushMinMax(current_node, n, m, k);
}

void generateChildren(node* current_node, int n, int m, int k){
    for(int i = 0; i < current_node->amount_of_children; i++){
        current_node->children[i] = new node;
        current_node->children[i] = createNewNode(current_node->children[i], current_node, current_node->player, n, m, k, i, 3);

        if(current_node->children[i]->result == SYMBOL_OF_NOT_FINISHED) {
            generateChildren(current_node->children[i], n, m, k);
        }
        if(current_node->children[i]->result == current_node->children[i]->player) { /** USPRAWNIENIE PIERWSZE **/
            current_node->result = current_node->children[i]->player;
            return;

        }
    }
}

void printResult(char result){
    if(result == SYMBOL_OF_PLAYER_ONE) printf("FIRST_PLAYER_WINS\n");
    else if (result == SYMBOL_OF_PLAYER_TWO) printf("SECOND_PLAYER_WINS\n");
    else printf("BOTH_PLAYERS_TIE\n");
}

void whoWin(){
    int n, m, k;
    char player;
    cin >> n;
    cin >> m;
    cin >> k;
    cin >> player;

    node root;

    if(player == SYMBOL_OF_PLAYER_ONE) root.player = SYMBOL_OF_PLAYER_TWO;
    else root.player = SYMBOL_OF_PLAYER_ONE;

    char** board = new char * [n];
    for(int i = 0; i < n; i++){
        board[i] = new char [m];
    }

    root.amount_of_children = countPoles(board, n, m, EMPTY_POLES);
    root.children = new node *[root.amount_of_children];
    root.board = board;
    root.result = checkStatusOfGame(board, n, m, k, MODE_THREE);

    if(checkStatusOfGame(board, n, m, k,MODE_THREE) == SYMBOL_OF_NOT_FINISHED) {
        generateChildren(&root, n, m, k);
        determineWinner(&root, &root, n, m, k);
    }

    printResult(root.result);

    freeMemory(&root);
}

int main() {
    char command[MAX_COMMAND_LENGTH];
    short iterator;
    while(cin >> command){
        iterator = checkCommand(command);
        switch(iterator){
            case 1:
                generateAllPossibleMoves(MODE_ONE);
                break;
            case 2:
                generateAllPossibleMoves(MODE_TWO);
                break;
            case 3:
                whoWin();
                break;
        }
    }

    return 0;
}
