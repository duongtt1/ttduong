---
title: Từ mã nguồn ra mã máy (Phần 3)
subtitle: Chia sẻ thêm về Linking

# Summary for listings and search engines
summary: Chia sẻ thêm về Linking. 

# Link this post with a project
projects: []

# Date published
date: "2022-06-14T00:00:00Z"

# Date updated
lastmod: "2022-06-14T00:00:00Z"

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

>Sau khi đã tìm hiểu qua về object file thì bây giờ chúng ta sẽ tiếp tục đi tìm hiểu rõ hơn về cách mà linking hoạt động. Chúng ta sẽ cùng đi biên dịch cũng như phân tích các địa chỉ ở trong các file object để xem cách mà Linking nó thực sự hoạt động.

## **Linking**

Thực ra phần này mình đã đề cập đến ở bài **Từ mã nguồn ra mã máy Phần 2** rồi nhưng mà mình muốn viết rõ hơn xíu nữa vừa để chia sẻ thêm với bạn đọc và cũng làm bài cơ sở cho các bài viết về **Static library và Dynamic library** sắp tới. Sau khi đã tìm hiểu qua về *object file* thì bây giờ chúng ta sẽ cùng đi biên dịch cũng như phân tích các địa chỉ ở trong các *object file* để xem cách mà `linking` nó thực sự hoạt động. Bạn đọc không nên tập trung vào đoạn code vì cái source này mình hứng lên nên code con Mux chơi chơi vậy á nên trông code nó hơi ngu si 🙂 Nhưng không sao, chủ đề chính của chúng ta hôm này sẽ tập trung vào phần linking. ahihi ^^

```c

// mux_4.h
int mux_2(int a, int b, int s);
int mux_4(int a, int b, int c, int d, int s0, int s1);

// mux_4.c
int mux_2(int a, int b, int s) {
  return s ? b : a;
}

int mux_4(int a, int b, int c, int d, int s0, int s1) {
  return s0 ? mux_2(c,d,s1) : mux_2(a,b,s1);
}
```

```c
# include <stdio.h>
# include "mux4.h"

int main(void) {
  int a=1, b=2, c=3, d=4, s0=0, s1=0, x = 0;
  x = mux_4(a,b,c,d,s0,s1);
  printf("%d",x);
  return 0;
}
```

Có chương trình rồi giờ chúng ta bắt đầu biên dịch thử coi nào.

```sh
~/$ gcc -c mux4.c -o mux4.o
~/$ gcc -c main.c -o main.o
```

Sau khi thực hiện 2 lệnh trên chúng ta sẽ có được 2 file `main.o` và `mux4.o` đều là *ELF object file* vì vậy nên chúng ta có thể sử dụng công cụ `readelf` để xem ở trong đó nó có cái gì.

```sh
readelf -hSl mux4.o
```

```sh
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              REL (Relocatable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x0
  Start of program headers:          0 (bytes into file)
  Start of section headers:          696 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           0 (bytes)
  Number of program headers:         0
  Size of section headers:           64 (bytes)
  Number of section headers:         12
  Section header string table index: 11

Section Headers:
  [Nr] Name              Type             Address           Offset
       Size              EntSize          Flags  Link  Info  Align
  [ 0]                   NULL             0000000000000000  00000000
       0000000000000000  0000000000000000           0     0     0
  [ 1] .text             PROGBITS         0000000000000000  00000040
       000000000000002d  0000000000000000  AX       0     0     16
  [ 2] .rela.text        RELA             0000000000000000  000001f8
       0000000000000030  0000000000000018   I       9     1     8
  [ 3] .data             PROGBITS         0000000000000000  0000006d
       0000000000000000  0000000000000000  WA       0     0     1
  [ 4] .bss              NOBITS           0000000000000000  0000006d
       0000000000000000  0000000000000000  WA       0     0     1
  [ 5] .comment          PROGBITS         0000000000000000  0000006d
       0000000000000013  0000000000000001  MS       0     0     1
  [ 6] .note.GNU-stack   PROGBITS         0000000000000000  00000080
       0000000000000000  0000000000000000           0     0     1
  [ 7] .eh_frame         PROGBITS         0000000000000000  00000080
       0000000000000040  0000000000000000   A       0     0     8
  [ 8] .rela.eh_frame    RELA             0000000000000000  00000228
       0000000000000030  0000000000000018   I       9     7     8
  [ 9] .symtab           SYMTAB           0000000000000000  000000c0
       0000000000000108  0000000000000018          10     8     8
  [10] .strtab           STRTAB           0000000000000000  000001c8
       000000000000002a  0000000000000000           0     0     1
  [11] .shstrtab         STRTAB           0000000000000000  00000258
       0000000000000059  0000000000000000           0     0     1
```

Như kết quả ở trên thì các số `[1, 3, 4, 9]` là các section quan trọng như `.text` là section chứa mã máy của đơn vị biên dịch (translation unit), `.data` và `.bss` là section chứa các biến global, static đã được khởi tạo giá trị hoặc vùng nhớ cần thiết để dành cho các biến chưa được khởi tạo giá trị cụ thể,`.symtab` là nơi lưu giữ symbol table. Thứ chúng ta đang muốn quan tâm ở đây chính là cái ông `.systab` này, bây giờ chúng ta sẽ dump file `main.o` ra để kiểm tra bảng này.

>Bạn đọc để ý khi nãy biên dịch file `main.o` cũng vẫn là 1 object file như bình thường. Quá trình linking chưa thực hiện nên chúng ta vẫn chưa có file thực thi cuối cùng. Bạn đọc tránh nhầm lẫn giữa file `main` và file `main.o`

```sh
readelf -s mux4.o

Symbol table '.symtab' contains 11 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS mux4.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    3
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    4
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    6
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    7
     7: 0000000000000000     0 SECTION LOCAL  DEFAULT    5
     8: 0000000000000000     8 FUNC    GLOBAL DEFAULT    1 mux_2
     9: 0000000000000010    29 FUNC    GLOBAL DEFAULT    1 mux_4
    10: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND _GLOBAL_OFFSET_TABLE_
```

Để ý chúng ta sẽ thấy `mux_2` bắt đầu từ `0` và `mux_4` bắt đầu từ `10`, điều này có nghĩa là các lệnh thực thi nằm liền kề nhau trên bộ nhớ và chúng ta có thể được di chuyển tới 1 nơi khác, ví dụ như: copy tập lệnh này vào đâu đó trong file thực thi cuối cùng chẳng hạn.

Tiếp theo chúng ta sẽ dump cả file `main.o` ra để xem trong đó nó có cái gì nữa nào:

```sh
Symbol table '.symtab' contains 15 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS main.c
     2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1
     3: 0000000000000000     0 SECTION LOCAL  DEFAULT    2
     4: 0000000000000000     0 SECTION LOCAL  DEFAULT    3
     5: 0000000000000000     0 SECTION LOCAL  DEFAULT    4
     6: 0000000000000000     0 SECTION LOCAL  DEFAULT    5
     7: 0000000000000000     0 SECTION LOCAL  DEFAULT    8
     8: 0000000000000000     0 SECTION LOCAL  DEFAULT    9
     9: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT    4 .LC0
    10: 0000000000000000     0 SECTION LOCAL  DEFAULT    7
    11: 0000000000000000    63 FUNC    GLOBAL DEFAULT    5 main
    12: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND _GLOBAL_OFFSET_TABLE_
    13: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND mux_4
    14: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND __printf_chk
```

Chúng ta có thể thấy các địa chỉ để lưu các symbol như `mux_4` thì đều là 0 cả. Điều này là vì bản thân file main.o nó cũng là một `object files`. Các symbol ở trong `object files` sẽ không có địa chỉ cố định mà địa chỉ của các `symbol` này nằm ở đâu trong file thực thi cuối cùng sẽ được quyết định thông qua quá trình `linking`.

Bây giờ chúng ta sẽ tiến hành biên dịch ra file thực thi `main` và dump nó ra để xem có gì khác file `main.o` ở trên trên không:

```sh
gcc mux4.o main.o -o main

Symbol table '.dynsym' contains 4 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND [...]@GLIBC_2.2.5 (2)
     2: 0000000000000000     0 NOTYPE  WEAK   DEFAULT  UND __gmon_start__
     3: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND [...]@GLIBC_2.3.4 (3)

Symbol table '.symtab' contains 74 entries:
   Num:    Value          Size Type    Bind   Vis      Ndx Name
     0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND
     1: 0000000000400318     0 SECTION LOCAL  DEFAULT    1
    ...
    50: 0000000000403dc0     0 OBJECT  LOCAL  DEFAULT   21 _DYNAMIC
    ...
    67: 0000000000404010     0 NOTYPE  GLOBAL DEFAULT   24 __bss_start
    68: 0000000000401040    63 FUNC    GLOBAL DEFAULT   14 main
    69: 0000000000000000     0 FUNC    GLOBAL DEFAULT  UND __printf_chk@@GL[...]
    70: 0000000000404010     0 OBJECT  GLOBAL HIDDEN    23 __TMC_END__
    71: 0000000000401170     8 FUNC    GLOBAL DEFAULT   14 mux_2
    72: 0000000000401180    29 FUNC    GLOBAL DEFAULT   14 mux_4
73: 0000000000401000     0 FUNC    GLOBAL HIDDEN    12_init
```

Chúng sẽ cần để ý đến kết quả trên có tới tận 2 symbol table là `.dynsym` và `.systab`. Ở symbol table `.dynsym` chứa các symbol cần được xử lý khi file thực thi bắt đầu được khởi chạy (nói cách khác thì đây là bảng để lưu các symbol của các *Dynamic library*), còn ở `.systab` sẽ chứ tất cả những symbol đã được xử lý và các symbol chưa được xử lý được đưa ra từ `Dynamic table` (còn đây chính là các symbol của *Static library*). Để ý ở dòng 71-72 ở `.systab` thì chúng ta có thể thấy địa chỉ của 2 symbol `mux_2` và `mux_4` là 2 địa chỉ tuyệt đối sau quá trình linking. Như vậy là các tập lệnh của từng symbol đã được thay thế vào đúng vị trí của symbol ở trong file thực thi cuối cùng. Như vậy thì qua quá trình Linking tất cả các tập lệnh mã máy đã được liên kết lại thành 1 file hoàn chỉnh và file này chính là file thực thi cuối cùng.

Thật lòng mà nói thì phần này là 1 phần tương đối khó để tưởng tượng, nếu mà giải thích bằng chữ thôi thì thật khó để hình dung, đấy là chưa kể câu văn của mình nó lại lũng cũng nữa nhưng mà mình hy vọng là qua từng bước chạy như trên bạn đọc có thể phần nào hình dung ra được cách mà linker làm việc. Sắp tới chúng ta sẽ đi tìm hiểu về **Static library và Dynamic library** nội dung của phần tới thì vẫn sẽ có phần liên quan đến bài này, đấy là mình dự định như thế chứ còn bao giờ viết tiếp thì mình cũng chưa rõ :))))

<!-- ## **Nguồn tham khảo**


- <https://stackoverflow.com/questions/12122446/how-does-c-linking-work-in-practice> -->
