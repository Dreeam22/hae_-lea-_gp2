// ConsoleApplication2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <cstring>
#include <cstdio>

void Memcpy(char * dest, char * src, int size) {

	/*for (int i=0; i < size; i++)
	{
		dest[i] = src[i];
	}*/
	
	while (size--)
	{
		dest[size] = src[size];
	}
}


int StrChr(char* grange, char chat)
{
	/*int length = strlen(grange);
	for (int i = 0; i < length ; i++)
	{
		if (grange[i] == chat)
		{
			return i;
		}	
		
	}
	return -1;*/

	/*int i = 0;
	while (grange[i]!= 0)
	{
		if (grange[i]==chat)
		{
			return i;
		}
		i++;
	}
	return -1;*/

	char* oldGrange = grange;
	while (*grange)
	{
		if (*grange == chat)
		{
			return(int)(grange - oldGrange);
		}
		grange++;

	}
	return -1;

	/*trouver la position du chat
		dans la grange
		si pas trouvé
		renvoyer -1*/
}

int main()
{
    std::cout << "Hello World!\n"; 
	char licorne[32] = "licorne";
	char vomi[32] = "vomit";
	Memcpy (licorne, vomi, strlen(licorne)+1);

	printf("licorne %s\n", licorne);

	char chateau[32] = "chateau";
	char soldat = 'e';

	printf("Le soldat est à la position %d\n", StrChr(chateau, soldat));
}


