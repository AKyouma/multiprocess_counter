/* Contador de primos com multiprocessador
 * Data de  submissao: 16/06/20
 * Nome: Augusto Lourenço de Faria
 * RA: 194447
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
	for (i=2; i < numero; i++){
		if (numero % i == 0)
			return 0;
	}
	return 1;
}

int main() {
	pid_t p;
	int *resultado;
	int entrada, filhos=0;

	/*Definir flags de protecao e visibilidade de memoria*/
	int protection = PROT_READ | PROT_WRITE;
	int visibility = MAP_SHARED | MAP_ANON;
	
	/*Criação da memória compartilhada para o resultado*/
	resultado = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);
	
	do{
		/*lê a entrada*/
		scanf("%d", &entrada);
		
		/*verifica se já tem 4 filhos e espera acabar um para poder continuar, retirei
		  a parte de tirar todos os filhos, pois não havia necessidade já que se tem um
		  disponível podemos continuar*/
		if(filhos == 4){
			while (waitpid(p, NULL, 0) > 0){
					filhos--; 
			}
		}
		
		/*cria os filhos*/
		p = fork();
		filhos++;
		if(p == 0){
			(*resultado) += primo(entrada);
			exit(0);	
		}
	}
	while((entrada = getchar()) != '\n');
	
	/*espera todos os filhos acabarem*/
	while(wait(NULL) > 0); 

	printf("%d\n", *resultado);
	
  return 0;
}
