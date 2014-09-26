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
#include "NSRunAction.hh"
#include "NSSD.hh"
#include "NSHit.hh"
#include "NSAnalysis.hh"

#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4SDManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"

#include "Randomize.hh"
#include <iomanip>
#include "G4ios.hh"
#include <fstream>

NSEventAction::NSEventAction()
: G4UserEventAction(),
  fcennsHCID(-1)
{
    runAct = (NSRunAction*)(G4RunManager::GetRunManager()->GetUserRunAction());
}

NSEventAction::~NSEventAction()
{}

NSHitsCollection* NSEventAction::GetHitsCollection(G4int hcID, const G4Event* event) const
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

	// output for this event?
  doOutputEvent = runAct->IsNextEvent(eventID);

	if(doOutputEvent)
	{
    // set outputstatus and get final outputFile name
    outputFile = runAct->GetOutputFile();

		// clear temp outputfile
		std::ofstream outfile;
		outfile.open("temp.out", std::ios::out | std::ios::trunc );
		outfile.close();
	}
		
  //event count output
  if((eventID+1<1000 && eventID+1%100==0) || eventID+1%1000==0)
		G4cout << "Reached " << eventID+1 << " event. Continue..." << G4endl;
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

  // Get analysis manager
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();

  // Do this, if we are currently collecting events and
  // the current event is interesting
    if(runAct->GetDoCollectEvents())
    {
        G4double edep = cennsHit->GetEdep(); 
        G4bool collectThis = false;
        G4String file;
        if(edep>2.25*MeV && edep<2.35*MeV)
        {
            collectThis = true;
            file = "2.2MEV";
        }
        else if(edep>1.9*MeV && edep<2.15*MeV)
        {
            collectThis = true;
            file = "2.1MEV";
        }
        else if(edep>.25*MeV && edep<.42*MeV)
        {
            collectThis = true;
            file = "0MEV";
        }

		if(collectThis)
		{
			G4cout << "collecting: " << eventID << " " << file << G4endl;
    
        std::ofstream outfile;
        outfile.open("criticalEventIDs", std::ios::app);

        outfile << eventID << "\t" << file << std::endl;
		}
    }
	// append temp output to final output
    else if(doOutputEvent)
	{
		std::ifstream infile;
		std::ofstream outfile;
		std::string buffer;
		
		infile.open("temp.out");
		outfile.open(outputFile, std::ios::app);

		outfile << "\n\n---------------------------------------------\nEvent found: " << cennsHit->GetEdep()/MeV << " MeV Energy deposition\n---------------------------------------------\n" << G4endl;

		while(!infile.eof()) 
    	{
	      getline(infile,buffer);
		  	outfile << buffer << G4endl;
      }
		
		outfile.close();
		infile.close();

		if(!runAct->PopEvent())  // pop processed Event ID from vector
			G4RunManager::GetRunManager()->AbortRun(); //stop if it was the last ID
	}

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
  G4double primEnergy = (primary->GetKineticEnergy());
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
  analysisManager->FillNtupleDColumn(1,2, x0);
  analysisManager->FillNtupleDColumn(1,3, y0);
  analysisManager->FillNtupleDColumn(1,4, z0);
  analysisManager->FillNtupleDColumn(1,5, primEnergy);
  analysisManager->FillNtupleDColumn(1,6, dx);
  analysisManager->FillNtupleDColumn(1,7, dy);
  analysisManager->FillNtupleDColumn(1,8, dz);
  analysisManager->AddNtupleRow(1);

  if(cennsHit->GetEntSD() == 1) // only if a particle entered the SD
	{
		// Fill ntuple id=2
  	analysisManager->FillNtupleDColumn(2,0, cennsHit->GetEdep());
  	analysisManager->FillNtupleDColumn(2,1, cennsHit->GetPhoton()/11499.9/keV); // change to keVee
  	analysisManager->FillNtupleDColumn(2,2, cennsHit->GetFirstContact());
  	analysisManager->AddNtupleRow(2);
  	
		// Fill ntuple id=3
  	analysisManager->FillNtupleIColumn(3,0, cennsHit->GetGamma());
  	analysisManager->FillNtupleIColumn(3,1, cennsHit->GetElectron());
  	analysisManager->FillNtupleIColumn(3,2, cennsHit->GetProton());
  	analysisManager->FillNtupleIColumn(3,3, cennsHit->GetDeuteron());
  	analysisManager->FillNtupleIColumn(3,4, cennsHit->GetAlpha());
  	analysisManager->FillNtupleIColumn(3,5, cennsHit->GetCarbon());
  	analysisManager->FillNtupleIColumn(3,6, cennsHit->GetOther());
  	analysisManager->FillNtupleIColumn(3,7, cennsHit->GetTotal());
  	analysisManager->AddNtupleRow(3);
	}
}
