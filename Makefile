cc = clang 

TARGET = mlang.exe

SRCS = src/*.c

HDRS = header/*.h

CFLAGS = -Wall -Wextra -g

$(TARGET) : $(SRCS) $(HDRS)
	$(cc) $(CFLAGS) -o $(TARGET) $(SRCS)

clean :
	del -Q $(TARGET)
