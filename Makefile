cc = clang 

TARGET = mlang.exe

SRCS = main.c tokenizer.c

HDRS = tokenizer.h

CFLAGS = -Wall -Wextra -g

$(TARGET) : $(SRCS) $(HDRS)
	$(cc) $(CFLAGS) -o $(TARGET) $(SRCS)

clean :
	del -Q $(TARGET)
