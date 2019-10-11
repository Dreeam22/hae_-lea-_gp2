// Cours2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "intArray.hpp"

void assert(bool condition) { if (!condition) throw std::exception("non"); }

int main()
{
    //std::cout << "Hello World!\n"; 

	//printf("Tesuto : %d\n",IntArray::TEST);

	//auto montableau = new IntArray(16);
	auto nameTab0 = "tab0";
	auto nameTab1 = "tab1";

	{
		//variable locale
		IntArray tab0 = IntArray(16, nameTab0);
	}
		//tableau détruit
	{
		//variable dynamique
		IntArray* tab1 = new IntArray(16, nameTab1);
		delete(tab1);
		tab1 = nullptr;
	}
	
	/*{
		IntArray t(16);
		t.set(0, 8);
		t.set(3, 66);
		for (int i = 0; i < t.getLenght(); i++) {
			printf("t[%d]: %d\n", i, t.get(i));
		}

		t.set(5,8);
		printf("t[%d]: %d\n", 5, t.get(5));
	}

	{
		IntArray t(16);
		for (int i = 0; i < 8; i++)
		{
			t.set(i, i*i);
		}
		t.push_back(5);
		t.push_front(2);
	}
	{
		IntArray t(0);
		t.push_back(5);
		t.push_front(2);
	}

	{
		IntArray t(16);
		for (int i = 0; i < 8; i++)
		{
			t.set(i, i*i);
		}
		t.insert(5, 2);

		
	}*/

	{
		IntArray t(1);
		t.set(0,5);
		t.set(1,6);
		t.set(2,10);

		assert(t.SearchPosition(1) == 0);
		assert(t.SearchPosition(5) == 0);
		assert(t.SearchPosition(6) == 1);
		assert(t.SearchPosition(8) == 2);

		t.remove(6);
	
	}

	{
		IntArray t(1,"racine");
		t.fillwithrandom(8);
		t.sort();

		int pq = 0;
	}

	
}


