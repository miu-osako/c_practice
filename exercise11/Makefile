# コンパイラ
CC = gcc
# コンパイルオプション
CFLAGS = -Wall -Wextra -O2
# 出力ファイル名
OUTPUT = display_file
# ソースファイル
SOURCES = practice11.c
# デフォルトのターゲット
all: $(OUTPUT)
# 出力ファイルを作成
$(OUTPUT): $(SOURCES)
	$(CC) $(CFLAGS) -o $(OUTPUT) $(SOURCES)
# クリーンターゲット
clean:
	rm -f $(OUTPUT)
