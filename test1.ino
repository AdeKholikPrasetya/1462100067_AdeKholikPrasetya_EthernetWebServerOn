#include <EtherCard.h>

#define STATIC 1  // set ke 1 untuk menonaktifkan DHCP (sesuaikan nilai myip/gwip di bawah)

#if STATIC
// Alamat IP antarmuka ethernet
static byte myip[] = { 192,168,1,200 }; // Alamat IP untuk Arduino
// Alamat IP gateway
static byte gwip[] = { 192,168,1,1 };   // Alamat IP gateway
#endif

// Alamat MAC ethernet - harus unik di jaringan Anda
static byte mymac[] = { 0x74,0x69,0x69,0x2D,0x30,0x31 };

// Buffer untuk mengirim dan menerima data TCP/IP
byte Ethernet::buffer[500];

// Konten halaman HTML yang akan disajikan
const char page[] PROGMEM =
"HTTP/1.0 503 My Service \r\n"
"Content-Type: text/html\r\n"
"Retry-After: 600\r\n"
"\r\n"
"<html>"
  "<head><title>"
    "Service Temporarily Unavailable"
  "</title></head>"
  "<body>"
    "<h3>Service ini sementara tidak tersedia</h3>"
    "<p><em>"
      "Server utama saat ini sedang offline.<br />"
      "Silakan coba lagi nanti."
    "</em></p>"
  "</body>"
"</html>"
;

void setup() {
  Serial.begin(9600); // Memulai komunikasi serial dengan baud rate 9600
  Serial.println("\n[backSoon]"); // Mencetak pesan ke monitor serial

  // Menginisialisasi Ethernet dengan ukuran buffer, alamat MAC, dan pin CS
  if (ether.begin(sizeof Ethernet::buffer, mymac, 10) == 0)
    Serial.println("Gagal mengakses pengontrol Ethernet"); // Mencetak error jika inisialisasi gagal

#if STATIC
  // Menggunakan konfigurasi IP statis
  ether.staticSetup(myip, gwip);
#else
  // Menggunakan DHCP untuk mendapatkan alamat IP
  if (!ether.dhcpSetup())
    Serial.println("DHCP gagal"); // Mencetak error jika DHCP gagal
#endif

  // Mencetak alamat IP ke monitor serial
  ether.printIp("IP:  ", ether.myip);
  ether.printIp("GW:  ", ether.gwip);
  ether.printIp("DNS: ", ether.dnsip);
}

void loop() {
  // Menunggu paket TCP masuk, tetapi mengabaikan isinya
  if (ether.packetLoop(ether.packetReceive())) {
    // Menyalin halaman HTML ke buffer Ethernet
    memcpy_P(ether.tcpOffset(), page, sizeof page);
    // Mengirim respons HTTP
    ether.httpServerReply(sizeof page - 1);
  }
}
