#include <iostream>

using namespace std;

#include "Matrix.h"
#include "Vect.h"

using namespace OOP;

int main() {

    Matrix m0;

    cout << "-----------\n";

    Vect v0;

    cout << "-----------\n";

    //сделать умножение
    v0 *= v0;

    v0 *= m0;

    m0 *= v0;

    v0 + v0;
    v0 - v0;

    m0 + v0;
    m0 - v0;

    v0 + m0;
    v0 - m0;

    m0 * v0;

    v0 * m0;
}
