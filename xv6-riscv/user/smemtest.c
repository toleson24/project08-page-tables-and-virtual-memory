#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
memcheck(char *addr, int c, int n)
{
  int match = 1;

  for(int i = 0; i < n; i++){
    if(addr[i] != c){
      // printf("memcheck: a=%d, addr[%d]=%d\n", c, i, addr[i]);  // TODO remove
      match = 0;
      break;
    }
  }
  
  return match;
}

void
memcheck_print(char *name, char *addr, int c, int n){
  int r;

  r = memcheck(addr, c, n);
  if(r == 0){
    printf("[%s] memcheck(%p, %c, %d) failed\n", name, addr, c, n);
    exit(-1);
  }
  printf("[%s] memcheck(%p, %c, %d) succeeded\n", name, addr, c, n);
}

void
smemtest(int n)
{
  char *smem_addr = (char *) 0x40000000;
  int smem_size;
  char smem_start_char = 'a';
  char smem_end_char = 'b';
  
  int r;
  int id;

  smem_size = n * 4096;
  // printf("smemtest n=%d, smem_size=%d\n", n, smem_size);  // TODO remove

  // Create shared memory region at VA 1GB
  // printf("before smem\n");  // TODO remove
  r = smem(smem_addr, smem_size);
  // printf("after smem r=%d\n", r);  // TODO remove
  if(r < 0){
    printf("smem(%p, %d) failed\n", smem_addr, smem_size);
    exit(-1);
  }

  // Initialize shared memory region to all 'a's
  // printf("before memset\n", r);  // TODO remove
  // printf("memset(%p, %c, %d)\n", smem_addr, smem_start_char, smem_size);  // TODO remove
  memset(smem_addr, smem_start_char, smem_size);
  // printf("after memset\n", r);  // TODO remove
  memcheck_print("parent_pre", smem_addr, smem_start_char, smem_size);

  // Fork a child, which should inherit the shared region
  id = fork();

  if(id == 0){
    // In child
    // printf("child running\n");
    memcheck_print("child_pre", smem_addr, smem_start_char, smem_size);
    // printf("before child memset\n");  // TODO remove
    memset(smem_addr, smem_end_char, smem_size);
    // printf("after child memset\n");  // TODO remove
    memcheck_print("child_post", smem_addr, smem_end_char, smem_size);

    // printf("child exiting\n");
    exit(0);
  }
  // printf("parent waiting\n");

  // In parent
  wait(0);
  // printf("parent running\n");

  memcheck_print("parent_post", smem_addr, smem_end_char, smem_size);
}


int
main(int argc, char **argv)
{
  int n;
  int p1, p2, diff;
  
  int id;

  if(argc != 2){
    printf("usage: smemtest <npages>\n");
    exit(-1);
  }

  n = atoi(argv[1]);

  p1 = kpages();

  id = fork();
  if(id == 0){
    smemtest(n);
    exit(0);
  }else{
    wait(0);
  }

  p2 = kpages();

  diff = p1 - p2;
  printf("[main] kpages() diff = %d\n", diff);

  return 0;
}
