

#include "UMaterials.h"
#include "UDetectorConstruction.h"
#include "UDetector.h"

G4VPhysicalVolume* UDetectorConstruction::Construct() {

	// Standart Box World

	G4NistManager* nist = G4NistManager::Instance();
	nist->SetVerbose(1);

	G4double worldX = 0.2 * meter;
	G4double worldY = 0.1 * meter;
	G4double worldZ = 0.1 * meter;

	G4Box* worldSolid = new G4Box(
		"world", worldX, worldY, worldZ);
	// x = 5, y = 1, z = 1 meters

	G4LogicalVolume* worldLogic = new G4LogicalVolume(
		worldSolid, vacuum, "worldLogic");

	G4VPhysicalVolume* world = new G4PVPlacement(
		0, G4ThreeVector(0, 0, 0), worldLogic, "World_phys", 0, false, 0, true);

	//
	G4double thin = 10 * mm;
	auto mat = nist->FindOrBuildMaterial("G4_Ti");
	auto plate = MakePlate(mat, thin);
	//auto detector = MakeDetector();

	G4RotationMatrix* rotation = new G4RotationMatrix;
	rotation->rotateY(M_PI / 2. * rad);

	G4ThreeVector platePos = G4ThreeVector(0, 0, 0);
	new G4PVPlacement(rotation, platePos, plate.second, "Plate_phys",
		worldLogic,
		false, 0, true);

	G4ThreeVector detectorPos = G4ThreeVector(0, 0, thin);
	/*
	new G4PVPlacement(0, detectorPos, detector.second, "Detector_phys",
		plate.second,
		false, 0, true);
	*/

	G4double worldInnerX = (worldY - 1 * mm);
	G4double worldInnerY = (worldY - 1 * mm);
	G4double worldInnerZ = (worldY - 1 * mm);
	
	G4Box* soilidbox = new G4Box("solid_box", 5*mm, worldInnerY / 100, (worldInnerZ - 0.5 * mm) / 100);
	logicDetectorUnits = new G4LogicalVolume(soilidbox, vacuum, "logicDetectorUnits");

	logicDetectorUnits->SetVisAttributes(G4VisAttributes(G4Colour(0.6, 0, 0)));
	for (G4int i = 0; i < 100; i++) {
		for (G4int j = 0; j < 100; j++) {
			//+ (worldY / 100) * (i+0.5)
			//+ (worldZ / 100) * (j + 0.5)
			G4VPhysicalVolume* pDet = new G4PVPlacement(
				0,
				G4ThreeVector(-worldX + 10*mm, -worldInnerY + 2 * worldInnerY * (i) / 100, -(worldInnerZ - 0.5 * mm) + 2 * (worldInnerZ - 0.5 * mm) * (j)/100),
				logicDetectorUnits, "phys_detect", worldLogic, false, j + i * 100, false
			);
		}
	}



	return world;
}

std::pair<G4Box*, G4LogicalVolume*> UDetectorConstruction::MakeDetector()
{
		
	G4NistManager* nist = G4NistManager::Instance();
	nist->SetVerbose(1);

	// Define each individual element
	// Define Nitrogen
	G4double A = 14.01 * g / mole;
	G4double Z = 7;
	G4Element* elN = new G4Element("Nitrogen", "N", Z, A);

	// Define Oxygen
	A = 16.0 * g / mole;
	Z = 8;
	G4Element* elO = new G4Element("Oxygen", "O", Z, A);

	// Define Hydrogen
	A = 1.01 * g / mole;
	Z = 1;
	G4Element* elH = new G4Element("Hydrogen", "H", Z, A);

	// Define Carbon
	A = 12.01 * g / mole;
	Z = 6;
	G4Element* elC = new G4Element("Carbon", "C", Z, A);

	// Define PMMA (C502H8) ~ Оргстекло
	G4Material* PMMA = new G4Material("PMMA", 1.19 * g / cm3, 3);
	PMMA->AddElement(elC, 5);
	PMMA->AddElement(elO, 2);
	PMMA->AddElement(elH, 8);

	G4Material* silicon = nist->FindOrBuildMaterial("G4_Si");
	G4Material* SiO2 = nist->FindOrBuildMaterial("G4_SILICON_DIOXIDE");


	//G4MaterialPropertiesTable* mpt_siO2 = new G4MaterialPropertiesTable();
	//mpt_siO2->AddProperty("RINDEX", );


	G4double SV_thick = 25. * um / 2.;
	// um = 1e-6m
	G4double PMMA_x = 100. * mm; // um = 1e-6m
	G4double PMMA_y = 100. * mm;
	G4double PMMA_z = SV_thick;


	G4Box* PMMA_box = new G4Box("PMMA_box", PMMA_x, PMMA_y, PMMA_z);
	G4LogicalVolume* logical_PMMA = new G4LogicalVolume(PMMA_box, PMMA, "PMMA_log", 0, 0, 0);

	G4VisAttributes PMMAColour(G4Colour(0., 1., 0.));
	//PMMAColour.SetForceSolid(true);
	logical_PMMA->SetVisAttributes(PMMAColour);
	
	// Si02 layer
	G4double oxyde_x = PMMA_x;
	G4double oxyde_y = PMMA_y;
	G4double oxyde_z = 1. * um / 2.;

	G4Box* oxyde_box = new G4Box("oxyde_box", oxyde_x, oxyde_y, oxyde_z);

	G4LogicalVolume* logical_oxyde = new G4LogicalVolume(oxyde_box, SiO2, "oxyde_log", 0, 0, 0);
	G4ThreeVector oxyde_position = G4ThreeVector(0, oxyde_z, -(PMMA_z + oxyde_z));
	
	G4VisAttributes oxydeColour(G4Colour(0.5, 0., 0.5));
	oxydeColour.SetForceSolid(true);
	logical_oxyde->SetVisAttributes(oxydeColour);

	new G4PVPlacement(0, oxyde_position, logical_oxyde, "oxyde_phys",
		logical_PMMA,
		false, 0, true);

	

	return {PMMA_box, logical_PMMA};
}


std::pair<G4Box*, G4LogicalVolume*> UDetectorConstruction::MakePlate(G4Material* material, G4double thin) {
	G4double plate_x = 100. * mm;
	G4double plate_y = 100. * mm;
	G4double plate_z = thin;

	G4Box* plate_box = new G4Box(material->GetName()+"_platebox", plate_x, plate_y, plate_z);

	G4LogicalVolume* plate_logic = new G4LogicalVolume(plate_box, material, material->GetName() + "_platelogic", 0, 0, 0);

	G4VisAttributes plateColour(G4Colour(0., 0.9, 0.9));
	plateColour.SetForceWireframe(true);
	plate_logic->SetVisAttributes(plateColour);

	return { plate_box, plate_logic};

}

void UDetectorConstruction::ConstructSDandField() {
	USensitiveDetector* sensDet = new USensitiveDetector("SensitiveDetector_1");
	logicDetectorUnits->SetSensitiveDetector(sensDet);


}