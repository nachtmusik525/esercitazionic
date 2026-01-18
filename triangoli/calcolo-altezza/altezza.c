#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
/* Genera un triangolo casuale e ne calcola l'altezza. */

#define OUTF "altezza.dat"

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


/*Calcolo determinante di una matrice 2x2.*/
float det(float coeff[2][2]) {
    // per colonne
    float a = coeff[0][0], b = coeff[1][0], c = coeff[0][1], d= coeff[1][1]; 
    printf("...(sist)... a: %.2f, b: %.2f, c: %.2f, d: %.2f\n", a,b,c,d);
    float det = a*d - b*c;
    printf("...det: %.2f\n", det);
    return det;
}

/* Risolve un sistema 2x2 avendo in input una matrice 2x2 di coefficienti 'coeff', 
una matrice colonna per i termini noti 'cterms', e restituisce un punto {x,y}. */
point solve_2x2_system(float coeff[2][2], float cterms[2]) {
    float det0 = det(coeff);

    if (det0 == 0) {
        printf("Sistema indeterminato o impossibile\n");
        exit(1);
    }

    float mat_x[2][2] = {{cterms[0], cterms[1]}, {coeff[1][0], coeff[1][1]}};
    float mat_y[2][2] = {{coeff[0][0], coeff[0][1]}, {cterms[0], cterms[1]}};
    float det_x = det(mat_x);
    float det_y = det(mat_y);
    printf("...%.2f, %.2f\n", det_x, det_y);

    point sol;
    sol.x = (det_x / det0);
    sol.y = (det_y / det0);
    printf("x: %.2f\n", sol.x);
    printf("y: %.2f\n", sol.y);
    return sol;
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

/* Dati tre array di coordinate per tre vertici, usa i primi due come base e 
calcola il punto di ancoraggio per l'altezza. */
point calc_height_anchorpoint(point v1, point v2, point v3) {
    
    check_triangle(v1,v2,v3);
    point anchorpoint;

    // verifico se la base è orizzontale o verticale 
    if (v2.x == v1.x) {
        // base verticale: il punto di ancoraggio dell'altezza e' sulla stessa ascissa
        // della base e sulla stessa ordinata del terzo vertice
        printf("...Base verticale.\n");
        anchorpoint.x = v2.x;
        anchorpoint.y = v3.y;
        return anchorpoint;
    }
    if (v2.y == v1.y)
    {
        // base orizzontale: il punto di ancoraggio dell'altezza e' sulla stessa ordinata
        // della base e sulla stessa ascissa del terzo vertice
        printf("...Base orizzontale.\n");
        anchorpoint.x = v3.x;
        anchorpoint.y = v2.y;
        return anchorpoint;
    }
    // non puo' rispettare entrambe le condizioni per via del controllo sul triangolo degenere.
    
    // ora proseguo calcolando i coefficienti angolari e ripeto una condizione simile per risolvere il sistema
    float m0 = (v2.y - v1.y)/(v2.x - v1.x); //coeff angolare retta che passa per la base
    float m1 = (-1)/m0; //coeff angolare inverso e opposto

    printf("...c. angolari: %.2f %.2f\n", m0, m1);
    
    // calcolo l'altezza risolvendo il sistema tra le due rette ortogonali
    // se non sono rette orizzontali o verticali, risolvo il sistema 
    if (m0 != 0 && m1 != 0)
    {
            //matrice dei coeff del sistema
            float coef[2][2] = {
                {(-1)*m0, (-1)*m1},
                {1,1}
            }; 
            // termini noti
            float tn[2] = {v1.y-v1.x*m0, v3.y-m1*v3.x};
            anchorpoint = solve_2x2_system(coef, tn);
    }
    return anchorpoint;
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

    // coordinate dei vertici del triangolo
    p1.x = (drand48()*10)-5;
    p1.y = (drand48()*10)-5;
    p2.x = (drand48()*10)-5;
    p2.y = (drand48()*10)-5;
    p3.x = (drand48()*10)-5;
    p3.y = (drand48()*10)-5;

    printf("Vertici: (%.2f, %.2f), (%.2f, %.2f), (%.2f, %.2f\n", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
    
    // Lunghezza della base
    float b = calc_distance(p1, p2);
    printf("\nBase: %.2f\n", b);
    
    // Calcolo dell'altezza
    point anchor = calc_height_anchorpoint(p1, p2, p3);
    float h = calc_distance(anchor, p3);
    printf("\nAltezza: %.2f\n", h);
    printf("...Punto ancoraggio: (%.2f, %.2f)\n", anchor.x, anchor.y);    
    fprintf(fp, "%.2f %.2f\n%.2f %.2f\n%.2f %.2f\n%.2f %.2f", p1.x, p1.y, p2.x, p2.y, p3.x, p3.y, anchor.x, anchor.y);
    
    // Area
    float area = (b*h)/2;
    printf("\nArea: %.2f\n", area);


    fclose(fp);
    exit(0);
}