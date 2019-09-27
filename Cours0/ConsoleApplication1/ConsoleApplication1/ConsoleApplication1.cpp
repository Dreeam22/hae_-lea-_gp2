// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
//#include <iostream>
#include <cstdlib>
#include <cstdio>
int appel(int & s)
{
	s++;
	return 0;
}

Vec3 incrX(Vec3 _in) {
	_in.x++;
	return _in;
}
int main()
{
	  // Affichage string printf = debug.log uniquement en string
    /*std::cout << "Hello World!\n"; 
	int foo = 0;
	const char * label = "sapin";
	const char label2[6] = { 's','a','p','i','n',0 };
	printf("hello world this is a test : %d label : %s %f\n",foo,label,66.66f);
	printf("hello world : l2 : %s\n", label2);*/

	  // affichage i via appel
	/*int i = 66;
	i++; //67
	appel(i);*/

	  // affichage de vecteur
	Vec3 toto = { 1,2,3 }; //new Vec3()
	incrX(toto);
	printf(" xval: %f\n yval: %f\n zval: %f\n", toto.x, toto.y, toto.z);
}


