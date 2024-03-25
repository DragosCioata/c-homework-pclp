#include <stdio.h>
#include <math.h>
#include <stdlib.h>

int castiga(int n, int v[])
{	
	// vom avea 2 loop uri. primul va fi for ul in care 
	// vom parcurge toate cutiile, iar cel de al 2 lea 
	// loop va fi un while cu care vom parcurge cutiile
	// pana fiecare prizonier va deschide n/2 cutii.  
	// acesta se va opri prin intermediul variabilei contor


	int i, j, ok, contor, stop;
	ok = 0;
	for (i = 1; i <= n; i++)
	{
		contor = 0;
		j = i;
		stop = 1;
		while (contor < n / 2)
		{
			if (v[j] == i && stop == 1)
			{
				ok++;
				stop = 0;
			}

	// prin intermediul if ului verificam daca 
	// prizonierul a gasit cutia corespunzatoare
	// numarului lui
	// la fiecare parcurgere al celui de al 2 lea
	// loop j va lua valoarea lui v[j] si vom sari
	// astfel prin vector dupa cerinta problemei
	// din cutia x in cutia regasita in interiorul
	// acesteia

			j = v[j];
			contor++;
		}
	}

	// in variabila ok vom tine evidenta a cati prizonieri
	// si au gasit cutia corespunzatoare numarului lor.
	// daca aceasta variabila va fi egala cu numarul de
	// prizonieri inseamna ca au reusit toti sa scape deci
	// iar functia va returna 1 pentru afisarea in main

	if (ok == n)
		return 1;
	else
		return 0;
}

void ciclu(int n, int v[], int x[])
{
	int i, j, stop, k, w[1000];
	for (i = 1; i <= n; i++)
		w[i] = 0;

	// vom lua un vector caracteristic pe care il vom
	// initializa cu 0 in care vom tine evidenta daca
	// numarul a mai facut parte sau nu din alt ciclu

	k = 1;
	for (i = 1; i <= n; i++)
	{
		j = i;
		stop = 1;
		while (stop == 1)
		{

	// daca in vectorul de frecventa valoarea corespunzatoare
	// numarului din momentul prezent este 0 inseamna ca 
	// nu a mai facut parte din niciun ciclu deci il vom
	// putea adauga in vectorul rezultat x si vom marca 
	// elementul in vectorul caracteristic ca fiind deja 
	// inclus in ciclu

			if (w[j] == 0)
			{
				x[k] = j;
				k++;
				w[j] = 1;
			}
	
	// daca s-a ajuns la numarul curent inseamna ca ne putem
	// opri si am gasit un ciclu

			if (v[j] == i)
				stop = 0;
			j = v[j];
		}
	}
}

int main()
{

	// Vom citi numarul de cutii/prizonieri dupa care vom
	// citi in v continutul fiecarei cutii.

	int n, v[1000], i, x[1000];
	scanf("%d", &n);
	for (i = 1; i <= n; i++)
		scanf("%d", &v[i]);

	// in functia castiga vom verifica daca reusesc sau nu
	// toti prizonierii sa isi gaseasca numarul si vom afisa
	// raspunsul

	if (castiga(n, v) == 1)
		printf("Da\n");
	else
		printf("Nu\n");

	ciclu(n, v, x);

	// functia ciclu a returnat in vectorul x ordinea in care
	// sunt parcurse elementele si cum formeaza ele cicluri
	// astfel in vectorul x am toate ciclurile in ordinea
	// corecta. pentru afisare vom folosi secventa de cod de
	// mai jos

	int ciclul;
	ciclul = 1;
	for (i = 1; i <= n; i++)
		if (v[x[i]] == ciclul)
		{
			printf("%d\n", x[i]);
			ciclul = x[i + 1];
		}
		else
			printf("%d ", x[i]);
	return 0;
}
