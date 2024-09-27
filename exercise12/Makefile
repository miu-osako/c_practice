# コンパイラ
CC = gcc

# コンパイルオプション
CFLAGS = -Wall -Wextra -O2

# 出力ファイル名 (作成する実行ファイル)
PROGRAM = hexdump

#オブジェクトファイル
OBJS = practice12.o

#デフォルトのターゲット
all: $(PROGRAM)

#出力ファイルを作成
$(PROGRAM): $(OBJS)
	$(CC) $(CFLAGS) -o $(PROGRAM) $(OBJS)

#クリーンターゲット
clean:
	rm -f $(PROGRAM) $(OBJS)
