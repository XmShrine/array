#include "array.h"
int print_int_array(array* arr) {
    if (!arr || array_is_empty(arr) || array_size(arr)!=sizeof(int)) {
        return -1;
    }
    printf("[");
    for (size_t i=0; i<array_len(arr); i++) {
        printf("%d,", array_fetch_deref(arr, i, int));
    }
    printf("\b \b]\n");
    return 0;
}
int main() {
    array* example = array_init(sizeof(int)); // 创建 array* 指针类型，并使用 array_init(int) 初始化，参数为数组类型的 sizeof
    array_push_back(example); // 使用 push_back / push_front 向数组后或前添加元素
    array_push_front(example);
    array_insert(example, 2); // 把第 [2] 个元素（实际第 3 个）及后面元素往后挪一位，并在 [2] 位（实际第 3 个）创建新元素， 第 [2] 个（实际第 3 个）前的元素不变
    array_remove(example, 1); // 删除第 [n] 个元素（实际第 n+1 个）
    array* copy_example = array_copy(example); // array_copy(array*) 可以深拷贝一个 array 指针
    array_clear(example); // 清空数组内元素
    int example_natural_arr[] = {1,2,4,5}; // 该类型我称其为 nar: natural array
    array_drop(&example); // 构析 array 与 C++ 类似，删除该指针，请谨慎使用，这个要求传入一个 array** 类型，所以要注意
    example = array_from_nar(example_natural_arr, sizeof(int), sizeof(example_natural_arr)/sizeof(*example_natural_arr));
    // 这个函数可以让自然数组转换为 array 类型的指针，也是 array 初始化的一种方法，注意，这是初始化方法，不是改变原有指针的内容，所以一定要先 drop array 在 init array
    // 现在来尝试看看这个数组内的内容是否可以正常显示
    print_int_array(example); // 显示数组
    // 重复最开始的几个操作，看看是否有效成功
    array_remove(example, 1); // 删除第 [n] 个元素（实际第 n+1 个）
    print_int_array(example); // 显示数组
    // 再给出一个函数 array_into_nar 这个函数只需传入一个 array 指针，返回的一个全新的自然指针（值与值对应）
    int* new_example = array_into_nar(example);
    // 读者可自证函数准确性
    // array_is_empty 是检查数组长度是否为 0 的函数，返回 1 为空， 返回 0 显示不空
    // array_move(array* arr, size_t num1, size_t num2) 该函数是交换两位置的值
    // array_len 是查看数组长度，array_size 查看数组数据类型自身的长度相当于 sizeof(int)
    void* ptr = array_fetch(example, 1); // 该函数取回数组 [n] 项处的追针
    int var = array_fetch_deref(example, 1); // 该函数返回数组 [n] 项处的值，但需要指明数据类型
    // 以上是 array 使用的基本教程，剩余还有些函数，请读者自行使用，另外顶上的 print_int_array 函数就是一个良好使用 array 库的函数
}

/*  函数一览表
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
*/