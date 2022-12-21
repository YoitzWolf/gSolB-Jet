
#ifndef UDetector_h
#define UDetector_h 1

#include "G4VSensitiveDetector.hh"

#include "g4root.hh"

class USensitiveDetector : public G4VSensitiveDetector {
public:
	USensitiveDetector(G4String);
	~USensitiveDetector();

private:
	virtual G4bool ProcessHits(G4Step*, G4TouchableHistory*);
};


#endif