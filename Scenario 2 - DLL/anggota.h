#ifndef ANGGOTA_H
#define ANGGOTA_H

// Tipe data untuk level prioritas anggota
typedef enum {
    MASYARAKAT,
    MAHASISWA,
    DOSEN
} Prioritas;

// ADT untuk menyimpan data anggota
typedef struct {
    char nama[100];
    char id[20];
    Prioritas prioritas;
} Anggota;

// Node untuk Doubly Linked List anggota
typedef struct AnggotaNode {
    Anggota data;
    struct AnggotaNode* next;
    struct AnggotaNode* prev;
} AnggotaNode;

// LinkedList untuk anggota
typedef struct {
    AnggotaNode* head;
    AnggotaNode* tail; // Tambahan untuk DLL
    int size;
} AnggotaList;

// Fungsi-fungsi ADT Anggota
void initAnggotaList(AnggotaList* list);
void tambahAnggota(AnggotaList* list, const char* nama, const char* id, Prioritas prioritas);
Anggota* cariAnggota(AnggotaList* list, const char* id);
void tampilkanSemuaAnggota(AnggotaList* list);
void hapusAnggota(AnggotaList* list, const char* id);
void freeAnggotaList(AnggotaList* list);
const char* dapatkanLabelPrioritas(Prioritas p);

#endif
