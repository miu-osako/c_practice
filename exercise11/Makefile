#コンパイラ
CC = gcc

#コンパイルオプション
CFLAGS = -Wall -Wextra -Werror -O3

#作成する実行ファイル
PROGRAM = display_file

#オブジェクトファイル
OBJS = practice11.o

#デフォルトのターゲット
all: $(PROGRAM)

#出力ファイルを作成
$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJS)

#クリーンターゲット
clean:
	rm -f practice11.o $(PROGRAM) $(OBJS)
