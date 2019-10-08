/*        my_algorithm.h         */
/*  implement algorithm learned in Introduction to Algorithms 3e   */

#include <iterator>
#include <functional>  
#include <cstddef>    // for size_t and ptrdiff_t
#include <cstdlib>    // for srand();
#include <ctime>      // for rand();
#include <algorithm>  // for iter_swap();
#include <cmath>      // for pow();

/***************************  Insortion-sort: 插入排序法: 要求随机存取迭代器 *******************************/

template <typename RandomAccessIterator, typename CompareType=std::less<typename std::iterator_traits<RandomAccessIterator>::value_type> >
void insert_sort(RandomAccessIterator begin, RandomAccessIterator end, CompareType compare=CompareType() )
{
 
    for ( auto item = begin+1; item != end; ++item ) // 从第二个元素开始插入排序
    {
        auto value = *item; // 取出需要插入排序的值
    
        // 寻找插入位置
        auto test = item-1;  // 第一个需要比较的迭代器在其前一个位置
        while ( test >= begin && compare( value, *test) ) // 若未遍历需要比较的元素，并且当前迭代器指向的元素比要插入的大，需要继续向前比较
        {
            *(test+1) = *test;  // 将迭代器指向的元素向后移动
            --test;             // 前移迭代器
        }
        *(test+1) = value;  // 找到需要插入的位置，置入需要插入的元素
    }
    return ;
}

/* ******************************************************************************************************** */



/***************************** Merge-sort 归并排序法 : 要求随机存取迭代器 ********************************* */

template<typename RandomAccessIterator>
void merge_sort(RandomAccessIterator begin, RandomAccessIterator end)
{
    if (begin+1 == end) // 若只有一个元素,则不必排序
        return;
    auto num = end - begin;  // 元素个数
    merge_sort(begin, begin+num/2); // 左递归
    merge_sort(begin+num/2, end);   // 右递归
       
    // 两个排序好的数列进行合并操作
    typename std::iterator_traits<RandomAccessIterator>::value_type temp[num]; //临时数组，存放排序结果
    RandomAccessIterator middle_change  = begin + num/2;
    RandomAccessIterator middle_copy    = middle_change;
    RandomAccessIterator begin_copy     = begin;
    RandomAccessIterator end_copy       = end;
    int index = 0;  // 比较连个数列的最小值，放入结果数组中
    while (begin != middle_copy && middle_change != end )
    {
       if ( *begin < *middle_change )
       {
           temp[index++] = *(begin++);
       }
       else
       {
           temp[index++] = *(middle_change++);
       } 
    }
    // 若左数组有余
    while (begin != middle_copy)
    {
        temp[index++] =*(begin++);
    }
    // 若右数组有余
    while ( middle_change != end )
    {
        temp[index++] = *(middle_change++);
    }
    // 拷贝回原空间
    for ( auto item : temp)
    {
        *(begin_copy++) = item;
    }
    
}

/* ******************************************************************************************************** */




/* ******************************* Heap-sort 堆排序：要求输入迭代器 *************************************** */

// 该函数保持以index为根的“最大堆”性质
template <class T>
void keep_max_heap(T* arr_pointer,int index,int num)
{
    int lChild_index = index * 2; // 左孩子
    int rChild_index = lChild_index + 1; // 右孩子
    int largest;   
    // 若左孩子大于定点
    if ( lChild_index <= num && arr_pointer[lChild_index] > arr_pointer[index] )
        largest = lChild_index;
    else
        largest = index;
    // 若右孩子大于左孩子和父节点
    if ( rChild_index <= num && arr_pointer[rChild_index] > arr_pointer[largest] )
        largest = rChild_index;
    // 若最大节点非父节点，进行交换，并对该孩子节点递归
    if ( largest != index )
    {
        T temp = arr_pointer[largest];
        arr_pointer[largest] = arr_pointer[index];
        arr_pointer[index]  = temp;
        keep_max_heap(arr_pointer,largest,num);
    }             
}

//  堆排序主函数
template <class Iterator>
void heap_sort(Iterator begin,Iterator end)
{
    ptrdiff_t num =0; // 元素个数
    for (auto item = begin; item != end; ++item)
        num++;    

    
    auto begin_copy = begin;
    typename std::iterator_traits<Iterator>::value_type arr[num + 1]; // 放在数组中进行排序，个数多1，因为不打算使用 arr[0]
    
    
    // 拷贝到该数组
    for (int i = 1; i < num + 1; ++i )
    {
        arr[i] = *(begin_copy++);
    } 

    // 建立“最大堆”，从第一个非叶节点开始
    for ( int i = num/2; i > 0; --i)
    {
        keep_max_heap(arr,i,num);
    }
    // 排序:首尾互换，并对头节点调用keep_max_heap()，在调用中数组数量应该减一
    for (int i = num; i > 1; --i )
    {
        auto temp = arr[1];
        arr[1] = arr[i];
        arr[i] = temp;
       keep_max_heap(arr,1,i-1);
    }

    // 拷贝回空间
    int index = 0;
    for (; begin != end; ++begin)
    {
        *begin = arr[++index];
    }
}

/* ******************************************************************************************************** */


/* ****************************** Quick-sort 快速排序:要求随机存取迭代器 ********************************** */

// randomized_partition 划分操作
template <class Iterator>
Iterator randomized_partition(Iterator begin,Iterator end)
{
    auto num = end - begin;
    srand(time(NULL));
    auto index = rand()%(num);   // 随机取为 pivot(主元) 
    
    // 与第一个元素交换
    std::iter_swap(begin,begin+index);

    // 开始划分
    auto value = *begin;
    Iterator result = begin; // 排列后，pviot 存在这里
    for (auto item = begin + 1; item < end; ++item) // 检查元素，小于pviot的值存在从第二个元素开始的区间中
    {
        if  ( *item <= value )
        {
            std::iter_swap(item,++result);
        }
    }
    std::iter_swap(result,begin);
    return result;
}

// 快排
template <class Iterator>
void quick_sort(Iterator first,Iterator last)
{
    if (first < last-1 )
    {
        Iterator div = randomized_partition(first,last);
        quick_sort( first, div );
        quick_sort( div + 1, last );
    }
}

/* ******************************************************************************************************** */


/* ××*************************** Counting-sort 计数排序: 要求随机存取迭代器 ******************************* */


// 通常作为 Radix-sort 的基石，不直接使用
template <class Iterator>
void counting_sort(Iterator begin, Iterator end,int bits) // bits 指此次要比较的是哪一位
{
    auto num = end - begin; // 元素个数

    const int max = 9;    

    // 临时数组用来存取小于i的元素个数
    int arr[max+1] = {}; // 零初始化
    
    int div_num = pow(10,bits-1);

    // arr[i] 初始化为 i 元素个数
    for (auto item = begin; item != end; ++item )
    {
        ++arr[  ( *item / div_num ) % 10];
    }
   
    // arr[i] 为小于 i 的元素个数
    for (int i = 1; i < max +1; ++i )
        arr[i] += arr[i-1];

    // 	排序，结果放在result中 
    typename std::iterator_traits<Iterator>::value_type result[num];
    for (auto item = end -1; item >= begin; --item )
    {
        result[arr[ (*item/div_num ) % 10]-1] = *item;
        --arr[ (*item/div_num) % 10];
    }

    // 拷贝回原位置
    for (auto it : result )
        *(begin++) = it;

}

/* ******************************************************************************************************** */


/* ****************************** Radix-sort 基数排序: 要求随机存取迭代器  ******************************* */

template <class Iterator>
void radix_sort(Iterator begin, Iterator end)
{
    // 求取元素的最大位数
    auto max = *begin;
    for (auto item = begin+1; item != end; ++item )
        if (*item > max)
            max = *item;

    int bits = 1; // 位数初始化为1；
    // 计算位数
    max /= 10;
    while ( max != 0 )
    {
        ++bits;
        max /= 10;
    }

    // 每一位调用 计数排序
    for (int bit = 1; bit <= bits; ++bit)
        counting_sort(begin,end,bit);
}

/* ******************************************************************************************************** */

/* *************************************** Shell-sort 希尔排序: *********************************************** */

template <class Iterator>
void shell_sort(Iterator begin,Iterator end)
{
   auto increment = end - begin; 
   do 
   {
       increment = increment/3 + 1; // 设置增量
       for (auto item = begin + increment; item < end; ++item )
       {
           if ( *item < *(item - increment))
           {
               std::iter_swap(item,item - increment);
               for (auto it = item-2*increment; it >= begin && *it > *(it + increment); it -=increment )
                   std::iter_swap(it,it + increment);
           }
       }
       
   }while ( increment > 1);

}

/* ******************************************************************************************************** */








