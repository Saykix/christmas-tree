#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#define BRANCHE 29  //valeur par défaut : 29
#define TRONC 4     //valeur par défaut : 4
#define ETOILE 4    // correspond au nombre de lignes que pompe l'étoile, par défaut 4

char sapin[(BRANCHE*2+2)*(BRANCHE+1+TRONC+ETOILE)]; // = sapin[largeur * hauteur];

char snow[(BRANCHE*2+2)*(BRANCHE+1+TRONC+ETOILE)];

int ligne[58];

int valeurTab(int rangee) { //fonction pour connaitre la valeur de la première case à gauche à partir de sa rangée
	return rangee*(BRANCHE*2+2)+(ETOILE*(BRANCHE*2+2));
}



int CreaEtoile(int i, int rangee) { //Création de l'étoile sah quel plaisir
	
	char etoile[28]="__/'\\__\\     //_   _\\  \\ /  ";
	rangee = 0;
	int j = 0;
	while (rangee < 4){
		i=0;
		while (i<BRANCHE-3) {
			sapin[rangee*(BRANCHE*2+2)+i] = ' ';
			i++;
		}
		while (i<BRANCHE+4) {
			sapin[rangee*(BRANCHE*2+2)+i] = etoile[j];
			i++;
			j++;
		}	
		while (i<(BRANCHE*2+2)-1) {
	                sapin[rangee*(BRANCHE*2+2)+i] = ' ';
	                i++;
	        }
	        rangee++;
	        sapin[rangee*(BRANCHE*2+2)-1] = '\n';
	}
}



int CreaSapin(int i, int rangee) {

	//création des branches du sapin
	
	i = rangee = 0;
	while (rangee<=BRANCHE) {
		while (i<BRANCHE-rangee) { //dessine les espaces à gauche
			sapin[valeurTab(rangee)+i] = ' ';
			i++;
		}
		while (i<BRANCHE+1+rangee) { //dessine l'entièreté des * de la ligne
			sapin[valeurTab(rangee)+i] = '*';
			i++;
		}
		while (i<BRANCHE*2+2) { //dessine les espaces à droite
			sapin[valeurTab(rangee)+i] = ' ';
			i++;
		}
		rangee++;
		sapin[valeurTab(rangee)-1] = '\n'; //changement de rangée, retour à la ligne
		i=0;	
	}

	//création du tronc
	
	while (rangee<=BRANCHE+TRONC) {
		while (i<BRANCHE-TRONC) { //espaces à gauche
			sapin[valeurTab(rangee)+i] = ' ';
			i++;
		}
		while (i<(BRANCHE-TRONC)+(TRONC*2+1)) { //entièreté du tronc
			sapin[valeurTab(rangee)+i] = '#';
			i++;
		}
		while (i<BRANCHE*2+2) { //espaces à droite
			sapin[valeurTab(rangee)+i] = ' ';
			i++;
		}
		rangee++;
		sapin[valeurTab(rangee)-1] = '\n'; //retour à la ligne
		i=0;
	}
}


//Fonctions pour les animations à mettre en-dessous.


int Bougies(int nbFrame3, int i, int rangee) {
	
	
	for (int j=0;j<4;j++){ //boucle for qui permet de rajouter autant de bougie qu'on veut
		 switch (j) { //chaque "tour" de la boucle = une coordonnée de bougie
	                case 0 :
	                        i = 22;
	                        rangee = 11;
	                        break;
	                case 1 :
	                        i = 41;
	                        rangee = 15;
	                        break;
	                case 2 :
	                        i = 18;
	                        rangee = 26;
                        	break;
			case 3 :
				i = 39;
				rangee = 23;
				break;
                	default:
        	                printf("Errorproutprout,%d\n",j);
	        }
		if (nbFrame3 == 1) {
			sapin[i+valeurTab(rangee)] = '(';
			sapin[(i+1)+valeurTab(rangee)] = '\\';
		} else if (nbFrame3 == 2) {
			sapin[i+valeurTab(rangee)] = '(';
			sapin[(i+1)+valeurTab(rangee)] = ')';
		}  else if (nbFrame3 == 3) {
			sapin[i+valeurTab(rangee)] = '/';			
                        sapin[(i+1)+valeurTab(rangee)] = ')';
		}

			sapin[i+valeurTab(rangee+1)] = '|';
			sapin[(i+1)+valeurTab(rangee+1)] = '|';
	}
}

int Herbe(int nbFrame8, int i, int rangee){
	i=0;
        for (int j=0;j<59;j++){//boucle pour faire toute la rangée d'herbe avant le tronc du sapin 
		if (sapin[i+valeurTab(33)] != '#'&&sapin[i+valeurTab(33)] != 'x' &&sapin[i+valeurTab(33)] != '+') {
                	if (nbFrame8 == 3) {
                	        sapin[i+valeurTab(33)] = '\\';
			} else if (nbFrame8 == 2 || nbFrame8 == 4) {
				sapin[i+valeurTab(33)] = ')';
                	} else if (nbFrame8 == 1|| nbFrame8 == 5) {
                	        sapin[i+valeurTab(33)] = '|';
			} else if (nbFrame8 == 6 || nbFrame8 == 8) {
				sapin[i+valeurTab(33)] = '(';
                	}  else if(nbFrame8 == 7) {
                	        sapin[i+valeurTab(33)] = '/';
                
			}
		}
                i++;
        }


}

int guirlande1(int nbFrame2, int i, int rangee){ // une ligne corespont à une chaine de charactère(-,0 et O ici) sur une même rangée
	int inc;   //variable qui est incrémenter dans le 'for'pour afficher des '-'
	int n=0;	//variable d'incrémentation qui sera comparer avec imax dans le but de connaire si on a besion de changer de rangée on non
	int maxg=5;	//variable qui donne le nombre de '-' par ligne
	int ligneinc=0;		//variable d'incrémentation permettant de changer le maxg car besion de 4 charactère à certaine ligne
	int imax;	//varibale contennat le x maximale de la guirlande
	char content;	//variable contenant un contenu qui sera affiché. elle contient soit un 'O', soit un '0';
	int w;		//variable d'incrémentation qui permet de choisir entre '0' et 'O'
	i=13;
	rangee=16;
	for(inc=1;inc<=18;inc++){		//de 1 à 18 car besoin de 18 -
		sapin[i+valeurTab(rangee)]='~';		//la ou on change les '*' en '-'
		i=i+2;		//augmente de 2 car un tiret tous les 2 charactères
		n=n+1;
		if(n==maxg){	//si n est égal à 5 alors on a print 5 tiret soit une ligne donc on a finit une ligne donc on change de ligne
			rangee=rangee+1;
			n=0;
			maxg=4;		//pour les lignes 2 et 3, il est demandé 4 tirets donc on passe la condition à 4
			ligneinc=ligneinc+1;
		}
		if(ligneinc==2){ // quand cette condition est vrai, cela veut dire que les prochaines lignes auront 5 tirets
			maxg=5;
		}
	}
	if(nbFrame2==1){
		rangee=16;
		imax=48;
		content='0';
		w=0;
		n=0;
		maxg=5;
		ligneinc=0;
		for(i=14;i<=imax;i=i+2){
			sapin[i+valeurTab(rangee)]=content;
			w=w+1;
			n=n+1;
			if(w%2==0){	//variable que l'on incrémente puis on teste, si pair alors on met un '0', si un impair, 'O', pour avoir 0 O 0 O ect...
				content='0';
			}else{
				content='o';
			}
			if(n==maxg){
				rangee=rangee+1;
				n=0;
				maxg=4;
				ligneinc=ligneinc+1;
			}
			if(ligneinc==2){
				maxg=5;
			}

		}
	}else{
		rangee=16;
                imax=48;
                content='o';
                w=0;
                n=0;
                maxg=5;
                ligneinc=0;
                for(i=14;i<=imax;i=i+2){
                        sapin[i+valeurTab(rangee)]=content;
                        w=w+1;
                        n=n+1;
                        if(w%2==0){		//comme on veut changer les O et 0 on change juste le faite que pair donnera O et non 0 comme dans la frame 1 et pareil pour l'autre
                                content='o';
                        }else{
                                content='0';
                        }
                        if(n==maxg){
                                rangee=rangee+1;
                                n=0;
                                maxg=4;
                                ligneinc=ligneinc+1;
                        }
                        if(ligneinc==2){
                                maxg=5;
                        }

                }

	}
}

int guirlande2(int nbFrame2, int i, int rangee){ // une ligne corespont à une chaine de charactère(-,0 et O ici) sur une même rangée
        int inc;   //variable qui est incrémenter dans le 'for'pour afficher des '-'
        int n=0;        //variable d'incrémentation qui sera comparer avec imax dans le but de connaire si on a besion de changer de rangée on non
        int maxg=5;     //variable qui donne le nombre de '-' par ligne
        int ligneinc=0;         //variable d'incrémentation permettant de changer le maxg car besion de 4 charactère à certaine ligne
        int imax;       //varibale contennat le x maximale de la guirlande
        char content;   //variable contenant un contenu qui sera affiché. elle contient soit un 'O', soit un '0';
        int w;          //variable d'incrémentation qui permet de choisir entre '0' et 'O'

        i=40;
        rangee=20;
        for(inc=1;inc<=18;inc++){               //de 1 à 18 car besoin de 18 -
                sapin[i+valeurTab(rangee)]='~';         //la ou on change les '*' en '-'
                i=i-2;          //augmente de 2 car un tiret tous les 2 charactères
                n=n+1;
                if(n==maxg){    //si n est égal à 5 alors on a print 5 tiret soit une ligne donc on a finit une ligne donc on change de ligne
                        rangee=rangee+1;
                        n=0;
                        maxg=4;         //pour les lignes 2 et 3, il est demandé 4 tirets donc on passe la condition à 4
                        ligneinc=ligneinc+1;
                }
                if(ligneinc==2){ // quand cette condition est vrai, cela veut dire que les prochaines lignes auront 5 tirets
                        maxg=5;
                }
        }
        if(nbFrame2==1){
                rangee=20;
                imax=6;
                content='0';
                w=0;
                n=0;
                maxg=5;
                ligneinc=0;
                for(i=39;i>=imax;i=i-2){
                        sapin[i+valeurTab(rangee)]=content;
                        w=w+1;
                        n=n+1;
                        if(w%2==0){     //variable que l'on incrémente puis on teste, si pair alors on met un '0', si un impair, 'O', pour avoir 0 O 0 O ect...
                                content='0';
                        }else{
                                content='o';
                        }
                        if(n==maxg){
                                rangee=rangee+1;
                                n=0;
                                maxg=4;
                                ligneinc=ligneinc+1;
                        }
                        if(ligneinc==2){
                                maxg=5;
                        }

                }
        }else{
                rangee=20;
                imax=6;
                content='o';
                w=0;
                n=0;
                maxg=5;
                ligneinc=0;
                for(i=39;i>=imax;i=i-2){
                        sapin[i+valeurTab(rangee)]=content;
                        w=w+1;
                        n=n+1;
                        if(w%2==0){             //comme on veut changer les O et 0 on change juste le faite que pair donnera O et non 0 comme dans la frame 1 et pareil pour l'autre
                                content='o';
                        }else{
                                content='0';
                        }
                        if(n==maxg){
                                rangee=rangee+1;
                                n=0;
                                maxg=4;
                                ligneinc=ligneinc+1;
                        }
                        if(ligneinc==2){
                                maxg=5;
                        }

                }

        }
}

int guirlande3(int nbFrame2, int i, int rangee){
	int inc;   //variable qui est incrémenter dans le 'for'pour afficher des '-'
        int n=0;        //variable d'incrémentation qui sera comparer avec imax dans le but de connaire si on a besion de changer de rangée on non
        int maxg=6;     //variable qui donne le nombre de '-' par ligne
        int ligneinc=0;         //variable d'incrémentation permettant de changer le maxg car besion de 4 charactère à certaine ligne
        int imax;       //varibale contennat le x maximale de la guirlande
        char content;   //variable contenant un contenu qui sera affiché. elle contient soit un 'O', soit un '0';
        int w;          //variable d'incrémentation qui permet de choisir entre '0' et 'O'
        i=13;
        rangee=24;
        for(inc=1;inc<=22;inc++){               //de 1 à 18 car besoin de 18 -
                sapin[i+valeurTab(rangee)]='~';         //la ou on change les '*' en '-'
                i=i+2;          //augmente de 2 car un tiret tous les 2 charactères
                n=n+1;
                if(n==maxg){    //si n est égal à 5 alors on a print 5 tiret soit une ligne donc on a finit une ligne donc on change de ligne
                        rangee=rangee+1;
                        n=0;
                        maxg=6;         //pour les lignes 2 et 3, il est demandé 4 tirets donc on passe la condition à 4
                        ligneinc=ligneinc+1;
                }
                if(ligneinc==2){ // quand cette condition est vrai, cela veut dire que les prochaines lignes auront 5 tirets
                        maxg=6;
                }
		if(rangee==29){
			rangee=28;
		}
        }
        if(nbFrame2==1){
                rangee=24;
                imax=56;
                content='0';
                w=0;
                n=0;
                maxg=6;
                ligneinc=0;
                for(i=14;i<=imax;i=i+2){
                        sapin[i+valeurTab(rangee)]=content;
                        w=w+1;
                        n=n+1;
                        if(w%2==0){     //variable que l'on incrémente puis on teste, si pair alors on met un '0', si un impair, 'O', pour avoir 0 O 0 O ect...
                                content='0';
                        }else{
                                content='o';
                        }
                        if(n==maxg){
                                rangee=rangee+1;
                                n=0;
                                maxg=6;
                                ligneinc=ligneinc+1;
                        }
                        if(ligneinc==2){
                                maxg=6;
                        }

                }
        }else{
                rangee=24;
                imax=56;
                content='o';
                w=0;
                n=0;
                maxg=6;
                ligneinc=0;
                for(i=14;i<=imax;i=i+2){
                        sapin[i+valeurTab(rangee)]=content;
                        w=w+1;
                        n=n+1;
                        if(w%2==0){             //comme on veut changer les O et 0 on change juste le faite que pair donnera O et non 0 comme dans la frame 1 et pareil pour l'autre
                                content='o';
                        }else{
                                content='0';
                        }
                        if(n==maxg){
                                rangee=rangee+1;
                                n=0;
                                maxg=6;
                                ligneinc=ligneinc+1;
                        }
                        if(ligneinc==2){
                                maxg=6;
                        }

                }

        }

}

int guirlande4(int nbFrame2, int i, int rangee){
	 int inc;   //variable qui est incrémenter dans le 'for'pour afficher des '-'
        int n=0;        //variable d'incrémentation qui sera comparer avec imax dans le but de connaire si on a besion de changer de rangée on non
        int maxg=4;     //variable qui donne le nombre de '-' par ligne
        int ligneinc=0;         //variable d'incrémentation permettant de changer le maxg car besion de 4 charactère à certaine ligne
        int imax;       //varibale contennat le x maximale de la guirlande
        char content;   //variable contenant un contenu qui sera affiché. elle contient soit un 'O', soit un '0';
        int w;		//variable d'incrémentation qui permet de choisir entre '0' et 'O'
        i=23;
        rangee=15;
        for(inc=1;inc<=10;inc++){               //de 1 à 18 car besoin de 18 -
                sapin[i+valeurTab(rangee)]='~';         //la ou on change les '*' en '-'
                i=i+2;          //augmente de 2 car un tiret tous les 2 charactères
                n=n+1;
                if(n==maxg){    //si n est égal à 5 alors on a print 5 tiret soit une ligne donc on a finit une ligne donc on change de ligne
                        rangee=rangee-1;
                        n=0;
                        maxg=4;         //pour les lignes 2 et 3, il est demandé 4 tirets donc on passe la condition à 4
                        ligneinc=ligneinc+1;
                }
                if(ligneinc==2){ // quand cette condition est vrai, cela veut dire que les prochaines lignes auront 5 tirets
                        maxg=4;
                }
                if(rangee==29){
                        rangee=28;
                }
        }
        if(nbFrame2==1){
                rangee=15;
                imax=42;
                content='0';
                w=0;
                n=0;
                maxg=4;
                ligneinc=0;
                for(i=24;i<=imax;i=i+2){
                        sapin[i+valeurTab(rangee)]=content;
                        w=w+1;
                        n=n+1;
                        if(w%2==0){     //variable que l'on incrémente puis on teste, si pair alors on met un '0', si un impair, 'O', pour avoir 0 O 0 O ect...
                                content='0';
                        }else{
                                content='o';
                        }
                        if(n==maxg){
                                rangee=rangee-1;
                                n=0;
                                maxg=4;
                                ligneinc=ligneinc+1;
                        }
                        if(ligneinc==2){
                                maxg=4;
                        }

                }
        }else{
                rangee=15;
                imax=42;
                content='o';
                w=0;
                n=0;
                maxg=4;
                ligneinc=0;
                for(i=24;i<=imax;i=i+2){
                        sapin[i+valeurTab(rangee)]=content;
                        w=w+1;
                        n=n+1;
                        if(w%2==0){             //comme on veut changer les O et 0 on change juste le faite que pair donnera O et non 0 comme dans la frame 1 et pareil pour l'autre
                                content='o';
                        }else{
                                content='0';
                        }
                        if(n==maxg){
                                rangee=rangee-1;
                                n=0;
                                maxg=4;
                                ligneinc=ligneinc+1;
                        }
                        if(ligneinc==2){
                                maxg=4;
                        }

                }

        }

}


int couleur(int nbFrame4){
        if(nbFrame4==1)               {printf("\x1b[1;32m");}
        if(nbFrame4==2)               {printf("\x1b[1;37m");}
        if(nbFrame4==3)               {printf("\x1b[1;31m");}
        if(nbFrame4==4)               {printf("\x1b[1;34m");}

}

int Boulle(int i, int rangee) {

        for (int j=0;j<=10;j++){ //boucle for qui permet de rajouter autant de boulle qu'on veut
                 switch (j) { //chaque "tour" de la boucle = une coordonnée de boulle
                        case 0 :
                                i = 27;
                                rangee = 11;
                                break;
                        case 1 :
                                i = 17;
                                rangee = 13;
                                break;
                        case 2 :
                                i = 23;
                                rangee = 26;
                                break;
                        case 3 :
                                i = 20;
                                rangee =20;
				break;
                         case 4 :
                                i = 45;
                                rangee =20;
                                break;
                         case 5 :
                                i = 29;
                                rangee =6;
                                break;
                        case 6 :
                                i = 35;
                                rangee =16;
                                break;
                         case 7 :
                                i = 50;
                                rangee =24;
                                break;
                         case 8 :
                                i = 43;
                                rangee =17;
                                break;
                         case 9 :
                                i = 35;
                                rangee =12;
                                break;
                         case 10 :
                                i = 34;
                                rangee =27;
                                break;
                        default:
                                printf("Errorpouetpouet\n");

		 }
		sapin[i+valeurTab(rangee)] = ',';
		sapin[i+valeurTab(rangee+1)] = 'Ô'; //ça fait des points d'interrogations mais c'est volontaire
                
        }
}


int neige(int rangee,int memoRandom){

	int L = BRANCHE*2+2;
	int H = BRANCHE+1+TRONC+ETOILE;

        // Clear Snow
	rangee = 0;
	int j = 0;
	while (rangee<33) {
		j=0;
		while (j<59) {
			if (rangee < 32-ligne[j]) {
				if (sapin[rangee*L+j] == '+' || sapin[rangee*L+j] == 'x') {
					sapin[rangee*L+j] = ' ';
				}
			}
			j++;
		}
		rangee++;
        }

	rangee = 32;
        while (rangee>=0) {
		j=58;
		while (j>=0) {
			if (rangee < 33-ligne[j]) {
                		if (snow[rangee*L+j] == '+'){
					if (rangee+1 == 33-ligne[j]) {
                                		ligne[j]++;
                                	}
                               	        snow[rangee*L+j] = ' ';
                                        snow[rangee*L+j+L] = 'x';
                                	
				}
			                
	                	else if (snow[rangee*L+j] == 'x'){
					if (rangee+1 == 33-ligne[j]) {
                                        	ligne[j]++;
                                        }
                                        snow[rangee*L+j] = ' ';
                                        snow[rangee*L+j+L] = '+';

	                	}
	                	else;   // Empty
			
			}
			j--;
	        }
		rangee--;
	}

        int r0, r1;
	r0 = random() %L;
	while (r0==memoRandom) {
        	r0 = random() %L;
	}
	memoRandom = r0;
        r1 = random() %2;
        if (r1 == 0 && ligne[r0] < 33) snow[r0] = '+';
        if (r1 == 1 && ligne[r0] < 33) snow[r0] = 'x';

        rangee = 0;
	while (rangee<33) {
		j = 0;
		while (j<59) {
			if(rangee < 33-ligne[j]) {	
		                if (sapin[rangee*L+j] == ' ' && snow[rangee*L+j] != ' '){
		                        if (snow[rangee*L+j] == '+') sapin[rangee*L+j] = '+';
		                        else sapin[rangee*L+j] = 'x';
		                }
			}
			int addition = rangee*L+j;
			j++;
	        }
		rangee++;
	}
	return memoRandom;
}

int lumEtoile(int nbFrame2){
	int largeur = BRANCHE*2+2;
	if (nbFrame2 == 1) {
		sapin[23] = '\\';
		sapin[35] = '/';
		sapin[22+largeur] = '_';
		sapin[36+largeur] = '_';
		sapin[23+3*largeur] = '/';
		sapin[35+3*largeur] = '\\';
	}
	else if (nbFrame2 == 2) {
                sapin[23] = ' ';
                sapin[35] = ' ';
                sapin[22+largeur] = ' ';
                sapin[36+largeur] = ' ';
                sapin[23+3*largeur] = ' ';
                sapin[35+3*largeur] = ' ';
	}
	else;
}


//MAIN EST ICI
int main() {

        int i = 0; // pour faciliter le calcul de la position x
        int rangee = 0; // pour faciliter le calcul de la position y, à utiliser avec la fonction valeurTab(rangee) !
        CreaEtoile(i,rangee);
        CreaSapin(i,rangee); //Création du sapin
        for (i = 0; i < (BRANCHE*2+2)*(2*BRANCHE+1+TRONC+ETOILE); i++) snow[i] = ' ';
	int prepaNeige = 0;
	while (prepaNeige<BRANCHE) {
                ligne[prepaNeige] = prepaNeige;
                prepaNeige++;
        }
        while (prepaNeige>=0) {
                ligne[58-prepaNeige] = prepaNeige;
                prepaNeige--;
        }
	int memoRandom=100;

        //Rajoutez vos frames ici.
        int nbFrame3 = 1;
        int nbFrame4 = 1;
        int nbFrame2 = 1;
        int nbFrame8 = 1;

        while (1) { //boucle infinie

                // PLACE AUX ANIMATIONS ! ATTENTION A L'ORDRE DANS LEQUEL ELLE VONT SE SUPERPOSER, CA PEUT CREER DES BUGS
                guirlande1(nbFrame2,i,rangee);
                guirlande2(nbFrame2,i,rangee);
                guirlande3(nbFrame2,i,rangee);
                guirlande4(nbFrame2,i,rangee);
                lumEtoile(nbFrame2);
                Boulle(i,rangee);
                Bougies(nbFrame3,i,rangee);
                couleur(nbFrame4)
		    memoRandom = neige(rangee,memoRandom);
                Herbe(nbFrame8,i,rangee);

		
		usleep(500000);
                system("clear");
                printf("\n%s\n",sapin);

                nbFrame2++;
                if (nbFrame2 == 3){
                        nbFrame2 = 1;
                }
                nbFrame3++;
                if (nbFrame3 == 4) {
                        nbFrame3 = 1;
                }
                nbFrame4++;
                if (nbFrame4 == 5) {
                        nbFrame4 = 1;
                }
                nbFrame8++;
                if (nbFrame8 == 9) {
                        nbFrame8 = 1;
                }
        }
}
