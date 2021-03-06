#ifndef MANAGER_H
#define MANAGER_H
#include <QString>
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include <vector>
#include "relations.h"


#endif // MANAGER_H



class RelationManager;

/// Classe mère Template abstraite Managers.
/** Cette classe regroupe les attributs et les méthodes communes aux différents Managers.
 * Elle est composée d'un vector de template<classe T> qui stockera et manipulera les objets T,
 *  et d'un chemin de fichier (par défaut) qui mène au fichier .xml dans lequel les objets seront sauvegardés.
 *
 */
template<class T>
class Manager {
protected :

   std::vector<T*> objets;
   mutable  QString filename;

public:

   /// fonction qui vérifie si l'id de l'objet de type T fourni en paramètre existe déja en parcourant le vector (exeption si c'est le cas), et qui l'ajoute à la fin du vector si ce n'est pas le cas.
  /**
  * @param T& : référence sur l'objet à ajouter.
  */
    void add (T& a_ajouter);
    /// fonction qui supprime du vector l'objet de type T fourni en paramètre
   /**
   * @param T& : référence sur l'objet à supprimer.
   */
    void Supprimer (T& toDelete);
    ///accesseur en lecture du vector contenant les objets T.
     const std::vector<T*> getobjets() const {return objets;}
     ///accesseur en lecture du chemin du fichier xml.
   QString getFilename() const { return filename; }

   /// met à jour le chemin du du fichier xml.
 /**
  * @param filename : le chemin du nouveau fichier xml.
  */
   void setFilename(const QString& f) { filename=f; }

    /// Constructeur de Manager, initialise le vector (vide) et  definit  le chemin par défaut du fichier xml.
   Manager():objets(0),filename(QString::fromStdString("..\\sauvegarde.xml")){}
    ///destructeur de Manager
   virtual ~Manager<T>(){std::cout<<"manager(base) detruit"<<std::endl;}
   /// méthode virtuelle pure pour charger les notes à définir dans les filles
      virtual void load () =0 ;
      /// méthode virtuelle pure pour sauvegarder les notes à définir dans les filles
   virtual void save () =0 ;

};



/// Classe fille héritant de Manager<note> et chargée des notes, elle dispose du Design Pattern Singleton.
class NotesManager2 :  public Manager<note> {

private :
    struct Handler {
             NotesManager2* instance; // pointeur sur l'unique instance
             Handler():instance(nullptr){}
            ~Handler() { delete instance; }
        };
    static Handler handler;
    NotesManager2(){};
    ~NotesManager2();

public:


   ///Méthode retournant une référence sur la note correspondant à l'id fourni ou la version antérieure correspondante si une date est fournie
   /**
    * @param id : id de la note demandée
    * @param date : date correspondante à la version recherchée. Si la date est non renseignée, c'est la note active qui est recherchée.
    */
   note& getNote (const std::string& id, const std::string& date="");



   ///Méthode Supprimant une note possédant l'id fourni et les couples dans lesquels elle est impliquée
   /** Si une date est fournie, on supprime juste la version correspondante
    * sinon, la fonction vérifie parmi les relations si la note est impliquée dans des couples, si c'est le cas, les couples sont aussi supprimés.
    * @param id : id de la note demmandée
    * @param date : date correspondante à la version recherchée
    */
   void SupprimerNote (note& toDelete, const std::string& date="");

   ///Méthode qui charge les données du fichier xml et qui crée les objets qui y sont sauvegardés
   /**Appellée au lancement du programme.
    */
   void load();
   ///Méthode chargée de sauvegarder les objets de tous les managers dans le fichier xml.
   /** appelée pendant le destructeur, elle appelle les getManager() de chaque Manager afin d'accéder à leurs vector et sauvegarde leur contennu.
    *  Elle définit les balises du xml en fonction de l'objet à sauvegarder pour que load() puisse les reconnaitre.
    */
   void save(); // save notes in file filename

   /// Renvoie une référence sur le NotesManager2 si il existe déja, sinon, le créé. (Design pattern singleton)
   static NotesManager2& getManager();
   /// libère l'instance unique de NotesManager2. (Design pattern singleton)
   static void freeManager();
   ///Vérifie si les notes contiennent des références vers d'autres notes, et ajoute les couples dans la relation "références" le cas échéant.
   void checkReferences() const;

};

/// Classe fille héritant de Manager<Relation> et chargée des relations, elle dispose du Design Pattern Singleton.
class RelationManager : public Manager<Relation> {

private:


    struct Handler {
             RelationManager* instance; // pointeur sur l'unique instance
             Handler():instance(nullptr){}
            ~Handler() { delete instance; }
        };
    static Handler handler;
    RelationManager();
    ~RelationManager();



 public:
/// Renvoie une référence sur la relation possédant le titre fournit en paramètre. Déclence une Exception sinon la relation n'existe pas
  /**
    * @param titre : le titre de la relation à rechercher.
    */
    Relation& getRelation (const std::string& titre);
    ///ajoute une relation au vector du RelationManager
    /**
     * @param relation : référence sur la relation à ajouter.
     */
    void addRelation(Relation& relation);

    /// Renvoie une référence sur le RelationManager si il existe déja, sinon, le créé.(fait partie du singleton)
    static RelationManager& getManager();

    /// libère l'instance unique de RelationManager (Design pattern singleton)
    static void freeManager();
    ///le load général est défini dans NotesManager2
    void load() {}
     ///le save général est défini dans NotesManager2
    void save(){}


};
