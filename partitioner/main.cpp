#include <iostream>
using namespace std;

bool ifPrimeNumber(int n){
    int i = 2;
    while ( n > i ){
        if ( n % i == 0){
            return false;
        }
        i++;
    }
    return true;
}

int nextPrimeNumber(int n){
    do{
        n++;
    }while(!ifPrimeNumber(n));
    return n;
}

void checkIfPrintPartitions( int* values, int base){
    int sum = 0;
    int a = 0;
    int if_have_been_written = 0;
    while ( (sum <= base) && (if_have_been_written == 0) ){
        sum += values[a];
        if( sum == base ) {
            cout << values[0];
            for (int j = 1; j < a + 1; j++) {
                cout << "+" << values[j];
            }
            cout << endl;
            if_have_been_written++;
        }
        a++;
    }
}

void partitions(int base, int largest){
    int length = (base - largest)/2 + 2;
    int * values = new int[length];
    values[0] = largest;
    for ( int i = 1; i < length; i++){
        values[i] = 2;
    }

    int index_to_change = 1;

    while(values[0] >= values[1]){


    int i = 0;
    while ( i < length){

        checkIfPrintPartitions(values, base);

        values[index_to_change + i] = nextPrimeNumber(values[index_to_change + i]);
        i++;
    }
        if( nextPrimeNumber(values[index_to_change]) <= largest){
            values[index_to_change] = nextPrimeNumber(values[index_to_change]);
        }
        else index_to_change++;
        for ( int k = index_to_change + 1; k < length; k++){
            values[k] = 2;
        }
    }
}

int main() {
    int how_many_tries;
    cin >> how_many_tries;
    for ( int i = 0; i < how_many_tries; i++){
        int positive_integer;
        cin >> positive_integer;
        int largest_value;
        cin >> largest_value;
        partitions(positive_integer, largest_value);
    }
    return 0;
}
