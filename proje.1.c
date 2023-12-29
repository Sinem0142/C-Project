#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define N 81

void csv_oku(char* dosya_adi, int adj[N][N]);
void en_yakin_ekleme_algoritmasi(int adj[N][N], int baslangic_dugumu, int tur[N+1]);
void matrixPrint(int matrix[][N], int rows, int cols);

int main() {
    int adj[N][N];
    int i;
    int baslangic_dugumu = 5; // ankara 6. sehir oldugu icin 5. indekse denk gelir

    // Excel tablosunun CSV'ye cevrilen 2. sayfasindan uzakliklar okunur
    csv_oku("Mesafe.csv", adj);
    matrixPrint(adj, N, N);
    int tur[N+1];

    // en yakin ekleme algoritmasini uygular
    en_yakin_ekleme_algoritmasi(adj, baslangic_dugumu, tur);

    int mesafe = 0;
    printf("Ankara (06) ile baslanilan hamilton dongusu:\n");
    for (i = 0; i <= N; i++) {
        // hamiltonian dongusunu yazdir
        printf("%d ", tur[i]+1);
        if (i > 0) {
            // hamiltonian dongusunu yazdirirken bir yandan da sehirler arasindaki uzaklik degerini mesafe degiskenine ekle
            mesafe += adj[tur[i-1]][tur[i]];
        }
    }
    // mesafeyi yazdir
    printf("\nToplam alinan mesafe: %d\n", mesafe);

    return 0;
}

void csv_oku(char* dosya_adi, int adj[N][N]) {
    FILE *fp;
    char satir[1024];
    char *token;
    int satir_no, sutun_no;

    // dosya acilamama kontrolu
    fp = fopen(dosya_adi, "r");
    if (fp == NULL) {
        printf("Dosya Acilamadi\n");
        return;
    }

    // ilk satir atlanir cunku sehir isimleri var
    fgets(satir, 1024, fp);
    printf(satir);
    
    // csv dosyasindan degerler alinir ve adjacency matrix doldurulur
    for (satir_no = 0; satir_no < N; satir_no++) {
        fgets(satir, 1024, fp);

        // ilk 3 sutunu atla cunku mesafe degerleri degiller.
        // atlamak icin 3 tane strtok kullaniriz her strtok sonraki elemana yani sutuna gecer.
        token = strtok(satir, ";");
        token = strtok(NULL, ";");
        token = strtok(NULL, ";");

        // mesafe degerini alip atoi ile csv'deki string elemani integer'a cevirip adj matrisindeki yerine yerlestiririz
        for (sutun_no = 0; sutun_no < N; sutun_no++) {
            token = strtok(NULL, ";");
            int deger = atoi(token);
            adj[satir_no][sutun_no] = deger;
        }
    }

    // dosya kapatilir
    fclose(fp);
}

void en_yakin_ekleme_algoritmasi(int adj[N][N], int baslangic_dugumu, int tur[N+1]) {
    int ziyaret_edildi[N] = {0};
    ziyaret_edildi[baslangic_dugumu] = 1;
    tur[0] = baslangic_dugumu;
	int i, j, k;
    // Mevcut turun en yakin ziyaret edilmemis sehrini bul ve turuna ekle
    for (i = 1; i <= N; i++) {
        int min_mesafe = 9999;
        int min_index = -1;

        // Tum sehirlere bak
        for (j = 0; j < N; j++) {
            // ziyaret edilmis bir sehirse atlayip for loopuna devam et
            if (ziyaret_edildi[j]) continue;

            // Mevcut turun son sehhrinden sehir j'ye ve sehir j'den baslangic sehrine olan mesafeyi hesapla
            int mesafe = adj[tur[i-1]][j] + adj[j][baslangic_dugumu];

            // eger daha kýsa bir mesafeyse min_mesafe
            if (mesafe < min_mesafe) {
                min_mesafe = mesafe;
                min_index = j;

                int sonraki_dugum_indexi = i;
                // Þehir j'yi mevcut turda en iyi konuma bul
                for (k = i; k > 0; k--) {
                    // Þehir j'nin turdaki k-1 ve k konumlarý arasýna yerleþtirilmesi durumunda mesafedeki deðiþikliði hesapla
                    if (adj[tur[k-1]][j] + adj[j][tur[k]] - adj[tur[k-1]][tur[k]] < min_mesafe) {
                        min_mesafe = adj[tur[k-1]][j] + adj[j][tur[k]] - adj[tur[k-1]][tur[k]];
                        sonraki_dugum_indexi = k;
                    }
                }

                // Þehir j'yi mevcut turda en iyi konuma yerleþtir
                tur[i] = j;
                
                // Tur dizisindeki tum ogeleri pozisyon i'den pozisyon "sonraki_dugum_indexi"ne kadar bir saga kaydir
                for (k = i; k > sonraki_dugum_indexi; k--) {
                    tur[k] = tur[k-1];
                }

                tur[sonraki_dugum_indexi] = j;
            }
        }

        ziyaret_edildi[min_index] = 1;
    }

    tur[N] = baslangic_dugumu;
}


void matrixPrint(int matrix[][N], int rows, int cols) {
	int i,j;
    for ( i = 0; i < rows; i++) {
        for ( j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}
