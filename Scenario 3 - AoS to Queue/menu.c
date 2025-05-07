#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menu.h"
#include "buku.h"
#include "anggota.h"
#include "peminjaman.h"

// Menampilkan menu utama
void tampilkanMenuUtama() {
	system("cls");
    printf("\n=== SISTEM MANAJEMEN PERPUSTAKAAN ===\n");
    printf("1. Kelola Buku\n");
    printf("2. Kelola Anggota\n");
    printf("3. Kelola Peminjaman\n");
    printf("4. Requirement Awal\n");
    printf("0. Keluar\n");
    printf("Pilihan: ");
}

// Menu untuk mengelola buku
void menuKelolaBuku(BukuArray* array) {
    int pilihan;
    char judul[100];
    int stok;
    
    do {
    	system("cls");
        printf("\n=== KELOLA BUKU ===\n");
        printf("1. Tambah Buku\n");
        printf("2. Hapus Buku\n");
        printf("3. Tampilkan Semua Buku\n");
        printf("0. Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1:
                printf("Masukkan judul buku: ");
                scanf(" %[^\n]", judul);
                printf("Masukkan stok: ");
                scanf("%d", &stok);
                if (tambahBuku(array, judul, stok)) {
                    printf("Buku berhasil ditambahkan.\n");
                } else {
                    printf("Gagal menambahkan buku.\n");
                }
                printf("\n\nPress ENTER untuk melanjutkan..\n");
    			getchar(); getchar();
                break;
            case 2:
                printf("Masukkan judul buku yang akan dihapus: ");
                scanf(" %[^\n]", judul);
                if (hapusBuku(array, judul)) {
                    printf("Buku berhasil dihapus.\n");
                } else {
                    printf("Buku tidak ditemukan.\n");
                }
                printf("\n\nPress ENTER untuk melanjutkan..\n");
    			getchar(); getchar();
                break;
            case 3:
                tampilkanSemuaBuku(array);
                printf("\n\nPress ENTER untuk melanjutkan..\n");
    			getchar(); getchar();
                break;
            case 0:
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);
}

// Menu untuk mengelola anggota 
void menuKelolaAnggota(AnggotaList* list) {
    int pilihan;
    char nama[100];
    char id[20];
    int prioritas;
    
    do {
    	system("cls");
        printf("\n=== KELOLA ANGGOTA ===\n");
        printf("1. Tambah Anggota\n");
        printf("2. Hapus Anggota\n");
        printf("3. Tampilkan Semua Anggota\n");
        printf("0. Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1:
                printf("Masukkan nama anggota: ");
                scanf(" %[^\n]", nama);
                printf("Masukkan ID anggota: ");
                scanf(" %s", id);
                printf("Pilih prioritas (0=Masyarakat, 1=Mahasiswa, 2=Dosen): ");
                scanf("%d", &prioritas);
                if (prioritas < 0 || prioritas > 2) {
                    printf("Prioritas tidak valid.\n");
                    break;
                }
                tambahAnggota(list, nama, id, (Prioritas)prioritas);
                printf("\n\nPress ENTER untuk melanjutkan..\n");
    			getchar(); getchar();
                break;
            case 2:
                printf("Masukkan ID anggota yang akan dihapus: ");
                scanf(" %s", id);
                hapusAnggota(list, id);
                printf("\n\nPress ENTER untuk melanjutkan..\n");
    			getchar(); getchar();
                break;
            case 3:
                tampilkanSemuaAnggota(list);
                printf("\n\nPress ENTER untuk melanjutkan..\n");
    			getchar(); getchar();
                break;
            case 0:
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);
} 

// Menu untuk mengelola peminjaman
void menuKelolaPeminjaman(BukuArray* bukuArray, AnggotaList* anggotaList) {
    int pilihan;
    char judul[100];
    char id[20];
    
    do {
    	system("cls");
        printf("\n=== KELOLA PEMINJAMAN ===\n");
        printf("1. Tambah Peminjaman\n");
        printf("2. Proses Peminjaman\n");
        printf("3. Proses Pengembalian\n");
        printf("4. Batalkan Peminjaman\n");
        printf("5. Tampilkan Antrian Peminjaman\n");
        printf("0. Kembali\n");
        printf("Pilihan: ");
        scanf("%d", &pilihan);
        
        switch (pilihan) {
            case 1: {
                printf("Masukkan judul buku: ");
                scanf(" %[^\n]", judul);
                printf("Masukkan ID anggota: ");
                scanf(" %s", id);
                tambahPeminjam(bukuArray, anggotaList, judul, id);
                printf("\n\nPress ENTER untuk melanjutkan..\n");
    			getchar(); getchar();
                break;
            }
            case 2: {
                printf("Masukkan judul buku yang akan diproses: ");
                scanf(" %[^\n]", judul);
                prosesPeminjaman(bukuArray, anggotaList, judul);
                printf("\n\nPress ENTER untuk melanjutkan..\n");
    			getchar(); getchar();
                break;
            }
            case 3: {
                printf("Masukkan judul buku yang dikembalikan: ");
                scanf(" %[^\n]", judul);
                printf("Masukkan ID anggota yang mengembalikan: ");
                scanf(" %s", id);
                prosesPengembalian(bukuArray, judul, id);
                printf("\n\nPress ENTER untuk melanjutkan..\n");
 			  	getchar(); getchar();
                break;
            }
            case 4: {
                printf("Masukkan judul buku: ");
                scanf(" %[^\n]", judul);
                printf("Masukkan ID anggota: ");
                scanf(" %s", id);
                batalkanPeminjaman(bukuArray, judul, id);
                printf("\n\nPress ENTER untuk melanjutkan..\n");
              	getchar(); getchar();
                break;
            }
            case 5: {
                printf("Masukkan judul buku: ");
                scanf(" %[^\n]", judul);
                tampilkanAntrianPeminjaman(bukuArray, judul);
                printf("\n\nPress ENTER untuk melanjutkan..\n");
    			getchar(); getchar();
                break;
            }
            case 0:
                break;
            default:
                printf("Pilihan tidak valid.\n");
        }
    } while (pilihan != 0);
}

// Fungsi untuk menjalankan requirement awal/skenario pengujian
void requirementAwal(BukuArray* bukuArray, AnggotaList* anggotaList) {
	system("cls");
    printf("\n=== MENJALANKAN REQUIREMENT AWAL/SKENARIO PENGUJIAN ===\n");
    
    // a) Insert 2 buku dengan stok masing-masing 1
    printf("\n1. Menambahkan 2 buku (Buku1 dan Buku2) dengan stok masing-masing 1...\n");
    tambahBuku(bukuArray, "Buku1", 1);
    tambahBuku(bukuArray, "Buku2", 1);
    tampilkanSemuaBuku(bukuArray);
    
    // b) Insert Anggota1 sebagai mahasiswa
    printf("\n2. Menambahkan Anggota1 sebagai mahasiswa...\n");
    tambahAnggota(anggotaList, "Anggota1", "A001", MAHASISWA);
    
    // c) Insert Dosen1 sebagai dosen
    printf("\n3. Menambahkan Dosen1 sebagai dosen...\n");
    tambahAnggota(anggotaList, "Dosen1", "D001", DOSEN);
    
    // d) Insert Umum1 sebagai masyarakat umum
    printf("\n4. Menambahkan Umum1 sebagai masyarakat umum...\n");
    tambahAnggota(anggotaList, "Umum1", "U001", MASYARAKAT);
    tampilkanSemuaAnggota(anggotaList);
    
    // e) Anggota1 meminjam Buku1
    printf("\n5. Anggota1 (mahasiswa) meminjam Buku1...\n");
    tambahPeminjam(bukuArray, anggotaList, "Buku1", "A001");
    
    // f) Dosen1 meminjam Buku1
    printf("\n6. Dosen1 meminjam Buku1...\n");
    tambahPeminjam(bukuArray, anggotaList, "Buku1", "D001");
    
    // g) Umum1 meminjam Buku1
    printf("\n7. Umum1 meminjam Buku1...\n");
    tambahPeminjam(bukuArray, anggotaList, "Buku1", "U001");
    
    // h) Umum1 meminjam Buku2
    printf("\n8. Umum1 meminjam Buku2...\n");
    tambahPeminjam(bukuArray, anggotaList, "Buku2", "U001");
    
    // Tampilkan antrian peminjaman
    printf("\n9. Menampilkan antrian peminjaman Buku1...\n");
    tampilkanAntrianPeminjaman(bukuArray, "Buku1");
    printf("\n10. Menampilkan antrian peminjaman Buku2...\n");
    tampilkanAntrianPeminjaman(bukuArray, "Buku2");
    
    // i) Proses peminjaman Buku1 (harusnya Dosen1 yang dapat)
    printf("\n11. Memproses peminjaman Buku1...\n");
    prosesPeminjaman(bukuArray, anggotaList, "Buku1");
    tampilkanSemuaBuku(bukuArray);
    tampilkanAntrianPeminjaman(bukuArray, "Buku1");
    
    // j) Dosen1 mengembalikan Buku1 (harusnya Anggota1 yang dapat berikutnya)
    printf("\n12. Dosen1 mengembalikan Buku1...\n");
    prosesPengembalian(bukuArray, "Buku1", "D001");
    tampilkanSemuaBuku(bukuArray);
    tampilkanAntrianPeminjaman(bukuArray, "Buku1");
    
    // k) Umum1 membatalkan peminjaman Buku2
    printf("\n13. Umum1 membatalkan peminjaman Buku2...\n");
    batalkanPeminjaman(bukuArray, "Buku2", "U001");
    tampilkanAntrianPeminjaman(bukuArray, "Buku2");
    
    printf("\n=== SKENARIO PENGUJIAN SELESAI ===\n");
    
    printf("\n\nPress ENTER untuk melanjutkan..\n");
    getchar(); getchar();
}
