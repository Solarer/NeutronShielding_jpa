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

  // Total energy deposited in step
  G4double edep = step->GetTotalEnergyDeposit();
  if ( edep==0.) return false;

	G4double temp = (step->GetPostStepPoint()->GetGlobalTime());
/*	if(temp>5000*ns)		// 5 micro seconds cutoff
		return false;
*/
	// Get scintillator ID
	G4ThreeVector position = step->GetPreStepPoint()->GetPosition();
	G4int scinID; 
	if(position.x()<0)
	{
		if(position.y()<0)
			scinID = 0;
		else
			scinID = 1;
	}
	else
	{
		if(position.y()<0)
			scinID = 2;
		else
			scinID = 3;
	}
	// Get particle name
	G4String particleName = step->GetTrack()->GetDefinition()->GetParticleName();


	// Get current particle energy
	G4double particleEnergy = step->GetPreStepPoint()->GetKineticEnergy();

	// Get material
	G4Material* stepMaterial = step->GetPreStepPoint()->GetMaterial();


	// Get photon response of material (determine particle first)
	G4double photon = 0;
	G4PhysicsOrderedFreeVector* property = NULL;


	if(stepMaterial->GetMaterialPropertiesTable() == NULL)
	{
		G4cerr << "ERROR: no propertiesTable for material defined" << G4endl;
		photon = 0;
	}
	else
	{
		if(particleName == "e-" || particleName == "e+" || particleName == "gamma")
			photon = stepMaterial->GetMaterialPropertiesTable()->GetConstProperty("responseElectron")*edep;
		else if(particleName == "proton")
			photon = stepMaterial->GetMaterialPropertiesTable()->GetConstProperty("responseElectron")*edep/10;
			//property = stepMaterial->GetMaterialPropertiesTable()->GetProperty("responseProton");
		else if(particleName == "deuteron")
			photon= stepMaterial->GetMaterialPropertiesTable()->GetConstProperty("responseDeuteron")*edep*0;
		else if(particleName == "alpha")
			photon = 0;
			//property = stepMaterial->GetMaterialPropertiesTable()->GetProperty("responseAlpha");
		else if(particleName == "C12" || particleName == "C13")
			photon = stepMaterial->GetMaterialPropertiesTable()->GetConstProperty("responseElectron")*edep/100;
			//property = stepMaterial->GetMaterialPropertiesTable()->GetProperty("responseCarbon");
		else
			{
			photon = 0;
			//	G4cerr<< "ERROR: unknown particle '"<< particleName << "'" << G4endl;	
			}
	}

	// now set photon response if not already set
	if(property != NULL)
	{
		if(particleEnergy < property->GetMinValue())
			photon = property->GetEnergy(property->GetMinValue())/(property->GetMinValue())*edep;
		else
			photon = property->GetEnergy(particleEnergy)-property->GetEnergy(particleEnergy-edep);
	}

	// split energy deposition in particle categories for investigation	
		if(particleName == "e-" || particleName == "e+" || particleName=="gamma")
				hit->AddElectron(photon);

			else if(particleName == "proton")
				hit->AddProton(photon);

			else if(particleName == "deuteron")
				hit->AddDeuteron(photon);

			else if(particleName == "alpha")
				hit->AddAlpha(photon);

			else if(particleName == "C12" || particleName == "C13")
				hit->AddCarbon(photon);

			else
				hit->AddOther(photon);

	// Add everything to hit object
  hit->AddEdep(edep,scinID);
	hit->AddPhoton(photon,scinID);

	if(hit->GetPhoton(scinID)>30*11499.9/1000)		// 30keVee threshold in current SD
		{
			// Timestamp
  		if(hit->GetFirstContact() == -1)
			{
				// else...
				// Entered sensitive detector
				hit->SetFirstContact(temp);
			}
  		hit->SetEntSD(1,scinID);	
		}
  return true;
}

void NSSD::EndOfEvent(G4HCofThisEvent*)
{
	// reset Vector
	
  // Print hits collection
  if (verboseLevel > 1)
  { 
     G4int nofHits = fHitsCollection->entries();
     G4cout << "\n-------->Hits Collection: in this event there are "
            << nofHits << " hits: " << G4endl;
     for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();
  }
}

