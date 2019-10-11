// ConsoleApplication2.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <cstring>
#include <cstdio>
static void TestRec();

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

	/*char text[1024] = "Lorem ipsum dolor sir amet";
	char token[1024] = "dolor";

	char* tokenInText = StrStr(text, token);
	int pos = (int)(tokenInText - text);
	printf("Le token est en position %d\n", pos);*/

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

	TestRec();
}

int add_0(int a, int b)
{
	int i = 0;
	for (i = 0; i < a + b; i++)
	return i;
}

int add_1(int a, int b)
{
	int val = a;
	for (int i = 0; i < b; i++)
		val++;

	return val;
}

int add_rec(int a, int b)
{
	printf("a:%d\n b:%d\n", a, b);
		// add_rec(7,8)
		// add_rec(6,9)
		// add_rec(5,10)
		//...
		// add_rec(0,15)
	if (a == 0)
		return b;

	return add_rec(a - 1, b + 1);
}

int add_rec2(int a, int b)
{
	//printf("a:%d\n b:%d\n", a, b);
	if (a == 0)
		return b;
	else if (b == 0)
		return a;
	else
		return 1 + add_rec2(a - 1, b);

	
}

int sub_rec1(int a, int b) {
	//cas terminal
	if (b == 0)	return a;
	if (a == 0) return b;

	//cas general
	if (b < 0) return sub_rec1(a + 1, b + 1);

	if (b > 0) return sub_rec1(a - 1, b - 1);
	//trouve un combinateur et un appel recursif sur des paramètres (n-1)
	return sub_rec1(a - 1, b - 1);
	return -1 + sub_rec1(a - 1, b);
}

int sub_rec2(int a, int b) {
	//printf("a:%d\n b:%d\n", a, b);

	if (b == 0) return a;
	else if (b > 0) 
		return sub_rec2(a, b - 1) - 1;
	else //if b < 0
		return sub_rec2(a, b + 1) + 1;
}

int mult(int a, int b) {
	//a*b = a *(b-1) + a
	//4 3
	//4 * 2 + 4
	//4 * 1 + 4
	//4 + 4 + 4
	//8 + 4
	//12

	if (b == 0) return 0;
	if (a == 0) return 0;

	if (b > 0)
		return a + mult(a, b - 1);
	else 
		return - mult(a, -b);

}

int mult2(int a, int b)
{
	if (a == 0 || b == 0)
		return a;
	else if (b < 0)
	{
		return -a + mult2(a, b + 1);
	}
	else
		return a + mult2(a, b - 1);
}

int div_rec(int a, int b)
{
	if (a == 0 )
		return 0;	
	if (b < 0 && a < 0) return -div_rec(a, b);
	if (b < 0)
		return -div_rec(a , - b);
	if (a < 0)
		return -div_rec(-a, b);

	if (a < b) return 0;

	return 1 + div_rec(a - b, b);
}

int mod_rec(int a, int b)
{
	//reste de la division euclidienne

	return a - mult(b, div_rec(a, b));
}

int Strlen_rec(const char * str)
{
	//contenu pointé est le caractère 0
	//retour 0
	//sinon 1 + strlenrec(avancer str)

	if (*str == 0) return 0;
	else return 1 + Strlen_rec( str + 1 );
}

int StrCpy_rec(char * copie, const char * cible)
{
	 *copie = *cible;  //copie le zero final
	if (*cible == 0) return 0;
	
	return StrCpy_rec(copie + 1, cible + 1);
}

void ZeroMemory(char *dst, int size)
{
	//mettre 0 dans dst
	//ZeroMemory (avancer dst, diminuer size)
	if (size == 0) return;
	*dst = 0;
	ZeroMemory(dst + 1, size-1);
}

void MemcpyRec(char* dst, const char * src, int size)
{
	if (size == 0) return;
	else *dst = *src;

	MemcpyRec(dst + 1 , src + 1, size -1);

}

int StrcmpRec(char* str0, char *str1) // renvoyer -1 0 1 selon l'ordre lexicographique
{
	if (*str0 == 0 && *str1 == 0) return 0;
	if (*str0 == 0) return 1;
	if (*str1 == 0) return -1;
	if (*str0 < *str1) return 1;
	if (*str0 > *str1) return -1;

	return StrcmpRec(str0 + 1, str1 + 1);
}

void StrcatRec(char * str0, char* str1) 
{
	//copier str1 à la fin de str0
	//chercher le \0 
	//puis copier str1
	
	if (*str0 == 0)
	{
		if (*str1 == 0)
			return;
		else {
			*str0 = *str1;
			*(str0 + 1) = 0;
			StrcatRec(str0 + 1, str1 + 1);
		}
	
	}
	else
		StrcatRec(str0 + 1, str1);

}

char * StrChrRec(char* str, char tok )
{
	if (*str == 0) return nullptr;
	if (*str == tok) return str;

	StrChrRec(str + 1, tok);
}

bool startWith(const char* s0, const char * s1) {
	if (*s0 == 0 && *s1 != 0) return false;

	if (*s1 == 0) return false;

	if (*s0 != *s1) return false;
	else return startWith(s0 + 1, s1 + 1);
}

char * StrStrRec2(char * s0, char* s1)
{
	if (startWith(s0, s1))
		return s0;
	else return StrStrRec2(s0 + 1, s1);

}

char * StrStrRec3(char * s0, char* s1)
{
	return (startWith(s0, s1)) ? s0 : StrStrRec3(s0 + 1, s1);

}

bool StrStrBoolRec(char* str0, char* str1)
{
	if (*str1 == 0) return true;
	if (*str0 == 0) return false;

	if (*str0 == *str1)
	{
		StrStrBoolRec(str0 + 1, str1 + 1);
	}
	else return false;
}

char * StrStrRec(char * str0, char* str1) 
{
	if (*str1 == 0) return nullptr;
	if (*str0 == 0) return nullptr;

	if (*str0 == *str1)
	{		
		if (StrStrBoolRec(str0, str1) == true)
			return str0;
	}

	StrStrRec(str0 + 1, str1);
}

bool contains(const char * s0, const char *s1) {
	int len = strlen(s0);
	return s1 >= 0 && s1 <= s0 + len;
}

void assert(bool condition) { if (!condition) throw std::exception("non"); }

void TestRec()
{
	//int foo = add_rec(2, 2);
	int foo2 = sub_rec2(3,2);

	int foo3 = mult(1, 3);
	int foo4 = mult(1,-3);
	int foo5 = div_rec(-6, 2);
	int foo6 = div_rec(-2, 6);
	int foo7 = div_rec(2, 6);
	int foo8 = mod_rec(16, 3);

	int foo9 = Strlen_rec("sapin");

	char dst[150];
	int foo10 = StrCpy_rec(dst,"pitiprout");

	/*int szBuf = 32;
	char * buffer = (char*)malloc(szBuf + 1);
	buffer[32] = 'x';
	ZeroMemory(buffer, szBuf);
	printf("%c", buffer[32]);*/

	/*MemcpyRec(dst, "groprout", strlen(dst));
	printf("%s", dst);

	char toto[32];
	char tata[32] = "it's me mariooo";
	MemcpyRec(toto, tata, strlen(tata) + 1);
	if (toto[0] != tata[0])
		throw std::exception("hmm?");*/

	char lapin[32] = "fly";
	char lapin2[32] = "teprou";

	/*if (StrcmpRec(lapin, lapin2) == 0)
	{
		throw std::exception("non");
	}*/

	//StrcatRec(lapin, lapin2);

	/*char chateau[32] = "chateau";
	char soldat = 'e';
	char* TokeninTxt = StrChrRec(chateau, soldat);
	int pos1 = (int)(TokeninTxt - chateau);

	printf("Le soldat est à la position %d\n", pos1); */

	char text[1024] = "Lorem dipsum dolor sir amet";
	char token[1024] = "dolor";

	char* tokenInText = StrStr(text, token);
	int pos = (int)(tokenInText - text);
	printf("Le token est en position %d\n", pos);

	if (contains(text, token) == true)
		printf("oui");

	int t = 0;

}
