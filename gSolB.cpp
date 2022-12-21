// gSolB.cpp : Defines the entry point for the application.
//
#pragma once

#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "G4UIExecutive.hh"
#include "G4VisExecutive.hh"

#include "include/UDetectorConstruction.h"
#include "include/UPhysicsList.h"
#include "include/UActionInitialization.h"
#include "include/UMaterials.h"
#include "include/CSVSaver.h"



using namespace std;

int main(int argc, char* argv[])
{

	auto table = CSVTable::getWriter();
	table->set_dir("./OUTPUT/CUSTOM/");
	
	//bool g = table.get();
	//table->open_file("BASE.txt");
	//table.close();
	bool a;
	//std::cin >> a;
	
	// construct the default run manager
	auto runManager = G4RunManagerFactory::CreateRunManager();
	
	int nThreads = 4;
	runManager->SetNumberOfThreads(nThreads);

	auto detector_constr = new UDetectorConstruction();
	detector_constr->baseConfig();
	// set mandatory initialization classes
	runManager->SetUserInitialization(detector_constr);
	runManager->SetUserInitialization(new UPhysicsList() );
	runManager->SetUserInitialization(new UActionInitialisation() );

	// initialize G4 kernel
	runManager->Initialize();

	// start a run
	//int numberOfEvent = 1;
	//runManager->BeamOn(numberOfEvent);

	// Graphic Visualisation
	G4VisManager* visManager = new G4VisExecutive();
	visManager->Initialize();

	// interactive mode : define UI session
	G4UIExecutive* ui = new G4UIExecutive(argc, argv, "csh");
	

	G4UImanager* UIManager = G4UImanager::GetUIpointer();
	UIManager->ApplyCommand("/control/execute cll.mac");

	



	ui->SessionStart();
	delete ui;
	

	// job termination
	delete visManager;
	delete runManager;
	return 0;
}