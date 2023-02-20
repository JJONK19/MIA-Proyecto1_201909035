#include "rep.h"

void rep(std::vector<std::string> &parametros, std::vector<disco> &discos){
    //VARIABLES
    bool paramFlag = true;                     //Indica si se cumplen con los parametros del comando
    bool required = true;                      //Indica si vienen los parametros obligatorios
    std::string ruta = "";                     //Atributo path
    std::string nombre = "";                   //Atributo name
    std::string id = "";                       //Atributo ID
    std::string rutaS = "";                    //Atributo ruta 
    std::string diskName;                      //Nombre del disco sin los numeros del ID
    int posDisco = -1;                         //Posicion del disco en la lista
    int posParticion = -1;                     //Posicion de la particion dentro del vector del disco

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
        }else if(tag == "name"){
            nombre = value;
        }else if(tag == "id"){
            id = value;
        }else if(tag == "ruta"){
            rutaS = value;
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
    if(nombre == "" || ruta == "" || id == ""){
        required = false;
    }

    if(!required){
        std::cout << "ERROR: La instrucción rep carece de todos los parametros obligatorios." << std::endl;
    }

    //REMOVER LOS NUMEROS DEL ID
    int posicion = 0;
    for(int i = 0; i< id.length(); i++){
        if(isdigit(id[i])){
            posicion++;
        }else{
            break;
        }
    }
    diskName = id.substr(posicion, id.length()-1);

    //BUSCAR SI EXISTE EL DISCO EN LA LISTA
    for(int i = 0; i < discos.size(); i++){
        disco temp = discos[i];
        if(temp.nombre == diskName){
            posDisco = i;
            break;
        }
    }

    if(posDisco == -1){
        std::cout << "ERROR: El disco no existe." << std::endl;
        return;
    }

    //BUSCAR LA PARTICION DENTRO DEL DISCO MONTADO
    disco &tempD = discos[posDisco];
    for(int i = 0; i < tempD.particiones.size(); i++){
        montada temp = tempD.particiones[i];
        if(temp.id == id){
            posParticion = i;
            break;
        }
    }

    if(posParticion == -1){
        std::cout << "ERROR: No existe una partción montada con ese ID." << std::endl;
        return;
    }

    //Verificar que existe la carpeta del reporte. Crearla si no.
    try {
        std::filesystem::create_directories(ruta);       //Crea los directorios
        std::filesystem::remove(ruta);                   //Borra el dir con el nombre del disco
    }
    catch (...) { 
        
    }
    //SEPARAR TIPO DE REPORTE Y EJECUTARLA
    transform(nombre.begin(), nombre.end(), nombre.begin(),[](unsigned char c){
        return tolower(c);
    });

    if(nombre == "mbr"){
        mbr(discos, posDisco, ruta);
    }else if(nombre == "disk"){
        disk(discos, posDisco, ruta);
    }else if(nombre == "inode"){
        
    }else if(nombre == "journaling"){
        
    }else if(nombre == "block"){
        
    }else if(nombre == "bm_inode"){
        
    }else if(nombre == "bm_block"){
        
    }else if(nombre == "tree"){
        
    }else if(nombre == "sb"){
        
    }else if(nombre == "file"){
        
    }else if(nombre == "ls"){
        
    }else{
        std::cout << "ERROR: Tipo de reporte invalido." << std::endl;
    }
}

void mbr(std::vector<disco> &discos, int posDisco, std::string &ruta){
    //VARIABLES
    std::string codigo;             //Contenedor del codigo del dot
    disco &uso = discos[posDisco];  //Disco en uso
    FILE *archivo;                  //Para leer el archivo
    MBR mbr;                        //Para leer el mbr
    int posExtendida;               //Posicion para leer la extendida
    EBR ebr;                        //Para leer los ebr de las particiones logicas          
    std::string comando;            //Instruccion a mandar a la consola para generar el comando

    //VERIFICAR QUE EXISTA EL ARCHIVO
    archivo = fopen(uso.ruta.c_str(), "r+b");
    if(archivo == NULL){
        std::cout << "ERROR: No se encontro el disco." << std::endl;
        return;
    }

    //LEER EL MBR
    fseek(archivo, 0,SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, archivo);

    //ESCRIBIR EL DOT
    codigo = "digraph mbr {node [shape=plaintext] struct1 [label= <<TABLE BORDER='2' CELLBORDER='0' CELLSPACING='0'>";
    
    codigo.append("<TR>");
    codigo.append("<TD BGCOLOR='#cd6155' WIDTH='300'>REPORTE DE MBR</TD>");
    codigo.append("<TD WIDTH='300' BGCOLOR='#cd6155'></TD>");
    codigo.append("</TR>");

    codigo.append("<TR>");
    codigo.append("<TD>Tamaño</TD>");
    codigo.append("<TD>");
    codigo.append(std::to_string(mbr.mbr_tamano));
    codigo.append("</TD>");
    codigo.append("</TR>");       

    codigo.append("<TR>");
    codigo.append("<TD>Fit</TD>");
    codigo.append("<TD>");
    codigo.push_back(mbr.dsk_fit);
    codigo.append("</TD>");
    codigo.append("</TR>");

    codigo.append("<TR>");
    codigo.append("<TD>DSK Signature</TD>");
    codigo.append("<TD>");
    codigo.append(std::to_string(mbr.mbr_dsk_signature));
    codigo.append("</TD>");
    codigo.append("</TR>");

    codigo.append("<TR>");
    codigo.append("<TD>Fecha Creacion</TD>");
    codigo.append("<TD>");
    codigo.append(asctime(gmtime(&mbr.mbr_fecha_creacion)));
    codigo.append("</TD>");
    codigo.append("</TR>");   

    //Particiones    
    for(int i = 0; i < 4; i++){
        if(mbr.mbr_partition[i].part_name[0] != '\0'){
            if(mbr.mbr_partition[i].part_type == 'p'){
                codigo.append("<TR>");
                codigo.append("<TD BGCOLOR='#e67e22' WIDTH='300'>PARTICION</TD>");
                codigo.append("<TD WIDTH='300' BGCOLOR='#e67e22'></TD>");
                codigo.append("</TR>");
        
                codigo.append("<TR>");
                codigo.append("<TD>Nombre</TD>");
                codigo.append("<TD>");
                codigo.append(mbr.mbr_partition[i].part_name);
                codigo.append("</TD>");
                codigo.append("</TR>");

                codigo.append("<TR>");
                codigo.append("<TD>Tamaño</TD>");
                codigo.append("<TD>");
                codigo.append(std::to_string(mbr.mbr_partition[i].part_s));
                codigo.append("</TD>");
                codigo.append("</TR>");

                codigo.append("<TR>");
                codigo.append("<TD>Fit</TD>");
                codigo.append("<TD>");
                codigo.push_back(mbr.mbr_partition[i].part_fit);
                codigo.append("</TD>");
                codigo.append("</TR>");

                codigo.append("<TR>");
                codigo.append("<TD>Inicio</TD>");
                codigo.append("<TD>");
                codigo.append(std::to_string(mbr.mbr_partition[i].part_start));
                codigo.append("</TD>");
                codigo.append("</TR>");
                
                codigo.append("<TR>");
                codigo.append("<TD>Status</TD>");
                codigo.append("<TD>");
                codigo.push_back(mbr.mbr_partition[i].part_status);
                codigo.append("</TD>");
                codigo.append("</TR>");

                codigo.append("<TR>");
                codigo.append("<TD>Tipo</TD>");
                codigo.append("<TD>");
                codigo.push_back(mbr.mbr_partition[i].part_type);
                codigo.append("</TD>");
                codigo.append("</TR>");
            }else{
                codigo.append("<TR>");
                codigo.append("<TD BGCOLOR='#e67e22' WIDTH='300'>PARTICION</TD>");
                codigo.append("<TD WIDTH='300' BGCOLOR='#e67e22'></TD>");
                codigo.append("</TR>");
        
                codigo.append("<TR>");
                codigo.append("<TD>Nombre</TD>");
                codigo.append("<TD>");
                codigo.append(mbr.mbr_partition[i].part_name);
                codigo.append("</TD>");
                codigo.append("</TR>");

                codigo.append("<TR>");
                codigo.append("<TD>Tamaño</TD>");
                codigo.append("<TD>");
                codigo.append(std::to_string(mbr.mbr_partition[i].part_s));
                codigo.append("</TD>");
                codigo.append("</TR>");

                codigo.append("<TR>");
                codigo.append("<TD>Fit</TD>");
                codigo.append("<TD>");
                codigo.push_back(mbr.mbr_partition[i].part_fit);
                codigo.append("</TD>");
                codigo.append("</TR>");

                codigo.append("<TR>");
                codigo.append("<TD>Inicio</TD>");
                codigo.append("<TD>");
                codigo.append(std::to_string(mbr.mbr_partition[i].part_start));
                codigo.append("</TD>");
                codigo.append("</TR>");
                
                codigo.append("<TR>");
                codigo.append("<TD>Status</TD>");
                codigo.append("<TD>");
                codigo.push_back(mbr.mbr_partition[i].part_status);
                codigo.append("</TD>");
                codigo.append("</TR>");

                codigo.append("<TR>");
                codigo.append("<TD>Tipo</TD>");
                codigo.append("<TD>");
                codigo.push_back(mbr.mbr_partition[i].part_type);
                codigo.append("</TD>");
                codigo.append("</TR>"); 

                //Recorrer Logicas
                posExtendida = mbr.mbr_partition[i].part_start; 
                fseek(archivo, posExtendida, SEEK_SET);
                fread(&ebr, sizeof(EBR), 1, archivo);
                bool continuar = true;
                while(continuar){
                    codigo.append("<TR>");
                    codigo.append("<TD BGCOLOR='#f1c40f' WIDTH='300'>PARTICION LOGICA</TD>");
                    codigo.append("<TD WIDTH='300' BGCOLOR='#f1c40f'></TD>");
                    codigo.append("</TR>");
            
                    codigo.append("<TR>");
                    codigo.append("<TD>Nombre</TD>");
                    codigo.append("<TD>");
                    codigo.append(ebr.part_name);
                    codigo.append("</TD>");
                    codigo.append("</TR>");

                    codigo.append("<TR>");
                    codigo.append("<TD>Tamaño</TD>");
                    codigo.append("<TD>");
                    codigo.append(std::to_string(ebr.part_s));
                    codigo.append("</TD>");
                    codigo.append("</TR>");

                    codigo.append("<TR>");
                    codigo.append("<TD>Fit</TD>");
                    codigo.append("<TD>");
                    codigo.push_back(ebr.part_fit);
                    codigo.append("</TD>");
                    codigo.append("</TR>");

                    codigo.append("<TR>");
                    codigo.append("<TD>Inicio</TD>");
                    codigo.append("<TD>");
                    codigo.append(std::to_string(ebr.part_start));
                    codigo.append("</TD>");
                    codigo.append("</TR>");
                    
                    codigo.append("<TR>");
                    codigo.append("<TD>Status</TD>");
                    codigo.append("<TD>");
                    codigo.push_back(ebr.part_status);
                    codigo.append("</TD>");
                    codigo.append("</TR>");

                    codigo.append("<TR>");
                    codigo.append("<TD>Next</TD>");
                    codigo.append("<TD>");
                    codigo.append(std::to_string(ebr.part_next));
                    codigo.append("</TD>");
                    codigo.append("</TR>");
                    
                    if(ebr.part_next == -1){
                        continuar = false;
                    }else{
                        posExtendida = ebr.part_next;
                        fseek(archivo, posExtendida, SEEK_SET);
                        fread(&ebr, sizeof(EBR), 1, archivo);
                    }
                }
            }
        }
    }   
    codigo.append("</TABLE>>];}");
    fclose(archivo);

    //GENERAR EL DOT
    std::ofstream outfile ("grafo.dot");
    outfile << codigo << std::endl;
    outfile.close();

    //EXTRAER EL TIPO DE FORMATO
    std::string::size_type pos = ruta.rfind('.', ruta.length());
    std::string extension = ruta.substr(pos + 1, ruta.length() - 1);

    //CREAR EL COMANDO DOT
    comando = "dot -T";
    comando.append(extension);
    comando.append(" grafo.dot -o");
    comando.append("'");
    comando.append(ruta);
    comando.append("'");

    //GENERAR EL GRAFO
    system(comando.c_str());
    std::cout << "MENSAJE: Reporte MBR creado correctamente." << std::endl;
}

void disk(std::vector<disco> &discos, int posDisco, std::string &ruta){
    //VARIABLES
    std::string codigo;             //Contenedor del codigo del dot
    disco &uso = discos[posDisco];   //Disco en uso
    FILE *archivo;                  //Para leer el archivo
    MBR mbr;                        //Para leer el mbr
    int posExtendida;               //Posicion para leer la extendida
    EBR ebr;                        //Para leer los ebr de las particiones logicas          
    std::string comando;            //Instruccion a mandar a la consola para generar el comando
    float size;                     //Tamaño del disco
    int finExtendida = -1;
    int posEBR = -1;
    std::vector<position> posiciones;
    int porcentaje;                  //Maneja los porcentajes a escribir en el reporte

    //VERIFICAR QUE EXISTA EL ARCHIVO
    archivo = fopen(uso.ruta.c_str(), "r+b");
    if(archivo == NULL){
        std::cout << "ERROR: No se encontro el disco." << std::endl;
        return;
    }

    //LEER EL MBR
    fseek(archivo, 0,SEEK_SET);
    fread(&mbr, sizeof(MBR), 1, archivo);

    //BUSCAR LA EXTENDIDA 
    for(int i = 0; i < 4; i++){
        if(mbr.mbr_partition[i].part_type == 'e'){
            posEBR = mbr.mbr_partition[i].part_start;
            finExtendida = mbr.mbr_partition[i].part_start + mbr.mbr_partition[i].part_s; 
            break;
        }
    }

    //ESCRIBIR EL DOT PARA PARTICIONES PRIMARIAS / EXTENDIDA
    codigo = "digraph mbr {node [shape=plaintext] struct1 [label= <<TABLE BORDER='2' CELLBORDER='1' CELLSPACING='0'>";
    size = (float)mbr.mbr_tamano;

    codigo.append("<TR>");
    codigo.append("<TD ROWSPAN='3' BGCOLOR='#A10035' HEIGHT='100'>MBR</TD>");

    //Crear un lista de las particiones  
    for(int i = 0; i < 4; i++){
        if(mbr.mbr_partition[i].part_name[0] != '\0'){
            position temp;
            temp.inicio = mbr.mbr_partition[i].part_start;
            temp.fin = mbr.mbr_partition[i].part_start + mbr.mbr_partition[i].part_s - 1;
            temp.nombre = mbr.mbr_partition[i].part_name;
            temp.tipo = mbr.mbr_partition[i].part_type;
            temp.tamaño = mbr.mbr_partition[i].part_s;
            posiciones.push_back(temp);
        }
    }

    if(posiciones.size() != 0){
        std::sort(posiciones.begin(), posiciones.end());
    }

    //Añadir el codigo de las particiones y los espacios vacios
    if(posiciones.size() == 0){
        codigo.append("<TD ROWSPAN='3' WIDTH='100' BGCOLOR='#3FA796'>LIBRE<BR/>");
        porcentaje = round((size / size) * 100);
        codigo.append(std::to_string(porcentaje));
        codigo.append("% del disco");
        codigo.append("</TD>");
    }else{
        for(int i = 0; i < posiciones.size(); i++){
            position &x = posiciones[i];
            int free = 0;
            if(i == 0 && i != (posiciones.size()-1)){
                free = x.inicio - EndMBR;
                if(free > 0){
                    codigo.append("<TD ROWSPAN='3' WIDTH='100' BGCOLOR='#3FA796'>LIBRE<BR/>");
                    porcentaje = round((free / size) * 100);
                    codigo.append(std::to_string(porcentaje));
                    codigo.append("% del disco");
                    codigo.append("</TD>");
                }

                //Añadir la particion
                if(x.tipo == 'p'){
                    codigo.append("<TD ROWSPAN='3' BGCOLOR='#355764' WIDTH='100'>PRIMARIA<BR/>");
                    codigo.append(x.nombre);
                    codigo.append("<br/>");
                    porcentaje = round((x.tamaño / size) * 100);
                    codigo.append(std::to_string(porcentaje));
                    codigo.append("% del disco");
                    codigo.append("</TD>");
                    
                }else{
                    codigo.append("<TD COLSPAN ='50' BGCOLOR='#FFA500' WIDTH='100'>EXTENDIDA<BR/>");
                    codigo.append("</TD>");
                }

                //Espacio entre la primera particion y la siguiente
                position &y = posiciones[i + 1];
                free = y.inicio - (x.fin + 1);
                if(free > 0){
                    codigo.append("<TD ROWSPAN='3' WIDTH='100' BGCOLOR='#3FA796'>LIBRE<BR/>");
                    porcentaje = round((free / size) * 100);
                    codigo.append(std::to_string(porcentaje));
                    codigo.append("% del disco");
                    codigo.append("</TD>");
                }
            }else if(i == 0 && i == (posiciones.size()-1)){
                //Espacio entre el inicio y la primera particion
                free = x.inicio - EndMBR;
                if(free > 0){
                    codigo.append("<TD ROWSPAN='3' WIDTH='100' BGCOLOR='#3FA796'>LIBRE<BR/>");
                    porcentaje = round((free / size) * 100);
                    codigo.append(std::to_string(porcentaje));
                    codigo.append("% del disco");
                    codigo.append("</TD>");
                }

                //Añadir la particion
                if(x.tipo == 'p'){
                    codigo.append("<TD ROWSPAN='3' BGCOLOR='#355764' WIDTH='100'>PRIMARIA<BR/>");
                    codigo.append(x.nombre);
                    codigo.append("<br/>");
                    porcentaje = round((x.tamaño / size) * 100);
                    codigo.append(std::to_string(porcentaje));
                    codigo.append("% del disco");
                    codigo.append("</TD>");
                    
                }else{
                    codigo.append("<TD COLSPAN ='50' BGCOLOR='#FFA500' WIDTH='100'>EXTENDIDA<BR/>");
                    codigo.append("</TD>");
                }

                //Espacio entre la primera particion y el fin
                free = size - (x.fin + 1);
                if(free > 0){
                    codigo.append("<TD ROWSPAN='3' WIDTH='100' BGCOLOR='#3FA796'>LIBRE<BR/>");
                    porcentaje = round((free / size) * 100);
                    codigo.append(std::to_string(porcentaje));
                    codigo.append("% del disco");
                    codigo.append("</TD>");
                }
            }else if(i != (posiciones.size()-1)){
                //Añadir la particion
                if(x.tipo == 'p'){
                    codigo.append("<TD ROWSPAN='3' BGCOLOR='#355764' WIDTH='100'>PRIMARIA<BR/>");
                    codigo.append(x.nombre);
                    codigo.append("<br/>");
                    porcentaje = round((x.tamaño / size) * 100);
                    codigo.append(std::to_string(porcentaje));
                    codigo.append("% del disco");
                    codigo.append("</TD>");
                    
                }else{
                    codigo.append("<TD COLSPAN ='50' BGCOLOR='#FFA500' WIDTH='100'>EXTENDIDA<BR/>");
                    codigo.append("</TD>");
                }

                //Espacio entre la primera particion y la siguiente
                position &y = posiciones[i + 1];
                free = y.inicio - (x.fin + 1);
                if(free > 0){
                    codigo.append("<TD ROWSPAN='3' WIDTH='100' BGCOLOR='#3FA796'>LIBRE<BR/>");
                    porcentaje = round((free / size) * 100);
                    codigo.append(std::to_string(porcentaje));
                    codigo.append("% del disco");
                    codigo.append("</TD>");
                }
            }else{
                //Añadir la particion
                if(x.tipo == 'p'){
                    codigo.append("<TD ROWSPAN='3' BGCOLOR='#355764' WIDTH='100'>PRIMARIA<BR/>");
                    codigo.append(x.nombre);
                    codigo.append("<br/>");
                    porcentaje = round((x.tamaño / size) * 100);
                    codigo.append(std::to_string(porcentaje));
                    codigo.append("% del disco");
                    codigo.append("</TD>");
                    
                }else{
                    codigo.append("<TD COLSPAN ='50' BGCOLOR='#FFA500' WIDTH='100'>EXTENDIDA<BR/>");
                    codigo.append("</TD>");
                }

                //Espacio entre la primera particion y el fin
                free = size - (x.fin + 1);
                if(free > 0){
                    codigo.append("<TD ROWSPAN='3' WIDTH='100' BGCOLOR='#3FA796'>LIBRE<BR/>");
                    porcentaje = round((free / size) * 100);
                    codigo.append(std::to_string(porcentaje));
                    codigo.append("% del disco");
                    codigo.append("</TD>");
                }
            }
        }
    }
    codigo.append("</TR>");

    //AÑADIR EL CODIGO DE LAS PARTICIONES LOGICAS
    if(posEBR != -1){
        codigo.append("<TR>");
        fseek(archivo, posEBR, SEEK_SET);
        fread(&ebr, sizeof(EBR), 1, archivo);
        bool cabecera_visitada = false;                    //Indica si es la cabecera la revisada
        bool continuar = true;                            //Sirve para salir del while
        int free;
        while(continuar){
            //Revisar primero la cabecera 
            if(!cabecera_visitada){
                if(ebr.part_s == 0){
                    codigo.append("<TD  BGCOLOR='#1F4690' HEIGHT='100'>EBR</TD>");
                    if(ebr.part_next == -1){
                        free = finExtendida - ebr.part_start; 
                    }else{
                        free = ebr.part_next - ebr.part_start;
                    }

                    if(free > 0){
                        codigo.append("<TD ROWSPAN='3' WIDTH='100' BGCOLOR='#3FA796'>LIBRE<BR/>");
                        porcentaje = floor((free / size) * 100);
                        codigo.append(std::to_string(porcentaje));
                        codigo.append("% del disco");
                        codigo.append("</TD>");
                    }
                }else{
                    codigo.append("<TD  BGCOLOR='#1F4690' HEIGHT='100'>EBR</TD>");
                    codigo.append("<TD  BGCOLOR='#3A5BA0' WIDTH='100'>LOGICA<BR/>");
                    codigo.append(ebr.part_name);
                    codigo.append("<br/>");
                    porcentaje = floor((ebr.part_s / size)*100);
                    codigo.append(std::to_string(porcentaje));
                    codigo.append("% del disco");
                    codigo.append("</TD>");
                    if(ebr.part_next == -1){
                        free = finExtendida - (ebr.part_start + ebr.part_s); 
                    }else{
                        free = ebr.part_next - (ebr.part_start + ebr.part_s);
                    }

                    if(free > 0){
                        codigo.append("<TD ROWSPAN='3' WIDTH='100' BGCOLOR='#3FA796'>LIBRE<BR/>");
                        porcentaje = floor((free / size) * 100);
                        codigo.append(std::to_string(porcentaje));
                        codigo.append("% del disco");
                        codigo.append("</TD>");
                    }
                }

                cabecera_visitada = false;
                if(ebr.part_next == -1){
                    continuar = false;
                }else{
                    posEBR = ebr.part_next;
                    fseek(archivo, posEBR, SEEK_SET);
                    fread(&ebr, sizeof(EBR), 1, archivo);
                }
            }else{
                codigo.append("<TD  BGCOLOR='#1F4690' HEIGHT='100'>EBR</TD>");
                codigo.append("<TD  BGCOLOR='#3A5BA0' WIDTH='100'>LOGICA<BR/>");
                codigo.append(ebr.part_name);
                codigo.append("<br/>");
                porcentaje = floor((ebr.part_s / size)*100);
                codigo.append(std::to_string(porcentaje));
                codigo.append("% del disco");
                codigo.append("</TD>");
                if(ebr.part_next == -1){
                    free = finExtendida - (ebr.part_start + ebr.part_s); 
                }else{
                    free = ebr.part_next - (ebr.part_start + ebr.part_s);
                }

                if(free > 0){
                    codigo.append("<TD ROWSPAN='3' WIDTH='100' BGCOLOR='#3FA796'>LIBRE<BR/>");
                    porcentaje = floor((free / size) * 100);
                    codigo.append(std::to_string(porcentaje));
                    codigo.append("% del disco");
                    codigo.append("</TD>");
                }
                if(ebr.part_next == -1){
                    continuar = false;
                }else{
                    posEBR = ebr.part_next;
                    fseek(archivo, posEBR, SEEK_SET);
                    fread(&ebr, sizeof(EBR), 1, archivo);
                }
            }
        }
        codigo.append("</TR>");
    }
    codigo.append("</TABLE>>];}");
    fclose(archivo);

    //GENERAR EL DOT
    std::ofstream outfile ("grafo.dot");
    outfile << codigo << std::endl;
    outfile.close();

    //EXTRAER EL TIPO DE FORMATO
    std::string::size_type pos = ruta.rfind('.', ruta.length());
    std::string extension = ruta.substr(pos + 1, ruta.length() - 1);

    //CREAR EL COMANDO DOT
    comando = "dot -T";
    comando.append(extension);
    comando.append(" grafo.dot -o");
    comando.append("'");
    comando.append(ruta);
    comando.append("'");
    
    //GENERAR EL GRAFO
    system(comando.c_str());
    std::cout << "MENSAJE: Reporte DISKS creado correctamente." << std::endl;

}
