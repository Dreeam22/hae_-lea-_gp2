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

int Max(int a, int b)
{
	return (a < b ? b : a);
}

int Min(int a, int b)
{
	return (a < b ? a : b);
}

int Strcmp(char* meule, char* aiguille)  
{
	int lenMeule = strlen(meule);
	int lenAiguille = strlen(aiguille);

	int maxLen = Max(lenMeule, lenAiguille);
	int minLen = Min(lenMeule, lenAiguille);

	for (int i = 0; i < minLen; i++)
	{
		if (meule[i] < aiguille[i])
		{
			return -1;
		}
		else if (meule[i]> aiguille[i])
		{
			return 1;
		}
			
	}
	if (minLen == maxLen)
		return 0;

	if (maxLen == lenMeule)
		return 1;
	
	return -1;
	
}

char* StrStr(char* meuleDeFoin, char* aiguille )
{
	int lenMeule = strlen(meuleDeFoin);
	int lenAiguille = strlen(aiguille);

	for (int i = 0; i < lenMeule; i++)
	{
		bool found = true;
		for (int j = 0; j < lenAiguille; j++)
		{
			if (meuleDeFoin[j] != aiguille[j])
			{
				found = false;
				break;
			}
		}
		if (found)
			return meuleDeFoin;
		meuleDeFoin++;

	}
	return nullptr;
}


int main()
{
    /*std::cout << "Hello World!\n"; 
	char licorne[32] = "licorne";
	char vomi[32] = "vomit";
	Memcpy (licorne, vomi, strlen(licorne)+1);

	printf("licorne %s\n", licorne);

	char chateau[32] = "chateau";
	char soldat = 'e';

	printf("Le soldat est à la position %d\n", StrChr(chateau, soldat));*/

	char text[1024] = "Lorem ipsum dolor sir amet";
	char token[1024] = "dolor";

	char* tokenInText = StrStr(text, token);
	int pos = (int)(tokenInText - text);
	printf("Le token est en position %d\n", pos);

	/*char licorne[] = "licorne";
	char vomi[] = "vomi";
	char lico[] = "lico";
	char blico[] = " licorne noire";


	printf("renvoi : %d\n", Strcmp(licorne, vomi));
	printf("renvoi : %d\n", Strcmp(licorne, lico));
	printf("renvoi : %d\n", Strcmp(licorne, blico));
	printf("renvoi : %d\n", Strcmp(licorne, licorne));

	printf("renvoi : %d\n", strcmp(licorne, vomi));
	printf("renvoi : %d\n", strcmp(licorne, lico));
	printf("renvoi : %d\n", strcmp(licorne, blico));
	printf("renvoi : %d\n", strcmp(licorne, licorne));*/

	int a = 0;
}


