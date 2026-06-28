*** Leia com calma cada observação aqui e os arquivos queue.h e queue_str.h ***


1) A implementação de fila feita aqui utiliza como base uma das listas encadeadas implementadas lá na pasta LinkedList (isto é, LinkedList para Queue e LinkedList_str para Queue_str). Então, não faz sentido usar o campo interno nesse caso, pois, se quer usar diretamente uma LinkedList ou LinkedList_str, crie esse tipo manualmente e não precisa usar uma fila, já que, a proposta dessa estrutura de dado é ter suas principais operações em tempo constante (isto é, θ(1)).
   OBS: A fim de ter o mesmo padrão como em outras estruturas de dados, foram implementadas as funções queue_free(), queue_to_string(), queue_print(), queue_println(), queue_str_free(), queue_str_to_string(), queue_str_print() e queue_str_println(), que são funções que não operam em tempo θ(1), porém, as funções realmente importantes em uma fila, como um inicializador, uma inserção, uma remoção, uma obtenção de tamanho e uma obtenção do elemento que representa o início da fila são em tempo θ(1).


2) O texto abaixo se refere ao arquivo "linked_list.h" na pasta LinkedList
     Funções que tiver como retorno obtido por parâmetro sendo em um parâmetro com  "tipo_linked_list*" sem áspas não é necessário digitar esse nome, pois pode simplesmente digitar o respectivo tipo equivalente a esse. Por exemplo, se manter o padrão DOUBLE_G que foi deixado em todas as estruturas, pode passar o endereço de uma variável double com o &, ou até mesmo o tipo que tenha selecionado (por exemplo, se escolheu TIPO_LINKED_LIST_INT ao invés do padrão TIPO_LINKED_LIST_DOUBLE_G, pode passar o endereço de um int com o &), não sendo necessário fazer todo esse processo com o nome maior tipo_linked_list.
 
 
3) Funções que tiver como retorno obtido por parâmetro sendo String deve-se fazer o seguinte: crie uma variável String e *inicialize-a* (recomendo que seja com o string_new_empty()) para que então use a função desejada. 
    OBS: Lembre-se de que, após usar a função e o retorno para o que for necessário, a respectiva memória da String deve ser liberada!
