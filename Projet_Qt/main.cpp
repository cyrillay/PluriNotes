#include <iostream>
#include <time.h>
#include "notes.h"
#include "fenetres.h"


/*


*
* est-ce que tu pourras rajouter l'initialisation de l'état à "en attente" quand on crée une tache ?
*
* faudra tu m'expliques pourquoi quand tu crée un objet tu fais m1.ajMulti(id,description,image).setTitre(t); pourquoi le titre est pas dans le constructeur ?
*
* 29/05 : ajout de docks dans l'app, l'ajout d'une note ajoute son ID dans le menu de gauche (j'en ai chié sa daronne)
*       : la sélection d'une note dans le menu de gauche affiche son titre dans la partie centrale
*           ->je sais pas trop comment gérer l'affichage selon le type de note (article, etc..) sans avoir de la redondance de code, si t'a des pistes écrit les ici
*
*/

int menu =0;


NotesManager2& m1 = NotesManager2::getManager();

int main(int argc,  char *argv[]){

    ///pour afficher/retirer l'interface graphique, (dé)commenter les 4 lignes suivantes
    QApplication app(argc, argv);
    FenPrincipale fenetre;
    fenetre.show();
    app.exec();

    int menu =99; int j=0;
    while (menu!=10) {

        std::cout << "  tu as actuellement "<<m1.getnbNote()<<" notes ; que voulez vous faire  ?"<<std::endl<<
                     "1- ajouter une note"<<std::endl<<
                     "2- afficher les notes "<<std::endl<<
                     "3- rechercher une note"<<std::endl<<
                     "10- quitter"<<std::endl;
        std::cin>>menu;

        switch (menu){

        case 1 : {std::cout<<" creer"<<std::endl;
            std::string t;
            std::string id;
            std::cout<<" ID ?"<<std::endl;
            std::cin>> id;

            std::cout<<" quel est le titre de la note a creer ?"<<std::endl;
            std::cin>> t;

            std::cout << " tu veux ?"<<std::endl<<
                         "1- article"<<std::endl<<
                         "2- multimedia "<<std::endl<<
                         "3- tache"<<std::endl;
            std::cin>>j;

                    if (j==1){  std::string txt;
                        std::cout<<" le texte de larticle ?"<<std::endl;
                        //std::cin>>txt;
                        //std::getline(std::cin,txt);

                        //std::cin.sync(); //clear buffer
                        //std::cin.get();

                        //std::getline(std::cin, txt);
                        std::cin>>txt;

                        m1.ajArticle(id,txt).setTitre(t);
                    }
                    if (j==2){ std::string description;std::string image;
                        std::cout<<" la description ?"<<std::endl;
                        std::cin>> description;
                        std::cout<<" la image ?"<<std::endl;
                        std::cin>> image;
                        m1.ajMulti(id,description,image).setTitre(t);
                    }
                    if (j==3){ std::string action ;  unsigned int priorite;  std::string echeance;

                        std::cout<<" action?"<<std::endl;
                        std::cin>> action;
                        std::cout<<" priorite (int)?"<<std::endl;
                        std::cin>> priorite;
                        std::cout<<" echeance?"<<std::endl;
                        std::cin>> echeance;

                        m1.ajTache(id,action,priorite,echeance).setTitre(t);
                    }break;
        }






        case 2 :{
            for(NotesManager2::ConstIterator it= m1.getIterator(); !it.isDone(); it.next())
            {
                    it.current().afficher();
            }
            break;
                }

        case 3 :{
            std::string tf;
            std::cout<<" titre/ partie du titre a trouver ?"<<std::endl;
            std::cin>> tf;
            for(NotesManager2::Searchiterator it= m1.getSearchIterator(tf); !it.isDone(); it.
                    next())
                    {
                        it.current().afficher();
                        //std::cout << it.current(); marche pas :'(
                    } break;
                }


         case 10 : break;
        }


    };

    return  0;
}
