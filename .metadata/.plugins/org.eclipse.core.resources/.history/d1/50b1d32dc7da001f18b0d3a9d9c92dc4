/*
 * app.c
 *
 *  Created on: Jan 18, 2025
 *      Author: steve
 */

#include "app.h"
#include <stdio.h>
#include <string.h>
#include "fatfs.h"
#define f_unmount(path) f_mount(0, path, 0)

extern UART_HandleTypeDef huart2;

typedef struct {
	TCHAR filename[_MAX_LFN];//_MAX_LFN];
	DWORD size;
	BYTE attribute;
} lfFileInfo;

int getDir(char *path, lfFileInfo *answer) {
	FATFS *fatFs;
	DIR *directoryO;
	FILINFO *fileInfo;
	volatile FRESULT resultF;
	TCHAR lfname[_MAX_LFN];//_MAX_LFN];
	int countFiles = 0;

	char str[13];
	uint32_t freeclusters, freesectors, totalsectors;

	fatFs = malloc(sizeof(FATFS));
	if(fatFs == NULL) while(1);
	directoryO = malloc(sizeof(DIR));
	if(directoryO == NULL) while(1);
	fileInfo = malloc(sizeof(FILINFO));
	if(fileInfo == NULL) while(1);

	/* Mount sdcard. */
	resultF = f_mount(fatFs, "", 1);

	if (resultF == FR_OK) {
		/* read volume label. */
		resultF = f_getlabel("", str, 0);

		if (resultF != FR_OK) {
		}

		/* Read directory contents. */
		resultF = f_opendir(directoryO, path);      // open 'root' directory.
		if (resultF != 0) {
		}

		// long file name
		while (1) {
			//fileInfo->fname = lfname;
			strcpy(fileInfo->fname, lfname);
			fileInfo->fsize = _MAX_LFN - 1;
			resultF = f_readdir(directoryO, fileInfo);
			if (resultF != 0) {
			}

			if (fileInfo->fname[0] == 0) {           // end of directory?
				break;
			}

			strncpy(answer[countFiles].filename,
			        fileInfo->fname[0] ? fileInfo->fname : fileInfo->fname, _MAX_LFN - 1);
			answer[countFiles].size = fileInfo->fsize;
			answer[countFiles].attribute = fileInfo->fattrib;

			countFiles++;
			if (fileInfo->fattrib & AM_DIR) {        // is it a directory?
			} else {                                  // it is a file.
				char size[5];
				if (fileInfo->fsize > 1048575) {
					sprintf(size, "%3ldM", fileInfo->fsize / 1048576);
				} else if (fileInfo->fsize > 1023) {
					sprintf(size, "%3ldK", fileInfo->fsize / 1024);
				} else {
					sprintf(size, "%3ld ", fileInfo->fsize);
				}
			}
		}

		/* get volume bytes info. */
		resultF = f_getfree("", &freeclusters, fatFs);

		if (resultF != FR_OK) {
		}

		totalsectors = (fatFs->n_fatent - 2) * fatFs->csize;
		freesectors = freeclusters * fatFs->csize;

		itoa(totalsectors, str, 10);
		itoa(freesectors, str, 10);
		itoa((totalsectors / 2), str, 10);
		itoa((freesectors / 2), str, 10);

		f_closedir(directoryO);

		// unmount
		resultF = f_mount(NULL, "", 1);
		free(fatFs);
		free(directoryO);
		free(fileInfo);
		if (resultF != FR_OK) {
		}
	}
	return countFiles;
}

void app() {
	// uart 초기화
	initUart(&huart2);
	// fafs 설정
	FATFS		*fatfs;
	FIL			*file;
	FRESULT	fresult;

	// 경로내의 파일 목록 읽기 예제
	int countFiles;
	static lfFileInfo list[100];	// 디렉토리당 최대 파일의 개수
	// 구조체 초기화
	for (int i = 0; i < 6; i++) {
		list[i].filename[0] = 0;
	}
	// 파일 목록 가져오기
	countFiles = getDir("/", list);
	char tmp[20];
	char str[_MAX_LFN];
	// 가져온 파일 목록 인쇄
	for (int i = 0; i < countFiles; i++) {
		if (list[i].filename[0] != 0) { // 파일 이름이 있는 경우
			char sizeString[5];
			// convert size
			if (list[i].size > 1048575) {
				printf(sizeString, "%3dM", list[i].size / 1048576);
			} else if (list[i].size > 1023) {
				printf(sizeString, "%3dK", list[i].size / 1024);
			} else {
				printf(sizeString, "%3d ", list[i].size);
			}
			// convert string
			if (list[i].attribute & AM_DIR) {
				strcpy(tmp, list[i].filename);
				tmp[17] = 0;
				printf(str, " <%s>", tmp);
			} else {
				strcpy(tmp, list[i].filename);
				tmp[15] = 0;
				printf(str, "%-16s-%s", tmp, sizeString);
			}
			printf(str);
		}
	}

	// 파일 읽기 및 쓰기 예제
	char message[100] = {0,};
	unsigned int	writeSize;
	unsigned int	readSize;
	// 메모리 할당
	fatfs = malloc(sizeof(FATFS));
	file = malloc(sizeof(FIL));
	// 디스크 마운트
	f_mount(fatfs, "0:", 0);
	// 파일 읽기
	fresult = f_open(file, "message.txt", FA_READ);
	if(fresult) printf("fail open message.txt\n");
	fresult = f_read(file, message, 100, &readSize);
	if(fresult) printf("fail read\n");
	f_close(file);
	// 파일 쓰기
	fresult = f_open(file, "message2.txt", FA_WRITE | FA_CREATE_ALWAYS);
	if(fresult) printf("fail open message2.txt\n");
	fresult = f_write(file, message, strlen(message), &writeSize);
	if(fresult) printf("fail write\n");
	f_close(file);
	// 디스크 언마운트
	f_unmount("0:");
	while(1) {

	}
}
