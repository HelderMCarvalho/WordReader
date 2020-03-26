all: ./Objects/main.o ./Objects/helpers.o ./Objects/FrequenciaPalavras.o ./Objects/FrequenciaLetras.o ./Objects/FrequenciaCertezas.o ./Objects/Categorias.o
	gcc -o TP1 ./Objects/main.o ./Objects/helpers.o ./Objects/Categorias.o ./Objects/FrequenciaLetras.o ./Objects/FrequenciaPalavras.o ./Objects/FrequenciaCertezas.o -lm

./Objects/Categorias.o: ./Partials/Categorias.c
	gcc -c -lm ./Partials/Categorias.c -o ./Objects/Categorias.o

./Objects/FrequenciaCertezas.o: ./Partials/FrequenciaCertezas.c ./Partials/Headers/FrequenciaCertezas.h
	gcc -c -lm ./Partials/FrequenciaCertezas.c -o ./Objects/FrequenciaCertezas.o

./Objects/FrequenciaLetras.o: ./Partials/FrequenciaLetras.c ./Partials/Headers/FrequenciaLetras.h
	gcc -c -lm ./Partials/FrequenciaLetras.c -o ./Objects/FrequenciaLetras.o

./Objects/FrequenciaPalavras.o: ./Partials/FrequenciaPalavras.c ./Partials/Headers/FrequenciaPalavras.h
	gcc -c -lm ./Partials/FrequenciaPalavras.c -o ./Objects/FrequenciaPalavras.o

./Objects/helpers.o: ./Partials/helpers.c ./Partials/Headers/helpers.h
	gcc -c -lm ./Partials/helpers.c -o ./Objects/helpers.o

./Objects/main.o: main.c
	gcc -c -lm main.c -o ./Objects/main.o
