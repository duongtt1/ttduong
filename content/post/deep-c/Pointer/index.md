---
title: Pointer
subtitle: 

# Summary for listings and search engines
summary: Con trỏ là một khái niệm cơ bản ở trong lập trình C/C++, để trở thành một lập trình viên C/C++ giỏi thì việc hiểu rõ về con trỏ là một yêu cầu bắt buộc. Ở bài viết lần này chúng ta sẽ cùng đi tìm hiểu các khái niệm cơ bản của con trỏ.

# Link this post with a project
projects: []

# Date published
date: "2022-09-18T00:00:00Z"

# Date updated
lastmod: "2022-09-18T00:00:00Z"

# Is this an unpublished draft?
draft: false

# Show this page in the Featured widget?
featured: false

# Featured image
# Place an image named `featured.jpg/png` in this page's folder and customize its options here.
image:
  caption: 'Image credit: [**imgur.com**](https://i.imgur.com/cdYTRZi.jpeg)'
  focal_point: ""
  placement: 2
  preview_only: false

authors:
- admin

tags:
- C

categories:
- C
---

>Con trỏ là một khái niệm cơ bản ở trong lập trình C/C++, để trở thành một lập trình viên C/C++ giỏi thì việc hiểu rõ về con trỏ là một yêu cầu bắt buộc. Ở bài viết lần này chúng ta sẽ cùng đi tìm hiểu các khái niệm cơ bản của con trỏ.

## **Con trỏ là gì ?**

Con trỏ là 1 biến.Ý tưởng của con trỏ rất đơn giản nó đơn thuần chỉ là 1 biến và có điều đặc biệt chút ở đây là biến này thay vì lưu các giá trị thông thường sẽ lưu trữ một địa chỉ bộ nhớ thôi. Vì là lưu địa chỉ thôi nên kích thước của con trỏ sẽ bằng kích thước của 1 cell nhớ của RAM vì vậy nên kích thước của con trỏ sẽ tùy thuộc vào kiến trúc phần cứng mà bạn đang sử dụng, nhưng mà phổ biến nhất thì kích thước của con trỏ sẽ là 4 bytes cho nền tảng 32 bits và 8 bytes cho nền tảng 64 bits. Để khai báo con trỏ thì chúng ta cần sử dụng đến ký tự `*` xem như ví dụ ở dưới:

```C
  int pValue = 2;
  int* ptr = 0;
  ptr = &pValue;
  *ptr = 9;
  ptr = NULL
  /*
    ptr = nullptr     // for C++
  */
```

Như đoạn code trên chúng ta khai báo 1 con trỏ `ptr` trỏ đến biến `pValue` thì có ý nghĩa là biến ptr sẽ lưu địa chỉ của biến pValue, để lấy ra địa chỉ của biến pValue thì chúng ta cần thêm ký tự `&`. Tiếp theo để truy cập đến giá trị của địa chỉ mà con trỏ đang nắm giữ thì chúng ta sẽ dùng ký tự `*`, ý của câu lệnh đó là gán giá trị tại địa chỉ mà ptr đang nắm giữ (chính là biến pValue) bằng 9. Sau đó thì chúng ta gán ptr bằng NULL với hàm ý rằng ptr đang không trỏ đến vùng nhớ nào cả. Trong C thì NULL là 1 macro và nó được định nghĩa bằng 0. Trong C++ thì cũng tương tự nhưng mà kể từ C++ 11 trở đi thì đã có 1 key word mới thay thế cho NULL đó là nullptr. nullptr không phải macro được định nghĩa 0 như NULL. nullptr là chính là null, vâng nó là null á, null chính hiệu luôn :)

Trong hầu hết các trình biên dịch hiện đại thì con trỏ khai báo mà chưa khởi tạo thì mặc định sẽ là null điều này có nghĩa là sẽ gán giá trị bằng 0 cho tất cả con trỏ chưa được khởi tạo. Đấy về cơ bản thì cú pháp của con trỏ nó vậy thôi. Tất nhiên là con trỏ nó còn rất nhiều magic nhưng mà khái niệm cơ bản thì mình thấy nó như vậy thôi.

## **Con trỏ void và con trỏ hàm**

Con trỏ void là con trỏ khai báo với kiểu void. Nó có thể nắm giữ bất kỳ địa chỉ bộ nhớ nào giống như các con trỏ khác. Có điều khác nhau là ở chỗ vì là khai báo void nên nó không xác định kiểu dữ liệu.Chúng ta cũng chưa thể sử dụng các toán tử `++`, `--` lên nó được vì nó không có kiểu dữ liệu cơ sở.

Như mình có nói ở trên con trỏ nó có rất nhiều magic, con trỏ hàm cũng là 1 tính năng hay ho của C/C++. Giống như biến con trỏ chứa giá trị là địa chỉ của 1 biến thì hàm con trỏ chứa giá trị là địa chỉ của 1 hàm và cho phép chúng ta có thể gọi hàm đó 1 cách gián tiếp.

```C
#include <stdio.h>
#include <stdbool.h>

bool ascending(int a, int b) { return a > b; }
bool descending(int a, int b) { return a < b; }

void swap(int *x, int *y)
{
    int temp = *x;
    *x = *y;
    *y = temp;
}


void sort_func_ptr(int *arr, int N, int (*func_ptr)(int, int)){
    int i,j;
    for(i=0; i<N-1; ++i){
        for(j=i; j<N; ++j){
            if (func_ptr(arr[i], arr[j])){
                swap(&arr[i], &arr[j]);
            }
        }
    }
}

void print_arr(int *arr, int N){
    for (int i=0; i < N; ++i){
        printf("%d \t", arr[i]);
    }
    printf("\n");
}

int main() {
    bool (*func_ptr)(int, int);
    func_ptr = NULL;
    int N = 5;
    int arr[5] = {1, 9, 5, 6, 4};
    // sort ascending
    func_ptr = &ascending;
    sort_func_ptr(arr, N, func_ptr);
    print_arr(arr, N);
    // sort descending
    func_ptr = &descending;
    sort_func_ptr(arr, N, func_ptr);
    print_arr(arr, N);
    return 0;
}
```

Như đoạn code ví dụ trên chúng ta có thể linh hoạt tùy chọn các hàm để truyền vào đối số cho 1 hàm khác, đó chỉ là 1 ví dụ cho việc sử dụng con trỏ hàm nếu như bạn đọc đã làm quen với lập trình hướng đối tượng thì bằng việc ứng dụng con trỏ hàm chúng ta có thể phần nào triển khai được tính đa hình (polymorphism) và phần nào đó bắt trước hảm ảo (virtual functions) của C++ ở trong C và tất nhiên là cũng giống như con trỏ biến, việc khai báo con trỏ hàm cũng cần được cẩn thận và thực hiện đúng cách nhằm tránh khỏi việc các vấn đề phức tạp về sau.

## **Dangling pointers**

Trong lập trình C/C++ thì thường con trỏ sẽ được trỏ đến địa chỉ của 1 biến đã được cấp phát vùng nhớ, nhưng nếu như con trỏ mà trỏ đến 1 vùng nhớ không hợp lệ và thao tác lên các vùng nhớ không hợp lệ này sẽ gây ra các vấn đề nghiêm trọng, chương trình có thể sẽ crash và ném ra các lỗi liên quan đến  segmentation fault. Đây là 1 trong những lỗi mà mình nghĩ là ai cũng đã từng gặp rồi. Việc truy cập vùng nhớ không hợp lệ thì có rất nhiều trường hợp, lấy ví dụ như đoạn code ở dưới:

```C
#include <stdio.h>

int* make_int(int val) {
  int p = val;
  return &p;
}
int main() {
  int* ptr = NULL;
  ptr = make_int(10);
  printf("%d\n", *ptr);
  return 0;
}
```

Như đoạn code trên chúng ta có thể thấy là chúng ta định nghĩa 1 hàm để tạo ra 1 biến kiểu int, đầu tiên là khai báo 1 con trỏ sau rồi gọi hàm make_int kèm đối số là giá trị muốn khởi tạo, xong rồi vào hàm thì khai báo 1 biến rồi trả về là địa chỉ của biến vừa khởi tạo đó, ở bên ngoài thì gán địa chỉ ptr cho địa chỉ của biến này. Như vậy thì sau khi thực hiện như trên ptr sẽ đang nắm giữ địa chỉ của biến p. Như vậy thì muốn truy cập đến biến p chúng ta có thể sử dụng thông qua con trỏ ptr. hm... trông thì cũng hợp lý và logic đó chứ nhưng mà sự thật thì không. Vấn của đoạn code trên chính là việc khởi tạo biến p ở trong hàm make_int mà chúng ta đã biết rồi, các biến khai báo local trong hàm thì sẽ được cấp phát trên vùng nhớ stack của hàm đó và sau khi đi ra khỏi hàm thì các vùng nhớ này sẽ bị thu hồi. Như vậy thì sau khi đi ra khỏi hàm make_int thì vùng nhớ mà biến p nắm giữ đã bị thu hồi cơ mà theo code trên thì con trỏ ptr lại đang cầm địa chỉ của vùng nhớ đó chính vì thế nên nếu như lúc này chúng ta sử dụng biến ptr để truy xuất vùng nhớ này sẽ là không hợp lệ và chương trình sẽ crash.

Ví dụ trên chỉ là 1 ví dụ đơn giản cho Dangling pointers còn rất nhiều trường hợp nữa là nên khi sử dụng con trỏ thường sẽ có nhiều vấn đề liên quan đến bộ nhớ nên mà các bạn và cả mình nữa nên cẩn thận trong việc sử dụng.

## **Nguồn tham khảo**

- Extreme C - Kamran Amini (PDF Book)
