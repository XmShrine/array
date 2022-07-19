#ifndef array_h
#define array_h
#define arr_init(type, name) typedef struct {type* data; size_t len;} arr_##name
#include <stdlib.h>
#include <stdio.h>
// nar - natural array
struct array;
typedef struct array array;
array* array_init(size_t size);
array* array_copy(array* arr);
array* array_from_nar(void* ptr, size_t size, size_t len);
int array_is_empty(array* arr);
int array_clear(array* arr);
int array_insert(array* arr, size_t num);
int array_remove(array* arr, size_t num);
int array_drop(array** arr);
int array_move(array* arr, size_t num1, size_t num2);
int array_swap(array* arr, size_t num1, size_t num2);
int array_append(array* arr, array* example);
int array_appfront(array* arr, array* example);
int array_push_back(array* arr); // non-checked
int array_push_front(array* arr); // non-checked
int array_remove_back(array* arr); // non-checked
int array_remove_front(array* arr); // non-checked
int array_add(array* arr, size_t num, size_t time); // non-checked
int array_add_back(array* arr, size_t time); // non-checked
int array_add_front(array* arr, size_t time); // non-checked
void* array_fetch_back(array* arr); // non-checked
void* array_fetch_front(array* arr); // non-checked
void* array_fetch(array* arr, size_t num);
void* array_into_nar(array* arr);
size_t array_len(array* arr);
size_t array_size(array* arr);
#define array_fetch_deref(arr, num, type) *(type*)(array_fetch(arr, num))
#define array_fetch_back_deref(arr, type) *(type*)(array_fetch_back(arr))
#define array_fetch_front_deref(arr, type) *(type*)(array_fetch_front(arr))
#endif
