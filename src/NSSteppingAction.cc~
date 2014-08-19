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

// This code was used to find out where the 0.477 peak was coming from.
// It outputs a file with step information for every particle and every secondary.
// Greatly increases run time!!! Leave commented out unless needed.

#include "NSSteppingAction.hh"
#include "NSEventAction.hh"
#include "NSDetectorConstruction.hh"
#include "NSRunAction.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "G4SteppingManager.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"

NSSteppingAction::NSSteppingAction(NSEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction)
{ }

NSSteppingAction::~NSSteppingAction()
{ }

void NSSteppingAction::UserSteppingAction(const G4Step* step)
{/*
  // Get step info
  G4int eventId = fEventAction->GetEventId();
  G4Track* track = step->GetTrack();
  G4int trackId = track->GetTrackID();
  G4int parentId = track->GetParentID();
  G4String volumeName 
    = step->GetPreStepPoint()->GetTouchableHandle()
      ->GetVolume()->GetLogicalVolume()->GetName();
  G4String particleName = track->GetDefinition()->GetParticleName();
  G4String processName
    = step->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName();
  G4double edep = step->GetTotalEnergyDeposit();

  outfileName = "step.out";

  // If file already exists, overwrite for new run
  if (eventId == 0 && trackId == 1)
  {
    outfile.open(outfileName, std::ofstream::out | std::ofstream::trunc);
    outfile.close();
  }

  outfile.open(outfileName, std::ofstream::out | std::ofstream::app);
  outfile << eventId << "\t" << trackId << " from " << parentId << "\t"
          << particleName << "\t" << processName << "\t" << volumeName << "\t"
          << edep << "\t" << G4endl;

  outfile.close();
*/
}


