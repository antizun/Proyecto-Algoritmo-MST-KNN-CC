CC = gcc
DEPS = utils.h mst.h knn.h 
OBJ = main.o knn.o mst.o utils.o  

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $< -lm 

main: $(OBJ)
	gcc $(CFLAGS) -o $@ $^ -lm 
