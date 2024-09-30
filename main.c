//Created by Michal Kilian on 18.11.2021
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct zaznam {
    char prezenter[52];
    char rodne_cislo[12];
    char kod_pr[5];
    char nazov_pr[152];
    char mena_aut[202];
    char typ_pr[4];
    char cas_pr[6];
    char datum[10];
    struct zaznam *dalsi_zaznam;
} ZAZNAM;

//funkcia na zistenie poctu zaznamov
void subor_pocet_zaznamov(FILE *subor, int *pocet_zaznamov_ptr) {
    int pocet_riadkov = 0;
    char character;
    for (character = getc(subor); character != EOF; character = getc(subor))
        if (character == '\n')
            pocet_riadkov = pocet_riadkov + 1;

    *pocet_zaznamov_ptr = (pocet_riadkov + 1) / 9;
    rewind(subor);
}

//funkcia n na nacitanie zaznamov zo suboru
void funkcia_n(FILE **subor, int **n_ptr, int *pocet_zaznamov_ptr, ZAZNAM **head) {

    //otvorenie suboru
    (*subor) = fopen("konferencny_zoznam(2).txt", "r");

    if ((*subor) == NULL)
        printf("Zaznamy neboli nacitane!\n");

    else {
        if (**n_ptr == 0) {
            //zistenie poctu zaznamov
            subor_pocet_zaznamov(*subor, pocet_zaznamov_ptr);

            //nacitanie zaznamov zo suboru
            (*head) = malloc(sizeof(struct zaznam));
            ZAZNAM *aktualny = (*head);
            ZAZNAM *nasledujuci = NULL;
            char riadok[202];

            for (int i = 0; i < (*pocet_zaznamov_ptr); i++) {
                fgets(riadok, 5, *subor);
                strcpy(aktualny->prezenter, fgets(riadok, 52, (*subor)));
                strcpy(aktualny->rodne_cislo, fgets(riadok, 12, (*subor)));
                strcpy(aktualny->kod_pr, fgets(riadok, 5, (*subor)));
                strcpy(aktualny->nazov_pr, fgets(riadok, 152, (*subor)));
                strcpy(aktualny->mena_aut, fgets(riadok, 202, (*subor)));
                strcpy(aktualny->typ_pr, fgets(riadok, 4, (*subor)));
                strcpy(aktualny->cas_pr, fgets(riadok, 6, (*subor)));
                strcpy(aktualny->datum, fgets(riadok, 10, (*subor)));

                if (i == *pocet_zaznamov_ptr - 1)
                    aktualny->dalsi_zaznam = NULL;
                else {
                    nasledujuci = malloc(sizeof(struct zaznam));
                    aktualny->dalsi_zaznam = nasledujuci;
                    aktualny = nasledujuci;
                }
            }

            printf("Nacitalo sa %d zaznamov\n", (*pocet_zaznamov_ptr));
            (**n_ptr) = 1;
            rewind(*subor);

        } else {
            //uvolnenie pamate
            ZAZNAM *aktualny = (*head);
            ZAZNAM *nasledujuci;

            while (aktualny != NULL) {
                nasledujuci = aktualny->dalsi_zaznam;
                free(aktualny);
                aktualny = nasledujuci;
            }
            (*head) = NULL;

            //nacitanie zaznamov zo suboru
            (*head) = malloc(sizeof(struct zaznam));
            char riadok[202];

            for (int i = 0; i < (*pocet_zaznamov_ptr); i++) {
                fgets(riadok, 5, *subor);
                strcpy(aktualny->prezenter, fgets(riadok, 52, (*subor)));
                strcpy(aktualny->rodne_cislo, fgets(riadok, 12, (*subor)));
                strcpy(aktualny->kod_pr, fgets(riadok, 5, (*subor)));
                strcpy(aktualny->nazov_pr, fgets(riadok, 152, (*subor)));
                strcpy(aktualny->mena_aut, fgets(riadok, 202, (*subor)));
                strcpy(aktualny->typ_pr, fgets(riadok, 4, (*subor)));
                strcpy(aktualny->cas_pr, fgets(riadok, 6, (*subor)));
                strcpy(aktualny->datum, fgets(riadok, 10, (*subor)));

                if (i == *pocet_zaznamov_ptr - 1)
                    aktualny->dalsi_zaznam = NULL;
                else {
                    nasledujuci = malloc(sizeof(struct zaznam));
                    aktualny->dalsi_zaznam = nasledujuci;
                    aktualny = nasledujuci;
                }
            }

            printf("Nacitalo sa %d zaznamov\n", (*pocet_zaznamov_ptr));
            (**n_ptr) = 1;
            rewind(*subor);
        }

    }
}

//funkcia v na vypis celeho spajaneho zoznamu zaznamov
void funkcia_v(ZAZNAM *head, int **n_ptr, int pocet_zaznamov_ptr, int **p_ptr) {

    if (**n_ptr == 1 || **p_ptr == 1) {
        ZAZNAM (*aktualny) = head;

        for (int i = 0; i < pocet_zaznamov_ptr; i++) {
            printf("%i.\n", i + 1);
            printf("Prezenter: %s", aktualny->prezenter);
            printf("Rodne cislo: %s", aktualny->rodne_cislo);
            printf("Kod prezentacnej miestnosti: %s", aktualny->kod_pr);
            printf("Nazov prispevku: %s", aktualny->nazov_pr);
            printf("Mena autorov: %s", aktualny->mena_aut);
            printf("Typ prezentovania: %s", aktualny->typ_pr);
            printf("Cas prezentovania: %s", aktualny->cas_pr);
            printf("Datum: %s", aktualny->datum);

            aktualny = aktualny->dalsi_zaznam;
        }
        printf("\n");
    }
}

//funkcia p na pridanie zaznamu do spajaneho zoznamu zaznamov
void funkcia_p(ZAZNAM **head, int **pocet_zaznamov_ptr, int n_ptr, int **p_ptr) {
    char prezenter_p[52], rodne_cislo_p[12], kod_pr_p[5], nazov_pr_p[152], mena_aut_p[202], typ_pr_p[4],
            cas_pr_p[6], datum_p[10];

    //pouzivatel zada poziciu kam sa ma pridat zaznam
    int pozicia;
    ZAZNAM *novy = malloc(sizeof(struct zaznam));

    if (scanf("%i", &pozicia) <= 0)
        printf("Neplatna pozicia\n");
    else {
        getchar();
        //pouzivatel zada novy zaznam
        printf("Zadaj novy zaznam: \n");

        fgets(prezenter_p, 52, stdin);
        strcpy(novy->prezenter, prezenter_p);
        fgets(rodne_cislo_p, 12, stdin);
        strcpy(novy->rodne_cislo, rodne_cislo_p);
        fgets(kod_pr_p, 5, stdin);
        strcpy(novy->kod_pr, kod_pr_p);
        fgets(nazov_pr_p, 152, stdin);
        strcpy(novy->nazov_pr, nazov_pr_p);
        fgets(mena_aut_p, 202, stdin);
        strcpy(novy->mena_aut, mena_aut_p);
        fgets(typ_pr_p, 4, stdin);
        strcpy(novy->typ_pr, typ_pr_p);
        fgets(cas_pr_p, 6, stdin);
        strcpy(novy->cas_pr, cas_pr_p);
        fgets(datum_p, 10, stdin);
        strcpy(novy->datum, datum_p);

        //ak neboli zaznamy nacitane tak vytvori prvy na zaciatku
        if (n_ptr == 0) {
            novy->dalsi_zaznam = (*head);
            (*head) = novy;
            (**pocet_zaznamov_ptr)++;
            (**p_ptr)++;
        } else {
            ZAZNAM *aktualny = (*head);
            ZAZNAM *predchadzajuci = NULL;

            for (int i = 1; i <= (**pocet_zaznamov_ptr); i++) {
                if (pozicia == 1 && i == pozicia) {
                    novy->dalsi_zaznam = (*head);
                    (*head) = novy;
                    (**pocet_zaznamov_ptr)++;
                    break;
                }
                if (i == pozicia - 1)
                    predchadzajuci = aktualny;
                if (i == pozicia) {
                    predchadzajuci->dalsi_zaznam = novy;
                    novy->dalsi_zaznam = aktualny;
                    (**pocet_zaznamov_ptr)++;
                    break;
                }
                if (pozicia > (**pocet_zaznamov_ptr)) {
                    if (i == (**pocet_zaznamov_ptr)) {
                        aktualny->dalsi_zaznam = novy;
                        novy->dalsi_zaznam = NULL;
                        (**pocet_zaznamov_ptr)++;
                        break;
                    }
                }
                aktualny = aktualny->dalsi_zaznam;
            }
        }
    }
}

//funkcia z na zmazanie zoznamov podla rodneho cisla
void funkcia_z(ZAZNAM **head, int **pocet_zaznamov_ptr) {
    if ((*head) == NULL)
        return;

    ZAZNAM *aktualny = (*head);
    ZAZNAM *vymazany = NULL;

    char rodne_cislo_z[12];
    printf("Zadaj rodne cislo: ");
    scanf("%s", rodne_cislo_z);
    getchar();

    //ak sa maze prvy zaznam
    if (aktualny != NULL && strncmp(aktualny->rodne_cislo, rodne_cislo_z, 10) == 0) {
        (*head) = aktualny->dalsi_zaznam;
        (**pocet_zaznamov_ptr)--;
        free(aktualny);
    }

    //ak sa maze zaznam iny ako prvy
    ZAZNAM *akt = (*head);
    ZAZNAM *predchadzajuci = NULL;

    for (int i = 0; i < (**pocet_zaznamov_ptr); i++) {
        if (strncmp(akt->rodne_cislo, rodne_cislo_z, 10) != 0) {
            predchadzajuci = akt;
            akt = akt->dalsi_zaznam;
        }
        if (akt == NULL)
            return;
        predchadzajuci->dalsi_zaznam = akt->dalsi_zaznam;
        (**pocet_zaznamov_ptr)--;
        vymazany = akt;
        free(vymazany);
    }
}

/*funkcia f1 na rekurziu
int fib1(int n) {
    if (n <= 1)
        return n;
    else
        return fib1(n - 2) + fib1(n - 1);
}

//funkcia f2 na iterativnu
int fib2(int n) {
    if (n <= 1)
        return n;
    else {
        int n_1, n_2, i, sucet;
        n_1 = 0;
        n_2 = 1;
        for (i = 2; i <= n; i++) {
            sucet = n_1 + n_2;
            n_1 = n_2;
            n_2 = sucet;
        }
        return sucet;
    }
}

//int funkcia() {
//    return 1;
//}

//v maine: //int (*funkcia_ptr) (int) = &funkcia();

//bitove operatory: sucin &, sucet |, exkl. sucet ^, negacia ~

void binarny_histogram(unsigned int x) {
    int a[10], i;
    for (i = 0; x > 0; i++) {
        a[i] = x % 2;
        x = x / 2;
    }
    for (i = i - 1; i >= 0; i--)
        printf("%d", a[i]);
    printf("\n");
}*/

//funkcia h na vypis poloziek zoznamu podla kodu prezentacnej miestnosti
void funkcia_h(ZAZNAM *head, int **pocet_zaznamov_ptr) {
    if (head == NULL)
        return;

    char kod_pr_h[5];
    printf("Zadaj kod prezentacnej miestnosti: ");
    scanf("%s", kod_pr_h);

    int counter = 0;
    ZAZNAM (*aktualny) = head;

    for (int i = 0; i < (**pocet_zaznamov_ptr); i++) {
        //ak sa najde kod prezentacnej miestnosti tak vypise zaznam tohto cloveka
        if (strncmp(aktualny->kod_pr, kod_pr_h, 3) == 0) {
            counter++;
            printf("%i.\n", counter);
            printf("Prezenter: %s", aktualny->prezenter);
            printf("Rodne cislo: %s", aktualny->rodne_cislo);
            printf("Kod prezentacnej miestnosti: %s", aktualny->kod_pr);
            printf("Nazov prispevku: %s", aktualny->nazov_pr);
            printf("Mena autorov: %s", aktualny->mena_aut);
            printf("Typ prezentovania: %s", aktualny->typ_pr);
            printf("Cas prezentovania: %s", aktualny->cas_pr);
            printf("Datum: %s", aktualny->datum);
        }
        aktualny = aktualny->dalsi_zaznam;
    }
    if (counter == 0)
        printf("Pre prezentacnu miestnost %s nie su prezentujuce osoby.\n", kod_pr_h);
    else
        printf("\n");
}

//funkcia a na aktualizaciu typu prezentovania prispevku
void funkcia_a(ZAZNAM *head, int **pocet_zaznamov_ptr) {
    if (head == NULL)
        return;

    ZAZNAM *aktualny = head;
    char rodne_cislo_a[12], novy_typ_pr_a[4];
    int check = 0;
    //pouzivatel zada rodne cislo a novy tp prezentovania
    printf("Zadaj rodne cislo:");
    scanf("%s", rodne_cislo_a);
    getchar();
    printf("Zadaj novy typ prezentovania:");
    scanf("%s", novy_typ_pr_a);
    getchar();

    //overenie korektnosti rodneho cisla
    /*long long rodne_c = strtoll(rodne_cislo_a, NULL, 10);
    if (rodne_c % 11 == 0)
        check = 0;
    else
        check++;*/

    //overenie korektnosti typu prezentovania
    if (novy_typ_pr_a[0] == 'U' || novy_typ_pr_a[0] == 'P' && novy_typ_pr_a[1] == 'D' || novy_typ_pr_a[1] == 'P')
        check = 0;
    else
        check++;

    //ak su zadane udaje korektne
    if (check == 0) {
        for (int i = 0; i < (**pocet_zaznamov_ptr); i++) {
            if (strncmp(aktualny->rodne_cislo, rodne_cislo_a, 10) == 0) {
                strncpy(aktualny->typ_pr, novy_typ_pr_a, 2);

                unsigned int dlzka_prezentera = strlen(aktualny->prezenter) - 1;
                unsigned int dlzka_nazvu_pr = strlen(aktualny->nazov_pr) - 1;

                printf("Prezenter s menom %.*s bude prezentovat prispevok %.*s: %.2s\n", dlzka_prezentera,
                       aktualny->prezenter, dlzka_nazvu_pr, aktualny->nazov_pr, aktualny->typ_pr);
            }
            aktualny = aktualny->dalsi_zaznam;
        }

    }
        //ak su zadane udaje nekorektne
    else {
        printf("Zadane udaje nie su korektne, zadaj novy retazec: ");
        scanf("%s %s\n", rodne_cislo_a, novy_typ_pr_a);

        for (int i = 0; i < (**pocet_zaznamov_ptr); i++) {
            if (strncmp(aktualny->rodne_cislo, rodne_cislo_a, 10) == 0) {
                strncpy(aktualny->typ_pr, novy_typ_pr_a, 2);

                unsigned int dlzka_prezentera = strlen(aktualny->prezenter) - 1;
                unsigned int dlzka_nazvu_pr = strlen(aktualny->nazov_pr) - 1;

                printf("Prezenter s menom %.*s bude prezentovat prispevok %.*s: %.2s\n", dlzka_prezentera,
                       aktualny->prezenter, dlzka_nazvu_pr, aktualny->nazov_pr, aktualny->typ_pr);
            }
            aktualny = aktualny->dalsi_zaznam;
        }
    }
}

//funkcia r na prehodenie 2 zaznamov v spajanom zozname
void funkcia_r() {}

//funkcia k na ukoncenie programu
void funkcia_k(FILE **subor, ZAZNAM **head, int **n_ptr, int **p_ptr) {

    //uvolnenie alokovanej pamate
    if (**n_ptr == 1 || **p_ptr == 1) {
        ZAZNAM *aktualny = (*head);
        ZAZNAM *nasledujuci;

        while (aktualny != NULL) {
            nasledujuci = aktualny->dalsi_zaznam;
            free(aktualny);
            aktualny = nasledujuci;
        }
        (*head) = NULL;
    }

    //uzavriem subor
    if (fclose(*subor) == EOF)
        printf("Subor sa nepodarilo zatvorit\n");
}


int main() {
    FILE *subor;
    int pocet_zaznamov = 0, *pocet_zaznamov_ptr = &pocet_zaznamov;
    int n = 0;
    int *n_ptr = &n;
    int p = 0;
    int *p_ptr = &p;

    ZAZNAM *head = NULL;

    char prikaz;

    printf("Zadaj prikaz: (n) (v) (p) (z) (h) (a) (r) (k)\n");
    while (scanf(" %c", &prikaz)) {
        switch (prikaz) {
            case 'n':
                funkcia_n(&subor, &n_ptr, pocet_zaznamov_ptr, &head);
                break;
            case 'v':
                funkcia_v(head, &n_ptr, *pocet_zaznamov_ptr, &p_ptr);
                break;
            case 'p':
                funkcia_p(&head, &pocet_zaznamov_ptr, *n_ptr, &p_ptr);
                break;
            case 'z':
                funkcia_z(&head, &pocet_zaznamov_ptr);
                break;
            case 'h':
                funkcia_h(head, &pocet_zaznamov_ptr);
                break;
            case 'a':
                funkcia_a(head, &pocet_zaznamov_ptr);
                break;
            case 'r':
                funkcia_r();
                break;
            case 'k': {
                funkcia_k(&subor, &head, &n_ptr, &p_ptr);
                return 0;
            }

            default:
                printf("Zadal si nespravny prikaz\n");

        }
    }
    return 0;
}