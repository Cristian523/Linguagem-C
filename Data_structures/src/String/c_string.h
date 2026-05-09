#ifndef C_STRING_H
#define C_STRING_H

#define STRING_DEFAULT_CAPACITY 50                       // Capacidade padrão de string. Isso será usado se necessário.
#include <stdbool.h>

typedef struct String {
	char* str;
	int length;
	int capacity;
} String;

String string_new_with_size(int);                        
// @ Inicializa uma string com um tamanho passado como parâmetro. Se tiver um tamanho inválido, assume a capacidade padrão (tamanho 50)

String string_new_with_cstr(const char*);                
// @ Inicializa uma string copiando todo o conteúdo de um vetor de caracteres padrão da linguagem C

String string_new_empty();                               
// @ Inicializa uma string vazia. Basicamente chama a função string_new_with_size(0)

String string_new();                                     
// @ Inicializa uma string com a capacidade padrão (tamanho 50)

int string_length(const String*);                        
// @ Retorna o tamanho da string sem o usuário se preocupar com os campos

bool string_append(String*, char);                       
// @ Adiciona um caractere no fim da string. Se necessário, esta função vai tentar aumentar o tamanho da string (em caso de problemas de memória ou o ponteiro do parâmetro for nulo, será retornado false).

void string_clear(String*);                              
// @ "Deleta" os caracteres da string, sem diminuir a capacidade ou liberar a memória corrente. Basicamene assume todos os caracteres como lixo de memória atribuindo ao campo length o valor 0

void string_free(String*);                               
// @ Libera a memória da string. 

bool string_remove(String*, char);                       
// @ Remove a primeira ocorrência do caractere x da string. Se não encontrar o caractere x ou a string for vazia, será retornado false.

bool string_remove_all(String*, char);                   
// @ Remove todas as ocorrências do caractere x da string. Se a string for vazia, será retornado false.

bool string_pop(String*);
// @ Remove o ultimo caractere da String. Se a string for vazia, será retornado false.

bool string_pop_at(String*, int);
// @ Remove o caractere na posição indicada no segundo parâmetro. Se a string for vazia ou a posição do segundo parâmetro for inválida, será retornado false,

bool string_is_valid(const String*);                     
// @ Verifica se a string é válida. Se o argumento for nulo, o campo capacity for 0 ou o campo str for nulo, será retornado false.

bool string_is_empty(const String*);                     
// @ Verifica se a string passada é vazia. Se a string for vazia ou o ponteiro passado por argumento for nulo, será retornado true.

int string_search(const String*, char);                  
// @ Procura a primeira ocorrência do caractere x da string. Se encontrar, será retornado uma posição válida desse caractere. Se não encontrar, será retornado -1

int string_count(const String*, char);                   
// @ Retorna a quantidade de vezes que o caractere do segundo parâmetro aparece na string

void string_print(const String*);                        
// @ Imprime na tela a string.

void string_println(const String*);                      
// @ Imprime na tela a string com um caractere '\n'

bool string_copy_cstr(String*, const char*);             
// @ Copia os caracteres do vetor vet para a string. Se falhar em memória ou um dos argumentos for inválido, será retornado false.

bool string_copy(String*, const String*);                
// @ Copia os caracteres de uma string para a outra. Se falhar em memória ou um dos argumentos for inválido, será retornado false.

char string_get(const String*, int);                     
// @ Retorna o caractere da posição indicada. Se não encontrar, será retornado '\0'

bool string_at(const String*, int, char*);               
// @ Retorna o caractere da posição indicada no terceiro parâmetro. Se não encontrar, será retornado false.

int string_compare(const String*, const String*);        
// @ Compara duas strings (basicamente usa o strcmp padrão do C, então espere o mesmo comportamento)

int string_compare_cstr(const String*, const char*);
// @ Compara string com vetor de caracteres (basicamente usa o strcmp padrão do C, então espere o mesmo comportamento)

String string_concat_new(const String*, const String*);         
// @ Retorna a concatenação entra as duas string em uma nova string (cadeia1 + cadeia2). Se falhar, será retornado uma string vazia ou um dos argumentos como cópia.

String string_concat_new_cstr_cstr(const char*, const char*);   
// @ Retorna a concatenação entre dois vetores de caracteres em formato de string. Se falhar, será retornado uma string vazia ou um dos argumentos como cópia

String string_concat_new_str_cstr(const String*, const char*);  
// @ Retorna a concatenação entre uma string e um vetor de caracteres em formato de string. Basicamente será chamado a função acima concat_new_cstr_cstr

String string_concat_new_cstr_str(const char*, const String*);  
// @ Retorna a concatenação entre um vetor de caracteres e uma string em formato de string. Basicamente será chamado a função acima concat_new_cstr_cstr

bool string_concat_cstr(String*, const char*);                  
// @ Concatena o vetor de caracteres do segundo parâmetro para a string. Se falhar, a string não será modificada.

bool string_concat(String*, const String*);                     
// @ Concatena a string do segundo parâmetro para o primeiro (faz cadeia1 += cadeia2). Se falhar, a primeira string não será modificada.

String string_substring(const String*, int, int);        
// @ Retorna a substring da posição do segundo parâmetro até o terceiro. Em caso de problemas nos argumentos ou de memória, será retornado uma string vazia

bool string_find(const String*, const String*, int*, int*);          
/* @ Verifica se existe a string do segundo parâmetro no primeiro. Se existir, será retornado nos terceiro e quarto parâmetro, respectivamente, a primeira e a ultima posição dos caracteres de onde encontrou essa substring, caso contrário, esses últimos dois parâmetros não serão modificados.
   OBS: Se a substring for uma string vazia, será retornado no terceiro e no quarto parâmetro o numero 0 em cada um
*/

bool string_find_cstr(const String*, const char*, int*, int*);
// @ Usa a função anterior, mas antes converte o segundo parâmetro para uma String provisória. Se não conseguir fazer essa conversão ou obtiver qualquer problema da outra função, será retornado false e os terceiro e quarto parâmetros não serão modificados.

String string_from_int(int);                             
// @ Retorna uma representação de um int como string. Se falhar na atribuição de retorno, será retornado uma string vazia.

String string_from_long(long int);                       
// @ Retorna uma representação de um long int como string. Se falhar na atribuição de retorno, será retornado uma string vazia.

String string_from_long_long(long long int);             
// @ Retorna uma representação de um long long int como string. Se falhar na atribuição de retorno, será retornado uma string vazia.

String string_from_float(float, int);                    
// @ Retorna uma representação de um float como string com precisão de tamanho fornecido no segundo parâmetro. Se falhar na atribuição de retorno, será retornado uma string vazia.

String string_from_double(double, int);                  
// @ Retorna uma representação de um double como string com precisão de tamanho fornecido no segundo parâmetro. Se falhar na atribuição de retorno, será retornado uma string vazia.

String string_from_double_g(double);                     
// @ Retorna uma representação de um double usando o modificador "%g". Se falhar na atribuição de retorno, será retornado uma string vazia.

String string_from_char(char);                           
// @ Retorna uma representação de um único caractere como string. Se falhar, será retornado uma string vazia.

char* string_to_cstr(const String*);                     
// @ Retorna um vetor de caracteres como representação da string como é na linguagem C. Aqui será retornado uma cópia.  (é necessário liberar esse retorno com o free se não for nulo)

const char* string_cstr(const String* s);               
// @ Retorna um vetor de caracteres como representação da string como é na linguagem C. Aqui será retornado o próprio campo str da string, porém como constante (Não deve ser liberado pelo usuário diretamente).


#endif
