#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 21

typedef struct kvar_st
{
    char ulica[MAX_SIZE];
    unsigned int broj;
    unsigned int brojDomacinstava;
    char tipObjekta[MAX_SIZE];
    char prijavljenKvar[MAX_SIZE];
}kvar;

FILE* safe_fopen(char* , char* , int );
void citanje(FILE* , kvar* , int* );
void upis(FILE* , kvar* , int , int );

int main(int brArg, char** argumenti)
{
    //provera poziva programa
    if (brArg != 4)
    {
        printf("Pogresan poziv programa, primer poziva ./a.out 5 trafo-stanica.txt bez-energije.txt");
        exit(EXIT_FAILURE);
    }
    if (atoi(argumenti[1])<0)
    {
        printf("Nepravilan unos drugog argumenta poziva");
        exit(2);
    }
    
    int n;
    kvar kvarovi[100];
    FILE* ulazna = safe_fopen(argumenti[2], "r", 3);
    citanje(ulazna, kvarovi, &n);
    FILE* izlazna = safe_fopen(argumenti[3], "w", 4);
    upis(izlazna, kvarovi, n, atoi(argumenti[1]));
    return 0;
}

FILE* safe_fopen(char* naziv, char* rezim, int kod_greske)
{
    FILE* pf = fopen(naziv, rezim);
    if (pf == NULL)
    {
        printf("Nemoguce je otvoriti datoteku %s\n", naziv);
        exit(kod_greske);
    }
    return pf;
}

void citanje(FILE* ulazna, kvar* kvarovi, int* n)
{
    int i = 0;
    while (fscanf(ulazna, "%s %d %d %s %s", kvarovi[i].ulica, &kvarovi[i].broj, &kvarovi[i].brojDomacinstava, kvarovi[i].tipObjekta, kvarovi[i].prijavljenKvar) != EOF)
    {
        i++;
    }
    *n = i;
}

void upis(FILE* izlazna, kvar* kvarovi, int n, int dozvoljenBroj)
{
    int brDomacinstava = 0, brPrijava = 0;
    for (int i = 0; i < n; i++)
    {
        //provera da li postoji kvar na datoj adresi
        if (strcmp(kvarovi[i].prijavljenKvar, "NE"))
        {
            fprintf(izlazna, "%s %2u %2u %s %s\n", kvarovi[i].ulica, kvarovi[i].broj, kvarovi[i].brojDomacinstava, kvarovi[i].tipObjekta, kvarovi[i].prijavljenKvar);
            // prebrojavanje priava
            brPrijava++;
            // prebrojavanje domacinstava
            brDomacinstava += kvarovi[i].brojDomacinstava;
        }
        
    }
    //ispisivanje broja domacinstava
    fprintf(izlazna, "\nBroj domacinstava bez struje: %d\n", brDomacinstava);
    //provera da li je moguc kvar trafo stanice
    if (brPrijava >= dozvoljenBroj)
    {
        fprintf(izlazna, "\nMoguc kvar trafo stanice\n");
    }
    
}