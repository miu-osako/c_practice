#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// エラー
#define SUCCESS 0 // 正常終了
#define FAILURE 1 // 引数エラー
#define ERR_OPN_FILE 2 // ファイルオープンエラー
#define ERR_FILE_FORMAT 3 //入力ファイルフォーマットエラー
#define ERR_DBFILE_FORMAT 4 // databaseファイルフォーマットエラー
#define ERR_MALLOC 5 // メモリ確保エラー
#define ERR_SYSTEM 6 // その他、致命的なエラー

#define MAX_INFILE_ROW_LENGTH 1024 //入力ファイルの1行の上限

// モードの定義
#define MODE_NOTSET 0 //モード未設定
#define MODE_INPUT 1 //入力モード
#define MODE_DISPLAY 2 //DB表示モード

// エラーメッセージ
#define MSG_ERR_PARA\
		"usage: wcount [-o database] -i infile\n"\
		"		wcount -r database\n" // 引数エラーメッセージ
#define MSG_ERR_OPN_FILE "file open error. [%s][%s]\n" //ファイルオープンエラーメッセージ
#define MSG_ERR_FILE_FORMAT "invalide file format. [%s]\n" //入力ファイルフォーマットエラーメッセージ
#define MSG_ERR_DBFILE_FORMAT "invalide database format. [%s]\n" //databaseファイルフォーマットエラーメッセージ
#define MSG_ERR_MALLOC "memory allocation error.\n" //メモリ確保エラーメッセージ
#define MSG_ERR_SYSTEM "system error.\n" //その他、致命的なエラーメッセージ

// word_data型構造体
// typedef struct word_data_t {
// 	char *word;
// 	int count;
// 	struct word_data_t *next;
// } word_data;

// void count_words() {
// 	WordData[];
// 	int word_count = 0;
// }

// param_list 構造体
struct param_list {
	int mode;
	char *infile;
	char *in_dbfile;
	char *out_dbfile;
}

// 引数チェック関数
int check_argc(int argc, char *argv[], struct param_list *plist) {
	int ret = FAILURE;
	int i;
	plist->mode = MODE_NOTSET;
	
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-i") == 0) {
			if (plist->mode != MODE_NOTSET) {
				goto end;
			}
			plist->mode = MODE_INPUT;
			if (i++ >= argc) {
				goto end;
			}
			plist->infile = argv[i];
		} else if (strcmp(argv[i], "-r") == 0) {
			if (plist->mode != MODE_NOTSET) {
				goto end;
			}
			plist->mode = MODE_DISPLAY;
			if (i++ >= argc) {
				goto end;
			}
			plist->in_dbfile = argv[i];
		} else if (strcmp(argv[i], "-o") == 0) {
			if (i++ >= argc) {
				goto end;
			}
			plist->out_dbfile = argv[i];
		} else {
			goto end;
		}
	}

	// モードチェック
	if (plist->mode == MODE_DISPLAY && plist->out_dbfile) {
		goto end;
	}

	ret = SUCCESS;
	
end:
	fprintf(stderr, "usage: wcount [-o database] -i infile\n"
					"		wcount -r database\n");
	return ret;
}

// main関数
int main(int argc, char *argv[]) {
	struct param_list plist = {0};

	if (check_argc(argc, argv, &plist) != SUCCESS) {
		return FAILURE;
	}

// 	FILE *fp;	
	// if ((fp = fopen(argv[2],"r")) == NULL) {
	// 	perror("file open error\n");
	// 	return 1;
// }
// 	count_words(fp);
// 	fclose(fp);
	return SUCCESS;
}