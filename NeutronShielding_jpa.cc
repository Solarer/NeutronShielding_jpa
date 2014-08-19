//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//

// This is the main program for the Neutron Shielding project.

#include "NSDetectorConstruction.hh"
#include "NSPrimaryGeneratorAction.hh"
#include "NSRunAction.hh"
#include "NSEventAction.hh"
#include "NSSteppingAction.hh"

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#include "G4UImanager.hh"

#include "QGSP_BIC_HP.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "Randomize.hh"

int main(int argc, char** argv)
{
  // Choose the Random engine
  CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);

  // User Verbose output class
//  G4VSteppingVerbose* verbosity = new NSSteppingVerbose;
//  G4VSteppingVerbose::SetInstance(verbosity);

  // Construct the default run manager
#ifdef G4MULTITHREADED
  G4MTRunManager* runManager = new G4MTRunManager;
#else
  G4RunManager* runManager = new G4RunManager;
#endif

  // Set mandatory initialization classes

  // Detector Construction
  NSDetectorConstruction* detector = new NSDetectorConstruction;
  runManager->SetUserInitialization(detector);

  // Physics List
  G4VModularPhysicsList* physicsList = new QGSP_BIC_HP;
  runManager->SetUserInitialization(physicsList);
  physicsList->SetVerboseLevel(0);

  // Set mandatory user action classes
  NSPrimaryGeneratorAction* gen_action = new NSPrimaryGeneratorAction(detector);
  runManager->SetUserAction(gen_action);

  NSRunAction* run_action = new NSRunAction;
  runManager->SetUserAction(run_action);

  NSEventAction* event_action = new NSEventAction;
  runManager->SetUserAction(event_action);

  NSSteppingAction* stepping_action = new NSSteppingAction(event_action);
  runManager->SetUserAction(stepping_action);

  // Initialize G4 kernel
  runManager->Initialize();

  #ifdef G4VIS_USE
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
  #endif    
     
  // Get the pointer to the User Interface manager
  G4UImanager * UImanager = G4UImanager::GetUIpointer();  

  if (argc!=1)   // batch mode  
    {
      G4String command = "/control/execute ";
      G4String fileName = argv[1];
      UImanager->ApplyCommand(command+fileName);
    }
  else           // interactive mode : define UI session
    { 
#ifdef G4UI_USE
      G4UIExecutive * ui = new G4UIExecutive(argc,argv);
#ifdef G4VIS_USE
      UImanager->ApplyCommand("/control/execute vis.mac");     
#endif
      ui->SessionStart();
      delete ui;
#endif
    }


  // Job termination
  //
  // Free the store: user actions, physics_list and detector_description are
  //                 owned and deleted by the run manager, so they should not
  //                 be deleted in the main() program !
  //
#ifdef G4VIS_USE
  delete visManager;
#endif  
  delete runManager;
//  delete verbosity;

  return 0;
}

