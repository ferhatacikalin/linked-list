#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>
#define DATA_FILE "data.txt"
struct Dugum
{
    int adet;
    char data[100];
    struct Dugum *next;
};
struct Dugum* Start=NULL;
struct Dugum* End=NULL;
void basaEkle(char data[100],int adet);
void arayaEkle(int pozisyon,char veri[100],int adet);
void sonaEkle(char data[100],int adet);
void yazdir();
int kelimeSay(char kelime[100]);
int eklendiMi(char kelime[100]);
int uygunPozisyon(int adet);

int main()
{
    setlocale( LC_ALL, "Turkish" );
    FILE *data_file;
    char temp[100];
    data_file=fopen(DATA_FILE, "r");
    if (data_file == NULL)
    {
        printf("dosya hatasi");
    }
    int eklendi=0;
    while (fscanf(data_file,"%s",&temp)!= -1)
    {
        int adet=kelimeSay(temp);
        int oncedenEklendi=eklendiMi(temp);
        if(Start==NULL){
                basaEkle(temp,adet);
                eklendi++;

        }
        else if(oncedenEklendi == -1){
            int uygunP=uygunPozisyon(adet);
            if(uygunP==1){
                basaEkle(temp,adet);
                eklendi++;
            }
            else if(uygunP==eklendi){
                sonaEkle(temp,adet);
                eklendi++;
            }
            else{
                arayaEkle(uygunP,temp,adet);
                eklendi++;
            }
            }

        }


    fclose(data_file);
    yazdir();
    return 0;
}
int uygunPozisyon(int adet){
    int pozisyon=1;
    struct Dugum *temp;
    temp=Start;
    while(temp!=NULL && temp->adet>=adet){

        temp=temp->next;
        pozisyon++;
    }
    return pozisyon;
}
int eklendiMi(char kelime[100])
{
    struct Dugum *temp;
    temp=Start;
    int i=0;
    while(temp!=NULL && strcmp(temp->data,kelime)!=0)
    {
        i++;
        temp=temp->next;

    }

    if(temp!=NULL)
    {
        return i;
    }
    else
    {
        return -1;
    }
}
int kelimeSay(char kelime[100])
{
    int kelime_count=0;
    char temp[100];
    FILE *source;
    source=fopen(DATA_FILE,"r");
    if(source==NULL)
    {
        printf("sorun var");
    }
    else
    {
        while(fscanf(source,"%s",&temp)!= -1)
        {
            if(strcmp(temp,kelime)==0)
            {
                kelime_count++;
            }

        }
    }
    fclose(source);
    return kelime_count;
}
void sonaEkle(char data[100],int adet)
{
    struct Dugum *yeni_dugum = (struct Dugum*) malloc(sizeof(struct Dugum));
    strcpy(yeni_dugum->data,data);
    yeni_dugum->adet=adet;
    yeni_dugum->next=NULL;
    if(Start==NULL)
    {
        Start=yeni_dugum;
    }
    else
    {
        End=Start;
        while(End->next!=NULL)
        {
            End=End->next;
        }
        End->next=yeni_dugum;

    }

}


void basaEkle(char data[100],int adet)
{
    struct Dugum *yeni_dugum = (struct Dugum*)malloc(sizeof(struct Dugum));
    strcpy(yeni_dugum ->data,data);
    yeni_dugum->adet=adet;
    yeni_dugum->next=Start;
    Start=yeni_dugum;

}
void arayaEkle(int pozisyon,char veri[100],int adet )
{
    struct Dugum *yeni_dugum, *temp;
    yeni_dugum=(struct Dugum*)malloc(sizeof(struct Dugum));
    strcpy(yeni_dugum->data,veri);
    yeni_dugum->adet=adet;
    yeni_dugum->next=NULL;
    temp=Start;
    for(int i=2; i<=pozisyon-1; i++)
    {
        temp=temp->next;
        if(temp==NULL) break;

    }
    if(temp->next !=NULL)
    {
        yeni_dugum->next=temp->next;
        temp->next=yeni_dugum;
    }


}
void yazdir()
{
    struct Dugum *yazdir=Start;
    int i=1;
    while(yazdir->next!=NULL)
    {
        printf("%d. %s:%d\n",i,yazdir->data,yazdir->adet);
        yazdir=yazdir->next;
        i++;
    }
    printf("%d. %s:%d\n",i,yazdir->data,yazdir->adet);
}
