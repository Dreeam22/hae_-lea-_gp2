// Cours3.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include "intArray.hpp"
#include "Util.hpp"


void assert(bool condition) { if (!condition) throw std::exception("non"); }

int main()
{


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
