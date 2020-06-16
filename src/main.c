/* Contador de Primos
 *
 * 
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include <unistd.h>


// função retorna 0 se não for primo e 1 se for primo
int primo (int numero){
	int i;
	if (numero == 1 || numero == 0)
		return 0;
	for (i=2; i<numero; i++){
		if (numero%i == 0)
			return 0;
	}
	return 1;
}

int main() {
	pid_t p[4];
	int *mem_compartilhada, *aponta;
	int resultado, final=0;
	char a;

	/*Definir flags de protecao e visibilidade de memoria*/
	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_SHARED | MAP_ANON;

	mem_compartilhada = (int*) mmap(NULL, sizeof(int)*500, protection, visibility, 0, 0);

	aponta = &(mem_compartilhada[0]);
	*aponta = 1;

	while((a = getchar()) != '\n'){

		scanf("%d", &(mem_compartilhada[(*aponta)]));
		(*aponta)++;
	}
	
	for(int filho=0; filho < 4; filho++){
		p[filho] = fork();
		if(p[filho] == 0)
			break;
	}

  	while ((*aponta) >= 1){
			(*aponta)--;
			resultado = resultado + primo(mem_compartilhada[(*aponta)]);
	}

	while(wait(&final) != -1){};

	printf("%d\n", resultado);
	
  return 0;
}
