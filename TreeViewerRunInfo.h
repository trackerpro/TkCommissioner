#ifndef TREEVIEWERRUNINFO_H
#define TREEVIEWERRUNINFO_H

#include <QString>
#include <QPair>
#include <QVector>

#include <TFile.h>
#include <TH1F.h>
#include <TTree.h>
#include <TEventList.h>

#include <vector>

class TreeViewerRunInfo {

    private:
        QString currentRun;
        QString referenceRun;
        QString currentPartition;
        QString referencePartition;
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
        std::vector<TH1*> summaryHists;
	QVector<TTree*> currentFriendTrees;
	QVector<TTree*> referenceFriendTrees;

    public:
        TreeViewerRunInfo(const QString&);
        ~TreeViewerRunInfo();

        QString getCurrentRunNumber() const;
        QString getReferenceRunNumber() const;
        QString getCurrentPartition() const;
        QString getReferencePartition() const;
        QString getCurrentFileName() const;
        QString getReferenceFileName() const;
        QString getCurrentTreePath() const;
        QString getReferenceTreePath() const;
        QString getTmpFileName() const;
        TTree* getCurrentTree();
        TTree* getReferenceTree();
	QVector<TTree*> getCurrentFriendTrees();
	QVector<TTree*> getReferenceFriendTrees();
        TEventList* getEventList();
        void useEventList(bool);
        void closeTree(bool);
        void buildTreeInfo(QPair<QString, QString>, QPair<QString, QString>, bool);
        bool isRefTreeTypeSame();
	TFile* getCurrentFile(){return currentFile;}
	TFile* getReferenceFile(){return referenceFile;}
	TFile* getTmpFile(){ return tmpFile;}
};

#endif

