OBJ_dir = obj
OBJECTOS = client.o driver.o main.o memory.o process.o restaurant.o
CC = gcc
LIBS = -lrt
CFLAGS = -Wall -g -I include -o
magnaeats: $(OBJECTOS)
	$(CC) $(addprefix $(OBJ_dir)/,$(OBJECTOS)) -o  bin/$@ $(LIBS)


objs: $(OBJECTOS)
	$(CC) $(addprefix $(OBJ_dir)/,$(OBJECTOS)) $(LIBS)
	rm -f a.out


%.o: src/%.c $($@)
	$(CC) $(CFLAGS) $(OBJ_dir)/$@ -c $<


clean:
	rm -r -f $(OBJ_dir)/*.o
	rm -f bin/magnaeats
