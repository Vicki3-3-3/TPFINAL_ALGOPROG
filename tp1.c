# include <stdio.h>
# include <stddef.h>
# include <stdbool.h>

void inicializar_matriz(size_t filas, size_t columnas, char matriz[filas][columnas]){

	for(size_t f=0; f<filas; f++){
		for(size_t c=0; c<columnas; c++){
			matriz[f][c]=0;
		}
	}
}


void copiar_matriz(size_t filas, size_t columnas, char destino[filas][columnas], char origen[filas][columnas]){

	for(size_t f=0; f<filas; f++){
		for(size_t c=0; c<columnas; c++){
			destino[f][c]=origen[f][c];
		}
	}
}


void imprimir_ppm(size_t filas, size_t columnas, char matriz[filas][columnas]){
	
	printf("P1\n%zu %zu\n",columnas, filas);
	
	for(size_t f=0; f<filas; f++){

		for(size_t c=0; c<columnas; c++)

			printf("%d ", matriz[f][c]);
		
		putchar('\n');
	}
}


bool pegar_submatriz(size_t mfs, size_t mcs, char matriz[mfs][mcs], size_t sfs, size_t scs, char submatriz[sfs][scs], size_t fi, size_t ci){

	if(sfs>mfs || scs>mcs)
		return false;

	for(size_t n=0; n<sfs; n++){
		size_t f_m = fi+n;

		for(size_t i=0; i<scs; i++){
			size_t c_m = ci+i;

			matriz[f_m][c_m]=submatriz[n][i];
		}
	}

	return true;
}


int sumar_entorno(size_t filas, size_t columnas, char m[filas][columnas], size_t fc, size_t cc){

	int suma=0;

	for(size_t i=0; i<3; i++){
		size_t c_m = cc+i-1;

		for(size_t n=0; n<3; n++){
			size_t f_m = fc+n-1;
			
			if(f_m==fc && c_m==cc)
				continue;

			suma+=m[f_m][c_m];
		}
	}

	return suma;
}


void evolucionar_celulas(size_t filas, size_t columnas, char final[filas][columnas], char inicial[filas][columnas]){

	for(size_t f=1; f<filas-1; f++){
		for(size_t c=1; c<columnas-1; c++){
			char celula=inicial[f][c];
			int suma = sumar_entorno(filas, columnas, inicial, f, c);

			if (celula==0 && suma==3)
				celula=1;

			else 
				if(celula==1 && (suma!=2 && suma!=3))
				celula=0;
			

			final[f][c]=celula;
		}
	}
}


//////////////////


#define ANCHO   20
#define ALTO    20
#define CICLOS  10

int main() {
    char m1[3][3] = {
        {1, 1, 0},
        {1, 0, 1},
        {0, 1, 0},
    };

    char m2[2][4] = {
        {0, 1, 1, 1},
        {1, 1, 1, 0},
    };

    char m3[3][3] = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 1},
    };

    char matriz[ANCHO][ALTO];

    inicializar_matriz(ANCHO, ALTO, matriz);

    pegar_submatriz(ANCHO, ALTO, matriz, 3, 3, m1, 15, 5);
    pegar_submatriz(ANCHO, ALTO, matriz, 2, 4, m2, 15, 15);
    pegar_submatriz(ANCHO, ALTO, matriz, 3, 3, m3, 5, 5);

    char auxiliar[ANCHO][ALTO];
    // Inicializamos toooda la matriz para garantizar que el borde esté en cero:
    inicializar_matriz(ANCHO, ALTO, auxiliar);

    for(size_t ciclo = 0; ciclo < CICLOS; ciclo++) {
        evolucionar_celulas(ANCHO, ALTO, auxiliar, matriz);
        copiar_matriz(ANCHO, ALTO, matriz, auxiliar);
    }

    imprimir_ppm(ANCHO, ALTO, matriz);

    return 0;
}