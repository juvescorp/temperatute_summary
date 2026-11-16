all: temp

temp: temp_functions.o temperature_calculate_csv.o
	gcc -o temp temp_functions.o temperature_calculate_csv.o -g

temperature_read_csv_testing_input.o: temperature_calculate_csv.c temp_functions.h
	gcc -c -o temperature_calculate_csv.o temperature_calculate_csv.c -g

temp_functions.o: temp_functions.c
	gcc -c -o temp_functions.o temp_functions.c -g

clean:
	rm -rf *.o temp
