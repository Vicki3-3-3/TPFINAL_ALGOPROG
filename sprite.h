#ifndef SPRITE_H
#define SPRITE_H
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>

/*Invariantes de representacion para el TDA sprite
Etiqueta es una cadena terminada en '\0'
Ancho y alto ocupan 1 byte
Maximos pixeles 255x255
Pixeles en paquetes de 1 byte

+-------------------+-------+-------+--------------------------------+
|      Etiqueta     | ancho | alto  |            pixeles             |
+-------------------+-------+-------+--------------------------------+
*/
typedef struct sprite sprite_t;

#endif

//CONSTRUCTOR: retorna sprite del archivo binario fi. NULL si falla o EOF
//fi != NULL, si fi == NULL, retorna NULL
//los caracteres de la etiqueta deben ocupar 20 bytes
//ancho y alto deben ocupar, como maximo, 255x255
//cada pixel ocupa 1 byte, y los pixeles totales deben ser ancho*alto
sprite_t *sprite_crear(FILE *fi);

//DESTRUCTOR
void sprite_destruir(sprite_t *s);

//Escribe en formato pbm el contenido del sprite s en el archivo fo en modo escritura de texto
bool sprite_a_pbm(const sprite_t *s, FILE *fo);

//GETTERS
size_t sprite_ancho(const sprite_t *s);
size_t sprite_alto(const sprite_t *s);
char *sprite_etiqueta(const sprite_t *s);
//Pixel de s en la fila y col indicada
bool sprite_obtener(const sprite_t *s, size_t fila, size_t col);

//SETTER
//escribe el valor dado en el pixel de s en la fila y col indicada
bool sprite_establecer(sprite_t *s, size_t fila, size_t col, bool valor);

