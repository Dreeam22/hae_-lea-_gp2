#include "pch.h"
#include "intArray.hpp"

int IntArray::TEST = 66;

bool IntArray::be_sure(int size) { //s'assure que le tableau fait au moins size
	if (size < maxSize) return false;

	int* newdata = new int[size];

	for (int i = 0; i < size; ++i) newdata[i] = 0;
	for (int i = 0; i < currentSize; i++)
		newdata[i] = data[i];

	delete(data);
	data = newdata;

	maxSize = size;
	return true;

}

void IntArray::push_back(int elem) {
	(be_sure(currentSize + 1));

	data[currentSize] = elem;
	currentSize++;

}

void IntArray::push_front(int elem) {
	(be_sure(currentSize + 1));

	for (int i = currentSize; i >0; i--) {
		data[i] = data[i - 1];
	}
	data[0] = elem;
	currentSize++;
}

void IntArray::insert(int pos, int elem) {
	(be_sure((pos >= currentSize) ? (pos + 1) : (currentSize + 1)));

	for (int i = currentSize; i > pos; i--) {
		data[i] = data[i - 1];
	}
	data[pos] = elem;
	
	if (pos >= currentSize)
		currentSize = pos + 1;
	else
		currentSize++;
}
