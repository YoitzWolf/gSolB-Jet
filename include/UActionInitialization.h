
#ifndef UActionInitialisation_h
#define UActionInitialisation_h 1

#include <G4VUserActionInitialization.hh>
#include <G4RunManager.hh>

#include "UPrimaryGeneratorAction.h"

class UActionInitialisation : public G4VUserActionInitialization {
public:
    virtual void Build() const;
};
#endif