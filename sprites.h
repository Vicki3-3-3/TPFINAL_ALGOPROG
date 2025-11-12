#include <stdio.h>
#include "sprite.h"
#ifndef SPRITES_H
#define SPRITES_H

/*TDA sprites
Contiene cantidad indefinida de sprite_t, los cuales se recuperan por etiqueta
Invariantes de representacion:
Cada sprite cumple las condiciones del sprite_t:
Etiqueta es una cadena terminada en '\0'
Ancho y alto ocupan 1 byte, Maximos pixeles 255x255
Pixeles en paquetes de 1 byte, se agrupan de a filas
*/
typedef struct sprites sprites_t;
#endif

//CONSTRUCTOR: TDA sprites con sprites archivo ruta
sprites_t *sprites_crear(const char *ruta);
//DESTRUCTOR
void sprites_destruir(sprites_t *ss);

//GETTER: retorna cantidad de sprites
size_t sprites_cantidad(const sprites_t *ss);

//Retorna el sprite con la etiqueta indicada, sino retorna NULL
sprite_t *sprites_obtener(const sprites_t *ss, const char *etiqueta);

