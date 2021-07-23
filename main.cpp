//Ferhat Ali TOKUC 20180702071 CSE 211 TERM PROJECT ALFA V.1
//Code will be more user friendly and clean on Beta phase. This updated will be in Term holiday
#include <iostream>
#include <stdlib.h>
#include <string>
#include<fstream>
#include<cstdlib>
using namespace std;
//LINKED LIST FUNCTIONS
void insertnewline(int x);
void openfilename(string textname);
void insertnewpage();
void writescreen();
void deleten(int deleteline);
void numaralandirma();
void insertntext(int linenumber,string userdata);
void replacentext(int linenumber,string userdata);
void moventom(int firstplace,int secondplace);
void next();
void prev();
void dummynode();
void newfile(string name);
void savefilename(string textname);
void push(int line,int operation,string text);
int linedondur2();
//STACK FUNCTIONS
int stackoperationdondur();
int linedondur();
string textdondur();
int pop();
void printstack();
//LINKED LIST STRUCT
typedef struct n {
    int linenumber;
    string text;
    n*next;
}node;
node*root=NULL;
//STACK STRUCT
typedef struct stacknode
{
    int stackline;// hangi nodeda ?
    int stackoperation;// Ne islem yapti ?
    int stackline2;
    //1-insert n text
    //2-delete n
    //3-move n to m
    //4-replace n text
    //5-next
    //6-prev
    string stacktext;//Yazı neydi?
    stacknode*next;
};
stacknode*iter=NULL;
int pagenumber=1;// suan hangi sayfadayim ?Baslangic 1
int maxpagenumber=1;//Toplam kac sayfa var
int totalnumber=0;// kac satir var
int sayfatutucu=0;//maxpage numberin kontrol case i line sayisina bakiyor
//Bundan sonrası struct fonksiyonları
void undocheck()
{
    int linenumberstack;
    int linenumberstack2;
    int operation;
    //1-insert n text
    //2-delete n
    //3-move n to m
    //4-replace n text
    //5-next
    //6-prev
    string textofstack;

    linenumberstack=linedondur();
    linenumberstack2=linedondur2();
    operation=stackoperationdondur();
    textofstack=textdondur();
    /*
    if(iter==NULL){
        cout<<"//////////////////////error/////////";
    }
    */
    if(operation==1)
    {

        deleten(linenumberstack);
        pop();
    }
    else if(operation==2)
    {
      //
        insertntext(linenumberstack,textofstack);
        pop();

    }
    else if(operation==3)
    {

      moventom(linenumberstack2,linenumberstack);
        pop();

    }
    else if(operation==4)
    {

       replacentext(linenumberstack,textofstack);
        pop();

    }
    else if(operation==5)
    {

        prev();
        pop();
    }
    else if(operation==6)
    {

        next();
        pop();
    }
    else
    {
        cout<<"!!You Reachead Maximum Undo Limit!!"<<endl;
    }
}
void push(int firstline,int secondline,int operation,string text)
{
    if(iter==NULL)
    {
        iter=new stacknode;
        iter->next=NULL;
    }
    iter->stackline=firstline;
    iter->stackoperation=operation;
    iter->stacktext=text;
    iter->stackline2=secondline;
    stacknode *newiter=new stacknode;
    newiter->next=iter;
    iter=newiter;

}

int stackoperationdondur()
{
    if(iter->next==NULL)
    {
        return -1;
    }
    int dondur=iter->next->stackoperation;
    return dondur;
}

int linedondur()
{
    if(iter->next==NULL)
    {
        return -1;
    }
    int dondur=iter->next->stackline;
    return dondur;
}
int linedondur2()
{
    if(iter->next==NULL)
    {
        return -1;
    }
    int dondur=iter->next->stackline2;
    return dondur;
}
string textdondur()
{
    if(iter->next==NULL)
        {
            return "-1";
        }
    string dondur=iter->next->stacktext;
    return dondur;
}

int pop()
{

    if(iter->next==NULL)
    {
            //cout<<"eror 404"<<endl;
            return -1;
    }
    int dondur=iter->next->stackline;
    stacknode*temp=iter;
    iter=iter->next;
    free(temp);
    return dondur;

}
void printstack()
{//For debug test (for future fonctions)

    cout<<"---icerik---"<<endl;
    stacknode*temp=iter->next;
    while(temp!=NULL)
    {
        cout<<temp->stackline<<endl;
        temp=temp->next;
    }
}
string texteeris(int x)
{

    node*iter=root;
    iter=iter->next;
    string eris;
    int skip=(pagenumber-1)*10;
    for(int i=0;i<skip;i++)
    {
        iter=iter->next;
    }
    for(int j=0;j<x-1;j++)
    {
        iter=iter->next;

    }
    eris=iter->text;
    return eris;
}

//Bundan sonrası linked list fonksiyonları
void newfile(string name)
{
        ofstream file;
        file.open(name);

        for(int i=1;i<=211;i++)
        {
            file<<""<<endl;
        }
        file.close();

}
void insertnewline(int x)
{
    node* iter=root;
    while(iter->next!=NULL)
    {
        iter=iter->next;
    }
    for(int i=0;i<x;i++)
    {
        iter->next=new node;
        iter=iter->next;
        iter->linenumber=totalnumber+1;
        iter->text="";
        totalnumber++;
    }
    iter->next=NULL;
    //cout<<"totalnumber"<<totalnumber<<endl;
    if(iter->linenumber%11==0)
    maxpagenumber++;
    numaralandirma();
}

void openfilename(string textname)
{
    ifstream readthefile;
    int choose;
    ifstream testthefile(textname);
    if(!testthefile.is_open())
    {
        cout<<"You create a new file ! Can you sure ?"<<endl<<"1-Yes 2-No"<<endl;
        cin>>choose;
        if(choose==2)
        {
            /*
            ofstream yazmadosyasi;
            yazmadosyasi.open(textname);
            readthefile.close();
            dummynode();
            insertnewpage();
            */
            return;
        }
       else if(choose==1)
        {
            newfile(textname);
        }
       else
        {
            cout<<"Unvalid option"<<endl;
        }

    }
    //else

        dummynode();
        string line;
        readthefile.open(textname);
        // getline(readthefile,line);
        node*iter;
        int sayfasonu=0;
        iter=root;
        while(getline(readthefile,line))
        {
            sayfasonu++;
            sayfatutucu++;
            if(sayfatutucu%11==0)
            {
              maxpagenumber++;
            }
            iter->next=new node;
            iter->next->text=line;
            iter->next->linenumber=totalnumber+1;
            totalnumber++;
            iter=iter->next;
        }
        if(sayfasonu%10==0)
        {
            iter->next=NULL;
        }
        else
        {
            insertnewline(10-(sayfasonu%10));
        }
        readthefile.close();



      numaralandirma();
}
void savefilename(string textname){

    ofstream yazmadosyasi;
    yazmadosyasi.open(textname);
    node*iter=root->next;
    while(iter->next!=NULL)
    {
      yazmadosyasi<<iter->text<<endl;
      iter=iter->next;
    }
     yazmadosyasi.close();
}
void insertnewpage()
{
    node* iter=root;
    //iter=root;
    while(iter->next!=NULL)
    {
        iter=iter->next;
    }
    for(int i=0;i<10;i++)
    {
        iter->next=new node;
        iter=iter->next;
        iter->linenumber=totalnumber+1;
        totalnumber++;
    }
    iter->next=NULL;
    maxpagenumber++;
}
void writescreen()
{
    cout<<"--------------"<<"  Page TOP  "<<pagenumber<<"--------------"<<endl;
    node*iter=root;
    iter=iter->next;
    int skip=(pagenumber-1)*10;
    for(int i=0;i<skip;i++)
    {
        iter=iter->next;
    }
    for(int j=0;j<10;j++)
    {
        if(iter->next==NULL)
        {
            insertnewpage();
        }
        cout<<iter->linenumber<<") ";
        cout<<iter->text<<endl;
        iter=iter->next;

    }
    cout<<"--------------"<<"Page BOTTOM "<<pagenumber<<"--------------"<<endl;
}

void deleten(int deleteline) //  LINKED LIST YAPISI ILE YAP
{
    //Dummy head node sayesinde root silinme sorunları ortadan kalkıyor.
    if(deleteline>=0&&deleteline<=10)
    {
        node*iter=root;
        //iter=iter->next;
        int passtopoint=(pagenumber-1)*10;
        for(int i=0;i<passtopoint;i++)
        {
            iter=iter->next;
        }
        for(int i=0;i<deleteline-1;i++)
        {
            iter=iter->next;
        }
        node*cur=iter->next;
        iter->next=iter->next->next;
        cur->next=NULL;
        delete cur;
        cur=NULL;
        numaralandirma();
    }
    else
    {
        cout<<"Please write a valid line number. Each page contain 10 line."<<endl;
    }

}
void numaralandirma(){
    int numara=0;
    node*iter=root;
    while(iter->next!=NULL)
    {
        iter->linenumber=numara;
        numara++;
        iter=iter->next;
    }
}
void insertntext(int linenumber,string userdata)
{
    if(linenumber>=0&&linenumber<=10)
    {
        int foundlocation=(pagenumber-1)*10;
        node*iter=root;
        //iter=iter->next;
        for(int i=0;i<foundlocation;i++)
        {
            iter=iter->next;
        }
        for(int i=0;i<linenumber-1;i++)
        {
            iter=iter->next;
        }//Bir onceki lineda durdu
        if(iter->next->text=="")
        {
            iter->next->text=userdata;
        }
        else
        {
            node*iter2=new node;
            iter2->next=iter->next;
            iter->next=iter2;
            iter2->text=userdata;
            numaralandirma();// BUG FİXED
        }

    }
    else
    {
        cout<<"Please write a valid line number 1-10!"<<endl;

    }
    numaralandirma();

}
//Replacebak
void replacentext(int linenumber,string userdata)
{
    int foundlocation=(pagenumber-1)*10;
    node*iter=root;
    iter=iter->next;
    for(int i=0;i<foundlocation;i++)
    {
        iter=iter->next;
    }
    for(int i=0;i<linenumber-1;i++)
    {
        iter=iter->next;
    }
    iter->text=userdata;

}
//BU FONKSIYONA BAK SADI EVREN SEKER
void moventom(int firstplace,int secondplace)
{
    int foundlocation=(pagenumber-1)*10;
    node*iter1=root;
    node*iter2=root;
    int fatcount1=0;
    int fatcount2=0;
    string tempstring;
    for(int i=0;i<foundlocation;i++)
    {
        iter1=iter1->next;
    }
    for(int i=0;i<foundlocation;i++)
    {
        iter2=iter2->next;
    }
    for(int i=0;i<firstplace-1;i++)
    {
        iter1=iter1->next;
    }
     for(int i=0;i<secondplace;i++)
    {
        iter2=iter2->next;
    }

    tempstring=iter1->next->text;
    node*deletetemp=iter1->next;
    iter1->next=iter1->next->next;
    deletetemp->next=NULL;
    delete deletetemp;
    node*newnode;
    newnode=new node;
    newnode->text=tempstring;
    newnode->next=iter2->next;
    iter2->next=newnode;

    /*
    node*temp=iter1->next;
    iter1->next=iter1->next->next;
    temp->next=iter2->next;
    iter2->next=temp;
    */
    numaralandirma();

}

void next()
{
    if(pagenumber<=maxpagenumber-1)
    {
        pagenumber++;
    }
    else
    {
        insertnewpage();
        pagenumber++;
    }

}
void prev()
{
    if(pagenumber>=2)
    {
        pagenumber--;
    }
    else
    {
        cout<<"REACHED THE TOP OF THE FILE"<<endl;
    }

}
void dummynode()
{//Derste gordugumuz bir method
    root=new node;
    root->next=NULL;
    root->text="DUMMY NODE";
    root->linenumber=0;

}
void nodedestroyer()
{
    node*iter=root;
    while(iter->next!=NULL)
    {
       iter=iter->next;
    }
    delete iter;
    iter=NULL;

}
int main()
{
    string filename;
    cout<<"Welcome to Ferhat Ali Tokuc's Basic Notepad Program"<<endl;
    //cin>>filename;
    //openfilename(filename);
    int controlwhile=0;
    string userdata;
    int linenumber;
    int linenumber2;
    int functionnumber;
    int undogaranter=0;
    int openfilecheck=0;
    int chosefile=0;
    int savechecker=1;
    int exitchecker=0;
    string stringchecker1;
    string stringchecker2;
    string stringchecker3;
    int    intchecker1;
    int    intchecker2;
    int    intchecker3;
    int firstopencheck=0;

    //cout<<"max page"<<maxpagenumber;
    cout<<"Please first open the file. If you did not you can not any operation!"<<endl;
    cout<<"Please write file name with .txt extension"<<endl;

    while(controlwhile==0)
    {
       // writescreen();
        cout<<"////////MENU\\\\\\\\\\\\"<<endl;
        cout<<"Please write operation - (with spaces and case sensitive!) ex:open test.txt"<<endl;
        cout<<"open \"filename\""<<endl;
        cout<<"insert \"n\" \"text\""<<endl;
        cout<<"delete n"<<endl;
        cout<<"move n m"<<endl;
        cout<<"replace n text"<<endl;
        cout<<"next"<<endl;
        cout<<"prev"<<endl;
        cout<<"save filename"<<endl;
        cout<<"undo"<<endl;
        cout<<"exit the program"<<endl;
        cout<<"/////END OF THE MENU\\\\\\\\\\\\"<<endl;
        cout<<"Your choice : " ;
        //Burada yazıyı function numbera çeviren bir kod gelecek
        cin>>stringchecker1;
        if(stringchecker1=="open")
        {

          //cin>>stringchecker2;,
                 firstopencheck=1;
                cin.ignore();
                getline(cin,filename);
                functionnumber=1;

        }

        else if(stringchecker1=="insert")
        {
            if(firstopencheck==0)
            {
                cout<<"PLEASE FIRST OPEN THE FILE"<<endl;
            }
            else
            {
                cin>>intchecker1;
                if(0<intchecker1&&11>intchecker1)
                {
                    cin.ignore();
                    getline(cin,userdata);
                    functionnumber=2;
                }
                else
                {
                    functionnumber=-1;
                }
            }


        }

        else if(stringchecker1=="delete")
        {
            if(firstopencheck==0)
            {
                cout<<"PLEASE FIRST OPEN THE FILE"<<endl;
            }
            else
            {
                cin>>intchecker1;
                if(0<intchecker1&&11>intchecker1)
                {
                    functionnumber=3;
                }
                else
                {
                    functionnumber=-1;
                }

            }

        }

        else if(stringchecker1=="move")
        {
             if(firstopencheck==0)
            {
                cout<<"PLEASE FIRST OPEN THE FILE"<<endl;
            }
            else
            {

                cin>>intchecker1;
                if(0<intchecker1&&11>intchecker1)
                {   cin>>intchecker2;
                    if(0<intchecker2&&11>intchecker2)
                    {
                        functionnumber=4;
                    }
                    else
                    {
                        functionnumber=-1;
                    }
                }
                else
                {
                    functionnumber=-1;
                }
            }

        }

        else if(stringchecker1=="replace")
        {

             if(firstopencheck==0)
            {
                cout<<"PLEASE FIRST OPEN THE FILE"<<endl;
            }
            else
            {

                cin>>intchecker1;
                if(0<intchecker1&&11>intchecker1)
                {

                    cin.ignore();
                    getline(cin,stringchecker2);
                    if(0<intchecker1&&11>intchecker1)
                    {

                        functionnumber=5;
                    }


                }
                else
                {
                    functionnumber=-1;
                }

            }

        }

        else if(stringchecker1=="next")
        {
             if(firstopencheck==0)
            {
                cout<<"PLEASE FIRST OPEN THE FILE"<<endl;
            }
            else
            {
                functionnumber=6;
            }

        }
        else if(stringchecker1=="prev")
        {
            if(firstopencheck==0)
            {
                cout<<"PLEASE FIRST OPEN THE FILE"<<endl;
            }
            else
            {
                 functionnumber=7;
            }

        }
        else if(stringchecker1=="save")
        {
            if(firstopencheck==0)
            {
                cout<<"PLEASE FIRST OPEN THE FILE"<<endl;
            }
            else
            {
            cin>>stringchecker2;
            functionnumber=8;
            }

        }
        else if(stringchecker1=="undo")
        {
             if(firstopencheck==0)
            {
                cout<<"PLEASE FIRST OPEN THE FILE"<<endl;
            }
            else
            {
                functionnumber=9;
            }

        }
        else if(stringchecker1=="exit")
        {
            if(firstopencheck==0)
            {
                cout<<"PLEASE FIRST OPEN THE FILE"<<endl;
            }
            else
            {
                cin>>stringchecker2;
                if(stringchecker2=="the")
                {
                        cin>>stringchecker3;
                        if(stringchecker3=="program")
                        {
                            functionnumber=10;
                        }
                    else
                    {
                        functionnumber=-1;
                    }
                }
                else
                {
                    functionnumber=-1;
                }
            }


        }
        else
        {//Default eror

            functionnumber=211; // respect to cse 211 :)
        }
        switch(functionnumber)
        {
                case 1:
                    //Node deleter ekle
                        if(openfilecheck!=0)
                        {
                            if(savechecker==1)
                            {
                                cout<<"You are trying to open a new file without saving the file. Your changes could not be saved! "<<endl;
                                cout<<endl<<"1-continue"<<"2-Save it after open file"<<endl;
                                cin>>chosefile;
                                if(chosefile==1)
                                {
                                    nodedestroyer();
                                    //dummynode();
                                    cout<<"Please write file name with .txt extension"<<endl;
                                    cin>>filename;
                                    openfilename(filename);
                                    openfilecheck=1;
                                    writescreen();
                                    savechecker=1;
                                    break;
                                }
                                else if(chosefile==2)
                                {
                                    savefilename(filename);
                                    nodedestroyer();
                                    //dummynode();
                                    cout<<"Please write file name with .txt extension"<<endl;
                                    cin>>filename;
                                    openfilename(filename);
                                    openfilecheck=1;
                                    writescreen();
                                    savechecker=1;
                                    break;
                                }
                                else
                                {
                                    cout<<"You push unvalid option"<<endl;
                                    while(chosefile==1||chosefile==2)
                                    {
                                        cout<<"You are trying to open a new file without saving the file. Your changes could not be saved! You can loose important data "<<endl;
                                        cout<<"1-continue"<<"2-Save it after open file"<<endl;
                                        cin>>chosefile;
                                        if(chosefile==1)
                                        {
                                            nodedestroyer();
                                            //dummynode();
                                            cout<<"Please write file name with .txt extension"<<endl;
                                            cin>>filename;
                                            openfilename(filename);
                                            openfilecheck=1;
                                            writescreen();
                                            savechecker=1;
                                            break;
                                        }
                                        else if(chosefile==2)
                                        {
                                            savefilename(filename);
                                            nodedestroyer();
                                           // dummynode();
                                            cout<<"Please write file name with .txt extension"<<endl;
                                            cin>>filename;
                                            openfilename(filename);
                                            openfilecheck=1;
                                            writescreen();
                                            savechecker=1;
                                            break;
                                        }


                                    }

                                }

                            }

                        }
                        else
                        {
                       // dummynode();
                        openfilename(filename);
                        openfilecheck=1;
                        writescreen();
                        savechecker=1;
                        break;

                        }
                case 2:
                        //BURASI SORUN CIKARABİLİR
                        insertntext(intchecker1,userdata);
                        push(intchecker1,0,1,userdata);
                        writescreen();
                        savechecker=1;
                        break;
                case 3:
                        push(intchecker1,0,2,texteeris(intchecker1));
                        deleten(intchecker1);
                        writescreen();
                        savechecker=1;
                        break;
                case 4:

                        if(intchecker1>intchecker2)
                        {
                        //push(intchecker1,intchecker2,3,"");
                        push(intchecker1,intchecker2,3,"");
                        // Normalde int checkerlar yer degistirecekti kazara bu methodu kesfettim.
                        moventom( intchecker1,intchecker2-1);
                        writescreen();
                        savechecker=1;
                        break;
                        }
                        else if(intchecker1<intchecker2)
                        {
                        push(intchecker1-1,intchecker2,3,"");
                        // Normalde int checkerlar yer degistirecekti kazara bu methodu kesfettim.
                        moventom( intchecker1, intchecker2);
                        writescreen();
                        savechecker=1;
                        break;
                        }
                        else
                        {//Nothing changes!
                         writescreen();
                         break;
                        }



                case 5:
                        push(intchecker1,0,4,texteeris(intchecker1));
                        replacentext( intchecker1, stringchecker2);
                        writescreen();
                        savechecker=1;
                        break;

                case 6:
                        next();
                        push(0,0,5,"");
                        writescreen();
                        savechecker=1;
                        break;

                case 7:
                        prev();
                        push(0,0,6,"");
                        writescreen();
                        savechecker=1;
                        break;
                case 8:
                        savefilename(stringchecker2);
                        writescreen();
                        savechecker=0;
                        break;
                case 9:
                        if(undogaranter==1)
                        {
                         undocheck();
                         writescreen();
                         savechecker=1;
                         break;
                        }
                        else
                        {
                            cout<<"You reached the Undo Limit"<<endl;
                        }
                        break;
                case 10:
                    if(savechecker==0)
                    {
                         controlwhile =1;
                         break;
                    }
                    else if(savechecker==1)
                    {
                        cout<<"Some changes not saved!."<<"1-Continue"<<endl<<"2-Save and close"<<endl;
                        cin>>exitchecker;
                        if(exitchecker==1)
                        {
                            controlwhile =1;
                            break;
                        }
                        else if(exitchecker==2)
                        {
                            savefilename(filename);
                            controlwhile =1;
                            break;

                        }
                    }

                    else
                    {
                            while(savechecker==1||savechecker==2)
                            {
                                 cout<<"Some changes not saved!."<<"1-Continue"<<endl<<"2-Save and close"<<endl;
                                cin>>exitchecker;
                                if(exitchecker==1)
                                {
                                    controlwhile =1;
                                    break;
                                }
                                else if(exitchecker==2)
                                {
                                    savefilename(filename);
                                    controlwhile =1;
                                    break;

                                }

                            }
                    }
                    //SAVE CONTROL AT BURAYA
                    break;
                case 211:
                     cout<<"Unvalid choose!  Please be careful"<<endl;
                     writescreen();

                    break;
                case -1:
                    cout<<"Unvalid choose!  Please be careful"<<endl;
                    writescreen();

                    break;

        }
            undogaranter=1;

    }

}







