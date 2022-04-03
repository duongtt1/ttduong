---
title: Giới thiệu Verilog-HDL 
subtitle: Verilog là ngôn ngữ mô tả phần cứng được sử dụng để mô hình hóa các hệ thống điện tử. Nó được sử dụng phổ biến nhất trong thiết kế và xác minh các mạch kỹ thuật số ở trừu tượng mức chuyển thanh ghi.

# Summary for listings and search engines
summary: Verilog, được tiêu chuẩn hóa thành IEEE 1364, là ngôn ngữ mô tả phần cứng (hardware description language, viết tắt là HDL) được sử dụng để mô hình hóa các hệ thống điện tử. Nó được sử dụng phổ biến nhất trong thiết kế và xác minh các mạch kỹ thuật số ở trừu tượng mức chuyển thanh ghi. Nó cũng được sử dụng trong việc xác minh các mạch tương tự và mạch tín hiệu hỗn hợp, cũng như trong thiết kế các mạch di truyền.

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

## Overview

Verilog, được tiêu chuẩn hóa thành IEEE 1364, là ngôn ngữ mô tả phần cứng (hardware description language, viết tắt: HDL) được sử dụng để mô hình hóa các hệ thống điện tử. Nó được sử dụng phổ biến nhất trong thiết kế và xác minh các mạch kỹ thuật số ở trừu tượng mức chuyển thanh ghi. Nó cũng được sử dụng trong việc xác minh các mạch tương tự và mạch tín hiệu hỗn hợp, cũng như trong thiết kế các mạch di truyền. Vào năm 2009, tiêu chuẩn Verilog (IEEE 1364-2005) đã được hợp nhất vào tiêu chuẩn SystemVerilog, tạo ra tiêu chuẩn IEEE 1800-2009. Kể từ đó, Verilog chính thức là một phần của ngôn ngữ SystemVerilog. Phiên bản hiện tại là tiêu chuẩn IEEE 1800-2017.

Trước khi Verilog-HDL ra đời tất cả các thiết kế bất kể là phức tạp hay đơn giản đều dựa trên việc thiết kế schematics. Điều này làm khó khăn hơn cho việc xác minh và dễ xảy ra lỗi, chu kỳ phát triển lại tốn nhiều thời gian mà công việc lại tẻ nhạt, chỉ đơn thuần verification... design, verification... design, verification...

Khi Verilog ra đời đã tạo ra 1 làn sóng mới trong việc thiết kế mạch logic, thông qua chuỗi bài viết này chúng ta sẽ lần lượt tìm hiểu các nội dung sau:

1. Specifications (specs)
2. High level design
3. Low level (micro) design
4. RTL coding
5. Verification
6. Synthesis

## Block diagram of arbiter

![Aribiter Signal!](/content/post/Verilog-HDL/tutorial/images/aribiter_signal.png "Aribiter Signal")
