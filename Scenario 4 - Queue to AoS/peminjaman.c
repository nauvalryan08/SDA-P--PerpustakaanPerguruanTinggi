#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "peminjaman.h"
#include "buku.h"
#include "anggota.h"

void initPeminjamanQueue(PeminjamanQueue* queue) {
    queue->headDosen = NULL;
    queue->tailDosen = NULL;
    queue->headMahasiswa = NULL;
    queue->tailMahasiswa = NULL;
    queue->headMasyarakat = NULL;
    queue->tailMasyarakat = NULL;
    queue->totalPeminjam = 0;
}

void tambahPeminjam(PeminjamanQueue* queue, BukuArray* bukuArray, AnggotaList* anggotaList, const char* judulBuku, const char* idAnggota) {
    Buku* buku = cariBuku(bukuArray, judulBuku);
    if (buku == NULL) {
        printf("Buku '%s' tidak ditemukan.\n", judulBuku);
        return;
    }

    Anggota* anggota = cariAnggota(anggotaList, idAnggota);
    if (anggota == NULL) {
        printf("Anggota dengan ID %s tidak ditemukan.\n", idAnggota);
        return;
    }

    PeminjamNode* newNode = (PeminjamNode*)malloc(sizeof(PeminjamNode));
    if (newNode == NULL) {
        printf("Gagal alokasi memori untuk peminjam baru.\n");
        return;
    }

    strncpy(newNode->idAnggota, idAnggota, sizeof(newNode->idAnggota) - 1);
    newNode->idAnggota[sizeof(newNode->idAnggota) - 1] = '\0';
    newNode->prioritas = anggota->prioritas;
    newNode->buku = buku;
    newNode->next = NULL;

    // Tambahkan ke queue sesuai prioritas
    switch (anggota->prioritas) {
        case DOSEN:
            if (queue->headDosen == NULL) {
                queue->headDosen = newNode;
                queue->tailDosen = newNode;
            } else {
                queue->tailDosen->next = newNode;
                queue->tailDosen = newNode;
            }
            break;
        case MAHASISWA:
            if (queue->headMahasiswa == NULL) {
                queue->headMahasiswa = newNode;
                queue->tailMahasiswa = newNode;
            } else {
                queue->tailMahasiswa->next = newNode;
                queue->tailMahasiswa = newNode;
            }
            break;
        case MASYARAKAT:
            if (queue->headMasyarakat == NULL) {
                queue->headMasyarakat = newNode;
                queue->tailMasyarakat = newNode;
            } else {
                queue->tailMasyarakat->next = newNode;
                queue->tailMasyarakat = newNode;
            }
            break;
    }

    queue->totalPeminjam++;
    printf("Peminjaman buku '%s' oleh anggota %s telah ditambahkan ke antrian.\n", judulBuku, idAnggota);
}

void prosesPeminjaman(PeminjamanQueue* queue, BukuArray* bukuArray, AnggotaList* anggotaList) {
    // Cari peminjam prioritas tertinggi yang tersedia
    PeminjamNode* peminjam = NULL;
    
    if (queue->headDosen != NULL) {
        peminjam = queue->headDosen;
        queue->headDosen = queue->headDosen->next;
        if (queue->headDosen == NULL) {
            queue->tailDosen = NULL;
        }
    } else if (queue->headMahasiswa != NULL) {
        peminjam = queue->headMahasiswa;
        queue->headMahasiswa = queue->headMahasiswa->next;
        if (queue->headMahasiswa == NULL) {
            queue->tailMahasiswa = NULL;
        }
    } else if (queue->headMasyarakat != NULL) {
        peminjam = queue->headMasyarakat;
        queue->headMasyarakat = queue->headMasyarakat->next;
        if (queue->headMasyarakat == NULL) {
            queue->tailMasyarakat = NULL;
        }
    } else {
        printf("Tidak ada antrian peminjaman.\n");
        return;
    }

    // Proses peminjaman
    if (peminjam->buku->dipinjam >= peminjam->buku->stok) {
        printf("Stok buku '%s' habis. Tidak bisa memproses peminjaman.\n", peminjam->buku->judul);
        free(peminjam);
        return;
    }

    Anggota* anggota = cariAnggota(anggotaList, peminjam->idAnggota);
    if (anggota == NULL) {
        printf("Anggota dengan ID %s tidak ditemukan.\n", peminjam->idAnggota);
        free(peminjam);
        return;
    }

    peminjam->buku->dipinjam++;
    queue->totalPeminjam--;

    printf("Buku '%s' berhasil dipinjam oleh %s (%s).\n", 
           peminjam->buku->judul, anggota->nama, dapatkanLabelPrioritas(anggota->prioritas));

    free(peminjam);
}

void prosesPengembalian(PeminjamanQueue* queue, BukuArray* bukuArray, const char* judulBuku, const char* idAnggota) {
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

void batalkanPeminjaman(PeminjamanQueue* queue, const char* judulBuku, const char* idAnggota) {
    // Cari di semua antrian prioritas
    int found = 0;
    struct {
        PeminjamNode** head;
        PeminjamNode** tail;
    } queues[] = {
        {&queue->headDosen, &queue->tailDosen},
        {&queue->headMahasiswa, &queue->tailMahasiswa},
        {&queue->headMasyarakat, &queue->tailMasyarakat}
    };

	int i = 0; 
    while (i < 3 && !found) {
        PeminjamNode* current = *queues[i].head;
        PeminjamNode* prev = NULL;

        while (current != NULL && !found) {
            if (strcmp(current->idAnggota, idAnggota) == 0 && 
                strcmp(current->buku->judul, judulBuku) == 0) {
                found = 1;

                if (prev == NULL) {
                    *queues[i].head = current->next;
                    if (*queues[i].head == NULL) {
                        *queues[i].tail = NULL;
                    }
                } else {
                    prev->next = current->next;
                    if (current->next == NULL) {
                        *queues[i].tail = prev;
                    }
                }

                free(current);
                queue->totalPeminjam--;
                printf("Peminjaman buku '%s' oleh anggota %s telah dibatalkan.\n", judulBuku, idAnggota);
            } else {
                prev = current;
                current = current->next;
            }
        }
        i++;
    }

    if (!found) {
        printf("Anggota %s tidak ditemukan dalam antrian peminjaman buku '%s'.\n", idAnggota, judulBuku);
    }
}

void tampilkanAntrianPeminjaman(PeminjamanQueue* queue) {
    printf("\nAntrian Peminjaman:\n");
    printf("Total Peminjam: %d\n", queue->totalPeminjam);

    printf("\nDosen:\n");
    PeminjamNode* current = queue->headDosen;
    while (current != NULL) {
        printf("- %s (Buku: %s)\n", current->idAnggota, current->buku->judul);
        current = current->next;
    }

    printf("\nMahasiswa:\n");
    current = queue->headMahasiswa;
    while (current != NULL) {
        printf("- %s (Buku: %s)\n", current->idAnggota, current->buku->judul);
        current = current->next;
    }

    printf("\nMasyarakat:\n");
    current = queue->headMasyarakat;
    while (current != NULL) {
        printf("- %s (Buku: %s)\n", current->idAnggota, current->buku->judul);
        current = current->next;
    }
}

void freePeminjamanQueue(PeminjamanQueue* queue) {
    // Bebaskan semua antrian
    PeminjamNode* current = queue->headDosen;
    while (current != NULL) {
        PeminjamNode* temp = current;
        current = current->next;
        free(temp);
    }

    current = queue->headMahasiswa;
    while (current != NULL) {
        PeminjamNode* temp = current;
        current = current->next;
        free(temp);
    }

    current = queue->headMasyarakat;
    while (current != NULL) {
        PeminjamNode* temp = current;
        current = current->next;
        free(temp);
    }

    queue->headDosen = NULL;
    queue->tailDosen = NULL;
    queue->headMahasiswa = NULL;
    queue->tailMahasiswa = NULL;
    queue->headMasyarakat = NULL;
    queue->tailMasyarakat = NULL;
    queue->totalPeminjam = 0;
}
