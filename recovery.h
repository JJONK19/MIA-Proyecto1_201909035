#ifndef RECOVERY
#define RECOVERY

//Locales
#include "structs.h"
#include "mkgrp.h"
#include "mkusr.h"
#include "rmusr.h"
#include "rmgrp.h"
#include "chgrp.h"
#include "chmod.h"
#include "mkdir.h"
#include "mkfile.h"
#include "chown.h"
#include "edit.h"
#include "remove.h"
#include "copy.h"
#include "move.h"
#include "rename.h"

//Librerias
#include <string>
#include <algorithm>
#include <vector>
#include <iostream>

void recovery(std::vector<std::string> &parametros, std::vector<disco> &discos);      

#endif
