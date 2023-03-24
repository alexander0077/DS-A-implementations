#include <iostream>
#include <vector>
#include <string>

using namespace std;

typedef struct kopiec {
    string data;
} heap;

int compareData(string first, string second){ //1 first is bigger
    if (first.size() > second.size()) return 1;
    else if (first.size() < second.size()) return -1;
    else return first.compare(second);
}

void print(vector<heap*> heap_h){
    for( int i = 0; i < heap_h.size(); i++){
        cout << heap_h[i]->data << endl;
    }
}

void sortMin(vector<heap*>& heap_h){
    int i = heap_h.size() - 1; //index nowego elementu
    int j = ( i - 1 ) / 2; //index rodzica

    while(( i > 0 ) && (compareData(heap_h[i]->data, heap_h[j]->data) == -1)){ //raczej git ale moze trezba zmienic
        heap* tmp = heap_h[i];
        heap_h[i] = heap_h[j];
        heap_h[j] = tmp;
        i = j;
        j = ( i - 1 ) / 2;
    }
}

void sortMax(vector<heap*>& heap_h){
    int i = heap_h.size() - 1; //index nowego elementu
    int j = ( i - 1 ) / 2; //index rodzica

    while(( i > 0 ) && (compareData(heap_h[i]->data, heap_h[j]->data) == 1)){ //raczej git ale moze trezba zmienic
        heap* tmp = heap_h[i];
        heap_h[i] = heap_h[j];
        heap_h[j] = tmp;
        i = j;
        j = ( i - 1 ) / 2;
    }
}

void add(vector<heap*>& heap_h, bool is_it_min){
    heap* tmp = new heap;
    cin >> tmp->data;
    heap_h.push_back(tmp);

    if(is_it_min){
        sortMin(heap_h);
    }
    else {
        sortMax(heap_h);
    }
}

void popOneMin(vector<heap*>& heap_h){
    int last = heap_h.size() - 1;
    heap* tmp = heap_h[0];
    heap_h[0] = heap_h[last];
    heap_h[last] = tmp;
    delete heap_h[last];
    heap_h.erase(heap_h.begin() + last);

    int n = heap_h.size();
    if(n != 0){
        int i = 0;
        int j = 1;
        while(j < n){
            if(j + 1 < n){
                if(compareData(heap_h[j]->data, heap_h[j+1]->data) == 1) j = j + 1; //raczej jest dobrze ale moze do poprawki
            }
            if(compareData(heap_h[i]->data, heap_h[j]->data) == 1 ) {
                heap* tmp = heap_h[i];
                heap_h[i] = heap_h[j];
                heap_h[j] = tmp;
                i = j;
                j = 2 * i + 1;
            }
            else j = n + 1;
        }
    }
}

void popOneMax(vector<heap*>& heap_h){
    int last = heap_h.size() - 1;
    heap* tmp = heap_h[0];
    heap_h[0] = heap_h[last];
    heap_h[last] = tmp;
    delete heap_h[last];
    heap_h.erase(heap_h.begin() + last);

    int n = heap_h.size();
    if(n != 0){
        int i = 0;
        int j = 1;
        while(j < n){
            if(j + 1 < n){
                if(compareData(heap_h[j]->data, heap_h[j+1]->data) == -1) j = j + 1; //raczej jest dobrze ale moze do poprawki
            }
            if(compareData(heap_h[i]->data, heap_h[j]->data) == -1 ) {
                heap* tmp = heap_h[i];
                heap_h[i] = heap_h[j];
                heap_h[j] = tmp;
                i = j;
                j = 2 * i + 1;
            }
            else j = n + 1;
        }
    }
}

void remove(vector<heap*>& heap_h, bool is_it_min){
    cout << heap_h[0]->data << endl;
    if(is_it_min) popOneMin(heap_h);
    else popOneMax(heap_h);
}

int main() {
    char command;
    bool end_game = false;
    bool is_it_min = true;
    vector<heap*> heap_h;
    while(!end_game){
        cin >> command;
        if(command == 'q') {
            end_game = true;
            while(heap_h.size() > 0){
                delete heap_h[0];
                heap_h.erase(heap_h.begin());
            }
        }
        else if (command == '+'){
            add(heap_h, is_it_min);
        }
        else if (command == 'r'){
            //todo remove all and create new
        }
        else if(command == 'p'){
            print(heap_h);
        }
        else if(command == 's'){
            //todo resequence
        }
        else if(command == '-'){
            remove(heap_h, is_it_min);
        }
    }
    return 0;
}
