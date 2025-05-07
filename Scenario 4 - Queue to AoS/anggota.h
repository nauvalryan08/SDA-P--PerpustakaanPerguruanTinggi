#ifndef ANGGOTA_H
#define ANGGOTA_H

typedef enum {
    MASYARAKAT,
    MAHASISWA,
    DOSEN
} Prioritas;

typedef struct {
    char nama[100];
    char id[20];
    Prioritas prioritas;
} Anggota;

typedef struct AnggotaNode {
    Anggota data;
    struct AnggotaNode* next;
} AnggotaNode;

typedef struct {
    AnggotaNode* head;
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
