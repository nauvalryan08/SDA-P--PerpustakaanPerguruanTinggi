#ifndef BUKU_H
#define BUKU_H

// ADT untuk menyimpan informasi buku
typedef struct {
    char judul[100];
    int stok;
    int dipinjam; // jumlah yang sedang dipinjam
} Buku;

// Node untuk Doubly Linked List buku
typedef struct BukuNode {
    Buku data;
    struct BukuNode* next;
    struct BukuNode* prev;
} BukuNode;

// LinkedList untuk buku
typedef struct {
    BukuNode* head;
    BukuNode* tail; // Tambahan untuk DLL
    int size;
} BukuList;

// Fungsi-fungsi ADT Buku
void initBukuList(BukuList* list);
void tambahBuku(BukuList* list, const char* judul, int stok);
Buku* cariBuku(BukuList* list, const char* judul);
void tampilkanSemuaBuku(BukuList* list);
void hapusBuku(BukuList* list, const char* judul);
void freeBukuList(BukuList* list);

#endif
