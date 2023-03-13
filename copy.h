#ifndef COPY
#define COPY

//Locales
#include "structs.h"

//Liberias
#include <iostream>
#include <regex>
#include <stack>
#include <string.h>

//La ruta es la ubicacion fisica del disco
//Retornan el inodo donde se escribio el archivo

void copy(std::vector<std::string> &parametros, std::vector<disco> &discos, usuario &sesion);

int carpetas(usuario &sesion, sbloque &sblock, std::string &ruta, int &no_inodo, int &padre_inodo);

int archivos(usuario &sesion, sbloque &sblock, std::string &ruta, int &no_inodo);

#endif