#ifndef MKFILE
#define MKFILE

//Locales
#include "structs.h"
#include "mkdir.h"

//Librerias
#include <iostream>
#include <regex>
#include <stack>
#include <string.h>
#include <fstream>

void mkfile(std::vector<std::string> &parametros, std::vector<disco> &discos, usuario &sesion);

#endif