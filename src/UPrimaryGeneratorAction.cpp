#include <G4RunManager.hh>

#include "UPrimaryGeneratorAction.h"
#include "CSVSaver.h"
#include <string>

UPrimaryGeneratorAction::UPrimaryGeneratorAction() { 
	this->gun = new G4ParticleGun();

	G4ParticleTable* pTable = G4ParticleTable::GetParticleTable();
	G4String ProtonName = "proton";
	G4String ElectronName = "e-";

	G4ParticleDefinition* proton = pTable->FindParticle(ProtonName);
	G4ParticleDefinition* electron = pTable->FindParticle(ElectronName);

	G4ThreeVector pos(0.9 * meter, 0., 0.);
	G4ThreeVector mom(-1., 0., 0.);

	gun->SetParticlePosition(pos);
	gun->SetParticleMomentumDirection(mom);
	gun->SetParticleMomentum(1 * GeV); // Kinetic Energy
	gun->SetParticleDefinition(electron);

	this->messenger = new G4GenericMessenger(
		this, "/primaryGenerator/",
		"UPrimaryGeneratorAction messenger"
	);
	messenger->DeclareMethod(
		"set_gun_power",
		&UPrimaryGeneratorAction::setPower,
		"Gun power useage"
	);
}

void UPrimaryGeneratorAction::setPower(G4double s) {
	gun->SetParticleMomentum(s * GeV); // Kinetic Energy
	CSVTable::globals["energy"] = std::to_string(s);
}

UPrimaryGeneratorAction::~UPrimaryGeneratorAction()
{
	delete gun;
}

void UPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	

	gun->GeneratePrimaryVertex(anEvent);

	/*
	#ifdef ANALYSIS_USE
		G4double energy = gun->GetParticleEnergy();
		analysis->SetPrimaryEnergy(energy);
	#endif
	*/
}