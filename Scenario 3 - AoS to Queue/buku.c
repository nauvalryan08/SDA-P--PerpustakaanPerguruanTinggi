#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buku.h"
#include "anggota.h"

// Inisialisasi array buku
void initBukuArray(BukuArray* array) {
    array->size = 0;
    int i = 0;
    while (i < MAX_BUKU) {
        array->peminjam[i].head = NULL;
        array->peminjam[i].tail = NULL;
        array->peminjam[i].size = 0;
        i++;
    }
}

// Menambahkan buku baru ke dalam array
int tambahBuku(BukuArray* array, const char* judul, int stok) {
    // Cek apakah array penuh
    if (array->size >= MAX_BUKU) {
        printf("Kapasitas buku penuh.\n");
        return 0;
    }

    // Cek apakah buku sudah ada
    int i = 0;
    while (i < array->size) {
        if (strcmp(array->data[i].judul, judul) == 0) {
            array->data[i].stok += stok;
            return 1;
        }
        i++;
    }

    // Tambahkan buku baru
    strncpy(array->data[array->size].judul, judul, sizeof(array->data[0].judul) - 1);
    array->data[array->size].judul[sizeof(array->data[0].judul) - 1] = '\0';
    array->data[array->size].stok = stok;
    array->data[array->size].dipinjam = 0;
    array->size++;

    return 1;
}

// Mencari buku berdasarkan judul
Buku* cariBuku(BukuArray* array, const char* judul) {
	int i = 0;
    while (i < array->size) {
        if (strcmp(array->data[i].judul, judul) == 0) {
            return &array->data[i];
        }
        i++;
    }
    return NULL;
}

// Menampilkan semua buku
void tampilkanSemuaBuku(BukuArray* array) {
    if (array->size == 0) {
        printf("Tidak ada buku dalam sistem.\n");
        return;
    }

    printf("\nDaftar Buku:\n");
    printf("%-40s %-10s %-10s\n", "Judul", "Stok", "Dipinjam");
    printf("------------------------------------------------------------\n");

	int i = 0;
    while (i < array->size) {
        printf("%-40s %-10d %-10d\n", 
               array->data[i].judul, 
               array->data[i].stok, 
               array->data[i].dipinjam);
        i++;
    }
}

// Menghapus buku dari array
int hapusBuku(BukuArray* array, const char* judul) {
	int i = 0;
    while (i < array->size) {
        if (strcmp(array->data[i].judul, judul) == 0) {
            // Geser elemen setelahnya ke depan
            int j = i;
            while (j < array->size - 1) {
                array->data[j] = array->data[j + 1];
                array->peminjam[j] = array->peminjam[j + 1];
                j++;
            }
            array->size--;
            return 1;
        }
        i++;
    }
    return 0;
}

// Membebaskan memori yang digunakan oleh queue peminjam
void freePeminjamQueue(PeminjamQueue* queue) {
    PeminjamNode* current = queue->head;
    while (current != NULL) {
        PeminjamNode* temp = current;
        current = current->next;
        free(temp);
    }
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
}

// Membebaskan memori yang digunakan oleh array buku
void freeBukuArray(BukuArray* array) {
	int i = 0;
    while (i < array->size) {
        freePeminjamQueue(&array->peminjam[i]);
        i++;
    }
    array->size = 0;
}
