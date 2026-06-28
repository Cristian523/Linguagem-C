*** Leia com calma cada observação aqui e os arquivos tree.h e avl_tree.h ***

1) Foram criadas várias funções para que não tenha que mexer diretamente nas structs Tree e AvlTree. Então, sempre que for interagir com os valores armazenados, recomendo que use as funções aqui criadas, pois assim você evita problemas.
   OBS1: Se for fazer muita questão de usar os campos das structs, então pode usar, mas apenas para obter o que foi armazenado como *leitura*, isto é, *NUNCA* modifique qualquer campo interno diretamente, pois, se modificado, isso pode acarretar em problemas.
   OBS2: Caso use os campos, saiba que, em caso de repetição de elementos, o campo Q é usado para guardar a quantidade de elementos repetidos.
 

2) As funções tree_to_cvet() e avl_tree_to_cvet() retornam um vetor ordenado com todos os elementos da árvore. Como esse vetor é feito por alocação dinâmica, lembre-se de, ao final, liberar a memória com o free()
