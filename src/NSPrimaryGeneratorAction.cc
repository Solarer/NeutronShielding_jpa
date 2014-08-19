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


#include "NSPrimaryGeneratorAction.hh"
#include "NSDetectorConstruction.hh"
#include "NSPrimaryGeneratorMessenger.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

NSPrimaryGeneratorAction::NSPrimaryGeneratorAction(NSDetectorConstruction* DC)
: Detector(DC)
{
  // Construct messenger
  fMessenger = new NSPrimaryGeneratorMessenger(this);

  // Construct particle gun
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // Choose default volume to generate paticles in (Shield1)
  genInShield = 1;

  // Default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="neutron");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(1.*MeV);
}

NSPrimaryGeneratorAction::~NSPrimaryGeneratorAction()
{
  delete fMessenger;
  delete fParticleGun;
}

void NSPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //event counter for output
  static unsigned long event_cnt=1;
  //this function is called at the begining of each event
  //
  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get Envelope volume
  // from G4LogicalVolumeStore.

  // Get detector configuration sizes
  G4double detRatio       = Detector->GetDetRatio();
  G4double det_sizeXY     = detRatio*shield1_sizeXY;
  G4double det_sizeZ      = detRatio*shield1_sizeZ;
  
  // Only generate particles in appropriate volume
  G4int inDet = 0;
  G4int inShield2 = 0;
  G4double x0, y0, z0;
  x0 = y0 = z0 = 0;
	// Check if it is possible to generate particles in current shield
	if(shield1_sizeXY == shield2_sizeXY && shield1_sizeZ == shield2_sizeZ)
		{
			SetGenInShield(2); //no shield1
			G4cerr << "Warning: shield2 overlaps completely with shield1! Now generating particles in shield2!" << G4endl;
		}
	else if(shield2_sizeXY == det_sizeXY && shield2_sizeZ == det_sizeZ)
		{
			SetGenInShield(1); //no shield2
			G4cerr << "Warning: Detector overlaps completely with shield2! Now generating particles in shield1!" << G4endl;
		}

	// Now generate
  if (genInShield == 2)        // generate particles in shield2
  {
    while (inDet == 0)
    {
      x0 = shield2_sizeXY * (G4UniformRand()-0.5);
      y0 = shield2_sizeXY * (G4UniformRand()-0.5);
      z0 = shield2_sizeZ  * (G4UniformRand()-0.5);

      if (fabs(x0)>det_sizeXY/2. ||
          fabs(y0)>det_sizeXY/2. ||
          fabs(z0)>det_sizeZ/2.)
      {
        inDet = 1;
      }
    }
  }

  else  if (genInShield == 1)  // generate particles in shield1
  {
    while (inShield2 == 0)
    {
      x0 = shield1_sizeXY * (G4UniformRand()-0.5);
      y0 = shield1_sizeXY * (G4UniformRand()-0.5);
      z0 = shield1_sizeZ * (G4UniformRand()-0.5);

      if (fabs(x0)>shield2_sizeXY/2. ||
          fabs(y0)>shield2_sizeXY/2. ||
          fabs(z0)>shield2_sizeZ /2.)
      {
        inShield2 = 1;
      }
    }
  }

  else
  {
    G4cout << "Invalid shield number" << G4endl;
  }

  // Set primary particle position
  fParticleGun->SetParticlePosition(G4ThreeVector(x0,y0,z0));

  // Isotropic in direction
  G4double phi = 2.*CLHEP::pi*G4UniformRand();
  G4double costh = 2.*G4UniformRand()-1;
  G4double th = acos(costh);

  G4double dx = cos(phi)*sin(th);
  G4double dy = sin(phi)*sin(th);
  G4double dz = costh;

  // Set primary particle direction
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(dx,dy,dz));

  // Generate a particle
  fParticleGun->GeneratePrimaryVertex(anEvent);

  //event count output
  if(event_cnt%100==0)
	G4cout << "Reached " << event_cnt << " event mark. Ongoing..." << G4endl;
  event_cnt++;
}

void NSPrimaryGeneratorAction::SetGenInShield (G4int value)
{
  // Set which shield the particles are generated in
  genInShield = value;
}

