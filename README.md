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
--- 

## Soal 1 
Source Code : [source](https://github.com/naminai/SoalShiftSISOP20_modul2_T06/tree/master/soal1) 

**Deskripsi** 
Buatlah program C yang menyerupai crontab untuk menjalankan script bash dengan ketentuan sebagai berikut: 

### Soal 1.a. 

**Pertanyaan** 
Program menerima 4 argumen berupa: 
i. Detik: 0-59 atau * (any value) 
ii. Menit: 0-59 atau * (any value) 
iii. Jam: 0-23 atau * (any value) 
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

### Penyelesaian. 


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

### Penyelesaian.


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

## Soal 3.c.

**Pertanyaan**
Diberilah tugas baru yaitu setelah di ekstrak, hasil dari ekstrakan tersebut (di dalam direktori “home/[USER]/modul2/jpg/”) harus dipindahkan sesuai dengan pengelompokan, semua file harus dipindahkan ke “/home/[USER]/modul2/sedaap/” dan semua direktori harus dipindahkan ke “/home/[USER]/modul2/indomie/”.

## Soal 3.d.

**Pertanyaan**
Untuk setiap direktori yang dipindahkan ke “/home/[USER]/modul2/indomie/” harus membuat dua file kosong. File yang pertama diberi nama “coba1.txt”, lalu 3 detik kemudian membuat file bernama “coba2.txt”. (contoh : “/home/[USER]/modul2/indomie/{nama_folder}/coba1.txt”).
