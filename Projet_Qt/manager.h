﻿#ifndef MANAGER_H
#define MANAGER_H
#include <QString>
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include <vector>


#endif // MANAGER_H

template<class T>
class Manager {
protected :

   std::vector<T*> type;
   mutable  QString filename;

public:

    void add (T& a);
    void Supprimer (T& toDelete);
     const std::vector<T*> gettype() const {return type;}
   QString getFilename() const { return filename; }
   void setFilename(const QString& f) { filename=f; }

   Manager(){}

   virtual ~Manager<T>(){std::cout<<"manager(base) detruit"<<std::endl;}
   Manager(const Manager& m);
   Manager& operator=(const Manager& m);
   virtual void load () =0 ;
   virtual void save () =0 ;

};




class NotesManager2 :  public Manager<note> {

private :

public:

    struct Handler {
             NotesManager2* instance; // pointeur sur l'unique instance
             Handler():instance(nullptr){}
            ~Handler() { delete instance; }
        };
    static Handler handler;
   NotesManager2();
   ~NotesManager2();


   //NotesManager2(const NotesManager2& m);
   //NotesManager2& operator=(const NotesManager2& m);

   //void addNote (const QString& i, const QString& ti, const QString& te);//3


public:

   note& getNote (const std::string& id, const std::string& date="");
   note& getOldNote(const std::string& id);
   void SupprimerNote (note& toDelete, const std::string& date="");

   void load(); // load notes from file filename
   void save(); // save notes in file filename


   static NotesManager2& getManager();
   static void freeManager();

   void checkReferences() const;

};
