#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define GemiAdetMiktari 4
#define GemiBoyutlari 5,4,3,2
#define GemiMiktarlari 1,2,3,4

void goster( int );
void yerlestir( int[] , int[] , int );
void oyna ( int , int , int );
int alan( int[] , int[] , int );

char a[10][10]; // gemi tablosu
char b[10][10]; // oyuncu tablosu

int main(){

    int i , j ;
    for( i = 0 ; i < 10 ; i++ ) for( j = 0 ; j < 10 ; j++ ) a[i][j] = '-';
    for( i = 0 ; i < 10 ; i++ ) for( j = 0 ; j < 10 ; j++ ) b[i][j] = '-';
    srand(time(0));

    int gemiler[GemiAdetMiktari] = { GemiBoyutlari };
    int miktar[GemiAdetMiktari] = { GemiMiktarlari };
    int ToplamAlan = ( alan( gemiler , miktar , GemiAdetMiktari ) );
    
    if ( ToplamAlan > 40 ){
    	printf("KOD HATASÝ");
    	return 1;
	}

    yerlestir( gemiler , miktar , GemiAdetMiktari );

    oyna( ToplamAlan*2 , 0 , ToplamAlan );
    goster( 0 );
    system("pause");

    return 0;
}

void oyna( int h , int hatali , int Kalan ){
    system("cls");
    goster( 1 );
    if ( Kalan == 0 ){
    	printf("\t\t  KAZANDINIZ!\n");
        return;
	}
    else if( h == 0 || h < Kalan ){
        printf("\t\t  Hakkiniz Bitti!\n");
        return;
    }
    else if( hatali == 1 ) printf("\n\tYanlis Girildi.");
    else if( hatali == 2 ) printf("\n\tZaten Daha Once Bu Konumu Kullandiniz.");
    else printf("\n");
    hatali = 0;
    
    char k;
    int l,m;
    printf("\n\tHak Sayisi = %d , Kalan Vurulacak Alan = %d\n\tOnce Karakteri Sonra Sayiyi Girerek\n\tHamlenizi Yapacaginiz Koordinatlari Giriniz-->",h,Kalan);
    scanf("%c%d",&k,&l);
    system("cls");

    if( k >= 'a' && k <= 'j' ) m = k - 'a';
    else if ( k >= 'A' && k <= 'J' ) m = k - 'A';
    else {
    	hatali = 1;
    	goto hata;
	}
    if ( l < 0 || l > 9 ){
        hatali = 1;
        goto hata;
    }
    
    if( b[m][l] == '-'){
        if( a[m][l] == 'O') {
        	b[m][l] = 'X';
        	--Kalan;
        }
        else b[m][l] = 'O';
    }
    else{
        hatali = 2;
        goto hata;
    }
    h--;
    hata:
    oyna( h , hatali , Kalan );
}

void goster( int k ){
    int i,j;
    printf("\n\t\t    0 1 2 3 4 5 6 7 8 9\n");
    for ( i = 0 ; i < 10 ; i++ ){
        printf("\n\t\t%c   ", (i+'A') );
        for ( j = 0 ; j < 10 ; j++ ){
        	if ( k==0 ) printf("%c ",a[i][j] );
        	else printf("%c ",b[i][j]);
        }
    }
    printf("\n\n");
}

void yerlestir( int g[] , int miktar[] , int sayi ){
    int i , j ;
    for ( i = 0 ; i < sayi ; i++){ // gemi tipini degistirir.
        for ( j = miktar[i] ; j != 0 ; j-- ){ // bu tipteki gemi miktarinca calisir..
            int t = 11 - g[i];
            while(1){
				int yon = ( rand() % 2 ); // yon = 0 > asagi , yon = 1 > sag
				int y,x,n;
				if ( yon == 0 ){
					y = ( rand() % t );
                	x = ( rand() % 10 );
				}
				else {
					y = ( rand() % 10 );
                	x = ( rand() % t );
				}
                int k = y;
                int l = x;
                int hata = 0 ;
                for ( n=0 ; n<g[i] ; n++ ){  //konumun yone gore bulundugu yerin bos olmasý kontrol ediliyor.
                    if( a[k][l] == '-' && ( ( a[k+1][l] == '-' ) || k == 9 ) && ( ( a[k-1][l] == '-' ) || k == 0 ) 
					&& ( ( a[k][l+1] == '-' ) || l == 9 ) && ( ( a[k][l-1] == '-' ) || l == 0 ) ){ // yerlestirme kosulumuz ^-^
                        if ( yon == 0 ) k++;
                        else l++;
                    }
                    else{
                        hata = 1;
                        break;
                    }
                }
                if( hata == 1 ) continue; // yerlesme kosulu saglanmiyor
                else{ // kosul saglaniyor yerlestirmeye basla
                    for ( n=0 ; n < g[i] ; n++ ){
                        a[y][x] = 'O';
                        if( yon == 0 ) y++;
                        else x++;
                    }
                    break;
}	}	}	}	}

int alan( int g[] , int miktar[] , int sayi ){
	int i,toplam=0;
	for ( i=0 ; i<sayi ; i++ ) toplam += g[i]*miktar[i];
	return toplam;
}
