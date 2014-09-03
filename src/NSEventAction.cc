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

#include "NSEventAction.hh"
#include "NSSD.hh"
#include "NSHit.hh"
#include "NSAnalysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"

#include "Randomize.hh"
#include <iomanip>

NSEventAction::NSEventAction()
: G4UserEventAction(),
  fcennsHCID(-1)
{ } 

NSEventAction::~NSEventAction()
{ }

NSHitsCollection* NSEventAction::GetHitsCollection(G4int hcID,
                                  const G4Event* event) const
{
  // Get hits collection
  NSHitsCollection* hitsCollection 
    = static_cast<NSHitsCollection*>( event->GetHCofThisEvent()->GetHC(hcID) );

  // Error message
  if ( ! hitsCollection ) 
	{
    G4ExceptionDescription msg;
    msg << "Cannot access hitsCollection ID " << hcID; 
    G4Exception("NSEventAction::GetHitsCollection()",
      "MyCode0003", FatalException, msg);
  }         
  return hitsCollection;
}    

void NSEventAction::PrintEventStatistics(G4double Edep) const
{
  // Print event statistics
  G4cout
     << "   Total energy: " 
     << std::setw(7) << G4BestUnit(Edep, "Energy")
     << G4endl;
}

void NSEventAction::BeginOfEventAction(const G4Event* event)
{
  // Get event ID
  eventID = event->GetEventID();
}

void NSEventAction::EndOfEventAction(const G4Event* event)
{

  // Get hits collections IDs (only once)
  if ( fcennsHCID == -1 )
  {
    fcennsHCID 
      = G4SDManager::GetSDMpointer()->GetCollectionID("CennsHitsCollection");
  }

  // Get hits collection
  NSHitsCollection* cennsHC = GetHitsCollection(fcennsHCID, event);

  // Get hit
  NSHit* cennsHit = (*cennsHC)[cennsHC->entries()-1];

  // Print per event (modulo n)
  G4int verboseLevel = G4RunManager::GetRunManager()->GetVerboseLevel();
  if (verboseLevel > 0)
  {
    G4int printModulo = 1000;
    if ( ( printModulo > 0 ) && ( eventID % printModulo == 0 ) )
    {
      G4cout << "---> End of event: " << eventID << G4endl;     
      PrintEventStatistics(cennsHit->GetEdep());
    }
  }

  // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Fill histograms
  analysisManager->FillH1(1, cennsHit->GetEntSD());  	// number entering detector
  analysisManager->FillH1(2, cennsHit->GetEdep());   	// energy deposition
  analysisManager->FillH1(3, cennsHit->GetPhoton());  // photons created

  // Get the primary position/direction information
  G4PrimaryParticle* primary = event->GetPrimaryVertex(0)->GetPrimary(0);

	G4double ID = eventID;
  G4double x0 = (event->GetPrimaryVertex()->GetX0());
  G4double y0 = (event->GetPrimaryVertex()->GetY0());
  G4double z0 = (event->GetPrimaryVertex()->GetZ0());
  G4double px = (primary->GetPx());
  G4double py = (primary->GetPy());
  G4double pz = (primary->GetPz());

  // Calculate initial direction from momentum
  G4double ptot = sqrt(px*px + py*py + pz*pz);
  G4double dx = px / ptot;
  G4double dy = py / ptot;
  G4double dz = pz / ptot;

  // Fill ntuple id=1
  analysisManager->FillNtupleIColumn(1,0, ID);
  analysisManager->FillNtupleIColumn(1,1, cennsHit->GetEntSD());
  analysisManager->FillNtupleDColumn(1,2, cennsHit->GetEdep());
  analysisManager->FillNtupleDColumn(1,3, x0);
  analysisManager->FillNtupleDColumn(1,4, y0);
  analysisManager->FillNtupleDColumn(1,5, z0);
  analysisManager->FillNtupleDColumn(1,6, dx);
  analysisManager->FillNtupleDColumn(1,7, dy);
  analysisManager->FillNtupleDColumn(1,8, dz);
  analysisManager->AddNtupleRow(1);

  // Fill ntuple id=2
  if(cennsHit->GetEntSD() == 1) // only if a particle entered the SD
	{
  	analysisManager->FillNtupleIColumn(2,0, cennsHit->GetGamma());
  	analysisManager->FillNtupleIColumn(2,1, cennsHit->GetElectron());
  	analysisManager->FillNtupleIColumn(2,2, cennsHit->GetProton());
  	analysisManager->FillNtupleIColumn(2,3, cennsHit->GetDeuteron());
  	analysisManager->FillNtupleIColumn(2,4, cennsHit->GetAlpha());
  	analysisManager->FillNtupleIColumn(2,5, cennsHit->GetCarbon());
  	analysisManager->FillNtupleIColumn(2,6, cennsHit->GetOther());
  	analysisManager->AddNtupleRow(2);
	}
}
