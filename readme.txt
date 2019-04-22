1º trabalho de Laboratório de programação 2018/2019
Interpreter realizado por Armando Martins(201504230) e Diogo Ribeiro(201504115)

Para compilar: gcc *.c
Para executar: ./a.out <nome do ficheiro>

O programa lida com o sguinte conjunto de instruções:

ler(<var>);
lê um número a partir do stdin.


escrever(<var ou num>);
escreve ou o número que está como argumento ou o valor que está guardado na variável.


<var> = <var ou num> <símbolo de operação aritmética> <var ou num>;
Operações aritméticas com está implementado em C.


label <label>;
serve de etiqueta para o programa saber para onde dirigir o program counter


if <var> goto <label>
se <var> for positivo ou negativo segue para a label , senão vai para a linha a seguir


goto <label>;
segue para a linha que tem como label <label>.


quit;
termina o programa.

Sobre a estrutura do código: 
O programa utiliza uma linked list de instruçoes em que cada instruçao contem um kind para distinguir o tipo de intruçao e 3 elementos cada um com um kind para saber que tipo de elemento se trata. Para lidar com as labels e e variaveis usamos uma tabela de hash que para as lables guarda o apontador para o nó da linked list a que pertence essa label e para as variaveis guarda o respetivo valor.

Notas importantes:
labels de var's são strings com 25 carateres e não podem começar com números
as variáveis podem guardar números decimais ou inteiros
