#include "pfix.h"

int main(){
    string infix;
    cout << "Masukkan ekspresi matematika: ";
    cin >> infix;
    cout << "Ekspresi postfix: " << infixToPostfix(infix) << endl;
    cout << "Hasil : " << calculatePostfix(infixToPostfix(infix)) << endl;
    return 0;
}
