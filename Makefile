build:
	gcc -Wall fileSystem.c lists.c trie.c main.c -o search_index
run:
	./search_index
clean:
	rm search_index