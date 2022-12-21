

#ifndef UDetectorConstruction_h
#define UDetectorConstruction_h 1

#include <utility>
#include <corecrt_math_defines.h>
#include <vector>

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"

#include "G4SystemOfUnits.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4SystemOfUnits.hh"

#include "G4GenericMessenger.hh"

#include "UMaterials.hpp"

class UDetectorConstruction: public G4VUserDetectorConstruction {
public:

    G4VPhysicalVolume* Construct();
    std::pair<G4Box*, G4LogicalVolume*> MakeDetector();
    std::pair<G4Box*, G4LogicalVolume*> MakePlate(G4Material* material, G4double thin);
    void baseConfig();
    UDetectorConstruction();
    void setMaterial(G4String);
    void setThickness(G4double);

private:
    std::vector<G4VPhysicalVolume*> physucal_volumes;
    G4LogicalVolume* logicDetectorUnits;
    virtual void ConstructSDandField();

    G4Box* worldSolid;
    G4LogicalVolume* worldLogic;
    G4VPhysicalVolume* world;

    G4double plateThick;
    G4Material* plateMaterial;

    G4Box* soilidbox;

    G4GenericMessenger* messenger;
};



#endif