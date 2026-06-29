*** Algumas observações e informações sobre este projeto: ***

OBSERVAÇÃO PRINCIPAL: Leia com calma cada informação aqui passada e cada arquivo .h que queira usar o tipo de dado.

1) Esta pasta contém minhas implementações de estruturas de dados em C em que eu priorizo segurança dos dados do que realmente complexidade (principalmente em estruturas que armazenam String), a fim de evitar problemas e inconsistências em caso de mudança de valores. 

2) Tudo o que foi implementado:

		2.1) String
		2.2) Vector
		2.3) Vector_str
		2.4) LinkedList
		2.5) LinkedList_str
		2.6) Stack
		2.7) Stack_str
		2.8) Queue
		2.9) Queue_str
		2.10) PriorityQueue
		2.11) PriorityQueue_str
		2.12) HashTable
		2.13) HashTable_sn
		2.14) HashTable_sls
		2.15) Tree
		2.16) AvlTree
	
		OBS1: Olhe cada arquivo .h de cada estrutura de dado acima e, caso existente, outros arquivos "README", pois eu deixo informações do que cada função faz, além do que acontece em caso de falhas.
		OBS2: Cada estrutura dessa PRECISA SER INICIALIZADA com alguma função new() que foi criada!
		OBS3: Em funções em que se tem uma String como retorno obtido em um parâmetro, saiba que o conteúdo antigo será removido para a obtenção do novo. Para que isso ocorra bem, é sempre necessário passar uma string inicializada, seja tendo conteúdo ou uma string vazia com o string_new_empty().
	
3) Explicação sobre as siglas:
   	
	3.1) str: Armazena Strings
	
	3.2) sn: Armazena String como chave e número como valor
	
	3.3) sls: Armazena String como chave e LinkedList_str como valor
	
	3.4) Qualquer outra estrutura de dados sem sigla armazena internamente números
		
4) Por padrão, em cada arquivo .h de estruturas de dados que contenha números, foi configurado um tipo primitivo para que armazenem números por padrão, neste caso é o que eu nomeio como DOUBLE_G. Se quiser alterar, basta comentar a linha da respectiva macro (do respectivo "#define") e descomentar (escolher) o seu tipo primitivo de sua preferência. As escolhas possíveis são:

		4.1) INT: Armazena int e usa string_from_int() para o to_string
		4.2) LONG: Armazena long e usa string_from_long() para o to_string
		4.3) LONG_LONG: Armazena long long e usa string_from_long_long() para o to_string
		4.4) FLOAT: Armazena float e usa string_from_float() para o to_string com a macro PRECISION (por padrão será usado precisão de 2 unidades no to_string, mas isso pode ser alterado)
		4.5) DOUBLE: Armazena double e usa string_from_double() para o to_string com a macro PRECISION (por padrão será usado precisão de 2 unidades no to_string, mas isso pode ser alterado)
		4.6) DOUBLE_G (padrão): Armazena double e usa string_from_double_g() para o to_string, em que esse string_from_double_g() usa internamente o modificador "%g" para ter melhor visualização dos dados na hora de obter a String.
		4.7) CHAR: Armazena char e usa string_from_char() para o to_string

		OBSERVAÇÃO1: Para não ter conflito entre cada arquivo, esses nomes que eu deixei aqui são os nomes finais de cada macro. Eis como está em linked_list.h como exemplo:
	
	
		// #define TIPO_LINKED_LIST_INT
		// #define TIPO_LINKED_LIST_LONG
		// #define TIPO_LINKED_LIST_LONG_LONG
		// #define TIPO_LINKED_LIST_FLOAT
		// #define TIPO_LINKED_LIST_DOUBLE
		#define TIPO_LINKED_LIST_DOUBLE_G
		// #define TIPO_LINKED_LIST_CHAR
	

		De forma semelhante, está assim em cada arquivo, começando com TIPO, no meio o nome da estrutura (em HashTable e HashTable_sn eu mudo um pouco essa regra para não ter repetição) e no final os tipos que eu comentei de 4.1) a 4.7).
		Reforçando que, se quiser alterar o tipo primitivo, basta comentar o que não quer usar e descomentar o que realmente quer usar
	
	
		OBSERVAÇÃO2: Apesar de em vários arquivos .h eu criar um tipo com um typedef usando um tipo primitivo (como tipo_vector, tipo_linked_list, etc), não é necessário usar esse tipo criado nas funções diretamente, basta usar o mesmo tipo que foi comentado mais acima caso queira evitar muita verbosidade. Exemplo: Se uma função tiver exigindo algum argumento como tipo_vector, basta usar o tipo declarado na macro de tipos, isto é, double (se seguir o padrão que eu criei) ou o tipo de sua preferência (se tiver escolhido LONG por exemplo, então use long), e por aí vai.



5) Algumas observações e limitações que tive:
		
	5.1) Como pôde perceber nos itens 2) a 4), eu tentei contornar limitações naturais por usar a linguagem C puro: não ter alguma espécie de tipo parametrizado de maneira não verbosa e mais simples de entender, como generics da linguagem Java ou templates da linguagem C++. 
	
	5.2) Ao olhar cada arquivo .h, vai perceber que eu fui muito verboso com algumas funções e repeti várias com pequenas mudanças de parâmetro e nomes, justamente por não ter um recurso que várias linguagens possuem: sobrecarga de função. Sinto muito pela grande verbosidade dos nomes das funções caso encomode, mas o C não possui esse recurso que tornaria as funções bem melhores para chamá-las. Caso se incomode em digitar nomes longos toda vez, uma sugestão é usar apontadores de função, assim pode incomodar menos caso use alguma função com mais frequência.
	
	5.3) Várias funções eu retorno tipo booleano para indicar uma possibilidade de falha também por limitação de algo que o C não possui: tratamento de erros try-catch como no Java ou try-exception como no Python. No caso o que mais atrapalha são em funções em que se retorna algum valor armazenado, como vector_at e stack_peek, em que eu tive que deixar um parâmetro específico para servir de retorno, o que é um pouco chato, mas necessário para evitar ao máximo que o usuário tenha que se preocupar em criar variáveis ponteiros (nesses casos do vector_at ou funções semelhantes, basta criar uma variável de tipo correspodente à estrutura e passar o endereço dela com o &) ou que tenha algum comportamento indefinido.
	
	5.4) Com o item 5.3) também tenho outra limitação: para ter retorno por parâmetro com tipos compostos (nesse caso String ou alguma outra estrutura de dado) sempre crie uma variável e  *inicialize-a* (usando algum inicizalizador já existente) para não se ter problemas, pois em cada função dessa de retorno por parâmetro, eu apago o conteúdo antigo que esteja armazenado, logo se tiver inicizalizado nada, vai tentar liberar algum lixo de memória e dará problemas. No caso de String (que é o tipo composto de mais uso nesses casos), crie um tipo String e o inicialize com string_new_empty() para não gastar muita memória, aí depois sim usar alguma dessas funções de retorno de parâmetro que citei.
	
	5.5) Cada implementação que faço eu uso e abuso bastante da heap, então sempre libere a memória de String ou de qualquer estrutura de dado que for usada para não se ter vazamento de memória ao final do uso, como string_free(), vector_free(), vector_str_free(), linked_list_free() e etc.
   	
   	
