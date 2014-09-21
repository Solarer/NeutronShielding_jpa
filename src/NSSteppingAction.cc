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
#include "NSVerboseMessenger.hh"

#include "G4Step.hh"
#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4LogicalVolume.hh"

#include "G4SteppingManager.hh"
#include "G4Track.hh"
#include "G4ios.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"


NSSteppingAction::NSSteppingAction(NSEventAction* eventAction)
: G4UserSteppingAction(),
  fEventAction(eventAction)
{
	fMessenger = new NSVerboseMessenger(this);
}

NSSteppingAction::~NSSteppingAction()
{ }

void NSSteppingAction::UserSteppingAction(const G4Step* theStep)
{
	if(fEventAction->DoOutputEvent()) 
	{
  outfile.open("temp.out", std::ofstream::out | std::ofstream::app);

	outfile << "Particle: " << theStep->GetTrack()->GetDefinition()->GetParticleName() << G4endl << "EventID: " << fEventAction->GetEventId() << " Parent/Track: " << theStep->GetTrack()->GetParentID() << "/" << theStep->GetTrack()->GetTrackID() << " Step is limited by '"
   << theStep->GetPostStepPoint()->GetProcessDefinedStep()->GetProcessName() ;
	outfile << "' in: " << theStep->GetPreStepPoint()->GetTouchableHandle()->GetVolume()->GetLogicalVolume()->GetName()<<G4endl;
	outfile << "ParticleEnergy: " << theStep->GetTrack()->GetKineticEnergy()/MeV << " MeV, Edep: " << theStep->GetTotalEnergyDeposit()/MeV << " MeV" << G4endl;
  outfile << "Processes involved to the step" << G4endl;
  G4StepStatus stepStatus = fpSteppingManager->GetfStepStatus();

  if(stepStatus==fAtRestDoItProc)
  {
    G4ProcessVector* procAtRest = fpSteppingManager->GetfAtRestDoItVector();
    G4SelectedAtRestDoItVector* selProcAtRest
     = fpSteppingManager->GetfSelectedAtRestDoItVector();
    size_t MAXofAtRestLoops = fpSteppingManager->GetMAXofAtRestLoops();
    for(size_t i1=0;i1<MAXofAtRestLoops;i1++)
    {
      if((*selProcAtRest)[MAXofAtRestLoops-i1-1]==2)
      { outfile << "  At rest : " << (*procAtRest)[i1]->GetProcessName() << " (forced)" << G4endl; }
      else if((*selProcAtRest)[MAXofAtRestLoops-i1-1]==1)
      { outfile << "  At rest : " << (*procAtRest)[i1]->GetProcessName() << G4endl; }
    }
  }

  if(stepStatus!=fExclusivelyForcedProc && stepStatus!=fAtRestDoItProc)
  {
    G4ProcessVector* procAlong = fpSteppingManager->GetfAlongStepDoItVector();
    size_t MAXofAlongStepLoops = fpSteppingManager->GetMAXofAlongStepLoops();
    for(size_t i2=0;i2<MAXofAlongStepLoops;i2++)
    {
      if((*procAlong)[i2]!=0)
      outfile << "  Along step : " << (*procAlong)[i2]->GetProcessName() << G4endl;
    }
  }

  if(stepStatus!=fAtRestDoItProc)
  {
    G4ProcessVector* procPost = fpSteppingManager->GetfPostStepDoItVector();
    G4SelectedPostStepDoItVector* selProcPost
     = fpSteppingManager->GetfSelectedPostStepDoItVector();
    size_t MAXofPostStepLoops = fpSteppingManager->GetMAXofPostStepLoops();
    for(size_t i3=0;i3<MAXofPostStepLoops;i3++)
    {
      if((*selProcPost)[MAXofPostStepLoops-i3-1]==2)
      { outfile << "  Post step : " << (*procPost)[i3]->GetProcessName() << " (forced)" << G4endl; }
      else if((*selProcPost)[MAXofPostStepLoops-i3-1]==1)
      { outfile << "  Post step : " << (*procPost)[i3]->GetProcessName() << G4endl; }
    }
  }

  G4int nSecAtRest = fpSteppingManager->GetfN2ndariesAtRestDoIt();
  G4int nSecAlong  = fpSteppingManager->GetfN2ndariesAlongStepDoIt();
  G4int nSecPost   = fpSteppingManager->GetfN2ndariesPostStepDoIt();
  G4int nSecTotal  = nSecAtRest+nSecAlong+nSecPost;
  G4TrackVector* secVec = fpSteppingManager->GetfSecondary();

  if(nSecTotal>0)
  {
    outfile << "  :----- List of 2ndaries - " << std::setw(3) << nSecTotal
           << " (Rest =" << std::setw(2) << nSecAtRest
           << ", Along =" << std::setw(2) << nSecAlong
           << ", Post ="  << std::setw(2) << nSecPost << ")" << G4endl;

    for(size_t lp1=(*secVec).size()-nSecTotal; lp1<(*secVec).size(); lp1++)
    {
      outfile << "    : "
             << G4BestUnit((*secVec)[lp1]->GetPosition(), "Length") << " "
             << std::setw( 9) << G4BestUnit((*secVec)[lp1]->GetKineticEnergy() , "Energy") << " "
             << std::setw(18) << (*secVec)[lp1]->GetDefinition()->GetParticleName()
             << " generated by " << (*secVec)[lp1]->GetCreatorProcess()->GetProcessName() << G4endl;
    }
  }
	outfile << G4endl;
  outfile.close();
	}

/*
	G4double kineticEnergy = step->GetTrack()->GetKineticEnergy();
  // Get step info
  if(true)
	{
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
          << "ParticleEnergy: " << track->GetKineticEnergy() << "edep: "<< edep << "\t" << G4endl;

  outfile.close();
	G4cout << "found Energy: " << kineticEnergy << " " << eventId << G4endl;
	}
*/
}

void NSSteppingAction::SetStepFileName(G4String fileName)
{
	outfileName = fileName;
}
