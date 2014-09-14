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


#include "NSVerboseMessenger.hh"

#include "G4SteppingManager.hh"
#include "G4UnitsTable.hh"

NSVerboseMessenger::NSVerboseMessenger(NSSteppingAction* stA)
:StepAction(stA)
{
  // Directories
  fNSDirectory = new G4UIdirectory("/NS/");
  fNSDirectory->SetGuidance("UI commands specific to this project.");

  fGenDirectory = new G4UIdirectory("/NS/verbose/");
  fGenDirectory->SetGuidance("Primary verbose action control");

  // Command to choose which shield the primary particles are generated in
  fStepFileNameCmd= new G4UIcmdWithAString("/NS/verbose/setStepFile", this);
  fStepFileNameCmd->SetGuidance("Write Step output to a file?");
  fStepFileNameCmd->SetParameterName("stepFile",false);
  fStepFileNameCmd->AvailableForStates(G4State_Idle);


NSVerboseMessenger::~NSVerboseMessenger()
{
	delete fRunDirectory;
	delete fNSDirectory;
	delete fSingleRunFileNameCmd;
	delete fStepFileNameCmd;
}
 
void NSVerboseMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
	if( command == fStepFileNameCmd )
  { 
		StepAction->SetStepFileName(newValue); 
	}
}
