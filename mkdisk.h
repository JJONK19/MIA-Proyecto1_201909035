#ifndef MKDISK
#define MKDISK

//Librerias 
#include "structs.h"

//Locales
#include <iostream>
#include <exception>
#include <filesystem>

/*
    parametros: Es el vector con los parametros de la instrucción
*/
void mkdisk(std::vector<std::string> &parametros);

#endif