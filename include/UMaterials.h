
#ifndef UMaterials_h
#define UMaterials_h 1

#include <G4Material.hh>
#include <G4Element.hh>

using namespace CLHEP;

static G4double vacuumDensity = 1.e-25 * g / cm3;
static G4double pressure	   = 3.e-18 * pascal;
static G4double temperature   = 2.73   * kelvin;
static G4Material* vacuum = new G4Material("Galactic", 1., 1.01 * g / mole,
	vacuumDensity, kStateGas, temperature, pressure);



static G4Element* Titanium			= new G4Element("Titanium",		"Ti",	22., 47.867	*g/mole);
static G4Element* Tungsten			= new G4Element("Tungsten",		"W",	74., 183.84 *g/mole);
static G4Element* Lead				= new G4Element("Lead",			"Pb",	82., 207.2  *g/mole);
static G4Element* Copper			= new G4Element("Copper",		"Cu",	29., 63.546 *g/mole);

#endif
