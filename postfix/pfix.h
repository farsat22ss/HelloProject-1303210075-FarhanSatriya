#ifndef PFIX_H_INCLUDED
#define PFIX_H_INCLUDED

#include <iostream>
#include <cmath>
#include <string>

using namespace std;
#define Top(S) ((S).top)
#define infos(S) ((S).info)
#define head(Q) ((Q).head)
#define tail(Q) ((Q).tail)
#define infoq(Q) Q->info
#define next(Q) Q->next
#define nil NULL

typedef struct elmQueue *adrQ;
struct Stack{
    char info[20]; //Menyimpan operator
    int top;
};
struct StackInt{
    int info[20]; //Menyimpan angka
    int top;
};
struct elmQueue{
    string info; //Menyimpan angka
    adrQ next;
};
struct Queue{
    adrQ head;
    adrQ tail;
};

// Membuat Stack dan Queue kosong
void createStack(Stack &S);
void CreateStackInt(StackInt &S);
void createQueue(Queue &Q);
adrQ alokasiElemenQueue(string x);

// Mengecek apakah Stack dan Queue kosong
bool isEmptyStack(Stack S);
bool isEmptyStackInt(StackInt S);
bool isEmptyQueue(Queue Q);

// Operasi Stack dan Queue
void Push(Stack &S, char x); // Yang dimasukkan ke stack adalah operator, misal +, -, *, /
char Pop(Stack &S); // Yang diambil dari stack adalah operator terakhir yang dimasukkan
void PushInt(StackInt &S, int x);
int PopInt(StackInt &S);
void Enqueue(Queue &Q, string x); // Yang dimasukkan ke queue adalah string, kumpulan angka, misal 23, 34, 100
string Dequeue(Queue &Q);

// Operasi untuk mengubah infix menjadi postfix, dan menghitung postfix
bool isValidOperation(char x);
int precedence(char x);
string infixToPostfix(string infix);
int calculatePostfix(string postfix);

#endif // PFIX_H_INCLUDED
