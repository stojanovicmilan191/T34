#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 21

//struktura
typedef struct merenje_st
{
    char prostorija[MAX_SIZE];
    double jutro;
    double podne;
    double vece;
}merenje;

//deklaracije funkcija
FILE* safe_fopen(char* , char* , int );
void procitaj(FILE* , merenje* , int* );
void prosecnaTemp(merenje* , int );

int main(int brArg, char** argumenti)
{
    //provera tacnosti poziva
    if (brArg != 2)
    {
        printf("Pogresan poziv programa, primer ispravnog poziva ./a.out merenja.txt");
        exit(EXIT_FAILURE);
    }
    
    int n;
    merenje merenja[30];
    //otvaranje ulazne datoteke
    FILE* ulazna = safe_fopen(argumenti[1], "r", 1);
    procitaj(ulazna, merenja, &n);
    //zatvaranje ulazne datoteke ovo nemoj da zaboravis
    fclose(ulazna);
    prosecnaTemp(merenja, n);
}

//funkcija safe_open kako program ne bi pucao kada nije moguce otvoriti datoteku, kod_greske sluzi kako bi smo znali gde se program zavrsio
FILE* safe_fopen(char* naziv, char* rezim, int kod_greske)
{
    //otvaranje datoteke
    FILE* pf = fopen(naziv, rezim);
    //provera da li pokazivac pf sadrzi neku adresu
    if (pf == NULL)
    {
        printf("Nemoguce je otvoriti datoteku %s\n", naziv);
        //zavrasavanje programa sa iznaznim kodom greske
        exit(kod_greske);
    }
    return pf;
}

//funckija za citanje iz fajla
void procitaj(FILE* ulazna, merenje* merenja, int* pn)
{
    int i = 0;
    //while petlja cita iz ulazne datoteke sve dok ne naidje na EOF(End Of File)
    while (fscanf(ulazna, "%s %lf %lf %lf", merenja[i].prostorija, &merenja[i].jutro, &merenja[i].podne, &merenja[i].vece) != EOF)
    {
        //i je brojac redova
        i++;
    }
    //smestamo vrednost brojaca na adresu pn kako bismo u main funkciji znali koliko smo redova procitali
    *pn = i;
}

void prosecnaTemp(merenje* merenja, int n)
{
    double avg, max = 0;
    //for petlja koja racuna prosecnu temperaturu svake prostorije
    for (int i = 0; i < n; i++)
    {
        avg = merenja[i].jutro + merenja[i].podne + merenja[i].vece;
        avg /= 3;
        //ispisivanje naziva prostorije i prosecne temperature
        printf("%s %.1lf\n", merenja[i].prostorija, avg);
        //pronalazak maksimalne prosecne temperature
        if (avg > max)
        {
            max = avg;
        }
    }
    printf("Najveca prosecna temperatura u zgradi je %.1lf stepeni\n", max);
}