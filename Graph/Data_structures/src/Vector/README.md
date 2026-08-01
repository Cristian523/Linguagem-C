# *** Leia com calma cada observação aqui e os arquivos vector.h e vector_str.h ***


1) Foram criadas várias funções para que não tenha que mexer diretamente nas structs Vector e Vector_str. Então, sempre que for interagir com os valores armazenados, recomendo que use as funções aqui criadas, pois assim você evita problemas.
   		
	* OBS: Se for fazer muita questão de usar os campos das structs, então pode usar, mas apenas para obter o que foi armazenado como *leitura*, isto é, *NUNCA* modifique qualquer campo interno diretamente, pois, se modificado, isso pode acarretar em problemas.
 


2) Em Vector, para obter o retorno no terceiro parâmetro das funções vector_at() e vector_pop_at(), não é necessário criar uma variável com o nome diretamente sendo tipo_vector, e sim usar o próprio tipo que foi escolhido que representa tipo_vector. Eis o exemplo:

		// Imagine que exista uma variável vetor do tipo Vector com pelo menos 1 elemento e queira obter o valor da posição 0.
		// Se permanecer com o padrão estabelecido sendo TIPO_VECTOR_DOUBLE_G, pode criar um double como a variável elemento abaixo. Caso tenha mudado, crie uma variável com o seu tipo escolhido.
		
		double elemento;  
		vector_at(&vetor, 0, &elemento);
		
		// Lembre-se de que, se quiser escrever, sem áspas, "tipo_vector elemento" pode normalmente. Isso aqui explicado é só uma alternativa para evitar verbosidade no retorno desejado.
 
 
 
3) Para obter sem problemas o retorno no terceiro parâmetro nas funções vector_str_at() e vector_str_pop_at(), crie uma variável do tipo String e inicialize-a (uma recomendação é usar o string_new_empty()) e, após isso, use a função desejada passando o endereço da variável com o &.
		
	* OBS: Lembre-se de sempre liberar a memória do tipo String obtido.



4) Lembre-se de que as funções vector_to_cvet() e vector_str_to_cvet() retornam uma cópia do vetor interno por alocação dinâmica, logo é necessário que a libere após o uso.
	
	* OBS: No caso do vetor obtido após o vector_str_to_cvet(), usar só o free() não liberará a memória corretamente. Uma forma de liberar a memória totalmente é a seguinte:



			// Imagine que exista uma variável vetor do tipo Vector_str que contenha todas as Strings usadas.
			
			int n = vector_str_size(&vetor);
			String* array = vector_str_to_cvet(&vetor);
			
			// Após usar a variável array para o que precisar, eis como liberar a memória:
			
			for (int i = 0; i < n; i++) {
				string_free(&array[i]);   // Libera a memória de cada String
			}
			free(array);  // Libera a memória de array
	

5) Tanto em Vector como em Vector_str existe um campo chamado is_sorted em que, em tempo constante, fica armazenado se o vetor interno está ordenado. 
	
	5.1) Existem as funções vector_is_ordered() e vector_str_is_ordered() que usam esse campo interno para ver se o vetor está ordenado, então não é necessário usar esse campo diretamente. Além disso, existem as funções vector_check_ordered() e vector_str_check_ordered() que verificam se o vetor está ordenado, mas aqui já é o processo manual, isto é, ver elemento a elemento se estão em ordem.
	
	5.2) Se adicionar algum elemento que quebre a ordem, então is_sorted será false. A única forma de tornar is_sorted true é com algum pop_at (vector_pop_at() ou vector_str_pop_at()) ou com algum remove (vector_remove() ou vector_str_remove()) caso remova justamente o elemento que esteja quebrando a ordem ou até mesmo com alguma função de ordenação implementada (além de vector_ckeck_ordered() e vector_str_check_ordered(), é claro).
	
	* OBS1: As funções vector_pop() e vector_str_pop() não atualizam o campo is_sorted a fim de manter a complexidade constante (isto é, θ(1)). Então, se apenas o último elemento que foi inserido quebrou a ordenação e você use algum desses pop's mencionados, o campo is_sorted permanece false, sendo necessário usar manualmente o vector_check_ordered() ou vector_str_check_ordered().
		
	* OBS2: Só é possível usar a inserção ordenada e a busca binária se o vetor estiver ordenado, então cuidado principalmente com o que foi dito em OBS1.
	


