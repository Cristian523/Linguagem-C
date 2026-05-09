#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include "c_string.h"

String string_new_with_size(int size) {      // Inicializa uma string com um tamanho passado como parâmetro. Se tiver um tamanho inválido, assume a capacidade padrão (tamanho 50)
	String cadeia;
	if (size < 0)
	        size = STRING_DEFAULT_CAPACITY;
	cadeia.str = (char*) malloc((size + 1) * sizeof(char));     // Este + 1 é para ter um espaço reservado para o caractere '\0'
	if (cadeia.str != NULL) {
	        cadeia.str[0] = '\0';
	        cadeia.capacity = size + 1;
        }
        else
                cadeia.capacity = 0;
	cadeia.length = 0;
	return cadeia;
}

String string_new_with_cstr(const char* vet) {     // Inicializa uma string copiando todo o conteúdo de um vetor de caracteres padrão da linguagem C, mas aqui é um vetor de String
	String cadeia;
	cadeia.str = NULL;
	if (vet == NULL) 
	        cadeia = string_new_with_size(0);
	else {
	        cadeia.capacity = strlen(vet) + 1;
	        string_copy_cstr(&cadeia, vet);            // Função que copia o vetor de caracteres da linguagem C para a string de inicialização
                if (cadeia.str == NULL) 
	                cadeia.length = cadeia.capacity = 0;
	}
	return cadeia;
}

String string_new_empty() {            // Cria uma string vazia. Basicamente chama a função string_new_with_size(0)
    return string_new_with_size(0);
}

String string_new() {                             // Inicializa uma string com a capacidade padrão (tamnho 50)
	return string_new_with_size(STRING_DEFAULT_CAPACITY);
}

static bool increase_size_string(char** vet, int* N) {  /* Função privada auxiliar que tenta aumentar o tamanho de um vetor de caracteres com o relloc dobrando o tamanho N passado. Se falhar, será retornado false.  */
	(*N) *= 2;
	char* novo_vet = (char*) realloc(*vet, (*N) * sizeof(char));
	if (novo_vet == NULL)
		return false;
	*vet = novo_vet;
	return true;
}


int string_length(const String* cadeia) {        // Retorna o tamanho da string sem precisar preocupar com os campos
	if (cadeia == NULL) return 0;
	return cadeia->length;
}

bool string_append(String* cadeia, char x) {     // Adiciona um caractere no fim da string. Se necessário, esta função vai tentar aumentar o tamanho da string.
	if (cadeia == NULL) return false;
	
	// Caso esta função seja chamada com nenhum tamanho inicial máximo.
	if (cadeia->capacity <= 0) {
		cadeia->capacity = STRING_DEFAULT_CAPACITY;
		cadeia->length = 0;
	}
	if (cadeia->str == NULL || cadeia->capacity == 1) {              // Uma verificação adicional
		if (cadeia->capacity == 1) {      // Isso aqui é se a string tiver apenas o '\0', daí não precisa fazer múltiplos reallocs se tiver um loop ao usar esta função.
		        free(cadeia->str);
		        cadeia->str = NULL;
		        cadeia->capacity = STRING_DEFAULT_CAPACITY;
		        cadeia->length = 0;
		}
		
		cadeia->str = malloc(cadeia->capacity * sizeof(char));
      	        if (cadeia->str == NULL) {
      		        cadeia->capacity = cadeia->length = 0;
      		        return false;
      		}
	}
	
	// Aumenta o tamanho da string, caso necessário
	if (cadeia->length + 1 >= cadeia->capacity) {
		if (!increase_size_string(&(cadeia->str), &(cadeia->capacity)))  // Tenta dobrar o tamanho
			return false;
	}
	cadeia->str[cadeia->length] = x;
	(cadeia->length)++;
	cadeia->str[cadeia->length] = '\0';
	return true;
}

void string_clear(String* cadeia) {             // "Deleta" os caracteres da string, sem diminuir a capacidade ou liberar a memória corrente
    if (cadeia != NULL && cadeia->str != NULL) {
        cadeia->str[0] = '\0';
        cadeia->length = 0;
    }
}

void string_free(String* cadeia) {          // Libera a memória da string. 
	if (cadeia != NULL && cadeia->str != NULL) {
		free(cadeia->str);
		cadeia->str = NULL;
		cadeia->length = cadeia->capacity = 0;
	}
}

bool string_remove(String* cadeia, char x) {          // Remove a primeira ocorrência do caractere x da string
	if (cadeia == NULL || cadeia->str == NULL)
		return false;
	int posicao = -1;
	for (int i = 0; i < cadeia->length; i++) {
		if (cadeia->str[i] == x) {
			posicao = i;
			break;
		}			
	}
	if (posicao != -1) {
		for (int i = posicao; i < cadeia->length - 1; i++) {
			cadeia->str[i] = cadeia->str[i + 1];
		}
		cadeia->str[cadeia->length - 1] = '\0';
		(cadeia->length)--;
		return true;
	}
	return false;
}

bool string_remove_all(String* cadeia, char x) {    // Remove todas as ocorrências do caractere x da string.
	if (cadeia == NULL || cadeia->str == NULL)
		return false;
	int i, j = 0;
	char aux;
	for (i = 0; i < cadeia->length; i++) {
		if (cadeia->str[i] != x) {
			cadeia->str[j] = cadeia->str[i];
			j++;
		}
	}
	cadeia->str[j] = '\0';
	cadeia->length = j;
	return true;
}

bool string_pop(String* cadeia) {   // Remove o ultimo caractere da String.
    if (string_is_empty(cadeia))
        return false;
        
    cadeia->length--;
    cadeia->str[cadeia->length] = '\0';
    return true;
}

bool string_pop_at(String* cadeia, int posicao) {   // Remove o caractere na posição indicada no segundo parâmetro.
    if (string_is_empty(cadeia) || posicao < 0 || posicao >= cadeia->length)
        return false;
    
    for (int i = posicao; i < cadeia->length; i++)
        cadeia->str[i] = cadeia->str[i + 1];

    cadeia->length--;
    cadeia->str[cadeia->length] = '\0';
    return true;
}


bool string_is_valid(const String* cadeia) {  // Verifica se a string é válida
    if (cadeia == NULL || cadeia->capacity == 0 || cadeia->str == NULL) return false;
    else return true;
}

bool string_is_empty(const String* cadeia) {       // Verifica se a string é vazia
    if (cadeia == NULL || cadeia->length == 0 || cadeia->str == NULL) return true;
    else return false;
}


int string_search(const String* cadeia, char x) {        // Procura a primeira ocorrência do caractere x da string. Se encontrar, será retornado uma posição válida desse caractere
	if (cadeia == NULL || cadeia->str == NULL)
		return -1;
	for (int i = 0; i < cadeia->length; i++) {
		if (cadeia->str[i] == x)
			return i; 
	}
	return -1;
}

int string_count(const String* cadeia, char x) {        // Retorna a quantidade de vezes que o caractere x aparece na string
	if (cadeia == NULL || cadeia->str == NULL) return 0;
	int count = 0;
	for (int i = 0; i < cadeia->length; i++) {
		if (cadeia->str[i] == x)
			count++;
	}
	return count;
}

void string_print(const String* cadeia) {              // Imprime na tela a string
	if (cadeia == NULL || cadeia->str == NULL)
	    return;
	for (int i = 0; i < cadeia->length; i++) 
		printf("%c", cadeia->str[i]);
}

void string_println(const String* cadeia) {           // Imprime na tela a string com um caractere '\n'
        string_print(cadeia);
        printf("\n");
}


bool string_copy_cstr(String* cadeia, const char* vet) {     // Copia os caracteres do vetor vet para a string 
	if (cadeia == NULL || vet == NULL)
	    return false;
	int n = strlen(vet);
	int N = cadeia->capacity;
	char* aux;
	if (N <= n)          // Se a capacidade da string tive um tamanho menor do que o vetor vet.
		N = n + 1;
	aux = (char*)malloc(N * sizeof(char));
	if (aux == NULL)
		return false;
		
	for (int i = 0; i < n; i++) 
		aux[i] = vet[i];
	aux[n] = '\0';
	if (cadeia->str != NULL)          // Se tiver caracteres a string, eu libero a memória que não precisar mais
		free(cadeia->str);	
	
	cadeia->str = aux;
	cadeia->capacity = N;
	cadeia->length = n;
	return true;	
}

bool string_copy(String* cadeia1, const String* cadeia2) {    // Copia os caracteres de uma string para a outra
        if (cadeia2 == NULL) return false;
        return string_copy_cstr(cadeia1, cadeia2->str);
}

char string_get(const String* cadeia, int posicao) {          // Retorna o caractere da posição indicada. Se não encontrar, será retornado '\0'
        if (cadeia == NULL || cadeia->str == NULL || cadeia->length == 0)
                return '\0';
        else if (posicao < 0 || posicao >= cadeia->length)
                return '\0';
        else
                return cadeia->str[posicao];

}

bool string_at(const String* cadeia, int posicao, char* retorno) {       // Retorna o caractere da posição indicada no terceiro parâmetro. Se não encontrar, será retornado false.
        if (cadeia == NULL || cadeia->str == NULL || cadeia->length == 0)
                return false;
        else if (posicao < 0 || posicao >= cadeia->length)
                return false;
        *retorno = cadeia->str[posicao];
        return true;
}

int string_compare(const String* cadeia1, const String* cadeia2) {       // Compara duas strings
        if (cadeia1 == NULL || cadeia2 == NULL)
                return INT_MIN;    // só retornando algo sem sentido
        return strcmp(cadeia1->str, cadeia2->str);
}

int string_compare_cstr(const String* cadeia, const char* caracteres) {   // compara string com vetor de caracteres
        if (cadeia == NULL)
                return INT_MIN;    // só retornando algo sem sentido
        return strcmp(cadeia->str, caracteres);
}

String string_concat_new(const String* cadeia1, const String* cadeia2) {     // Retorna a concatecação entra as duas string em uma nova string (cadeia1 + cadeia2)
        String cadeia;
        if (cadeia1 == NULL && cadeia2 == NULL) 
                cadeia = string_new_with_size(0);
        else if (cadeia1 != NULL && cadeia2 == NULL) 
                cadeia = string_new_with_cstr(cadeia1->str);
        else if (cadeia1 == NULL && cadeia2 != NULL)
                cadeia = string_new_with_cstr(cadeia2->str);
        
        else {
                  cadeia = string_new_with_size(cadeia1->length + cadeia2->length + 1);  // Este +1 é para evitar realocação desnecessária
                  for (int i = 0; i < cadeia1->length; i++) {
                          if (!string_append(&cadeia, cadeia1->str[i])) {
                                  string_free(&cadeia);
                                  cadeia = string_new_with_size(0);
                                  return cadeia;
                          }         
                  }
                  for (int i = 0; i < cadeia2->length; i++) {
                          if (!string_append(&cadeia, cadeia2->str[i])) {
                                  string_free(&cadeia);
                                  cadeia = string_new_with_size(0);
                                  return cadeia;
                          }         
                  }
        }
        return cadeia;
}

String string_concat_new_cstr_cstr(const char* vet1, const char* vet2) {      // Concatenação entre dois vetores de caracteres e depois retorna uma string.
        String cadeia;
        if (vet1 == NULL && vet2 == NULL) {
                cadeia = string_new_with_size(0); 
                return cadeia;
        }
        else if (vet1 != NULL && vet2 == NULL) {
                cadeia = string_new_with_cstr(vet1);
                return cadeia;
        }
        else if (vet1 == NULL && vet2 != NULL) {
                cadeia = string_new_with_cstr(vet2);
                return cadeia;
        }
        
        char* vet = (char*) malloc((strlen(vet1) + strlen(vet2)) * sizeof(char));
        if (vet == NULL) {
                cadeia = string_new_with_size(0); 
                return cadeia;
        }
        
        strcpy(vet, vet1);
        strcat(vet, vet2);
        cadeia = string_new_with_cstr(vet);
        free(vet);
        return cadeia;

}

String string_concat_new_str_cstr(const String* cadeia, const char* vet2) {     // Concatenação entre uma string e um vetor de caracteres em formato de string
        char* vet1 = NULL;
        if (cadeia != NULL)
                vet1 = cadeia->str;
        return string_concat_new_cstr_cstr(vet1, vet2);
}

String string_concat_new_cstr_str(const char* vet1, const String* cadeia) {     // Concatenação entre um vetor de caracteres e uma string em formato de string
        char* vet2 = NULL;
        if (cadeia != NULL)
                vet2 = cadeia->str;
        return string_concat_new_cstr_cstr(vet1, vet2);
}

bool string_concat_cstr(String* cadeia1, const char* vet) {         // Concatena o vetor de caracteres do segundo parâmetro para a string
        if (cadeia1 == NULL)
                return false;
        bool deu_certo;
        if (vet != NULL) {
                String cadeia_aux = string_new_with_size(0);
                deu_certo = string_copy(&cadeia_aux, cadeia1);
                if (!deu_certo)
                        return false;
                
                int vet_length = strlen(vet);
                for (int i = 0; i < vet_length; i++) {
                        if (!string_append(&cadeia_aux, vet[i])) { 
                                string_free(&cadeia_aux);
                                return false;        
                        }
                }
                
                free(cadeia1->str);              // Liberando a memória antiga para colocar o conteúdo de cadeia_aux
                cadeia1->str = cadeia_aux.str;
                cadeia1->length = cadeia_aux.length;
                cadeia1->capacity = cadeia_aux.capacity;
                
                // Eu não uso string_free(&cadeia_aux) aqui pois a memória alocada do campo str ficará em cadeia1, daí não é necessário usar o string_copy novamente
        }
        return true;
}

bool string_concat(String* cadeia1, const String* cadeia2) {        // Concatena a string do segundo parâmetro para o primeiro (faz cadeia1 += cadeia2)
        if (cadeia1 == NULL)
                return false;
        char* vet = NULL;
        if (cadeia2 != NULL) 
                vet = cadeia2->str;
        
        return string_concat_cstr(cadeia1, vet);
}

String string_substring(const String* cadeia, int start, int end) {          // Retorna a substring da posição start até a posição end
        String sub;
        if (cadeia != NULL && cadeia->length > 0 && end >= cadeia->length)
                end = cadeia->length - 1;
        if (cadeia == NULL || cadeia->length == 0 || start < 0 || 
            start >= cadeia->length  || end < 0 || start > end) {
                    sub = string_new_with_size(0);
        }
        else {
                sub = string_new_with_size(end - start + 1);
                if (sub.str != NULL) {     
                        int j = 0;
                        for (int i = start; i <= end; i++) {
                                sub.str[j] = cadeia->str[i];
                                j++;
                        }
                        sub.str[j] = '\0';
                        sub.length = j;
                }
        }
        return sub;

}

bool string_find(const String* cadeia, const String* sub, int* start, int* end) {    // Verifica se existe a substring sub na string atual
        if (cadeia == NULL || sub == NULL)     // apenas verificação se algum argumento é nulo.
              return false;
        else if (sub->length > cadeia->length)
              return false;
              
        if (sub->length == 0)
              return true;
              
        int j = 0, k = 0;
        for (int i = 0; i < cadeia->length; i++) {
              j = i;
              if (cadeia->str[j] == sub->str[k]) {
                      k++;
                      int fim_da_sub = j;
                      for (j = i + 1; j < cadeia->length; j++) {
                              if (k == sub->length)
                                      break;
                              else if (cadeia->str[j] != sub->str[k]) { 
                                      break;
                              }
                              k++;
                              fim_da_sub++;
                      }
                      if (k == sub->length)  { // se percorreu toda a substring, então conseguiu encontrar 
                              *start = i;
                              *end = fim_da_sub;
                              return true;
                      }
              }
              k = 0;
        }
        return false;
}

bool string_find_cstr(const String* cadeia, const char* sub_caracteres, int* start, int* end) {   // Usa a função anterior
    if (cadeia == NULL)
        return false;
    if (sub_caracteres == NULL || strlen(sub_caracteres) == 0)
        return true;
    
    String aux = string_new_with_cstr(sub_caracteres);
    bool result = string_find(cadeia, &aux, start, end);
    string_free(&aux);
    return result;
}

String string_from_int(int numero) {                    // Retorna uma representação de um int como string.
        char aux[50];
        String cadeia;
        int result = snprintf(aux, sizeof(aux), "%d", numero);
        if (result < 0)
                cadeia = string_new_with_size(0);
        else {
                String cadeia = string_new_with_cstr(aux);
                if (cadeia.str == NULL)
                        cadeia = string_new_with_size(0);
        }
        return cadeia;
}

String string_from_long(long int numero) {              // Retorna uma representação de um long int como string.
        char aux[50];
        String cadeia;
        int result = snprintf(aux, sizeof(aux), "%ld", numero);
        if (result < 0)
                cadeia = string_new_with_size(0);
        else {
                String cadeia = string_new_with_cstr(aux);
                if (cadeia.str == NULL)
                        cadeia = string_new_with_size(0);
        }
        return cadeia;
}

String string_from_long_long(long long int numero) {    // Retorna uma representação de um long long int como string.
        char aux[50];
        String cadeia;
        int result = snprintf(aux, sizeof(aux), "%lld", numero);
        if (result < 0)
                cadeia = string_new_with_size(0);
        else {
                String cadeia = string_new_with_cstr(aux);
                if (cadeia.str == NULL)
                        cadeia = string_new_with_size(0);
        }
        return cadeia;
}

String string_from_float(float numero, int precisao) {               // Retorna uma representação de um float como string 
        char aux[50];
        char num[6];
        char aux2[6];
        int result;
        String cadeia;
        
        if (precisao < 0)
                precisao = 0;
        
        result = snprintf(num, sizeof(num), "%d", precisao);       // Convertendo precisao para vetor de caracteres
        if (result < 0) {
                cadeia = string_new_with_size(0);
                return cadeia;
        }
        
        strcpy(aux2, "%.");
        strcat(aux2, num);
        strcat(aux2, "f");
        
        result = snprintf(aux, sizeof(aux), aux2, numero);
        if (result < 0)
                cadeia = string_new_with_size(0);       
        else {
                cadeia = string_new_with_cstr(aux);
                if (cadeia.str == NULL)
                        cadeia = string_new_with_size(0);
        }       
        return cadeia;
}

String string_from_double(double numero, int precisao) {             // Retorna uma representação de um double como string 
        char aux[50];
        char num[6];
        char aux2[6];
        int result;
        String cadeia;
        
        if (precisao < 0)
                precisao = 0;
        
        result = snprintf(num, sizeof(num), "%d", precisao);        // Convertendo precisao para vetor de caracteres
        if (result < 0) {
                cadeia = string_new_with_size(0);
                return cadeia;
        }
        
        strcpy(aux2, "%.");
        strcat(aux2, num);
        strcat(aux2, "f");
        
        result = snprintf(aux, sizeof(aux), aux2, numero);
        if (result < 0)
                cadeia = string_new_with_size(0);       
        else {
                cadeia = string_new_with_cstr(aux);
                if (cadeia.str == NULL)
                        cadeia = string_new_with_size(0);
        }       
        return cadeia;
}

String string_from_double_g(double numero) {           // Retorna uma representação de um double usando o modificador "%g"
        char aux[50];
        int result;
        String cadeia;
    
        result = snprintf(aux, sizeof(aux), "%g", numero);
        if (result < 0)
                cadeia = string_new_with_size(0);       
        else {
                cadeia = string_new_with_cstr(aux);
                if (cadeia.str == NULL)
                        cadeia = string_new_with_size(0);
        }       
        return cadeia;
}

String string_from_char(char caractere) {
        String cadeia = string_new_with_size(1);
        if (cadeia.str == NULL)
                cadeia = string_new_with_size(0);
        else {
                cadeia.str[0] = caractere;
                cadeia.str[1] = '\0';
                cadeia.length = 1;
        }
        return cadeia;
}

char* string_to_cstr(const String* cadeia) {           // Retorna um vetor de caracteres como representação da string como é na linguagem C. Aqui será retornado uma cópia.
        if (cadeia == NULL || cadeia->str == NULL)
                return NULL;
        char* s = (char*) malloc((cadeia->length + 1) * sizeof(char));
        if (s == NULL)
                return NULL;
        strcpy(s, cadeia->str);
        return s;
}

const char* string_cstr(const String* cadeia) {      // Retorna um vetor de caracteres como representação da string como é na linguagem C. Aqui será retornado o próprio campo str da string, porém como constante
        return cadeia->str;
}

