#ifndef FIODATA_H
#define FIODATA_H
# include <stdio.h>
# include <io.h>
# include "array.h"

template<typename Type>
int freadArray(Type* arr, size_t size, FILE* stream)
{
	return fread(arr, sizeof(Type), size, stream);
}

template<typename Type>
int freadArray(Array<Type>* ar, FILE* stream)
{
	return freadArray(ar->arr, ar->count, stream);
}

template<typename Type>
int fwriteArray(Type* arr, size_t size, FILE* stream)
{
	return fwrite(arr, sizeof(Type), size, stream);
}

template<typename Type>
int fwriteArray(Array<Type>* ar, FILE* stream)
{
	return fwriteArray(ar->arr, ar->count, stream);
}

template<typename Type>
int freadData(Type* data, long pos, FILE* stream, int orign = SEEK_SET)
{
	return fseek(stream, sizeof(Type) * pos, orign) ? 0 : fread(data, sizeof(Type), 1, stream);
}

template<typename Type>
int fwriteData(Type* data, long pos, FILE* stream, int orign = SEEK_SET)
{
	return fseek(stream, sizeof(Type) * pos, orign) ? 0 : fwrite(data, sizeof(Type), 1, stream);
}

template <typename Type>
long flengthData(FILE* stream)
{
	return _filelength(_fileno(stream)) / sizeof(Type);
}

template <typename Type>
int fchangesizeData(FILE* stream, long size)
{
	return !chsize(fileno(stream), size * sizeof(Type));
}

template <typename Type>
void swap(Type& d1, Type& d2)
{
	Type temp = d1; d1 = d2; d2 = temp;
}

template<typename Type>
void consoletoFile(FILE* stream, Type(*pinin)(), int orign = SEEK_SET)
{
	Array<Type> ar = inputArray(pinin);
	fseek(stream, 0, orign);
	fwriteArray(&ar, stream);
	freeArray(&ar);
}

template <typename Type>
void filetoConsole(FILE* stream, void (*poutput)(Type*), int orign = SEEK_SET, int c = 0)
{
	Type data;
	int i = 0;
	if (freadData(&data, 0, stream, orign))
	{
		do {
			if (c) printf("%d. ", i++);
		} while (poutput(&data), freadArray(&data, 1, stream));
	}
}

template<typename Type>
int inputData(Type* data, long pos, FILE* stream, int orign = SEEK_SET)
{
	fseek(stream, sizeof(Type) * pos, orign);
	int n = flengthData<Type>(stream) + 1 - pos;
	Type* arr = new Type[n];
	arr[0] = *data;
	fseek(stream, sizeof(Type) * pos, orign);
	freadArray(arr + 1, n - 1, stream);
	fseek(stream, sizeof(Type) * pos, orign);
	return fwriteArray(arr, n, stream);
}

template<typename Type>
void dellDataFast(FILE* stream, long pos, int orign = SEEK_SET)
{
	Type temp = 0;
	freadData(&temp, 0, stream, SEEK_END);
	fwriteData(temp, pos, stream, orign);
	Type zero = 0;
	fwriteData(&zero, 0, stream, SEEK_END);
}

template<typename Type>
void dellData(FILE* stream, long pos, int orign = SEEK_SET)
{
	Type* temp = 0;
	fseek(stream, pos + 1, orign);
	freadArray(temp, stream);
	inputData(temp, pos, stream, orign);
	Type zero = 0;
	fwriteData(&zero, 0, stream, SEEK_END);
}


#endif