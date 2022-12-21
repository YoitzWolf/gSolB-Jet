
#ifndef UPhysicsList_h
#define UPhysicsList_h 1


#include "G4VModularPhysicsList.hh"
#include "G4IonFluctuations.hh"
#include "G4IonParametrisedLossModel.hh"
#include "G4EmProcessOptions.hh"
#include "G4HadronPhysicsQGSP_BIC_HP.hh"
#include "G4RadioactiveDecayPhysics.hh"

class UPhysicsList : public G4VModularPhysicsList {
public:
	UPhysicsList();
	~UPhysicsList();
};

#endif