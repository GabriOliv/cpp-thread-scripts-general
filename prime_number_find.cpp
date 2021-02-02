//Numeros Primos

//	Primos Aleatorios
//	Threads em Vetor, Hard Threads, 2Threads per Core
//	Dinamica

#include <iostream>
#include <stdlib.h>		//Numero Random
#include <thread>		//Threads


//Saida da Lista
void p_out(int** A, int x){
	std::cout<<"\n\n";
	for(int i=0; i<x; i++){
		std::cout<<"\n["<<(i+1)<<"]\t\t"<<A[i][1]<<"\t\t"<<A[i][0];
		if(A[i][1] == 1) std::cout<<"\t Primo";
	}
	std::cout<<"\n\n";
}

void prime_Fill(int** A, int i){
	A[i][1] = 1;
	A[i][0] = (rand()%(i+10))+2;
}

void prime_Find(int** A, int y, int z){
	for(int i = y; i < z; i++){
		for(int j = (A[i][0])-1; j > 1; j--){
			if(( (A[i][0]) %j) == 0){
				A[i][1] = 0;
				j = 0;
			}
		}
	}
}

int main(){
	//Tamanho da Lista
	int x = 200000;

	//A(x,2)
	int** A = new int*[x];
	for(int i=0; i<x; i++){
		A[i] = new int[2];
		prime_Fill(A,i);
	}

	//Numero de Cores(Nucleos) do Processador
	unsigned int cores = std::thread::hardware_concurrency();
	std::cout<<"\nCore Count:"<<cores<<"\n";

	//Numero de 2 Threads/Core (Piper)
	int n = cores*2;

	//Intervalo de linhas
	int y = x/n;

	//Vetor de Threads
	std::thread t00[n];

	//Vetor de Threads
	for(int i=0; i < n; i++){
		int ini = i*y;
		int fim;

		if(i+1 == n)	fim = x;
		else 			fim = (i+1)*y;

		std::cout<<"\nThread ["<<i<<"]: "<<ini<<" <-> "<<fim<<".";

		//Parametro de Threads
		t00[i] = std::thread(prime_Find,A,ini,fim);
	}

	//Join das Threads
	for(int i=0; i < n; i++){
		t00[i].join();
	}

	bool exec = false;
	while(exec == false){
		for(int i=0; i < n; i++){
			exec = (exec)|(t00[i].joinable());
		}
		exec = ~exec;
		std::cout<<"\nThread execution";
	}
	std::cout<<"\nThread terminada";

	//Saida Lista
	p_out(A,x);

	return 0;
}

