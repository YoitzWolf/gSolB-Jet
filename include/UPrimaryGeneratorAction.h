#ifndef UPrimaryGeneratorAction_h
#define UPrimaryGeneratorAction_h 1


#include <G4ParticleGun.hh>
#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4Event.hh>
#include <G4SystemOfUnits.hh>

class UPrimaryGeneratorAction : public G4VUserPrimaryGeneratorAction {
public:
	UPrimaryGeneratorAction();
	~UPrimaryGeneratorAction();

	void GeneratePrimaries(G4Event* anEvent);
private:
	G4ParticleGun* gun;
	//AnalysisManager* analysis;
};

#endif