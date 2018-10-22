#include "TreeViewerRunInfo.h"
#include <TFile.h>
#include <TTree.h>
#include <TROOT.h>
#include <TKey.h>
#include <iostream>
#include <TFriendElement.h>

TreeViewerRunInfo::~TreeViewerRunInfo() {

  if (eventList) delete eventList;  
  if (tmpFile) {
    if (tmpFile->IsOpen()){
      tmpFile->Close();
      delete tmpFile;
    }
  }
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

QVector<TTree*> TreeViewerRunInfo::getCurrentFriendTrees(){
  return currentFriendTrees;
} 
QVector<TTree*> TreeViewerRunInfo::getReferenceFriendTrees(){
  return referenceFriendTrees;
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
    for(int itree = 0; itree < currentFriendTrees.size(); itree++){
      if(currentFriendTrees.at(itree)) currentFriendTrees.at(itree)->Write();
    }
    for(int itree = 0; itree < referenceFriendTrees.size(); itree++){
      if(referenceFriendTrees.at(itree)) referenceFriendTrees.at(itree)->Write();
    }
  }
  else {

    tmpFile->cd();
    if (referenceTree) {
      currentTree->RemoveFriend(referenceTree);
      for(int itree = 0; itree < referenceFriendTrees.size(); itree++){
	if(referenceFriendTrees.at(itree)){
	  referenceTree->RemoveFriend(referenceFriendTrees.at(itree));
	  if(currentFriendTrees.size() > itree)
	    referenceFriendTrees.at(itree)->RemoveFriend(currentFriendTrees.at(itree));
	}
      }
    }
    
    if (currentTree) {
      for(int itree = 0; itree < currentFriendTrees.size(); itree++){
      	if(currentFriendTrees.at(itree)) {
      	  currentTree->RemoveFriend(currentFriendTrees.at(itree));
      	}
      }
    }
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
    
    if (inputCurrentTree) { // tree found
      if (currentTree) {
	if (referenceTree) currentTree->RemoveFriend(referenceTree);
	for(int itree = 0; itree < currentFriendTrees.size(); itree++){
	  if(currentFriendTrees.at(itree)) delete currentFriendTrees.at(itree);
	}
	delete currentTree;
	currentFriendTrees.clear();
      }
      
      tmpFile->cd();      
      currentTree = inputCurrentTree->CloneTree();      
      currentTree->SetName("currentTree");
      
      // Add friends      
      TIter next(currentFile->GetListOfKeys());    
      TKey* key;    
      while ((key = (TKey*)next())){
	TClass *cl = gROOT->GetClass(key->GetClassName());
	if (!cl->InheritsFrom("TTree")) continue;
	TTree *tree = (TTree*)key->ReadObj();	
	if(not tree or not TString(tree->GetName()).Contains("friend")) continue;
	currentFriendTrees.push_back(tree->CloneTree());
	currentTree->AddFriend(currentFriendTrees.back());
	currentTree->BuildIndex("DeviceId");
	currentFriendTrees.back()->BuildIndex("DeviceId");
	delete tree;
      }

      // Get list of friends
      delete inputCurrentTree;
      currentFile->Close();      
      if (referenceTree){
	referenceTree->BuildIndex("DeviceId");
	currentTree->AddFriend(referenceTree, "ref");
      }
      for(int itree = 0; itree < referenceFriendTrees.size(); itree++){
	if(currentFriendTrees.size() > itree and currentFriendTrees.at(itree) and referenceFriendTrees.at(itree)){
      	  currentFriendTrees.at(itree)->AddFriend(referenceFriendTrees.at(itree),"ref");
	  referenceFriendTrees.at(itree)->BuildIndex("DeviceId");
	  currentFriendTrees.at(itree)->BuildIndex("DeviceId");
	}
      }
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
      if (referenceTree) {
	if (currentTree) currentTree->RemoveFriend(referenceTree);
	for(int itree = 0; itree < referenceFriendTrees.size(); itree++){
	  if(currentFriendTrees.size() > itree)
	    referenceFriendTrees.at(itree)->RemoveFriend(currentFriendTrees.at(itree));
	  if(referenceFriendTrees.at(itree)) delete referenceFriendTrees.at(itree);
	}
	referenceFriendTrees.clear();
	delete referenceTree;
      }

      tmpFile->cd();
      referenceTree = inputReferenceTree->CloneTree();
      referenceTree->SetName("referenceTree");
      referenceTree->BuildIndex("DeviceId");
      TIter next(referenceFile->GetListOfKeys());    
      TKey* key;    
      while ((key = (TKey*)next())){
	TClass *cl = gROOT->GetClass(key->GetClassName());
	if (!cl->InheritsFrom("TTree")) continue;
	TTree *tree = (TTree*)key->ReadObj();
	if(not tree or not TString(tree->GetName()).Contains("friend")) continue;
	referenceFriendTrees.push_back(tree->CloneTree());
	referenceTree->AddFriend(referenceFriendTrees.back());	
	referenceFriendTrees.back()->BuildIndex("DEviceId");
	delete tree;
      }      
      delete inputReferenceTree;
      referenceFile->Close();
      if (currentTree) currentTree->AddFriend(referenceTree, "ref");
      for(int itree = 0; itree < referenceFriendTrees.size(); itree++){
      	if(currentFriendTrees.size() > itree and referenceFriendTrees.at(itree) and currentFriendTrees.at(itree))
      	  currentFriendTrees.at(itree)->AddFriend(referenceFriendTrees.at(itree),"ref");
      }
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

