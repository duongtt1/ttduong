---
title: Tiền xử lý trong C (Phần 2)
subtitle: Qua Phần 1 vừa rồi chúng ta đã tìm hiểu được các kiến thức cơ bản của macro, ở Phần 2 này chúng ta lại tiếp tục đi tìm hiểu thêm về 1 loại macro khác đó là Variadic macros.

# Summary for listings and search engines
summary: Qua Phần 1 vừa rồi chúng ta đã tìm hiểu được các kiến thức cơ bản của macro, ở Phần 2 này chúng ta lại tiếp tục đi tìm hiểu thêm về 1 loại macro khác đó là Variadic macros. 

# Link this post with a project
projects: []

# Date published
date: "2022-04-14T00:00:00Z"

# Date updated
lastmod: "2022-04-14T00:00:00Z"

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

>Nếu bạn chưa đọc Phần 1 thì nên đọc qua phần 1 trước nhé, vì ở phần 1 chúng ta đã đi tìm hiểu khá kỹ lưỡng về macro. Còn nếu bạn không thích đọc Phần 1 thì cũng không sao cả, cứ đọc luôn phần 2 cũng không sao :v

## **Variadic macros**

Tiếp theo chúng ta cùng nhau đi tìm hiểu tiếp về *Variadic macros*, nó cũng là macro thôi nhưng mà điểm hay ho của nó đó là nó có thể nhận vào 1 số lượng đối số không nhất định. Có thể là 2 đối số cũng có thể là 3 hoặc cũng có thể là 8, nhận vào bao nhiêu là tuỳ thuộc vào người sử dụng nó. Cũng nhờ tính chất chất này mà nó rất hữu dụng khi chúng ta cần định nghĩa các macro mà chưa biết được số lượng tham số truyền vào hoặc là số lượng tham số có thể thay đổi tuỳ từng trường hợp. Đoạn code dưới đây là 1 ví dụ:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "1.4.22"
#define AUTHOR "Admin"

#define LOG_ERROR(pfile, format, ...) \
  fprintf(pfile, format, __VA_ARGS__)

int main(int argc, char **argv)
{
    FILE *pf;
    pf = fopen ("log.txt", "a+");
    if(argc != 3){
      LOG_ERROR(pf, "Chỉ nhận 2 tham số đầu vào ====> VERSION: %s\n", VERSION);
      exit(-1);
    }
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    if(y == 0){
      LOG_ERROR(stderr, "Lỗi không thể chia cho 0 ====> VERSION: %s ====> AUTHOR: %s\n", VERSION, AUTHOR);
      exit(-1);
    }
    else
      return x/y;
}
```

Trong ví dụ trên thì có 2 điểm cần lưu ý trong phần định nghĩa của macro như bên, đầu tiên là dấu `...` phần tên của macro, nó là đối số cuối cùng trong định nghĩa macro, thứ 2 là ký tự nhận diện `__VA_ARGS__`, ký tự `__VA_ARGS__` chỉ cho Bộ tiền xử lý biết để thay thế nó bằng toàn bộ các đối số đầu vào còn lại mà chưa được gán cho bất kỳ tham số nào. Các tham số còn lại này chính là những đối số đầu vào được thay thế vào chỗ của đối số `...` trông mình giải thích nó khá là lôi thôi nhỉ :) thôi đi vào ví dụ sẽ dễ hiểu hơn, như định nghĩa trên thì khi chúng ta gọi `LOG_ERROR(pf, "Chỉ nhận 2 tham số đầu vào ====> VERSION: %s\n", VERSION);` thì đối số `pf` tương ứng với tham số `pfile` trong phần định nghĩa, tương tự đối số `format` với đoạn code sau `"Chỉ nhận 2 tham số đầu vào ====> VERSION: %s\n"` *mỗi đối số sẽ phân chia nhau bằng dấu chấm phẩy*, và tất cả các đối số được truyền thêm ở tiếp theo như `VERSION` sẽ tương ứng với `...` và tất cả chúng cũng sẽ được thay thế vào chỗ của `__VA_ARGS__` bao gồm cả dấu chấm phẩy ở giữa. Sau khi thực hiện tiền xử lý thì ví dụ trên sẽ có mã nguồn như sau:

```c
........................
int main(int argc, char **argv)
{
    FILE *pf;
    pf = fopen ("log.txt", "a+");
    if(argc != 3){
      fprintf(pf, "Chỉ nhận 2 tham số đầu vào ====> VERSION: %s\n", "1.4.22");
      exit(-1);
    }
    int x = atoi(argv[1]);
    int y = atoi(argv[2]);
    if(y == 0){
      fprintf(stderr, "Lỗi không thể chia cho 0 ====> VERSION:%s ====> AUTHOR: %s\n", "1.4.22", "Admin");
      exit(-1);
    }
    else
      return x/y;
}
```

aaaaaaaaaaaaaaa

## **Nguồn**

- Extreme C: Taking you to the limit in Concurrency, OOP, and the most advanced capabilities of C 1st Edition - Kamran Amini (PDF Book)
- <https://en.cppreference.com/w/c/preprocessor>
