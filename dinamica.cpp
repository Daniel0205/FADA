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

void Merge(int* A,int* hola,int p,int q,int r) {
    int n1=q-p+1;
    int n2=r-q;
    int L[n1+1];
    int L1[n1+1];
    int R[n2+1];
    int R1[n2+1];
    for(int i=0; i<n1; i++){
		 L[i]=A[p+i];
		 L1[i]=hola[p+i];
	 }
    for(int j=0; j<n2; j++){
		 R[j]=A[q+1+j];
		 R1[j]=hola[q+1+j];		 
	 }
	 		for (int i = 0; i < tamano; i++){
			cout << A[i] << "-" << hola[i]	<<endl;		
		}
		cout<< "------------------" << endl;
	 
    int i=0;
    int j=0;
    int n=0;
    while(i!=n1 && j!=n2) {
        if(L[i]+L1[i]>R[j]+R1[j]) {
            A[p+n]=R[j];
            hola[p+n]=R1[j];
            j++;
        } else {
            A[p+n]=L[i];
            hola[p+n]=L1[i];
            i++;
        }
        n++;
    }
    while(j!=n2) {
        A[p+n]=R[j];
        hola[p+n]=L1[i];
        j++;
        n++;
    }
    while(i!=n1) {
        A[p+n]=L[i];
        hola[p+n]=L1[i];
        i++;
        n++;
    }
}
void MergeSort(int *A,int *B,int p,int r) {
    if(r>p) {
        int q;
        q=(p+r)/2;
        MergeSort(A,B,p,q);
        MergeSort(A,B,q+1,r);
        Merge(A,B,p,q,r);
    }
}


void ordenarVectores(vector<int> *posicion,vector<int> *radio){
		int *a=new int[(int)posicion->size()];
		int *b=new int[(int)posicion->size()];
		tamano=(int)posicion->size();
		
		for (int i = tamano-1; i >=0 ; i--){
			a[i]=posicion[0][i];
			b[i]=radio[0][i];
			posicion->pop_back();
			radio->pop_back();
		}

		
		
		MergeSort(a,b,0,tamano-1);

		cout<< tamano <<endl;
		
		for (int i = 0; i <tamano ; i++){
			//cout << i << endl;
			posicion->push_back(a[i]);
			radio->push_back(b[i]);
		}
		
			
	
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
	/////////////////////////////////////////////////////////////////
	ordenarVectores(&posicion,&radio);
	for (int i = 0; i < (int)posicion.size(); i++){
		printf("%d-%d\n",posicion[i],radio[i]);		
	}
	
	
	
	//Se Llena las matrices creadas
	llenarMatriz(largo,posicion,radio,matrizDinamica,binAtaques);

		
	// Se imprime el valor de la solucion optima
	printf("El Mayor area es de: %f\n",matrizDinamica[largo][posicion.size()]);
	
	//se imprime la solucion
	printf("Lista de ataques:\n");
	imprimirSolucion(posicion, radio,largo,binAtaques);
	
	/*
	for (int i = 0; i <= largo; i++){
		for (int j = 0; j <=(int)posicion.size(); j++){
			cout << binAtaques[i][j] << "-";
		}
		cout << endl;
		
		
	}*/
	
	
}
