---
title: Từ mã nguồn ra mã máy (Phần 2)
subtitle: Trong phần trước chúng ta đã tìm hiểu về Preprocessing và Compilation tiếp theo ở bài viết này thì chúng ta sẽ tiếp tục tìm hiểu thêm 2 bước còn lại là Asemble và Linking.

# Summary for listings and search engines
summary: Trong phần trước chúng ta đã tìm hiểu về Preprocessing và Compilation tiếp theo ở bài viết này thì chúng ta sẽ tiếp tục tìm hiểu thêm 2 bước còn lại là Asemble và Linking.

# Link this post with a project
projects: []

# Date published
date: "2022-04-29T00:00:00Z"

# Date updated
lastmod: "2022-04-29T00:00:00Z"

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

## **Asemble**

Bước tiếp theo sau khi hoàn thành bước compilation đó là Asemble. Ở bước này thì sẽ sinh ra mã máy (machine code) dựa trên mã Assembly được sinh ra ở quá trình compilation.

Trong hầu hết các nên tảng họ nhà Unix chúng ta sẽ được cung cấp sẵn 1 tools để biên dịch các file code Assembly đó là `as`. Sau khi biên dịch các file mã assembly này ra thành mã máy tương ứng với kiến trúc phần cứng thì các file chứa mã máy này được gọi là các `object file`. Tuy là file chứa mã máy nhưng mà các object file này không chạy được, chúng chỉ đơn giản là chứa các mã máy được biên dịch ra từ các translation unit.

Để biên dịch từ file `.s` ra file object chúng ta sử dụng cmd sau:

```bash
as sortint.s -o sortint.o
```

Trong ví dụ trên thì đối số `-o` dùng để chỉ định tên cho file object, phần mở rộng của các file object thì thường sẽ là `.o` hoặc có thể là `.obj` ở trên Window.

>Mặc dù chúng ta có thể sử dụng trực tiếp `as` để biên dịch nhưng thực tế thì việc này không được khuyến khích, thay vào đó thì chúng ta sẽ sử dụng trình biên dịch và chính nó sẽ gọi đến `as` thay cho chúng ta. Bằng việc sử dụng đối số `-c` khi compile với gcc chúng ta cũng sẽ có kết quả tương tự.
>
>vd: `gcc -c sortint.c`

Đây cũng là bước cuối cùng trong việc biên dịch các file riêng lẽ. Tất cả các file mã nguồn C mà được sử dụng trong dự án của chúng ta đều sẽ cần phải được biên dịch ra đến object file (file .o) khi có đầy đủ các object file rồi thì chúng ta mới có thể tiếp tục đến với bước cuối cùng đó là *Linking*.

Theo như source code đã được xây dựng ở phần trước thì chúng ta tiến hành biên dịch thêm file `main.c` ra object file.

```bash
gcc -c main.c
```

Như vậy là chúng ta đã có 2 file object đó là `main.o` và `sortint.o` tiếp theo chúng ta sẽ đến với bước *Linking* để có thể liên kết các file object này thành 1 file thực thi cuối cùng.

## **Linking**

Cũng như `as`, ở bước này thì chúng ta lại được các nền tảng họ nhà Unix cung cấp sẵn 1 tools mặc định đó là `ld` để dùng cho việc liên kết các file object thành file thực thi cuối cùng. Ở bước trước thì chúng ta đã có sẵn 2 file `main.o` và `sortint.o` nên bây giờ chúng ta sẽ tiến hành liên kết 2 file này lại theo lệnh sau:

```bash
ld main.o sortint.o
```

Và đây là kết quả:

```bash
.../bin/ld: warning: cannot find entry symbol _start; defaulting to 0000000000401000
.../bin/ld: main.o: in function `main':
main.c:(.text.startup+0x17): undefined reference to `malloc'
.../bin/ld: main.c:(.text.startup+0x6b): undefined reference to `__printf_chk'
.../bin/ld: main.c:(.text.startup+0x78): undefined reference to `free'
```

Các bạn thấy đấy, liên kết đã thất bại rồi. Tuy biết là lệnh nó như thế nhưng mà thực tế thì để chạy trực tiếp `ld` thì cũng không dễ dành cho lắm :))) đó là lý do vì sao ở phần assemble ở trên việc chạy `as` trực tiếp không được khuyến khích.

Bây giờ cùng phân tích lỗi trên nó thông báo ra cái gì nào? chú ý là dòng số 2, 3 và 4 chúng ta sẽ thấy nó báo là 3 ông `malloc`, `__printf_chk` và `free` thì chưa có được định nghĩa. malloc và free thì chúng ta có sử dụng ở trong hàm `main()` thật, nhưng mà có cái ông `__printf_chk` thì trông lạ lẫm quá :))) Chúng ta có dùng ông thần này trong hàm `main()` đâu nhỉ? Thực ra nó có chức năng tương tự với  hàm `printf` chỉ khác ở chỗ `__printf_chk` có kiểm tra tràn `stack` và nó cũng chỉ có trong binary standard. `__printf_chk` đã được thay thế vào bởi trình biên dịch và việc này chỉ có ở Linux, nếu bạn dùng `ld` ở trên Window thì sẽ không gặp cái này.

>Vì trong quá trình linking trên Linux có đụng trường hợp này nên mình nêu ra như ví dụ, nếu có dịp sẽ có bài nói chi tiết hơn về việc biên dịch trên Linux. Còn bạn thắc mắc cái ông `__printf_chk` là cái gì? thì có thể đọc ở [đây](https://refspecs.linuxbase.org/LSB_4.1.0/LSB-Core-generic/LSB-Core-generic/libc---printf-chk-1.html "__printf_chk"). Nhưng mà có đọc cái này thì cũng nhớ quay lại đây đọc tiếp phần linking nữa nhá :)))

Nhưng mà tóm gọn lại thì `ld` nó báo là nó không có tìm thấy mấy cái hàm trên, mà để `ld` nó tìm thấy được mấy cái hàm trên thì chúng ta cần cung cấp cho `ld` file object của mấy hàm trên thì nó mới tìm ra được. Điều này lại khá là rắc rối, vì vậy cách chạy trực tiếp bằng tay `ld` như thế này đúng là rất khó khăn. Nhưng mà may mắn thay cho chúng ta khi trong các nền tảng họ nhà Unix thì hầu hết các trình biên dịch đều đã hỗ trợ chúng ta làm việc này. Vì thế nên chúng ta sẽ không cần chạy `ld` bằng tay nữa. Công việc bây giờ trở nên khá là đơn giản ví dụ sử dụng gcc để thực hiện liên kết như sau:

```bash
gcc main.o sortint.o
```

>Thực ra là khi chạy với gcc thì nó cũng gọi đến `ld` thôi nhưng có cái khác đó là nó đã tự động thêm các đối số là các thư viện tĩnh,... vào giúp chúng ta luôn rồi. Nên là công việc này trở nên đơn giản là chạy  `ld` bằng tay hơn.

Nếu chúng ta nghĩ quá trình linking cũng đơn giản như vậy thôi thì chúng ta đã đánh giá quá thấp nó rồi. Việc này chỉ đơn giản khi chúng ta cứ phang gcc vào mà chạy, nhưng mà chỉ sử dụng `gcc` thì chúng ta vẫn chỉ biết xài `gcc` để chạy vậy thôi chứ chưa thực sự hiểu linking hoạt động ra sao?, làm sao để nó có thể liên kết được các file object?, làm sao mà lại ra được file thực thi cuối cùng???. Phần này tuy phức tạp vcl và cũng dài vcl nhưng lại có nhiều chỗ thú vị. Vì vậy ở phần tiếp theo của bài viết này chúng ta sẽ tìm hiểu thêm một chút nữa về mà Linking.

Để nhìn thấy được *linker* hoạt động như thế nào chúng ta cần phải biết được cách mà nó sử dụng các file object, mà để biết được cách nó sử dụng thì trước hết chúng ta cần biết được file object đang chứa nội dung gì?

>Tổng quan thì linker là 1 chương trình máy tính dùng để liên kết các file object thành một file thực thi cuối cùng. Ở phần trên thì nó chính là tools `ld` ấy.

Câu trả lời cho câu hỏi ở đoạn trên thì chúng ta đã nói ở phần trước. file object chỉ đơn giản là chứa mã máy được biên dịch từ translation unit. Tuy nhiên các tập lệnh mã máy này không được đưa vào file object một cách ngẫu nghiên và chúng sẽ được nhóm lại thành cách section. Và các section mã máy này được gọi là *symbols*.

Sự thật là trong file object có nhiều thứ khác chứ không phải chỉ có symbols, nhưng mà để giải thích cách hoạt động của linker thì tạm thời chúng ta chỉ cần quan tâm đến nó thôi. Bây giờ chúng ta sẽ cùng xem xét lại ví dụ sortint đã làm ở trên:

```c
...
void swapInt(int *a, int *b){
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void sortInt(int* a, int n, type_compare type){
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i+1; j < n; j++)
        {
            if (type == ASCENDING ? a[i] > a[j] : a[i] < a[j])
            {
                swapInt(&a[i], &a[j]);
            }

        }
    }
}
```

Chúng ta có thể thấy ở trong sortint.c có 2 hàm là `swapInt` và `sortInt` bây giờ chúng ta cùng xem các symbol có ở trong file object của sortint xem nó như nào, để làm được việc này thì chúng ta có tổ hợp các công cụ được Unix cung cấp sẵn đó là `nm`, `readelf`, `objdump`. Với tools `nm` sẽ cho phép chúng ta có thể nhìn thấy các symbol trong object file như sau:

```bash
nm sortint.o
                  U _GLOBAL_OFFSET_TABLE_
0000000000000010 T sortInt
0000000000000000 T swapInt
```

Như kết quả trên chúng ta có thể trong file object có chứa 2 symbol trùng với tên hàm chúng ta đã định nghĩa trong file `sortint.c`, để rõ hơn nữa thì chúng ta thể sử dụng `readelf` để xem cả *symbol table* ở trong object file. Lệnh sử dụng readelf như sau:

```bash
readelf -s sortint.o

Symbol table '.symtab' contains 11 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS sortint.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    3 
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    4 
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    6 
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    7 
     7: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 
     8: 0000000000000000     9 FUNC    GLOBAL DEFAULT    1 swapInt
     9: 0000000000000010   191 FUNC    GLOBAL DEFAULT    1 sortInt
    10: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND _GLOBAL_OFFS
```

Tất nhiên là chúng ta vẫn sẽ có 2 hàm `swapInt` và `sortInt` tương ứng với 2 hàm được định nghĩa bên mã nguồn C rồi. Nhưng mà *symbol table* cung cấp cho chúng ta nhiều thông tin hơn. Về chi tiết các symbol khác trong symbol table này thì có thể sẽ có 1 bài viết riêng để nói về nó vì nó cũng khá là dài :)))

Tiếp theo nếu mà vẫn chưa thoả mãn, thì chúng ta có thể xem được cả các nhóm lệnh ASM tương ứng với các FUNC symbol luôn, bằng cách sử dụng `objdump` như ví dụ sau:

```bash
objdump -d sortint.o
```

Và kết quả:

```asm

sortint.o:     file format elf64-x86-64

Disassembly of section .text:

0000000000000000 <swapInt>:
   0:   8b 07                   mov    (%rdi),%eax
   2:   8b 16                   mov    (%rsi),%edx
   4:   89 17                   mov    %edx,(%rdi)
   6:   89 06                   mov    %eax,(%rsi)
   8:   c3                      retq   
   9:   0f 1f 80 00 00 00 00    nopl   0x0(%rax)

0000000000000010 <sortInt>:
  10:   41 57                   push   %r15
  12:   89 f0                   mov    %esi,%eax
  14:   41 56                   push   %r14
  16:   41 55                   push   %r13
  ....
  ....
  cc:   41 5f                   pop    %r15
  ce:   c3                      retq  
```

Dựa trên những gì chúng ta đã làm ở trên có thể thấy mỗi *function symbol* tương ứng với một hàm đã được định nghĩa trong mã nguồn. Mỗi file object chỉ chứa 1 phần các chức năng (function,...) trong toàn bộ các chức năng của 1 chương trình hoàn chỉnh. Bằng cách tập hợp tất cả các symbol của các file object lại và kết hợp chúng lại thành 1 file thực thi hoàn chỉnh thì Linker đã hoàn thành được công việc của mình.

>Cái phần sử dụng `nm`, `readelf` hay `objdump` là những phần mình show ra để bạn đọc hiểu trong file object nó như thế nào nhằm mục đích giải thích cho việc Linker nó dựa vào cái gì để thực hiện việc liên kết. Chứ không đó không phải các bước thực hiện của Linker :))) Nếu bạn muốn tìm hiểu kỹ lưỡng hơn về việc Linker liên kết các file object và sắp xếp các tập lệnh trên địa chỉ bộ nhớ như thế nào thì có thể xem thêm ở [video này](https://youtu.be/oXk87NRTL1Y).

Như vậy là bước cuối cùng cũng đã xong, Hy vọng là qua bài viết này các bạn có cái nhìn bao quát hơn về C và cụ thể là quá trình biên dịch 1 chương trình C. Còn một số vấn đề liên quan đến phần Linking này nữa nhưng mà mình xin tạm dừng bài viết ở đây vì nó cũng dài rồi. Sau này nếu có thời gian trống chúng ta sẽ cùng nhau thảo luận thêm về các vấn đề này.

## **Nguồn tham khảo**


- <http://www.chiark.greenend.org.uk/doc/cpp-4.3-doc/cppinternals.html>
- <http://icps.u-strasbg.fr/~pop/gcc-ast.html>
- <https://youtu.be/oXk87NRTL1Y>
