---
title: Thư viện tĩnh và Thư viện động
subtitle: Thư viện trong C/C++ được chia làm 2 loại là Static Libraries và Dynamic Libraries hay Shared Libraries.

# Summary for listings and search engines
summary: Thư viện trong C/C++ được chia làm 2 loại là Static Libraries và Dynamic Libraries hay Shared Libraries. 

# Link this post with a project
projects: []

# Date published
date: "2022-06-21T00:00:00Z"

# Date updated
lastmod: "2022-06-21T00:00:00Z"

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

## **Static libraries**

*Static library* hay còn gọi tiếng việt là thư viện tĩnh đơn giản chỉ là một archive file được tạo ra từ các object file thông qua `ar` tools. Những file thư viện tĩnh này có thể được linked với các objects file khác để tạo thành 1 file thư viện khác hoặc 1 file thực thi.

Mình cũng tính viết 1 chương trình mới rồi nhưng mà máu lười nó lại nổi lên nên thôi chúng ta dùng luôn cái source code sort hồi bữa vậy, nhưng mà lần này mình sẽ đổi gió dùng C++ cải tiến nó 1 xíu. Dùng C++ thì sẽ biên dịch bằng `g++` nhưng mà không sao cả, vì trong phạm vi bài viết này thì `gcc` và `g++` không có gì khác nhau.

```cpp
// sort.h
#include <iostream>

template <typename T>
bool ascending(const T &a, const T &b){
  return a > b;
}

template <typename T>
bool decending(const T &a, const T &b){
  return a < b;
}

template<class T, size_t N>
void sortCustom(T (&arr)[N], bool (*compare)(const T &a, const T &b))
{
    for(int i=0; i<N-1; ++i){
      for(int j=i; j<N; ++j){
        if(compare(arr[i],arr[j])){
          std::swap(arr[i],arr[j]);
        }
      }
    }
}

template<class T, size_t N>
void printArr(const T (&arr)[N])
{
    for(int i=0; i<N; ++i){
      std::cout << arr[i] << "\t";
    }
  std::cout << "\n";
}

//main.cpp
#include "sort.h"

int main() {
  int a[5]{1, 5, 156, 56, 531};
  sortCustom(a,decending);
  printArr(a);
  return 1;
}
```

Sau khi đã có code rồi thì bây giờ mục đích của chúng ta là sẽ build thành thư viện tĩnh để sử dụng. Như đã nói ở bài trước đó, thì điều đầu tiên cần làm đó là chúng ta cần biên dịch ra các objects file :

Lưu ý là mình đang dùng Linux, nếu bạn đọc sử dụng khác nền tảng thì sẽ có 1 số chỗ khác nhau.

```sh
~/$ g++ -c sort.cpp -o sort.o
~/$ g++ -c main.cpp -o main.o
```

Sau lệnh trên chúng ta đã có được `sort.o` để tạo ra thư viện tĩnh thì đơn giản ta chỉ cần thực hiện:

```sh
~/$ ar crs libsort.a sort.o
```

Giải thích lệnh trên 1 xíu:

- `c`: (create) nếu chưa tồn tại thì tạo mới.
- `r`: (replace) nếu thư viện đã tồn tại rồi thì thay thế.
- `s`: (sort) sắp xếp lại để việc tìm kiếm được nhanh hơn.
- `libsort.a`: là tên thư viện được tạo ra, với lib là do mình tự thêm vào, sort là tên thư viện và .a là đuôi mở rộng của file. Ngoại trừ đuôi .a ra thì bạn muốn đặt như nào cũng được. Nhưng mà nên đặt tên theo các rules mà các lập trình viên có kinh nghiệm đã khuyến nghị để dễ dàng làm việc về sau.
- `sort.o` thì là objects file của thư viện sort mình vừa build hồi nãy rồi, ở đây vì chỉ có 1 file nên mình truyền 1 file, nếu như thư viện cần build cần nhiều objects file thì chúng ta có thể truyền thêm vào ở đây.

Để kiểm tra nội dung của file achive vừa nãy, chúng ta có thể sử dụng tools ar và tiến hành biên dịch ra file thực thi cuối cùng như sau:

```sh
~/$ ar t libsort.a 
sort.o
~/$ g++ main.o -L./ -lsort -o main.out
~/$ ./main.out
531 156 56  5   1
```

Ở trong đoạn lệnh biên dịch ra file thực thi cuối cùng có đối số `-L./` có ý nghĩa bảo với `g++` là ngoài `/usr/lib` và `/usr/local/lib` thì hãy tìm những file thư viện tĩnh hay thư viện động ở trong thư mục này. Đối số `-lsort` có ý nghĩa bảo với `g++` hãy tìm các file `libsort.a` hoặc `libsort.so`

Sau quá trình liên kết thì file thực thi bây giờ không còn liên quan gì đến thư viện tĩnh nữa, bây giờ file thực thi có thể chạy độc lập mà không cần quan tâm đến các file thư viện tĩnh. Như đã nói ở bài trước, trong quá trình linking diễn ra các tập lệnh trong thư viện đã được thay thế vào vị trí của symbol tương ứng trong file thực thi cuối cùng. Nếu như chương trình sử dụng nhiều thư viện tĩnh thì kích thước của file thực thi cuối cùng thường sẽ lớn, chúng ta có sử dụng thư viện động để giảm kích thước của file thực thi nhưng đánh đổi lại thì file thực thi cuối cùng sẽ không hoàn chỉnh và sẽ không chạy được nếu như không có các file Shared library. Về Shared library chúng ta sẽ chia sẻ thêm ở phần tiếp theo.

## **Dynamic libraries**

*Dynamic libraries* hay *Shared libraries* là một cách khác để tạo ra cái thư viện có thể tái sử dụng. Nhưng không như *static libraries* chúng không phải là một phần trong file thực thi, thay vào đó chúng sẽ được load và đưa vào file thực thi khi file thực thi bắt đầu khởi chạy.

Vì static libraries là một phần trong file thực thi nên khi biên dịch, *linker* sẽ phát hiện ra các undefined symbols sau đó sẽ tìm các symbol này trong các object files và cuối cùng là đưa tất cả bọn chúng và file thực thi cuối cùng.  Vì vậy nên file thực thi cuối cùng chỉ hoàn thành khi tất cả các undefined symbols được tìm thấy, tất cả việc này đều được hoàn thành ở quá trình linking. Đối với dynamic libraries nó có thể có các undefined symbols mà chưa được xử lý tại thời điểm linking, thay vào đó các undefined symbols sẽ được xử lý bởi dynamic *linker* hoặc *loader* vào lúc file thực thi bắt đầu khởi chạy. Trong khi các static libraries có đuôi file là .a thì các dynamic libraries hay shared libraries sẽ có đuôi `.so` trên hầu hết các hệ điều hành họ Unix, đối với MacOS sẽ là đuôi `.dylib` còn Window sẽ là `.DLL`

Khi file thực thi bắt đầu khởi chạy, các dynamic libraries hay shared libraries sẽ được load và map vào vùng nhớ được phép truy cập bởi tiến trình của file thực thi. Cả ELF executable file và shared object files đều có các segment nhưng có 2 điểm khác biệt chính giữa ELF executable file và shared object files , điều đầu tiên đó là các symbol ở trong shared object files có địa chỉ địa chỉ là tương đối nhưng khoảng cách giữa các lệnh mà symbol đại diện thì đã được fix cứng nên điều này giúp cho chúng có thể được load như một phần của nhiều process ở cùng một thời điểm. Điểm thứ 2 đó là shared object files không có các segment liên quan đến việc loading như trong ELF executable file vì vậy nên shared object files không thể chạy được.

Bây giờ chúng ta sẽ đi vào bước tiếp theo đó là các bước để tạo ra dynamic libraries, vẫn là source cũ ở trên bây giờ chúng ta sẽ bắt đầu đi từ đầu biên dịch ra object files:

```sh
~/$ g++ -c sort.cpp -fPIC -o sort.o
~/$ g++ -shared sort.o -o libsort.so
```

Ở  trong lệnh trên để ý chúng ta có thể thấy nó khác so với lệnh của static libraries ở chỗ có thêm option `-fPIC` đây là 1 option bắt buộc nếu như chúng ta muốn build ra dynamic libraries, `PIC` ở đây có nghĩa là *Position Independent Code* tức là cách lệnh ở trong object files sau khi được biên dịch sẽ không fix cứng địa chỉ. Điều này cũng không có nghĩa là loader sẽ load share object files vào cùng một địa chỉ ở các vùng nhớ của tiến trình khác nhau, sự thật là loader tạo ra một ánh xạ bộ nhớ tới share object files và vùng nhớ để ánh xạ này cũng có thể khác nhau. Việc này mấu chốt giúp cho share object files có thể được load ở nhiều process ở cùng một thời điểm.

Tiếp theo chúng ta sẽ tiếp tục các bước tiếp theo để biên dịch ra được file thực thi cuối cùng:

```sh
~/$ g++ main.o -L./ -lsort -o main
~/$ ./main
./main: error while loading shared libraries: libsort.so: cannot open shared object file: No such file or directory
```

Và lỗi.... Như đã nói ở trên dynamic libraries sẽ bị phụ thuộc vào các shared object files và để nó có thể thực thi được chúng ta cần cung cấp đầy đủ đường dẫn cho dynamic linker để nó có thể tìm ra được các shared object files để làm điều này thì chúng ta sẽ cật nhật biến môi trường `LD_LIBRARY_PATH` sẽ trỏ tới đường dẫn hiện tại đang chứa `libsort.so` hoặc chúng ta cũng có thể thêm biến môi trường này vào câu lệnh thực thi cũng được, các lệnh để chạy sẽ như sau:

```sh
~/$ export LD_LIBRARY_PATH=./
~/$ ./main
531 156 56  5   1
~/$ LD_LIBRARY_PATH=./ ./main
531 156 56  5   1
```

Như vậy là coi như chúng ta đã đi xong các bước cơ bản để tạo ra và sử dụng thư viện động rồi. Ngoài cách load tự động như vậy thì chúng ta cũng có thể load theo cách thủ công. Vì bài viết cũng dài rồi nên mình để link bài viết tham khảo ở [*đây*](https://tldp.org/HOWTO/Program-Library-HOWTO/dl-libraries.html). Nếu bạn đọc muốn tìm hiểu thêm có thể đọc qua. Hẹn bạn đọc ở một lúc nào đó rảnh thì lại tìm hiểu tiếp ^^

## Nguồn tham khảo

- Extreme C - Kamran Amini (PDF Book)
- <https://tldp.org/HOWTO/Program-Library-HOWTO/dl-libraries.html>
- <https://stackoverflow.com/questions/29714300/what-does-the-rcs-option-in-ar-do>
