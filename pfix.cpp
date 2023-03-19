#include "pfix.h"

// Membuat Stack dan Queue kosong
void createStack(Stack &S){
    Top(S) = -1;
}
void CreateStackInt(StackInt &S){
    Top(S) = -1;
}
void createQueue(Queue &Q){
    head(Q) = nil;
    tail(Q) = nil;
}
adrQ alokasiElemenQueue(string x){
    adrQ Q = new elmQueue;
    infoq(Q) = x;
    next(Q) = nil;
    return Q;
}

// Mengecek apakah Stack dan Queue kosong
bool isEmptyStack(Stack S){
    return Top(S) == -1;
}
bool isEmptyStackInt(StackInt S){
    return Top(S) == -1;
}
bool isEmptyQueue(Queue Q){
    return head(Q) == nil;
}

// Operasi Stack dan Queue
void Push(Stack &S, char x){
    if(Top(S) == 19){
        cout << "Stack penuh" << endl;
    }else{
        Top(S)++;
        infos(S)[Top(S)] = x;
    }
} // Yang dimasukkan ke stack adalah operator, misal +, -, *, /
char Pop(Stack &S){
    if(isEmptyStack(S)){
        cout << "Stack kosong" << endl;
        return ' ';
    }else{
        char x = infos(S)[Top(S)];
        Top(S)--;
        return x;
    }
} // Yang diambil dari stack adalah operator terakhir yang dimasukkan
void PushInt(StackInt &S, int x){
    if(Top(S) == 19){
        cout << "Stack penuh" << endl;
    }else{
        Top(S)++;
        infos(S)[Top(S)] = x;
    }
}
int PopInt(StackInt &S){
    if(isEmptyStackInt(S)){
        cout << "Stack kosong" << endl;
        return 0;
    }else{
        int x = infos(S)[Top(S)];
        Top(S)--;
        return x;
    }
}
void Enqueue(Queue &Q, string x){
    adrQ Qnew = alokasiElemenQueue(x);
    if(isEmptyQueue(Q)){
        head(Q) = Qnew;
        tail(Q) = Qnew;
    }else{
        next(tail(Q)) = Qnew;
        tail(Q) = Qnew;
    }
} // Yang dimasukkan ke queue adalah string, kumpulan angka, misal 23, 34, 100
string Dequeue(Queue &Q){
    if(isEmptyQueue(Q)){
        cout << "Queue kosong" << endl;
        return " ";
    }else{
        string x = infoq(head(Q));
        adrQ Qdel = head(Q);
        head(Q) = next(head(Q));
        delete Qdel;
        return x;
    }
}

// Operasi untuk mengubah infix menjadi postfix, dan menghitung postfix
bool isValidOperation(char x){ // Mengecek apakah karakter yang dimasukkan adalah operator, misal +, -, *, /
    return x == '+' || x == '-' || x == '*' || x == '/' || x == '^' || x == '(' || x == ')';
}
int precedence(char x){ // Mengecek prioritas operator, misal + dan - memiliki prioritas 1, * dan / memiliki prioritas 2, dan ^ memiliki prioritas 3
    if(x == '^'){
        return 3;
    }else if(x == '*' || x == '/'){
        return 2;
    }else if(x == '+' || x == '-'){
        return 1;
    }else{
        return 0;
    }
}
string infixToPostfix(string infix){ // Mengubah ekspresi infix menjadi postfix
    Stack S;
    createStack(S);
    Queue Q;
    createQueue(Q);
    string postfix = "";
    for(int i = 0; i < infix.length(); i++){
        if(infix[i] == ' '){
            continue;
        }else if(isdigit(infix[i])){
            string temp = "";
            while(isdigit(infix[i])){

                temp += infix[i];
                i++;
            }
            i--;
            Enqueue(Q, temp);
        }else if(isValidOperation(infix[i])){
            if(isEmptyStack(S)){
                Push(S, infix[i]);
            }else{
                if(infix[i] == '('){
                    Push(S, infix[i]);
                }else if(infix[i] == ')'){
                    while(infos(S)[Top(S)] != '('){
                        Enqueue(Q, string(1, Pop(S)));
                    }
                    Pop(S);
                }else{
                    if(precedence(infix[i]) > precedence(infos(S)[Top(S)])){
                        Push(S, infix[i]);
                    }else{
                        while(!isEmptyStack(S) && precedence(infix[i]) <= precedence(infos(S)[Top(S)])){
                            Enqueue(Q, string(1, Pop(S)));
                        }
                        Push(S, infix[i]);
                    }
                }
            }
        }
    }
    while(!isEmptyStack(S)){
        Enqueue(Q, string(1, Pop(S)));
    }
    while(!isEmptyQueue(Q)){
        postfix += Dequeue(Q) + " ";
    }
    return postfix;
}
int calculatePostfix(string postfix){
    StackInt S;
    CreateStackInt(S);
    for(int i = 0; i < postfix.length(); i++){
        if(postfix[i] == ' '){
            continue;
        }else if(isdigit(postfix[i])){
            string temp = "";
            while(isdigit(postfix[i])){
                temp += postfix[i];
                i++;
            }
            i--;
            PushInt(S, stoi(temp));
        }else if(isValidOperation(postfix[i])){
            int x = PopInt(S);
            int y = PopInt(S);
            if(postfix[i] == '+'){
                PushInt(S, y + x);
            }else if(postfix[i] == '-'){
                PushInt(S, y - x);
            }else if(postfix[i] == '*'){
                PushInt(S, y * x);
            }else if(postfix[i] == '/'){
                PushInt(S, y / x);
            }else if(postfix[i] == '^'){
                PushInt(S, pow(y, x));
            }
        }
    }
    return PopInt(S); // Mengembalikan hasil operasi
}
