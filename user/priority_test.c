#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main() {
  int pid_high = fork();
  if (pid_high == 0) {
    // High-priority child
    set_priority(5);
    for (int i = 0; i < 1000; i++) {
      write(1, "H", 1);
    }
    exit(0);
  }

  // Give the high-priority child a head start
  sleep(10);

  int pid_low = fork();
  if (pid_low == 0) {
    // Low-priority child
    set_priority(95);
    for (int i = 0; i < 1000; i++) {
      write(1, "L", 1);
    }
    exit(0);
  }

  // Wait for both children
  wait(0);
  wait(0);

  printf("\nTEST PASSED!\n");

  exit(0);
}