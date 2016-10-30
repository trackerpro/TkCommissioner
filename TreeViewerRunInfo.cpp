#include "TreeViewerRunInfo.h"
#include <TFile.h>
#include <TTree.h>
#include <iostream>

TreeViewerRunInfo::~TreeViewerRunInfo() {
    if (tmpFile) {
        if (tmpFile->IsOpen()) tmpFile->Close();
        delete tmpFile;
    }
    if (eventList) delete eventList;
}

TreeViewerRunInfo::TreeViewerRunInfo(const QString& tmpFileName_):
    currentFileName(""),
    referenceFileName(""),
    currentTreePath(""),
    referenceTreePath(""),
    tmpFileName(tmpFileName_),
    currentFile(NULL),
    referenceFile(NULL),
    currentTree(NULL),
    referenceTree(NULL)
{
    if (tmpFileName_ != "") tmpFile = new TFile(qPrintable(tmpFileName), "RECREATE"); 
    eventList = new TEventList("eventList", "eventList");
}

QString TreeViewerRunInfo::getCurrentRunNumber() const {
    return currentRun;
}

QString TreeViewerRunInfo::getReferenceRunNumber() const {
    return referenceRun;
}

QString TreeViewerRunInfo::getCurrentPartition() const {
    return currentPartition;
}

QString TreeViewerRunInfo::getReferencePartition() const {
    return referencePartition;
}

QString TreeViewerRunInfo::getCurrentFileName() const {
    return currentFileName;
}

QString TreeViewerRunInfo::getReferenceFileName() const {
    return referenceFileName;
}

QString TreeViewerRunInfo::getCurrentTreePath() const {
    return currentTreePath;
}

QString TreeViewerRunInfo::getReferenceTreePath() const {
    return referenceTreePath;
}

QString TreeViewerRunInfo::getTmpFileName() const {
    return tmpFileName;
}

TTree* TreeViewerRunInfo::getCurrentTree() {
    return currentTree;
}

TTree* TreeViewerRunInfo::getReferenceTree() {
    return referenceTree;
}

TEventList* TreeViewerRunInfo::getEventList() {
    return eventList;
}

void TreeViewerRunInfo::closeTree(bool save) {
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
}

void TreeViewerRunInfo::buildTreeInfo(QPair<QString, QString> runid_, QPair<QString, QString> treePath_, bool isCurrent) {
    if (!tmpFile || !tmpFile->IsOpen()) return;

    if (isCurrent) {
        currentRun = runid_.second;
        currentPartition = runid_.first;
        currentFileName = treePath_.first;
        currentTreePath = treePath_.second;
        
        currentFile = new TFile(qPrintable(currentFileName));
        TTree* inputCurrentTree   = (TTree*)currentFile->Get(qPrintable(currentTreePath));
        
        if (inputCurrentTree) {
            tmpFile->cd();
            if (currentTree) {
                if (referenceTree) currentTree->RemoveFriend(referenceTree);
                currentTree->Delete();
            }
            currentTree = inputCurrentTree->CloneTree();
            currentTree->SetName("currentTree");
            inputCurrentTree->Delete();
            currentFile->Close();
            if (referenceTree) currentTree->AddFriend(referenceTree, "ref");
        }
    }

    else {
        referenceRun = runid_.second;
        referencePartition = runid_.first;
        referenceFileName = treePath_.first;
        referenceTreePath = treePath_.second;
        
        referenceFile = new TFile(qPrintable(referenceFileName));
        TTree* inputReferenceTree = (TTree*)referenceFile->Get(qPrintable(referenceTreePath));
        
        if (inputReferenceTree) {
            tmpFile->cd();
            if (referenceTree) {
                if (currentTree) currentTree->RemoveFriend(referenceTree);
                referenceTree->Delete();
            }
            referenceTree = inputReferenceTree->CloneTree();
            referenceTree->SetName("referenceTree");
            inputReferenceTree->Delete();
            referenceFile->Close();
            if (currentTree) currentTree->AddFriend(referenceTree, "ref");
        }
    }
}

void TreeViewerRunInfo::useEventList(bool flag) {
    if (flag) currentTree->SetEventList(eventList);
    else      currentTree->SetEventList(NULL);
}

bool TreeViewerRunInfo::isRefTreeTypeSame() {
    if (currentTree == NULL || referenceTree == NULL) return false;
    if (currentTree->GetListOfBranches()->GetEntries() != referenceTree->GetListOfBranches()->GetEntries()) return false;

    TObjArray* currentBranchList   = currentTree->GetListOfBranches();
    TObjArray* referenceBranchList = referenceTree->GetListOfBranches();
    for(Int_t i = 0; i < currentBranchList->GetEntries(); ++i ) {
        if (QString((static_cast<TBranch*>(currentBranchList->At(i))->GetName())) != QString((static_cast<TBranch*>(referenceBranchList->At(i))->GetName()))) return false;
    }

    return true;
}

