OBJS += Queue.o mythread.o

SHARED_LIB := mythread.so

CFLAGS = -g -fpic
CC    =  gcc 

.c.o:
    $(CC) $(CFLAGS) -c $< -o $@
    
$(SHARED_LIB): Queue.o mythread.o
    $(CC) -shared $(OBJS) -o libmythread.so 
clean:
    rm *.o *.so
