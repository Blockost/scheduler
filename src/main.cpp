#include <iostream>

using namespace std;

int main() {

    #pragma omp parallel
    {
        // Code inside this region runs in parallel.
        cout << "Hello\n";
    }
}
