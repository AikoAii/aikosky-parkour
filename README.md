# Aiko Sky Parkour

Game **parkour vertikal sederhana** yang dibuat menggunakan **C++** dan **Raylib**.

Proyek ini dibuat sebagai project pembelajaran pribadi untuk mencoba mekanik game sederhana, struktur kode yang rapi, dan proses build lintas platform menggunakan **CMake**.

Ide permainannya sederhana: **naik setinggi mungkin sebelum waktu habis.**

---

## Gameplay

Gerakkan karakter ke kiri dan kanan untuk berpindah antar platform sambil menghindari bahaya dan mengumpulkan item.

Semakin tinggi kamu naik, semakin besar skor yang bisa didapat.

Elemen dalam game:

* **Platform Biru** → tempat aman untuk berpijak
* **Duri Merah** → langsung game over
* **Koin Kuning** → +200 skor
* **Jam Hijau** → +10 detik waktu

Tujuan permainan:

> bertahan selama mungkin dan capai skor setinggi mungkin.

---

## Kontrol

| Tombol          | Fungsi                |
| --------------- | --------------------- |
| ← →             | Bergerak kiri / kanan |
| ENTER           | Memulai permainan     |
| ESC / Backspace | Kembali ke menu       |

---

## Struktur Proyek

```
.
├── CMakeLists.txt
├── main.cpp
├── include
│   ├── game.h
│   └── renderer.h
├── src
│   ├── game.cpp
│   └── renderer.cpp
└── README.md
```

Pembagian tanggung jawab file:

* **main.cpp** → game loop utama
* **game.cpp** → logika gameplay
* **renderer.cpp** → menggambar UI dan teks

---

## Persyaratan

Program ini membutuhkan:

* **Compiler C++** (g++, clang, atau MSVC)
* **CMake**
* **Raylib**

Silakan instal menggunakan package manager sesuai sistem operasi.

Contoh:

Linux (Arch Linux):

```bash
sudo pacman -S raylib cmake base-devel
```

Linux (Ubuntu / Debian):

```bash
sudo apt install libraylib-dev cmake g++
```

macOS:

```bash
brew install raylib cmake
```

Windows (MSYS2):

```bash
pacman -S mingw-w64-x86_64-raylib
```

---

## Build & Menjalankan (Universal)

Langkah berikut dapat digunakan di **Linux, macOS, maupun Windows**.

```bash
# membuat folder build
mkdir build
cd build

# konfigurasi project
cmake ..

# proses kompilasi
cmake --build .
```

Menjalankan game:

Linux / macOS:

```bash
./AikoSkyParkour
```

Windows:

```bash
AikoSkyParkour.exe
```

---

## Catatan

Proyek kecil ini dibuat untuk:

* belajar **game development dengan C++ menggunakan library Raylib**
* melatih **struktur kode modular**
* mencoba **build system CMake lintas platform**
* belajar logika prosedural

Silakan eksplorasi kode jika tertarik. 

---

Dibuat dengan rasa penasaran dan banyak eksperimen.

**— Aiko**
