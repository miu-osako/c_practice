#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>

// エラー
#define SUCCESS 0 // 正常終了
#define ERR_PARAM 1 // 引数エラー
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
#define MSG_ERR_PARAM\
		"usage: wcount [-o database] -i infile\n"\
		"		wcount -r database\n" // 引数エラーメッセージ
#define MSG_ERR_OPN_FILE "file open error. [%s][%s]\n" //ファイルオープンエラーメッセージ
#define MSG_ERR_FILE_FORMAT "invalide file format. [%s]\n" //入力ファイルフォーマットエラーメッセージ
#define MSG_ERR_DBFILE_FORMAT "invalide database format. [%s]\n" //databaseファイルフォーマットエラーメッセージ
#define MSG_ERR_MALLOC "memory allocation error.\n" //メモリ確保エラーメッセージ
#define MSG_ERR_SYSTEM "system error.\n" //その他、致命的なエラーメッセージ

//word_data型構造体
typedef struct word_data_t {
	char *word;
	int count;
	struct word_data_t *next;
} word_data;

//insert_into_listのプロトタイプ宣言
int insert_into_list(word_data **head, const char *input);

//入力ファイルを処理する関数
int read_infile(const char *filename, word_data **head, FILE **fp) {
	char buffer[MAX_INFILE_ROW_LENGTH];
	int file_close_status;
		
	if (filename == NULL || head == NULL) {
		return ERR_PARAM;
	}

	if ((*fp = fopen(filename,"r")) == NULL) {
		fprintf(stderr, MSG_ERR_OPN_FILE, filename, strerror(errno));
		return ERR_OPN_FILE;
	}

	while(fscanf(*fp, "%s", buffer) == 1) {
		insert_into_list(head, buffer);
	}

	file_close_status = fclose(*fp);
	if (file_close_status != 0) {
		return ERR_PARAM;
	}

	return SUCCESS;	
}

//リストに単語を入れる関数
int insert_into_list(word_data **head, const char *input) {
	word_data *current = *head;
	
	if (!input) {
		return ERR_PARAM;
	}
	
	word_data *new_node = (word_data *)malloc(sizeof(word_data));
    if (!new_node) {
        return ERR_MALLOC;
    }

    new_node->word = strdup(input);
    if (new_node->word == NULL) {
        free(new_node);
        return ERR_MALLOC;
    }

    new_node->count = 1;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return SUCCESS;
    }

    if (strcmp(new_node->word, (*head)->word) < 0) {
        new_node->next = *head;
        *head = new_node;
        return SUCCESS;
    }

    while (current->next != NULL && strcmp(new_node->word, current->next->word) > 0) {
        current = current->next;
    }

    new_node->next = current->next;
    current->next = new_node;

    return SUCCESS; 
}

//リストの内容を表示する関数
void print_list(word_data *head) {
	while (head != NULL) {
		printf("%-20s%10d\n", head->word, head->count);
		head = head->next;
	}
}

//リストを解放する関数
void free_list(word_data *head) {
	word_data *current = head;
	while (current != NULL) {
		word_data *next = current->next;
		free(current);
		current = next;
	}
}

// param_list 構造体
struct param_list {
	int mode;
	char *infile;
	char *in_dbfile;
	char *out_dbfile;
};

// 引数チェック関数
int check_argc(int argc, char *argv[], struct param_list *plist) {
	int i, ret = ERR_PARAM;
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

	//モードチェック
	if (plist->mode == MODE_NOTSET) {
		goto end;
	}
	if (plist->mode == MODE_DISPLAY && plist->out_dbfile) {
		goto end;
	}

	ret = SUCCESS;
	
end:
	if (ret != SUCCESS) {
		fprintf(stderr, MSG_ERR_PARAM);
	}
	
	return ret;
}

// main関数
int main(int argc, char *argv[]) {
	struct param_list plist = {0};
	word_data *head = NULL;
	FILE *fp;
	int rc = SUCCESS;

	if (check_argc(argc, argv, &plist) != SUCCESS) {
		return ERR_PARAM;
	}

	if (read_infile(plist.infile, &head, &fp) != SUCCESS) {
		return errno;
	}

	print_list(head);
	free_list(head);

	return rc;
}
