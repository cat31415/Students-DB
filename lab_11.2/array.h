#ifndef ARRAY_H
#define ARRAY_H
template <typename Type>
struct Array
{
	Type* arr;
	int count;
};

template<typename Type>
Array<Type> allocArray(int n)
{
	Array<Type> a = { new Type[n], n };
	return a;
}

template <typename Type>
Array<Type> inputArray(Type(*pinput)())
{
	printf("Write amount of data: ");
	int n;
	scanf_s("%d", &n);

	Array<Type> ar = allocArray<Type>(n);
	printf("Write data: \n");
	for (int i = 0; i < n; ar.arr[i++] = pinput());

	return ar;
}

template<typename Type>
void outputArray(Array<Type>* ar, void(*pinout)(Type* t), int c = 0)
{
	for (int i = 0; i < ar->count; pinout(ar->arr + i++))
		if (c) printf("%d. ", i);
}

template<typename Type>
void freeArray(Array<Type>* ar)
{
	delete[] ar->arr;

	ar->arr = 0;
	ar->count = 0;
}

#endif