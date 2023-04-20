#include <iostream>
#include<fstream>
using namespace std;

//1.
char** crear_arreglo(char* linea); //Recibe una cadena de caracteres y crea un arreglo en donde cada posicion es delimitada por las comas
char* crear_cadena(char** curso); //Recibe un arreglo y crea una cadena de caracteres
char** buscar_codigo(char* codCurso); /*Recibe el codigo del curso y cuando lo encuentra se usa la funcion crear_arreglo para retornar el
                                         arreglo con la informacion del curso*/
void escribir_matricula(char** curso); //Con la funcion crear_cadena escribe su lo que retorna es funcion en el archivo matricula
bool son_num(char* codCurso); //Verifica si el codigo del curso son solo numeros
//2.
char*** creacion_horario(); /* Creacion del horario*/
void escribir_horario(); // Registra la informacion del horario en horario.txt
//3.
char recomendar(); /* calcula las HTI: HTI = (NC * 3) - HTD. Y de acuerdo con horario donde encuentre que no hay una materia
                      recomendara poner el horario de estudio */
char invertir(); /* se usara para invertir el codCurso para asignarselo a su hora de estudio para poder registrarlo en horario.txt
                    con escribir_horario();*/

int main(){
    int opcion;
    cout << "Escibe el numero de lo que deseas hacer: " << endl;
    cout << " 1 --> Crear tu matricula" << endl;
    cout << " 2 --> Hacer tu horario" << endl;
    cout << " 3 --> Recomendacion de horas de estudio" << endl;
    cout << " Cualquier otra cosa --> Salir" << endl;
    cin >> opcion;
    while(true){
        switch(opcion){
        case 1:
            char codCurso[7];
            cout << "Digite el codigo del curso que desea matricular: ";
            cin >> codCurso;
            char** curso=buscar_codigo(codCurso);
            if(son_num(codCurso)){
                if(curso!=NULL){
                    escribir_matricula(curso);
                }
                else{
                    cout<<"El codigo ingresado no pertenece a ningun curso"<<endl;
                }
            }
            else{
                cout<<"El codigo debe ser solo numeros"<<endl;
            }
        case 2:
            //HORARIO
        case 3:
            //Recomendacion
        default:
            break;
        }
    }

    return 0;
}
char** crear_arreglo(char* linea){
    char** curso = new char*[4];
    for (int i = 0; i < 4; i++) {
        curso[i] = new char[20]; // inicializar cada puntero interno con un arreglo de 20 caracteres
    }
    int i = 0;
    int j = 0;
    int k = 0;
    while(linea[j]!='\0'){
        if(linea[j]==','){
            curso[i][k]='\0';
            i++;
            k=0;
        }
        else{
            curso[i][k]=linea[j];
            k++;
        }
        j++;
    }
    curso[i][k] = '\0'; // Agregar terminador nulo al final del último elemento del arreglo.
    return curso;
}

char* crear_cadena(char** curso){
    int i = 0;
    int j = 0;
    int k = 0;
    for (i = 0; i < 4; i++) {
        while(curso[i][k]!='\0'){
            linea[j]=curso[i][k];
            j++;
            k++;
        }
        linea[j]=',';
        j++;
        k=0;
    }
    linea[j-1]='\0'; // terminar la cadena con un carácter nulo y quitar la última coma
    return linea;
}

char**buscar_codigo(char* codCurso){
        ifstream lectura;

        lectura.open("cursos.txt");
        if(!lectura.is_open()){
            cout << "No se pudo abrir el archivo." << endl;
            return NULL; //Retornamos NULL si no se encontró el código solicitado
        }
        else{
            char* linea = new char[70]; //A la variable linea se le asignará memoria suficiente para almacenar 70 caracteres consecutivos.
            int contador=0;
            char* curso[4]; //Reservamos memoria para el arreglo de 4 cadenas de caracteres
            while(lectura.getline(linea,70)){
                for(int i=0;i<7;i++){
                    if(linea[i]==codCurso[i]){ //verifica si el codigo que se esta buscando esta en alguna linea
                        contador++;         // El contador sirve para saber si el codigo del cuerso de una linea es igual al solicitado
                    }
                }
                if(contador==7){
                    char** curso= crear_arreglo(linea); //Llamamos a la función crear_arreglo para obtener las 4 cadenas de caracteres en un arreglo
                    delete[] linea; //Liberamos la memoria asignada a la variable linea
                    return curso;
                }
                contador=0;
            }
            delete[] linea; //Liberamos la memoria asignada a la variable linea
            return NULL; //Retornamos NULL si no se encontró el código solicitado
        }
        lectura.close();
}

void escribir_matricula(char** curso){
        char* cadena = crear_cadena(curso);
        ofstream escribir("matricula.txt", ios::app); // abrir en modo de "añadir"
        if (!escribir.is_open()) {
            cout << "No se pudo abrir el archivo\n";
        }
        else {
            escribir << linea<<'\n';
            escribir.close(); // cerrar el archivo
        }
}

bool son_num(char* codCurso){
        bool es_numero = false;
        for(int i=0;i<7;i++){
            if(codCurso[i]<58 && codCurso[i]>47){
                es_numero=true;
            }
            else{
                return false;
            }
        }
        return true;
}

char*** creacion_horario(){
        char*** horario = new char**[7]; // Se reseva memoria para un arreglo de 7 punteros a un arreglo bidimencional
        char dias[7]={'L','M','W','J','V','S','D'}; //Arreglo con los dias de la semana

        for(int i=0;i<7;i++){
            horario[i] = new char*[24]; // Se reserva memoria para un arreglo de 24 punteros que apuntan a un arreglo
            for(int j=0;j<24;j++){
                horario[i][j] = new char[3]; //Crear un arreglo de caracteres de 3 elementos para cada hora del día
                horario[i][j][0]=0;
                horario[i][j][1]=j;
                horario[i][j][2]=dias[i];
            }
        }
        return horario;
}




















