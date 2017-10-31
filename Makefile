all: print_pid process_tree

clean:
	rm print_pid process_tree

print_pid: print_pid.c
	gcc -o print_pid print_pid.c

process_tree: process_tree.c
	gcc -o process_tree process_tree.c 
