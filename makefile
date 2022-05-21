#Grupo: SO-010
 #Membros:
 #Francisco Teixeira | FC56305
 #Andre Alves        | FC56349
 #Rodrigo Antunes    | FC56321
 #
OBJ_dir = obj
OBJECTOS = client.o driver.o main.o memory.o process.o restaurant.o synchronization.o metime.o configuration.o mesignal.o log.o stats.o
CC = gcc
LIBS = -lrt -lpthread
CFLAGS = -Wall -g -O0 -I include -o
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
