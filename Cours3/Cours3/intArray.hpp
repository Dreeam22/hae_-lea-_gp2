#pragma once
#include <cstdio>
#include <cstdlib>
#include <string>

class IntArray {
public :

	std::string name;
	//membre TEST statique qui n'existe qu'à un seul endroit
	static int TEST;
	int * data; //tableau dynamique qui va contenir nos données
	int maxSize;
	int currentSize = 0;

	IntArray(int size = 1, const char * name = "") {
		this->name = name;
		//printf("construite \n", this->name.c_str());

			//version C old school
		/*data = (int *)malloc(size * sizeof(int));
		memset(data, 0, size * sizeof(int));*/
			//version C new school
		//data = (int*)calloc(size, sizeof(int));
			//calloc met des zero

			//version c++ plus safe
		data = new int[size];
		for (int i = 0; i < size; i++) data[i] = 0;

		maxSize = size;
	}

	~IntArray()
	{
		//printf("détruite! \n", name.c_str());
	}

	bool be_sure(int size);

	int getLenght() {
		return currentSize;
	}

	int get(int pos) {
		return data[pos];
	}
	
	/*inline int operator()(int pos) {
		be_sure(pos+1);
		return data[pos];
	}

	inline int & operator[](int pos) {
		be_sure(pos+1);
		return data[pos];
	}*/
	void set(int pos, int elem) {

		(be_sure(pos+1));		
		data[pos] = elem;
		if (currentSize <= pos)
			currentSize = pos + 1;
		
		
		//s'assurer de la taille des données
		//changer data
	}

	void push_back(int elem);

	void push_front(int elem);

	void insert(int pos, int elem);

	int SearchPosition(int elem)
	{
		for (int i = 0; i < getLenght(); i++)
		{
			if (elem <= data[i])
				return i;			
		}
		return getLenght();
	}

	void remove(int valeur);

	void remove_all();

	void fillwithrandom(int nbElem);

	void sort();

	void permuter(int pos0, int pos1);

	void triInser();

	void fillwithtruc(int nbElem) {
		remove_all();
		int val = 0;
		for (int i = 0; i < nbElem; i++)
		{
			val++;			
			set(i,val);

		}
	}

	int binarySearch(int key)
	{
		//demander la recherche entre 0 et la taille
		return _binarySearch(key, 0, getLenght());

	}

	int _binarySearch(int key, int start, int end)
	{		
		//trouver le pivot
		//est ce qu'on part à gauche ?
		//est ce qu'on part à droite ?
		//demander le sous résultat
		if (start >= end) return start;
		
		if (end == start + 1) {
			if (key > data[start]) return end;
			if (key < data[end]) return start;
			return start;
		}
		int pivot = (start + end) / 2;
		if (key == data[pivot]) return pivot;
		
		if (key < data[pivot])//va à gauche 
		{
			return _binarySearch(key, start, pivot);
		} 	
		else return _binarySearch(key, pivot, end);
		
		
	}
};