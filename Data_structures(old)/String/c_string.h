#ifndef C_STRING_H
#define C_STRING_H


typedef struct String {
	char* str;
	int length;
	int Max_length;
} String;

String string_new_with_size(int);
String string_new_with_str(char*, int);
String string_new();
bool increase_size(char**, int*);
bool string_input(String*);
int string_length(String);
bool string_append(String*, char);
void string_destroy(String*);
bool string_remove(String*, char);
bool string_remove_all(String*, char);
int string_search(String, char);
int string_count(String, char);
void string_print(String);
bool string_parseInt(String, int*);
bool string_parseFloat(String, float*);
bool string_parseDouble(String, double*);
bool string_copy(String*, char*, int);
bool string_nextInt(int*);
bool string_nextFloat(float*);
bool string_nextDouble(double*);

#endif
