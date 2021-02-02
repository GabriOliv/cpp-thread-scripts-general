//Numero Perfeito

//	Numero Perfeito
//	Threads em Vetor, Hard Threads, 2Threads per Core
//	Dinamica

#include <iostream>
#include <stdlib.h>		//Numero Random
#include <thread>		//Threads

void DivisorTest(int** A, int first, int last, int N){
	//Preenchimento / Contagem
	for(int j=first; j<last; j++){
		//Criacao do Elemento
		A[j][0] = j+1;
		//Funcao de Composto (Verifica Divisor)
		if(N%(A[j][0]) == 0)	A[j][1] = 1;//True
		else			A[j][1] = 0;//False
	}
}


int main(){
	//Numeros Testes
	int x = 10000;
	std::cout<<"\nTeste com "<<x<<" itens";

	//Vetor de Perfeitos
		int N = x-3;
		//Vetor de Perfeitos
		int** B = new int* [N];
		for(int j=0; j<N; j++)	B[j] = new int[2];
		//Preenchimento de [N/Signal]
		for(int j=0; j<N; j++){
			B[j][0] = j+3;
			B[j][1] = 0;
		}
	
	//Vetor de Divisores
		//Dinamic
		int** A = new int* [x-1];
		for(int j=0; j<x-1; j++)	A[j] = new int[2];

	//Vetor de Threads
		//Numero de Cores(Nucleos) do Processador
		unsigned int cores = std::thread::hardware_concurrency();
		std::cout<<"\nCore Count:"<<cores<<"";
		//Numero de 2 Threads/Core (Piper)
		int P = cores*2;
		std::cout<<"\nThread Count:"<<P<<"\n\n\n";
		//Vetor de Threads
		std::thread t00[P];


	//Testes Pai
	for(int i = 3; i<x; i++){
		//Tamanho do acesso ao Vetor
		int k = i-1;

		//Intervalo de Divisores
		int y = i/P;

		//Preenchimento / Contagem / Thread
		for(int j=0; j<P; j++){
			int  first = j*y, last;

			if(j+1 == P)	last = i;
			else 		last = (j+1)*y;

//Log de Valores
//Saida de Threads
//		std::cout<<"\nT["<<j<<"]:"<<first<<"<->"<<last<<".";
			t00[j] = std::thread(DivisorTest,A,first,last,i);
		}

		//Join das Threads
		for(int l=0; l < P; l++)	t00[l].join();

		//Sync de Threads
		bool exec = false;
		while(exec == false){
			for(int j=0; j < P; j++){
				exec = (exec)|(t00[j].joinable());
			}
			exec = ~exec;
		}

		//Verificacao Perfeito / Soma de Divisores
		//Soma
		int sum = 0;
		for(int j=0; j<k; j++){
			//Somatorio
			sum += A[j][0]*A[j][1];
		}

		//Se Perfeito [Signal->1]
		if(sum == i){
			B[i-3][1] = 1;
		}

//Log de Valores
//Saida de N/Soma
//		std::cout<<"\n["<<i<<"]\tSoma: "<<sum<<"\n";
	}


	//Saida de Perfeitos
	std::cout<<"\n\n\n";
	for(int i=0; i<N; i++){
		if(B[i][1] == 1)	std::cout<<B[i][0]<<"\n";
	}
	std::cout<<"\n";

	return 0;
}

