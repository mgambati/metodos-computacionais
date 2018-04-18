#include <iostream>
#include <stack>
#include "zero_of_function.h"

using namespace std;

void SelectionMenu() {
    cout << "Bem vindo, escolha uma das opções." << endl;
    cout << "1 - Calcular zero de funções" << endl;

    int selected;
    cin >> selected;

    switch (selected) {
        case 1:
            ShowZeroMenu();
            break;
        default:
            cout << "Saindo...";
    }
}


int main() {
    SelectionMenu();

    return 0;
}