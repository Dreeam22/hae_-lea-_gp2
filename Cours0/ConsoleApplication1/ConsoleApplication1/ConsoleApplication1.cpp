// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <chrono>


int appel(int & s)
{
	s++;
	return 0;
}

Vec3 incrX(Vec3 _in) {
	_in.x++;
	return _in;
}

Vec3 stackOverflow(Vec3 _in) {
	Vec3 temp = _in;
	temp.y++;
	return stackOverflow(temp);
}

int Strlen(const char * src) {
	int counter = 0;
	while (*src != 0)
	{	
		*src++;
		counter++;		
	}	
	return counter;
}

void Strcpy(char* dest, const char * src) {
	//put copy in dest
	return ;
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
	/*Vec3 toto = { 1,2,3 }; //new Vec3()
	incrX(toto);
	printf(" xval: %f\n yval: %f\n zval: %f\n", toto.x, toto.y, toto.z);*/

	 //stackOverflow
	/*Vec3 bob = { 1,2,3 };
	bob = stackOverflow(bob);
	printf(" val x : %f\n", bob.x);*/

	/*Vec3 vecTab[4];
	vecTab[0] = { 1,2,3 };
	vecTab[1] = { 4,5,6 };
	vecTab[2] = { 7,8,9 };
	//printf("v0x %f\n", vecTab[0].x);
	//printf("v0x %f\n", vecTab[0]);

	Vec3 * t0 = 0;
	Vec3 * t1 = nullptr;
	Vec3 * t2 = &vecTab[1];

	(*t2).y = 777;
	t2->y = 888;
	t2->x = 222;
	t2->z = 000;

	Vec3 * iter = &vecTab[0];
	int i = 0;
	for (i = 0; i < 3; ++i) {
		printf("val vec x: %d\n", iter->x);
		iter++;
	}
	Vec3 * t3 = t2 + 1; // 
	t2++;


	   //s'allouer de la mémoire

	const char label2[6] = { 's','a','p','i','n' , 0 };
	const char * ptr = &label2[0];
	ptr++;
	printf("%c\n", ptr);
	auto start = std::chrono::system_clock::now();
	int * bigBlock = (int*)malloc(1024 * 1024 * 1024);

	for (int k = 0; k < 64 * 1024 * 1024; ++k) {
		bigBlock[k] = 0xdeadbeef;
	}

	printf("beef? : %x\n", bigBlock[1024 * 1024]);
	auto end = std::chrono::system_clock::now();
	auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	printf("time ? : %d\n", millis);
	*/

	  //allouer des vecteurs
	/*Vec3 tableau[16];
	Vec3 *tableau0 = (Vec3*)malloc(sizeof(Vec3) * 16); //en C pur
	memset(tableau, 0, sizeof(Vec3) * 16);

	Vec3 * tableau1 = (Vec3*)calloc(sizeof(Vec3), 16); //en C pur

	Vec3 * tableau2 = new Vec3[16]; //en C++
	Vec3 * unSeulVec = new Vec3(); //c++ allocation dynamique
	Vec3 unSeulVecAussiMaisSurLeTas = Vec3(); //c++ allocation statique*/

	int _i = 0;

	const char * source = "mon lapin est dodu";
	int len = Strlen(source);
	char * dest = (char*)calloc(1024, sizeof(char));
	Strcpy(dest, source);

	
	printf("dest val: %d len:%s\n", Strlen(source), dest);
	int i = 0;
}


