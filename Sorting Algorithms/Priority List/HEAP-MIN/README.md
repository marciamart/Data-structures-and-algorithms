# HEAP
## *Descrição:*
Heap estática. Os elementos do vetor são adicionados cumprindo propriedades particulares da heap, ou seja, para todo i temos que 
x[i] é menor que ou equivalente a x[2*i] e a x[2*i+1]. 

## ***Neste repositório estão:***
### main.c
aqui estão as funções de comparação e de impressão do vetor.  
[main para teste] - ***ADAPTAVEL***   
a main deve ser adaptada de acordo com as necessidades na qual a heap será utilizada.

### heap.h
aqui estão declaradas as funções:
* HEAP_create
* HEAP_add
* HEAP_remove

### HEAP.c
aqui estão implementadas as funções do heap.h

## *Tecnologias utilizadas:*
Linguaguem C  
testado e compilado com Ubuntu 20.04 e gcc 9.4

## *como utilizar:*
* para compilar é nessário que o gcc 9.4 teja instalado
1. clone o projeto:  
copie e cole o comando abaixo no seu terminal:
```
git clone https://github.com/marciamart/HEAP
```
2. `compile e execute` desta maneira: 

```
cd HEAP
gcc HEAP.c main.c -o heap
./heap
```
