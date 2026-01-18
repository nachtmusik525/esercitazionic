#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// numero di termini della successione
#define N 10000
#define STEPS 1000
#define OUTF "fractal.dat"

// coordinate dei vertici del triangolo
#define p1x -3.0
#define p1y  0.0
#define p2x  3.0
#define p2y  0.0
#define p3x  0.0
#define p3y  5.0

const float p1[2] = {p1x, p1y};
const float p2[2] = {p2x, p2y};
const float p3[2] = {p3x, p3y};


/* Controlla se il punto 'point' (array di coordinate) si trova all'interno
del rettangolo delimitato dai tre vertici w1, w2, w3. */
int IsInRect(float point[2], const float w1[2], const float w2[2], const float w3[2]) {
    float max_x = fmaxf(fmaxf(w1[0], w2[0]), w3[0]);
    float max_y = fmaxf(fmaxf(w1[1], w2[1]), w3[1]);

    float min_x = fminf(fminf(w1[0], w2[0]), w3[0]);
    float min_y = fminf(fminf(w1[1], w2[1]), w3[1]);

    printf("Punto (%.2f, %.2f) compreso tra ascisse %.2f, %.2f e ordinate %.2f, %.2f ? ", point[0], point[1], min_x, max_x, min_y, max_y);

    if (point[0] >= min_x && point[0] <= max_x && point[1] >= min_y && point[1] <= max_y) { printf("OK\n"); return 1; }
    else { printf("NO\n"); return 0; }
}

/*    ChaosGame:
    Si genera un nuovo punto della successione come: v2 = 1/2 (v1 + PR). 
    Il simbolo PR, con R = 1, 2 o 3 indica un vertice scelto in modo casuale. */
void NewPoint(const float v1[2], const float pr[2], float v2[2]) {
    v2[0] = (v1[0] + pr[0])/2;
    v2[1] = (v1[1] + pr[1])/2;
}



int main() {
    
    // inizializzazione del seed random
    srand48(time(0));

    // il file di output
    FILE *fp;
    fp = fopen(OUTF, "w");
    if (fp == NULL)
    {
        printf("Errore nell'apertura del file di output");
        exit(1);
    }
    

    /*
    Il programma chiede all’utente di inserire le coordinate del punto v1 da cui far partire 
    la successione, e controlla, tramite una funzione IsInRect(), che il punto corrispondente si trovi
    all’interno del rettangolo di base 6 e altezza 5, che contiene esattamente il triangolo di vertici
    P1, P2 e P3 */
    const float *vertx[3] = {p1, p2, p3};
    float v1[2];
    float vin[2];
    float vout[2];

    // chiedo le coordinate del vertice iniziale
    int isinrect = 0; 
    while (isinrect == 0)
    {
        printf("Inserisci le coordinate x,y del punto da cui far partire la successione:\n");
        if (scanf("%f %f", &v1[0], &v1[1]) != 2) {
            printf("Errore: devi inserire due numeri!\n");
            // Pulizia del buffer: leggiamo caratteri finché non troviamo un invio (\n)
            int c;
            while ((c = getchar()) != '\n' && c != EOF); 
            continue; // Torna all'inizio del ciclo e richiedi l'input
        }
        printf("Hai inserito %.2f, %.2f\n", v1[0], v1[1]);
        isinrect = IsInRect(v1, p1, p2, p3);
    }
    
    // Le coordinate iniziali vengono quindi salvate in un vettore vin[] di tipo e dimensioni opportune.
    vin[0] = v1[0]; vin[1] = v1[1];

    /*
    A questo punto, il programma itera N volte l’algoritmo del Chaos game descritto sopra, tramite
    una funzione NewPoint() che riceve in input le coordinate del punto vn contenute nel vettore
    vin[] e genera un nuovo punto della successione, scegliendo in modo casuale uno dei tre vertici
    PR e calcolando vn+1 tramite l’Eq. 1.1. Le coordinate del punto vn+1 vengono salvate in un
    vettore vout[] di tipo e dimensioni opportune.

    ChaosGame:
    Si genera un nuovo punto della successione come: v2 = 1/2 (v1 + PR). 
    Il simbolo PR, con R = 1, 2 o 3 indica un vertice scelto in modo casuale.
    */
    for (int i = 0; i < N; i++)
    {
        // vertice random tra 0,1,2
        int j = drand48()*3;
        // printf("%d ", j);

        // crea il nuovo punto
        NewPoint(vin, vertx[j], vout);
        // printf("%.2f %.2f\n", vout[0], vout[1]);

        /*
        Ogni 10 passi, il programma stampa sullo schermo le seguenti informazioni: numero del passo;
        numero del vertice scelto per generare il nuovo punto; coordinate del punto di partenza vn;
        coordinate del punto di arrivo vn+1, nel formato:
        It. n. 860 vertice n. 1 v(n) = (-2.38,0.83) v(n+1)=(-2.69,0.42)
        */
        if ((i+1)%STEPS == 0)
        {
            printf("It. n. %4d vertice n. %d v(n) = (%.2f, %.2f) e v(n+1) = (%.2f, %.2f)\n",
                i+1, j, vin[0], vin[1], vout[0], vout[1]);
        }

        /*
        Le coordinate dei punti vn che compongono la successione vengono salvate su un ﬁle di due
        colonne di nome fractal.dat
        */
        fprintf(fp, "%.2f %.2f\n", vin[0], vin[1]);
        

        // scrivo il valore di vn+1 come nuovo punto iniziale
        vin[0] = vout[0]; 
        vin[1] = vout[1]; 
    }
    
    fclose(fp);
    exit(0);
}