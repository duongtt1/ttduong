---
title: Tiền xử lý trong C (Phần 1)
subtitle: Tiền xử lý là 1 tính năng mạnh mẽ của ngôn ngữ lập trình C, nhờ tính năng này là các lập trình viên có thể sửa đổi mã nguồn trước khi chúng được chuyển đến cho compiler.

# Summary for listings and search engines
summary: Tiền xử lý là 1 tính năng mạnh mẽ của ngôn ngữ lập trình C, nhờ tính năng này là các lập trình viên có thể sửa đổi mã nguồn trước khi chúng được chuyển đến cho compiler. 

# Link this post with a project
projects: []

# Date published
date: "2022-04-13T00:00:00Z"

# Date updated
lastmod: "2022-04-13T00:00:00Z"

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

>Bài viết này mình ghi chú lại khi tìm hiểu về macros ở trong C, trước khi đọc bài này thì mình nghĩ là bạn đọc nên có kiến thức cơ bản về C là tối ưu nhất, còn nếu bạn chưa biết gì về C thì cũng không sao, bạn có thể đọc qua rồi sau này gặp thì áp dụng cũng được ^^

## **Chỉ thị tiền xử lý (preprocessor directives)**

Tiền xử lý là 1 tính năng mạnh mẽ của ngôn ngữ lập trình C, nhờ tính năng này là các lập trình viên có thể sửa đổi mã nguồn trước khi chúng được chuyển đến cho compiler. Bước tiền xử lý này cũng là bước được xử lý đặc biệt của C và C++ mà lại không có ở hầu hết các ngôn ngữ bậc cao hiện nay.

Chỉ thị tiền xử lý là các chỉ thị (lệnh) được cung cấp cho bộ tiền xử lý để xử lý mã nguồn trước khi gửi mã nguồn đi đến compiler. Các chỉ thị này thì sẽ bắt đầu với dấu `#` ở đầu. Bản thân compiler cũng không hiểu các chỉ thị này, mà các chỉ thị này sẽ được xử lý trực tiếp ở Bộ tiền xử lý, sau khi Bộ tiền xử lý đã xử lý xong hết các chỉ thị xuất hiện trong cả file header và file source thì lúc này source code hoàn chỉnh mới được gửi đến cho compiler.

Trong C có khá nhiều loại chỉ thị nhưng trong khuôn khổ nội dung ghi chú này, mình chỉ trình bày các chỉ thị quan trọng hay được xử dụng nhất như định nghĩa macro,... Còn các chỉ thị nâng cao xin hẹn ở một bài viết khác.

## **Macros**

Bạn đọc hiểu nôm na Macro là 1 cách đặt tên trong C và thường được hay sử dụng cho các ứng dụng dưới đây:

- Định nghĩa hằng
- Dùng để thay thế cho việc viết 1 hàm bằng C
- Loop unrolling
- Bảo vệ header
- Sinh code
- Biên soạn lại code theo điều kiện

Để định nghĩa macro chúng ta sử dụng chỉ thị `#define` chi tiết như nào thì chúng ta sẽ đi vào các ví dụ ở trong các phần tiếp theo ở dưới đây.

## **Định nghĩa một Macro**

Một macro được định nghĩa bởi chỉ thị `#define` theo sau chỉ thị này là 1 *tên* của marco và 1 danh sách các tham số (có thể có hoặc không). Đó cũng chính là giá trị được thay thế cho *tên* của marco trong mã nguồn thông qua 1 bước là *macro expansion*. Một macro cũng có thể là *undefined* khi sử dụng chỉ thị `#undef`. Chúng ta cùng đi qua ví dụ dưới để để có thể dễ hình dung hơn:

```c
#include <stdio.h>

#define y 9

int main(void) {
    // sau khi buoc macro expansion hoan thanh
    // y se dc thay the = 9
    int x = 2;          
    int s = x + y;      //  s = x + 9
    printf("s= %d", s); // s = 11
    return 0;
}
```

Trong đoạn code trên chúng ta có thể thấy `y` không phải là 1 biến `int` cũng không phải là 1 hằng `int`. `y` đơn thuần là 1 marco và nó có tên là `y` tương ứng giá trị là `9` sau khi bộ tiền xử lý thực hiện xong bước *macro expansion* thì đoạn mã nguồn ở dưới đây sẽ được gửi đến compiler:

```c
.....
int main(void) {
    int x = 2;          
    int s = x + 9;      
    printf("s= %d", s); 
    return 0;
}
```

Bây giờ thêm 1 ví dụ khác để chúng ta hiểu rõ thêm về bước  *macro expansion*

```c
#include <stdio.h>

#define SUM(a,b) a + b

int main(int argc, char **argv)
{
  int s = SUM(2,3);
  printf("s= %d",s); // s= 5
  return 0;
}
```

Như đoạn code trên chúng ta thấy `SUM` không phải là 1 hàm, nó chỉ trông giống như hàm. Chính xác thì nó chính là 1 macro có nhận tham số truyền vào. Sau thi qua bước  *macro expansion* thì đoạn code trên sẽ được xử lý thành như sau:

Nếu bạn sử dụng `gcc` hoặc `clang` để build thì có thể thêm tham số `-E` vào lệnh build để có thể xem mã nguồn được chỉnh sửa sau khi qua bước tiền xử lý như hình dưới:

>Vì chúng ta có `#include <stdio.h>` nên sau khi tiền xử lý mã nguồn chính sẽ có cả nội dung của file này ở trên đầu, phần mã nguồn chính trong hàm main của chúng ta sẽ xuất hiện ở dưới cùng.

![Phần đầu khi chạy gcc!](./images/option-e.PNG "Phần đầu khi chạy lệnh gcc -e")

![Phần sau khi chạy gcc!](./images/out-e.PNG "Mã nguồn khi xử lý xong bước tiền xử lý")

Khi chúng ta gọi marco `SUM(2,3)` thì sẽ tương ứng với các tham số truyền vào theo thứ tự như chúng ta đã định nghĩa ở trên, trong đoạn code trên thì `a = 2` và `b = 3` từ đó tất cả các tham số `a` ở phần định nghĩa giá trị của macro sẽ được thay thế bằng `2`, đối với tham số `b` sẽ làm tương tự. Sau khi thay thế hết các giá trị tham số truyền vào thì bước cuối cùng sẽ thay thế tên của macro bằng giá trị macro đã được thay thế tham số, ở đoạn code trên thì `SUM(2,3)` sẽ được thay thế bằng `2 + 3`

Chúng ta có thể sử dụng marco để định nghĩa 1 hàm và dùng nó thay thế cho việc viết 1 hàm C và gọi nó ra. Làm như vậy thì khi đi qua bước tiền xử lý, thì macro sẽ được thay thế bằng logic của hàm mà chúng ta đã định nghĩa, việc thay đổi này là thay đổi trực tiếp trên source code, đây là 1 điểm khác so với hàm C bình thường vốn dĩ muốn thực thi logic của hàm C chúng ta phải thực hiện 1 lời gọi hàm. Tất nhiên là đánh đổi lại việc sử dụng macro như vậy cũng sẽ có nhược điểm, phần này chúng ta sẽ tìm hiểu thêm ở phần sau.

>Có 1 điều khá là quan trọng khi sử dụng macro đó là macro chỉ tồn tại đến bước tiền xử lý và compiler sẽ không biết gì về macro cả (đối với những trình biên dịch cũ). Vì vậy khi bạn muốn sử dụng macro thay cho hàm bình thường thì hãy để ý đến việc này. Compiler có thể hiểu được hàm bởi vì hàm là 1 phần trong cú pháp của C. Hàm khi gửi đến compiler nó sẽ được phân tích cú pháp và đưa vào *cây phân tích cú pháp* (parse tree) còn macro chỉ là 1 chỉ thị tiền xử lý và chỉ có Bộ tiền xử lý hiểu nó.

Nào bây giờ chúng ta cùng xem xét 1 ví dụ trông có vẻ nguy hiểm hơn 1 chút:

```c
#include <stdio.h>

#define PRINT(temp) printf("%d\n", temp);
#define FORLOOP(i, start, end) \
  for (int i = start; i <= end; i++) {
#define ENDLOOP }

int main(void) {
  FORLOOP(i, 0, 9)
    PRINT(i)
  ENDLOOP
  return 0;
}
```

Nhìn qua đoạn code trên chúng ta có thể thấy chúng không đúng với cú pháp của C cho lắm, nhưng mà hãy xem thử mã nguồn sau khi được tiền xử lý xem sao nào

```c
......
int main(void) {
  for (int i = start; i <= end; i++) {
    printf("%d\n", i);
  }
  return 0;
}
```

Như chúng ta có thể thấy, sau khi đi qua bước tiền xử lý, mã nguồn đã được xử lý đúng theo cú pháp của C. Đây là 1 ứng dụng quan trọng của macro được dùng để định nghĩa một ngôn ngữ đặc tả chuyên biệt **(Domain Specific Language - DSL)** mới và viết code để sử dụng nó.

>DSLs (Domain Specific Language) có nhiều ứng dụng trong nhiều phần trong 1 dự án. Các framework testing như Google Test (gtest) đã sử dụng rất nhiều DSLs để viết **assertions** (vd: EXPECT_TRUE, SUCCEED, FAIL, ADD_FAILURE_AT,... ), **expectations** và  **test scenarios**

Đến đây cũng khá là dài rồi, bây giờ chúng ta sẽ đi tìm hiểu thêm về 1 ví dụ cuối cùng trong phần này, Phần macros này sẽ có 3 phần, đây là phần 1, ở 2 phần sau chúng ta sẽ đi tìm hiểu tiếp về  **Variadic macros** Còn bây giờ cùng xem xét về đoạn code phía dưới nào.

```c
// build: gcc *namefile*.c
// run: a.exe copy

#include <stdio.h>
#include <string.h>

#define CMD(NAME)            \
  char NAME##_cmd[256] = ""; \
  strcpy(NAME##_cmd, #NAME);

int main(int argc, char **argv)
{
  CMD(copy)
  CMD(paste)
  CMD(delete)

  if (strcmp(argv[1], copy_cmd) == 0) {
    printf("copy_cmd");
  }
  if (strcmp(argv[1], paste_cmd) == 0) {
    printf("paste_cmd");
  }
  if (strcmp(argv[1], delete_cmd) == 0) {
    printf("delete_cmd");
  }
  return 0;
}
```

Mã nguồn sau khi đi qua bước tiền xử lý

```c
...............
int main(int argc, char **argv)
{
  char copy_cmd[256] = ""; strcpy(copy_cmd, "copy");
  char paste_cmd[256] = ""; strcpy(paste_cmd, "paste");
  char cut_cmd[256] = ""; strcpy(cut_cmd, "cut");

  if (strcmp(argv[1], copy_cmd) == 0) {
    printf("copy_cmd");
  }
  if (strcmp(argv[1], paste_cmd) == 0) {
    printf("paste_cmd");
  }
  if (strcmp(argv[1], delete_cmd) == 0) {
    printf("delete_cmd");
  }
  return 0;
}
```

Trong bước *macros expansion* toán tử `#` sẽ biến đổi tham số truyền vào của macro (tham số có tên đi theo sau toán tử #) trở thành dạng `string` và sẽ thay thế vào chính vị trí của toán tử `#`. Ví dụ như trong đoạn code trên dòng `#define CMD(NAME) ... strcpy(NAME##_cmd, #NAME);` với tham số truyền vào là `CMD(delete)` thì ở toán tử `#` sẽ được thay thế lại như sau `strcpy(NAME##_cmd, "copy")` như vậy từ tham số truyền vào là `copy` thì toán tử `#` đã xử lý thành `"copy"`, khi đã đưa về được dạng `string` thì lúc này đưa vào làm đối số của hàm `strcmp()` hoàn toàn hợp lệ với cú pháp của C.

Trong đoạn code định nghĩa macro trên, ngoài toán tử `#` thì còn có 1 toán tử nữa là `##`. Đối với toán tử `##` thì cách hoạt động của nó là nối tham số với 1 thành phần khác trong định nghĩa của macro và thường là sẽ tạo thành 1 tên biến. Quay lại ví dụ trên ở dòng `#define CMD(NAME) char NAME##_cmd[256] = "";` với đối số truyền vào là `CMD(delete)` thì khi đi vào bước tiền xử lý `char NAME##_cmd[256]` sẽ được thay thế bằng `char delete_cmd[256]`.

Trên đây chỉ là những ví dụ cơ bản nhằm mục đích giới thiệu là chính. Bản thân ngôn ngữ C cung cấp cho chúng ta nhiều "vũ khí" mạnh mẽ, nhưng tuỳ vào từng trường hợp mà sẽ có cách sử dụng khác nhau. Các ứng dụng thực tế của chúng trong các mã nguồn dự án viết bằng C có rất nhiều, nếu có dịp nào đó thì chúng ta sẽ đi tìm hiểu thêm về chủ đề này. Còn bây giờ Phần 1 của chủ đề macro nên tạm dừng ở đây, ở Phần 2 chúng ta sẽ đi tìm hiểu 1 loại macro khác đó là *Variadic macros*.

## **Nguồn tham khảo**

- Extreme C: Taking you to the limit in Concurrency, OOP, and the most advanced capabilities of C 1st Edition - Kamran Amini (PDF Book)
- <https://en.cppreference.com/w/c/preprocessor>
