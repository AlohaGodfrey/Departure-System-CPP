#pragma once
class Stack
{
private:
	int maxSize;
	int* stackData;
	int top;
public:
	Stack(int maxSize);
	void Push(int value);
	int Pop();
	int Peek();
	bool IsEmpty();
	bool IsFull();
};

