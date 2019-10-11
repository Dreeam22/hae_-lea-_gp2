#pragma once
#include <cstdio>
#include <cstdlib>

class IntArray {
public :

	std::string name;
	//membre TEST statique qui n'existe qu'à un seul endroit
	static int TEST;
	int * data; //tableau dynamique qui va contenir nos données
	int maxSize;
	int currentSize = 0;

	IntArray(int size, const char * name = nullptr) {
		this->name = name;
		printf("construite \n", this->name.c_str());

			//version C old school
		/*data = (int *)malloc(size * sizeof(int));
		memset(data, 0, size * sizeof(int));*/
			//version C new school
		//data = (int*)calloc(size, sizeof(int));
			//calloc met des zero

			//version c++ plus safe
		data = new int[size];
		for (int i = 0; i < size; i++) data[i] = 0;


	}

	~IntArray()
	{
		printf("détruite! \n", name.c_str());
	}
};