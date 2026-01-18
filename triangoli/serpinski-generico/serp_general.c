#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// numero di termini della successione
#define N 10000
#define STEPS 1000
#define OUTF "genfractal.dat"


/* Generalizzabile a qualsiasi triangolo IN DUE DIMENSIONI 
con base e altezza non necessariamente parallele agli assi cartesiani. */ 

// tipo di coordinate
typedef struct 
{
    float x;
    float y;
} point;

point p1;
point p2;
point p3;

/* Calcola la distanza tra due punti utilizzando la nota formula della geometria analitica */
float calc_distance(point coord1, point coord2) {
    // NB: DEVE ESSERE BIDIMENSIONALE.
    float a = pow(coord1.x-coord2.x, 2);
    float b = pow(coord1.y-coord2.y, 2);
    // printf("  ...norma al quadrato di (%.2f, %.2f) e (%.2f, %.2f): _ %.2f + %.2f _ \n\n", coord1[0],coord1[1], coord2[0],coord2[1], a,b);
    return sqrt( a + b );
}


/* Calcola il punto medio del segmento tra due punti point1 e point2, restituisce un 'point' */
point calc_midpoint(point point1, point point2) {
    point midpoint;
    midpoint.x = (point1.x + point2.x)/2;
    midpoint.y = (point1.y + point2.y)/2;
    return midpoint;
}


/* Dati tre array di coordinate per tre vertici, effettua un controllo se i tre punti definiscono
un triangolo non degenere. */
void check_triangle(point v1, point v2, point v3) {

        // Dato che il triangolo e' generico, controllo che non sia degenere
        float len_segment_1 = calc_distance(p1, p2);
        float len_segment_2 = calc_distance(p2, p3);
        float len_segment_3 = calc_distance(p1, p3);
    
        if (len_segment_1 == 0 || len_segment_2 == 0 || len_segment_3 == 0)
        {
            printf("ERRORE: triangolo degenere.");
            exit(1);
        }
        if (len_segment_1+len_segment_2 <= len_segment_3 || len_segment_2+len_segment_3 <= len_segment_1 || len_segment_1+len_segment_3 <= len_segment_2)
        {
            printf("ERRORE: il triangolo non rispetta la disuguaglianza dei lati.");
            exit(1);
        }
}


int main() {

    // inizializzazione del seed random
    srand48(time(0));

    // coordinate dei vertici del triangolo
    p1.x = (drand48()*10)-5;
    p1.y = (drand48()*10)-5;
    p2.x = (drand48()*10)-5;
    p2.y = (drand48()*10)-5;
    p3.x = (drand48()*10)-5;
    p3.y = (drand48()*10)-5;
    point vertx[3] = {p1, p2, p3};

    printf("Vertici: (%.2f, %.2f), (%.2f, %.2f), (%.2f, %.2f)", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);

    // il file di output
    FILE *fp;
    fp = fopen(OUTF, "w");
    if (fp == NULL)
    {
        printf("Errore nell'apertura del file di output");
        exit(1);
    }
    
    /*
    Il programma dovrebbe chiedere all’utente di inserire le coordinate del punto v1 da cui far partire 
    la successione, ma io uso uno dei tre vertici (non mi piace la scanf).  */
    // parto dal vertice 3
    point vin;
    vin.x = p3.x;
    vin.y = p3.y;
    
    
    /*
    A questo punto, il programma itera N volte l’algoritmo del Chaos game descritto sopra.
    Io uso la mia funzione calc_midpoint e salvo l'output in una struct invece che in un array.
    */
    for (int i = 0; i < N; i++)
    {
        // vertice random tra 0,1,2
        int j = drand48()*3;
        // printf("%d ", j);

        // crea il nuovo punto
        point vout = calc_midpoint(vin, vertx[j]);
        // printf("%.2f %.2f\n", vout[0], vout[1]);

        /*
        Ogni STEPS passi, il programma stampa sullo schermo le seguenti informazioni: numero del passo;
        numero del vertice scelto per generare il nuovo punto; coordinate del punto di partenza vn;
        coordinate del punto di arrivo vn+1, nel formato:
        It. n. 860 vertice n. 1 v(n) = (-2.38,0.83) v(n+1)=(-2.69,0.42)
        */
        if ((i+1)%STEPS == 0)
        {
            printf("It. n. %4d vertice n. %d v(n) = (%.2f, %.2f) e v(n+1) = (%.2f, %.2f)\n",
                i+1, j, vin.x, vin.y, vout.x, vout.y);
        }

        /*
        Le coordinate dei punti vn che compongono la successione vengono salvate su un ﬁle di due
        colonne di nome fractal.dat
        */
        fprintf(fp, "%.2f %.2f\n", vin.x, vin.y);
        

        // scrivo il valore di vn+1 come nuovo punto iniziale
        vin.x = vout.x; 
        vin.y = vout.y; 
    }
    
    
    fclose(fp);
    exit(0);
}