err_pcm_open.o:err_pcm_open.c
	gcc -O0 -g -c err_pcm_open.c -I../include -lrt -lasound -lm -ldl -lpthread -o err_pcm_open.o

err_pcm_hw_param.o:err_pcm_hw_param.c
	gcc -O0 -g -c err_pcm_hw_param.c -I../include -lrt -lasound -lm -ldl -lpthread -o err_pcm_hw_param.o

main.o:main.c
	gcc -O0 -g -c main.c -I../include -lrt -lasound -lm -ldl -lpthread -o main.o

sof_test:main.o err_pcm_open.o err_pcm_hw_param.o
	gcc -O0 -g -o sof_test main.o err_pcm_open.o err_pcm_hw_param.o -lrt -lasound -lm -ldl -lpthread

aplay:sof_test.c
	gcc -O0 -g sof_test.c -I../include -lrt -lasound -lm -ldl -lpthread -o aplay

clean:
	rm aplay sof_test


