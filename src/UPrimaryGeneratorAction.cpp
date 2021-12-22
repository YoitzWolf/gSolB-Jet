#include <G4RunManager.hh>

#include "UPrimaryGeneratorAction.h"


UPrimaryGeneratorAction::UPrimaryGeneratorAction() { 
	this->gun = new G4ParticleGun();
}

UPrimaryGeneratorAction::~UPrimaryGeneratorAction()
{
	delete gun;
}

void UPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	G4ParticleTable* pTable = G4ParticleTable::GetParticleTable();
	G4String ProtonName = "proton";
	G4String ElectronName = "e-";
	
	G4ParticleDefinition* proton	= pTable->FindParticle(ProtonName);
	G4ParticleDefinition* electron	= pTable->FindParticle(ElectronName);
	
	G4ThreeVector pos(0.9*meter, 0., 0.);
	G4ThreeVector mom(-1., 0., 0.);

	gun->SetParticlePosition(pos);
	gun->SetParticleMomentumDirection(mom);
	gun->SetParticleMomentum(5 *GeV); // Kinetic Energy
	gun->SetParticleDefinition(electron);

	gun->GeneratePrimaryVertex(anEvent);

	/*
	#ifdef ANALYSIS_USE
		G4double energy = gun->GetParticleEnergy();
		analysis->SetPrimaryEnergy(energy);
	#endif
	*/
}