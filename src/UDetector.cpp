
#include "UDetector.h"

#include <G4RunManager.hh>


USensitiveDetector::USensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{
	
}

USensitiveDetector::~USensitiveDetector(){

}

G4bool USensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory* story) {
	
	G4Track* track = step->GetTrack();
	track->SetTrackStatus(fStopAndKill);

	G4StepPoint* preStepPoint	= step->GetPreStepPoint();
	G4StepPoint* postStepPoint	= step->GetPostStepPoint();

	G4ThreeVector particle_position = preStepPoint->GetPosition();

	//G4cout << "Particle position:: " << particle_position << G4endl; ;

	const G4VTouchable* tch = step->GetPreStepPoint()->GetTouchable();
	G4int copyNumber = tch->GetCopyNumber(); // detector taken the position
	G4VPhysicalVolume* pv = tch->GetVolume();
	G4ThreeVector detectorPosition = pv->GetTranslation(); // detector position

	auto e = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
	G4AnalysisManager* man = G4AnalysisManager::Instance();
	man->FillNtupleIColumn(0, e);
	man->FillNtupleDColumn(1, detectorPosition[0]);
	man->FillNtupleDColumn(2, detectorPosition[1]);
	man->FillNtupleDColumn(3, detectorPosition[2]);
	man->AddNtupleRow(0);
	return false;
}