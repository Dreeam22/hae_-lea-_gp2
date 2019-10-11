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

	IntArray(int size, const char * name = "") {
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

	inline int operator()(int pos) {
		be_sure(pos);
		return data[pos];
	}

	inline int & operator[](int pos) {
		be_sure(pos);
		return data[pos];
	}
	void set(int pos, int elem) {

		(be_sure(pos));
		
		data[pos] = elem;
		currentSize = pos;
		
		//s'assurer de la taille des données
		//changer data
	}

	void push_back(int elem);

	void push_front(int elem);

	void insert(int pos, int elem);
};