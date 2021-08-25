# project_threads
 
 ## PARTE 1
 
 |  Código | Explicação  |
|---|---|
|![lib](https://github.com/paulovitornovaes/project_threads/blob/9a4c6c73fe0b4307746f37d7526cab76f47109b9/part_1/assets/library_part1.png)|<ul> <li>Bibliotecas necessárias. </li></ul> |
|![part1](https://github.com/paulovitornovaes/project_threads/blob/9a4c6c73fe0b4307746f37d7526cab76f47109b9/part_1/assets/inputs_part1.PNG)   | <ul> <li>Inteiro n para o usuário escolher a quantidade de threads.</li> <li>Vetor que armazenará os nomes das threads geradas.</li> <li>Vetor de char para armazenar as strings geradas para posteriormente armazenar no vetor anterior.</li> </ul>  |
|![loop1](https://github.com/paulovitornovaes/project_threads/blob/3714e7591be01c19e80d30e8982be5c875adbc85/part_1/assets/loop1_part1.png)| <ul> <li>Laço de repetição de 0 até a quantidade de threads que o usuário deu input.</li> <li>vetor de caracteres para armazenar a string "Thread_</li> <li>vetor de caracteres para armazenar o numero da thread</li> <li>ponteiro que aponta para o vetor name_thread</li></ul>
|   |   |


 O looping está pegando a string __name_Thread__ lendo com a string __number_thread__ que tem o valor do __iterador i__ convertido para string com a função __*sprintf*__ e logo após concatena ambas strings.
 Após isso usamos o __ponteiro__ para apontar o endereço que contém a __Thread_1 -> Thread_2...__ finalmente o vetor com o nome da thread criado vai receber com auxilio da função strcpy, names[i] recebe o valor do ponteiro que aponta para o endereço que contém o nome da thread gerada.
 
| Código  | Explicação  |
|---|---|
| ![final](https://github.com/paulovitornovaes/project_threads/blob/59942b31e1534f6e53c80c52751d1bc6099857ec/part_1/assets/final_loop.png)  | <ul> <li>Laço de 0 até o input do usuário.</li> <li>ponteiro que aponta para os nomes das threads já criados</li> <li>função pthread_create</li> </ul>  |


Aqui necessitamos explicar melhor como funciona a função pthread_create, vamos lá:
<ul>
<li>Primeiro parametro se refere a onde a thread será armazenada, no começo do código criamos o vetor do tipo pthread para essa ocasião.</li>
<li>Segundo parametro não é necessário para nossa implementação então o valor recebido é NULL
<li>Terceiro parametro é a rotina que a thread irá executar, como o desafio era imprimir Olá sou a thread_X iremos implementar essa função.</li>
<li>Quarto parametro é referente aos argumentos que a rotina terá, obrigatoriamente a rotina é tipo void, como nossa thread é tipo string precisamos fazer um typecast para passar, chegando na rotina devemos novamente fazer o typecast, mas dessa vez o argumento deve receber type string.</li></ul>

 |  Código | Explicação  |
|---|---|
| ![rotina](https://github.com/paulovitornovaes/project_threads/blob/85ef8bbc4146fab8c147279bd8f05a586e65e11a/part_1/assets/rotina.png)| <ul><li>ponteiro de string recebe o typecast char do argumento da rotina como explicado anteriormente.</li><li>Uso do pthread_self().</li><li>Uso do gettid().</li><ul> |

 
 Aqui terão dois prints diferentes, um com uma id criada com pthread_self() que cria uma id para cada thread e pode ser reutilizado após a finalização da thread, já o gettid que é uma chamada do sistema não pode ser reutilizado.
<br>
<br>
<br>
<br>
 
 ## PARTE 2
 
|  Código | Explicação  |
|---|---|
 |![libs](https://github.com/paulovitornovaes/project_threads/blob/13547fe0819719d092839682126f262d90daa810/part_2/assets/library.png)| bibliotecas necessárias. |
 |struct |<ul> <li>struct vetor_dados.</li><li>vetor com tamanho definido MAX.</li><li>inteiro indicando tamanho.</li><<ul> |
 |---|---|
 | função auxiliar  | Função gera vetores. |
 |---|---|
 
 Função auxiliar que vai gerar um vetor com números randomizados. estamos usando a função srand com a função time para gerar esses números.
 |---|---|
 | Função auxiliar 2| Função imprime vetores. |
 |---|---|
 | Função compara vetores | Função compara vetores  |
 
 
