#ifndef UPrimaryGeneratorAction_h
#define UPrimaryGeneratorAction_h 1


#include <G4ParticleGun.hh>
#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4Event.hh>
#include <G4SystemOfUnits.hh>
#include <G4GenericMessenger.hh>

class UPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
	UPrimaryGeneratorAction();
	~UPrimaryGeneratorAction();

	void GeneratePrimaries(G4Event* anEvent);
	void setPower(G4double);

private:
	G4ParticleGun* gun;
	G4GenericMessenger* messenger;
	//AnalysisManager* analysis;
};

#endif