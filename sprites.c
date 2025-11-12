#include "sprites.h"
#include "sprite.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct sprites{
	//n es la cantidad de sprites en el vector sprites
	//si n = 0, sprites = NULL
	// n <= MAX_SPRITES
	sprite_t **sprites;
	size_t n;
};

//CONSTRUCTOR: TDA sprites con sprites archivo ruta
sprites_t *sprites_crear(const char *ruta){
	FILE *fi = fopen(ruta, "rb");
	 if (fi == NULL) {
        perror("Error al abrir archivo binario");
        return NULL;
    }

	sprites_t *ss = malloc(sizeof(sprites_t));
	if(ss == NULL){
		fclose(fi);
		return NULL;
	}
		ss->n = 0;
		ss->sprites = NULL;

		sprite_t *s;
		while((s = sprite_crear(fi))!= NULL){
			sprite_t **aux_ss = realloc(ss->sprites, (ss->n + 1)*sizeof(sprite_t *));
			if(aux_ss == NULL){
				sprite_destruir(s);
				break;
			}
			ss->sprites = aux_ss;
			ss->sprites[ss->n] = s;
			ss->n++;
			}	

	fclose(fi);

	if(ss->n == 0){
		free(ss->sprites);
		free(ss);
		return NULL;
	}

	return ss;
}

//DESTRUCTOR
void sprites_destruir(sprites_t *ss){
	if(ss == NULL) return;
	for(size_t i = 0; i < ss->n; i++){
		sprite_destruir(ss->sprites[i]);
	}
	free(ss->sprites);
	free(ss);
}

//GETTER: retorna cantidad de sprites
size_t sprites_cantidad(const sprites_t *ss){
	return ss->n;
}

//Retorna el sprite con la etiqueta indicada, sino retorna NULL
sprite_t *sprites_obtener(const sprites_t *ss, const char *etiqueta){
	if(etiqueta == NULL) return NULL;
	for(size_t i = 0; i < ss->n; i++){
		if(strcmp(etiqueta, sprite_etiqueta(ss->sprites[i]))==0){
			return ss->sprites[i];
		}
	}
	return NULL;
}