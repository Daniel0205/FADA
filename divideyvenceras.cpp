#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using namespace std;


//definicion manual de constante pi
float pi=3.14159265359;

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


int maxArea(vector<int> posicion,vector<int> radio,int elemento,int posicionDis){

	if (elemento==(int)posicion.size() )return 0;
	
	if (posicion[elemento]-radio[elemento]<posicionDis ){
		return maxArea(posicion,radio,elemento+1,posicionDis);
	}
	else {
		 return max(maxArea(posicion,radio,elemento+1,posicionDis),maxArea(posicion,radio,elemento+1,posicion[elemento]+radio[elemento])+radio[elemento]);
	 }	
}

void elementos(vector<int> posicion,vector<int> radio,vector<int> *posicion1,vector<int> *radio1){
	int posicionDis=0,aux;

	for (int i = 0; i <(int)posicion.size() -1; i++){

		if(posicion[i]-radio[i]>=posicionDis){

			if(maxArea(posicion,radio,i+1,posicionDis)<=(maxArea(posicion,radio,i+1,posicion[i]+radio[i])+radio[i])){
				
				posicion1->push_back(posicion[i]);
				radio1->push_back(radio[i]);
				posicionDis=posicion[i]+radio[i];			
			}
		}
		aux=i;
	}
	aux++;
	
	if (posicion[aux]-radio[aux]>=posicionDis){	
				posicion1->push_back(posicion[aux]);
				radio1->push_back(radio[aux]);
				posicionDis=posicion[aux]+radio[aux];
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


//Funcion main
int main(){
	int largo,ancho;
	vector<int> posicion;
	vector<int> radio;
	vector<int> posicion1;
	vector<int> radio1;
	
	//Se leen el archivo y se le asignan los datos a los vectores
	leerArchivo(&largo,&ancho,&posicion, &radio);
	
	sort(posicion,radio);	

	
	//cout << maxArea(posicion,radio,0,0)<< endl;
	elementos(posicion,radio,&posicion1,&radio1);
	
	
	for (int i = 0; i < (int)posicion1.size(); i++){
		printf("indice %d: %d-%d\n",i,posicion1[i],radio1[i]);	
	}
	

	
}
