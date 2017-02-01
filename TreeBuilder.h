#ifndef BASICTREEBUILDER_H
#define BASICTREEBUILDER_H

#include <QString> 
#include <QPair> 
#include <TFile.h>
#include <TTree.h>
#include <TEventList.h>
#include <vector>

class TreeBuilder {

    private:
        QString currentFileName;
        QString referenceFileName;
        QString currentTreePath;
        QString referenceTreePath;
        QString tmpFileName;
        TFile* currentFile;
        TFile* referenceFile;
        TFile* tmpFile;
        TTree* currentTree;
        TTree* referenceTree;
        TEventList* eventList;

    public:
        TreeBuilder();
        ~TreeBuilder();
        TreeBuilder(const QString&, std::vector<QPair<QString, QString> >);

        QString getCurrentFileName();
        QString getReferenceFileName();
        QString getCurrentTreePath();
        QString getReferenceTreePath();
        QString getTmpFileName();
        TTree* getCurrentTree();
        TTree* getReferenceTree();
        TEventList* getEventList();
        void useEventList(bool);
        void closeTree(bool);
        void buildTree(const QString&, std::vector<QPair<QString, QString> >);
        bool isRefTreeTypeSame();
};

#endif
