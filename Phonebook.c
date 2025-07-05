//PhoneBook Project
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
//File Creating and String size
#define MAX_LEN 100
#define FILE_NAME "phonebook.dat"
//Structures
struct Contact
{
 char name[MAX_LEN];
 char phone[MAX_LEN];
 char email[MAX_LEN];
 char address[MAX_LEN];
};
//Function for Saving Contact
void add_contact(FILE *fp)
{
 struct Contact c;

 printf("Enter Name: ");
 scanf("%s", c.name);
 int len;
 do 
  {
   printf("Enter Phone Number (10 digits): ");
   scanf("%s", c.phone);
   len = strlen(c.phone);
   if (len != 10) 
    {
     printf("Invalid Entry. Phone number must be 10 digits.\n");
    } else 
    {
     int i;
     for (i = 0; i < len; i++) 
      {
       if (!isdigit(c.phone[i])) 
        {
         printf("Invalid Entry. Phone number must only contain digits.\n");
         break;
        }
      }
     if (i == len) break;
    }
  } while (1);
 printf("Enter email: ");
 scanf("%s", c.email);
 printf("Enter Address: ");
 scanf("%s", c.address);

 fwrite(&c, sizeof(struct Contact), 1, fp);
}
//Function to View all Contacts
void list_contacts(FILE *fp)
{
 struct Contact c;

 rewind(fp);
 while (fread(&c, sizeof(struct Contact), 1, fp) == 1)
  {
    printf("Name: %s\n", c.name);
    printf("Phone: %s\n", c.phone);
    printf("Email: %s\n", c.email);
    printf("Address: %s\n", c.address);
    printf("\n");
  }
}
//Function Menu to specify what to edit
void edit_menu()
{
 printf("Choose an Option to Edit\n");
 printf("1.Name\n");
 printf("2.Phone Numb\n");
 printf("3.Address\n");
}
//Function to Modify Contact
void edit_contact(FILE *fp)
{
 struct Contact c, new_c;
 char name[MAX_LEN];
 int found = 0;
 int cont;
 int len;

 printf("Enter Name of the Contact to Edit: ");
 scanf("%s", name);
 rewind(fp);
 while (fread(&c, sizeof(struct Contact), 1, fp) == 1)
 {
  if (strcmp(c.name, name) == 0)
  {
   found = 1;
   break;
  }
 }
 if (!found)
  {
   printf("Contact not found\n");
   return;
  }
 edit_menu();
 scanf("%d", &cont);
 switch (cont)
  {
   case 1:
    printf("Enter new Name: ");
    scanf("%s", new_c.name);
    strcpy(c.name, new_c.name);
    break;
   case 2:
    do 
    {
     printf("Enter New Phone Number (10 digits): ");
     scanf("%s", new_c.phone);
     len = strlen(new_c.phone);
     if (len != 10) 
     {
      printf("Invalid Entry. Phone number must be 10 digits.\n");
     } else 
     {
      int i;
      for (i = 0; i < len; i++) 
      {
       if (!isdigit(new_c.phone[i])) 
        {
         printf("Invalid Entry. Phone number must only contain digits.\n");
         break;
        }
      }
      if (i == len) break;
     }
    } while (1);
    strcpy(c.phone, new_c.phone);
    break;
   case 3:
    printf("Enter new Address: ");
    scanf("%s", new_c.address);
    strcpy(c.address, new_c.address);
    break;
   default:
    printf("Invalid option");
    break;
  }
 fseek(fp, -1 * sizeof(struct Contact), SEEK_CUR);
 fwrite(&c, sizeof(struct Contact), 1, fp);
}
//Function to Search Contact
void search_contact(FILE *fp)
{
 struct Contact c;
 char name[MAX_LEN];
 int found = 0;

 printf("Enter name of the Contact to search: ");
 scanf("%s", name);
 rewind(fp);
 while (fread(&c, sizeof(struct Contact), 1, fp) == 1)
  {
   if (strcmp(c.name, name) == 0)
    {
     found = 1;
     break;
    }
  }
 if (!found)
  {
   printf("Contact not found\n");
   return;
  }
 printf("Name: %s\n", c.name);
 printf("Phone: %s\n", c.phone);
 printf("Email: %s\n", c.email);
 printf("Address: %s\n", c.address);
}
//Function to Delete Contact
void delete_contact(FILE *fp) 
{
 struct Contact c;
 char name[MAX_LEN];
 int found = 0;

 printf("Enter Name of the contact to Delete: ");
 scanf("%s", name);
 FILE *temp_fp = fopen("temp.dat", "wb");
 rewind(fp);
 while (fread(&c, sizeof(struct Contact), 1, fp) == 1)
  {
   if (strcmp(c.name, name) != 0)
    {
     fwrite(&c, sizeof(struct Contact), 1, temp_fp);
    }
   else
    {
     found = 1;
    }
  }
 if (!found)
  {
   printf("Contact not found\n");
   fclose(temp_fp);
   return;
  }
 fclose(fp);
 fclose(temp_fp);
 remove(FILE_NAME);
 rename("temp.dat", FILE_NAME);
 fp = fopen(FILE_NAME, "r+b");
 printf("Contact Deleted Sucessfully\n");
}
//Function to print Main Menu
void print_menu() 
{
 printf("\n***** Main Menu *****\n");
 printf("1. Add Contact\n");
 printf("2. List Contacts\n");
 printf("3. Edit Contact\n");
 printf("4. Search Contact\n");
 printf("5. Delete Contact\n");
 printf("6. Exit\n");
 printf("*********************\n\n");
 printf("Enter your Choice : ");
}
//Program Starts here
int main()
{
 int option;
 FILE *fp = fopen(FILE_NAME, "r+");
 if (fp == NULL) 
  {
   fp = fopen(FILE_NAME, "w+");
   if (fp == NULL) 
    {
     fprintf(stderr, "Error opening file\n");
     exit(1);
    }
  }
 while (1) 
  {
   print_menu();
   scanf("%d", &option);
   switch (option) 
    {
     case 1:
      add_contact(fp);
      break;
     case 2:
      list_contacts(fp);
      break;
     case 3:
      edit_contact(fp);
      break;
     case 4:
      search_contact(fp);
      break;
     case 5:
      delete_contact(fp);
      break;
     case 6:
      printf("Exiting Phonebook App\n");
      fclose(fp);
      exit(0);
      break;
     default:
      printf("Invalid option\n");
      break;
    }
  }
 return 0;
}
