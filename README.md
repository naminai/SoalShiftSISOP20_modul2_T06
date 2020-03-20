# SoalShiftSISOP20_modul2_T06 
Penyelesaian Soal Shift Modul 2 Sistem Operasi 2020\ 
Kelompok T06 
  * Donny Kurnia Ramadhani (05311840000004) 
  * Made Krisnanda Utama (0531184000033) 

--- 
## Daftar Isi 
* [Soal 1](#soal-1) 
  * [Soal 1.a.](#soal-1a) 
  * [Soal 1.b.](#soal-1b) 
  * [Soal 1.c.](#soal-1c) 
  * [Soal 1.d.](#soal-1d) 
  * [Soal 1.e.](#soal-1e) 
  * [Penyelesaian.](#penyelesaian) 
* [Soal 2](#soal-2) 
  * [Soal 2.a.](#soal-2a) 
  * [Soal 2.b.](#soal-2b) 
  * [Soal 2.c.](#soal-2c) 
  * [Soal 2.d.](#soal-2d) 
  * [Soal 2.e.](#soal-2e) 
  * [Penyelesaian.](#penyelesaian) 
* [Soal 3](#soal-3) 
  * [Soal 3.a.](#soal-3a) 
  * [Soal 3.b.](#soal-3b) 
  * [Soal 3.c.](#soal-3c) 
  * [Soal 3.d.](#soal-3d) 
  * [Penyelesaian.](#penyelesaian) 
* [Kendala]
--- 

## Soal 1 
Source Code : [source](https://github.com/naminai/SoalShiftSISOP20_modul2_T06/tree/master/soal1) 

**Deskripsi** 
Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan ketentuan sebagai berikut: 

### Soal 1.a. 

**Pertanyaan** 
Program menerima 4 argumen berupa: 
\
i. Detik: 0-59 atau * (any value) 
\
ii. Menit: 0-59 atau * (any value) 
\
iii. Jam: 0-23 atau * (any value) 
\
iv. Path file .sh 

### Soal 1.b. 

**Pertanyaan** 
Program akan mengeluarkan pesan error jika argumen yang diberikan tidak sesuai! 

### Soal 1.c. 

**Pertanyaan** 
Program hanya menerima 1 config cron! 

### Soal 1.d. 

**Pertanyaan** 
Program berjalan di background (daemon)! 

### Soal 1.e. 

**Pertanyaan** 
Tidak boleh menggunakan fungsi system()! 

## Penyelesaian. 

```
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
```

```  
  int detik = -1;
  int menit = -1;
  int jam = -1; 
  ```
  1. Deklarasi variabel detik, menit, dan jam dan set value mereka = -1.
  
  ``` 
  time_t waktu = time(NULL);
  struct tm cTime = *localtime(&waktu);
  ```
  1. Mencari waktu lokal (waktu terkini) menggunakan datatype time_t yang digunakan untuk menyimpan nilai waktu sistem dan mengisinya dengan time(NULL) yang akan me-return waktu terkini.
  2. Deklarasi structure tm bernama cTime, yang akan digunakan untuk mendapatkan nilai `tm_sec`(detik), `tm_min`(menit), `tm_hour`(jam).
  
  ```
  if (jumlah != 5) {
    printf ("Argumen terlalu banyak / terlalu sedikit, pastikan pas\n");
    }
  if (argumen[1][0] != '*') detik = atoi(argumen[1]);
  if (argumen[2][0] != '*') menit = atoi(argumen[2]);
  if (argumen[3][0] != '*') jam = atoi(argumen[3]);
  ```
  1. Melakukan pengecekan terhadap jumlah argumen yang diinput user, 5 argumen yaitu `argumen[0]` = nama program, `argumen[1]` = detik, `argumen[2]` = menit, `argumen[3]`= jam, `argumen[4]` = lokasi/nama file.
  2. Melakukan pengecekan terhadap masing-masing argumen, dimana apabila bukan char `*`, maka akan dikonversi dari string menjadi integer menggunakan `atoi`.
  
  ```
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
  ```
  1. Pengecekan detik, menit, dan jam.
  2. Menit dan detik lebih besar dari 60, karena terhitung dari 0-59.
  3. Jam lebih besar dari 25, karena terhitung dari 0-24.
  
  ```
  if ((cTime.tm_hour == jam || jam == -1) && (cTime.tm_min == menit || menit == -1) && (cTime.tm_sec == detik || detik == -1)) {
    if (fork()==0)
      execl("/bin/bash", "bash", argumen[4], NULL);}
      sleep(1);
  ```
  1. Melakukan pengecekan untuk jam, menit, dan detik terhadap waktu lokal. Terkecuali apabila jam = -1, maka kita perlakukan sebagai `*` atau any value. 
  2. Selain itu maka kita sesuaikan dengan jam, menit, maupun detik argumen. Apabila waktu lokal sama dengan argumen, maka program bash `argumen[4]` dijalankan dengan `execl`. 
  3. Sleep setiap 1 detik, agar daemon terus melakukan cek setiap detiknya (apabila `*` atau any value).

## Output Soal 1
![Modul 2 Soal 1](https://user-images.githubusercontent.com/61267430/77213670-4354d980-6b3e-11ea-969c-c5589d63dfc0.png)
![Modul2 Soal 1 bash](https://user-images.githubusercontent.com/61267430/77213715-67b0b600-6b3e-11ea-910f-450adeda82b8.png)
![Soal 1 isi bash](https://user-images.githubusercontent.com/61267430/77213784-ad6d7e80-6b3e-11ea-978b-d63e151d133c.png)

## Soal 2 
Source code : [source](https://github.com/naminai/SoalShiftSISOP20_modul2_T06/tree/master/soal2) 

**Deskripsi** 
Shisoppu mantappu! itulah yang selalu dikatakan Kiwa setiap hari karena sekarang dia merasa sudah jago materi sisop. Karena merasa jago, suatu hari Kiwa iseng membuat sebuah program. 

### Soal 2.a. 

**Pertanyaan** 
Pertama-tama, Kiwa membuat sebuah folder khusus, di dalamnya dia membuat sebuah program C yang per 30 detik membuat sebuah folder dengan nama timestamp [YYYY-mm-dd_HH:ii:ss]. 

### Soal 2.b. 

**Pertanyaan** 
Tiap-tiap folder lalu diisi dengan 20 gambar yang di download dari https://picsum.photos/, dimana tiap gambar di download setiap 5 detik. Tiap gambar berbentuk persegi dengan ukuran (t%1000)+100 piksel dimana t adalah detik Epoch Unix. Gambar tersebut diberi nama dengan format timestamp [YYYY-mm-dd_HH:ii:ss]. 

### Soal 2.c.

**Pertanyaan**
Agar rapi, setelah sebuah folder telah terisi oleh 20 gambar, folder akan di zip dan folder akan di delete(sehingga hanya menyisakan .zip).

### Soal 2.d.

**Pertanyaan**
Karena takut program tersebut lepas kendali, Kiwa ingin program tersebut men- generate sebuah program "killer" yang siap di run(executable) untuk menterminasi semua operasi program tersebut. Setelah di run, program yang menterminasi ini lalu akan mendelete dirinya sendiri.

### Soal 2.e.

**Pertanyaan**
Kiwa menambahkan bahwa program utama bisa dirun dalam dua mode, yaitu MODE_A dan MODE_B. untuk mengaktifkan MODE_A, program harus dijalankan dengan argumen -a. Untuk MODE_B, program harus dijalankan dengan argumen -b. Ketika dijalankan dalam MODE_A, program utama akan langsung menghentikan semua operasinya ketika program killer dijalankan. Untuk MODE_B, ketika program killer dijalankan, program utama akan berhenti tapi membiarkan proses di setiap folder yang masih berjalan sampai selesai(semua folder terisi gambar, terzip lalu di delete).

## Penyelesaian.

```
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
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
      char zipFile[100];
      time_t rawtime, loctime;
      struct tm * cur_time, * nex_time;
      rawtime = time(NULL);
      cur_time = localtime (&rawtime);  
      strftime(file, 100, "/home/donny/modul2/%Y-%m-%d_%H:%M:%S", cur_time);
      strftime(zipFile, 100, "%Y-%m-%d_%H:%M:%S", cur_time);

      if(fork()==0)
      {
        execl("/bin/mkdir","mkdir","-p",file, NULL);
      }
      if(fork()==0){
        for(int i=0; i<20 ;i++){
          loctime = time(NULL);
          nex_time = localtime(&rawtime);
          if(fork()==0){
            strftime(newFile, 100, "/%Y-%m-%d_%H:%M:%S", nex_time);
            strcat(file, newFile);
            int file_size = ((loctime % 1000) + 100);
            sprintf(url,"https://picsum.photos/%d",file_size);
            execl("/usr/bin/wget","wget","-O", file, url, NULL);
          }
          sleep(5);
        }
        pid = wait(NULL);
        if(fork()==0){   
          execl("/usr/bin/zip","zip","-rm", zipFile, zipFile, NULL);
        }}
    sleep(30);     
    }}
```

```
char newFile[100];
      char file[100];
      char url[100];
      char dirList[100];
      char zipFile[100];
      time_t rawtime, loctime;
      struct tm * cur_time, * nex_time;
```
1. Deklarasi variabel seperti biasa dan juga struct tm dan time_t seperti soal nomor 1.
2. Menggunakan 2 variabel untuk masing-masing agar untuk folder dan image size.

```
strftime(file, 100, "/home/donny/modul2/%Y-%m-%d_%H:%M:%S", cur_time);
strftime(zipFile, 100, "%Y-%m-%d_%H:%M:%S", cur_time);
```
1. Menggunakan `strftime` untuk mendapatkan waktu sesuai dengan setting yang kita inginkan yaitu `%Y-%m-%d_%H:%M:%S"`.
2. Memasukkan kepada variabel file untuk dibuat menjadi nama folder.
3. Memasukkan kepada variabel zipFile untuk menjadi nama zip.

```
 if(fork()==0)
      {
        execl("/bin/mkdir","mkdir","-p",file, NULL);
      }
```
1. Menggunakan `execl` untuk menggunakan `mkdir` untuk membuat folder bernama `file` yang berarti waktu diunduhnya gambar.

```
if(fork()==0){
        for(int i=0; i<20 ;i++){
          loctime = time(NULL);
          nex_time = localtime(&rawtime);
          if(fork()==0){
            strftime(newFile, 100, "/%Y-%m-%d_%H:%M:%S", nex_time);
            strcat(file, newFile);
            int file_size = ((loctime % 1000) + 100);
            sprintf(url,"https://picsum.photos/%d",file_size);
            execl("/usr/bin/wget","wget","-O", file, url, NULL);
          }
```
1. Melakukan download sebanyak 20 kali dengan melakukan loop `for(int i=0; i<20 ;i++)`
2. Menggunakan integer `file_size` untuk menyimpan ukuran gambar.
3. Menggunakan sprintf untuk mendapatkan nama file berdasarkan `file_size` dan disimpan ke variabel `url`.
4. Mendownload gambar dari picsum.photos menggunakan `wget`.

## Output Soal 2
![Modul 2 Soal 2](https://user-images.githubusercontent.com/61267430/77213815-d0982e00-6b3e-11ea-8d7d-2f9eaf93d542.png)

## Soal 3
Source Code : [souce](https://github.com/naminai/SoalShiftSISOP20_modul2_T06/tree/master/soal3)

**Deskripsi**
Jaya adalah seorang programmer handal mahasiswa informatika. Suatu hari dia memperoleh tugas yang banyak dan berbeda tetapi harus dikerjakan secara bersamaan (multiprocessing).

### Soal 3.a.

**Pertanyaan**
Program buatan jaya harus bisa membuat dua direktori di “/home/[USER]/modul2/”. Direktori yang pertama diberi nama “indomie”, lalu lima detik kemudian membuat direktori yang kedua bernama “sedaap”.

### Soal 3.b.

**Pertanyaan**
Kemudian program tersebut harus meng-ekstrak file jpg.zip di direktori “/home/[USER]/modul2/”. Setelah tugas sebelumnya selesai, ternyata tidak hanya itu tugasnya.

### Soal 3.c.

**Pertanyaan**
Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan pengelompokan, semua file harus dipindahkan ke “/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke “/home/[USER]/modul2/indomie/”.

### Soal 3.d.

**Pertanyaan**
Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/” harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu 3 detik kemudian membuat file bernama “coba2.txt”. (contoh : “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”).

## Penyelesaian.

```
#include <stdio.h> 
#include <stdlib.h>
#include <unistd.h>  
#include <string.h> 
#include <sys/stat.h>
#include <dirent.h>
#include <wait.h>

int findStat(const char *path)
{
  struct stat pathDir; 
  stat(path, &pathDir);
  return S_ISDIR(pathDir.st_mode); //Melakukan cek apakah directory?
}

int main()
{
	pid_t child1 = fork();
	pid_t child2 = fork();
	pid_t child  = fork(); 	
	int status; //status akhir 
	if (child1 > 0 && child2 > 0)
 	{ 
			while ((wait(&status)) > 0);
			DIR *directory; 
			struct dirent *folder;
			chdir("/home/donny/modul2/jpg/"); 
			directory = opendir(".");
			if (directory)
			{
	      	while ((folder = readdir(directory)) != NULL)
			{
			  	if(strcmp(folder->d_name,"..")==0 || strcmp(folder->d_name,".")==0)
					continue;
			  	if(findStat(folder->d_name))
				{
			  		if(fork() == 0)
					{
			        	char folder_pindah[1000];
			        	sprintf(folder_pindah,"/home/donny/modul2/jpg/%s",folder->d_name);
			        	char* argv[] = {"mv", folder_pindah,"/home/donny/modul2/indomie/", NULL};
			        	execv("/bin/mv", argv);
		      		}
		      		else
					{
		        		while ((wait(&status)) > 0);
		          		if(fork() == 0)
						{
		          			if(fork() == 0)
							{
				  	    		char coba1[1000];
				  	    		FILE *file;
				    	    	sprintf(coba1,"/home/donny/modul2/indomie/%s/coba1.txt",folder->d_name);
				    	    	file = fopen(coba1, "w");
				    	    	fclose(file);
		      	  			}
		            		else
							{
				        		while ((wait(&status)) > 0);
				        		sleep(3);
				        		char coba2[1000];
				        		FILE *file;
				        		sprintf(coba2,"/home/donny/modul2/indomie/%s/coba2.txt",folder->d_name);
				        		file = fopen(coba2, "w");
				        		fclose(file);
				        		exit(0);
				      		}
		        		}
		        		else
						{
				      		while ((wait(&status)) > 0);
			    			exit(0);
					    }
					}
		    	}
		      	else
				{
		      		while ((wait(&status)) > 0);
		      		if(fork() == 0)
					{
			      		while ((wait(&status)) > 0);
			      		char file_pindah[1000];
				      	sprintf(file_pindah,"/home/donny/modul2/jpg/%s",folder->d_name);
				      	char* argv[] = {"mv", file_pindah,"/home/donny/modul2/sedaap/", NULL};
				      	execv("/bin/mv", argv);
					}
			  	}        
			}
		}
	}	 
	else if (child1== 0 && child2 > 0)
	{ 
	    while ((wait(&status)) > 0);
	    if (child == 0)
		{
			char *argv[] = {"mkdir", "-p","/home/donny/modul2/indomie", NULL};
		    execv("/bin/mkdir", argv);
    	}
    	else
		{
			while ((wait(&status)) > 0);
      		sleep(5);
      		char *argv[] = {"mkdir", "-p","/home/donny/modul2/sedaap", NULL};
      		execv("/bin/mkdir", argv);
    	}	
  	} 
	else if (child1 > 0 && child2 == 0)
	{ 
	    char* argv[] = {"unzip", "-q","/home/donny/modul2/jpg.zip", NULL};
	    execv("/usr/bin/unzip", argv);
	}
	return 0; 
} 
```

```
int findStat(const char *path)
{
  struct stat pathDir; 
  stat(path, &pathDir);
  return S_ISDIR(pathDir.st_mode); //Melakukan cek apakah directory?
}
```
1. Mendeklarasikan function findStat dengan argumen path/nama direktori.
2. Menggunaka struct stat dari <sys/stat.h> yang digunakan untuk mendapatkan data suatu file/direktori.
3. Melakukan stat dengan argumen path (pathname file/direktori) dan pointer pathDir sebagai pointer terhadap stat structure.
4. Kemudian menggunakan S_ISDIR untuk menentukan apakah dia adalah direktori atau bukan (Jika direktori, dia akan me-return value bukan nol).

```
if (child1 > 0 && child2 > 0)
 	{ 
			while ((wait(&status)) > 0);
			DIR *directory; 
			struct dirent *folder;
			chdir("/home/donny/modul2/jpg/"); 
			directory = opendir(".");
```
1. Merupakan parent, menunggu apabila child1 dan child2 sudah selesai. 
2. `DIR *directory;` Mendeklarasikan directory sebagai type DIR(directory stream) yang mana merupakan list dari seluruh isi dari sebuah direktori.
3. `struct dirent *folder;` Mendeklarasikan folder sebagai pointer terhadap struct dirent, yang digunakan untuk mendapatkan d_name dari masing-masing file/folder dari direktori `directory`.
4. Mengganti working directory menggunakan `chdir` ke dalam direktori jpg.
5. Menggunakan `opendir` untuk membuka directory stream yang akan digunakan type DIR `directory`.

```
if (directory)
			{
	      	while ((folder = readdir(directory)) != NULL)
			{
			  	if(strcmp(folder->d_name,"..")==0 || strcmp(folder->d_name,".")==0)
					continue;
```
1. Apabila dapat dilakukan directory stream (yang berarti opendir berhasil), function `readdir` akan mulai membaca dari posisi awal directory stream hingga `NULL` yang merupakan end dari directory stream.
2. Dengan menggunakan `strcmp` kita dapat mengecek apabila terdapat `d_name` (nama folder) yang bernama `.` atau `..` maka tidak perlu dicek lebih lanjut dengan statement `continue` yang melanjutkan ke baris berikutnya.

```
if(findStat(folder->d_name))
				{
			  		if(fork() == 0)
					{
			        	char folder_pindah[1000];
			        	sprintf(folder_pindah,"/home/donny/modul2/jpg/%s",folder->d_name);
			        	char* argv[] = {"mv", folder_pindah,"/home/donny/modul2/indomie/", NULL};
			        	execv("/bin/mv", argv);
		      		}
		      		else
					{
		        		while ((wait(&status)) > 0);
		          		if(fork() == 0)
						{
		          			if(fork() == 0)
							{
				  	    		char coba1[1000];
				  	    		FILE *file;
				    	    	sprintf(coba1,"/home/donny/modul2/indomie/%s/coba1.txt",folder->d_name);
				    	    	file = fopen(coba1, "w");
				    	    	fclose(file);
		      	  			}
							while ((wait(&status)) > 0);
				        		sleep(3);
				        		char coba2[1000];
				        		FILE *file;
				        		sprintf(coba2,"/home/donny/modul2/indomie/%s/coba2.txt",folder->d_name);
				        		file = fopen(coba2, "w");
				        		fclose(file);
				        		exit(0);
```
1. Memindahkan folder yang ada dalam direktori jpg menuju ke direktori indomie menggunakan `execv` dan `mv`
2. Menambahkan file bernama coba1.txt kepada folder pada direktori indomie menggunakan `fopen` dengan mode `w` (write)  kemudian menutupnya dengan `fclose`.
3. Setelah coba1.txt berhasil dibuat maka kita tunggu 3 detik dengan `sleep(3)`. Menambahkan file bernama coba2.txt kepada folder pada direktori indomie menggunakan `fopen` dengan mode `w` (write)  kemudian menutupnya dengan `fclose`.

```
{
		      		while ((wait(&status)) > 0);
		      		if(fork() == 0)
					{
			      		while ((wait(&status)) > 0);
			      		char file_pindah[1000];
				      	sprintf(file_pindah,"/home/donny/modul2/jpg/%s",folder->d_name);
				      	char* argv[] = {"mv", file_pindah,"/home/donny/modul2/sedaap/", NULL};
				      	execv("/bin/mv", argv);
					}
```
1. Memindahkan sisa file yang ada di dalam direktori jpg ke direktori sedaap.

```
else if (child1== 0 && child2 > 0)
	{ 
	    while ((wait(&status)) > 0);
	    if (child == 0)
		{
			char *argv[] = {"mkdir", "-p","/home/donny/modul2/indomie", NULL};
		    execv("/bin/mkdir", argv);
    	}
    	else
		{
			while ((wait(&status)) > 0);
      		sleep(5);
      		char *argv[] = {"mkdir", "-p","/home/donny/modul2/sedaap", NULL};
      		execv("/bin/mkdir", argv);
```
1. Merupakan Child1
2. Menggunakan `execv` kita menggunakan `mkdir` untuk membuat folder bernama `indomie`.
3. Menggunakan `sleep (5)` untuk menunggu 5 detik setelah pembuatan folder indomie untuk membuat folder `sedaap`.

```
else if (child1 > 0 && child2 == 0)
	{ 
	    char* argv[] = {"unzip", "-q","/home/donny/modul2/jpg.zip", NULL};
	    execv("/usr/bin/unzip", argv);
	}
	return 0; 
```
1. Merupakan Child2
2. Menggunakan `execv` kita dapat menggunakan `unzip` terhadap jpg.zip dengan mode `-q` (quiet) atau tanpa menyebutkan masing-masing nama file yang telah di unzip ke terminal.

## Output Soal 3
![Modul 2 Soal 3](https://user-images.githubusercontent.com/61267430/77213623-07ba0f80-6b3e-11ea-81de-efeeab8f25db.png)
![Modul 2 Soal 3 folders](https://user-images.githubusercontent.com/61267430/77213601-f96bf380-6b3d-11ea-9097-71abdb9fa95e.png)
![Modul 2 Soal 3 Indomie](https://user-images.githubusercontent.com/61267430/77213635-16082b80-6b3e-11ea-872e-338e8c1c531d.png)
![Output Soal 3 Coba1+2](https://user-images.githubusercontent.com/61267430/77213321-06d4ae00-6b3d-11ea-880f-50915aed53cb.png)
![Sedaap](https://user-images.githubusercontent.com/61267430/77213647-228c8400-6b3e-11ea-92ce-f298f13de3ba.png)

## Kendala.
- Nomor 2 tidak dapat diselesaikan praktikkan (poin d dan e) dikarenakan praktikkan belum mengetahui bagaimana solusi ataupun langkah-langkah menuju penyelesaian 
- Hal diatas dikarenakan masih kurangnya pengetahuan praktikkan terhadap bahasa pemrograman C.
