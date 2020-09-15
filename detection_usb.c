/* DATE   : LE 15/05/2017
 * AUTEUR : EL-HAJJAM Oussama
 * OBJET  :  (Programme de d�tection de l'insersion d'une cl� USB (ISGA SETTAT)
 */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h> // Pour ex�cuter des commandes MS-DOS
#include <locale.h>  // pour le support des charact�res sp�ciaux fran�ais


char tous_les_disques[30];
size_t len = 0;


char getRemovableDisk();


int main(void){
    setlocale(LC_CTYPE,""); // pour le support des charact�res sp�ciaux fran�ais
    printf("\t******** ISGA Malware (^_-) ************\n\
<** D�tecteur de l'insertion d'une cl� USB ou p�rif�rique amouvible **>\n\n\
   D�tection en cours ");
    char lettre_du_lecteur = getRemovableDisk();
    while(1){
        lettre_du_lecteur = getRemovableDisk();
        if(lettre_du_lecteur!='0'){
            printf("\nNouveau disque inser� : %c:/ \nContenu du disque (^_^):\n", lettre_du_lecteur);
            char commande[200]="dir ";
            size_t len = strlen(commande);//avoir la longeure de se qui est d�ja stocker dans commande ("dir ")
            commande[len]=lettre_du_lecteur;//mettre la lettre du lecteur a la derniere case de commande ("dir G")
            commande[len+1]='\0';
            strcat(commande,":\\");
            system(commande);
            printf("\n D�tection en cours ");
        }
        else
            printf("|");
        Sleep(1000); // La fr�quence de rafraichissement en millisecondes
    }

    return 0;
}


char getRemovableDisk(){// fonction pour obtenir le "caract�re" du disk amovible
    char disque='0';

    char szLogicalDrives[MAX_PATH];
    DWORD dwResult = GetLogicalDriveStrings(MAX_PATH, szLogicalDrives);

    char disques_actuels[20]="";

    int i,j,k,trouve;
    for(i=0; i<dwResult; i++)
    {
        if(szLogicalDrives[i]>='A' && szLogicalDrives[i]<='Z')//il faut que le caract�re de disk amovible >=A et <=Z
        {
            len = strlen(disques_actuels);
            disques_actuels[len]=szLogicalDrives[i];
            disques_actuels[len+1]='\0';
            if(strchr(tous_les_disques,szLogicalDrives[i]) == NULL)
            {
                disque = szLogicalDrives[i];
            }
        }
    }
    strcpy(tous_les_disques,disques_actuels);
    return disque;
}

