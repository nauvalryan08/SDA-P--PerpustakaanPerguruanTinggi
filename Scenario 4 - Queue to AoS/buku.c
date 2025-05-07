#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buku.h"

void initBukuArray(BukuArray* array) {
    array->size = 0;
}

int tambahBuku(BukuArray* array, const char* judul, int stok) {
    if (array->size >= MAX_BUKU) {
        printf("Kapasitas buku penuh.\n");
        return 0;
    }
	
	int i = 0; 
    while (i < array->size) {
        if (strcmp(array->data[i].judul, judul) == 0) {
            array->data[i].stok += stok;
            return 1;
        }
        i++;
    }

    strncpy(array->data[array->size].judul, judul, sizeof(array->data[0].judul) - 1);
    array->data[array->size].judul[sizeof(array->data[0].judul) - 1] = '\0';
    array->data[array->size].stok = stok;
    array->data[array->size].dipinjam = 0;
    array->size++;

    return 1;
}

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

int hapusBuku(BukuArray* array, const char* judul) {
	int i = 0; 
    while (i < array->size) {
        if (strcmp(array->data[i].judul, judul) == 0) {
        	int j = i;
            while (j < array->size - 1) {
                array->data[j] = array->data[j + 1];
            }
            array->size--;
            j++;
            return 1;
        }
        i++;
    }
    return 0;
}

void freeBukuArray(BukuArray* array) {
    array->size = 0;
}
