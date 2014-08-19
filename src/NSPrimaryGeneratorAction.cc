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
  G4int boxNumber = Detector->GetShieldBoxNumber();
  G4double boxX, boxY, boxZ;
		boxX = Detector->GetShieldBoxSizeX();
		boxY = Detector->GetShieldBoxSizeY();
		boxZ = Detector->GetShieldBoxSizeZ();
	const G4ThreeVector* shieldBoxPosition = Detector->GetShieldBoxPosition();
	G4int box;
  G4double x0, y0, z0;

	// Now generate
  box =  int(boxNumber * G4UniformRand()); //random box
  x0 = (boxX * (G4UniformRand()-0.5)) + shieldBoxPosition[box].getX();
  y0 = (boxY * (G4UniformRand()-0.5)) + shieldBoxPosition[box].getY();
  z0 = (boxZ * (G4UniformRand()-0.5)) + shieldBoxPosition[box].getZ();

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

