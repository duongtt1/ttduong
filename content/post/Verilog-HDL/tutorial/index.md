---
title: Giới thiệu Verilog-HDL (P1)
subtitle: Verilog là ngôn ngữ mô tả phần cứng được sử dụng để mô hình hóa các hệ thống điện tử. Nó được sử dụng phổ biến nhất trong thiết kế và xác minh các mạch kỹ thuật số ở trừu tượng mức chuyển thanh ghi.

# Summary for listings and search engines
summary: Verilog là ngôn ngữ mô tả phần cứng (hardware description language, viết tắt là HDL) được sử dụng để mô hình hóa các hệ thống điện tử. Nó được sử dụng phổ biến nhất trong thiết kế và xác minh các mạch kỹ thuật số ở trừu tượng mức chuyển thanh ghi. Nó cũng được sử dụng trong việc xác minh các mạch tương tự và mạch tín hiệu hỗn hợp, cũng như trong thiết kế các mạch di truyền.

# Link this post with a project
projects: []

# Date published
date: "2022-04-03T00:00:00Z"

# Date updated
lastmod: "2022-04-03T00:00:00Z"

# Is this an unpublished draft?
draft: false

# Show this page in the Featured widget?
featured: false

# Featured image
# Place an image named `featured.jpg/png` in this page's folder and customize its options here.
image:
  caption: 'Image credit: [**Digilent**](https://digilent.com/reference/_media/learn/fundamentals/digital-logic/verilog-hdl-the-first-example/firstexample.png)'
  focal_point: ""
  placement: 2
  preview_only: false

authors:
- admin

tags:
- Verilog-HDL

categories:
- Verilog-HDL
---

### **Overview**

Verilog, được tiêu chuẩn hóa thành IEEE 1364, là ngôn ngữ mô tả phần cứng (hardware description language, viết tắt: HDL) được sử dụng để mô hình hóa các hệ thống điện tử. Nó được sử dụng phổ biến nhất trong thiết kế và xác minh các mạch kỹ thuật số ở trừu tượng mức chuyển thanh ghi. Nó cũng được sử dụng trong việc xác minh các mạch tương tự và mạch tín hiệu hỗn hợp, cũng như trong thiết kế các mạch di truyền. Vào năm 2009, tiêu chuẩn Verilog (IEEE 1364-2005) đã được hợp nhất vào tiêu chuẩn SystemVerilog, tạo ra tiêu chuẩn IEEE 1800-2009. Kể từ đó, Verilog chính thức là một phần của ngôn ngữ SystemVerilog. Phiên bản hiện tại là tiêu chuẩn IEEE 1800-2017.

Trước khi Verilog-HDL ra đời tất cả các thiết kế bất kể là phức tạp hay đơn giản đều dựa trên việc thiết kế schematics. Điều này làm khó khăn hơn cho việc xác minh và dễ xảy ra lỗi, chu kỳ phát triển lại tốn nhiều thời gian mà công việc lại tẻ nhạt, chỉ đơn thuần verification... design, verification... design, verification...

Khi Verilog ra đời đã tạo ra 1 làn sóng mới trong việc thiết kế mạch logic, thông qua chuỗi bài viết này chúng ta sẽ lần lượt tìm hiểu các nội dung sau:

1. Specifications (specs)
2. High level design
3. Low level (micro) design
4. RTL coding
5. Verification
6. Synthesis

Ở những phần tiếp theo chúng ta sẽ cùng nhau đi xây dựng khối Aribiter. Nếu bạn chưa biết khối Aribiter là cái gì ? thì nên đọc qua trước bài viết này trước [Tìm hiểu về round robin arbiter - semiconvn.com](https://www.semiconvn.com/home/hoc-thiet-ke-vi-mach/bai-hc-vi-mch/12787-tim-hiu-v-round-robin-arbiter.html) sau đó có thể quay lại để đọc tiếp vì phần sau sẽ không tập trung vào giải thích kỹ lưỡng về chức năng của khối này mà chỉ nói sơ qua chủ yếu tập trung đến việc xây dựng nó bằng verilog.

### **Block diagram của khối Arbiter**

![Aribiter Signal!](./images/aribiter_signal.png "Aribiter Signal")

Nếu  muốn thiết kế máy trạng thái như trên mà không sử dụng Verilog thì thường chúng ta sẽ phải vẽ 1 máy trạng thái, từ đây chúng ta sẽ lập ra bảng sự thật với các chuyển đổi trạng thái cho mỗi con Flip-Flop. Sau đó thực hiện vẽ bìa Karnaugh từ bìa Karnaugh chúng ta có thể đơn giản các cổng luận lý và cuối cùng ra được mạch. Cách làm này ở những mạch nhỏ thì vẫn có thể ổn, nhưng khi mạch trở nên phức tạp thì cách làm này trở nên phức tạp và tiềm ẩn nhiều lỗi phát sinh. Và rồi Verilog ra đời và cho chúng ta 1 hướng tiếp cận khác để thiết kế mạch, chi tiết hơn thì chúng ta cùng đi tới phần tiếp theo.

### **Low level design**

Để xem cách Verilog giúp chúng ta thiết kế Aribiter như thế nào thì trước tiên chúng ta sẽ cùng nhau xem qua sơ đồ máy trạng thái của nó.

![FSM Aribiter!](./images/aribiter_fsm.png "FSM Aribiter")

Mỗi vòng tròn đại diện cho một trạng thái. Mỗi trạng thái tương ứng với một đầu ra. Các mũi tên giữa các trạng thái tức là chuyển đổi trạng thái, được gắn nhãn bởi sự kiện gây ra chuyển đổi.

Ví dụ: mũi tên màu cam ngoài cùng bên trái có nghĩa là nếu máy ở trạng thái GNT0 (xuất tín hiệu tương ứng với GNT0) và nhận đầu vào là !Req_0 máy sẽ chuyển sang trạng thái IDLE và xuất tín hiệu tương ứng với trạng thái IDLE.

Máy trạng thái này mô tả tất cả logic của hệ thống mà bạn cần để có thể tự tay thiết kế ra mạch Aribiter dựa trên các cổng luận lý số (AND, OR, XOR, NOT,...). Nhưng mà nội dung chính của chúng ta là Verilog nên bước tiếp theo chúng ta sẽ xây dựng nó bằng Verilog ở phần số 2 của seri này.

### Nguồn tham khảo

* [Verilog In One Day Part-I](https://www.asic-world.com/verilog/verilog_one_day1.html#Introduction)
* [Tìm hiểu về round robin arbiter - semiconvn.com](https://www.semiconvn.com/home/hoc-thiet-ke-vi-mach/bai-hc-vi-mch/12787-tim-hiu-v-round-robin-arbiter.html)
