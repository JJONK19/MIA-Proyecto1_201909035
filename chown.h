#ifndef CHOWN
#define CHOWN

//Locales
#include "structs.h"

//Librerias
#include <iostream>
#include <regex>
#include <stack>

void chown(std::vector<std::string> &parametros, std::vector<disco> &discos, usuario &sesion);

#endif