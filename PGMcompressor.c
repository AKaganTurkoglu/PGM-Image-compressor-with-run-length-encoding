//Aydýn kaðan Türkoðlu
// 18011060
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#define MAX 16384
// PGM dosyasýnda # ile baþlayan yorum satýrý bulunmamalýdýr.
typedef struct PGMData {
    int satir;
    int sutun;
    int max_gray;
    int pixel[MAX];
} PGMDATA;
typedef struct RLE {
    int satir;
    int sutun;
    int max_gray;
    int combo[MAX];
    int renk[MAX];
} RLE;

PGMDATA *PGM_aktar(char *dosyaadi);
RLE *RLE_encoder(PGMDATA *pgm);
PGMDATA *RLE_decoder(RLE *rle);
RLE *RLE_aktar(char *dosyaadi);
int charToInt(char c);
int satirsay(char *dosyaadi);
int elemansay(char *dosyaadi);
char *strndup(const char *s, size_t n);
void pgm_ekrana_yazdir(PGMDATA *pgm);
void Ek_islemler(int islem);
void RLE_dosya_yaz(RLE *rle);
void pgm_dosya_yazdir(PGMDATA *pgm);
void RLE_ekran_yaz(RLE *rle);

int main(int argc, char *argv[]) {
      int bitis=0,talep,islem;
      char isim[100];
      
      while(bitis==0){
      printf("\n PGM okuyup sonra Run Length Encoding yapip en son da test_decoded olusturmak icin (ortaya karisik): 1");
		printf("\n PGM dosyasini ekrana yazdirmak icin: 2 ");
		printf("\n PGM dosyasina Run Length Encoding yapmak icin (test_encoded.txt olusuyor) : 3");
		printf("\n Run Length Encoding dosyasi olan test_encoded dosyasini ekrana yazdirmak icin: 4");
		printf("\n Run Length Encoding yapilmis test_encoded.txt dosyasinin uygunlugunu TEST etmek icin (dosya olusturmadan) : 5");
		printf("\n Run Length Encoding yapilmis test_encoded.txt dosyasindan test_decoded.pgm uretmek (dosyaya yazma) icin : 6");
		printf("\n Verilen bir Rengin degerini degistirme  : 7");
		printf("\n Koordinatlari verilmis bir pikselin degerini degistirmek icin : 8");
		printf("\n Resmin histogramini hesaplamak icin : 9");
		printf("\n hangi islem sekmesine girmek istiyorsunuz: ");
		scanf("%d",&talep);
		system ("cls");	
		switch(talep){
			
			case 1:	
			printf("\n islem yapmak istediginiz PGM dosyasinin adini giriniz (.pgm dahil orn:(input.pgm)) : ");
			scanf("%s",isim);
			pgm_dosya_yazdir(RLE_decoder(RLE_encoder(PGM_aktar(isim))));
			break;	
			
			case 2:	
			printf("\n ekrana yazdirmak istediginiz PGM dosyasinin adini giriniz (.pgm dahil orn:(input.pgm)) : ");
			scanf("%s",isim);
			pgm_ekrana_yazdir(PGM_aktar(isim));
			break;
			
			case 3:	
			printf("\n Run Length Encoding yapmak istediginiz PGM dosyasinin adini giriniz (.pgm dahil orn:(input.pgm)) : ");
			scanf("%s",isim);
	//		RLE_encoder(PGM_aktar(isim));
			RLE_ekran_yaz(RLE_encoder(PGM_aktar(isim)));			
			break;
			
			case 4:	
			RLE_ekran_yaz(RLE_aktar("test_encoded.txt"));
			break;
			
			case 5:	
			RLE_decoder(RLE_aktar("test_encoded.txt"));
			break;
			
			case 6:	
			pgm_dosya_yazdir(RLE_decoder(RLE_aktar("test_encoded.txt")));
			break;
			
			case 7:	
			Ek_islemler(1);
			break;
			
			case 8:	
			Ek_islemler(2);
			break;
			
			case 9:	
			Ek_islemler(3);
			break;
		}
	printf("\n\n yeni islem yapmak icin 0 (sifir) giriniz \n programi guvenli bir sekilde bitirmek icin 1 (bir) giriniz: ");
	scanf("%d",&bitis);	
	system ("cls");
	  }
      
return 0;
}

RLE *RLE_aktar(char *dosyaadi){
	RLE *rle=(RLE*)(malloc(sizeof(RLE)));	
			FILE *Data;	
			int i,j=0;
			int eleman=elemansay("test_encoded.txt");
        	int dizi[eleman];			
	    Data=fopen("test_encoded.txt","r+"); 
    		if(Data==NULL){
		printf("test_encoded.txt bulunamadi");	}		
		for(i=0;i< eleman ;i++){
    	fscanf(Data,"%d,",&dizi[i]);		
		}
		rle->satir=dizi[1];
		rle->sutun=dizi[0];
		rle->max_gray=dizi[2];
		for(i=3;i<eleman ;i=i+2){
    	rle->combo[j]=dizi[i];
		rle->renk[j]=dizi[i+1];
		j++;
		}
		fclose(Data);
		return rle;
}

void pgm_ekrana_yazdir(PGMDATA *pgm){
	int i,j,pixel;
	printf("P2\n");
	printf("%d %d\n",pgm->sutun,pgm->satir);
	printf("%d\n",pgm->max_gray);
	pixel=pgm->sutun*pgm->satir;
	j=pgm->sutun;
	for(i=0;i<pixel;i++){
	printf("%d ",pgm->pixel[i]);
	if(i==j-1){
	printf("\n");
	j=j+pgm->sutun;	
	}
	}
}
void pgm_dosya_yazdir(PGMDATA *pgm){
	FILE *Data;
	Data=fopen("test_decoded.pgm","w+");
    		if(Data==NULL){
		printf("dosya olusturulamadý");	}
    int i,j,pixel;
	fprintf(Data,"P2\n");
	fprintf(Data,"%d %d\n",pgm->sutun,pgm->satir);
	fprintf(Data,"%d\n",pgm->max_gray);
	pixel=pgm->sutun*pgm->satir;
	j=pgm->sutun;
	for(i=0;i<pixel;i++){
	fprintf(Data,"%d ",pgm->pixel[i]);
	if(i==j-1){
	fprintf(Data,"\n");
	j=j+pgm->sutun;	
	}
	}
	fclose(Data);	
}

int elemansay(char *dosyaadi){
	FILE *fp=fopen(dosyaadi,"r");
	int durum;
	int satir=0;
	if(fp==NULL){
	printf("hata olustu");}

	while(!feof(fp)){
		durum=fgetc(fp);
		if (durum==','){
			satir++;
		}
	}
	fclose(fp);
	return satir;
}

void Ek_islemler(int islem){
	int i,j,his,eleman,renkyeni,renkeski,satir,sutun,konum,konum2,kontrol;
	RLE *rle=(RLE*)(malloc(sizeof(RLE)));
	rle=RLE_aktar("test_encoded.txt");
	
	if(islem==1){
		printf("\n degistirmek istediginiz eski rengi giriniz = ");
		scanf("%d",&renkeski);
		printf("\n yeni eklemek istediginiz yeni rengi giriniz = ");
		scanf("%d",&renkyeni);
		eleman=elemansay("test_encoded.txt");
		eleman=(eleman-3)/2;
	for(i=0;i<eleman;i++){
		if(rle->renk[i]==renkeski)
		rle->renk[i]=renkyeni;
	}
	RLE_dosya_yaz(rle);
	RLE_ekran_yaz(rle);
		printf("\n");
	}
	
	else if(islem==2){
		printf("\n degistirmek istediginiz pikselin satir sayisini giriniz (0 ile %d arasinda deger giriniz) = ",rle->satir-1);
		scanf("%d",&satir);
		while(satir<0&&satir>rle->satir-1){
		printf("\n verilen sinirlar disinda giris yaptiniz lutfen girdinizi guncelleyiniz (0 ile %d arasinda deger giriniz) = ",rle->satir-1);
		scanf("%d",&satir);	
		}
		printf("\ndegistirmek istediginiz pikselin sutun sayisini giriniz (0 ile %d arasinda deger giriniz) = ",rle->sutun-1);
		scanf("%d",&sutun);
		while(sutun<0&&sutun>rle->sutun-1){
		printf("\n verilen sinirlar disinda giris yaptiniz lutfen girdinizi guncelleyiniz (0 ile %d arasinda deger giriniz) = ",rle->sutun-1);
		scanf("%d",&sutun);	
		}
		printf("\n yeni eklemek istediginiz yeni rengi giriniz (en yuksek %d giriniz) = ",rle->max_gray);
		scanf("%d",&renkyeni);
		while(renkyeni<0&&renkyeni>rle->max_gray){
		printf("\n verilen sinirlar disinda giris yaptiniz lutfen girdinizi guncelleyiniz (0 ile %d arasinda deger giriniz) = ",rle->max_gray);
		scanf("%d",&renkyeni);	
		}
		konum=(rle->sutun*satir)+sutun;
		j=0;
		konum2=konum;
		while(konum2>0){
			konum2=konum2 - rle->combo[j];
			j++;
		}
        eleman=elemansay("test_encoded.txt");
		eleman=(eleman-3)/2;
		eleman=eleman+2;
         int tmp[500][2],k=0;
		 if(konum2==0){
		 	eleman=eleman-1;
		 	for(i=0;i<eleman;i++){
		 		if(i==j){
				tmp[i][0]=1;
				tmp[i][1]=renkyeni;
				
				if(rle->combo[i]!=1){
				tmp[(i+1)][0]=rle->combo[i]-1;
				tmp[i+1][1]=rle->renk[i];
    			i++;		
				            		}
    			i++;
    			k++;
				}
                tmp[i][0]=rle->combo[k];
				tmp[i][1]=rle->renk[k];
	            k++;
			 }
			 
			 
		 }else if(konum2==-1){
		 	eleman=eleman-1;
		 	for(i=0;i<eleman;i++){
		 		if(i==j-1){
				tmp[i][0]=rle->combo[i]-1;
				tmp[i][1]=rle->renk[i];
				tmp[i+1][0]=1;
				tmp[i+1][1]=renkyeni;
    			i=i+2;
    			k++;
				}
                tmp[i][0]=rle->combo[k];
				tmp[i][1]=rle->renk[k];
	            k++;
			 }
		 }else{
		 for(i=0;i<eleman;i++){
		 		if(i==j-1){
				tmp[i][0]=rle->combo[i]+konum2;
				tmp[i][1]=rle->renk[i];
				tmp[i+1][0]=1;
				tmp[i+1][1]=renkyeni;
				tmp[i+2][0]=rle->combo[i]-1-tmp[i][0];
				tmp[i+2][1]=rle->renk[i];
    			i=i+3;
    			k++;
				}
                tmp[i][0]=rle->combo[k];
				tmp[i][1]=rle->renk[k];
	            k++;
			 }	
		 }
		   for(i=0;i<eleman;i++){
		   	rle->combo[i]=tmp[i][0];
		   	rle->renk[i]=tmp[i][1];
		   }   
    RLE_ekran_yaz(rle);
		printf("\n");	   
	RLE_dosya_yaz(rle);	
	}
	
	else if(islem==3){
	printf("\n******** RESMIN HISTOGRAMI *********\n ");
	printf("resim %d * %d toplam %d pixelden olusmaktadir. \n",rle->satir,rle->sutun,(rle->satir*rle->sutun));
	eleman=0;
		while(rle->combo[eleman]!=0)
		eleman++;
	int mat[eleman][2];
	his=0;
	for(i=0;i<eleman;i++){
		mat[his][0]=rle->renk[i];
		mat[his][1]=rle->combo[i];	
		his++;	
		
    j=i+1;
    while(j<eleman){
    	if(mat[his-1][0]==rle->renk[j]){
    	mat[i][1]=mat[i][1]+rle->combo[j];
		rle->renk[j]=-1;		}
    j++;
	}
	
	if(rle->renk[i]!=-1&&his<eleman){
	printf("%d rengi %d sayida bulunmaktadir \n",mat[his-1][0],mat[his-1][1]); }	
	
	}
		
	}
	
}

int satirsay(char *dosyaadi){
	FILE *fp=fopen(dosyaadi,"r");
	int durum;
	int satir=0;
	if(fp==NULL){
	printf("hata olustu");}

	while(!feof(fp)){
		durum=fgetc(fp);
		if (durum=='\n'){
			satir++;
		}
	}
	fclose(fp);
	return satir;
}

PGMDATA *RLE_decoder(RLE *rle){	
PGMDATA *pgm=(PGMDATA*)(malloc(sizeof(PGMDATA)));
		int i,j=0,k;
		int eleman=elemansay("test_encoded.txt");
		//KONTROLLER
		int topEleman=rle->satir*rle->sutun;
		int topElKontrol=0,renkkontrol=0,arkakontrol=0,yerkontrol=0;
		
		for(i=0;i<(eleman-3)/2;i++){
			topElKontrol=topElKontrol+rle->combo[i];
			if(rle->renk[i]<0 || rle->renk[i]>255){
		renkkontrol=rle->renk[i];	}
		    if(rle->renk[i]==rle->renk[i+1]){
		arkakontrol=rle->renk[i];
		yerkontrol=i;	}
		
		}
		
		if(topEleman==topElKontrol){
			printf("\n Piksel sayisi uyusuyor");			
		if(renkkontrol==0){
			printf("\n Renkler tutarli");			
		if(arkakontrol==0){
			printf("\n arka arkaya gelen renk yok");			
			printf("\n Bir hata bulunmadi. isleme devam ediliyor \n");
		pgm->satir=rle->satir;
		pgm->sutun=rle->sutun;
		pgm->max_gray=rle->max_gray;
		j=0;
		k=0;
		for(i=0;i<(eleman-3)/2;i++){
			while(j < rle->combo[i]){
			pgm->pixel[k]=rle->renk[i];
			j++;
			k++;
			}
			j=0;
		}
		printf("test_decoded dosyasi hazir\n");	
		}else{
		printf("\n yanlis compression yapildigi icin islem yapilamiyor \n ");
		printf(" hataya sebeb olan eleman = %d konumu = %d\n",arkakontrol,yerkontrol);
		}
			
		}else{
		printf("\n renk araliginin disina cikildi icin islem yapilamiyor disaridaki eleman = %d \n",renkkontrol);	
		}
			
		}else{
	printf("satir sayisi = %d sutun sayisi = %d olmasý gereken eleman sayisi = %d \n",rle->satir,rle->sutun,topEleman);
	printf(" gercekte olan eleman sayisi = %d - eleman sayisi uyusmadigi icin islem yapýlamiyor\n",topElKontrol);
		}
		pgm_ekrana_yazdir(pgm);
		return pgm;
}

int charToInt(char c){
	int num = 0;
	num = c - '0';
	return num;
}

RLE *RLE_encoder(PGMDATA *pgm){
			FILE *Data;
	int uzulunluk = pgm->satir*pgm->sutun;
	int count,i,j=0;
    RLE *rle=(RLE*)(malloc(sizeof(RLE)));
    rle->max_gray=pgm->max_gray;
    rle->satir=pgm->satir;
    rle->sutun=pgm->sutun;
    for (i=0;i<uzulunluk; i++) {
         count = 1;
        while (i<uzulunluk-1 && pgm->pixel[i] == pgm->pixel[i + 1]) {
            count++;
            i++;
        }
        rle->combo[j]=count;
        rle->renk[j]=pgm->pixel[i];
        j++;
    }
    RLE_dosya_yaz(rle);
   
    return rle;
}

void RLE_ekran_yaz(RLE *rle){
	    int i,j=0;
		while(rle->combo[j]!=0)
		j++;
		printf("\n islem gerceklestirilmistir. test_encoded.txt dosyasinin son hali asagidadir\n");
   	printf("ilk 3 deger satir sayisi, sutun sayisi ve en buyuk piksel degerini temsil ediyor\n");
    printf("%d,%d,%d,",rle->sutun,rle->satir,rle->max_gray);    
		for(i=0;i<j;i++){
    	printf("%d,%d,",rle->combo[i],rle->renk[i]);		
		}
}

void RLE_dosya_yaz(RLE *rle){
		int i,j=0;
		while(rle->combo[j]!=0)
		j++;
		FILE *Data;
	Data=fopen("test_encoded.txt","w+");
    		if(Data==NULL){
		printf("dosya olusturulamadý");	}
    	fprintf(Data,"%d,%d,%d,",rle->sutun,rle->satir,rle->max_gray);
		for(i=0;i<j;i++){
    	fprintf(Data,"%d,%d,",rle->combo[i],rle->renk[i]);		
		}
		printf("\n test_encoded.txt basari ile olusturuldu");
    	fclose(Data);
}

char *strndup(const char *s, size_t n) {
 // bu fonksiyon normalde string.h icinde varmýs.
 //  ama bazen bulunmuyormus o yuzden ne olur ne olmaz ekledim.
    char *p;
    size_t n1;
    for (n1 = 0; n1 < n && s[n1] != '\0'; n1++)
        continue;
    p = malloc(n + 1);
    if (p != NULL) {
        memcpy(p, s, n1);
        p[n1] = '\0';
    }
    return p;
}

PGMDATA *PGM_aktar(char *dosyaadi){
	PGMDATA *pgm=(PGMDATA*)(malloc(sizeof(PGMDATA)));
	int i=0,j=0,satir,tmp,count=0;
          satir=satirsay(dosyaadi);	
	int sayidizi[16000];
    char *lutfen[500];
    char *cp;
FILE *filePointer= fopen(dosyaadi, "r");
	if(filePointer==NULL){
	printf("dosya acilamadi");}
int bufferUzunluk = 255;
char buffer[bufferUzunluk];

while(fgets(buffer, bufferUzunluk, filePointer)) {
	lutfen[i] = strndup(buffer, 50000);
    i++;
}
          char * token = strtok(lutfen[1], " "); 
                j=0;
          for(i=1;i<=satir;i++){	  
        while( token != NULL ) {
        	if(sayidizi[0]==sayidizi[2]&&j==3){
        		j=j-1;
			} 
        	sayidizi[j]=strtol(token,&cp,10);
      token = strtok(NULL, " ");    
      j++;
   }
   token = strtok(lutfen[i], " ");
   } 
// normalde bu kýsýma gerek yoktu ama verdiðiniz input.pgm satýr sonlarýnda white space olduðundan (normalde olmamasý gerekiyor)
// kontrol yapmak zorunda kaldým.  
    int tmp2=sayidizi[0]+1;
    tmp=sayidizi[0]+3;
    for(i=tmp+tmp2;i<j;i=i+tmp2){
    if(sayidizi[i]==sayidizi[i-tmp2])	
    	count++;
	}
	pgm->satir=sayidizi[1];
	pgm->sutun=sayidizi[0];
	pgm->max_gray=sayidizi[2];
	int kontrol=0;
		for(i=3;i<j;i++){
	if(count==sayidizi[1]-1){
			if(tmp!=i){
				pgm->pixel[kontrol]=sayidizi[i];
				kontrol++;
		}
		else{
				tmp=tmp+tmp2;			
		}
		
		}
		else{
			pgm->pixel[i-3]=sayidizi[i];
		}
	}
fclose(filePointer);
return pgm;	
}




