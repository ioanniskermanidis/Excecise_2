#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct contact
{
	char name[100];
	char address[100];
	char gender[8];
	char email[100];
	char phone[10];
	int deleted;
};

typedef struct contact contact;

void printTitle();

void printContact(contact entry);
int countContacts(char* filename);
void readContacts(char* filename,contact* contacts);
contact* loadContacts(char* filename);
void saveTxt(char* filename,contact* contacts, int contactCounter);
//����������� ��� ����������� ��������� ��� ��� ��������

void listContacts(contact* contacts, int contactCounter);
void searchContact(contact* contacts, int contactCounter);
void updateContact(contact* contacts, int contactCounter);
void deleteContact(contact* contacts, int contactCounter);
void exitEnv(char* filename,contact* contacts, int contactCounter);
contact* addContact(contact* contacts, int* ptr_contactCounter);

int main()
{
	
	char filename[]="contacts.txt";
	contact* contacts=loadContacts(filename);
	int contactCounter= countContacts(filename);
	while(1)
	{
	printTitle();
	printf(" 1.Add New Contact\n 2.Search Contact\n 3.Update Contact\n 4.Delete Contact\n 5.List Contacts\n 6.Exit\n ");
	char choice;
	choice=getch();
	switch(choice){
		case '1':
			contacts = addContact(contacts, &contactCounter);
			saveTxt(filename,contacts,contactCounter);
			break;
		case '2':
			searchContact(contacts,contactCounter);
			break;
		case '3':
			updateContact(contacts,contactCounter);
			saveTxt(filename,contacts,contactCounter);
			break;
		case '4':
			deleteContact(contacts, contactCounter);
			saveTxt(filename,contacts,contactCounter);
			break;	
		case '5':
			listContacts(contacts, contactCounter);
			break;
		case '6':
			exitEnv(filename, contacts, contactCounter);
			break;
	}
	printf("\n Press m for menu: ");
	while(1){
		choice = getch();
		if(choice=='m') break;
	}
	
	}
	
	return 0;
}


//Functions

void printTitle(){
	system("cls");
	printf("--------------------------------------------------------------------------\n");
	printf("|                         CONTACTS MANAGEMENT                            |\n");
	printf("--------------------------------------------------------------------------\n\n");
	
}

void printContact(contact entry)
{
	puts("----------------------------------");
	printf(" Name: %s\n Address: %s\n Gender: %s\n Email: %s\n Phone: %s\n\n", entry.name, entry.address, entry.gender, entry.email, entry.phone);	
	puts("----------------------------------");
}
int countContacts(char* filename)
{
	
	FILE *file = fopen(filename,"r");
	int i=0;
	char line[1024];
	while(fgets(line,1024, file))i++;
	fclose(file);
	return i;
}
void readContacts(char* filename,contact* contacts)
{
	FILE *file = fopen(filename,"r");
	char line[1024];
	int i=0;
	while(fgets(line,1024, file)){
		contacts[i].deleted=0;
		sscanf(line,  "%s %s %s %s %s" , contacts[i].name, contacts[i].address, contacts[i].gender, contacts[i].email, contacts[i].phone);
		i++;	
}
fclose(file);
}
contact* loadContacts(char* filename)
{
	int linecounter= countContacts(filename);
	contact* contacts=malloc(linecounter*sizeof(contact));
	readContacts(filename, contacts);
	return contacts;
}
void saveTxt(char* filename,contact* contacts, int contactCounter)
{
	FILE *file = fopen(filename,"w");
	int i=0;
	for (i=0; i<contactCounter; i++){
		if(contacts[i].deleted==0)
		{
			fprintf(file, "%s %s %s %s %s\n",  contacts[i].name, contacts[i].address, contacts[i].gender, contacts[i].email, contacts[i].phone);
		}
	}
	fclose(file);
	printf("\n File saved successfully");
}

/* -------------------------------------------------------*/

contact* addContact(contact* contacts, int* ptr_contactCounter){
	printTitle();
	(*ptr_contactCounter)++; 
	contacts = realloc(contacts, *ptr_contactCounter * sizeof(contacts));
	puts("--> Add New Contact");
	printf(" Name: ");
	scanf("%s", contacts[*ptr_contactCounter - 1].name);
	printf(" Address: ");
	scanf("%s", contacts[*ptr_contactCounter - 1].address);
	printf(" Gender: ");
	scanf("%s", contacts[*ptr_contactCounter - 1].gender);
	printf(" Email: ");
	scanf("%s", contacts[*ptr_contactCounter - 1].email);
	printf(" Phone: ");
	scanf("%s", contacts[*ptr_contactCounter - 1].phone);
	return contacts;
}

void listContacts(contact* contacts, int contactCounter)
{
	printTitle();
	int i;
	for (i=0; i<contactCounter; i++)
	{
	printContact(contacts[i]);		
	}
	printf(" Number of records found: %d\n", i);
}

void searchContact(contact* contacts, int contactCounter)
{
	printTitle();
	char name[100];
	printf("Enter contact name:");
	scanf("%s", name);
	int i=0;
	for ( i=0; i<contactCounter; i++){
		if(strcmp(name,contacts[i].name)==0 && contacts[i].deleted==0)
		{
			printf("Record found\n");
			printContact(contacts[i]);
			return;
		}
	}
	printf("Record not found\n");
}

void updateContact(contact* contacts, int contactCounter)
{	
	printTitle();
	char name[100];
	printf("Enter contact name:");
	scanf("%s", name);
	int i=0;
	for ( i=0; i<contactCounter; i++){
		if(strcmp(name,contacts[i].name)==0 && contacts[i].deleted==0)
		{
			printf("Enter new address:");
			scanf("%s", contacts[i].address);
			printf("Enter gender:");
			scanf("%s", contacts[i].gender);
			printf("Enter new email:");
			scanf("%s", contacts[i].email);
			printf("Enter new phone nubmer:");
			scanf("%s", contacts[i].phone);
			printf("\nSelected entry updated!");
			return;
		}
	}
	printf(" Entry not found\n");
}
void deleteContact(contact* contacts, int contactCounter)
{
	printTitle();
	char name[100];
	printf("Enter contact name:");
	scanf("%s", name);
	int i=0;
	for ( i=0; i<contactCounter; i++)
	{
		if(strcmp(name,contacts[i].name)==0 && contacts[i].deleted==0)
		{ 
			contacts[i].deleted=1;
			printf("Record deleted succesfully");
			return;
		}
	}
	printf(" Record NOT succesfully deleted- please enter a valid name");
	
}
void exitEnv(char* filename,contact* contacts, int contactCounter)
{
	saveTxt(filename,contacts,contactCounter);
	exit(0);
}
