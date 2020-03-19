#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <syslog.h>
#include <string.h>
#include <time.h>

int main (int jumlah, char *argumen[]) {
  pid_t pid, sid;
  pid = fork();

  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }

  umask(0);

  sid = setsid();
  if (sid < 0) {
    exit(EXIT_FAILURE);
  }

  close(STDIN_FILENO);
  close(STDOUT_FILENO);
  close(STDERR_FILENO);

  int detik = -1;
  int menit = -1;
  int jam = -1;
  time_t waktu = time(NULL);
  struct tm cTime = *localtime(&waktu);
  if (jumlah != 5) {
    printf ("Argumen terlalu banyak / terlalu sedikit, pastikan pas\n");
  }
  if (argumen[1][0] != '*') detik = atoi(argumen[1]);
  if (argumen[2][0] != '*') menit = atoi(argumen[2]);
  if (argumen[3][0] != '*') jam = atoi(argumen[3]);

  if (detik>=60) {
    printf("Detiknya tuh kebanyakan, kurangin dong\n");
  }
  if (detik<0) {
    printf("Detiknya tuh kurang banyak, banyakin dong\n");
  }
  if (menit>=60) {
    printf("Menitnya tuh kebanyakan, kurangin dong\n");
  }
  if (menit<0) {
    printf("Menitnya tuh kurang banyak, tambahin dong\n");
  }
  if (jam>=25) {
    printf("Jamnya tuh kebanyakan, tambahin dong\n");
  }
  if (jam<0) {
    printf("Jamnya tuh kurang banyak, tambahin dong\n");
  }

  while (1) 
  {
  waktu = time(NULL);
  cTime = *localtime(&waktu);
  if ((cTime.tm_hour == jam || jam == -1) && (cTime.tm_min == menit || menit == -1) && (cTime.tm_sec == detik || detik == -1)) {
    if (fork()==0)
      execl("/bin/bash", "bash", argumen[4], NULL);}
      sleep(1);
  }
}     
