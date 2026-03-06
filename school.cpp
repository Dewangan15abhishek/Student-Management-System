#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

class Student
{
    int addmissionnumber;
    char name[50];
    char dob[20];
    char course[50];
    float fees;
    public:
        void add_data(int adno)
        {   
            addmissionnumber=adno+1;
            cout<<"\n\tADDMISSION NUMBER "<<addmissionnumber;
        
            cout<<"\n\tENTER NAME ";
            fflush(stdin);
            cin.getline(name,50);
            cout<<"\n\tENTER DATE OF BIRTH ";
            fflush(stdin);
            cin.getline(dob,20);
            cout<<"\n\tENTER COURSE ";
            fflush(stdin);
            cin.getline(course,50);
            cout<<"\n\tENTER FEES ";
            cin>>fees; 
          
        }

        void show_data()
        {
            cout<<"\n\tADDMISSION NUMBER \t"<<addmissionnumber;
            cout<<"\n\tNAME \t\t\t";
            cout.write(name,strlen(name));
            cout<<"\n\tDATE OF BIRTH \t\t";
            cout.write(dob,strlen(dob));
            cout<<"\n\tCOURSE \t\t\t"<<course;
            cout<<"\n\tFEES \t\t\t"<<fees<<endl;
         
        }

        int returnadno()
        {
            return addmissionnumber;
        }
};


void add_rec()
{
    Student s1,s2;
    fstream fout;
    int recsize =sizeof(s1);
    int adno;
    int flag=0;
    fout.open("a1",ios::in);
    if(!fout)
    {
        cout<<"\n\t FILE NOT OPEN \n\t";
        system("pause");
        return;
    }
 
    fout.seekg(0,ios::end);
    int x=(fout.tellg()/recsize);
    fout.seekg((-1*recsize),ios::end);
    fout.read((char*)&s1,recsize);
    if( x<=0)
        adno=0;
    else
        adno=s1.returnadno();
    
    fout.close();

    system("cls");
    cout<<"\n\t\tADD NEW MENU \n\t";
    cout<<"\n\tPREVIOUS ADDMISSION NUMBER "<<adno<<endl;
    s2.add_data(adno);

    fout.open("a1",ios::out | ios::app);
    if(!fout)
    {
        cout<<"\n\tFILE NOT OPEN \n\t";
        system("pause");
        return;
    }
    fout.write((char*)&s2,recsize);

    cout<<"\n\tRECORD ADDED \n\t";
    system("pause");
    fout.close();
}

void delete_all()
{
    fstream fout,temp;
    system("cls");
    fout.open("a1",ios::in);
    if(!fout)
    {
        cout<<"\n\tFILE NOT OPEN\n\t";
        system("pause");
        return;
    }

    temp.open("temp",ios::app);
    if(!temp)
    {
        cout<<"\n\tFILW NOT OPEN\n\t";
        system("pause");
        return;
    }
    fout.close();
    temp.close();

    char confirm;
    cout<<"\n\tDO YOU WANT TO DELETE ALL DATA ";
    fflush(stdin);
    cin.get(confirm);
    if(confirm=='y' || confirm=='Y')
    {
        remove("a1");
        rename("temp","a1");
        cout<<"\n\tALL RECORD DELETED \n\t";
    }
    else
    {
        cout<<"\n\t";
    }
    system("pause");
}

void delete_rec()
{
    Student s1;
    fstream fout,temp;
    int adno,flag=0;
    int recsize=sizeof(Student);
    system("cls");
    cout<<"\n\tDELETE RECORD\n\t";
    fout.open("a1",ios::in);
    if(!fout)
    {
        cout<<"\n\tFILE NOT OPEN\n\t";
        system("pause");
        return;
    }

    temp.open("temp",ios::app);
    if(!temp)
    {
        cout<<"\n\tFILW NOT OPEN\n\t";
        system("pause");
        return;
    }

    cout<<"\n\tENTER ADDMISSION NUMBER ";
    cin>>adno;

    while(fout.read((char*)&s1,recsize))
    {
        if(s1.returnadno()==adno)
        {
            s1.show_data();
            char confirm;
            cout<<"\n\tDO YOU WANT TO DELETE THIS DATA ";
            fflush(stdin);
            cin.get(confirm);
            if(confirm=='Y' || confirm=='y')
            {
                fout.read((char*)&s1,recsize);
                cout<<"\n\tRECORD DELETED\n\t";
                flag=1;
                if(!fout)
                break;
            }
            flag=1;
        }
        temp.write((char*)&s1,recsize);
    }
    fout.close();
    temp.close();

    remove("a1");
    rename("temp","a1");

    if(flag==0)
    {
        cout<<"\n\tNO SUCH RECORD FOUND \n\t";
    }
    system("pause");
}

void modify_rec()
{
    Student s1;
    fstream fout;
    int adno,flag=0;
    int recsize=sizeof(Student);
    system("cls");
    fout.open("a1",ios::in|ios::out);
    if(!fout)
    {
        cout<<"\n\tFILE NOT OPEN \n\t";
        system("pause");
        return;
    }

    fout.seekg(ios::beg);
    int pos=fout.tellg();
    cout<<"\n\tENTER ADDMISSION NUMBER ";
    cin>>adno;
    fout.read((char*)&s1,recsize);

    while(fout)
    {
        if(adno==s1.returnadno())
        {
            system("cls");
            s1.show_data();
            int tno=s1.returnadno()-1;
            Student s2;
            cout<<"\n\n\n\tENTER NEW DATA \n\n\t";
            s2.add_data(tno);
            char confirm;
            cout<<"\n\tARE YOU SURE ";
            fflush(stdin);
            cin>>confirm;
            if(confirm=='y'||confirm=='Y')
            {
                fout.seekg(pos);
                fout.write((char*)&s2,recsize);
                cout<<"\n\tRECORD CHANGED\n\t";
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            cout<<"\n\tNO RECORD FOUND\n\t";
        }

        pos=fout.tellg();
        fout.read((char*)&s1,recsize);
    }
    fout.close();
    system("pause");
}

void search_rec()
{
    Student s1;
    fstream fout;
    int adno,flag=0;
    int recsize=sizeof(Student);
    fout.open("a1",ios::in | ios::out);
    if(!fout)
    {
        cout<<"\n\tFILE NOT FOUND \n\t";
        system("pause");
        return;
    }
    system("cls");
    cout<<"\n\tENTER ADDMISSION NUMBER ";
    cin>>adno;

    while(fout.read((char*)&s1,recsize))
    {
        if(s1.returnadno()==adno)
        {
            s1.show_data();
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        cout<<"\n\tNO RECORD FOUND\n\t";
    }
    cout<<"\n\t";
    system("pause");
    fout.close();
}

void show_all()
{
    Student s1;
    fstream fout;
   
    int recsize=sizeof(Student);
    int count=0;
    system("cls");
    fout.open("a1",ios::in);
    if(!fout)
    {
        cout<<"\n\tFILE NOT OPEN\n\t";
        system("pause");
        return;
    }
    fout.seekg(0);
    fout.read((char*)&s1,recsize);
    while(fout)
    {
        s1.show_data();
        count++;
        fout.read((char*)&s1,recsize);
        cout<<"\n\n";
    }
    
    cout<<"\n\tEND OF FILE \n";
    cout<<"\n\tNUMBER OF RECORDS ARE "<<count<<"\n\t";
    system("pause");
    fout.close();
}


int main()
{
    int c;
    fstream fout;
    do
    {
        system("cls");
        cout<<"\n\t 1. ADD NEW ";
        cout<<"\n\t 2. DELETE ANY ";
        cout<<"\n\t 3. MODIFY ANY ";
        cout<<"\n\t 4. SEARCH ANY ";
        cout<<"\n\t 5. SHOW ALL ";
        cout<<"\n\t 6. DELETE ALL ";
        cout<<"\n\t 7. EXIT ";
        cout<<"\n\t ENTER CHOICE ";
        fflush(stdin);
        cin>>c;

        fout.open("a1",ios:: in | ios::out |ios::app);
        fout.close();
    
        switch(c)
        {
        case 1:
            add_rec();
            break;
        case 2:
            delete_rec();
            break;
        case 3:
            modify_rec();
            break;
        case 4:
            search_rec();
            break;
        case 5:
            show_all();
            break;
        case 6:
            delete_all();
            break;
        case 7 :
            break;
        }
    }while(c!=7);
    
}