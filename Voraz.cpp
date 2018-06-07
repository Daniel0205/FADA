/* 
 * File:   proyecto_FADA.cpp
 * Author: jem pool suarez
 *
 * Created on 28 de mayo de 2018, 03:50 PM
 */

#include <vector>
#include <cstdlib>
#include <iostream>
#include <cstdio>
#include <ios>
#include <math.h>

using namespace std;


//Funcion que determina si un ataque es factible
//Ademas, si el ataque es factible lo almacena en los objetivos seleccionados
//Tambien almacena en que intervalo [a,b] debe modificarse la trinchera 
bool ataque_Factible(vector<int> trinchera, vector<int> ataque,
        vector<int> &objetivos, int *a, int *b) {

    int libre = trinchera.size();
    bool factible = false;

    while (libre) {
        if (ataque[0] >= trinchera[libre - 2] && ataque[1] <= trinchera[libre - 1]) {
            *a = libre - 2;
            *b = libre - 1;
            objetivos.push_back(ataque[0]);
            objetivos.push_back(ataque[1]);
            factible = true;
        }
        libre = libre - 2;
    }

    return factible;
}


//Funcion que reseva un intervalo de la trinchera a un ataque
//esto se hace para que nuevos ataques no se solapen con este intervalo
void reservar_intervalo(vector<int> &trinchera, vector<int> ataque,
        int *a, int *b) {
    //Si coinciden en el extremo izquierdo
    if (ataque[0] == trinchera[*a] && ataque[1] != trinchera[*b])
        trinchera[*a] = ataque[1];
        //Si coinciden en el extremo derecho
    else if (ataque[1] == trinchera[*b] && ataque[0] != trinchera[*a])
        trinchera[*b] = ataque[0];
        //Si coinciden en ambos extremos
    else if (ataque[0] == trinchera[*a] && ataque[1] == trinchera[*b]) {
        trinchera.erase(trinchera.begin() + *a);
        trinchera.erase(trinchera.begin() + *a);
    }//Si no coinciden en ningun extremo
    else {
        trinchera.insert(trinchera.begin() + *b, ataque[1]);
        trinchera.insert(trinchera.begin() + *b, ataque[0]);
    }
}


//Funcion MERGE-SORT modificada para ordenar dos vectores
void Merge(vector<int> &A, vector<int> &B,int p,int q,int r) {
    int n1=q-p+1;
    int n2=r-q;
    int L1[n1+1], L2[n1+1];
    int R1[n2+1], R2[n2+1];
    for(int i=0; i<n1; i++){ 
        L1[i]=A[p+i];
        L2[i]=B[p+i];
    }
    for(int j=0; j<n2; j++){ 
        R1[j]=A[q+1+j];
        R2[j]=B[q+1+j];
    }
    int i=0;
    int j=0;
    int n=0;
    while(i!=n1 && j!=n2) {
        if(L1[i]>R1[j]) {
            A[p+n]=R1[j];
            B[p+n]=R2[j];
            j++;
        } else {
            A[p+n]=L1[i];
            B[p+n]=L2[i];
            i++;
        }
        n++;
    }
    while(j!=n2) {
        A[p+n]=R1[j];
        B[p+n]=R2[j];
        j++;
        n++;
    }
    while(i!=n1) {
        A[p+n]=L1[i];
        B[p+n]=L2[i];
        i++;
        n++;
    }
}
void MergeSort(vector<int> &A, vector<int> &B,int p,int r) {
    if(r>p) {
        int q;
        q=(p+r)/2;
        MergeSort(A,B,p,q);
        MergeSort(A,B,q+1,r);
        Merge(A,B,p,q,r);
    }
}


int main(int argc, char** argv) {

    //Declaracion de variables
    freopen("input", "r", stdin);
    string str_buffer;
    int N, M, areaAtaque=0;
    vector<int> trinchera;//Ancho representado por intervalo(s)
    int a, b; //Variables auxiliares del intervalo a eliminar en la trinchera   
    vector<int> objetivos; //Objetivos seleccionados
    vector<int> dupla_1, dupla_2, buffer;
    buffer.push_back(0);
    buffer.push_back(0);

    //Lectura de datos desde archivo de texto (nombre: input)
    cin >> str_buffer;
    N = atoi(str_buffer.c_str()); //Largo
    cin >> str_buffer;
    M = atoi(str_buffer.c_str()); //Ancho
    trinchera.push_back(0);
    trinchera.push_back(N);

    while (cin >> str_buffer) {
        dupla_1.push_back(atoi(str_buffer.c_str())); //Posicion en x  
        cin >> str_buffer;
        dupla_2.push_back(atoi(str_buffer.c_str())); //Radio
    }
    
    
        //Ordenamiento de datos con INSERTION-SORT
        int length = dupla_2.size();
        MergeSort(dupla_2,dupla_1, 0, length-1);

/*        
    //----------------------------------------------------------------
    cout << "Ataque factible en [0," << N <<"] ?"<< endl;
    cout << "(posx,r)"<< endl;
    for(int i=0; i<length; i++){
        cout << "(" << dupla_1[i] << "," << dupla_2[i] << ")" << endl;
    }
    //----------------------------------------------------------------
*/   
    //Conversion de coordenadas (posicion, radio) a [limite izq., limite der.]
    for (int i = 0; i < length; i++) {
        int radio = dupla_1[i];   
        dupla_1[i] = radio - dupla_2[i];
        dupla_2[i] = radio + dupla_2[i];
    }
    
    //Lanzamiento de ataques, empezando por los de mayor area
    int cont = dupla_1.size();
    while (cont--) {

        buffer[0] = dupla_1[cont];
        buffer[1] = dupla_2[cont];

        //Aqui se determina la factibilidad de los puntos de ataque
        if (ataque_Factible(trinchera, buffer, objetivos, &a, &b))
            reservar_intervalo(trinchera, buffer, &a, &b);

        dupla_1.erase(dupla_1.begin() + cont);
        dupla_2.erase(dupla_2.begin() + cont);
    }
/*    
    //IMPRIMIR-------------------------------------------------------    
    cout << endl << "Trinchera despues del ataque (intervalos)" << endl;
    for (int i = 0; i < trinchera.size(); i = i + 2) {
        cout << "[" << trinchera[i] << ", ";
        cout << trinchera[i + 1] << "] ";
    }

    cout <<  "\n\nobjetivos seleccionados (intervalos)" << endl;
    for (int i = 0; i < objetivos.size(); i = i + 2) {
        cout << "[" << objetivos[i] << ", ";
        cout << objetivos[i + 1] << "]" << endl;
    }
*/
    //Convertir los objetivos seleccionados a (posx,r)
    for (int i = 0; i < objetivos.size(); i = i + 2) {
        int radio = (objetivos[i+1]-objetivos[i])/2;
        int posx = objetivos[i]+radio;        
        objetivos[i] = posx;
        objetivos[i+1] = radio;
    }      
    
    cout << "objetivos seleccionados (posx,radio)" << endl;
    for (int i = 0; i < objetivos.size(); i = i + 2) 
        cout << "(" << objetivos[i] << ", " << objetivos[i + 1] << ")" << endl;

    //Mostrar el area total
    for (int i = 0; i < objetivos.size(); i = i + 2) 
        areaAtaque += objetivos[i+1]*objetivos[i+1]*M_PI;
    
    cout << "\nArea total de los objetivos seleccionados\n" << areaAtaque << endl;
    
    
    return 0;
}
