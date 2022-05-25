//CO658 DSA Flight Project.cpp
//Student Name: Immanuel Godfrey
//Student ID: 21817368
//Course ID: CO650 - Advanced Programming

#include <iostream>
#include <string>
#include "HashTable.h"
#include "Stack.h"
#include "DepartureSystem.h"
using namespace std;


void displayStudent()
{
    cout << "//Student Name: Immanuel Godfrey" << endl;
    cout << "//Student ID: 21817368" << endl;
    cout << "//Course ID: CO650 - Advanced Programming" << endl;
    cout << endl;
}


void StackTest() {
    Stack* myStack = new Stack(10);
    myStack->Push(5);
    myStack->Push(7);
    myStack->Push(3);
    myStack->Push(11);
    while (!myStack->IsEmpty()) 
    {
        cout << myStack->Pop() << endl;
    }
}

void HashTableTest() {
    HashTable HT;

    if (HT.isEmpty()) {
        cout << "Correct answer. Good job" << endl;
    }
    else {
        cout << "Oh oh. We need to check out code!" << endl;
    }

    

    HT.insertItem(905, "Jim");
    HT.insertItem(201, "Tom");
    HT.insertItem(782, "Dick");
    HT.insertItem(344, "Harry");
    HT.insertItem(747, "James");
    HT.insertItem(169, "Lewis");
    HT.insertItem(958, "Capaldi");
    HT.insertItem(323, "Leroy");
    HT.insertItem(323, "Lewandowski");

    HT.printTable();

    HT.removeItem(344);
    HT.removeItem(100);

    if (HT.isEmpty()) {
        cout << "Oh oh. We need to check out code!" << endl;
    }
    else {
        cout << "Correct answer. Good job" << endl;
    }

    cout << HT.searchTable(344) << endl;
};

int main()
{

    displayStudent();

    DepartureSystem* myTerminal;
    myTerminal = new DepartureSystem();

    myTerminal->runDepartureSystemFSM();

    return 0;
}


