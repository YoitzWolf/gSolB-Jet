

#include "URunAction.h"
#include "CSVSaver.h"

#include <G4Run.hh>
#include <string>

#include <direct.h>

URunAction::URunAction() {
	G4AnalysisManager* man = G4AnalysisManager::Instance();


	man->CreateNtuple("Hits", "Hits List");
	man->CreateNtupleIColumn("fEvent");
	man->CreateNtupleSColumn("Type");
	man->CreateNtupleDColumn("X");
	man->CreateNtupleDColumn("Y");
	man->CreateNtupleDColumn("Z");
	man->CreateNtupleDColumn("Energy");
	man->FinishNtuple(0);

	_mkdir("./OUTPUT");
}

URunAction::~URunAction() {

}

void URunAction::BeginOfRunAction(const G4Run* run) {
	G4AnalysisManager* man = G4AnalysisManager::Instance();
	int rn = run->GetRunID();
	auto table = CSVTable::getWriter();
	table->open_file("Pb-" + CSVTable::globals["energy"] +"GeV" + CSVTable::globals["thickness"] + "mm-id" + std::to_string(rn) + ".csv");
	
	man->OpenFile("./OUTPUT/out"+ std::to_string(rn) + ".root");

	
}

void URunAction::EndOfRunAction(const G4Run*) {
	G4AnalysisManager* man = G4AnalysisManager::Instance();
	man->Write();
	man->CloseFile();

	auto table = CSVTable::getWriter();
	table->close();
}