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

#include "NSRunMessenger.hh"
#include "NSRunAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithABool.hh"

NSRunMessenger::NSRunMessenger(NSRunAction* run)
:Action(run)
{
  fNSDirectory = new G4UIdirectory("/NS/");
  fNSDirectory->SetGuidance("UI commands specific to this project.");

  fRunDirectory = new G4UIdirectory("/NS/run/");
  fRunDirectory->SetGuidance("Run action control");

  fSingleRunFileNameCmd =
    new G4UIcmdWithAString("/NS/run/setSingleRunFileName", this);
  fSingleRunFileNameCmd->SetGuidance("Enter the name of files for one run");
  fSingleRunFileNameCmd->SetParameterName("singleRunFileName",false);
  fSingleRunFileNameCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  fSteppingFileNameCmd =
    new G4UIcmdWithAString("/NS/run/setSteppingFileName", this);
  fSingleRunFileNameCmd->SetGuidance("Enter the name of file for output");
  fSingleRunFileNameCmd->SetParameterName("steppingFileName",false);
  fSingleRunFileNameCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  fDoCollectEventsCmd =
    new G4UIcmdWithABool("/NS/run/doCollectEvents", this);
  fSingleRunFileNameCmd->SetGuidance("Want to collect interesting Events for output?");
  fSingleRunFileNameCmd->SetParameterName("doCollectEventsCmd",false);
  fSingleRunFileNameCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

  fDoProcessEventsCmd =
    new G4UIcmdWithABool("/NS/run/doProcessEvents", this);
  fSingleRunFileNameCmd->SetGuidance("Want to process previously collected Events?");
  fSingleRunFileNameCmd->SetParameterName("doProcessEventsCmd",false);
  fSingleRunFileNameCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

NSRunMessenger::~NSRunMessenger()
{
  delete fDoCollectEventsCmd;
  delete fDoProcessEventsCmd;
  delete fSingleRunFileNameCmd;
  delete fSteppingFileNameCmd;
  delete fNSDirectory;
  delete fRunDirectory;
}

void NSRunMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{ 
 /* if( command == fSingleRunFileNameCmd )
  { Action->SetSingleRunFileName(newValue); }
  if( command == fSteppingFileNameCmd )
 // { Action->SetSteppingFileName(newValue); }*/
  if( command == fDoCollectEventsCmd)
  { 
    Action->SetCollectEvents(newValue); 
		if(newValue)
    	Action->SetProcessEvents(!newValue); 
  }
  if( command == fDoProcessEventsCmd)
  { 
    Action->SetProcessEvents(newValue); 
		if(newValue)
    	Action->SetCollectEvents(!newValue); 
  }
}

