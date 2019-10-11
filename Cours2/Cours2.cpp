// Cours2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "intArray.hpp"

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
	
	{
		IntArray t(16);
		t.set(0, 8);
		t.set(3, 66);
		for (int i = 0; i < t.getLenght(); i++) {
			printf("t[%d]: %d\n", i, t[i]);
		}

		t[5] = 8;
		printf("t[%d]: %d\n", 5, t[5]);
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

		int i = 0;
	}
}


