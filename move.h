#ifndef MOVE
#define MOVE

//Locales
#include "structs.h"
#include "remove.h"

//Librerias
#include <iostream>
#include <regex>
#include <stack>
#include <string.h>

void move(std::vector<std::string> &parametros, std::vector<disco> &discos, usuario &sesion);

bool parchivos(usuario &sesion, sbloque &sblock, std::string &ruta, int &no_inodo);

bool pcarpetas(usuario &sesion, sbloque &sblock, std::string &ruta, int &no_inodo);

void actualizar_padre(usuario &sesion, sbloque &sblock, std::string &ruta, int &no_inodo, int &padre_inodo);

#endif