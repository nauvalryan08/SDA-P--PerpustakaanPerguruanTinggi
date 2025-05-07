#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "peminjaman.h"
#include "buku.h"
#include "anggota.h"

// Inisialisasi list peminjaman (DLL version)
void initPeminjamanList(PeminjamanList* list) {
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}

// Menambahkan peminjam ke dalam antrian prioritas (DLL version)
void tambahPeminjam(PeminjamanList* list, const char* judulBuku, const char* idAnggota, Prioritas prioritas) {
    // Cari apakah buku sudah ada dalam list peminjaman
    PeminjamanListNode* currentListNode = list->head;
    PeminjamanListNode* prevListNode = NULL;
    
    while (currentListNode != NULL && strcmp(currentListNode->data.judulBuku, judulBuku) != 0) {
        prevListNode = currentListNode;
        currentListNode = currentListNode->next;
    }
    
    // Jika buku belum ada dalam list peminjaman, buat entry baru
    if (currentListNode == NULL) {
        PeminjamanListNode* newNode = (PeminjamanListNode*)malloc(sizeof(PeminjamanListNode));
        if (newNode == NULL) {
            printf("Gagal alokasi memori untuk peminjaman baru.\n");
            return;
        }
        
        strncpy(newNode->data.judulBuku, judulBuku, sizeof(newNode->data.judulBuku) - 1);
        newNode->data.judulBuku[sizeof(newNode->data.judulBuku) - 1] = '\0';
        newNode->data.headDosen = NULL;
        newNode->data.tailDosen = NULL;
        newNode->data.headMahasiswa = NULL;
        newNode->data.tailMahasiswa = NULL;
        newNode->data.headMasyarakat = NULL;
        newNode->data.tailMasyarakat = NULL;
        newNode->data.totalPeminjam = 0;
        newNode->next = NULL;
        newNode->prev = list->tail;
        
        // Tambahkan ke list
        if (list->head == NULL) {
            list->head = newNode;
        } else {
            list->tail->next = newNode;
        }
        list->tail = newNode;
        currentListNode = newNode;
        list->size++;
    }
    
    // Buat node peminjaman baru
    PeminjamanNode* newPeminjam = (PeminjamanNode*)malloc(sizeof(PeminjamanNode));
    if (newPeminjam == NULL) {
        printf("Gagal alokasi memori untuk data peminjam.\n");
        return;
    }
    
    strncpy(newPeminjam->idAnggota, idAnggota, sizeof(newPeminjam->idAnggota) - 1);
    newPeminjam->idAnggota[sizeof(newPeminjam->idAnggota) - 1] = '\0';
    newPeminjam->next = NULL;
    newPeminjam->prev = NULL;
    
    // Tambahkan ke antrian prioritas yang sesuai
    PeminjamanNode** head = NULL;
    PeminjamanNode** tail = NULL;
    
    switch (prioritas) {
        case DOSEN:
            head = &(currentListNode->data.headDosen);
            tail = &(currentListNode->data.tailDosen);
            break;
        case MAHASISWA:
            head = &(currentListNode->data.headMahasiswa);
            tail = &(currentListNode->data.tailMahasiswa);
            break;
        case MASYARAKAT:
            head = &(currentListNode->data.headMasyarakat);
            tail = &(currentListNode->data.tailMasyarakat);
            break;
    }
    
    if (*head == NULL) {
        *head = newPeminjam;
        *tail = newPeminjam;
    } else {
        newPeminjam->prev = *tail;
        (*tail)->next = newPeminjam;
        *tail = newPeminjam;
    }
    
    currentListNode->data.totalPeminjam++;
    printf("Peminjaman buku '%s' oleh anggota %s telah ditambahkan ke antrian.\n", judulBuku, idAnggota);
}

// Proses peminjaman buku (DLL version)
void prosesPeminjaman(PeminjamanList* peminjamanList, BukuList* bukuList, AnggotaList* anggotaList) {
    if (peminjamanList->head == NULL) {
        printf("Tidak ada antrian peminjaman.\n");
        return;
    }
    
    char judulBuku[100];
    printf("Masukkan judul buku yang akan diproses peminjamannya: ");
    scanf(" %[^\n]", judulBuku);
    
    // Cari buku dalam list peminjaman
    PeminjamanListNode* currentListNode = peminjamanList->head;
    while (currentListNode != NULL && strcmp(currentListNode->data.judulBuku, judulBuku) != 0) {
        currentListNode = currentListNode->next;
    }
    
    if (currentListNode == NULL) {
        printf("Tidak ada antrian peminjaman untuk buku '%s'.\n", judulBuku);
        return;
    }
    
    // Cari buku dalam list buku
    Buku* buku = cariBuku(bukuList, judulBuku);
    if (buku == NULL) {
        printf("Buku '%s' tidak ditemukan dalam sistem.\n", judulBuku);
        return;
    }
    
    // Cek stok buku
    if (buku->dipinjam >= buku->stok) {
        printf("Stok buku '%s' habis. Tidak bisa memproses peminjaman.\n", judulBuku);
        return;
    }
    
    // Cari peminjam prioritas tertinggi
    PeminjamanNode* peminjam = NULL;
    char* idAnggota = NULL;
    
    if (currentListNode->data.headDosen != NULL) {
        peminjam = currentListNode->data.headDosen;
        currentListNode->data.headDosen = peminjam->next;
        if (currentListNode->data.headDosen != NULL) {
            currentListNode->data.headDosen->prev = NULL;
        } else {
            currentListNode->data.tailDosen = NULL;
        }
    } else if (currentListNode->data.headMahasiswa != NULL) {
        peminjam = currentListNode->data.headMahasiswa;
        currentListNode->data.headMahasiswa = peminjam->next;
        if (currentListNode->data.headMahasiswa != NULL) {
            currentListNode->data.headMahasiswa->prev = NULL;
        } else {
            currentListNode->data.tailMahasiswa = NULL;
        }
    } else if (currentListNode->data.headMasyarakat != NULL) {
        peminjam = currentListNode->data.headMasyarakat;
        currentListNode->data.headMasyarakat = peminjam->next;
        if (currentListNode->data.headMasyarakat != NULL) {
            currentListNode->data.headMasyarakat->prev = NULL;
        } else {
            currentListNode->data.tailMasyarakat = NULL;
        }
    } else {
        printf("Tidak ada peminjam dalam antrian untuk buku '%s'.\n", judulBuku);
        return;
    }
    
    // Proses peminjaman
    idAnggota = peminjam->idAnggota;
    Anggota* anggota = cariAnggota(anggotaList, idAnggota);
    
    if (anggota == NULL) {
        printf("Anggota dengan ID %s tidak ditemukan.\n", idAnggota);
        free(peminjam);
        return;
    }
    
    buku->dipinjam++;
    currentListNode->data.totalPeminjam--;
    
    printf("Buku '%s' berhasil dipinjam oleh %s (%s).\n", 
           judulBuku, anggota->nama, dapatkanLabelPrioritas(anggota->prioritas));
    
    free(peminjam);
}

// Proses pengembalian buku (sama dengan SLL version)
void prosesPengembalian(PeminjamanList* peminjamanList, BukuList* bukuList, AnggotaList* anggotaList) {
    char judulBuku[100];
    char idAnggota[20];
    
    printf("Masukkan judul buku yang dikembalikan: ");
    scanf(" %[^\n]", judulBuku);
    
    printf("Masukkan ID anggota yang mengembalikan: ");
    scanf(" %s", idAnggota);
    
    // Cari buku dalam list buku
    Buku* buku = cariBuku(bukuList, judulBuku);
    if (buku == NULL) {
        printf("Buku '%s' tidak ditemukan dalam sistem.\n", judulBuku);
        return;
    }
    
    // Cari anggota
    Anggota* anggota = cariAnggota(anggotaList, idAnggota);
    if (anggota == NULL) {
        printf("Anggota dengan ID %s tidak ditemukan.\n", idAnggota);
        return;
    }
    
    // Kurangi jumlah dipinjam
    if (buku->dipinjam > 0) {
        buku->dipinjam--;
        printf("Buku '%s' berhasil dikembalikan oleh %s (%s).\n", 
               judulBuku, anggota->nama, dapatkanLabelPrioritas(anggota->prioritas));
    } else {
        printf("Tidak ada buku '%s' yang sedang dipinjam.\n", judulBuku);
    }
}

// Membatalkan peminjaman (DLL version)
void batalkanPeminjaman(PeminjamanList* list, const char* judulBuku, const char* idAnggota) {
    PeminjamanListNode* currentListNode = list->head;
    while (currentListNode != NULL && strcmp(currentListNode->data.judulBuku, judulBuku) != 0) {
        currentListNode = currentListNode->next;
    }
    
    if (currentListNode == NULL) {
        printf("Tidak ada antrian peminjaman untuk buku '%s'.\n", judulBuku);
        return;
    }
    
    // Cari di semua antrian prioritas
    int found = 0;
    struct {
        PeminjamanNode** head;
        PeminjamanNode** tail;
    } queues[] = {
        {&(currentListNode->data.headDosen), &(currentListNode->data.tailDosen)},
        {&(currentListNode->data.headMahasiswa), &(currentListNode->data.tailMahasiswa)},
        {&(currentListNode->data.headMasyarakat), &(currentListNode->data.tailMasyarakat)}
    };
    
    int i = 0;
    while (i < 3 && !found) {
        PeminjamanNode* current = *queues[i].head;
        PeminjamanNode* prev = NULL;
        
        while (current != NULL && !found) {
            if (strcmp(current->idAnggota, idAnggota) == 0) {
                found = 1;
                
                // Atur pointer prev dan next
                if (prev != NULL) {
                    prev->next = current->next;
                } else {
                    *queues[i].head = current->next;
                }
                
                if (current->next != NULL) {
                    current->next->prev = prev; // Perbaikan di sini
                } else {
                    *queues[i].tail = prev;
                }
                
                free(current);
                currentListNode->data.totalPeminjam--;
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

// Menampilkan antrian peminjaman untuk buku tertentu (sama dengan SLL version)
void tampilkanAntrianPeminjaman(PeminjamanList* list, const char* judulBuku) {
    PeminjamanListNode* currentListNode = list->head;
    while (currentListNode != NULL && strcmp(currentListNode->data.judulBuku, judulBuku) != 0) {
        currentListNode = currentListNode->next;
    }
    
    if (currentListNode == NULL) {
        printf("Tidak ada antrian peminjaman untuk buku '%s'.\n", judulBuku);
        return;
    }
    
    printf("\nAntrian Peminjaman untuk Buku '%s':\n", judulBuku);
    printf("Total Peminjam: %d\n", currentListNode->data.totalPeminjam);
    
    printf("\nDosen:\n");
    PeminjamanNode* current = currentListNode->data.headDosen;
    while (current != NULL) {
        printf("- %s\n", current->idAnggota);
        current = current->next;
    }
    
    printf("\nMahasiswa:\n");
    current = currentListNode->data.headMahasiswa;
    while (current != NULL) {
        printf("- %s\n", current->idAnggota);
        current = current->next;
    }
    
    printf("\nMasyarakat:\n");
    current = currentListNode->data.headMasyarakat;
    while (current != NULL) {
        printf("- %s\n", current->idAnggota);
        current = current->next;
    }
}

// Membebaskan memori yang digunakan oleh list peminjaman (DLL version)
void freePeminjamanList(PeminjamanList* list) {
    PeminjamanListNode* currentListNode = list->head;
    while (currentListNode != NULL) {
        // Bebaskan semua antrian peminjam
        PeminjamanNode* currentDosen = currentListNode->data.headDosen;
        while (currentDosen != NULL) {
            PeminjamanNode* temp = currentDosen;
            currentDosen = currentDosen->next;
            free(temp);
        }
        
        PeminjamanNode* currentMahasiswa = currentListNode->data.headMahasiswa;
        while (currentMahasiswa != NULL) {
            PeminjamanNode* temp = currentMahasiswa;
            currentMahasiswa = currentMahasiswa->next;
            free(temp);
        }
        
        PeminjamanNode* currentMasyarakat = currentListNode->data.headMasyarakat;
        while (currentMasyarakat != NULL) {
            PeminjamanNode* temp = currentMasyarakat;
            currentMasyarakat = currentMasyarakat->next;
            free(temp);
        }
        
        PeminjamanListNode* temp = currentListNode;
        currentListNode = currentListNode->next;
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
}
