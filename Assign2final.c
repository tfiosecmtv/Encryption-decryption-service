#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void encryption(FILE *fin, FILE *fout,char subarr[], char pass[])
{
    char for_encrypt;
    int i=0;
    while (!feof(fin)) {
        for_encrypt = fgetc(fin);
        if (feof(fin)) break;
        fprintf(fout, "%c", subarr[(unsigned char)((for_encrypt + pass[i])%254)]);
        i++;
        i %= strlen(pass);
    }
}
void decryption(FILE *fin, FILE *fout,char subarr[], char pass[])
{
    char for_decrypt;
    int i=0;
    while (!feof(fin)) {
        for_decrypt = fgetc(fin);
        if (feof(fin)) break;
        int n=0;
        do{
            n++;
        }while(for_decrypt!=subarr[n - 1]);
        n--;
        fprintf(fout, "%c", (unsigned char)((n-pass[i]) % 254));
        i++;
        i %= strlen(pass);
    }
}
void readmykeyfile(FILE *key_file, char keyfile[254]) { //function for reading the contents of keyfile
    int i = 0;
    while (i < 254) {
        keyfile[i] = fgetc(key_file);
        i++;
    }
}
int main() {
    setvbuf(stdout, NULL, _IONBF, 0);
    printf("WELCOME to the program!\n");
    printf("ENTER your password:\n");
    char password[255];
    scanf("%s", password);
    char key_file_store[254];
    FILE *key_file = NULL;
    key_file = fopen("key.254", "r"); // opens keyfile and further lines of code test if it's working or not
    if (key_file == NULL) {
        printf("CANNOT open the keyfile!\n");
        return 0;
    }
    readmykeyfile(key_file, key_file_store); //gets the content of keyfile and stores it into the array
    
    char ch[128],c;
    do {
        printf("MENU: e-encrypt a file, q-quit, d-decrypt a file\n");
        
        scanf("%s", ch);
        c=ch[0];
        
        switch (c) {case 'e': //switch is used for menu commands
            {
                printf("ENTER a file to encrypt\n");
                FILE *toencrypt;
                char name[256];
                scanf("%s", name);
                toencrypt=fopen(name, "r"); // opens file for encryption and further lines of code test if it's working or not
                if(toencrypt==NULL) {
                    printf("CANNOT open\n");
                    continue;
                }
                
                printf("ENTER a filename for the encrypted file\n");
                FILE *forencrypt;
                char nameout[256];
                scanf("%s", nameout);
                forencrypt=fopen(nameout, "w"); // opens file for encrypted text and further lines of code test if it's working or not
                if(forencrypt==NULL) {
                    printf("CANNOT open\n");
                    continue;}
                
                encryption(toencrypt, forencrypt, key_file_store, password); //starts encryption
                fclose(toencrypt);
                fclose(forencrypt);
                break;
            }
                
            case 'd': {
                printf("ENTER a file to decrypt\n");
                FILE *todecrypt;
                char name[256];
                scanf("%s", name);
                todecrypt=fopen(name, "r"); // opens file for decryption and further lines of code test if it's working or not
                if(todecrypt==NULL) {
                    printf("CANNOT open\n");
                    continue;}
                
                printf("ENTER a filename for the encrypted file\n");
                FILE *fordecrypt;
                char nameout[256];
                scanf("%s", nameout);
                fordecrypt=fopen(nameout, "w"); // opens file for decrypted text and further lines of code test if it's working or not
                if(fordecrypt==NULL) {
                    printf("CANNOT open\n");
                    continue;}
                
                decryption(todecrypt, fordecrypt, key_file_store, password); //starts decryption
                fclose(todecrypt);
                fclose(fordecrypt);
                break;}
                
            case 'q':{break;}
                
            default: printf("UNRECOGNIZED command\n");
                
        }}while (ch[0]!='q');
    
    printf("BYE!\n");
}
