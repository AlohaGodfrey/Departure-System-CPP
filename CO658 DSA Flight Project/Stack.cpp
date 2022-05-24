#include "Stack.h"

Stack::Stack(int maxSize) {
	this->maxSize = maxSize;
	stackData = new int[maxSize];
	top = -1;
}

void Stack::Push(int value) {
	stackData[++top] = value;
}

int Stack::Pop() {
	return stackData[top--];
}

int Stack::Peek() {
	return stackData[top];
}

bool Stack::IsEmpty() {
	return (top == -1);
}

bool Stack::IsFull() {
	return (top == maxSize - 1);
}
