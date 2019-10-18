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

	void remove(int valeur) {
		for (int i = 0; i < currentSize; i++) {
			if (data[i] == valeur) {
				for (int j = i; j < currentSize; j++)
				{
					data[j] = data[j+1];
					//data[j]= (j+1<currentSize?data[j+1]:NULL); //sert à clean la suite du tableau
				}
				currentSize--;
				break;

			}
		}
	}

	void remove_all(){
		for (int i = 0; i < currentSize; i++) {
			data[i] = NULL;
			
		}
		currentSize = 0;
	}

	void fillwithrandom(int nbElem) {
		remove_all();
		be_sure(nbElem);

		for (int i = 0; i < nbElem; i++)
		{
			int val = std::rand() % 100;
			set(i, val);
		}
	}

	void sort(){
		IntArray nuData(1,"corneille");
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
};