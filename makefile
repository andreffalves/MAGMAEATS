OBJ_dir = obj
OBJECTOS = client.o driver.o main.o memory.o process.o restaurant.o
CC = gcc

magnaeats: $(OBJECTOS)
	$(CC) $(addprefix $(OBJ_dir)/,$(OBJECTOS)) -o  bin/$@ -lrt

%.o: src/%.c $($@)
	$(CC) -I include -o $(OBJ_dir)/$@ -c $<

clean:
	rm -r -f $(OBJ_dir)/*.o
	rm -f bin/magnaeats
