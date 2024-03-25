#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void adunare(char *a, char *b, int N)
{
    int i, carry, S;
    char c[2001];

    carry = 0;
    S = 0;

    // parcurgem numerele de la final la inceput si construim in c[]
    // suma numerelor astfel: adaugam in c[] ultima cifra a lui S iar
    // daca acesta este mai mare decat 10 vom pastra in carry ceea
    // ce se va adauga la urmatoare apelare a for ului. Pentru a face
    // conversia am folosit din ascii diferenta - '0' pentru a trece
    // din char in int si + '0' pentru a trece din int in char

    for (i = N - 2; i >= 0; i--)
    {
        S = (a[i] - '0') + (b[i] - '0') + carry;
        c[i] = (S % 10 + '0');
        carry = S / 10;
    }

    // rezultatul din c[] il copiem in a[] care va fi returnat ca
    // parametru al functiei

    for (i = 0; i < (N - 1); i++)
        a[i] = c[i];
}

void scadere(char *a, char *b, int N)
{
    int i, carry, S;
    char c[2001];

    carry = 0;
    S = 0;

    // parcurgem numerele de la final la inceput si construim in c[]
    // diferenta numerelor astfel: Daca diferenta este mai mica decat
    // 0 atunci vom adauga 10 la aceasta, iar carry va deveni 1 pentru
    // urmatorul pas. Pentru a face conversia am folosit din ascii
    // diferenta - '0' pentru a trece din char in int si + '0' pentru
    // a trece din int in char

    for (i = N - 2; i >= 0; i--)
    {
        S = (a[i] - '0') - (b[i] - '0') - carry;

        if (S < 0)
        {
            S = S + 10;
            carry = 1;
        }
        else
            carry = 0;

        c[i] = S + '0';
    }

    // rezultatul din c[] il copiem in a[] care va fi returnat ca
    // parametru al functiei

    for (i = 0; i < (N - 1); i++)
        a[i] = c[i];
}

void calculplus(char *a, char *b, int N)
{

    // Am adaugat in readme logica dupa care se desfasoara
    // calculele din if urile de mai jos.

    char reala[1001], realb[1001], imaga[1001], imagb[1001];
    char bitreala, bitrealb, bitimaga, bitimagb;
    int i, j;
    bitreala = a[0];
    bitrealb = b[0];
    bitimaga = a[(N - 1) / 2];
    bitimagb = b[(N - 1) / 2];

    // initializam bitul de semn pentru partea reala si partea
    // imaginara atat pentru numarul a cat si pentru numarul b
    // cu valorile potrivite din a si b

    strncpy(reala, a, ((N - 1) / 2));
    strncpy(realb, b, ((N - 1) / 2));
    memmove(reala, reala + 1, strlen(reala));
    memmove(realb, realb + 1, strlen(realb));

    strcpy(imaga, a);
    strcpy(imagb, b);
    memmove(imaga, imaga + (((N - 1) / 2) + 1), strlen(imaga));
    memmove(imagb, imagb + (((N - 1) / 2) + 1), strlen(imagb));

    // initializam partea reala si imaginara a numerelor a si b
    // si adaugam terminatorul de sir pentru a elimina rezidurile
    // create in partile reale in urma memmove

    reala[((N - 1) / 2 - 1)] = '\0';
    realb[((N - 1) / 2 - 1)] = '\0';

    // d si e vor fi variabilele in care vom stoca rezultatul
    // compararii sirurilor reala realb si imaga imagb

    int d = strncmp(reala, realb, (N / 2 - 1));
    int e = strncmp(imaga, imagb, (N / 2 - 1));
    int q = 0;
    int p = 0;

    // q si p vor fi variabilele cu care vom tine evidenta
    // daca s au verificat sau nu conditiile urmatoare pentru
    // a evita cazul in care se va modifica bitul de semn
    // in una din conditii pentru crearea rezultatului si
    // drept urmare se va intra in alta conditie conform
    // bitului de semn modificat

    // suma numere pozitive => numar pozitiv si adun numerele

    if (bitreala == '0' && bitrealb == '0' && q == 0)
    {
        bitreala = '0';
        adunare(reala, realb, N / 2);
        q = 1;
    }

    // suma numar pozitiv cu numar negativ => nu stim daca vom
    // obtine un numar pozitiv sau negativ deci vom avea 3 cazuri
    // daca primul e mai mare vom face scadere intre cele 2 numere
    // daca al 2 lea e mai mare vom face b - a practic si cum functia
    // scadere returneaza rezultatul in primul parametru vom copia
    // rezultatul in reala
    // daca ambele sunt egale atunci vom face bitul de semn 0 si
    // vom initializa intreg numarul (in cazul nostru reala) cu 0

    if (bitreala == '0' && bitrealb == '1' && q == 0)
    {
        if (d > 0)
        {
            bitreala = '0';
            scadere(reala, realb, N / 2);
        }
        if (d < 0)
        {
            bitreala = '1';
            scadere(realb, reala, N / 2);
            strcpy(reala, realb);
        }
        if (d == 0)
        {
            bitreala = '0';
            for (j = 0; j < ((N / 2) - 1); j++)
                reala[j] = '0';
        }
        q = 1;
    }

    // similar cu ce avem mai sus

    if (bitreala == '1' && bitrealb == '0' && q == 0)
    {
        if (d > 0)
        {
            bitreala = '1';
            scadere(reala, realb, N / 2);
        }
        if (d < 0)
        {
            bitreala = '0';
            scadere(realb, reala, N / 2);
            strcpy(reala, realb);
        }
        if (d == 0)
        {
            bitreala = '0';
            for (j = 0; j < ((N / 2) - 1); j++)
                reala[j] = '0';
        }
        q = 1;
    }

    // daca ambele numere sunt negative practiv vom avea
    // o suma a numerelor cu semnul "-" in fata

    if (bitreala == '1' && bitrealb == '1' && q == 0)
    {
        bitreala = '1';
        adunare(reala, realb, N / 2);
        q = 1;
    }

    // dupa efectuarea calculelor cu partile reale vom face
    // exact acelasi lucru si cu cele imaginare. puteam face
    // probabil o functie pentru a face aceleasi calcule atat
    // cu partea reala cat si cu partea imaginara care ar fi
    // primit drept parametrii bita, partea, bitb, parteb
    // sa injumatatim if urile, dar copy paste si replace a
    // fost mai simplu :))

    if (bitimaga == '0' && bitimagb == '0' && p == 0)
    {
        bitimaga = '0';
        adunare(imaga, imagb, N / 2);
        p = 1;
    }

    if (bitimaga == '0' && bitimagb == '1' && p == 0)
    {
        if (e > 0)
        {
            bitimaga = '0';
            scadere(imaga, imagb, N / 2);
        }
        if (e < 0)
        {
            bitimaga = '1';
            scadere(imagb, imaga, N / 2);
            strcpy(imaga, imagb);
        }
        if (e == 0)
        {
            bitimaga = '0';
            for (j = 0; j < ((N / 2) - 1); j++)
            {
                imaga[j] = '0';
            }
        }
        p = 1;
    }

    if (bitimaga == '1' && bitimagb == '0' && p == 0)
    {
        if (e > 0)
        {
            bitimaga = '1';
            scadere(imaga, imagb, N / 2);
        }
        if (e < 0)
        {
            bitimaga = '0';
            scadere(imagb, imaga, N / 2);
            strcpy(imaga, imagb);
        }
        if (e == 0)
        {
            bitimaga = '0';
            for (j = 0; j < ((N / 2) - 1); j++)
                imaga[j] = '0';
        }
        p = 1;
    }

    if (bitimaga == '1' && bitimagb == '1' && p == 0)
    {
        bitimaga = '1';
        adunare(imaga, imagb, N / 2);
        p = 1;
    }

    // am obtinut astfel rezultatele in bitreala, reala,
    // bitimaga, imaga pe care le vom concatena astfel
    // a[0] devine bitreala, dupa care vom parcurge
    // dimensiunea partii reale si o vom adauga element
    // cu element in a. urmatorul element va fi chiar
    // bitul partii imaginare pe care il vom adauga
    // iar la final vom parcurge dimensiunea ramasa
    // a numarului si cu un contor k vom adauga in a
    // intreg numarul rezultat

    a[0] = bitreala;
    for (i = 1; i <= ((N - 1) / 2 - 1); i++)
        a[i] = reala[i - 1];
    a[(N - 1) / 2] = bitimaga;
    int k = 0;
    for (i = ((N - 1) / 2 + 1); i < N; i++)
    {
        a[i] = imaga[k];
        k++;
    }

    // afisam rezultatul format in a si il vom trimite
    // ca parametru pentru urmatoarele calcule cu noile
    // operatii citite

    printf("%s\n", a);
}

void calculminus(char *a, char *b, int N)
{

    // Am adaugat in readme logica dupa care se desfasoara
    // calculele din if urile de mai jos. Functia calculminus()
    // functioneaza similar cu cea de mai sus dar vor diferi
    // conditiile dupa care se vor calcula rezultatele. Putem
    // observa logica conditiilor in tabelul 2 din fisierul
    // README

    char reala[1001], realb[1001], imaga[1001], imagb[1001];
    char bitreala, bitrealb, bitimaga, bitimagb;
    int i, j;
    bitreala = a[0];
    bitrealb = b[0];
    bitimaga = a[(N - 1) / 2];
    bitimagb = b[(N - 1) / 2];

    strncpy(reala, a, ((N - 1) / 2));
    strncpy(realb, b, ((N - 1) / 2));
    memmove(reala, reala + 1, strlen(reala));
    memmove(realb, realb + 1, strlen(realb));

    strcpy(imaga, a);
    strcpy(imagb, b);
    memmove(imaga, imaga + (((N - 1) / 2) + 1), strlen(imaga));
    memmove(imagb, imagb + (((N - 1) / 2) + 1), strlen(imagb));

    reala[((N - 1) / 2 - 1)] = '\0';
    realb[((N - 1) / 2 - 1)] = '\0';

    int d = strncmp(reala, realb, (N / 2 - 1));
    int e = strncmp(imaga, imagb, (N / 2 - 1));
    int q = 0;
    int p = 0;

    // vom avea exact aceleasi initializari ca in functia de
    // mai sus si vom efectua aceleasi calcule in functie de
    // modificarile pe care le aduce semnul "-" al operatiei
    // Puteam face probabil o functie calcul in care sa se
    // efectueze ambele cazuri si eliminam astfel declararea
    // de 2 ori a variabilelor.

    if (bitreala == '0' && bitrealb == '0' && q == 0)
    {
        if (d > 0)
        {
            bitreala = '0';
            scadere(reala, realb, N / 2);
        }

        if (d < 0)
        {
            bitreala = '1';
            scadere(realb, reala, N / 2);
            strcpy(reala, realb);
        }
        if (d == 0)
        {
            bitreala = '0';
            for (j = 0; j < ((N / 2) - 1); j++)
                reala[j] = '0';
        }
        q = 1;
    }

    if (bitreala == '0' && bitrealb == '1' && q == 0)
    {
        bitreala = '0';
        adunare(reala, realb, N / 2);
        q = 1;
    }

    if (bitreala == '1' && bitrealb == '0' && q == 0)
    {
        bitreala = '1';
        adunare(reala, realb, N / 2);
        q = 1;
    }

    if (bitreala == '1' && bitrealb == '1' && q == 0)
    {
        if (d > 0)
        {
            bitreala = '1';
            scadere(reala, realb, N / 2);
        }
        if (d < 0)
        {
            bitreala = '0';
            scadere(realb, reala, N / 2);
            strcpy(reala, realb);
        }
        if (d == 0)
        {
            bitreala = '0';
            for (j = 0; j < ((N / 2) - 1); j++)
                reala[j] = '0';
        }
        q = 1;
    }

    if (bitimaga == '0' && bitimagb == '0' && p == 0)
    {
        if (e > 0)
        {
            bitimaga = '0';
            scadere(imaga, imagb, N / 2);
        }
        if (e < 0)
        {
            bitimaga = '1';
            scadere(imagb, imaga, N / 2);
            strcpy(imaga, imagb);
        }
        if (e == 0)
        {
            bitimaga = '0';
            for (j = 0; j < ((N / 2) - 1); j++)
                imaga[j] = '0';
        }
        p = 1;
    }

    if (bitimaga == '0' && bitimagb == '1' && p == 0)
    {
        bitimaga = '0';
        adunare(imaga, imagb, N / 2);
        p = 1;
    }

    if (bitimaga == '1' && bitimagb == '0' && p == 0)
    {
        bitimaga = '1';
        adunare(imaga, imagb, N / 2);
        p = 1;
    }

    if (bitimaga == '1' && bitimagb == '1' && p == 0)
    {
        if (e > 0)
        {
            bitimaga = '1';
            scadere(imaga, imagb, N / 2);
        }
        if (e < 0)
        {
            bitimaga = '0';
            scadere(imagb, imaga, N / 2);
            strcpy(imaga, imagb);
        }
        if (e == 0)
        {
            bitimaga = '0';
            for (j = 0; j < ((N / 2) - 1); j++)
                imaga[j] = '0';
        }
        p = 1;
    }

    a[0] = bitreala;
    for (i = 1; i <= ((N - 1) / 2 - 1); i++)
        a[i] = reala[i - 1];
    a[(N - 1) / 2] = bitimaga;
    int k = 0;
    for (i = ((N - 1) / 2 + 1); i < N; i++)
    {
        a[i] = imaga[k];
        k++;
    }

    // totul a functionat similar cu functia precedenta.
    // afisam rezultatul dupa ce l am stocat in a pe care
    // il vom returna ca parametru.

    printf("%s\n", a);
}

int main()
{
    // citire primul N si primul element

    char a[2001], b[2001], op;
    int N;
    scanf("%d", &N);
    scanf("%s", a);
    
    // loop infinit pentru citirea urmatoarelor operatii si numere

    while (1)
    {
        getchar();
        scanf("%c", &op);

        // ne oprim cand operatia citita este 0

        if (op == '0')
            return 0;
        getchar();
        scanf("%s", b);

        // 2 cazuri in functie de operatia citita si vor apela functia de
        // prelucrare si afisare. rezultatul va fi returnat in "a" de tip
        // pointer pentru a efectua urmatoarele operatii, astfel se va
        // putea lucra cu rezultatul obtinut in a si cel citit la infinit
        // in b pana la intalnirea operatiei 0

        if (op == '+')
        {
            calculplus(a, b, N);
        }

        if (op == '-')
        {
            calculminus(a, b, N);
        }
    }
    return 0;
}
