#ifndef ANALIZADOR
#define ANALIZADOR

//Locales
#include "structs.h"
#include "lexico.h"
#include "execute.h"
#include "mkdisk.h"
#include "rmdisk.h"
#include "fdisk.h"
#include "mount.h"
#include "rep.h"

//Librerias
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

void ejecutar(std::string &cadena, usuario &sesion, std::vector<disco> &discos);         

#endif