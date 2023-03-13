#ifndef EXEC
#define EXEC

//Locales
#include "lexico.h"
#include "structs.h"
#include "mkdisk.h"
#include "rmdisk.h"
#include "fdisk.h"
#include "mount.h"
#include "unmount.h"
#include "mkfs.h"
#include "login.h"
#include "logout.h"
#include "mkgrp.h"
#include "mkusr.h"
#include "rmusr.h"
#include "rmgrp.h"
#include "chgrp.h"
#include "chmod.h"
#include "mkdir.h"
#include "mkfile.h"
#include "pause.h"
#include "loss.h"
#include "chown.h"
#include "edit.h"
#include "remove.h"
#include "copy.h"
#include "move.h"
#include "find.h"
#include "rename.h"
#include "cat.h"
#include "recovery.h"
#include "rep.h"

//Librerias
#include <iostream>
#include <iterator>
#include <regex>
#include <fstream>

/*
    parametros: lista de parametros de la instrucción exec
    sesion: struct con los datos del usuario loggeado- Sirve para las instrucciones del script. Es global durante la ejecución.
    discos: Vector con la informacón de los discos cargados en memoria. Es global durante la ejecución.
*/
void execute(std::vector<std::string> &parametros, usuario &sesion, std::vector<disco> &discos);

#endif