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

 void IntArray::remove(int valeur) {
	for (int i = 0; i < currentSize; i++) {
		if (data[i] == valeur) {
			for (int j = i; j < currentSize; j++)
			{
				data[j] = data[j + 1];
				//data[j]= (j+1<currentSize?data[j+1]:NULL); //sert à clean la suite du tableau
			}
			currentSize--;
			break;

		}
	}
}

 void IntArray::remove_all() {
	for (int i = 0; i < currentSize; i++) {
		data[i] = NULL;

	}
	currentSize = 0;
}

 void IntArray::fillwithrandom(int nbElem) {
	remove_all();
	be_sure(nbElem);

	for (int i = 0; i < nbElem; i++)
	{
		int val = std::rand() % 100;
		set(i, val);
	}
}

 void IntArray::sort() {
	IntArray nuData(1, "corneille");
	int z = getLenght();
	for (int i = 0; i < z; i++) {
		int val = get(i);
		int pos = nuData.SearchPosition(val);
		nuData.insert(pos, val);
	}

	for (int i = 0; i < getLenght(); i++) {
		set(i, nuData.get(i));
	}
}

void IntArray::permuter(int pos0, int pos1) {
	 int save = data[pos0];
	 data[pos0] = data[pos1];
	 data[pos1] = save;
 }

void IntArray::triInser() {
	for (int i = 1; i < currentSize; i++) {
		int j = i;

		while ((j>0) && (data[j] < data[j - 1]))
		{
			permuter(j, j - 1);
			j = j - 1;
		}
	}
}
