#ifndef INDEXARR_H
#define INDEXARR_H
#include "array.h"
#include "fiodata.h"

template<typename Type>
struct IndexElem {
	int index;
	Type znach;
};

template<typename Type>
int addElemInIndexArr(IndexElem<Type>* elem, FILE* arrStream, int(*pcm)(Type*, Type*))
{
	IndexElem<Type> getelem;
	int n = flengthData<IndexElem<Type>>(arrStream);
	for (int i = 0; i < flengthData<IndexElem<Type>>(arrStream); i++)
	{
		freadData(&getelem, i, arrStream);
		if (pcm(&(elem->znach), &getelem.znach) <= 0)
			return inputData(elem, i, arrStream);
	}
	return(fwriteData(elem, 0, arrStream, SEEK_END));
}

template<typename Type>
void addInIndex(FILE* stream, Type znach, int n, int(*cmp)(Type*, Type*))
{
	IndexElem<Type> elem = { n, znach };
	addElemInIndexArr(&elem, stream, cmp);
	fflush(stream);
}


template<typename Type>
void startIndexArray(FILE* arrStream, FILE* stream, FILE* maskArr, int(*pcm)(Type*, Type*))
{
	Type znach;
	IndexElem<Type> elem;
	int mask = 0;
	for (int i = 0; i < flengthData<Type>(stream); i++)
	{
		freadData(&mask, i, maskArr);
		if (mask)
		{
			elem.index = i;
			freadData(&elem.znach, i, stream);
			addElemInIndexArr(&elem, arrStream, pcm);
			fseek(arrStream, 0, SEEK_SET);
		}
	}
}

template<typename Type>
void pinout(IndexElem<Type>* t, void(*pinout(Type*)))
{
	pinout(t->znach);
}
#endif 
