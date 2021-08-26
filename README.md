# project_threads
 
 ## PARTE 1
 
 |  Código | Explicação  |
|---|---|
|![lib](https://github.com/paulovitornovaes/project_threads/blob/9a4c6c73fe0b4307746f37d7526cab76f47109b9/part_1/assets/library_part1.png)|<ul> <li>Bibliotecas necessárias. </li></ul> |
|  |  |
|![part1](https://github.com/paulovitornovaes/project_threads/blob/9a4c6c73fe0b4307746f37d7526cab76f47109b9/part_1/assets/inputs_part1.PNG)   | <ul> <li>Inteiro n para o usuário escolher a quantidade de threads.</li> <li>Vetor que armazenará os nomes das threads geradas.</li> <li>Vetor de char para armazenar as strings geradas para posteriormente armazenar no vetor anterior.</li> </ul>  |
| |  |
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
 <br>
 <br>
  
 -------
 
 ## PARTE 2
 
|  Código | Explicação  |
|---|---|
 |![libs](https://github.com/paulovitornovaes/project_threads/blob/21de4ba378ac1deef6d309bd24ee7389ae2f3a30/part_2/assets/0.png)| bibliotecas necessárias. |
 |   |   |
 |![struct](https://github.com/paulovitornovaes/project_threads/blob/609606a018c5f5b54061e4cb809e4c2d59293dd5/part_2/assets/1.1.png) |<ul> <li>struct vetor_dados.</li><li>vetor com tamanho definido MAX.</li><li>inteiro indicando tamanho.</li><ul> |
 |     |     |
 | ![função auxiliar](https://github.com/paulovitornovaes/project_threads/blob/ca0a4012cf1e4b61c5d31f4dcf595f301c92b942/part_2/assets/2.png)  | Função gera vetores. |
 
 
 Função auxiliar que vai gerar um vetor com números randomizados. estamos usando a função srand com a função time para gerar esses números.
 
|  Código | Explicação  |
|---|---|
| ![Função auxiliar 2](https://github.com/paulovitornovaes/project_threads/blob/ca0a4012cf1e4b61c5d31f4dcf595f301c92b942/part_2/assets/3.png)| Função imprime vetores. |
 |  |  |
| ![Função compara vetores](https://github.com/paulovitornovaes/project_threads/blob/ca0a4012cf1e4b61c5d31f4dcf595f301c92b942/part_2/assets/4.png) | Função compara vetores  |

 
 Algoritmo que recebe duas structs vetor_dados como parametro e compara posição por posição qualquer inconsistência.
 
 
|  Código | Explicação  |
|---|---|
|![Função sequencial](https://github.com/paulovitornovaes/project_threads/blob/ca0a4012cf1e4b61c5d31f4dcf595f301c92b942/part_2/assets/5.png) | função remove_par sequencial.|
 
Função que recebe como parametro um tipo vetor_dados e em um laço de repetição procura por pares, caso encontrado outro laço será utilizado para organizar as posições sem esse número par encontrado.
 
 
|  Código | Explicação  |
|---|---|
|![Função sequencial2](https://github.com/paulovitornovaes/project_threads/blob/ca0a4012cf1e4b61c5d31f4dcf595f301c92b942/part_2/assets/6.png) | função remove_mul_cinco sequencial.|
 
Funciona da mesma forma que o anterior, mas dessa vez remove os múltiplos de 5.
 
 
|  Código | Explicação  |
|---|---|
|![Função com thread e semaforo](https://github.com/paulovitornovaes/project_threads/blob/ca0a4012cf1e4b61c5d31f4dcf595f301c92b942/part_2/assets/7.png) | função remove par com threads e semáforos.|
 
 
 Essa função tem como o mesmo objetivo da anterior, remover os pares, a diferença aqui é o uso de threads e semáforos, para ser uma rotina da thread a gente coloca como parametro o argumento tipo void.
 Dentro do laço, antes de verificar se o número é divisivel por 2 nós colocamos o sem_wait(&semaphore), que é a condição de parada dos semáforos.
 Depois da verificação ocorre a condição de corrida.
Isso é necessário pois a proxima região vai entrar na região critica também, então primeiro uma função entra, depois outra função entra, chamamos isso de exclusão mútua.
 
 |  Código | Explicação  |
|---|---|
|![Função com thread e semaforo 2](https://github.com/paulovitornovaes/project_threads/blob/ca0a4012cf1e4b61c5d31f4dcf595f301c92b942/part_2/assets/8.png) | função remove múltiplos de 5 com threads e semáforos.|
 
 Funciona da mesma forma que o anterior, removendo múltiplos de 5 e garantindo a exclusão mútua graças ao sem_wait antes de entrar na região crítica e sem_post após terminar o acesso a região crítica.
 
 |  Código | Explicação  |
|---|---|
|![int main1](https://github.com/paulovitornovaes/project_threads/blob/ca0a4012cf1e4b61c5d31f4dcf595f301c92b942/part_2/assets/9.png) | Vamos usar as funções.|
 
 
 Definimos duas threads para o uso das rotinas remover multiplos de 5 e remover pares.
 Definimos o tipo clock_t para calcular o tempo de execução da função sequencial e da função com uso de threads e semáforos.
 Definimos 3 structs e seus devidos ponteiros, a primeira é para o uso das funções sequenciais, a segunda é para
 threads com semáforos e a terceira é para o vetor comparador, para isso precisamos de um vetor_inteiros original, o original vai receber valores aleatorios com a função gera_vetor_random, e essas outras structs vão receber o vetor_original.
 
 __*Resposta do desafio*__ = Teste o programa com e sem semáforos (ambos com threads), observe o resultado e explique o que está acontecendo.

Caso não seja utilizado os semáforos você irá notar que em algum momento o algoritmo de compara_vetor vai apresentar inconsistencias com o vetor original, isso ocorre pois ambas threads executam as rotinas entrando na região crítica ao mesmo tempo, como o algoritmo de remover pares ou múltiplos de 5 vão verificar e remover ao mesmo tempo, em algum momento uma das funções vai analisar um caso que já tenha sido removido pelo outro, por isso a necessidade de exclusão mútua nesse cenário é vital.
 
 |  Código | Explicação  |
|---|---|
|![int main função thread](https://github.com/paulovitornovaes/project_threads/blob/ca0a4012cf1e4b61c5d31f4dcf595f301c92b942/part_2/assets/9.png) | Vamos usar as threads.|
 
 Criado uma variavel t_thread_sem para pegar o timer inicial da iniciação da implementação com thread.
 Usamos a função sem_init que inicia o semáforo, vamos aos parametros =
 <ul><li>Endereço do semáforo.</li> <li>Valor para classificar se é compartilhado entre processos ou não (ajuda na parte 3). </li> <li> Valor inicial do semáforo.</li> </ul>
 
Vamos setar o &semaphore por que declaramos no começo do programa o tipo sem_t semaphore.
 
Para o segundo valor vamos colocar 0 pois não estamos trabalhando com processos ainda.
 
Para o terceiro valor vamos colocar 1 pois assim uma rotina pode entrar na região crítica por vez.
 
 
 criação das threads com as rotinas e o uso do pthread_join() que serve para suspender a thread chamada a não ser que ela já tenha sido terminada. É uma função útil para programas multithreading.
 
 Após toda função ter sido executada o t_thread_sem recebe o valor do tempo de execução e usamos a função em baixo.
 
 |  Código | Explicação  |
|---|---|
|![int main função sequencial](https://github.com/paulovitornovaes/project_threads/blob/ca0a4012cf1e4b61c5d31f4dcf595f301c92b942/part_2/assets/10.png)| Vamos usar as funções sequenciais.|
 
 Mesma ideia da implementação anterior, vamos setar o inicio do clock, chamar as funções e calcular o tempo total.
 
 
 |  Código | Explicação  |
|---|---|
|![int main função sequencial](https://github.com/paulovitornovaes/project_threads/blob/ca0a4012cf1e4b61c5d31f4dcf595f301c92b942/part_2/assets/11.png)| Vamos usar as funções sequenciais.|
 
 
 Após toda implementação, mais um requisito é necessário, um algoritmo que remove em um laço de repetição pares e multiplos de 5, para depois comparar com a versão das threads. Terminando tudo o resultado esperado tem que ser 0 diferenças.
 
 <br>
 <br>
 <br>
 <br>
 <br>
 
 -------
 
 ## Parte 3
 
 |  Código | Explicação  |
|---|---|
|![lib](https://github.com/paulovitornovaes/project_threads/blob/8eceeeddca9ddea337ffcac8505b02bc79ae266a/part_3/assets/0.png)|<ul> <li>Bibliotecas necessárias. </li></ul> |
|  |  |
 |![lib](https://github.com/paulovitornovaes/project_threads/blob/8eceeeddca9ddea337ffcac8505b02bc79ae266a/part_3/assets/1.png)|<ul> <li>macro do máximo valor</li> <li>struct do tipo shmid_ds</li> <li>struct do tipo vetor_dados</li></ul> |
|  |  |
 
 
 Para essa terceira parte a gente usa as mesmas funções da parte 2, a diferença é que vamos usar processos dessa vez.
 
 |  Código | Explicação  |
|---|---|
 |![lib](https://github.com/paulovitornovaes/project_threads/blob/8eceeeddca9ddea337ffcac8505b02bc79ae266a/part_3/assets/2.png)|<ul> <li>executando as funções no int main().</li></ul> |
|  |  |
 |![lib](https://github.com/paulovitornovaes/project_threads/blob/8eceeeddca9ddea337ffcac8505b02bc79ae266a/part_3/assets/3.png)|<ul> <li>Bibliotecas necessárias. </li></ul> |
|  |  |
 
 Aqui começamos criando a área da memória compartilhada.
 O shmget() retorna o identificador do segmento da memória compartilhada associado com a key escolhida no primeiro parametro.
 <ul> <li>Primeiro parametro diz sobre a key mencionada anteriormente</li> <li>Segundo parametro diz sobre o tamanho alocado para a memória compartilhada.</li> <li>Terceiro parametro é sobre as flags</li> </ul>
 
 
Sobre as flags, são elas que definem os direitos de acesso a essa memória compartilhada, se a flag for privada = 0, apenas o processo proprietário vai poder utilizar ela. Utilizei a IPC_CREAT para criar o segmento, a IPC_EXCL para assegurar a criação do segmento e 0600 significa read and write, nós precisamos ler cada valor dos indices para saber se precisamos remover.

 |  Código | Explicação  |
|---|---|
 |![lib](https://github.com/paulovitornovaes/project_threads/blob/8eceeeddca9ddea337ffcac8505b02bc79ae266a/part_3/assets/4.png)|<ul> <li>Bibliotecas necessárias. </li></ul> |
|  |  |
