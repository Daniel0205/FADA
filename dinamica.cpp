#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;


//definicion manual de constante pi
float pi=3.14159265359;

int tamano;

//Funcion encargada de leer el archivo de entrada y asignar cada valor 
//al vector posicion y radio
//complejidad de funcion O(N) con N=cantidad de ataques
void leerArchivo(int *largo,int *ancho, vector<int> *posicion, vector<int> *radio){
	int aux;
	
	ifstream archivo("archivo1.txt");
	archivo >> *largo;
	archivo >> *ancho;	
	
	while(!archivo.eof()){
		archivo >> aux;
		posicion->push_back(aux);	
		
		archivo >> aux;
		radio->push_back(aux);
		
	}
	archivo.close();
	radio->erase(radio->begin()+radio->size()-1);
	posicion->erase(posicion->begin()+posicion->size()-1);	

}


//Funcion encargada de llenar la matriz de costos y matriz auxiliar 
//simultaneamente, deacuerdo a la funcion definida en el informe
//complejidad de funcion O(nxN) n=largo del campo; N=cantidad de ataques
void llenarMatriz(int largo,vector<int> posicion,vector<int> radio,float **matrizDinamica,bool ** binAtaques){
	for (int i = 0; i <= (int)posicion.size(); i++){
		int inicio=posicion[i-1]-radio[i-1],final=posicion[i-1]+radio[i-1];		
		
		for (int j = largo; j >=0; j--){
			
			if (i==0){
				matrizDinamica[j][i]=0;
				binAtaques[j][i]=false;
			}
			else{
				if (j>=final){
					float area=pow(radio[i-1],2)*pi;
					float siVa=matrizDinamica[inicio][i-1]+area;
					matrizDinamica[j][i]=max(matrizDinamica[j][i-1],siVa);
					
					if (matrizDinamica[j][i]==siVa)binAtaques[j][i]=true;
					else binAtaques[j][i]=false;
				}
				if (j<final){
					matrizDinamica[j][i]=matrizDinamica[j][i-1];
					binAtaques[j][i]=false;
				}
			}		
		}		
	}	
}


void mergeSort(vector<int>&leftPos, vector<int>&rightPos,vector<int>&leftRad, vector<int>& rightRad, vector<int>& pos,vector<int>& rad)
{
    int nL = leftPos.size();
    int nR = rightPos.size();
    int i = 0, j = 0, k = 0;
	
    while (j < nL && k < nR) 
    {	
        if (leftPos[j]+leftRad[i] < rightPos[k]+rightRad[i]) {
            pos[i] = leftPos[j];
            rad[i] =leftRad[j];
            j++;
        }
        else {
            pos[i] = rightPos[k];
            rad[i] = rightRad[k];
            k++;
        }
        i++;
    }
    
	
	
    while (j < nL) {
        pos[i] = leftPos[j];
        rad[i] = leftRad[j];
        j++; i++;
    }
    while (k < nR) {
        pos[i] = rightPos[k];
        rad[i] = rightRad[k];
        k++; i++;
    }

}


void sort(vector<int> & pos,vector<int>& rad) {
    if (pos.size() <= 1) return;

    int mid = pos.size() / 2;
    vector<int> leftPos;
    vector<int> rightPos;
    vector<int> leftRad;
    vector<int> rightRad;
    

    

    for (int j = 0; j < mid;j++){
        leftPos.push_back(pos[j]);
        leftRad.push_back(rad[j]);
	}
    for (int j = 0; j < (int)(pos.size()) - mid; j++){
        rightPos.push_back(pos[mid + j]);
        rightRad.push_back(rad[mid+j]);
	}

	
	
    sort(leftPos,leftRad);
    sort(rightPos,rightRad);
    mergeSort(leftPos, rightPos,leftRad,rightRad, pos,rad);
}


//Funcion que imprime la solucion en base a una matriz auxiliar partiendo desde la base
//inferior derecha y siguiendo asi hasta llegar a la primera columna
void imprimirSolucion(vector<int> posicion,vector<int> radio,int largo,bool **binAtaques){
	int aux=largo;
	for (int i = posicion.size() ; i > 0 ; i--){		
		if(binAtaques[aux][i]){			
			printf("-Centro: %d  -Radio: %d\n",posicion[i-1],radio[i-1]);
			aux=posicion[i-1]-radio[i-1];
		}

	}
}

//Funcion main
int main(){
	int largo,ancho;
	vector<int> posicion;
	vector<int> radio;
	
	
	//Se leen el archivo y se le asignan los datos a los vectores
	leerArchivo(&largo,&ancho,&posicion, &radio);
	
	//Creacion de matriz de costos y matriz auxiliar de forma dinamica
	float ** matrizDinamica= new float *[largo+1];
	bool ** binAtaques=new bool *[largo+1];

	for (int i = 0; i <= largo; i++){
		matrizDinamica[i]=new float [(int)posicion.size()+1];
		binAtaques[i]=new bool [(int)posicion.size()+1];
	}

	sort(posicion,radio);	
	
	//Se Llena las matrices creadas
	llenarMatriz(largo,posicion,radio,matrizDinamica,binAtaques);

		
	// Se imprime el valor de la solucion optima
	printf("El Mayor area es de: %f\n",matrizDinamica[largo][posicion.size()]);
	
	//se imprime la solucion
	printf("Lista de ataques:\n");
	imprimirSolucion(posicion, radio,largo,binAtaques);
	
	
}
