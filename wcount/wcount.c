#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <arpa/inet.h>

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
#define MSG_ERR_FILE_FORMAT "invalid file format. [%s]\n" //入力ファイルフォーマットエラーメッセージ
#define MSG_ERR_DBFILE_FORMAT "invalid database format. [%s]\n" //databaseファイルフォーマットエラーメッセージ
#define MSG_ERR_MALLOC "memory allocation error.\n" //メモリ確保エラーメッセージ
#define MSG_ERR_SYSTEM "system error.\n" //その他、致命的なエラーメッセージ

// word_data型構造体
typedef struct word_data_t {
	char *word;
	int count;
	struct word_data_t *next;
} word_data;

// input_word_data構造体
typedef struct input_word_data_t {
	word_data *head;
} input_word_data;

// param_list 構造体
struct param_list {
	int mode;
	char *infile;
	char *display_dbfile;
	char *dbfile;
};

// リストに単語を入れる関数
int insert_into_list(word_data *head, const char *input, int count)
{
	word_data *current = head;
	
	if (!input) {
		return ERR_PARAM;
	}
	
	while (current->next != NULL) {
		if (strcmp(current->next->word, input) == 0) {
			current->next->count += count;
			return SUCCESS;
		} else if (strcmp(current->next->word, input) > 0) {
			break;
		}
		current  = current->next;
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
	
	new_node->count = 0 + count;
	new_node->next = current->next;
	current->next = new_node;
	
	return SUCCESS;
}

// リストの内容を表示する関数
void print_list(const word_data *head)
{
	word_data *current = head->next;

	while (current != NULL) {
		printf("%-20s %d\n", current->word, current->count);
		current = current->next;
	}
}

// リストを解放する関数
void free_list(word_data *head)
{
	word_data *current = head->next;

	while (current != NULL) {
		word_data *next = current->next;
		free(current->word);
		free(current);
		current = next;
	}
}

// 入力ファイルを処理する関数
int read_infile(const char *filename, word_data *head)
{
	char buffer[MAX_INFILE_ROW_LENGTH];
	FILE *fp;
	int rc = SUCCESS;
	
	if ((fp = fopen(filename, "r")) == NULL) {
		rc = ERR_OPN_FILE;
		goto end;
	}

	// 最終的にはfreadを使う
	while (fscanf(fp, "%s", buffer) == 1) {
		if ((rc = insert_into_list(head, buffer, 1)) != SUCCESS) {
			goto end;
		}
	}

	if (ferror(fp)) {
		rc = ERR_SYSTEM;
		goto end;
	}
	
end:
	if (fp && fclose(fp)) {
		rc = ERR_SYSTEM;
	}

	return rc;	
}

// databaseにファイル書込みする関数
int write_to_database(const char *filename, const word_data *head)
{
	int length, int_big_endian, rc = SUCCESS;
	word_data *current = head->next;
	FILE *fp;
	size_t size;
	
	if ((fp = fopen(filename, "wb")) == NULL) {
		rc = ERR_OPN_FILE;
		goto end;
	}

	while (current != NULL) {
		length = strlen(current->word) + 1;
		int_big_endian = htonl(length); // host_to_network_long(int)
		size = fwrite(&int_big_endian, sizeof(int), 1, fp);
		if (size < 1) {
			rc = ERR_SYSTEM;
			goto end;
		}

		size = fwrite(current->word, sizeof(char), length, fp);
		if (size < length) {
			rc = ERR_SYSTEM;
			goto end;
		}

		int_big_endian = htonl(current->count);
		size = fwrite(&int_big_endian, sizeof(int), 1, fp);
		if (size < 1) {
			rc = ERR_SYSTEM;
			goto end;
		}
		current = current->next;
	}

end:
	if (fp && fclose(fp)) {
		rc = ERR_SYSTEM;
	}

	return rc;
}

// databaseからファイル読込する関数
int read_from_database(const char *filename, word_data *head)
{
	char buffer[MAX_INFILE_ROW_LENGTH];
	FILE *fp;
	int length, count, int_big_endian, rc = SUCCESS;
	size_t size;	
	
	if ((fp = fopen(filename, "rb")) == NULL) {
		rc = ERR_OPN_FILE;
		goto end;
	}
	
	for (;;) {
		size = fread(&int_big_endian, 1, sizeof(int), fp);
		if (size < sizeof(int)) {
			if (size == 0) {
				if (feof(fp) == 0) {
					rc = ERR_SYSTEM;
				} else {
					rc = SUCCESS; // 正常系
				}
			} else {
				rc = ERR_DBFILE_FORMAT;
			}
			goto end;
		}
		
		length = ntohl(int_big_endian);
		if (length <= 0 || length > MAX_INFILE_ROW_LENGTH) {
			rc = ERR_DBFILE_FORMAT;
			goto end;
		}
		
		size = fread(buffer, sizeof(char), length, fp);
		if (size != length) {
			rc = ERR_DBFILE_FORMAT;
			goto end;
		}

		size = fread(&int_big_endian, 1, sizeof(int), fp);
		if (size < sizeof(int)) {
			if (size == 0) {
				if (feof(fp) == 0) {
					rc = ERR_SYSTEM;
				} else {
					rc = ERR_DBFILE_FORMAT;
				}
			} else {
				rc = ERR_SYSTEM;
			}
			goto end;
		}

		count = ntohl(int_big_endian);
		
		rc = insert_into_list(head, buffer, count);
		if (rc != SUCCESS) {
			goto end;
		}
	}

	if (ferror(fp)) {
		rc = ERR_SYSTEM;
		goto end;
	}
	
end:
	if (fp && fclose(fp)) {
		rc = ERR_SYSTEM;
	}

	return rc;
}

// 引数チェック関数
int check_argc(int argc, char *argv[], struct param_list *plist)
{
	int i, rc = ERR_PARAM;
	plist->mode = MODE_NOTSET;
	
	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "-i") == 0) {
			if (plist->mode != MODE_NOTSET) {
				goto end;
			}
			plist->mode = MODE_INPUT;
			if (++i >= argc) {
				goto end;
			}
			plist->infile = argv[i];
		} else if (strcmp(argv[i], "-r") == 0) {
			if (plist->mode != MODE_NOTSET) {
				goto end;
			}
			plist->mode = MODE_DISPLAY;
			if (++i >= argc) {
				goto end;
			}
			plist->display_dbfile = argv[i];
		} else if (strcmp(argv[i], "-o") == 0) {
			if (++i >= argc) {
				goto end;
			}
			plist->dbfile = argv[i];
		} else {
			goto end;
		}
	}

	// モードチェック
	if (plist->mode == MODE_NOTSET) {
		goto end;
	}
	if (plist->mode == MODE_DISPLAY && plist->dbfile) {
		goto end;
	}

	rc = SUCCESS;
	
end:
	return rc;
}

void print_error(int rc, const char *filename)
{
	switch (rc) {
		case SUCCESS:
			break;
		case ERR_PARAM:
			fprintf(stderr, MSG_ERR_PARAM);
			break;
		case ERR_OPN_FILE:
			fprintf(stderr, MSG_ERR_OPN_FILE, filename, strerror(errno));
			break;
		case ERR_FILE_FORMAT:
			fprintf(stderr, MSG_ERR_FILE_FORMAT, filename);
			break;
		case ERR_DBFILE_FORMAT:
			fprintf(stderr, MSG_ERR_DBFILE_FORMAT, filename);
			break;
		case ERR_MALLOC:
			fprintf(stderr, MSG_ERR_MALLOC);
			break;
		case ERR_SYSTEM:
			fprintf(stderr, MSG_ERR_SYSTEM);
			break;
		// defineで定義
		default:
			fprintf(stderr, "Error: Unhandled error code %d.\n", rc);
			break;
	}
}

// main関数
int main(int argc, char *argv[])
{
	struct param_list plist = {0};
	word_data head = {0};
	int rc;

	if ((rc = check_argc(argc, argv, &plist)) != SUCCESS) {
		goto end;
	}

	// 入力モード
	if (plist.mode == MODE_INPUT) {
		// DBファイル読込
		if (plist.dbfile) {
			if ((rc = read_from_database(plist.dbfile, &head)) != SUCCESS) {
				if (errno == ENOENT) {
					// ファイルが存在しない場合処理を正常に継続
				} else {
					goto end;
				}
			}
		}
		
		if ((rc = read_infile(plist.infile, &head)) != SUCCESS) { // 入力ファイル読込
			goto end;
		}
		
		if (plist.dbfile) { // DBファイル書込
			if ((rc = write_to_database(plist.dbfile, &head)) != SUCCESS) {
				goto end;
			}

		} else { // 標準出力表示
			print_list(&head);
		}

	// DB表示モード
	} else {
		// DBファイル読込
		if ((rc = read_from_database(plist.display_dbfile, &head)) != SUCCESS) {
			goto end;
		}

		// 標準出力表示
		print_list(&head);
	}

end:
	free_list(&head);
	print_error(rc, plist.infile);
	return rc;
}
