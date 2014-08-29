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

#include "NSDetectorMessenger.hh"
#include "NSDetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithADouble.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithoutParameter.hh"

NSDetectorMessenger::NSDetectorMessenger(NSDetectorConstruction* Det)
 : G4UImessenger(),
   fDetectorConstruction(Det)
{
  // Directories

  fNSDirectory = new G4UIdirectory("/NS/");
  fNSDirectory->SetGuidance("UI commands specific to this project.");

  fDetDirectory = new G4UIdirectory("/NS/det/");
  fDetDirectory->SetGuidance("Detector construction control");

  // Detector size commands


  // Detector materials commands


  // Update command, MUST be applied before "beamOn"
  fUpdateCmd = new G4UIcmdWithoutParameter("/NS/det/update",this);
  fUpdateCmd->SetGuidance("Update geometry.");
  fUpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  fUpdateCmd->SetGuidance("if you changed geometrical value(s).");
  fUpdateCmd->AvailableForStates(G4State_Idle);
}

NSDetectorMessenger::~NSDetectorMessenger()
{
  //delete fShieldSizeCmd;
  //delete fShield2RatioCmd;
  //delete fDetRatioCmd;

  //delete fWorldMatCmd;
  //delete fShieldMatCmd;
  //delete fShield2MatCmd;
  //delete fDetMatCmd;

  delete fUpdateCmd;

  delete fNSDirectory;
  delete fDetDirectory;
}

void NSDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
  // Detector size commands

  if( command == fDetRatioCmd ) {
    fDetectorConstruction
      ->SetDetRatio(fDetRatioCmd->GetNewDoubleValue(newValue));
  }

  // Detector materials commands

  if( command == fWorldMatCmd )
   { fDetectorConstruction->SetWorldMat(newValue);}

  if( command == fShieldMatCmd )
   { fDetectorConstruction->SetShieldMat(newValue);}

  if( command == fDetMatCmd )
   { fDetectorConstruction->SetDetMat(newValue);}

  // Update command, MUST be applied before "beamOn"
  if( command == fUpdateCmd )
   { fDetectorConstruction->UpdateGeometry(); }
}

