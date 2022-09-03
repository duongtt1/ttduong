---
title: Tiền xử lý trong C (Phần 3)
subtitle: Qua 2 phần vừa rồi chúng ta đã tìm hiểu được các kiến thức cơ bản của macro, ở Phần 3 này chúng ta sẽ tản mạn 1 chút về các vấn đề khi sử dụng nó để có thể sử dụng nó tốt nhất.

# Summary for listings and search engines
summary: Qua 2 phần vừa rồi chúng ta đã tìm hiểu được các kiến thức cơ bản của macro, ở Phần 3 này chúng ta sẽ tản mạn 1 chút về các vấn đề khi sử dụng nó để có thể sử dụng nó tốt nhất. 

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

## **Tản mạn về macro**

Macro có một đặc tính rất đặc biệt đó là sau quá trình tiền xử lý thì toàn bộ các macro sẽ được thay thế bằng các dòng\đoạn code khác. Điều này làm cho mã nguồn trở nên dài hơn và tuần tự. Cũng vì vậy mà mã nguồn tại thời điểm biên dịch sẽ không có module nào cả. Nếu chính ta là tác giả của mã nguồn trên thì mọi chuyện có vẻ như sẽ đỡ căng thẳng khi chúng ta vẫn sẽ nhớ được các logic về macro mà chúng ta đã định nghĩa, nhưng trong file mã máy thực thi thì logic này lại không hề xuất hiện vì vậy nên vấn đề sẽ phát sinh đối với các đồng nghiệp của chúng ta. Và các vấn đề liên quan đến thiết kế phần mềm cũng sẽ bắt đầu từ đây.

Trong thiết kế phần mềm thì chúng ta thường cố gắng đóng gói các thuật toán hoặc các *"mẫu code" (concept)* thành các *module* để có thể tái sử dụng. Điều này lại ngược lại với macro vì nó luôn cố gắng đưa mọi thứ về dạng *code thô* có nghĩa là nó ghi trực tiếp các lệnh vào mã nguồn cho dù là các dòng code này có thể là lặp đi lặp lại. Điều này ngược với tính chất *tái sử dụng* trong tư duy thiết kế phần mềm.

Cũng vì macro cố gắng đưa mọi thứ về dạng *code thô* nên khi xây dựng các khối logic bằng macro trong thiết kế phần mềm thì các thông tin liên quan đến chúng có thể sẽ bị mất khi đi qua bước tiền xử lý. Đó là lý do tại sao các nhà thiết kế phần mềm sử dụng quy tắc ngón tay cái về macro:

>**If a macro can be written as a C function, then you should write a C function instead!**

Nếu nhìn từ gốc độ gỡ lỗi (debug) thì macro giống như là 1 nỗi đau của các lập trình viên. Trong quá trình làm việc thì các lập trình viên thường sẽ dựa vào *compilation errors*, *logs*, *compilation warnings* để tìm ra nơi nào xuất hiện lỗi (thường là những lỗi cú pháp) và fix nó. Nhưng có 1 điều đặc biệt đối với các trình biên dịch C cũ đó là chúng không biết gì về quá trình tiền xử lý cả. Vì vậy khi 1 lập trình viên nhìn vào mã nguồn C với macro và mã nguồn khi khi đã qua tiền xử lý thay thế hết macro thì chúng như là 2 thế giới khác nhau vậy. Điều này gây ra sự khó khăn trong việc hiểu các *errors* và *warnings* mà trình biên dịch thông báo. Tất nhiên là từ việc khó hiểu đó nó lại sinh ra sự khó chịu và tiêu tốn nhiều thời gian ngồi dò lại code và fix bug rồi.

Tuy nhiên điều này cũng bớt căng thẳng đi phần nào khi các trình biên dịch hiện đại ngày nay như GCC hay Clang đã có thêm hiểu biết về quá trình tiền xử lý. Các trình biên dịch hiện đại này có thể đưa ra các cảnh báo hoặc lỗi theo như mã nguồn mà các lập trình viên đã code ra (tức là mã nguồn chưa qua tiền xử lý). Dù vậy thì các vấn đề của macro liên quan đến debug vẫn ít nghiêm trọng hơn các vấn đề liên quan đến thiết kế phần mềm mà chúng ta đã thảo luận ở trước.

Thêm một vấn đề nữa mà chúng ta đã từng thảo luận ở phần trước, Đó là về sự đánh đổi giữa kích thước file thực thi và hiệu suất khi sử dụng macro trong C. Một dạng tổng quát hơn của vấn đề này đó là *một file thực thi lớn duy nhất* hay *nhiều file module nhỏ* nhiều file ở đây có thể là các file module, các thư viện (kể cả thư viện động lẫn thư viện tĩnh). Cả 2 cách trên đều cho 1 chức năng y hệt nhau nhưng về mặt hiệu năng thì có vẻ như cách làm đầu tiên có hiệu năng tốt hơn, mặc dù tốt hơn cũng không nhiều. Thường thì trong 1 dự án đặc biệt là các dự án lớn được phát triển trên các thiết kế phần mềm tốt thì số file thực thi và kích thước của chúng được các lập trình viên tính toán cẩn thận. Và thường sẽ bao gồm nhiều tệp thực thi nhẹ với kích thước tối thiểu có thể áp dụng, thay vì chỉ có một thực thi khổng lồ.

>Thiết kế phần mềm luôn cố gắng chia nhỏ các thành phần trong phần mềm ra thành các module nhỏ lẻ hơn và có tính tái sử dụng cao. Và điều này về bản chất lại ảnh hưởng tới hiệu suất mặc dù ảnh hưởng của nó đối với hiệu suất là rất nhỏ trong hầu hết các trường hợp.

Nếu vậy thì việc sử dụng các macro đang đối đầu lại với các thiết kế phần mềm ??? hm....Không hẳn là như vậy. Như đã thảo luận ở phần trước về việc chúng ta phải đánh đổi giữa *thiết kế* và *hiệu năng*, khi chúng ta cần hiệu năng thì đôi khi chúng ta sẽ phải hy sinh đi 1 chút thiết kế. Ví dụ minh hoạ tốt nhất có việc này đó là kỹ thuật *loop unrolling* đây cũng chính là ví dụ LOOP của chúng ta ở phần trước. Trong ví dụ đó chúng ta đã sử dụng macro để bắt trước 1 vòng lặp và biến đổi vòng lặp thành tập hợp cách lệnh được sắp xếp theo tuần tự. Đây chỉ là 1 cách ví dụ cho việc macro có thể được sử dụng để điều chỉnh hiệu suất trong trong các chương trình nhúng và các môi trường mà một thay đổi nhỏ trong cách thực thi các lệnh sẽ làm  hiệu suất tăng đáng kể. Ngoài ra macro có thể ứng dụng được ở rất nhiều việc khác.

>*loop unrolling* tức là loại bỏ đi các vòng lặp và làm cho chúng tuần tự để tăng hiệu suất và tránh các chi phí lặp lại trong khi chạy vòng lặp. Chúng được sử dụng nhiều trong phát triển các chương trình nhúng trên các thiết bị có phần cứng hạn chế.

Có 1 điểm nữa là để đạt được hiệu suất tốt nhất có thể thì chúng ta nên để CPU thực thi các lệnh 1 cách tuần tự và cố gắng đừng bắt CPU phải nhảy qua nhảy lại giữa các phần khác nhau trong mã nguồn. Để làm được điều này thì có đa dạng cách như sửa đổi thuật toán,... Nhưng điều này lại bị mẫu thuẫn với các tính chất của thiết kế phần mềm như chúng ta đã thảo luận ở trước, việc thiết kế luôn mong muốn chia nhỏ và hệ thống hoá các thành phần trong phần mềm điều này lại làm nó mất đi tính tuần tự. Vì vậy, việc đánh đổi giữa hiệu năng và thiết kế này cần được quan tâm và cân đối cho từng vấn đề riêng biệt.

Còn 1 ứng dụng phổ biến nữa của macro đó là *DSLs*. *Microsoft MFC*, *Qt*, *Linux Kernel*, and *wxWidgets* và hàng nghìn dự án khác đang sử dụng macro để tạo ra các *DSLs* của riêng họ. Hầu hết đều là các dự án C++ nhưng vẫn sử dụng tính năng này của C để tạo ra các bộ API.

Qua các thảo luận trên thì có thể thấy macro tuy có nhiều ưu điểm nhưng khi sử dụng chúng ta cần xem xét cẩn thận tuỳ vào từng trường hợp cụ thể. Nếu quá lạm dụng macro có thể gây ra nhiều vấn đề khó khăn không chỉ cho bạn và còn khó khăn cho cả đồng đội của bạn nữa.

## **Nguồn tham khảo**

- Extreme C - Kamran Amini (PDF Book)
- <https://en.cppreference.com/w/c/preprocessor>
