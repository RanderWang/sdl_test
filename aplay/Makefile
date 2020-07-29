err_pcm_open.o:err_pcm_open.c
	gcc -O0 -g -c err_pcm_open.c -I../include -lrt -lasound -lm -ldl -lpthread -o err_pcm_open.o

err_pcm_hw_param.o:err_pcm_hw_param.c
	gcc -O0 -g -c err_pcm_hw_param.c -I../include -lrt -lasound -lm -ldl -lpthread -o err_pcm_hw_param.o

err_pcm_prepare.o:err_pcm_prepare.c
	gcc -O0 -g -c err_pcm_prepare.c -I../include -lrt -lasound -lm -ldl -lpthread -o err_pcm_prepare.o

err_pcm_write.o:err_pcm_write.c
	gcc -O0 -g -c err_pcm_write.c -I../include -lrt -lasound -lm -ldl -lpthread -o err_pcm_write.o

err_pcm_close.o:err_pcm_close.c
	gcc -O0 -g -c err_pcm_close.c -I../include -lrt -lasound -lm -ldl -lpthread -o  err_pcm_close.o

main.o:main.c
	gcc -O0 -g -c main.c -I../include -lrt -lasound -lm -ldl -lpthread -o main.o

sof_test:main.o err_pcm_open.o err_pcm_hw_param.o err_pcm_prepare.o err_pcm_write.o err_pcm_close.o
	gcc -O0 -g -o sof_test main.o err_pcm_open.o err_pcm_hw_param.o err_pcm_prepare.o err_pcm_write.o err_pcm_close.o -lrt -lasound -lm -ldl -lpthread

aplay:sof_test.c
	gcc -O0 -g sof_test.c -I../include -lrt -lasound -lm -ldl -lpthread -o aplay

clean:
	rm sof_test *.o


