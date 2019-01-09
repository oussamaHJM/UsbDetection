/* DATE   : LE 15/05/2017
 * AUTEUR : Khalid EL GHOLAMI
 * OBJET  :  (Programme de détection de l'insersion d'une clé USB (ISGA SETTAT)
 */

#include <stdio.h>
#include <time.h>
#include <string.h>
#include <windows.h> // Pour exécuter des commandes MS-DOS
#include <locale.h>  // pour le support des charactères spéciaux français


char tous_les_disques[30];
size_t len = 0;


char getRemovableDisk();


int main(void){
    setlocale(LC_CTYPE,""); // pour le support des charactères spéciaux français
    printf("\t******** ISGA Malware (^_-) ************\n\
<** Détecteur de l'insertion d'une clé USB ou périférique amouvible **>\n\n\
   Détection en cours ");
    char lettre_du_lecteur = getRemovableDisk();
    while(1){
        lettre_du_lecteur = getRemovableDisk();
        if(lettre_du_lecteur!='0'){
            printf("\nNouveau disque inseré : %c:/ \nContenu du disque (^_^):\n", lettre_du_lecteur);
            char commande[200]="dir ";
            size_t len = strlen(commande);//avoir la longeure de se qui est déja stocker dans commande ("dir ")
            commande[len]=lettre_du_lecteur;//mettre la lettre du lecteur a la derniere case de commande ("dir G")
            commande[len+1]='\0';
            strcat(commande,":\\");
            system(commande);
            printf("\n Détection en cours ");
        }
        else
            printf("|");
        Sleep(1000); // La fréquence de rafraichissement en millisecondes
    }

    return 0;
}


char getRemovableDisk(){// fonction pour obtenir le "caractère" du disk amovible
    char disque='0';

    char szLogicalDrives[MAX_PATH];
    DWORD dwResult = GetLogicalDriveStrings(MAX_PATH, szLogicalDrives);

    char disques_actuels[20]="";

    int i,j,k,trouve;
    for(i=0; i<dwResult; i++)
    {
        if(szLogicalDrives[i]>='A' && szLogicalDrives[i]<='Z')//il faut que le caractère de disk amovible >=A et <=Z
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

