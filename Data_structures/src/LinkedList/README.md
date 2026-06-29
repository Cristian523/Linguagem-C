# *** Leia com calma cada observação aqui e os arquivos linked_list.h e linked_list_str.h ***

1) Foram criadas várias funções para que não tenha que mexer diretamente nas structs LinkedList e LinkedList_str. Então, sempre que for interagir com os valores armazenados, recomendo que use as funções aqui criadas, pois assim você evita problemas.
   OBS: Se for fazer muita questão de usar os campos das structs, então pode usar, mas apenas para obter o que foi armazenado como *leitura*, isto é, *NUNCA* modifique qualquer campo interno diretamente, pois, se modificado, isso pode acarretar em problemas.
 
 
 2) Funções que tiver como retorno obtido por parâmetro sendo em um parâmetro com  "tipo_linked_list*" sem áspas não é necessário digitar esse nome, pois pode simplesmente digitar o respectivo tipo equivalente a esse. Por exemplo, se manter o padrão DOUBLE_G que foi deixado em todas as estruturas, pode passar o endereço de uma variável double com o &, ou até mesmo o tipo que tenha selecionado (por exemplo, se escolheu TIPO_LINKED_LIST_INT ao invés do padrão TIPO_LINKED_LIST_DOUBLE_G, pode passar o endereço de um int com o &), não sendo necessário fazer todo esse processo com o nome maior tipo_linked_list.
 
 
 3) Funções que tiver como retorno obtido por parâmetro sendo String deve-se fazer o seguinte: crie uma variável String e *inicialize-a* (recomendo que seja com o string_new_empty()) para que então use a função desejada. 
         
      * OBS: Lembre-se de que, após usar a função e o retorno para o que for necessário, a respectiva memória da String deve ser liberada!
 
 
 4) Diferente como ocorre com Vector e Vector_str, LinkedList e LinkedList_str não possuem tratamento com algum campo interno que verifique se a lista está ordenada. Então, as funções linked_list_insert_ordered() e linked_list_str_insert_ordered() aqui implementadas funcionam corretamente apenas se a lista estiver ordenada.
 
 
5) Para navegar por uma lista encadeada sem usar qualquer campo interno de forma mais simples, sempre use primeiro alguma função reset (linked_list_reset() ou linked_list_str_reset()) e depois o seguinte:


      5.1) Em uma LinkedList:

         // Suponha que exista uma variável lista de tipo LinkedList.
         
         // Lembre-se de que tipo_linked_list pode ser substituído pelo seu tipo primitivo equivalente definido como dito em 2)
         
         tipo_linked_list elemento;
         linked_list_reset(&lista);
         if (!linked_list_is_empty(&lista)) {
            do {
               linked_list_current(&lista, &elemento);
               // Começa do primeiro elemento e vai até o último
               // ...
               
            } while (linked_list_next(&lista));
         }
    
    
      5.2) Em uma LinkedList_str:
    
         // Suponha que exista uma variável lista de tipo LinkedList_str.
         
         String elemento = string_new_empty();  // Sempre lembre de inicializar como em 3)
         linked_list_str_reset(&lista);
         if (!linked_list_str_is_empty(&lista)) {
            do {
               linked_list_str_current(&lista, &elemento);
               // Começa do primeiro elemento e vai até o último
               // ...
               
            } while (linked_list_str_next(&lista));
         }
         string_free(&elemento);  // Mesmo que a lista não tenha elementos, uma string vazia ainda tem alocação feita!
