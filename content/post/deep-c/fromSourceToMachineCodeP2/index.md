---
title: Từ mã nguồn ra mã máy (Phần 2)
subtitle: Ở trong chuỗi bài này thì chúng ta cùng nhau tìm hiểu về quá trình bắt đầu từ viết code C cho đến các bước Preprocessing, compilation, Asemble, Linking để rồi ra được 1 file thực thi cuối cùng.

# Summary for listings and search engines
summary: Ở trong chuỗi bài này thì chúng ta cùng nhau tìm hiểu về quá trình bắt đầu từ viết code C cho đến các bước Preprocessor, Compiler, Assemblers, Linker để rồi ra được 1 file thực thi cuối cùng. 

# Link this post with a project
projects: []

# Date published
date: "2022-04-24T00:00:00Z"

# Date updated
lastmod: "2022-04-24T00:00:00Z"

# Is this an unpublished draft?
draft: true

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

Trong phần trước chúng ta đã tìm hiểu về Preprocessing và Compilation tiếp theo ở bài viết này thì chúng ta sẽ tiếp tục tìm hiểu thêm 2 bước còn lại là Asemble và Linking.

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
`

```bash
ld main.o sortint.o
```

## **Nguồn**

- Extreme C: Taking you to the limit in Concurrency, OOP, and the most advanced capabilities of C 1st Edition - Kamran Amini (PDF Book)
- <https://www.toptal.com/c-plus-plus/c-plus-plus-understanding-compilation>
- <http://www.chiark.greenend.org.uk/doc/cpp-4.3-doc/cppinternals.html>
- <http://icps.u-strasbg.fr/~pop/gcc-ast.html>
