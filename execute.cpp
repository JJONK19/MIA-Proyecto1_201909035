#include "execute.h"

void execute(std::vector<std::string> &parametros, usuario &sesion, std::vector<disco> &discos){
    //VARIABLES
    std::string ruta = "";          //Almacena la ruta del script
    bool paramFlag = true;          //Indica si se cumplen con los parametros del comando
    bool required = true;           //Indica si vienen los parametros obligatorios
    FILE *archivo;                  //Sirve para verificar que el archivo exista
    std::string linea;              //Usado para leer el script

    //COMPROBACIÓN DE PARAMETROS
    for(int i = 1; i < parametros.size(); i++){
        std::string &temp = parametros[i];
        std::vector<std::string> salida(std::sregex_token_iterator(temp.begin(), temp.end(), igual, -1),
                    std::sregex_token_iterator());

        std::string &tag = salida[0];
        std::string &value = salida[1];

        //Pasar a minusculas
        transform(tag.begin(), tag.end(), tag.begin(),[](unsigned char c){
            return tolower(c);
        });

        if(tag == "path"){
            ruta = value;
        }else{
            std::cout << "ERROR: El parametro " << tag << " no es valido." << std::endl;
            paramFlag = false;
            break;
        }
    }

    if(!paramFlag){
        return;
    }

    //COMPROBAR PARAMETROS OBLIGATORIOS
    if(ruta == ""){
        required = false;
    }

    if(!required){
        std::cout << "ERROR: La instrucción execute carece de todos los parametros obligatorios." << std::endl;
    }

    //VERIFICAR QUE EL ARCHIVO EXISTA
    archivo = fopen(ruta.c_str(), "r");

    if(archivo == NULL){
        std::cout << "ERROR: El Script no existe.." << std::endl;
        return;
    }else{
        fclose(archivo);                 //Para leer el archivo se va a utilizar otra forma
    }

    //LEER EL ARCHIVO Y EJECUTAR LAS INSTRUCCIONES
    std::ifstream file(ruta.c_str());
    while (getline(file, linea)){

        //Vaciar el vector. Se va a reutilizar el del parametro.
        parametros.clear();

        //Se debe de imprimir el comando y analizarlo para separar sus parametros 
        std::cout << linea << std::endl;
        analizar(linea, parametros);

        //Si es comentario, parametros viene vacio. Se debe de omitir.
        if(parametros.empty()){
            continue;
        }

        //Determinar el tipo de comando. La posicion 0 contiene el tipo de instruccion. Se pasa a minusculas el tipo.
        std::string &tipo = parametros[0];

        transform(tipo.begin(), tipo.end(), tipo.begin(),[](unsigned char c){
            return tolower(c);
        });

        if(tipo == "mkdisk"){
            mkdisk(parametros);
        }else if(tipo == "rmdisk"){
            rmdisk(parametros);
        }else if(tipo == "fdisk"){
            
        }else if(tipo == "mount"){
            
        }else if(tipo == "unmount"){
            
        }else if(tipo == "mkfs"){
            
        }else if(tipo == "login"){
            
        }else if(tipo == "logout"){
            
        }else if(tipo == "mkgrp"){
            
        }else if(tipo == "rmgrp"){
            
        }else if(tipo == "mkusr"){
            
        }else if(tipo == "rmusr"){
            
        }else if(tipo == "mkfile"){
            
        }else if(tipo == "cat"){
            
        }else if(tipo == "remove"){
            
        }else if(tipo == "edit"){
            
        }else if(tipo == "rename"){
            
        }else if(tipo == "mkdir"){
            
        }else if(tipo == "copy"){
            
        }else if(tipo == "move"){
            
        }else if(tipo == "find"){
            
        }else if(tipo == "chown"){
            
        }else if(tipo == "chgrp"){
            
        }else if(tipo == "chmod"){
            
        }else if(tipo == "pause"){
            
        }else if(tipo == "recovery"){
            
        }else if(tipo == "loss"){
            
        }else if(tipo == "rep"){
            
        }else{
            std::cout << "ERROR: El comando ingresado no existe." << std::endl;
        }        

        std::cout << std::endl;
    }

}
