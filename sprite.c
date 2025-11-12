#include "sprite.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct sprite{
	//etiqueta != NULL
	//si alto = 0 y ancho = 0, pixeles NULL
	//pixeles tiene ancho*alto elementos, maximo 255x255
	char *etiqueta;
	size_t alto;
	size_t ancho;
	uint8_t **pixeles; //matriz de pixeles con ancho columnas y alto filas
};


sprite_t *sprite_crear(FILE *fi){
	if(fi == NULL) return NULL;
	
	char etiqueta[21];
	for(size_t i = 0; i <= 20; i++){
		etiqueta[i] = 0;
	}

	uint8_t ancho, alto = 0;

	size_t bytes_leidos = fread(etiqueta, sizeof(char), 20, fi);
	if(bytes_leidos!=20)return NULL;
	
	etiqueta[20] = '\0';

	if(fread(&ancho, sizeof(ancho), 1, fi)!= 1 || fread(&alto, sizeof(alto), 1, fi)!= 1) return NULL;

	sprite_t *sprite = malloc(sizeof(sprite_t));
	if(sprite == NULL) return NULL;

	sprite->etiqueta = malloc(21*sizeof(char));
	if(sprite->etiqueta == NULL){
		free(sprite);
		return NULL;
	}

	memcpy(sprite->etiqueta, etiqueta, 21);

	sprite->ancho = ancho;
	sprite->alto = alto;

	sprite->pixeles = malloc(alto*sizeof(uint8_t*));
	if(sprite->pixeles == NULL){
		free(sprite->etiqueta);
		free(sprite);
		return NULL;
	}

	for(size_t i = 0; i < sprite->alto; i++){
		sprite->pixeles[i] = NULL;
	}

	size_t bytes_fila = (ancho + 7)/8;
	uint8_t *auxiliar = malloc(bytes_fila);
	if(auxiliar == NULL){
		free(sprite);
		return NULL;
	}

	for(size_t fila = 0; fila < sprite->alto; fila++){
		if(fread(auxiliar, sizeof(uint8_t), bytes_fila, fi) != bytes_fila){
			free(auxiliar);
			sprite_destruir(sprite);
			return NULL;
		}

		sprite->pixeles[fila] = malloc(sprite->ancho * sizeof(uint8_t));
		if(sprite->pixeles[fila] == NULL){
			free(auxiliar);
			sprite_destruir(sprite);
			return NULL;
		}

		for(size_t columna = 0; columna < sprite->ancho; columna++){
			size_t byte = columna / 8;
			size_t bit = columna % 8;
			bool valor = ((auxiliar[byte] >> bit) & 1)!= 0;
			sprite_establecer(sprite, fila, columna, valor);
		}
	}
	free(auxiliar);
	return sprite;
}

void sprite_destruir(sprite_t *s){
	if(s == NULL) return;
	free(s->etiqueta);
	if(s->pixeles != NULL){
		for(size_t i = 0; i < s->alto; i++){
			free(s->pixeles[i]);
		}
		free(s->pixeles);
	}
	free(s);
}

bool sprite_a_pbm(const sprite_t *s, FILE *fo){
	if(s == NULL || fo == NULL) return false;
	fprintf(fo, "P1\n");
	fprintf(fo, "%zd %zd\n", s->ancho, s->alto);
	for(size_t i = 0; i < s->alto; i++){
		for(size_t j = 0; j < s->ancho; j++){
			fprintf(fo, "%d  ", s->pixeles[i][j]? 1 : 0);
		}
		fprintf(fo, "\n");
	}
	return true;
}

size_t sprite_ancho(const sprite_t *s){
	if(s == NULL) return 0;
	return s->ancho;
}

size_t sprite_alto(const sprite_t *s){
	if(s == NULL) return 0;
	return s->alto;
}

char *sprite_etiqueta(const sprite_t *s){
	if(s == NULL) return NULL;
	return s->etiqueta;
}

bool sprite_obtener(const sprite_t *s, size_t fila, size_t col){
	if(s == NULL) return false;
	if(fila >= s->alto || col >= s->ancho) return false;
	return s->pixeles[fila][col] != 0;
}

bool sprite_establecer(sprite_t *s, size_t fila, size_t col, bool valor){
	if(s==NULL || fila >= s->alto || col >= s->ancho)
		return false;
	s->pixeles[fila][col] = valor ? 1 : 0;
	return true;
}

