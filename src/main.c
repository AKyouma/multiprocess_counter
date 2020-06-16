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
	for (i=2; i<=numero/2; i++){
		if (numero % i == 0)
			return 0;
	}
	return 1;
}

int main() {
	pid_t p;
	int *resultado;
	int a, filhos=0;

	/*Definir flags de protecao e visibilidade de memoria*/
	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_SHARED | MAP_ANON;
	
	/*Criação da memória compartilhada para o resultado*/
	resultado = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);
	

	
	do{
		/*lê a entrada*/
		scanf("%d", &a);
		
		if(filhos == 4){
			for(; waitpid(p, NULL, 0) > 0; filhos--);
			for(; filhos >= 4; filhos--)
				wait(NULL);
		}
		
		p = fork();
		filhos++;
		if(p == 0){
			(*resultado) += primo(a);
			exit(0);	
		}
	}
	while((a = getchar()) != '\n');
	
	/*espera todos os filhos acabarem*/
	while(wait(NULL) > 0); 

	printf("%d\n", *resultado);
	
  return 0;
}
