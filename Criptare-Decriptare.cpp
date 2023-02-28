#include <iostream>
#include <cstring>
#include <cstdlib> //pentru rand()
#include <ctime>
using namespace std;

char c[95][4][3], msj[513], auxi[257];
int  opt, cheie;
bool repeat=0;


void optiune()
{
    if (repeat==0)
    {
        cout<<"Alegeti o optiune: \n";
        cout<<"1) Pentru a introduce cheia si mesajul pe care doriti sa-l criptati, inserati cifra 1; \n";
        cout<<"2) Pentru a introduce doar mesajul, iar cheia sa fie generata automat, inserati cifra 2; \n";
        cout<<"3) Pentru a decripta un mesaj, inserati cifra 3; \n";
        cout<<"4) Pentru ajutor si mai multe informatii inserati tasta 4. \n\n";
    }
    cin>>opt; cout<<endl;
    if (repeat==1) cout<<"\n";
}


void palindrom()                                          //opt 1, 2 si 3
{
    int pal;
    pal=cheie;
    while(pal!=0)
    {
        cheie=cheie*10+pal%10;
        pal=pal/10;
    }
}


void dePal()                                              //opt 1, 2, si 3
{
    int n=0;
    int pal=cheie;
    while(pal!=0)
    {
        n++;
        pal=pal/10;
    }
    for(int i=n; i>n/2; i--)
        cheie=cheie/10;
}


void citireMsj()                                          //opt 1 si 2
{
    cout<<"Dati mesajul pe care doriti sa-l criptati (maxim 256 de caractere):";
    cin.ignore();
    cin.getline(msj, 257);
}


void citire()                                             //opt 1
{
    cout<<"Dati cheia formata din maxim 4 cifre pe care o doriti pentru a cripta si a decripta mesajul:";
    cin>>cheie;
    palindrom();
    citireMsj();
}


//optional
void afisareMatrice()                                     //opt 1, 2 si 3
{
    cout<<endl<<endl;
    for(int i=0;i<=94;i++)
    {cout<<"Pentru caracterul '"<<char(i+32)<<"'\n";
        for(int j=0;j<=2;j++)
            cout<<c[i][j][0]<<' '<<c[i][j][1]<<endl;
        cout<<endl;
    }
}


void constrMatrice()                                      //opt 1, 2 si 3
{
    //matricea tridimensionala va stoca posibile combinatii de caractere aleatorii ce vor inlocui
    //fiecare caracter din mesaj
    //fiecare caracter va avea 3 combinatii posibile; va fi aleasa una la intamplare
    srand(cheie);
    rand();
    for(int i=0;i<=94;i++)
        for(int j=0;j<=2;j++)
            for(int k=0; k<= 1;k++)
            {
                int l, m;
                bool dif=0;
                do{
                    c[i][j][k]=rand() %94 + 32;
                    if(k==1){for(int l=0;l<=i;l++)        //la fiecare doi pasi verifica daca aceasta
                            for(int m=0;m<=2;m++)     //combinatie e unica in matrice
                                if(  i!=l || j!=m  )
                                {
                                    if (c[i][j][0]!=c[l][m][0] || c[i][j][1]!=c[l][m][1]) dif=1;
                                    else k=0;
                                }
                    }
                    else dif=1;
                }
                while (dif==0);

            }

    //afisareMatrice();

}


void amestecMsj ()                                        //opt 1, 2 si 3
{
    srand(cheie);
    rand();
    char aux;
    int i, j, p;           //p este divizorul pozitiilor
    unsigned int k;
    for(i=1; i<=7; i++)
    {
        p= rand() % 4 +2;
        for(j=strlen(msj)-2; j>=0 ; j--)
            if(j%p==0)             //elementele de pe pozitiile multiple de p
            {              //vor fi puse la sfarsit in ordine inversa aparitiei lor in sir
                aux=msj[j];
                for(k=j; k<=strlen(msj)-2; k++)
                    msj[k]=msj[k+1];
                msj[strlen(msj)-1]=aux;
            }
        //cout<<endl<<p<<':'<<msj;
    }
    //cout<<endl;
}


void utilMatrice()                                        //opt 1, 2 si 3
{
    unsigned int i;
    char aux[257];
    strcpy(aux, msj);
    for(i=0;  i<=strlen(aux)-1;   i++)
    {
        int a=rand()%3;
        msj[2*i]  = c  [int (aux[i])-32]  [a] [0];
        msj[2*i+1]= c  [int (aux[i])-32]  [a] [1];
    }
    //cout<<endl<<msj<<endl;
}


void afisare()                                            //opt 1 si 2
{
    cout<<"\nMesajul criptat este intre paranteze (copiati-l undeva, fara paranteze):\n("<<msj<<")\n";
    dePal();
    cout<<"Cheia dvs. este:\n"<<cheie<<endl;
}


void citireDecr()                                         //opt 3
{
    cout<<"Dati cheia necesara pentru a decripta mesajul:";
    cin>>cheie;
    palindrom();
    cout<<"Dati mesajul criptat pe care doriti sa-l decriptati:";
    cin.ignore();
    cin.getline(msj, 513);
}


void reOrdonare()                                         //opt 3
{
    unsigned int i, j, k ,mem[8];
    char aux;
    srand(cheie);
    rand();
    for(i=1;i<=7;i++)mem[i]=rand()%4+2;         //mem[i] este divizorul pozitiilor, adica p
    for(i=7;i>=1;i--)
    {                                  //+1 pt elementul care era pe pozitia 0
        for(j=0; j<(strlen(msj)-1)/mem[i]+1; j++)
        {
            aux=msj[strlen(msj)-1];
            for(k=strlen(msj)-1; k>=mem[i]*j+1; k--)
                msj[k]=msj[k-1];
            msj[mem[i]*j]=aux;
        }
        //cout<<mem[i]<<':'<<msj<<endl;
    }
}


void decriptare()                                         //opt 3
{
    unsigned int i, j, k;

    for(k=0; k<=strlen(msj)/2-1; k++)
        for(i=0; i<=94; i++)
            for(j=0; j<=2; j++)
                if(msj[2*k]==c[i][j][0] && msj[2*k+1]==c[i][j][1])
                {
                    auxi[k]=char(i+32);
                    //cout<<"\nauxi este:"<<auxi;
                }
    //cout<<"\nAuxi este:"<<auxi;
    strcpy(msj, auxi);
    //cout<<"\nDupa decriptare (inca amestecat):"<<msj<<endl;
}


void afisareDecr()                                        //opt 3
{
    cout<<"\nMesajul original este intre paranteze:\n("<<msj<<")\n";
    dePal();
    cout<<"Cheia este:\n"<<cheie;
}


void ajutor()                                             //opt 4
{
    cout<<" Programul citeste un mesaj pe care il va cripta(codifica) cu ajutorul unei chei.";
    cout<<"\n Numai cel care cunoaste cheia(parola) asociata acelui mesaj neinteligibil il poate decripta(descifra).";
    cout<<"\n\n Optiunile 1 si 2 cripteaza mesajul citit. Prima citeste cheia, iar a doua genereaza cheia automat.";
    cout<<"\n Daca ati ales functia 1, inserati un mesaj(ex: 'Imi place inghetata'), iar apoi cheia ce va fi asociata acelui mesaj.";
    cout<<"\n Vi se va da mesajul criptat. Copiati-l fara paranteze undeva si retineti cheia pentru a-l decripta ulterior.";
    cout<<"\n Daca ati ales functia 2 introduceti doar mesajul. Cheia asociata mesajului dvs va fi generata de calculator.";
    cout<<"\n Optiunea 3 decripteaza un mesaj deja criptat utilizand cheia setata in momentul criptarii.";
    cout<<"\n Daca mesajul criptat nu se potriveste cu cheia, atunci programul va da eroare.";
    cout<<"\n\n Incercati acum una din functiile acestui program:\n\n";
}



int main()
{
    optiune();
    switch (opt) {
        case 1:
            citire();
            constrMatrice();
            amestecMsj();
            utilMatrice();
            amestecMsj();
            afisare();
            break;


        case 2:
            citireMsj();
            cheie=static_cast<unsigned int>(time(0)) %10000;
            cout<<cheie<<endl;
            palindrom();
            constrMatrice();
            amestecMsj();
            utilMatrice();
            amestecMsj();
            afisare();
            break;


        case 3:
            citireDecr();
            constrMatrice();
            reOrdonare();
            decriptare();
            reOrdonare();
            afisareDecr();
            break;


        case 4:
            ajutor();
            repeat=1;
            main();
            return 0;
            break;


        case 0:
            return 0;


        default:
            cout<<"\nNu ati inserat o optiune disponibila. Incercati din nou\n";
            repeat=1;
            main();
            return 0;
            break;
    }

    cout<<"\n\nDaca doriti, mai puteti alege o optiune (1, 2 sau 3).\nAlftel, inchideti programul.\n";
    repeat=1;
    main();
    return 0;
}
