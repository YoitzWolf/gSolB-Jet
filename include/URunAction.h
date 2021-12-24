#ifndef RunAction_h
#define RunAction_h 1

#include <G4UserRunAction.hh>
#include <g4root.hh>

class URunAction : public G4UserRunAction {
public:
	URunAction();
	~URunAction();

	virtual void BeginOfRunAction(const G4Run*);
	virtual void EndOfRunAction(const G4Run*);

//private:
	//G4AnalysisManager* man;
};

#endif