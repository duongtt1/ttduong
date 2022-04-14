#include <stdio.h>
#include <string.h>

#define CMD(NAME)              \
	char NAME##_cmd[256] = ""; \
	strcpy(NAME##_cmd, #NAME);

int main(int argc, char **argv)
{
	CMD(copy)
	CMD(paste)
	CMD(delete)

  if (strcmp(argv[1], copy_cmd) == 0) {
    printf("copy_cmd");
  }
  if (strcmp(argv[1], paste_cmd) == 0) {
    printf("paste_cmd");
  }
  if (strcmp(argv[1], delete_cmd) == 0) {
    printf("delete_cmd");
  }
	return 0;
}
