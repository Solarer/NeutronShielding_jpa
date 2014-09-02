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

  // Particle entered sensitive detector
  hit->SetEntSD(1);

  // Total energy deposited in step
  G4double edep = step->GetTotalEnergyDeposit();
  if ( edep==0.) return false;

	// Get particle name
	G4String particleName = step->GetTrack()->GetDefinition()->GetParticleName();

	// Get current particle energy
	G4double particleEnergy = step->GetPreStepPoint()->GetKineticEnergy();

	// Get material
	G4Material* stepMaterial = step->GetPreStepPoint()->GetMaterial();


	// Get photon response of material (determine particle first)
	G4double photonFactor = 0/MeV;
	G4PhysicsOrderedFreeVector* property = NULL;

	if(particleName == "e-" || particleName == "e+" || particleName == "gamma")
		photonFactor = stepMaterial->GetMaterialPropertiesTable()->GetConstProperty("responseElectron");
	else if(particleName == "proton")
		property = stepMaterial->GetMaterialPropertiesTable()->GetProperty("responseProton");
	else if(particleName == "deuteron")
		photonFactor = stepMaterial->GetMaterialPropertiesTable()->GetConstProperty("responseDeuteron");
	else if(particleName == "alpha")
		property = stepMaterial->GetMaterialPropertiesTable()->GetProperty("responseAlpha");
	else if(particleName == "C12" || particleName == "C13")
		property = stepMaterial->GetMaterialPropertiesTable()->GetProperty("responseCarbon");
	else{
		photonFactor = 0;
		G4cerr<< "ERROR: unknown particle '"<< particleName << "'" << G4endl;	
		}
	// now set photon response with linear fit (delta E = 1keV) in #photons/MeV
	if(property != NULL)		// photonFactor not set
	{
		if(particleEnergy < property->GetMinValue())
			photonFactor = (property->GetEnergy(property->GetMinValue()))/(0.1*MeV);
		else if(particleEnergy+1*keV >= property->GetMaxValue())
			photonFactor = (property->GetEnergy(property->GetMaxValue())-property->GetEnergy(property->GetMaxValue()-1*keV))/(1*keV);
		else 
			photonFactor = (property->GetEnergy(particleEnergy+1*keV)-property->GetEnergy(particleEnergy))/(1*keV);
	}

static int k=1;
	if(edep!=particleEnergy){
		G4cout << "not total "<< -(edep-particleEnergy)/MeV << "MeV " <<k << G4endl;
k++;
}
	G4cout <<G4endl<< particleName << G4endl << "Material: " << stepMaterial->GetName()<<G4endl;
	G4cout << "particle Energy: " << particleEnergy/MeV << "MeV" << G4endl;
	G4cout << "Energyloss: " << edep/MeV <<"MeV"<< G4endl;
	if(property!=NULL)
	{
		G4cout << "Val1: " << property->GetEnergy(particleEnergy) << " Val2: " << property->GetEnergy(particleEnergy+1*keV) <<G4endl<<G4endl;
    G4cout << "MinVal: " << property->GetMinLowEdgeEnergy()<<G4endl;
		G4cout << "PhotonFactor: " << photonFactor << G4endl;
	}
	G4cout << "eDep: " << edep/MeV<< " MeV " << edep*photonFactor << " photons" << G4endl;

	

	G4double photon = edep*photonFactor;

	// Add everything to hit object
  hit->AddEdep(edep);
	hit->AddPhoton(photon);
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

