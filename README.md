# project_threads
 use of pthreads 
 
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
|---|---|
