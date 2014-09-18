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

#include "NINSNPrimaryGeneratorMessenger.hh"
#include "NINSNPrimaryGeneratorAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAnInteger.hh"

NINSNPrimaryGeneratorMessenger::NINSNPrimaryGeneratorMessenger(
                                          NINSNPrimaryGeneratorAction* Gun)
:Action(Gun)
{
  // Directories

  fNINSNDirectory = new G4UIdirectory("/NINSN/");
  fNINSNDirectory->SetGuidance("UI commands specific to this project.");

  fGenDirectory = new G4UIdirectory("/NINSN/gen/");
  fGenDirectory->SetGuidance("Primary generator action control");

  // Command to choose which shield the primary particles are generated in
  fGenInShieldCmd = new G4UIcmdWithAnInteger("/NINSN/gen/genInShield", this);
  fGenInShieldCmd->SetGuidance("Generate particles in which shield layer?");
  fGenInShieldCmd->SetParameterName("genInShield",false);
  fGenInShieldCmd->AvailableForStates(G4State_Idle);

  // Command to choose evaporation spectrum
  fGenEvaporationCmd = new G4UIcmdWithAnInteger("/NINSN/gen/genEvaporation", this);
  fGenEvaporationCmd->SetGuidance("Generate particles with evaporation spectrum?");
  fGenEvaporationCmd->SetParameterName("genEvaporation",false);
  fGenEvaporationCmd->AvailableForStates(G4State_Idle);


}

NINSNPrimaryGeneratorMessenger::~NINSNPrimaryGeneratorMessenger()
{
  delete fGenInShieldCmd;
  delete fNINSNDirectory;
  delete fGenDirectory;
}

void NINSNPrimaryGeneratorMessenger::SetNewValue(
                                        G4UIcommand* command, G4String newValue)
{ 
  if( command == fGenInShieldCmd )
  { Action->SetGenInShield(fGenInShieldCmd->GetNewIntValue(newValue)); }

  if( command == fGenEvaporationCmd )
  { Action->SetGenEvaporation(fGenEvaporationCmd->GetNewIntValue(newValue)); }

}
