#include <iostream>
#include <string>

using namespace std;

#define MAX_KEYS 100000

typedef struct word {
    string word;
    int reps;
    struct word* next;
} word_t;

int hashing(string buffer) {
    int tmp_key = 0;
    for(int i = 0; i < buffer.size(); i++){
        tmp_key += char(buffer[i]);
    }
    return tmp_key;
}

void newWord(word_t *tab, string buffer, int new_key){
    word_t *tmp = new word_t;
    tmp->word = buffer;
    tmp->reps = 1;
    tmp->next = nullptr;
    tab[new_key] = *tmp;
}

void addColision(word_t *tab, string buffer, int new_key){
    word_t* tmp_ptr = &tab[new_key];

    while(tmp_ptr != nullptr){

        if(tmp_ptr->word == buffer) {
            tmp_ptr->reps++;
            return;
        }
        else {
            if(tmp_ptr->next == nullptr) {
                tmp_ptr->next = new word_t;
                tmp_ptr = tmp_ptr->next;
                tmp_ptr->word = buffer;
                tmp_ptr->reps = 1;
                break;
            }
            else tmp_ptr = tmp_ptr->next;
        }
    }

}

void getAmountFromTable(word_t *tab, string buffer){
    buffer.erase(0, 1);
    int key = hashing(buffer);
    word_t* tmp_ptr = &tab[key];

    while(tmp_ptr != nullptr){
        if(tmp_ptr->word == buffer) {
            cout << tmp_ptr->reps << endl;
            return;
        }
        else tmp_ptr = tmp_ptr->next;
    }
    cout << "0" << endl;

}

bool ifEmpty(word_t *tab, int new_key){
    if(hashing(tab[new_key].word) == new_key) return false;
    else return true;
}


void addWord(word_t *tab, string buffer){
    int new_key;
    new_key = hashing(buffer);
    bool if_empty = ifEmpty(tab, new_key);

    if(if_empty){
        newWord(tab, buffer, new_key);
    }
    else addColision(tab, buffer, new_key);
}

void removeWordFromTable(word_t *tab, string buffer){
    buffer.erase(0, 1);
    int key = hashing(buffer);
    word_t* tmp_ptr = &tab[key];

    while(tmp_ptr != nullptr){
        if(tmp_ptr->word == buffer) {
            tmp_ptr->reps = 0;
            return;
        }
        else tmp_ptr = tmp_ptr->next;
    }
}

int main() {
    word_t* tab = new word_t [MAX_KEYS];

    string buffer_word;
    bool if_ended = false;
    while(!if_ended){
        cin >> buffer_word;
        if(buffer_word == "q") if_ended = true;
        else if(buffer_word[0] == '?') getAmountFromTable(tab, buffer_word);
        else if(buffer_word[0] == '-') removeWordFromTable(tab, buffer_word);
        else {
            addWord(tab, buffer_word);
        }
    }
    return 0;
}
