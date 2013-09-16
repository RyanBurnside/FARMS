OBJS = Chr_code.o

test: $(OBJS)
	g++ -o test main.cpp $(OBJS)

Chr_code.o: Chr_code.cpp Chr_code.h
	g++ -c Chr_code.cpp

clean_objects:
	rm *.o
	echo Cleaning done

clean_temps:
	rm *~*
	echo Cleaned up temps

clean_all:
	rm *.o
	echo Cleaning done
	rm *~*
	echo Cleaned up temps

clean_for_git:
	rm *.o
	echo Cleaning done
	rm *~*
	echo Cleaned up temps
	rm test
