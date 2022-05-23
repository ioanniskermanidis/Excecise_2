/* 
	Omada Ergastiriou: B'
			IOANNIS KERMANIDIS A' ETOS, AM: 1093654
			Imerominia Syggrafis: 24/05/2022
			
			Skopos: 
				Prokeitai gia diaxeirisi enos ilektronikou tilefwnikou katalogou me dinatotites:
				1. prosthikis, 2. anazitisis, 3.epeksergasias , 4. diagrafis epafis kai 5. provolis olokliris tis listas epafwn*/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*orizoume mia domi dedomenwn tin opoia tha xrisimopoioume gia na apothikeuoyme tis plirofories kathe epafis*/
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


/* parakatw synartiseis einai EPIVOITHITIKES kai xrisimopoiountai mesa stis zitoumenes synartiseis*/

void printTitle(); /* typonei ton titlo "Contact Management" sta apaitoumena shmeia*/
void printContact(contact entry); /* dexetai os parametro mia epafi kai ektypwnei stin othoni tis antistoixes plirofories */
int countContacts(char* filename); /* epistrefei ton aritho twn epafwn tou arxeiou */
void readContacts(char* filename,contact* contacts); /* dexetai os orisma ton pinaka apo contact-structure kai ton symplirwnei me ta stoixeia ton epafwn tou arxeiou*/
contact* loadContacts(char* filename); /* diavazei to arxeio, desmeuei dynamika mnimmi kai fortonei stin mnimi tis epafes */
void saveTxt(char* filename,contact* contacts, int contactCounter); /* grafei ksana sto arxeio ta dedomena apo tin mnimi (eite added,updated,deleted) */

/*oi parakatw einai  synartiseis pou zitontai YPOXREWTIKA apo tin ekfwnisi tis askisis*/
/* i kathe sinartisi ektelei ton skopo pou anaferetai ston pinaka tis ekfonisis pou dothike*/
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
	printf("\n Press m for menu: \n");
	while(1){
		choice = getch();
		if(choice=='m') break;
	}

	}

	return 0;
}


//Functions

void printTitle(){
    //system("cls");
	printf(" --------------------------------------------------------------------------\n");
	printf(" |                         CONTACTS MANAGEMENT                            |\n");
	printf(" --------------------------------------------------------------------------\n\n");

}

void printContact(contact entry)
{
	puts("----------------------------------");
	printf(" Name: %s\n Address: %s\n Gender: %s\n Email: %s\n Phone: %s\n", entry.name, entry.address, entry.gender, entry.email, entry.phone);
	puts("----------------------------------\n");
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
}

/* -------------------------------------------------------*/

contact* addContact(contact* contacts, int* ptr_contactCounter){
	printTitle();
	printf("-->Add Contact\n\n");
	(*ptr_contactCounter)++;
	int contactCounter = *ptr_contactCounter;
	contacts = realloc(contacts, contactCounter * sizeof(contacts));

	contacts[contactCounter- 1].deleted=0;
	puts("--> Add New Contact");
	printf(" Name: ");
	scanf("%s", contacts[contactCounter - 1].name);
	printf(" Address: ");
	scanf("%s", contacts[contactCounter - 1].address);
	printf(" Gender: ");
	scanf("%s", contacts[contactCounter - 1].gender);
	printf(" Email: ");
	scanf("%s", contacts[contactCounter - 1].email);
	printf(" Phone: ");
	scanf("%s", contacts[contactCounter - 1].phone);
	printf("\nNew entry added!\n");
	return contacts;
}

void listContacts(contact* contacts, int contactCounter)
{
	printTitle();
	printf("-->List Contact\n\n");
	int i;
    int countPrinted = 0;
	for (i=0; i<contactCounter; i++)
	{
	if(contacts[i].deleted==0){
            printContact(contacts[i]);
            countPrinted++;
	}
	}
	printf(" Number of records found: %d\n", countPrinted);
}

void searchContact(contact* contacts, int contactCounter)
{
	printTitle();
	printf("-->Search Contact\n\n");
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
	printf("-->Update Contact\n\n");
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
	printf("-->Delete Contact\n\n");
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
    printf("\n File saved successfully");
	exit(0);
}
