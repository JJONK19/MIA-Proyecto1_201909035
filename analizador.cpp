#include "analizador.h"

void ejecutar(std::string &cadena, usuario &sesion, std::vector<disco> &discos){
    //VARIABLES
    std::vector<std::string> parametros; 

    //ANALIZAR LA CADENA
    analizar(cadena, parametros);

    //IGNORAR COMENTARIOS 
    if(parametros.empty()){
       return; 
    }

    //EJECUTAR INSTRUCCION
    std::string &tipo = parametros[0];

    std::transform(tipo.begin(), tipo.end(), tipo.begin(),[](unsigned char c){
        return tolower(c);
    });

    if(tipo == "mkdisk"){
        mkdisk(parametros);
    }else if(tipo == "rmdisk"){
        rmdisk(parametros);
    }else if(tipo == "fdisk"){
        fdisk(parametros);
    }else if(tipo == "mount"){
        mount(parametros, discos);
    }else if(tipo == "unmount"){
        unmount(parametros, discos);
    }else if(tipo == "mkfs"){
        mkfs(parametros, discos);
    }else if(tipo == "login"){
        login(parametros, discos, sesion);
    }else if(tipo == "logout"){
        logout(sesion);
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
        rep(parametros, discos);
    }else if(tipo == "execute"){
        execute(parametros, sesion, discos);
    }else{
        std::cout << "ERROR: El comando ingresado no existe." << std::endl;
    }

}