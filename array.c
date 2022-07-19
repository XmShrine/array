#include "array.h"
struct array {
    void* data;
    size_t size;
    size_t len;
};
int mem_copy(void* ptr, void* goal_ptr, size_t len) {
    if (!ptr || !goal_ptr || !len) {
        return -1;
    }
    for (size_t i=0; i<len; i++) {
        *(char*)(goal_ptr + i) = *(char*)(ptr + i);
    }
    return 0;
}
void* mem_dcopy(void* ptr, size_t len) {
    if (!ptr || !len) {
        return NULL;
    }
    void* goal_ptr = malloc(len);
    if (!goal_ptr) {
        return NULL;
    }
    mem_copy(ptr, goal_ptr, len);
    return goal_ptr;
}
int mem_free(void** ptr) {
    if (!ptr || !*ptr) {
        return -1;
    }
    free(*ptr);
    *ptr = NULL;
    return 0;
}
int mem_insert(void** ptr, size_t num, size_t size, size_t len) {
    if (!ptr || !size || num>len) {
        return -1;
    }
    if (!len) {
        if (!num) {
            *ptr = malloc(size);
            return 0;
        } else {
            return -1;
        }
    }
    void* dev = malloc(size*(len + 1));
    mem_copy(*ptr, dev, num * size);
    mem_copy(*ptr + num * size, dev + num * size + size, (len - num) * size);
    mem_free(ptr);
    *ptr = dev;
    return 0;
}
int mem_remove(void** ptr, size_t num, size_t size, size_t len) {
    if (!ptr || !*ptr || !size || !len || num>len) {
        return -1;
    }
    if (!(len - 1)) {
        if (!num) {
            mem_free(*ptr);
            *ptr = NULL;
            return 0;
        } else {
            return -1;
        }
    }
    void* dev = malloc(size*(len - 1));
    mem_copy(*ptr, dev, num * size);
    mem_copy(*ptr + num * size + size, dev + num * size, (len - num - 1) * size);
    mem_free(ptr);
    *ptr = dev;
    return 0;
}
int mem_move(void** ptr, size_t original_num, size_t goal_num, size_t size, size_t len) {
    if (!ptr || !*ptr || !size || !len || original_num>len || goal_num>len || original_num == goal_num) {
        return -1;
    }
    void* temp = malloc(size);
    void* dev = NULL;
    mem_copy(*ptr + size * original_num, temp, size);
    mem_remove(ptr, original_num, size, len);
    len--;
    mem_insert(ptr, goal_num, size, len);
    len++;
    dev = *ptr + goal_num * size;
    mem_copy(temp, dev, size);
    mem_free(&temp);
    return 0;
}
array* array_init(size_t size) {
    if (!size) {
        return NULL;
    }
    array* arr = malloc(sizeof(array));
    if (!arr) {
        return NULL;
    }
    arr->data = NULL;
    arr->size = size;
    arr->len = 0;
    return arr;
}
array* array_copy(array* arr) {
    if (!arr) {
        return NULL;
    }
    if (array_is_empty(arr)) {
        if (arr->size) {
            return array_init(arr->size);
        }
        return NULL;
    }
    array* carr = array_init(arr->size);
    carr->len = arr->len;
    carr->data = mem_dcopy(arr->data, arr->size*arr->len);
    return carr;
}
array* array_from_nar(void* ptr, size_t size, size_t len) {
    if (!ptr || !size) {
        return NULL;
    }
    array* arr = array_init(size);
    arr->data = mem_dcopy(ptr, size*len);
    arr->len = len;
    return arr;
}
int array_is_empty(array* arr) {
    if (!arr) {
        return -1;
    }
    if (!arr->data || !arr->size || !arr->len) {
        return 1;
    }
    return 0;
}
int array_clear(array* arr) {
    if (!arr) {
        return -1;
    }
    if (array_is_empty(arr)) {
        return 0;
    }
    free(arr->data);
    arr->data = NULL;
    return 0;
}
int array_insert(array* arr, size_t num) {
    if (!arr) {
        return -1;
    }
    int result = mem_insert(&arr->data, num, arr->size, arr->len);
    if (!result) {
        arr->len++;
    }
    return result;
}
int array_remove(array* arr, size_t num) {
    if (!arr || num>arr->len-1) {
        return -1;
    }
    int result = mem_remove(&arr->data, num, arr->size, arr->len);
    if (!result) {
        arr->len--;
    }
    return result;
}
int array_drop(array** arr) {
    if (!arr || !*arr) {
        return -1;
    }
    if (array_is_empty(*arr)) {
        return 0;
    }
    free((*arr)->data);
    *arr = NULL;
    return 0;
}
int array_move(array* arr, size_t num1, size_t num2) {
    if (!arr || array_is_empty(arr)) {
        return -1;
    }
    return mem_move(&arr->data, num1, num2, arr->size, arr->len);
}
int array_swap(array* arr, size_t num1, size_t num2) {
    if (!arr || array_is_empty(arr) || num1>=arr->len || num2>=arr->len) {
        return -1;
    }
    void* dev = mem_dcopy(array_fetch(arr, num1), arr->size);
    if (!dev) {
        return -1;
    }
    mem_copy(array_fetch(arr, num2), array_fetch(arr, num1), arr->size);
    mem_copy(dev, array_fetch(arr, num2), arr->size);
    free(dev);
    return 0;
}
int array_append(array* arr, array* example) {
    if (!arr || !example || array_is_empty(example) || arr->size!=example->size) {
        return -1;
    }
    for (size_t i=0; i<array_len(example); i++) {
        array_push_back(arr);
        mem_copy(array_fetch(example, i), array_fetch_back(arr), arr->size);
    }
    return 0;
}
int array_appfront(array* arr, array* example) {
    if (!arr || !example || array_is_empty(example) || arr->size!=example->size) {
        return -1;
    }
    for (size_t i=0; i<array_len(example); i++) {
        array_push_front(arr);
        mem_copy(array_fetch(example, array_len(example)-i-1), array_fetch_front(arr), arr->size);
    }
    return 0;
}
int array_push_back(array* arr) /* non-checked */ {
    if (!arr) {
        return -1;
    }
    return array_insert(arr, arr->len);
}
int array_push_front(array* arr) /* non-checked */ {
    return array_insert(arr, 0);
}
int array_remove_back(array* arr) /* non-checked */ {
    if (!arr) {
        return -1;
    }
    return array_remove(arr, arr->len-1);
}
int array_remove_front(array* arr) /* non-checked */ {
    return array_remove(arr, 0);
}
int array_add(array* arr, size_t num, size_t time) /* non-checked */ {
    int result = 0;
    for (size_t i=0; i<time; i++) {
        result = array_insert(arr, num);
    }
    return result;
}
int array_add_back(array* arr, size_t time) /* non-checked */ {
    if (!arr) {
        return -1;
    }
    return array_add(arr, arr->len, time);
}
int array_add_front(array* arr, size_t time) /* non-checked */ {
    return array_add(arr, 0, time);
}
void* array_fetch_back(array* arr) /* non-checked */ {
    if (!arr) {
        return NULL;
    }
    return array_fetch(arr, arr->len-1);
}
void* array_fetch_front(array* arr) /* non-checked*/ {
    return array_fetch(arr, 0);
}
void* array_fetch(array* arr, size_t num) {
    if (!arr || num>=arr->len || array_is_empty(arr)) {
        return NULL;
    }
    return arr->data+arr->size*num;
}
void* array_into_nar(array* arr) {
    if (!arr || array_is_empty(arr)) {
        return NULL;
    }
    return mem_dcopy(arr->data, arr->size*arr->len);
}
size_t array_len(array* arr) {
    if (!arr || array_is_empty(arr)) {
        return 0;
    }
    return arr->len;
}
size_t array_size(array* arr) {
    if (!arr) {
        return 0;
    }
    return arr->size;
}
