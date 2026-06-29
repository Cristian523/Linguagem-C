*** Leia com calma cada observação aqui e os arquivos hash_table.h, hash_table_sn.h e hash_table_sls.h ***


1) Explicação rápida de que o que cada tabela hash de encadeamento externo aqui armazena como chave e valor:
	1.1) HashTable armazena dados como chave e valor sendo números de tipos que podem ser distintos (por padrão os dois são DOUBLE_G, mas isso pode ser alterado individualmente)
	1.2) HashTable_sn armazena dados como chave sendo uma String e como valor sendo um número.
	1.3) HashTable_sls armazena dados como chave sendo String e como valor sendo LinkedList_str.
	

2) Funções que tiver como retorno obtido por parâmetro sendo em um parâmetro com  "tipo_value*" ou "tipo_value_number*" sem áspas não é necessário digitar esse nome, pois pode simplesmente digitar o respectivo tipo equivalente a esse. Por exemplo, se manter o padrão DOUBLE_G que foi deixado em todas as estruturas, pode passar o endereço de uma variável double com o &, ou até mesmo o tipo que tenha selecionado, não sendo necessário fazer todo esse processo com o nome maior tipo_value ou tipo_value_number.
	

3) Para obter sem problemas o retorno em parâmetro da função hash_table_sls_get(), crie uma variável do tipo que for necessário (neste caso LinkedList_str) e inicialize-a (com o linked_list_str_new()) e, após isso, use a função desejada passando o endereço da variável com o &.
	OBS: Após obter o retorno e usá-lo para o que for necessário, lembre-se de liberar a memória com linked_list_str_free().



4) Ao usar qualquer função de obter todas as chaves ou obter todos os pares chave-valor, é necessário liberar a memória corretamente. Eis aqui alguns exemplos, supondo que existe uma variável tabela de tipo:

   4.1) HashTable:
	/* Se quiser obter todas as chaves:  */

	// Ao invés de tipo_value*, poderia passar o tipo correspondente a tipo_value, como double* se não tiver alterado o que foi implementado como TIPO_VALUE_DOUBLE_G por padrão:
	
	tipo_value* chaves = hash_table_get_keys(&tabela);
	
	// Após ter usado as chaves para o que for necessário:
	free(chaves);
	
	
	
	/* Se quiser obter todos os pares chave-valor:  */
	
	KeyValue* pares = hash_table_get_keys_values(&tabela);
	
	// Após ter usado os pares chave-valor para o que for necessário:
	
	free(pares);
	
	
	
   4.2) HashTable_sn:
	/* Se quiser obter todas as chaves:  */
	
	String* chaves = hash_table_sn_get_keys(&tabela);
	
	// Após ter usado as chaves para o que for necessário, supondo que não tenha removido qualquer elemento do vetor de chaves ou da tabela (isto é, se a mesma quantidade de chaves da tabela são iguais a quantidade de elementos do vetor obtido):
	
	int n = hash_table_sn_size(&tabela); 
	for (int i = 0; i < n; i++) {
		string_free(&chaves[i]);
	}
	free(chaves);
	
	
	/* Se quiser obter todos os pares chave-valor:  */
	
	KeyValue_sn* pares = hash_table_sn_get_keys_values(&tabela);
	
	// Após ter usado os pares chave-valor para o que for necessário, supondo que não tenha removido qualquer elemento do vetor pares ou da tabela (isto é, se a mesma quantidade de chaves da tabela são iguais a quantidade de elementos do vetor obtido):
	
	int n = hash_table_sn_size(&tabela); 
	for (int i = 0; i < n; i++) {
		string_free(&pares[i].key);
	}
	free(pares);
	
	

   4.3) HashTable_sls
   	/* Se quiser obter todas as chaves:  */
	
	String* chaves = hash_table_sls_get_keys(&tabela);
	
	// Após ter usado as chaves para o que for necessário, supondo que não tenha removido qualquer elemento do vetor de chaves ou da tabela (isto é, se a mesma quantidade de chaves da tabela são iguais a quantidade de elementos do vetor obtido):
	
	int n = hash_table_sn_size(&tabela); 
	for (int i = 0; i < n; i++) {
		string_free(&chaves[i]);
	}
	free(chaves);
	
	
	/* Se quiser obter todos os pares chave-valor:  */
	
	KeyValue_sls* pares = hash_table_sls_get_keys_values(&tabela);
	
	// Após ter usado os pares chave-valor para o que for necessário, supondo que não tenha removido qualquer elemento do vetor pares ou da tabela (isto é, se a mesma quantidade de chaves da tabela são iguais a quantidade de elementos do vetor obtido):
	
	int n = hash_table_sn_size(&tabela); 
	for (int i = 0; i < n; i++) {
		string_free(&pares[i].key);
		linked_list_str_free(&pares[i].value);
	}
	free(pares);
	
