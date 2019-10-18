// Cours3.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "intArray.hpp"
#include "Util.hpp"
#include "List.hpp"
#include "Tri.hpp"

void assert(bool condition) { if (!condition) throw std::exception("non"); }


void TestIntTree() {

	
	IntTree * tree = new IntTree();
	Node<int> * leaf = new IntNode(8);
	tree->root = leaf;
	leaf->insert(4);
	//assert(leaf->left->elem == 4);

	leaf->insert(9);
	//assert(leaf->right->elem == 9);

	leaf->insert(16);
	leaf->insert(3);
	leaf->insert(5);
	assert(leaf->getLength() == 6);


	assert(leaf->Contains(16) == true);
	leaf->remove(16);
	assert(leaf->Contains(16) == false);
	assert(leaf->Contains(4) == true);
	leaf->remove(4);
	assert(leaf->Contains(4) == false);
	leaf->insert(0);
	assert(leaf->Contains(0) == true);
	leaf->remove(0);
	assert(leaf->Contains(0) == false);



	tree->dfsprint();
	int k = 0;
}



void testIntlist() {
	IntList * toto = new IntList(8);

	toto->Append(65);
	assert(toto->Length() == 2);

	toto = toto->addFirst(33);
	assert(toto->Length() == 3);
	assert(toto->elem == 33);

	toto = toto->Remove(12);
	assert(toto->Length() == 3);
	toto = toto->Remove(33);
	assert(toto->Length() == 2);


	toto = toto->addFirst(70);
	toto = toto->Remove(70);
	IntList * tata = new IntList(66);
	tata = tata->Remove(66);
	assert(tata == nullptr);



	/*bool MRP = toto->Contains(60);
	assert(MRP == false);
	bool MRP2 = toto->Contains(65);
	assert(MRP2 == true);*/
	int k = 0;
}

int main()
{
	TestIntTree();
	testIntlist();
	/*{
		IntArray t(1);
		t.fillwithrandom(16);
		t.triInser();

		for (int i = 0; i < t.getLenght() - 1; i++)
		{
			assert(t.data[i] < t.data[i + 1]);
		}


		int pq = 0;
	}

	{
		double t0 = Util::getTimestamp();
		IntArray toto;
		toto.fillwithrandom(256);
		toto.triInser();

		for (int i = 0; i < toto.getLenght() - 1; i++)
		{
			assert(toto.data[i] <= toto.data[i + 1]);
		}

		double t1 = Util::getTimestamp();

		printf("temps de calcul: %f s for %d\n", (t1 - t0), toto.getLenght());

		int j = 0;
	}

	{
		double t0 = Util::getTimestamp();
		IntArray toto;
		toto.fillwithrandom(1024);
		toto.triInser();
		toto.binarySearch(6);
		for (int i = 0; i < toto.getLenght() - 1; i++)
		{
			assert(toto.data[i] <= toto.data[i + 1]);
		}

		double t1 = Util::getTimestamp();

		printf("temps de calcul: %f s for %d\n", (t1 - t0), toto.getLenght());

		int j = 0;
	}*/

	{
		IntArray tete;
		tete.fillwithtruc(10);

		int bpos = tete.binarySearch(6);


		int p = 0;
	}

}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
