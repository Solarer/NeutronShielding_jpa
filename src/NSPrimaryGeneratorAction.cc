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
: Detector(DC),genEvaporation(0), primaryParticleEnergy(10), genTwoNeutrons(0)
{
  // Construct messenger
  fMessenger = new NSPrimaryGeneratorMessenger(this);

  // Construct particle gun
  G4int n_particle = 1;
  fParticleGun  = new G4ParticleGun(n_particle);

  // Choose default volume to generate paticles in 
  genInLead = true;

  // Default particle kinematic
  G4ParticleTable* particleTable = G4ParticleTable::GetParticleTable();
  G4String particleName;
  G4ParticleDefinition* particle
    = particleTable->FindParticle(particleName="neutron");
  fParticleGun->SetParticleDefinition(particle);
  fParticleGun->SetParticleEnergy(primaryParticleEnergy*MeV);
}

NSPrimaryGeneratorAction::~NSPrimaryGeneratorAction()
{
  delete fMessenger;
  delete fParticleGun;
}

void NSPrimaryGeneratorAction::GeneratePrimaries(G4Event* anEvent)
{
	// particle position
  G4double x0, y0, z0;
	G4double detX, detY, detZ, detLowerPart;
	G4double holeX, holeY, holeZ;
	holeX= holeY = Detector->GetHoleSizeXY();
	holeZ = Detector->GetHoleSizeZ();
	detX = detY = Detector->GetDetSizeXY();
	detZ = Detector->GetDetSizeZ();
	detLowerPart = Detector->GetDetLowerPart();

  //this function is called at the begining of each event
  //
  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get Envelope volume
  // from G4LogicalVolumeStore.

	if(true) // generate in lead
	{
		G4double scinRad, scinHeight;
		G4double muonVetoThick = Detector->GetMuonVetoThick();
		scinRad = Detector->GetScinRadOut2();
		scinHeight = Detector->GetScinHeight();

		// check if there is space to generate a particle
		if(detZ<=scinHeight && detX*detX+detY*detY <= scinRad*scinRad)
			G4cerr << "ERROR: no free space to generate particle!!! Change detector geometry!" << G4endl;
		
		while(1) // generate, until particle not in scintillator
		{
			// generate at radom position in one quarter of the detector...
  		x0 = detX/2 * (G4UniformRand()-0.5);
  		y0 = detY/2 * (G4UniformRand()-0.5);
  		z0 = detZ   * (G4UniformRand()-0.5) - 0.5*holeZ + 0.5*detZ + muonVetoThick;
			
			// ... until the particle is not inside of a scintilator
			if((x0)*(x0)+(y0)*(y0)>scinRad*scinRad || -holeZ/2+muonVetoThick+detLowerPart>z0)
				break;
		}
		if(G4UniformRand()<0.5)
			x0 += detX/4;
		else
			x0 -= detX/4;

		if(G4UniformRand()<0.5)
			y0 += detY/4;
		else
			y0 -= detY/4;
	}
	else // generate somewhere inside watershield
	{
		G4double shieldXY, shieldZ;
		shieldXY = Detector->GetShieldSizeXY();
		shieldZ = Detector->GetShieldSizeZ();
		
		// check if there is space to generate a particle
		if(detX<=holeX && detY<=holeY && detZ<=holeZ)
			G4cerr << "ERROR: no free space to generate particle!!! Change detector geometry!" << G4endl;

		while(1)
		{		
  		x0 = shieldXY * (G4UniformRand()-0.5);
  		y0 = shieldXY * (G4UniformRand()-0.5);
  		z0 = shieldZ  * (G4UniformRand()-0.5);
			
			// ... until the particle is inside the water
			if(abs(x0)>holeX/2 || abs(y0)>holeY/2 || abs(z0)>holeZ/2)
				break;
		}
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

  // Select from random evaporation spectrum
	if (genEvaporation == 1) 
	{
        G4double evapEnergy = NSPrimaryGeneratorAction::GetEvaporationEnergy();
        fParticleGun->SetParticleEnergy(evapEnergy*MeV);
	}

  // Generate a particle
  fParticleGun->GeneratePrimaryVertex(anEvent);
}

void NSPrimaryGeneratorAction::SetGenEvaporation (G4bool value)
{
  // Set whether energy distribution or not (-> monochromatic)
  genEvaporation = value;
}

G4double NSPrimaryGeneratorAction::GetEvaporationEnergy(void) {

  // Stolen from HALO code; integral MC method
  // I am not sure this gives quite the right spectrum ?
 const G4int nBins = 10;

	G4double Edistrib[nBins][2] = {
	{0.148,  .25},
	{0.401,  .75},
	{0.567, 1.25},
	{0.697, 1.75},
	{0.801, 2.25},
	{0.876, 2.75},
	{0.933, 3.25},
	{0.967, 3.75},
	{0.987, 4.25},
	{1.0, 4.75},
	};


	G4int i=0;
	G4double rnum = G4UniformRand();
	while (Edistrib[i][0]< rnum) 
	{
		i++;
	}

	return Edistrib[i][1]-(G4UniformRand()-0.5)*0.5;
}

void NSPrimaryGeneratorAction::SetParticleEnergy(G4double energy) 
{
	if(energy>=0.)
		fParticleGun->SetParticleEnergy(energy*MeV);
	else
		G4cerr << "ERROR: Invalid particle energy" << G4endl;
}

void NSPrimaryGeneratorAction::SetGenTwoNeutrons(G4bool value) 
{
	genTwoNeutrons = value;
}
