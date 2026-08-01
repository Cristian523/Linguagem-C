OBJETOS_DATA = Data_structures/bin/teste.o Data_structures/bin/c_string.o Data_structures/bin/vector.o Data_structures/bin/vector_str.o \
	       Data_structures/bin/linked_list.o Data_structures/bin/linked_list_str.o Data_structures/bin/stack.o Data_structures/bin/stack_str.o \
	       Data_structures/bin/queue.o Data_structures/bin/queue_str.o Data_structures/bin/hash_table.o Data_structures/bin/hash_table_sls.o \
	       Data_structures/bin/hash_table_sn.o Data_structures/bin/tree.o Data_structures/bin/avl_tree.o Data_structures/bin/priority_queue.o \
	       Data_structures/bin/priority_queue_str.o
	  
ARQUIVOS_H_DATA = Data_structures/data_structures.h Data_structures/src/String/c_string.h Data_structures/src/Vector/vector.h Data_structures/src/Vector/vector_str.h \
		  Data_structures/src/LinkedList/linked_list.h Data_structures/src/LinkedList/linked_list_str.h Data_structures/src/Stack/stack.h \
		  Data_structures/src/Stack/stack_str.h Data_structures/src/Queue/queue.h Data_structures/src/Queue/queue_str.h Data_structures/src/HashTable/hash_table.h \
		  Data_structures/src/HashTable/hash_table_sls.h Data_structures/src/HashTable/hash_table_sn.h Data_structures/src/Tree/tree.h Data_structures/src/Tree/avl_tree.h \
		  Data_structures/src/PriorityQueue/priority_queue.h Data_structures/src/PriorityQueue/priority_queue_str.h

OBJETOS_AUXILIARES = Auxiliares/bin/edge.o Auxiliares/bin/vector_edge.o Auxiliares/bin/pqnode.o Auxiliares/bin/priority_queue_pqnode.o Auxiliares/bin/graph.o Auxiliares/bin/main.o \
		     Auxiliares/bin/hash_table_ew.o

ARQUIVOS_H_AUXILIARES = graph.h Auxiliares/auxiliares.h Auxiliares/src/edge.h Auxiliares/src/vector_edge.h Auxiliares/src/pqnode.h Auxiliares/src/priority_queue_pqnode.h \
			Auxiliares/src/hash_table_ew.h

STRING = Data_structures/src/String/c_string.c Data_structures/src/String/c_string.h

INCLUDES = -I./Data_structures -I./Data_structures/src/String -I./Data_structures/src/Vector -I./Data_structures/src/LinkedList -I./Data_structures/src/Stack -I./Data_structures/src/Queue \
           -I./Data_structures/src/HashTable -I./Data_structures/src/Tree -I./Data_structures/src/PriorityQueue -I./Auxiliares -I./Auxiliares/src


all: 	$(OBJETOS_DATA) $(OBJETOS_AUXILIARES) 
	@gcc -g $(OBJETOS_DATA) $(OBJETOS_AUXILIARES) -o executavel -lm
	@ #./executavel
	@valgrind --leak-check=full --track-origins=yes ./executavel

Auxiliares/bin/main.o: main.c $(ARQUIVOS_H_DATA) $(ARQUIVOS_H_AUXILIARES)
	@mkdir -p Auxiliares/bin
	@gcc $(INCLUDES) -c main.c -o Auxiliares/bin/main.o
	
Auxiliares/bin/graph.o: graph.c $(ARQUIVOS_H_DATA) $(ARQUIVOS_H_AUXILIARES)
	@mkdir -p Auxiliares/bin
	@gcc $(INCLUDES) -c graph.c -o Auxiliares/bin/graph.o
	
Auxiliares/bin/edge.o: Auxiliares/src/edge.c Auxiliares/src/edge.h $(STRING)
	@mkdir -p Auxiliares/bin
	@gcc $(INCLUDES) -c Auxiliares/src/edge.c -o Auxiliares/bin/edge.o
	
Auxiliares/bin/pqnode.o: Auxiliares/src/pqnode.c Auxiliares/src/pqnode.h $(STRING)
	@mkdir -p Auxiliares/bin
	@gcc $(INCLUDES) -c Auxiliares/src/pqnode.c -o Auxiliares/bin/pqnode.o
	
Auxiliares/bin/vector_edge.o: Auxiliares/src/vector_edge.c Auxiliares/src/vector_edge.h $(STRING)
	@mkdir -p Auxiliares/bin
	@gcc $(INCLUDES) -c Auxiliares/src/vector_edge.c -o Auxiliares/bin/vector_edge.o
	
Auxiliares/bin/priority_queue_pqnode.o: Auxiliares/src/priority_queue_pqnode.c Auxiliares/src/priority_queue_pqnode.h $(STRING)
	@mkdir -p Auxiliares/bin
	@gcc $(INCLUDES) -c Auxiliares/src/priority_queue_pqnode.c -o Auxiliares/bin/priority_queue_pqnode.o
	
Auxiliares/bin/hash_table_ew.o: Auxiliares/src/hash_table_ew.c Auxiliares/src/hash_table_ew.h $(STRING)
	@mkdir -p Auxiliares/bin
	@gcc $(INCLUDES) -c Auxiliares/src/hash_table_ew.c -o Auxiliares/bin/hash_table_ew.o





	
Data_structures/bin/teste.o: Data_structures/teste.c $(ARQUIVOS_H_DATA)
	@mkdir -p Data_structures/bin
	@gcc $(INCLUDES) -c Data_structures/teste.c -o Data_structures/bin/teste.o
	
Data_structures/bin/c_string.o: Data_structures/src/String/c_string.c Data_structures/src/String/c_string.h
	@mkdir -p Data_structures/bin
	@gcc $(INCLUDES) -c Data_structures/src/String/c_string.c -o Data_structures/bin/c_string.o

Data_structures/bin/vector.o: Data_structures/src/Vector/vector.c Data_structures/src/Vector/vector.h $(STRING)
	@mkdir -p Data_structures/bin
	@gcc $(INCLUDES) -c Data_structures/src/Vector/vector.c -o Data_structures/bin/vector.o
 
Data_structures/bin/vector_str.o: Data_structures/src/Vector/vector_str.c Data_structures/src/Vector/vector_str.h $(STRING)
	@mkdir -p Data_structures/bin
	@gcc $(INCLUDES) -c Data_structures/src/Vector/vector_str.c -o Data_structures/bin/vector_str.o
	
Data_structures/bin/linked_list.o: Data_structures/src/LinkedList/linked_list.c Data_structures/src/LinkedList/linked_list.h $(STRING)
	@mkdir -p Data_structures/bin
	@gcc $(INCLUDES) -c Data_structures/src/LinkedList/linked_list.c -o Data_structures/bin/linked_list.o
	
Data_structures/bin/linked_list_str.o: Data_structures/src/LinkedList/linked_list_str.c Data_structures/src/LinkedList/linked_list_str.h $(STRING)
	@mkdir -p Data_structures/bin
	@gcc $(INCLUDES) -c Data_structures/src/LinkedList/linked_list_str.c -o Data_structures/bin/linked_list_str.o

Data_structures/bin/stack.o: Data_structures/src/Stack/stack.c Data_structures/src/Stack/stack.h Data_structures/src/LinkedList/linked_list.c \
			     Data_structures/src/LinkedList/linked_list.h $(STRING)
	@mkdir -p Data_structures/bin
	@gcc $(INCLUDES) -c Data_structures/src/Stack/stack.c -o Data_structures/bin/stack.o
	
Data_structures/bin/stack_str.o: Data_structures/src/Stack/stack_str.c Data_structures/src/Stack/stack_str.h Data_structures/src/LinkedList/linked_list_str.c \
				 Data_structures/src/LinkedList/linked_list_str.h $(STRING)
	@mkdir -p Data_structures/bin
	@gcc $(INCLUDES) -c Data_structures/src/Stack/stack_str.c -o Data_structures/bin/stack_str.o

Data_structures/bin/queue.o: Data_structures/src/Queue/queue.c Data_structures/src/Queue/queue.h Data_structures/src/LinkedList/linked_list.c \
			     Data_structures/src/LinkedList/linked_list.h $(STRING)
	@mkdir -p Data_structures/bin
	@gcc $(INCLUDES) -c Data_structures/src/Queue/queue.c -o Data_structures/bin/queue.o
	
Data_structures/bin/queue_str.o: Data_structures/src/Queue/queue_str.c Data_structures/src/Queue/queue_str.h Data_structures/src/LinkedList/linked_list_str.c \
				 Data_structures/src/LinkedList/linked_list_str.h $(STRING)
	@mkdir -p Data_structures/bin
	@gcc $(INCLUDES) -c Data_structures/src/Queue/queue_str.c -o Data_structures/bin/queue_str.o
	
Data_structures/bin/hash_table.o: Data_structures/src/HashTable/hash_table.c Data_structures/src/HashTable/hash_table.h $(STRING)
	@mkdir -p Data_structures/bin
	@gcc $(INCLUDES) -c Data_structures/src/HashTable/hash_table.c -o Data_structures/bin/hash_table.o

Data_structures/bin/hash_table_sls.o: Data_structures/src/HashTable/hash_table_sls.c Data_structures/src/HashTable/hash_table_sls.h $(STRING)
	@mkdir -p Data_structures/bin
	@gcc $(INCLUDES) -c Data_structures/src/HashTable/hash_table_sls.c -o Data_structures/bin/hash_table_sls.o

Data_structures/bin/hash_table_sn.o: Data_structures/src/HashTable/hash_table_sn.c Data_structures/src/HashTable/hash_table_sn.h $(STRING)
	@mkdir -p Data_structures/bin
	@gcc $(INCLUDES) -c Data_structures/src/HashTable/hash_table_sn.c -o Data_structures/bin/hash_table_sn.o

Data_structures/bin/tree.o: Data_structures/src/Tree/tree.c Data_structures/src/Tree/tree.h $(STRING)
	@mkdir -p Data_structures/bin
	@gcc $(INCLUDES) -c Data_structures/src/Tree/tree.c -o Data_structures/bin/tree.o
	
Data_structures/bin/avl_tree.o: Data_structures/src/Tree/avl_tree.c Data_structures/src/Tree/avl_tree.h $(STRING)
	@mkdir -p Data_structures/bin
	@gcc $(INCLUDES) -c Data_structures/src/Tree/avl_tree.c -o Data_structures/bin/avl_tree.o
	
Data_structures/bin/priority_queue.o: Data_structures/src/PriorityQueue/priority_queue.c Data_structures/src/PriorityQueue/priority_queue.h $(STRING)
	@mkdir -p Data_structures/bin
	@gcc $(INCLUDES) -c Data_structures/src/PriorityQueue/priority_queue.c -o Data_structures/bin/priority_queue.o

Data_structures/bin/priority_queue_str.o: Data_structures/src/PriorityQueue/priority_queue_str.c Data_structures/src/PriorityQueue/priority_queue_str.h $(STRING)
	@mkdir -p Data_structures/bin
	@gcc $(INCLUDES) -c Data_structures/src/PriorityQueue/priority_queue_str.c -o Data_structures/bin/priority_queue_str.o
	
clean:
	@rm -rf Data_structures/bin/ Auxiliares/bin/ executavel
	@echo "Os arquivos objeto foram removidos com sucesso!"
