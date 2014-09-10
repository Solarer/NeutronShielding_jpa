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


#include "NINSNPrimaryGeneratorAction.hh"
#include "NINSNDetectorConstruction.hh"
#include "NINSNPrimaryGeneratorMessenger.hh"

#include "G4ParticleGun.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"

#include "G4SystemOfUnits.hh"
#include "Randomize.hh"

NINSNPrimaryGeneratorAction::NINSNPrimaryGeneratorAction(NINSNDetectorConstruction* DC)
: Detector(DC)
{
  // Construct messenger
  fMessenger = new NINSNPrimaryGeneratorMessenger(this);

  // Construct particle gun
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // Choose default volume to generate particles in (Shield1)
  genInShield = 1;

  // Choose default: no evaporation spectrum

  genEvaporation = 0;

  // Default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="neutron");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(1.*MeV);
}

NINSNPrimaryGeneratorAction::~NINSNPrimaryGeneratorAction()
{
  delete fMessenger;
  delete fParticleGun;
}

void NINSNPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
  //this function is called at the beginning of each event
  //
  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get Envelope volume
  // from G4LogicalVolumeStore.

  // Get detector configuration sizes
  G4double shield1_sizeXY = Detector->GetShield1SizeXY();
  G4double shield1_sizeZ  = Detector->GetShield1SizeZ();
  G4double shield2Ratio   = Detector->GetShield2Ratio();
  G4double shield2_sizeXY = shield2Ratio*shield1_sizeXY;
  G4double shield2_sizeZ  = shield2Ratio*shield1_sizeZ;
  G4double detRatio       = Detector->GetDetRatio();
  G4double det_sizeXY     = detRatio*shield1_sizeXY;
  G4double det_sizeZ      = detRatio*shield1_sizeZ;
  
  // Only generate particles in appropriate volume
  G4int inDet = 0;
  G4int inShield2 = 0;
  G4double x0, y0, z0;
  x0 = y0 = z0 = 0;

  if (genInShield == 2)        // generate particles in shield2
  {
    if (shield2_sizeXY<0 || shield2_sizeZ<0) {
      G4cout << "Shield 2 does not exist! "<<G4endl;
      return;
    }
    while (inDet == 0)
    {
      x0 = shield2_sizeXY * (G4UniformRand()-0.5);
      y0 = shield2_sizeXY * (G4UniformRand()-0.5);
      z0 = shield2_sizeZ  * (G4UniformRand()-0.5);

      if (fabs(x0)>det_sizeXY/2. ||
          fabs(y0)>det_sizeXY/2. ||
          fabs(z0)>det_sizeZ /2.)
      {
        inDet = 1;
      }
    }
  }

  else  if (genInShield == 1)  // generate particles in shield1
  {

   
    G4double inner_gensizeXY = shield2_sizeXY;
    G4double inner_gensizeZ= shield2_sizeZ;

    // If no shield2, use detector size for generation range
    if (shield2_sizeXY<0 || shield2_sizeZ<0) {
      inner_gensizeXY= det_sizeXY;
      inner_gensizeZ= det_sizeZ;
    }

    while (inShield2 == 0)
    {
      x0 = shield1_sizeXY * (G4UniformRand()-0.5);
      y0 = shield1_sizeXY * (G4UniformRand()-0.5);
      z0 = shield1_sizeZ * (G4UniformRand()-0.5);

      if (fabs(x0)>inner_gensizeXY/2. ||
          fabs(y0)>inner_gensizeXY/2. ||
          fabs(z0)>inner_gensizeZ /2.)
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

  if (genEvaporation == 1) {

  // Select from random evaporation spectrum
    G4double evapEnergy = NINSNPrimaryGeneratorAction::GetEvaporationEnergy();
    
    fParticleGun->SetParticleEnergy(evapEnergy*MeV);

  }

  // Set primary particle direction
  fParticleGun->SetParticleMomentumDirection(G4ThreeVector(dx,dy,dz));

  // Generate a particle
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

void NINSNPrimaryGeneratorAction::SetGenInShield (G4int value)
{
  // Set which shield the particles are generated in
  genInShield = value;
}


void NINSNPrimaryGeneratorAction::SetGenEvaporation (G4int value)
{
  // Set which shield the particles are generated in
  genEvaporation = value;
}

G4double NINSNPrimaryGeneratorAction::GetEvaporationEnergy(void) {

  G4double evapEnergy=1.;

  // Stolen from HALO code; integral MC method
  // I am not sure this gives quite the right spectrum ?

  const G4int nBins = 13;

  G4double Edistrib[nBins][2] = {
   {0.138,  .25},
   {0.391,  .75},
   {0.557, 1.25},
   {0.687, 1.75},
   {0.791, 2.25},
   {0.866, 2.75},
   {0.923, 3.25},
   {0.957, 3.75},
   {0.977, 4.25},
   {0.989, 4.75},
   {0.994, 5.25},
   {0.998, 5.75},
   {1.000, 6.25}
   } ; 


  G4int i=0;
  G4double rnum = G4UniformRand();
  while (Edistrib[i][0]< rnum) {
    i++;
  }

  evapEnergy = Edistrib[i][1];
  return evapEnergy;

}
