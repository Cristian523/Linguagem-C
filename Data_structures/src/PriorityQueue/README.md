# *** Leia com calma cada observação aqui e os arquivos priority_queue.h e priority_queue_str.h


1) Foram criadas várias funções para que não tenha que mexer diretamente nas structs PriorityQueue e PriorityQueue_str. Então, sempre que for interagir com os valores armazenados, recomendo que use as funções aqui criadas, pois assim você evita problemas.
   

2) Funções que tiver como retorno obtido por parâmetro sendo em um parâmetro com  "tipo_priority_queue*" sem áspas não é necessário digitar esse nome, pois pode simplesmente digitar o respectivo tipo equivalente a esse. Por exemplo, se manter o padrão DOUBLE_G que foi deixado em todas as estruturas, pode passar o endereço de uma variável double com o &, ou até mesmo o tipo que tenha selecionado (por exemplo, se escolheu TIPO_PRIORITY_QUEUE_INT ao invés do padrão TIPO_PRIORITY_QUEUE_DOUBLE_G, pode passar o endereço de um int com o &), não sendo necessário fazer todo esse processo com o nome maior tipo_priority_queue.


3) Funções que tiver como retorno obtido por parâmetro sendo String deve-se fazer o seguinte: crie uma variável String e *inicialize-a* (recomendo que seja com o string_new_empty()) para que então use a função desejada. 
      
    * OBS: Lembre-se de que, após usar a função e o retorno para o que for necessário, a respectiva memória da String deve ser liberada!
  


4) A String obtida com algum to_string() aqui implementado representa o vetor internamente, que este vetor representa uma árvore binária cheia ou quase cheia (se conhesse bem uma fila de prioridade, vai saber como está estruturada essa árvore no vetor).
