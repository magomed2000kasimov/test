#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
    char last_name[50];
    char first_name[50];
    int proz;
    int gtx;
    int ssd;
    int hdd;
    int server;
} person;

void fprint_person(FILE* file, person* p) {
    fprintf(file,"%s %s %d %d %d %d %d\n",
            p->last_name,
            p->first_name,
            p->proz,
            p->gtx,
            p->ssd,
            p->hdd,
            p->server
    );
}

void person_create(person* p) {
    p->proz = p->gtx = p->ssd = p->hdd = p->server=0;

}

void person_destroy(person* p) {
    free(p->first_name);
    free(p->last_name);
    p->proz = p->gtx = p->ssd = p->hdd = 0;

}

int scan_person(FILE* file, person* p) {
    if (fscanf(file, "%s %s %d %d %d %d %d\n", p->last_name, p->first_name, &p->proz, &p->gtx, &p->ssd, &p->hdd, &p->server) == EOF) {
        return 0;
    }
    return 1;
}


int scan_person_from_stdin(person* p) {
    if (scanf("%s %s %d %d %d %d %d", p->last_name, p->first_name, &p->proz, &p->gtx, &p->ssd, &p->hdd, &p->server) == EOF) {
        return 0;
    }
    return 1;
}

void print_person(person* p) {
    printf("%s %s %d %d %d %d %d\n",
           p->last_name,
           p->first_name,
           p->proz,
           p->gtx,
           p->ssd,
           p->hdd,
           p->server
    );
}

void copy_file(FILE* input, FILE* output) {
    char c = fgetc(input);
    while (c != EOF) {
        fputc(c,output);
        c = fgetc(input);
    }
}

void print_file(FILE* input) {
    char c = fgetc(input);
    while (c != EOF) {
        putchar(c);
        c = fgetc(input);
    }
}

int enterChoice(void)
{
    int menu;
    printf("enter\n"
           "1-print\n"
           "2-zadanie\n"
           "3-add\n"
           "4-delete\n"
           "5-poisk\n"
           "6-end\n"
    );
    scanf("%d",&menu);
    return menu;
}





int main() {

    FILE* temp;
    int choice;
    FILE *output = fopen("in.txt", "rt");
    if (output == 0) {
        printf("%s\n", "Can't open database  file");
        exit(1);
    }
    FILE * base_bin = fopen("out.bin","wb");
    copy_file(output, base_bin);
    fclose(base_bin);
    fclose(output);
    person* cur_person = malloc(sizeof(person));
    person_create(cur_person);
    while ((choice = enterChoice()) != 6) {
        switch (choice) {
            case 1:
                base_bin = fopen("out.bin", "rb");
                while (scan_person(base_bin,cur_person)) {
                    print_person(cur_person);
                }
                fclose(base_bin);
                break;
            case 2:
                base_bin = fopen("out.bin", "rb");
                while (scan_person(base_bin,cur_person)) {
                    print_person(cur_person);
                }
                fclose(base_bin);
                break;
            case 3:
                base_bin = fopen("out.bin", "ab");
                printf("VVedite dannie \n");
                scan_person_from_stdin(cur_person);
                fprint_person(base_bin,cur_person);
                fclose(base_bin);
                break;
            case 4:
                base_bin = fopen("out.bin", "rb"); // udalenie po familii
                printf("Kogo udalit?\n");
                char to_remove[50];
                scanf("%s", to_remove);
                temp = fopen("program_temp_file.bin","wb");
                if (temp == 0) {
                    printf("Cant open temp file\n");
                    exit(1);
                }
                while (scan_person(base_bin, cur_person)) {
                    if (strcmp(cur_person->last_name,to_remove) != 0) {
                        fprint_person(temp,cur_person);
                    }
                }
                fclose(base_bin);
                base_bin = fopen("out.bin", "wb");
                fclose(temp);
                temp = fopen("program_temp_file.bin", "rb");
                copy_file(temp, base_bin);
                fclose(temp);
                fclose(base_bin);
                remove("program_temp_file.bin");
                break;
            case 5:
                base_bin = fopen("out.bin", "rb");
                printf("Kogo naiti?\n");
                char to_remove1[50];
                scanf("%s", to_remove1);
                temp = fopen("program_temp_file.bin","wb");
                if (temp == 0) {
                    printf("Cant open temp file\n");
                    exit(1);
                }
                while (scan_person(base_bin, cur_person)) {
                    if (strcmp(cur_person->last_name,to_remove1) == 0) {
                        printf("%s %s %d %d %d %d %d \n",
                               cur_person->last_name,
                               cur_person->first_name,
                               cur_person->proz,
                               cur_person->gtx,
                               cur_person->ssd,
                               cur_person->hdd,
                               cur_person->server
                        );

                    }
                }

        }
    }
    fclose(output);
    return 0;
}