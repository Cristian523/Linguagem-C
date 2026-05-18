OBJETOS = bin/teste.o bin/c_string.o bin/vector.o bin/vector_str.o bin/linked_list.o bin/linked_list_str.o \
	  bin/stack.o bin/stack_str.o bin/queue.o bin/queue_str.o bin/hash_table.o bin/hash_table_sls.o \
	  bin/hash_table_sn.o 
	  
ARQUIVOS_H = data_structures.h src/String/c_string.h src/Vector/vector.h src/Vector/vector_str.h src/LinkedList/linked_list.h \
	     src/LinkedList/linked_list_str.h src/Stack/stack.h src/Stack/stack_str.h src/Queue/queue.h \
	     src/Queue/queue_str.h src/HashTable/hash_table.h src/HashTable/hash_table_sls.h src/HashTable/hash_table_sn.h \
	     

STRING = src/String/c_string.c src/String/c_string.h

INCLUDES =  -I./src/String -I./src/Vector -I./src/LinkedList -I./src/Stack -I./src/Queue -I./src/HashTable

all: 	$(OBJETOS)
	@gcc -g $(OBJETOS) -o executavel -lm
	@./executavel
	@ #valgrind --leak-check=full --track-origins=yes ./executavel
	
	
bin/teste.o: teste.c $(ARQUIVOS_H)
	@mkdir -p bin
	gcc $(INCLUDES) -c teste.c -o bin/teste.o
	
bin/c_string.o: src/String/c_string.c src/String/c_string.h
	@mkdir -p bin
	gcc $(INCLUDES) -c src/String/c_string.c -o bin/c_string.o

bin/vector.o: src/Vector/vector.c src/Vector/vector.h $(STRING)
	@mkdir -p bin
	gcc $(INCLUDES) -c src/Vector/vector.c -o bin/vector.o
 
bin/vector_str.o: src/Vector/vector_str.c src/Vector/vector_str.h $(STRING)
	@mkdir -p bin
	gcc $(INCLUDES) -c src/Vector/vector_str.c -o bin/vector_str.o
	
bin/linked_list.o: src/LinkedList/linked_list.c src/LinkedList/linked_list.h $(STRING)
	@mkdir -p bin
	gcc $(INCLUDES) -c src/LinkedList/linked_list.c -o bin/linked_list.o
	
bin/linked_list_str.o: src/LinkedList/linked_list_str.c src/LinkedList/linked_list_str.h $(STRING)
	@mkdir -p bin
	gcc $(INCLUDES) -c src/LinkedList/linked_list_str.c -o bin/linked_list_str.o

bin/stack.o: src/Stack/stack.c src/Stack/stack.h src/LinkedList/linked_list.c src/LinkedList/linked_list.h $(STRING)
	@mkdir -p bin
	gcc $(INCLUDES) -c src/Stack/stack.c -o bin/stack.o
	
bin/stack_str.o: src/Stack/stack_str.c src/Stack/stack_str.h src/LinkedList/linked_list_str.c src/LinkedList/linked_list_str.h $(STRING)
	@mkdir -p bin
	gcc $(INCLUDES) -c src/Stack/stack_str.c -o bin/stack_str.o

bin/queue.o: src/Queue/queue.c src/Queue/queue.h src/LinkedList/linked_list.c src/LinkedList/linked_list.h $(STRING)
	@mkdir -p bin
	gcc $(INCLUDES) -c src/Queue/queue.c -o bin/queue.o
	
bin/queue_str.o: src/Queue/queue_str.c src/Queue/queue_str.h src/LinkedList/linked_list_str.c src/LinkedList/linked_list_str.h $(STRING)
	@mkdir -p bin
	gcc $(INCLUDES) -c src/Queue/queue_str.c -o bin/queue_str.o
	
bin/hash_table.o: src/HashTable/hash_table.c src/HashTable/hash_table.h $(STRING)
	@mkdir -p bin
	gcc $(INCLUDES) -c src/HashTable/hash_table.c -o bin/hash_table.o

bin/hash_table_sls.o: src/HashTable/hash_table_sls.c src/HashTable/hash_table_sls.h $(STRING)
	@mkdir -p bin
	gcc $(INCLUDES) -c src/HashTable/hash_table_sls.c -o bin/hash_table_sls.o

bin/hash_table_sn.o: src/HashTable/hash_table_sn.c src/HashTable/hash_table_sn.h $(STRING)
	@mkdir -p bin
	gcc $(INCLUDES) -c src/HashTable/hash_table_sn.c -o bin/hash_table_sn.o




clean:
	@rm -rf bin/ executavel
	@echo "Os arquivos objeto foram removidos com sucesso!"
