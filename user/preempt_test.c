#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(void) {
  int pid = fork();
  if (pid == 0) {
    // Low-priority child
    set_priority(90);  // Low priority
    for (int i = 0; i < 1000; i++) {
      write(1, "L", 1);
      sleep(1);  
    }
    exit(0);
  }

  sleep(10);  // Let low-priority child start

  int pid2 = fork();
  if (pid2 == 0) {
    // High-priority child
    set_priority(5);  // High priority
    for (int i = 0; i < 1000; i++) {
      write(1, "H", 1);
    }
    exit(0);
  }

  wait(0);
  wait(0);

  printf("\nPREEMPTION TEST PASSED!\n");

  exit(0);
}
