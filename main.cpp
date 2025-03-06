#include <iostream>
#include <ctime>
#include <Windows.h>
#include "matriz.h"
using namespace std;

int main() {
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
    srand(static_cast<unsigned int>(time(nullptr)));
    Matriz m;
    m.proceso();
    cout << "\nPresione Enter para continuar...";
    cin.get();

    return EXIT_SUCCESS;
}