#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <pwd.h>
#include <spawn.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

const char* exec = "/usr/bin/ccache";
const char* gcc = "/usr/bin/gcc";
//const char* exec = "/bin/echo";
extern char** environ;
void print_args(const char** args)
{
  int idx = 0;
  printf("CHAM: ");
  while (args[idx]) {
    printf("%s ", args[idx]);
    ++idx;
  }
  printf("\n");
}

#define PLS 1024 * 16
char playground[PLS];

void print_compile_command(char* argv[])
{
  struct passwd* pw = getpwuid(getuid());
  sprintf(playground, "%s/compile_commands.json", pw->pw_dir);
  int arg;

  for (arg = 0;; ++arg) {
    if (argv[arg] == NULL)
      break;

    if (argv[arg][0] && argv[arg][0] == '-' && argv[arg][1] && argv[arg][1] == 'c' && argv[arg][2] == '\0') {
      break;
    }
  }
  if (argv[arg] == NULL) {
    return;
  }
  const char* file = argv[arg + 1];

  FILE* o = fopen(playground, "a");
  if (o == NULL) {
    fprintf(stderr, "CHAM %d: open %s failed\n", __LINE__, playground);
    return;
  }
  if (0 != flock(fileno(o), LOCK_EX)) {
    fprintf(stderr, "CHAM %d: flock failed\n", __LINE__);
    return;
  }
  fputs("{\n  \"directory\":\"", o);
  if (NULL == getcwd(playground, PLS)) {
    fprintf(stderr, "CHAM %d: getcwd failed\n", __LINE__);
    fclose(o);
    return;
  }
  fputs(playground, o);
  fputs("\",\n  \"file\":\"", o);
  fputs(file, o);
  fputs("\",\n  \"command\":\"", o);
  for (int arg = 0;; ++arg) {
    if (argv[arg] == NULL)
      break;
    char* b = argv[arg];
    char* e = b;
    while (*e) {
      if (*e == '"') {
        char c = *e;
        *e = '\0';
        fputs(b, o);
        fputc('\\', o);
        *e = c;
        b = e;
      }
      ++e;
    }
    fputs(b, o);
    fputc(' ', o);
  }
  fputs("\"\n},\n", o);
  fclose(o);
}

int main(int argc, char* argv[])
{
  int max_args = argc + 10;
  const char** filtered_args = (const char**)malloc(max_args * sizeof(char*));
  int fpos = 0;
  int pos;
  char *x, *y;
  char target[100] = "/usr/bin/";
  y = argv[0];
  for (x = argv[0]; *x != 0; ++x) {
    if (*x == '/')
      y = x + 1;
  }
  strcat(target, y);
  bool comp = true;
  filtered_args[fpos++] = "ccache";
  //filtered_args[fpos++] = y;
  filtered_args[fpos++] = target; //"/usr/bin/gcc";

  for (pos = 1; pos < argc; ++pos) {
    if (argv[pos][0] == '\0')
      continue;
    if (strstr(argv[pos], "-O0") != NULL)
      continue;
    if (strstr(argv[pos], "-fomit-frame-pointer") != NULL)
      continue;
    if (strstr(argv[pos], "-g") == argv[pos])
      continue;
    if (strstr(argv[pos], "-Wl,-S") == argv[pos])
      continue;
    if (strstr(argv[pos], "-fuse-ld=gold") != NULL) {
      exec = gcc;
      comp = false;
      //continue;
    }
    filtered_args[fpos++] = argv[pos];
  }
  if (comp) {
    filtered_args[fpos++] = "-g1";
    filtered_args[fpos++] = "-O2";
    filtered_args[fpos++] = "-fno-omit-frame-pointer";
  } else { //linking
    filtered_args[fpos++] = "-Wl,--compress-debug-sections=none";
  }
  filtered_args[fpos++] = (char*)NULL;
  pid_t pid;
  int status;
  if (exec == gcc) {
    filtered_args[1] = gcc;
    print_args(&filtered_args[1]);
    status = posix_spawn(&pid, exec, NULL, NULL, (char* const*)&filtered_args[1], environ);
  } else {
    print_args(filtered_args);
    print_compile_command((char**)&filtered_args[1]);
    status = posix_spawn(&pid, exec, NULL, NULL, (char* const*)filtered_args, environ);
  }
  if (status == 0) {
    //printf("Child id: %i\n", pid);
    fflush(NULL);
    if (waitpid(pid, &status, 0) == -1) {
      return 1;
    } else {
      return WEXITSTATUS(status);
    }
  } else {
    printf("posix_spawn: %s\n", strerror(status));
    return 1;
  }
}
