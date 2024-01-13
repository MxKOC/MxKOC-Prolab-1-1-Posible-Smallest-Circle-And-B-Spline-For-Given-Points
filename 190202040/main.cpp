#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>
#include <math.h>



struct Nokta{
 double x;
 double y;
};

struct Daire{
 double yaricap;
 struct Nokta daire;
};

//-----------------------------------------------------------------------------------------------------------------------------
//Bu fonksiyonda iki nokta arasi uzaklik belirlenir

double uzaklik_bul(struct Nokta nokta1,struct Nokta nokta2){                                          // hepsi icin cap bulma

double sonuc=sqrt(pow(nokta1.x-nokta2.x,2)+pow(nokta1.y-nokta2.y,2));
return sonuc;

}

//-----------------------------------------------------------------------------------------------------------------------------
//Bu fonksiyonda iki nokta arasindaki orta nokta belirlenir


struct Daire cap_belirle1(struct Nokta nokta1,struct Nokta nokta2){                               // sadece 2 nokta icin cember olusturma

    struct Daire cap;
    cap.daire.x=(nokta1.x+nokta2.x)/2;
    cap.daire.y=(nokta1.y+nokta2.y)/2;

    cap.yaricap=uzaklik_bul(nokta1,nokta2)/2;
    return cap;
}

//-----------------------------------------------------------------------------------------------------------------------------
//Bu fonksiyonda 3 erli noktalarin cevrel cember merkezi hesaplanir belirlenir


struct Daire cap_belirle2(struct Nokta n1,struct Nokta n2,struct Nokta n3){                        //sadece 3 nokta icin cember olusturma

struct Nokta nokta_cevrel;

double Bx=n2.x - n1.x;
double By=n2.y - n1.y;
double Cx=n3.x - n1.x;
double Cy=n3.y - n1.y;

double B=(Bx*Bx)+(By*By);
double C=(Cx*Cx)+(Cy*Cy);
double D=((Bx*Cy)-(By*Cx));

nokta_cevrel.x=(Cy*B-By*C)/(2*D);
nokta_cevrel.y=(C*Bx-B*Cx)/(2*D);
nokta_cevrel.x=nokta_cevrel.x+n1.x;
nokta_cevrel.y=nokta_cevrel.y+n1.y;


struct Daire cap;
cap.daire.x=nokta_cevrel.x;
cap.daire.y=nokta_cevrel.y;
cap.yaricap=uzaklik_bul(nokta_cevrel,n1);



return cap;
}



//-----------------------------------------------------------------------------------------------------------------------------
//Bu fonksiyonda noktalarin daire icinde kalip kalmadigi belirlenir



int dogrulama(struct Daire daire_dogrula,struct Nokta nokta1[],int N){            //hepsi icin nokta kontrolu

    struct Nokta nokta_dongu;
    int a;

for(int i=0 ; i<N ; i++){

    nokta_dongu.x=nokta1[i].x;
    nokta_dongu.y=nokta1[i].y;
    a=uzaklik_bul(daire_dogrula.daire,nokta_dongu);

    if(a>daire_dogrula.yaricap){         //hep false olursa ise yarar
        return 0;                       // 1 kere true olursa 0 doner ve ise yaramaz
        }
 }

    return 1;
}


//-----------------------------------------------------------------------------------------------------------------------------
//Bu fonksiyon baslangic fonksiyonudur 0 ve 1 nokta icin hizli atama yapar

struct Daire ana_fonk(struct Nokta nokta[],int N){   //---------------------anafonk---------------------------

struct Daire daire1;
daire1.daire.x=2;
daire1.daire.y=2;
daire1.yaricap=2;
struct Daire daire2;
daire2.yaricap=0;
daire2.daire.x=nokta[0].x;
daire2.daire.y=nokta[0].y;


if(N==0) return daire1;
if(N==1) return daire2;

struct Daire daireana1;

struct Daire buyuk;
buyuk.daire.x=0;
buyuk.daire.y=0;
buyuk.yaricap=INFINITY;

for (int i=0; i < N; i++) {
for (int j=i+1; j < N; j++) {

daireana1 = cap_belirle1(nokta[i],nokta[j]);



if((daireana1.yaricap<buyuk.yaricap) &&  dogrulama(daireana1,nokta,N)){

    buyuk.daire.x=daireana1.daire.x;
    buyuk.daire.y=daireana1.daire.y;
    buyuk.yaricap=daireana1.yaricap;


}}}




for (int i = 0; i < N; i++) {
for (int j = i + 1; j < N; j++) {
for (int k = j + 1; k < N; k++) {


daireana1=cap_belirle2(nokta[i],nokta[j],nokta[k]);


if((daireana1.yaricap<buyuk.yaricap) &&  dogrulama(daireana1,nokta,N)){

    buyuk.daire.x=daireana1.daire.x;
    buyuk.daire.y=daireana1.daire.y;
    buyuk.yaricap=daireana1.yaricap;

}


}}}

return buyuk;

}

//-----------------------------------------------------------------------------------------------------------------------------
//Bu fonksiyonda kordinat sistemi bastirilir



void cizgiler(int a,struct Daire dairex){

char yazi1[30];
char yazi2[30];
char yazi3[30];
char sayilar[30];

sprintf(yazi1,"%f",dairex.daire.x);
sprintf(yazi2,"%f",dairex.daire.y);
sprintf(yazi3,"%f",dairex.yaricap);

outtextxy(20,50,"Daire Merkezi:");

outtextxy(130,50,"X:");
outtextxy(150,50,yazi1);
outtextxy(220,50,"Y:");
outtextxy(240,50,yazi2);


outtextxy(20,80,"Daire Yaricapi:");
outtextxy(130,80,yazi3);


for(int m=-1;m>-40;m--){
    sprintf(sayilar,"%d",m);
    outtextxy(720,497+(-m*a),sayilar);
    outtextxy(745-(-m*a),470,sayilar);
}

for(int m=1;m<40;m++){
    sprintf(sayilar,"%d",m);
    outtextxy(765,493-(m*a),sayilar);
    outtextxy(747+(m*a),515,sayilar);
}


setcolor(LIGHTGREEN);

     line(0,500,1500,500);
    line(0,501,1500,501);
    line(0,499,1500,499);
    for(int i=1;i<70;i++){
        line(750+(i*a),490,750+(i*a),510);
        line(750-(i*a),490,750-(i*a),510);
    }


    line(751,0,751,1000);
    line(750,0,750,1000);
    line(749,0,749,1000);

    for(int i=1;i<45;i++){

        line(740,500+(i*a),760,500+(i*a));
        line(740,500-(i*a),760,500-(i*a));

    }
}


//-----------------------------------------------------------------------------------------------------------------------------
//Bu fonksiyonda istege bagli hermite spline egrisi bastirilir
	Nokta yol(struct Nokta nokta[] ,float t)
	{
		int p0, p1, p2, p3;


        p1 = (int)t + 1;
        p2 = p1 + 1;
        p3 = p2 + 1;
        p0 = p1 - 1;


		t = t - (int)t;

		float tt = t * t;
		float ttt = tt * t;

		float q1 = -ttt + 2.0f*tt - t;
		float q2 = 3.0f*ttt - 5.0f*tt + 2.0f;
		float q3 = -3.0f*ttt + 4.0f*tt + t;
		float q4 = ttt - tt;

		float tx = 0.5f * (nokta[p0].x * q1 + nokta[p1].x * q2 + nokta[p2].x * q3 + nokta[p3].x * q4);
		float ty = 0.5f * (nokta[p0].y * q1 + nokta[p1].y * q2 + nokta[p2].y * q3 + nokta[p3].y * q4);

		return{ tx, ty };
	}







//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------
//-----------------------------------------------------------------------------------------------------------------------------



int main()
{
//-----------------------------------------------------------------------------------------------------------------------------
// Burada satir sayma islemi

FILE *dosya;

int N=1;
char satir;
if((dosya=fopen("C:\\Users\\Muhammed KOÇ\\Desktop\\190202040\\dosya.txt","r")) != NULL){
while(!feof(dosya)){
satir=getc(dosya);
if(satir=='\n'){
   N++;
}
}
}


    else{

    printf("BULUNAMADI");

}
fclose(dosya);


//-----------------------------------------------------------------------------------------------------------------------------
//Burada noktalar okunur


struct Nokta nokta[N];






int i=0,j;
if((dosya=fopen("C:\\Users\\Muhammed KOÇ\\Desktop\\190202040\\dosya.txt","r")) != NULL){

while(!feof(dosya)){




    fscanf(dosya,"%lf %lf",&nokta[i].x,&nokta[i].y);
    i++;
}


for(j=0;j<i;j++){
    printf("%d.NOKTA -> %lf,%lf\n",j+1,nokta[j].x,nokta[j].y);
    }



}

else{

    printf("BULUNAMADI");
}

fclose(dosya);


//-----------------------------------------------------------------------------------------------------------------------------
//Burada noktalar ana fonksiyona gönderilir ve sonuc alinir
struct Daire dairex =ana_fonk(nokta,N);
printf("DAIRE MERKEZININ X KORDINATI:%lf \nDAIRE MERKEZININ Y KORDINATI:%lf \nDAIRE MERKEZININ YARICAPI: %lf",dairex.daire.x,dairex.daire.y,dairex.yaricap);

//-----------------------------------------------------------------------------------------------------------------------------


initwindow( 1500, 1000, "Window Text",0, 0);


setcolor(BLUE);
    int x0=750;
    int y0=500;
    int a=20;                                               //Degisistirilebilir parametre kucuk buyuk boyut farki icin

setcolor(YELLOW);
cizgiler(a,dairex);  //Burada kordinat sistemi basilir

    float x1, y1, r;

    setcolor(YELLOW);
  	for(int i=0;i<N;i++){

    x1=nokta[i].x;
  	y1=nokta[i].y;
    r=5;
    circle((x1*a+x0),(y0-(a*y1)),(r));   //Burada noktalar basilir
  	}

  	struct Nokta nokta_yeni[N];
  	for(int say=0;say<N;say++){

        nokta_yeni[say+1].x=nokta[say].x;
        nokta_yeni[say+1].y=nokta[say].y;

  	nokta_yeni[0].x=nokta[0].x;
  	nokta_yeni[0].y=nokta[0].y;

  	}


  	//Proje B spline a gore yapilmistir ama gozlemlenen sonuc ile istenilen sonuc ayni olmadigi dusunulerek daha uygun gorulen hermite spline da
    // proje ye dahil edilmisir.

    // Eger istenirse yorum satirlariyla belirtilen hermite spline yeri yorum satirina alinip B spline diye belirtilen yerdeki yorum satirlari
    // kaldirilirsa B spline gorunecektir.




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

                                               //HERMITE SPLINE


struct Nokta nokta2;
setcolor(WHITE);
for (float t = 0; t < N-1; t += 0.0005f)
		{
			Nokta nokta2 = yol(nokta_yeni,t);
			circle((nokta2.x*a+x0),(y0-(a*nokta2.y)),1);
		}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                              //B SPLINE
    /*
for(int i=0;i<N+1;i++)
{

            for(float t = 0.0; t <1.0; t += 0.0005){
    double koordinatsistemxt = ((pow (1-t, 3) * nokta[i-1].x + (3 *pow (t, 3)-6*pow (t, 2)+4) * nokta[i].x +
            (-3 * pow (t, 3) +3*pow (t, 2)+3*t+1)* nokta[i+1].x + (pow (t, 3))* nokta[i+2].x))/6;


        double koordinatsistemyt = ((pow (1-t, 3) * nokta[i-1].y + (3 *pow (t, 3)-6*pow (t, 2)+4) * nokta[i].y +
            (-3 * pow (t, 3) +3*pow (t, 2)+3*t+1)* nokta[i+1].y + (pow (t, 3))* nokta[i+2].y))/6;
    circle((koordinatsistemxt*a)+x0,(koordinatsistemyt*a)+y0,1);


    }
    }

     */
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Burada cember ve merkez basilir

  	x1=dairex.daire.x;
  	y1=dairex.daire.y;
  	r=dairex.yaricap;


    setcolor(GREEN);
    circle((x1*a+x0),(y0-(a*y1)),1);
    circle((x1*a+x0),(y0-(a*y1)),2);
    circle((x1*a+x0),(y0-(a*y1)),3);
  	circle((x1*a+x0),(y0-(a*y1)),(a*r));
  	circle((x1*a+x0),(y0-(a*y1)),(a*r+1));
  	circle((x1*a+x0),(y0-(a*y1)),(a*r+2));
  	circle((x1*a+x0),(y0-(a*y1)),(a*r+3));
  	getch();

 return 0;
}

