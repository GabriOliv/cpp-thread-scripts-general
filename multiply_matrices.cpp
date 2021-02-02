//Multiplicacao de Matrizes

//	Multiplicação
//	Threads em Vetor, Hard Threads, 2Threads per Core
//	Dinamica
#include <iostream>
#include <stdlib.h>		//Numero Random
#include <thread>		//Threads

//Preenchimento de Matriz
void m_fill(long int** M, int m){
	std::cout<<"\n\nPreenchimento --";
	//Preenchimento
	for(int i=0; i<m; i++){
		for(int j=0; j<m; j++){
			M[i][j] = rand()%10;
		}
	}
	std::cout<<"V\n";
}

//Saida de Matriz
void m_out(long int** M, int m){
	std::cout<<"\n\n";
	for(int i=0; i<m; i++){
		for(int j=0; j<m; j++)
			std::cout<<"  "<<M[i][j];
		std::cout<<"\n";
	}
}

//Multiplicacao de Matrix
//( A , B , C , inicio, final)
void m_multi(long int** A, long int** B, long int** M, int start, int endin, int m){
	std::cout<<"\n\nCalculo  :"<<(endin-start)*(endin-start)<<" elementos";
	//Calculo
	for(int i=start; i<endin; i++){
		for(int j=0; j<m; j++){
			M[i][j] = 0;
			for(int k=0; k<m; k++)
				M[i][j] = M[i][j] + (A[i][k] * B[k][j]);
		}
	}

	std::cout<<"\nComplete :"<<(endin-start)*(endin-start)<<" elementos\n";
}



int main(){
	//Dimensoes A[m,m] x B[m,m] = C[m,m]
	int m = 1000;

	//A,B,C
	long int** A = new long int*[m];
	long int** B = new long int*[m];
	long int** C = new long int*[m];
	for(int i=0; i<m; i++){
		A[i]=new long int[m];
		B[i]=new long int[m];
		C[i]=new long int[m];
	}

	//Preenche Matrix ( A B )
	m_fill(A,m);
	m_fill(B,m);

	//Numero de Cores(Nucleos) do Processador
	unsigned int cores = std::thread::hardware_concurrency();
	std::cout<<"Core Count:"<<cores<<"\n";

	int n = cores*2;	//Numero de 2 Threads/Core (Piper)
	std::thread t00[n];	//Vetor de Threads
	int interv = m/n;	//Intervalo de linhas

	for(int i=0; i < n; i++){
		int fim,ini = i*interv;

		if(i+1 == n)	fim = m;
		else 			fim = (i+1)*interv;
		std::cout<<"\nIntervalo: "<<ini<<" <-> "<<fim<<".";

		t00[i] = std::thread(m_multi,A,B,C,ini,fim,m);
	}

	for(int i=0; i < n; i++){
		t00[i].join();
	}

//Log de Valores
/*
	//Saida Matrix ( A B )
	m_out(A,m);
	m_out(B,m);

	//Saida Matrix ( C )
	m_out(C,m);
*/

	return 0;
}

