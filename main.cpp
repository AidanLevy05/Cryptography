#include <iostream>
#include <fstream>
#include "Encrypt.h"
using namespace std;

int main() {

    ofstream output("output.txt");

    long long numbers[] = {
        32416190071,
        982451653,
        67280421310721,
        9999999967,
        32416187567,
        2305843009213693951,
        9223372036854775783,
        18446744073709551557ULL
    };

    int count = sizeof(numbers) / sizeof(numbers[0]);
    for (int i = 0; i < count; i++) {
        if (isPrime(numbers[i])) {
            output << numbers[i] << endl;
            cout << "Prime: " << numbers[i] << endl;
        } else {
            cout << "Composite: " << numbers[i] << endl;
        }
    }

    output.close();
    return 0;
    
}