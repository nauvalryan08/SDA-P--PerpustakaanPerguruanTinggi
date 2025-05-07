#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buku.h"

// Inisialisasi list buku
void initBukuList(BukuList* list) {
    list->head = NULL;
    list->size = 0;
}

// Menambahkan buku baru ke dalam list
void tambahBuku(BukuList* list, const char* judul, int stok) {
    // Cek apakah buku sudah ada
    Buku* existing = cariBuku(list, judul);
    if (existing != NULL) {
        existing->stok += stok;
        return;
    }
    
    // Buat node baru
    BukuNode* newNode = (BukuNode*)malloc(sizeof(BukuNode));
    if (newNode == NULL) {
        printf("Gagal alokasi memori untuk buku baru.\n");
        return;
    }
    
    // Isi data buku
    strncpy(newNode->data.judul, judul, sizeof(newNode->data.judul) - 1);
    newNode->data.judul[sizeof(newNode->data.judul) - 1] = '\0';
    newNode->data.stok = stok;
    newNode->data.dipinjam = 0;
    newNode->next = NULL;
    
    // Tambahkan ke list
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        BukuNode* current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

// Mencari buku berdasarkan judul
Buku* cariBuku(BukuList* list, const char* judul) {
    BukuNode* current = list->head;
    while (current != NULL) {
        if (strcmp(current->data.judul, judul) == 0) {
            return &(current->data);
        }
        current = current->next;
    }
    return NULL;
}

// Menampilkan semua buku
void tampilkanSemuaBuku(BukuList* list) {
    if (list->head == NULL) {
        printf("Tidak ada buku dalam sistem.\n");
        return;
    }
    
    printf("\nDaftar Buku:\n");
    printf("%-40s %-10s %-10s\n", "Judul", "Stok", "Dipinjam");
    printf("------------------------------------------------------------\n");
    
    BukuNode* current = list->head;
    while (current != NULL) {
        printf("%-40s %-10d %-10d\n", 
               current->data.judul, 
               current->data.stok, 
               current->data.dipinjam);
        current = current->next;
    }
}

// Menghapus buku dari list
void hapusBuku(BukuList* list, const char* judul) {
    if (list->head == NULL) {
        printf("Buku tidak ditemukan.\n");
        return;
    }
    
    BukuNode* current = list->head;
    BukuNode* prev = NULL;
    
    // Cari node yang akan dihapus
    while (current != NULL && strcmp(current->data.judul, judul) != 0) {
        prev = current;
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Buku tidak ditemukan.\n");
        return;
    }
    
    // Hapus node
    if (prev == NULL) {
        list->head = current->next;
    } else {
        prev->next = current->next;
    }
    
    free(current);
    list->size--;
    printf("Buku '%s' telah dihapus.\n", judul);
}

// Membebaskan memori yang digunakan oleh list buku
void freeBukuList(BukuList* list) {
    BukuNode* current = list->head;
    while (current != NULL) {
        BukuNode* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->size = 0;
}
