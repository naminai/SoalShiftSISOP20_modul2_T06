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
#include <signal.h>
#include <wait.h>

int main(int argc,char* argv[]) { 

  pid_t pid, sid;        // Variabel untuk menyimpan PID
  pid_t child_id;

  pid = fork();     // Menyimpan PID dari Child Process
  child_id = fork();
  /* Keluar saat fork gagal
  * (nilai variabel pid < 0) */
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }

  /* Keluar saat fork berhasil
  * (nilai variabel pid adalah PID dari child process) */
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
  
  if (child_id < 0) {
    exit(EXIT_FAILURE);
  }

  while (1){
      char newFile[100];
      char file[100];
      char url[100];
      char dirList[100];
      char zipFIle[100];
      time_t rawtime, loctime;
      struct tm * cur_time, * nex_time;
      rawtime = time(NULL);
      loctime = localtime (&rawtime);  
      strftime(file, 100, "/home/it/Desktop/%Y-%m-%d_%H:%M:%S", loctime);
      strftime(zipFIle, 100, "%Y-%m-%d_%H:%M:%S", loctime);

      if(fork()==0){
        execl("/bin/mkdir","mkdir","-p",file, NULL);
      }
      if(fork()==0){
        for(int i=0; i<20 ;i++){
          cur_time = time(NULL);
          nex_time = localtime(&cur_time);

          if(fork()==0){
            strftime(file1, 100, "/%Y-%m-%d_%H:%M:%S", nex_time);
            strcat(file, file1);
            int size = ((cur_time % 1000) + 100);
            sprintf(url,"https://picsum.photos/%d",size);
            execl("/usr/bin/wget","wget","-O", file, url, NULL);
          }
          sleep(5);
        }
        pid = wait(NULL);
        if(fork()==0){   
          execl("/usr/bin/zip","zip","-rm", zipFile, zipFile, NULL);
        }
      }
    sleep(30);     
    }
}
