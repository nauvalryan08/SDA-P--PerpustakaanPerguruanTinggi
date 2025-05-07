#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "peminjaman.h"
#include "buku.h"
#include "anggota.h"

// Menambahkan peminjam ke dalam antrian buku tertentu
void tambahPeminjam(BukuArray* bukuArray, AnggotaList* anggotaList, const char* judulBuku, const char* idAnggota) {
    // Cari buku
    Buku* buku = cariBuku(bukuArray, judulBuku);
    if (buku == NULL) {
        printf("Buku '%s' tidak ditemukan.\n", judulBuku);
        return;
    }

    // Cari anggota
    Anggota* anggota = cariAnggota(anggotaList, idAnggota);
    if (anggota == NULL) {
        printf("Anggota dengan ID %s tidak ditemukan.\n", idAnggota);
        return;
    }

    // Cari index buku
    int index = -1; int i = 0;
    while (i < bukuArray->size) {
        if (strcmp(bukuArray->data[i].judul, judulBuku) == 0) {
            index = i;
            break;
        }
        i++;
    }

    if (index == -1) {
        printf("Buku '%s' tidak ditemukan.\n", judulBuku);
        return;
    }

    // Buat node peminjam baru
    PeminjamNode* newNode = (PeminjamNode*)malloc(sizeof(PeminjamNode));
    if (newNode == NULL) {
        printf("Gagal alokasi memori untuk peminjam baru.\n");
        return;
    }

    strncpy(newNode->idAnggota, idAnggota, sizeof(newNode->idAnggota) - 1);
    newNode->idAnggota[sizeof(newNode->idAnggota) - 1] = '\0';
    newNode->prioritas = anggota->prioritas;
    newNode->next = NULL;

    // Tambahkan ke queue peminjam
    if (bukuArray->peminjam[index].head == NULL) {
        bukuArray->peminjam[index].head = newNode;
        bukuArray->peminjam[index].tail = newNode;
    } else {
        // Masukkan berdasarkan prioritas (dosen > mahasiswa > masyarakat)
        PeminjamNode* current = bukuArray->peminjam[index].head;
        PeminjamNode* prev = NULL;

        // Cari posisi yang tepat berdasarkan prioritas
        while (current != NULL && current->prioritas >= newNode->prioritas) {
            prev = current;
            current = current->next;
        }

        if (prev == NULL) {
            // Insert di head
            newNode->next = bukuArray->peminjam[index].head;
            bukuArray->peminjam[index].head = newNode;
        } else {
            // Insert di tengah atau tail
            prev->next = newNode;
            newNode->next = current;
            if (current == NULL) {
                bukuArray->peminjam[index].tail = newNode;
            }
        }
    }

    bukuArray->peminjam[index].size++;
    printf("Peminjaman buku '%s' oleh anggota %s telah ditambahkan ke antrian.\n", judulBuku, idAnggota);
}

// Proses peminjaman buku
void prosesPeminjaman(BukuArray* bukuArray, AnggotaList* anggotaList, const char* judulBuku) {
    Buku* buku = cariBuku(bukuArray, judulBuku);
    if (buku == NULL) {
        printf("Buku '%s' tidak ditemukan.\n", judulBuku);
        return;
    }

    // Cek stok buku
    if (buku->dipinjam >= buku->stok) {
        printf("Stok buku '%s' habis. Tidak bisa memproses peminjaman.\n", judulBuku);
        return;
    }

    // Cari index buku
    int index = -1; int i = 0;
    while (i < bukuArray->size) {
        if (strcmp(bukuArray->data[i].judul, judulBuku) == 0) {
            index = i;
            break;
        }
        i++;
    }

    if (index == -1 || bukuArray->peminjam[index].head == NULL) {
        printf("Tidak ada antrian peminjaman untuk buku '%s'.\n", judulBuku);
        return;
    }

    // Ambil peminjam pertama (prioritas tertinggi)
    PeminjamNode* peminjam = bukuArray->peminjam[index].head;
    bukuArray->peminjam[index].head = peminjam->next;
    if (bukuArray->peminjam[index].head == NULL) {
        bukuArray->peminjam[index].tail = NULL;
    }
    bukuArray->peminjam[index].size--;

    // Cari data anggota
    Anggota* anggota = cariAnggota(anggotaList, peminjam->idAnggota);
    if (anggota == NULL) {
        printf("Anggota dengan ID %s tidak ditemukan.\n", peminjam->idAnggota);
        free(peminjam);
        return;
    }

    // Proses peminjaman
    buku->dipinjam++;
    printf("Buku '%s' berhasil dipinjam oleh %s (%s).\n", 
           judulBuku, anggota->nama, dapatkanLabelPrioritas(anggota->prioritas));

    free(peminjam);
}

// Proses pengembalian buku
void prosesPengembalian(BukuArray* bukuArray, const char* judulBuku, const char* idAnggota) {
    Buku* buku = cariBuku(bukuArray, judulBuku);
    if (buku == NULL) {
        printf("Buku '%s' tidak ditemukan.\n", judulBuku);
        return;
    }

    if (buku->dipinjam > 0) {
        buku->dipinjam--;
        printf("Buku '%s' berhasil dikembalikan oleh anggota %s.\n", judulBuku, idAnggota);
    } else {
        printf("Tidak ada buku '%s' yang sedang dipinjam.\n", judulBuku);
    }
}

// Membatalkan peminjaman
void batalkanPeminjaman(BukuArray* bukuArray, const char* judulBuku, const char* idAnggota) {
    // Cari index buku
    int index = -1; int i = 0;
    while (i < bukuArray->size) {
        if (strcmp(bukuArray->data[i].judul, judulBuku) == 0) {
            index = i;
            break;
        }
        i++;
    }

    if (index == -1) {
        printf("Buku '%s' tidak ditemukan.\n", judulBuku);
        return;
    }

    PeminjamQueue* queue = &bukuArray->peminjam[index];
    PeminjamNode* current = queue->head;
    PeminjamNode* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->idAnggota, idAnggota) == 0) {
            if (prev == NULL) {
                // Hapus dari head
                queue->head = current->next;
                if (queue->head == NULL) {
                    queue->tail = NULL;
                }
            } else {
                prev->next = current->next;
                if (current->next == NULL) {
                    queue->tail = prev;
                }
            }

            free(current);
            queue->size--;
            printf("Peminjaman buku '%s' oleh anggota %s telah dibatalkan.\n", judulBuku, idAnggota);
            return;
        }

        prev = current;
        current = current->next;
    }

    printf("Anggota %s tidak ditemukan dalam antrian peminjaman buku '%s'.\n", idAnggota, judulBuku);
}

// Menampilkan antrian peminjaman untuk buku tertentu
void tampilkanAntrianPeminjaman(BukuArray* bukuArray, const char* judulBuku) {
    // Cari index buku
    int index = -1; int i = 0;
    while (i < bukuArray->size) {
        if (strcmp(bukuArray->data[i].judul, judulBuku) == 0) {
            index = i;
            break;
        }
        i++;
    }

    if (index == -1) {
        printf("Buku '%s' tidak ditemukan.\n", judulBuku);
        return;
    }

    PeminjamQueue* queue = &bukuArray->peminjam[index];

    printf("\nAntrian Peminjaman untuk Buku '%s':\n", judulBuku);
    printf("Total Peminjam: %d\n", queue->size);

    PeminjamNode* current = queue->head;
    while (current != NULL) {
        printf("- %s (%s)\n", current->idAnggota, dapatkanLabelPrioritas(current->prioritas));
        current = current->next;
    }
}
