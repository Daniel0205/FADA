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
	
	ifstream archivo("archivo.txt");
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


//Funcion main
int main(){
	int largo,ancho;
	vector<int> posicion;
	vector<int> radio;
	vector<int> posicion1;
	vector<int> radio1;
	
	//Se leen el archivo y se le asignan los datos a los vectores
	leerArchivo(&largo,&ancho,&posicion, &radio);
	
	//cout << maxArea(posicion,radio,0,0)<< endl;
	elementos(posicion,radio,&posicion1,&radio1);
	
	
	for (int i = 0; i < (int)posicion1.size(); i++){
		printf("indice %d: %d-%d\n",i,posicion1[i],radio1[i]);	
	}
	

	
}
