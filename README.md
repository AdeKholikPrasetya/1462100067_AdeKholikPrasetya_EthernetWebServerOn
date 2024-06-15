# 1462100067_AdeKholikPrasetya_EthernetWebServerOn

# Ethernet Web Server Simulation Project

Proyek ini adalah simulasi server web sederhana menggunakan Arduino dan library EtherCard. Server web ini akan menampilkan halaman HTML yang menunjukkan pesan "Service Temporarily Unavailable".

## Persyaratan

- Arduino (contoh: Arduino Uno)
- Modul Ethernet (contoh: ENC28J60)
- Library EtherCard untuk Arduino
- Proteus 8 Professional untuk simulasi

## Instalasi Library EtherCard

Untuk menggunakan library EtherCard, Anda perlu mengunduh dan menginstalnya melalui Library Manager di Arduino IDE atau secara manual:

1. Buka Arduino IDE.
2. Pergi ke `Sketch` -> `Include Library` -> `Manage Libraries`.
3. Cari `EtherCard`.
4. Pilih dan instal library EtherCard.

### Pengaturan IP Statis

Pastikan untuk mengkonfigurasi alamat IP statis di bagian berikut dari kode:

```cpp
#define STATIC 1  // set ke 1 untuk menonaktifkan DHCP (sesuaikan nilai myip/gwip di bawah)

#if STATIC
// Alamat IP antarmuka ethernet
static byte myip[] = { 192,168,1,200 }; // Alamat IP untuk Arduino
// Alamat IP gateway
static byte gwip[] = { 192,168,1,1 };   // Alamat IP gateway
#endif
