#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buku.h"

// Inisialisasi list buku
void initBukuList(BukuList* list) {
    list->head = NULL;
    list->tail = NULL; // Inisialisasi tail
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
    newNode->prev = list->tail; // Set prev ke tail
    
    // Tambahkan ke list
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        list->tail->next = newNode;
    }
    list->tail = newNode;
    list->size++;
}

// Mencari buku berdasarkan judul (sama dengan SLL version)
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

// Menampilkan semua buku (sama dengan SLL version)
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

// Menghapus buku dari list (DLL version)
void hapusBuku(BukuList* list, const char* judul) {
    if (list->head == NULL) {
        printf("Buku tidak ditemukan.\n");
        return;
    }
    
    BukuNode* current = list->head;
    
    // Cari node yang akan dihapus
    while (current != NULL && strcmp(current->data.judul, judul) != 0) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Buku tidak ditemukan.\n");
        return;
    }
    
    // Atur pointer prev dan next
    if (current->prev != NULL) {
        current->prev->next = current->next;
    } else {
        list->head = current->next;
    }
    
    if (current->next != NULL) {
        current->next->prev = current->prev;
    } else {
        list->tail = current->prev;
    }
    
    free(current);
    list->size--;
    printf("Buku '%s' telah dihapus.\n", judul);
}

// Membebaskan memori yang digunakan oleh list buku (DLL version)
void freeBukuList(BukuList* list) {
    BukuNode* current = list->head;
    while (current != NULL) {
        BukuNode* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}
