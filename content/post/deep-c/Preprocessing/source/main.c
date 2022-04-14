#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define VERSION "1.4.22"
#define LOG_ERROR(format, ...) \
  fprintf(stderr, format, __VA_ARGS__)

int main(int argc, char **argv)
{
    if(argc != 3){
    LOG_ERROR("Chương trình chỉ nhận 2 tham số đầu vào ====> VERSION: %s\n.", VERSION);
    exit(-1);
  }
  int x = atoi(argv[1]);
  int y = atoi(argv[2]);

  if(y == 0){
    LOG_ERROR("Lỗi không thể chia cho 0 ====> VERSION: %s\n.", VERSION);
    exit(-1);
  }
  else
    return x/y;
}
