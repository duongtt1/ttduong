---
title: Giới thiệu Verilog-HDL
subtitle: Các kiểu dữ liệu cơ bản trong Verilog

# Summary for listings and search engines
summary: Các kiểu dữ liệu cơ bản trong Verilog 

# Link this post with a project
projects: []

# Date published
date: "2022-04-17T00:00:00Z"

# Date updated
lastmod: "2022-04-17T00:00:00Z"

# Is this an unpublished draft?
draft: true

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


>Trước khi bắt đầu hãy chắc rằng bạn đã biết qua về kiến thức cơ bản của **Nhập môn mạch số** và **Thiết kế luận lý số**.  Bài viết này không tập trung vào các kiến thức mạch số cơ bản mà chỉ tập trung vào việc sử dụng Verilog để hiện thực hóa chúng.

## **Các kiểu dữ liệu trong Verilog**

Khác với C hay các ngôn ngữ lập trình khác, Verilog có một vài kiểu dữ liệu mới. Các kiểu dữ liệu này giúp cho việc mô tả phần cứng trở nên dễ dàng và dễ hiểu hơn. Tuy có nhiều kiểu nhưng về cơ bản chúng được chia làm 2 loại: **NETS** và **Registers**. Các kiểu dữ liệu này khác nhau về cách chúng được gán và giữ các giá trị, đồng thời chúng cũng mổ tả cho các cấu trúc phần cứng khác nhau.

Bộ giá trị Verilog HDL bao gồm bốn giá trị cơ bản:

- **0**: Giá trị logic 0 hoặc là False
- **1**: Giá trị logic 1 hoặc là True
- **X**: Giá trị logic Không xác định
- **Z**: Trở kháng cao

## **Kiểu dữ liệu số nguyên và số thực**

Verilog đã giới thiệu các kiểu dữ liệu hai trạng thái mới (two-state). Ở trong kiểu dữ liệu này thì giá trị của mỗi bit là *0* hoặc *1*. Việc sử dụng biến 2 trạng thái ở trong mô hình RTL sẽ giúp cho phép trình mô phỏng hoạt động hiểu quả hơn và chúng cũng không ảnh hưởng đến quá trình tổng hợp (synthesis).

| Kiểu   |      Kích thước     |
|--------|---------------------|
| bit |  Tự định nghĩa kích thước khi khai báo  |
| byte |    8 bits (signed) |
| shortint | 16 bits (signed)|
| int | 32 bits (signed)|
| longint | 64 bits (signed) |

### **Kiểu dữ liệu 2 trạng thái số nguyên**

## **Nguồn tham khảo**

- <https://www.asic-world.com/verilog/verilog_one_day.html>
