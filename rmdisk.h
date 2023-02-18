#ifndef RMDISK
#define RMDISK

//Locales
#include "structs.h"

//Librerias
#include <iostream>
#include <exception>
#include <filesystem>

/*
    parametros: Es el vector con los parametros de la instrucción
*/
void rmdisk(std::vector<std::string> &parametros);

#endif