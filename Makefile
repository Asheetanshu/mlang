cc = clang 

TARGET = mlang.exe

SRCS = src/main.c src/tokenizer.c

HDRS = header/tokenizer.h

CFLAGS = -Wall -Wextra -g

$(TARGET) : $(SRCS) $(HDRS)
	$(cc) $(CFLAGS) -o $(TARGET) $(SRCS)

clean :
	del -Q $(TARGET)
