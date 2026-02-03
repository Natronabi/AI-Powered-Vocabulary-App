    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main() {
        char kelime[50];
        FILE *dosya;

        // Karşılamayı döngü dışına aldık ki sadece 1 kere görünsün
        printf("--- AI Kelime Defterine Hos Geldiniz ---\n");
        printf("(Cikmak icin 'cikis' yazabilirsiniz)\n\n");

        while(1) {
            int internet_var_mi = system("ping -n 1 google.com > nul");
            printf("Ogrenmek istedigin kelime: ");
            if (internet_var_mi == 0) {
            printf("[DURUM: Cevrimici] AI destekli kayit yapiliyor...\n");
            } 
            else {
            printf("[DURUM: Cevrimdisi] Kelime sadece yerel deftere kaydedilecek.\n");
            }
            fflush(stdout);
            scanf("%s", kelime);

            // ÇIKIŞ KONTROLÜ: Eğer kullanıcı 'cikis' yazarsa döngüyü kır
            if (strcmp(kelime, "cikis") == 0) {
                printf("Programdan cikiliyor, hoscakal!\n");
                break; 
            }

            // DOSYA İŞLEMİ: Her kelime için dosyayı açıp kapatıyoruz
            dosya = fopen("kelimelerim.txt", "a");

            if (dosya == NULL) {
                printf("Hata: Dosya sistemi su an calismiyor!\n");
                return 1;
            }

            fprintf(dosya, "%s | 0\n", kelime);
            fclose(dosya);
            // n8n Köprüsü: Eğer internet varsa kelimeyi AI'ya gönder
            if (internet_var_mi == 0) {
            char komut[512]; // Komut için yeterli bir alan açıyoruz
            
            // n8n Webhook URL'ini aşağıya yapıştır
            sprintf(komut, "curl -X POST -H \"Content-Type: application/json\" -d \"{\\\"kelime\\\":\\\"%s\\\"}\" https://natronabi.app.n8n.cloud/webhook-test/kelime-getir", kelime);
            
            // Hazırladığımız CURL komutunu sisteme veriyoruz
            system(komut);
            printf("-> AI cevabı n8n üzerinden işleniyor...\n");
        }

            printf("-> '%s' kaydedildi.\n\n", kelime);
            
            // Buraya 'return 0' koymuyoruz çünkü koyarsak döngü başa dönmez!
        }

        return 0; // Program her şey bittikten sonra burada kapanır
    }