# VETOR ORDENADO
## *Descrição:*
Vetor ordenado estático. Os elementos do vetor são adicionados ordenadamente.  
## ***Neste repositório estão:***
### main.c
aqui estão as funções de comparação e de impressão do vetor.  
[main para teste] - ***ADAPTAVEL***   
a main deve ser adaptada de acordo com as necessidades na qual o vetor ordernado será utilizado.
### ordvetor.h
aqui estão declaradas as funções:
* VETORD_create
* VETORD_add
* VETORD_remove
### vetord.c
aqui estão implementadas as funções do  ordvetor.h
## *Tecnologias utilizadas:*
Linguaguem C

testado e compilado com Ubuntu 20.04 e gcc 9.4

## *como utilizar:*
* para compilar é nessário que o gcc 9.4 teja instalado
1. clone o projeto:
copie e cole o comando abaixo no seu terminal:
```
git clone https://github.com/marciamart/VETORD
```
2. `compile e execute` desta maneira: 

```
cd VETORD
gcc vetord.c main.c -o vetor_ordenado
./vetor_ordenado
```
