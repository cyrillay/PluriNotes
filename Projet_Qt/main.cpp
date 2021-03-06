#include <iostream>
#include <time.h>
#include "notes.h"
#include "fenetres.h"
#include "relations.h"
#include "manager.h"

/*
*       : reste à faire :
*           - gérer la corbeille et l'archivage des notes, faire que la suppression d'une note supprime les couples
*           dans laquelle elle est impliquée
*           - gérer l'affichage ergonomique des taches selon prio/échance + arborescence
*           - améliorer la gestion mémoire au niveau de la suppression, il reste des trucs non libérés
*           - Annuler/Rétablir
*
*
* 13/06 : les deux manages différents sont ok  mais add pour une relation marche pas du coup c'est add relation de base
*
*
*/





int main(int argc,  char *argv[]) {


    NotesManager2  &m1 = NotesManager2::getManager();
    RelationManager& m2 = RelationManager::getManager();
    //pour afficher/retirer l'interface graphique, (dé)commenter les 4 lignes suivantes
    QApplication app(argc, argv);

    FenPrincipale fenetre;
    fenetre.show();

    m1.load();
    fenetre.affichage_notes_relations();
    app.exec();


    int menu =99; int j=0;
    while (menu!=10) {

        std::cout << "  tu as actuellement "<<m1.getobjets().size() <<" notes ; que voulez vous faire  ?"<<std::endl<<
                     "1- ajouter une note"<<std::endl<<
                     "2- afficher les notes "<<std::endl<<
                     "3- rechercher une note"<<std::endl<<
                     "4- mettre a jour note(que tachepour le moment)"<<std::endl<<
                     "5- SupprimerNote une note"<<std::endl<<
                     "7- tests cyril affichage relation note "<<std::endl<<
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
                        std::cin>>txt;

           //             m1.ajArticle(id,t,txt);
                    }
                    if (j==2){ std::string description;std::string image;
                        std::cout<<" la description ?"<<std::endl;
                        std::cin>> description;
                        std::cout<<" la image ?"<<std::endl;
                        std::cin>> image;
       //                 m1.ajMulti(id,t,description,image);
                    }
                    if (j==3){ std::string action ;  unsigned int priorite;  std::string echeance;

                        std::cout<<" action?"<<std::endl;
                        std::cin>> action;
                        std::cout<<" priorite (int)?"<<std::endl;
                        std::cin>> priorite;
                        std::cout<<" echeance?"<<std::endl;
                        std::cin>> echeance;

           //             m1.ajTache(id,t,action,priorite,echeance,en_attente);


                    }break;
        }






        case 2 :{


                }

        case 3 :{
            std::string tf;
            std::cout<<" titre/ partie du titre a trouver ?"<<std::endl;
            std::cin>> tf;

                }

        case 4 :{
            std::string tf;
            std::cout<<" ID de la note a changer?"<<std::endl;
            std::cin>> tf;
            //m1.getNote(tf).MiseAJour();// plymorphisme à definir dans les classes filles
                                          // faudrait que ca les affiche comme si on en créait non ?
                     break;
                }

        case 5 :{
                std::cout<<"id de la note à SupprimerNote?"<<std::endl;
                std::string td;
                std::cin>> td;

               m1.SupprimerNote(m1.getNote(td));
             // m1.SupprimerNote(m1.getNote(td));
            break;
                }

         case 7 :
        {
            std::cout << "ESSAIS CYRIL references de notes\n";
            article* nouv = new article("id","titre","txt, \\ref{id} suite \\ref{id2} okalm");
            article* nouv1 = new article("id1","titre","texte a lacon");
            article* nouv2 = new article("id2","titr2222e","txt");
            m1.add(*nouv);
            m1.add(*nouv1);
            m1.add(*nouv2);
            m1.checkReferences();

        }

         case 10 : break;
        }


    };
         m1.freeManager();
         m2.freeManager();
    return  0;
}
