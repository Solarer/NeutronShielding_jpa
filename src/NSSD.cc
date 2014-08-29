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

#include "NSSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"

#include "G4Track.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleTypes.hh"
#include "G4VProcess.hh"

NSSD::NSSD(const G4String& name,
           const G4String& hitsCollectionName)
 : G4VSensitiveDetector(name),
   fHitsCollection(NULL)
{
  collectionName.insert(hitsCollectionName);
}

NSSD::~NSSD() 
{ }

void NSSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection
  fHitsCollection 
    = new NSHitsCollection(SensitiveDetectorName, collectionName[0]); 

  // Add this collection in hce
  G4int hcID 
    = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection );

  // Create hit object
  fHitsCollection->insert(new NSHit());
}

G4bool NSSD::ProcessHits(G4Step* step, G4TouchableHistory*)
{
  // Get hit
  NSHit* hit = (*fHitsCollection)[0];
  if ( ! hit )
  {
    G4ExceptionDescription msg;
    msg << "Cannot access hit 0"; 
    G4Exception("NSSD::ProcessHits()",
      "MyCode0004", FatalException, msg);
  }

  // Count particle
  hit->SetEntSD(1);

	// Get particle name
	G4String particleName = step->GetTrack()->GetDefinition()->GetParticleName();

	// Get current particle energy
	G4double particleEnergy = step->GetTrack()->GetKineticEnergy();

	// Get material
	G4Material* stepMaterial = step->GetPreStepPoint()->GetMaterial();


	// Get photon response of material
	G4double photonFactor = 0;
	if(particleName == "e-" || particleName == "gamma")
		photonFactor = stepMaterial->GetMaterialPropertiesTable()->GetConstProperty("responseElectron");
	else if(particleName == "proton")
		photonFactor = stepMaterial->GetMaterialPropertiesTable()->GetProperty("responseProton")->GetEnergy(particleEnergy);
	else if(particleName == "alpha")
		photonFactor = stepMaterial->GetMaterialPropertiesTable()->GetProperty("responseAlpha")->GetEnergy(particleEnergy);
	else if(particleName == "carbon" || particleName == "C12")
		photonFactor = stepMaterial->GetMaterialPropertiesTable()->GetProperty("responseCarbon")->GetEnergy(particleEnergy);
	else if (particleName == "C13")
		G4cout << "C13"<< G4endl;
	else{
		photonFactor = 0;
		//G4cout << "ERROR: unknown particle '"<< particleName << "'" << G4endl;	
		}
	
	//G4cout <<G4endl<< particleName << G4endl << stepMaterial->GetName()<<G4endl;
	//G4cout << "particle Energy: " << particleEnergy/MeV << G4endl;
	//G4cout << "value: " << photonFactor << G4endl;

  // Total energy deposited in step
  G4double edep = step->GetTotalEnergyDeposit();
  if ( edep==0.) return false;

	G4double photon = edep*photonFactor;

	// Add everything to hit object
  hit->AddEdep(edep);
	hit->AddPhoton(photon);
	G4cout << "eDep: " << edep/MeV<< " MeV " << photon << " photons" << G4endl;
  return true;
}

void NSSD::EndOfEvent(G4HCofThisEvent*)
{
  // Print hits collection
  if (verboseLevel > 1)
  { 
     G4int nofHits = fHitsCollection->entries();
     G4cout << "\n-------->Hits Collection: in this event there are "
            << nofHits << " hits: " << G4endl;
     for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();
  }
}

