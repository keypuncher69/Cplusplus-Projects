//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// HEADER FILES USED IN PROJECT:
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<fstream.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<dos.h>
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// CONSTANTS USED:
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

const float TAX=0.03;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// CLASSES USED:
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class product
{
	int pno;
	char name[50];
	float price,stk,dis;
	public:
	void create_product()
	{
		cout<<"\n\nPlease Enter The Product No. of The Product: ";
		cin>>pno;
		cout<<"\nPlease Enter The Name of The Product: ";
		gets(name);
		cout<<"\nPlease Enter The Price of The Product: ";
		cin>>price;
		cout<<"\nPlease Enter the stock of the Product:";
		cin>>stk;
		cout<<"\nPlease Enter The Discount (%): ";
		cin>>dis;
	}
	void show_product()
	{
		cout<<"\n\nThe Product No: "<<pno;
		cout<<"\nThe Name of The Product: "<<name;
		cout<<"\nThe Price of The Product: "<<price;
		cout<<"\nThe Stock of the Product:"<<stk;
		cout<<"\nDiscount: "<<dis;
	}
	int retpno()
	{
		return pno;
	}
	float retprice()
	{
		return price;
	}
	char* retname()
	{
		return name;
	}
	float retdis()
	{
		return dis;
	}
	float retstk()
	{
		return stk;
	}
};
class customer: public product  //INHERITING THE MAJOR CLASS
{
	char c_phone[9];
	char c_name[50];
	char c_address[100];
	public:
	void getdata()
	{
		cout<<"\n Enter your Phone no: ";
		gets(c_phone);
		cout<<"\n Enter your Name: ";
		gets(c_name);
		cout<<"\n Enter Address: ";
		gets(c_address);
	}
	void putdata()
	{
		cout<<"\n Your Name is: "<<c_name;
		cout<<"\n Your Phone number is: "<<c_phone;
		cout<<"\n Your Address is: "<<c_address;
	}
	char *retc_phone()
	{
		return c_phone;
	}

	char *retc_name()
	{
		return c_name;
	}

	char *retc_address()
	{
		return c_address;
	}
};

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FUNCTION DECLARATIONS:
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void write_product();
void display_all();
void display_sp(long);
void modify_product();
void delete_product();
void login();
void p_table();
void reg();
void admin_menu();
void user_menu();
void the_main();
float calc(float,float);
void bill();
void c_table();
void update_c();
void del_c();
void load();
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FUNCTION TO WRITE TO FILE:
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void write_product()
{
	product pr;
	ofstream fout;
	fout.open("Products.dat",ios::binary|ios::app);
	pr.create_product();
	fout.write((char*)&pr,sizeof(pr));
	fout.close();
	cout<<"\n\nThe Product Has Been Created!! ";
	getch();
	admin_menu();
}

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FUNCTION TO READ ALL RECORDS FROM FILE:
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void display_all()
{
	clrscr();
	product pr;
	ifstream fin;
	cout<<"\n\n\n\t\tDISPLAY ALL RECORDS \n";
	cout<<"\t\t_____________________"<<endl;
	fin.open("Products.dat",ios::binary|ios::in);
	while(fin.read((char*)&pr,sizeof(pr)))
	{
		pr.show_product();
		cout<<"\n\n====================================\n";
		getch();
	}
	fin.close();
	getch();
	admin_menu();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FUNCTION TO READ SPECIFIC RECORD FROM FILE:
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void display_sp()
{
	clrscr();
	product pr;
	ifstream fin;
	int flag=0,n;
	cout<<"\n Enter the product to search: ";
	cin>>n;
	fin.open("Products.dat",ios::binary|ios::in);
	while(fin.read((char*)&pr,sizeof(pr)))
	if(pr.retpno()==n)
	{
		cout<<"\n";
		pr.show_product();
		flag=1;
	}
	fin.close();
	if(flag==0)
	cout<<"\n RECORD DOES NOT EXIST...";
	getch();
	admin_menu();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FUNCTION TO MODIFY RECORD OF A FILE:
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void modify_product()
{
	clrscr();
	int no;
	cout<<"\n\n\tTO MODIFY: ";
	cout<<"\n\t____________";
	cout<<"\n\n\tPlease Enter The Product No:";
	cin>>no;
	int f=0;
	cout<<"\n";
	ifstream fin("Products.dat",ios::binary);
	ofstream fout("Temp.dat",ios::binary);
	product pr;
	while(fin.read((char*)&pr,sizeof(pr)))
	{
		if(pr.retpno()==no)
		{
			pr.show_product();
			cout<<"\n\n Enter the details of new product: ";
			pr.create_product();
			f=1;
		}
		fout.write((char*)&pr,sizeof(pr));
	}
	fin.close();
	fout.close();
	remove("Products.dat");
	rename("Temp.dat","Products.dat");
	if(f==0)
		cout<<"Product not found...";
	else
		cout<<"Record updated!";
	getch();
	admin_menu();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FUNCTION TO DELETE RECORD OF FILE:
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void delete_product()
{
	clrscr();
	int no;
	cout<<"\n\n\tTO DELETE: ";
	cout<<"\n\t____________";
	cout<<"\n\n\tPlease Enter The Product No:";
	cin>>no;
	int f=0;
	cout<<"\n";
	ifstream fin("Products.dat",ios::binary);
	ofstream fout("Temp.dat",ios::binary);
	product pr;
	while(fin.read((char*)&pr,sizeof(pr)))
	{
		if(pr.retpno()!=no)
		{
			fout.write((char*)&pr,sizeof(pr));
		}
		else
		f=1;
	}
	fin.close();
	fout.close();
	remove("Products.dat");
	rename("Temp.dat","Products.dat");
	if(f==0)
		cout<<"Product not found...";
	else
		cout<<"Record deleted!";
	getch();
	admin_menu();
}
//+++++++++++++++++++++++++++++++++++++++++++++
// FUNCTION FOR CUSTOMER LOGIN:
//+++++++++++++++++++++++++++++++++++++++++++++
void login()
{
	customer c;
	char p[9];
	int f=0;
	ifstream fin;
	fin.open("Members.dat",ios::binary|ios::in);
	cout<<"\n Enter your phone number (8 digits): ";
	gets(p);
	load();
	while(fin.read((char*)&c,sizeof(c)))
	{
		if(strcmp(p,c.retc_phone())==0)
		{
			clrscr();
			cout<<"\n\n\n\t\t\t\t WELCOME "<<c.retc_name()<<"\n\t\t\t\t ________________ "<<"\n";
			c.putdata();
			cout<<"\n\n \t\t Go shopping (y/n)? ";
			char x;
			cin>>x;
			if (x=='y'||x=='Y')
			bill();
			else
			if(x=='n'||x=='N')
			user_menu();
			f=1;
			break;
		}
	}
	if(f==0)
		cout<<"\n\n Sorry, you are not a member! ";
	cout<<"\n Do you want to register (y/n)? ";
	char z;
	cin>>z;
	if(z=='y'||z=='Y')
	reg();
	fin.close();
}
//+++++++++++++++++++++++++++++++++++++++++++++
// FUNCTION FOR REGISTERING CUSTOMER:
//+++++++++++++++++++++++++++++++++++++++++++++
void reg()
{
	   customer c;
	   ofstream fout;
	   fout.open("Members.dat",ios::binary|ios::out|ios::app);
	   clrscr();
	   cout<<"\n \t\t\t\t WELCOME TO SUPERMART!";
	   cout<<"\n \t\t\t\t _______________________";
	   cout<<"\n We would like to get some details about you! \n";
	   c.getdata();
	   fout.write((char*)&c,sizeof(c));
	   fout.close();
	   load();
	   cout<<"\n\n \t\t Success !";
	   char o;
	   cout<<"\n\n \t\t\t\t Shop now (y/n)? ";
	   cin>>o;
	   if(o=='y'||o=='Y')
		bill();
	   if(o=='n'||o=='N')
		user_menu();
	   else
	   {
		cout<<"Invalid choice";
		user_menu();
	   }
}
//+++++++++++++++++++++++++++++++++++++++++++++
// FUNCTION TO UPDATE CUSTIOMERS :
//+++++++++++++++++++++++++++++++++++++++++++++
void update_c()
{
	customer c;
	char p[9];
	int found=0;
	ifstream fin("Members.dat",ios::binary);
	ofstream fout("Temp.dat",ios::binary);
	clrscr();
	cout<<"\n\n\tTO UPDATE: ";
	cout<<"\n\t____________";
	cout<<"\n\n\tPlease Enter Your Phone No:";
	cin>>p;
	cout<<"\n";
	while(fin.read((char*)&c,sizeof(c)))
	{
		if(strcmp(c.retc_phone(),p)==0)
		{
			c.putdata();
			cout<<"\n\n Enter the new details : ";
			c.getdata();
			found=1;
		}
		fout.write((char*)&c,sizeof(c));
	}
	fin.close();
	fout.close();
	remove("Members.dat");
	rename("Temp.dat","Members.dat");
	if(found==0)
		cout<<"Member not found...";
	else
		cout<<"Record updated!";
	getch();
	user_menu();
}
//+++++++++++++++++++++++++++++++++++++++++++++
// FUNCTION TO DELETE CUSTOMER:
//+++++++++++++++++++++++++++++++++++++++++++++
void del_c()
{
	customer c;
	char p[9];
	int found=0;
	ifstream fin("Members.dat",ios::binary);
	ofstream fout("Temp.dat",ios::binary);
	clrscr();
	cout<<"\n\n\tTO DEACTIVATE: ";
	cout<<"\n\t____________";
	cout<<"\n\n\tPlease Enter Your Phone No:";
	cin>>p;
	cout<<"\n";
	while(fin.read((char*)&c,sizeof(c)))
	{
		if(strcmp(c.retc_phone(),p)!=0)
		fout.write((char*)&c,sizeof(c));
		else
		found=1;
	}
	fin.close();
	fout.close();
	remove("Members.dat");
	rename("Temp.dat","Members.dat");
	if(found==0)
		cout<<"Member not found...";
	else
		cout<<"Record Deleted!";
	getch();
	user_menu();
}
//+++++++++++++++++++++++++++++++++++++++++++++
// FUNCTION TO CALCULATE PRICE:
//+++++++++++++++++++++++++++++++++++++++++++++
float calc(float p,float dis)
{
	float d=dis*p;
	float t=TAX*d;
	float tot=p-(d+t);
	return tot;
}
//+++++++++++++++++++++++++++++++++++++++++++++
// FUNCTION TO PRODUCE BILL:
//+++++++++++++++++++++++++++++++++++++++++++++

void bill()
{
	fstream fp;
	ifstream fin;
	product pr;
	int p;
	char ch;
	float add=0.0;
	clrscr();
	fin.open("Products.dat",ios::binary|ios::in);
	cout<<"\n\n\t\tPRODUCT MENU\n";
	cout<<"\t\t_______________"<<endl;
	cout<<"\n====================================================\n";
	cout<<"P.NO.\t\tNAME\t\tPRICE\n";
	cout<<"====================================================\n";
	while(fin.read((char*)&pr,sizeof(pr)))
		cout<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
	fin.close();
	fin.open("Products.dat",ios::binary|ios::in);
	fp.open("Cart.dat",ios::binary|ios::out);
	while(p!=0)
	{
		cout<<"\n Choose product:(0 if u have done shopping!) ";
		cin>>p;
		while(fin.read((char*)&pr,sizeof(pr)))
		if(pr.retpno()==p)
		{
			fp.write((char*)&pr,sizeof(pr));
			break;
		}
		fin.seekg(0);
	}
	fin.close();
	fp.close();
	cout<<"\n Generate Bill : press any key to continue... ";
	getch();
	clrscr();
	fp.open("Cart.dat",ios::binary|ios::in);
	cout<<"\n\n\t\t\t\t BILL \n";
	cout<<"\t\t\t\t______ \n\n";
	cout<<"================================================================================\n";
	cout<<"P.NO.\t\tNAME\t\t\t\tPRICE\t\tDISCOUNT\n";
	cout<<"================================================================================";
	while(fp.read((char*)&pr,sizeof(pr)))
	{
		cout<<"\n"<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<"\t\t"<<pr.retprice()<<"\t\t"<<pr.retdis()<<endl;
		add+=calc(pr.retprice(),pr.retdis());
	}
	cout<<"\n\n Tax on all products is 3% \n\n ";
	cout<<"\n\t\t***************************************************";
	cout<<"\n\t\t\t\t YOUR BILL = "<<add<<"\n";
	cout<<"\t\t***************************************************\n";
	getch();
	fp.close();
	exit(0);
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FUNCTION TO DISPLAY ALL PRODUCTS PRICE LIST:
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void p_table()
{
	product pr;
	ifstream fin;
	clrscr();
	fin.open("Products.dat",ios::binary|ios::in);
	cout<<"\n\n\t\tPRODUCT MENU\n";
	cout<<"\t\t_______________"<<endl;
	cout<<"\n============================================================\n";
	cout<<"\tP.NO.\t\tNAME\t\tPRICE\n";
	cout<<"============================================================\n";
	while(fin.read((char*)&pr,sizeof(pr)))
		cout<<"\t"<<pr.retpno()<<"\t\t"<<pr.retname()<<"\t\t"<<pr.retprice()<<endl;
	fin.close();
	getch();
	admin_menu();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// FUNCTION TO DISPLAY ALL CUSTOMER DETAILS:
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void c_table()
{
	clrscr();
	ifstream fin;
	customer c;
	fin.open("Members.dat",ios::binary|ios::in);
	cout<<"\n\n\t\tCUSTOMER'S RECORDS\n";
	cout<<"\t\t__________________"<<endl;
	cout<<"\n============================================================\n";
	cout<<"\tPHONE.NO.\t\tNAME\t\tADDRESS\n";
	cout<<"============================================================\n";
	while(fin.read((char*)&c,sizeof(c)))
		cout<<"\t"<<c.retc_phone()<<"\t\t"<<c.retc_name()<<"\t\t"<<c.retc_address()<<endl;
	fin.close();
	getch();
	admin_menu();
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// ADMINSTRATOR MENU FUNCTION:
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void admin_menu()
{
	clrscr();
	int ch2;
	cout<<"\n\n\n\tADMIN MENU";
	cout<<"\n\t___________";
	cout<<"\n\n\t1.CREATE PRODUCT";
	cout<<"\n\n\t2.DISPLAY ALL PRODUCTS";
	cout<<"\n\n\t3.QUERY ";
	cout<<"\n\n\t4.MODIFY PRODUCT";
	cout<<"\n\n\t5.DELETE PRODUCT";
	cout<<"\n\n\t6.VIEW PRODUCT MENU";
	cout<<"\n\n\t7.VIEW CUSTOMER DETAILS";
	cout<<"\n\n\t8.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-8): ";
	cin>>ch2;
	switch(ch2)
	{
	case 1: clrscr();
		write_product();
		break;

	case 2: display_all();
		break;

	case 3: display_sp();
		break;

	case 4: modify_product();
		break;

	case 5: delete_product();
		break;

	case 6: p_table();
		getch();
		break;

	case 7: c_table();
		getch();
		break;

	case 8:	the_main();
		break;

	default:cout<<"\a";
	}
   getch();
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// USER MENU FUNCTION:
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void user_menu()
{
	clrscr();
	long ch;
	do
	{
		clrscr();
		cout<<"\n\n\n\tCUSTOMER MENU";
		cout<<"\n\t_______________ ";
		cout<<"\n\n\t1.LOGIN";
		cout<<"\n\n\t2.REGISTER";
		cout<<"\n\n\t3.UPDATE YOUR INFO";
		cout<<"\n\n\t4.DEACTIVATE MEMBERSHIP";
		cout<<"\n\n\t5.BACK TO MAIN MENU";
		cout<<"\n\n\tPlease Enter Your Choice (1-5): ";
		cin>>ch;
		switch(ch)
		{
			case 1: login();
				break;
			case 2: reg();
				break;
			case 3: update_c();
				break;
			case 4: del_c();
				break;
			case 5: the_main();
				break;
			default: cout<<"INVALID CHOICE ENTERED!!\n";
		}
	}
	while(ch!=3);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// PASSWORD FUNCTION
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void password(char ar[],int max)
{
	char ch;
	int x=0;
	while(1)
	{
		ch=getch();
		if(ch==13)
		{
			ar[x]='\0';
			break;
		}
		if(ch==8 && x!=0)
		{
			cout<<"\b \b";
			if(x<=max && x>0)
			x--;
		}
		else if(x<max && ch!=8)
		{
			cout<<"*";
			ar[x]=ch;
			x++;
		}
	}
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// LOAD FUNCTION:
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void load()
{
	int i;
	char ch=177,ce=178;
	textcolor(WHITE);
	clrscr();
	gotoxy(20,9);
	cout<<"LOADING...";
	gotoxy(20,10);
	for(i=0;i<26;i++)
		cout<<ch;
	gotoxy(20,10);
	for(i=0;i<26;i++)
	{
		delay(100);
		cout<<ce;
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// MAIN PAGE FUNCTION:
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void the_main()
{
	int ch;
	int pass;
	do
	{
		clrscr();
		cout<<"\n\t\t Welcome To Supermart Billing System Application";
		cout<<"\n \t\t **********************************************";
		cout<<"\n\n\n\n\n\tMAIN MENU";
		cout<<"\n\t____________ ";
		cout<<"\n\n\t01. CUSTOMER";
		cout<<"\n\n\t02. ADMINISTRATOR";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-3): ";
		cin>>ch;
		switch(ch)
		{
			case 1:
			clrscr();
			user_menu();
			getch();
			break;

			case 2:
			clrscr();
			cout<<"\n \n \n \n \t \t Enter the password: ";
			char ps[5];
			password(ps,4);
			if(strcmpi(ps,"1010")==0)
			admin_menu();
			else
			{
				cout<<"\n\n\t\t Incorrect passcode!!!";
				getch();
			}
			break;

			case 3:
			exit(0);

			default:
			cout<<"\a";
		}
	}
	while(ch!=3);
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// THE MAIN FUNCTION:
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
void main()
{
   clrscr();
   load();
   the_main();
   getch();
}
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// END OF PROJECT
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++


