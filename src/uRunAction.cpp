

#include "URunAction.h"


URunAction::URunAction() {

}

URunAction::~URunAction() {

}

void URunAction::BeginOfRunAction(const G4Run*) {
	G4AnalysisManager* man = G4AnalysisManager::Instance();
	man->OpenFile("out.root");

	man->CreateNtuple("Hits", "Hits List");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleDColumn("X");
	man->CreateNtupleDColumn("Y");
	man->CreateNtupleDColumn("Z");
	man->FinishNtuple(0);
}

void URunAction::EndOfRunAction(const G4Run*) {
	G4AnalysisManager* man = G4AnalysisManager::Instance();
	man->Write();
	man->CloseFile();
}