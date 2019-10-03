﻿#include <stdio.h>
#include <stdlib.h>

#include "header.h"
#include "file.h"
#include "verbose.h"

HEADER_FILE_SIZE_CONTAINER_TYPE_64 GetSizeFileInBytes(FILE* file)
{
	const HEADER_FILE_SIZE_CONTAINER_TYPE_64 save_cursor_pos = ftell(file);
	fseek(file, 0L, SEEK_END);
	const HEADER_FILE_SIZE_CONTAINER_TYPE_64 size = ftell(file);
	fseek(file, 0, save_cursor_pos);
	return size;
}

File* FileLoad(const char* path, char* mode)
{
	File* my_file = (File*)malloc(sizeof(File));
	if (my_file == NULL)
	{
		printf("Error malloc my_file");
		exit(2);
	}
	my_file->file_handler = fopen(path, mode);
	if (my_file->file_handler == NULL)
	{
		printf("Error, %s can't be opened with mode %s\n", path, mode);
		exit(2);
	}
	my_file->size = GetSizeFileInBytes(my_file->file_handler);
	VERBOSE_ON printf("File %s have been opened with mode %s and is weight %lld bytes\n", path, mode, my_file->size);
	return my_file;
}

void FileUnload(File** file_to_delete)
{
	fclose((*file_to_delete)->file_handler);
	file_to_delete == NULL;
}
