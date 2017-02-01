#include "TreeBuilder.h"
#include <TFile.h>
#include <TTree.h>
#include <iostream>

TreeBuilder::~TreeBuilder() {
}

TreeBuilder::TreeBuilder(): 
    currentFileName(""),
    referenceFileName(""),
    currentTreePath(""),
    referenceTreePath(""),
    tmpFileName(""),
    currentFile(NULL),
    referenceFile(NULL),
    tmpFile(NULL),
    currentTree(NULL),
    referenceTree(NULL)
{
    eventList = new TEventList("eventList", "eventList");
}

TreeBuilder::TreeBuilder(const QString& tmpFileName_, std::vector<QPair<QString, QString> > treePaths_): 
    currentFile(NULL),
    referenceFile(NULL),
    tmpFile(NULL),
    currentTree(NULL),
    referenceTree(NULL)
{
    buildTree(tmpFileName_, treePaths_);
}

QString TreeBuilder::getCurrentFileName() {
    return currentFileName;
}

QString TreeBuilder::getReferenceFileName() {
    return referenceFileName;
}

QString TreeBuilder::getCurrentTreePath() {
    return currentTreePath;
}

QString TreeBuilder::getReferenceTreePath() {
    return referenceTreePath;
}

QString TreeBuilder::getTmpFileName() {
    return tmpFileName;
}

TTree* TreeBuilder::getCurrentTree() {
    return currentTree;
}

TTree* TreeBuilder::getReferenceTree() {
    return referenceTree;
}

TEventList* TreeBuilder::getEventList() {
    return eventList;
}

void TreeBuilder::closeTree(bool save) {
    if (currentFile == NULL || tmpFile == NULL) return;
    if (save) {
        tmpFile->cd();
        if (referenceTree) referenceTree->Write();
        if (currentTree) currentTree->Write();
        tmpFile->Close();
    }
    else {
        tmpFile->cd();
        if (referenceTree) {
            referenceTree->Delete();
            currentTree->RemoveFriend(referenceTree);
        }            
        if (currentTree) currentTree->Delete();
        tmpFile->Close();
    }
    if (eventList) delete eventList;
}

void TreeBuilder::buildTree(const QString& tmpFileName_, std::vector<QPair<QString, QString> > treePaths_) {
    closeTree(false);

    if (treePaths_.size() == 0 || treePaths_.size() > 2) return;

    tmpFileName = tmpFileName_;
    currentFileName = treePaths_[0].first;
    currentTreePath = treePaths_[0].second;

    currentFile = new TFile(qPrintable(currentFileName));
    TTree* inputCurrentTree   = (TTree*)currentFile->Get(qPrintable(currentTreePath));

    if (inputCurrentTree) {
        tmpFile = new TFile(qPrintable(tmpFileName), "RECREATE");
        currentTree = inputCurrentTree->CloneTree(); 
        currentTree->SetName("currentTree");
        inputCurrentTree->Delete();
        currentFile->Close();
    }

    if (treePaths_.size() == 1) return;

    referenceFileName = treePaths_[1].first;
    referenceTreePath = treePaths_[1].second;
    if (referenceFileName != "" && referenceTreePath != "") {
        referenceFile = new TFile(qPrintable(referenceFileName));
        TTree* inputReferenceTree = (TTree*)referenceFile->Get(qPrintable(referenceTreePath));

        if (currentTree && inputReferenceTree) {
            tmpFile->cd();
            referenceTree = inputReferenceTree->CloneTree();
            referenceTree->SetName("referenceTree");
            inputReferenceTree->Delete();
            referenceFile->Close();
            currentTree->AddFriend(referenceTree, "ref");
        }
    }
}

void TreeBuilder::useEventList(bool flag) {
    if (flag) currentTree->SetEventList(eventList);
    else      currentTree->SetEventList(NULL);
}

bool TreeBuilder::isRefTreeTypeSame() {
    if (currentTree == NULL || referenceTree == NULL) return false;
    if (currentTree->GetListOfBranches()->GetEntries() != referenceTree->GetListOfBranches()->GetEntries()) return false;

    TObjArray* currentBranchList   = currentTree->GetListOfBranches();
    TObjArray* referenceBranchList = referenceTree->GetListOfBranches();
    for(Int_t i = 0; i < currentBranchList->GetEntries(); ++i ) {
        if (QString((static_cast<TBranch*>(currentBranchList->At(i))->GetName())) != QString((static_cast<TBranch*>(referenceBranchList->At(i))->GetName()))) return false;
    }

    return true;
}
