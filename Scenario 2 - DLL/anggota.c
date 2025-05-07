#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "anggota.h"

// Inisialisasi list anggota
void initAnggotaList(AnggotaList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// Menambahkan anggota baru ke dalam list (DLL version)
void tambahAnggota(AnggotaList* list, const char* nama, const char* id, Prioritas prioritas) {
    // Cek apakah ID sudah ada
    Anggota* existing = cariAnggota(list, id);
    if (existing != NULL) {
        printf("Anggota dengan ID %s sudah ada.\n", id);
        return;
    }
    
    // Buat node baru
    AnggotaNode* newNode = (AnggotaNode*)malloc(sizeof(AnggotaNode));
    if (newNode == NULL) {
        printf("Gagal alokasi memori untuk anggota baru.\n");
        return;
    }
    
    // Isi data anggota
    strncpy(newNode->data.nama, nama, sizeof(newNode->data.nama) - 1);
    newNode->data.nama[sizeof(newNode->data.nama) - 1] = '\0';
    
    strncpy(newNode->data.id, id, sizeof(newNode->data.id) - 1);
    newNode->data.id[sizeof(newNode->data.id) - 1] = '\0';
    
    newNode->data.prioritas = prioritas;
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

// Mencari anggota berdasarkan ID (sama dengan SLL version)
Anggota* cariAnggota(AnggotaList* list, const char* id) {
    AnggotaNode* current = list->head;
    while (current != NULL) {
        if (strcmp(current->data.id, id) == 0) {
            return &(current->data);
        }
        current = current->next;
    }
    return NULL;
}

// Menampilkan semua anggota (sama dengan SLL version)
void tampilkanSemuaAnggota(AnggotaList* list) {
    if (list->head == NULL) {
        printf("Tidak ada anggota terdaftar.\n");
        return;
    }
    
    printf("\nDaftar Anggota:\n");
    printf("%-20s %-15s %-15s\n", "Nama", "ID", "Prioritas");
    printf("------------------------------------------------\n");
    
    AnggotaNode* current = list->head;
    while (current != NULL) {
        printf("%-20s %-15s %-15s\n", 
               current->data.nama, 
               current->data.id, 
               dapatkanLabelPrioritas(current->data.prioritas));
        current = current->next;
    }
}

// Menghapus anggota dari list (DLL version)
void hapusAnggota(AnggotaList* list, const char* id) {
    if (list->head == NULL) {
        printf("Anggota tidak ditemukan.\n");
        return;
    }
    
    AnggotaNode* current = list->head;
    
    // Cari node yang akan dihapus
    while (current != NULL && strcmp(current->data.id, id) != 0) {
        current = current->next;
    }
    
    if (current == NULL) {
        printf("Anggota tidak ditemukan.\n");
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
    printf("Anggota dengan ID %s telah dihapus.\n", id);
}

// Membebaskan memori yang digunakan oleh list anggota (DLL version)
void freeAnggotaList(AnggotaList* list) {
    AnggotaNode* current = list->head;
    while (current != NULL) {
        AnggotaNode* temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// Mendapatkan string untuk level prioritas (sama dengan SLL version)
const char* dapatkanLabelPrioritas(Prioritas p) {
    switch (p) {
        case DOSEN: return "Dosen";
        case MAHASISWA: return "Mahasiswa";
        case MASYARAKAT: return "Masyarakat";
        default: return "Tidak Diketahui";
    }
}
