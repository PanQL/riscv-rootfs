#include <common.h>
#include <sys/time.h>
#include <time.h>

void _putc(int ch) {
  putchar(ch);
}

static struct timeval boot_time = {};

uint32_t uptime() {
  struct timeval now;
  gettimeofday(&now, NULL);
  long seconds = now.tv_sec - boot_time.tv_sec;
  long useconds = now.tv_usec - boot_time.tv_usec;
  return seconds * 1000 + (useconds + 500) / 1000;
}

void _ioe_init() {
  gettimeofday(&boot_time, NULL);
}

int screen_width() {
  return 320;
}

int screen_height() {
  return 240;
}
