---
title: Tiền xử lý trong C (Phần 3)
subtitle: Qua 2 phần vừa rồi chúng ta đã tìm hiểu được các kiến thức cơ bản của macro, ở Phần 3 này chúng ta lại tiếp tục đi tìm hiểu về ưu nhược điểm của nó để có thể sử dụng nó tốt nhất.

# Summary for listings and search engines
summary: Qua 2 phần vừa rồi chúng ta đã tìm hiểu được các kiến thức cơ bản của macro, ở Phần 3 này chúng ta lại tiếp tục đi tìm hiểu về ưu nhược điểm của nó để có thể sử dụng nó tốt nhất. 

# Link this post with a project
projects: []

# Date published
date: "2022-04-15T00:00:00Z"

# Date updated
lastmod: "2022-04-15T00:00:00Z"

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

>Nếu bạn chưa đọc Phần 1 và Phần 2 thì nên đọc qua 2 phần này trước nhé, vì ở 2 phần trước chúng ta đã đi tìm hiểu khá kỹ lưỡng về macro. Còn nếu bạn không thích đọc 2 phần trước thì cũng không sao cả, cứ đọc luôn phần 3 được :v

## **Ưu và Nhược điểm của macro**

Macro có một đặc tính rất đặc biệt đó là sau quá trình tiền xử lý thì toàn bộ các macro sẽ được thay thế bằng các dòng\đoạn code khác. Điều này làm cho mã nguồn trở nên dài hơn và tuần tự. Cũng vì vậy mà mã nguồn tại thời điểm biên dịch sẽ không có module nào cả. Nếu chính ta là tác giả của mã nguồn trên thì mọi chuyện có vẻ như sẽ đỡ căng thẳng khi chúng ta vẫn sẽ nhớ được các logic về macro mà chúng ta đã định nghĩa, nhưng trong file mã máy thực thi thì logic này lại không hề xuất hiện vì vậy nên vấn đề sẽ phát sinh đối với các đồng nghiệp của chúng ta. Và các vấn đề liên quan đến thiết kế phần mềm cũng sẽ bắt đầu từ đây.

Trong thiết kế phần mềm thì chúng ta thường cố gắng đóng gói các thuật toán hoặc các *"mẫu code" (concept)* thành các *module* để có thể tái sử dụng. Điều này lại ngược lại với macro vì nó luôn cố gắng đưa mọi thứ về dạng *code thô* có nghĩa là nó ghi trực tiếp các lệnh vào mã nguồn cho dù là các dòng code này có thể là lặp đi lặp lại. Điều này ngược với tính chất *tái sử dụng* trong tư duy thiết kế phần mềm.

Cũng vì macro cố gắng đưa mọi thứ về dạng *code thô* nên khi xây dựng các khối logic bằng macro trong thiết kế phần mềm thì các thông tin liên quan đến chúng có thể sẽ bị mất khi đi qua bước tiền xử lý. Đó là lý do tại sao các nhà thiết kế phần mềm sử dụng quy tắc ngón tay cái về macro:

>**If a macro can be written as a C function, then you should write a C function instead!**

Nếu nhìn từ gốc độ gỡ lỗi (debug) thì macro giống như là 1 nỗi đau của các lập trình viên. Trong quá trình làm việc thì các lập trình viên thường sẽ dựa vào *compilation errors*, *logs*, *compilation warnings* để tìm ra nơi nào xuất hiện lỗi (thường là những lỗi cú pháp) và fix nó. Nhưng có có 1 điều đặc biệt đối với các trình biên dịch C cũ đó là chúng không biết gì về quá trình tiền xử lý cả. Vì vậy khi 1 lập trình viên nhìn vào mã nguồn C với macro và mã nguồn khi khi đã qua tiền xử lý thay thế hết macro thì chúng như là 2 thế giới khác nhau vậy. Điều này gây ra sự khó khăn trong việc hiểu các *errors* và *warnings* mà trình biên dịch thông báo. Tất nhiên là từ việc khó hiểu đó nó lại sinh ra sự khó chịu và tiêu tốn nhiều thời gian ngồi dò lại code và fix bug rồi.

Tuy nhiên điều này cũng bớt căng thẳng đi phần nào khi các trình biên dịch hiện đại ngày nay như GCC hay Clang đã có thêm hiểu biết về quá trình tiền xử lý. Các trình biên dịch hiện đại này có thể đưa ra các cảnh báo hoặc lỗi theo như mã nguồn mà các lập trình viên đã code ra (tức là mã nguồn chưa qua tiền xử lý). Dù vậy thì các vấn đề của macro liên quan đến debug vẫn ít nghiêm trọng hơn các vấn đề liên quan đến thiết kế phần mềm mà chúng ta đã thảo luận ở trước.

## **Nguồn**

- Extreme C: Taking you to the limit in Concurrency, OOP, and the most advanced capabilities of C 1st Edition - Kamran Amini (PDF Book)
- <https://en.cppreference.com/w/c/preprocessor>
