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
#include "unmount.h"
#include "login.h"
#include "logout.h"
#include "mkfs.h"
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
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

void ejecutar(std::string &cadena, usuario &sesion, std::vector<disco> &discos);         

#endif