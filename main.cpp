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
        9223372036854775783LL
    };

    int count = sizeof(numbers) / sizeof(numbers[0]);

    startTimer();
    for (int i = 0; i < count; i++) {
        if (isPrime(numbers[i])) {
            output << numbers[i] << endl;
            cout << "Prime: " << numbers[i] << endl;
        } else {
            cout << "Composite: " << numbers[i] << endl;
        }
    }
    double time = stopTimer();

    output.close();

    cout << "Total time: " << time << " seconds" << endl;
    return 0;
    
}