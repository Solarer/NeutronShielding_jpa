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
: Detector(DC),genEvaporation(0)
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

	// particle position
  G4double x0, y0, z0;

  //this function is called at the begining of each event
  //
  // In order to avoid dependence of PrimaryGeneratorAction
  // on DetectorConstruction class we get Envelope volume
  // from G4LogicalVolumeStore.

	if(genInLead) // generate in leadshield
	{
		G4double shieldX, shieldY, shieldZ;
		G4double scinRad, scinHeight;
		shieldX = shieldY = Detector->GetDetSizeXY();
		shieldZ = Detector->GetDetSizeZ();
		scinRad = Detector->GetScinRad();
		scinHeight = Detector->GetScinHeight();
		
		while(1) // generate, until particle not in scintillator
		{
  		x0 = shieldX * (G4UniformRand()-0.5);
  		y0 = shieldY * (G4UniformRand()-0.5);
  		z0 = shieldZ * (G4UniformRand()-0.5);
			
			if(sqrt(x0*x0+y0*y0)>scinRad || abs(z0)>shieldZ) // particle not in scintillator
				break;
		}
	}
	else // generate in watershield
	{
  	    // Get detector configuration sizes
  	    G4int maxBoxNumber = Detector->GetShieldBoxNumber();
  	    G4double boxX, boxY, boxZ;
	    boxX = Detector->GetShieldBoxSizeX();
	    boxY = Detector->GetShieldBoxSizeY();
	    boxZ = Detector->GetShieldBoxSizeZ();
	    const G4ThreeVector* shieldBoxPosition = Detector->GetShieldBoxPosition();

	    // Now generate in random box
  	    G4int box =  int(maxBoxNumber * G4UniformRand());
  	    z0 = (boxZ * (G4UniformRand()-0.5)) + shieldBoxPosition[box].getZ();
	
	    // some boxes are turned by 90°
	    if(box >= maxBoxNumber-4 || box%6 == 1 || box%6 == 4) // box has to be turned by 90°
	    {
  	        x0 = (boxY * (G4UniformRand()-0.5)) + shieldBoxPosition[box].getX();
  	        y0 = (boxX * (G4UniformRand()-0.5)) + shieldBoxPosition[box].getY();
	    }
	    else	// box is not turned
	    {
  	        x0 = (boxX * (G4UniformRand()-0.5)) + shieldBoxPosition[box].getX();
  	        y0 = (boxY * (G4UniformRand()-0.5)) + shieldBoxPosition[box].getY();
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

  //event count output
  if((event_cnt<1000 && event_cnt%100==0) || event_cnt%1000==0)
	G4cout << "Reached " << event_cnt << " event mark. Ongoing..." << G4endl;
    event_cnt++;
}

void NSPrimaryGeneratorAction::SetGenEvaporation (G4int value)
{
  // Set which shield the particles are generated in
  genEvaporation = value;
}

G4double NSPrimaryGeneratorAction::GetEvaporationEnergy(void) {

  // Stolen from HALO code; integral MC method
  // I am not sure this gives quite the right spectrum ?

  const G4int nBins = 13;

  G4double Edistrib[nBins][2] = {
   {0.,    0.  },
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
   }; 

    while (true) 
    {
        G4double energy = G4UniformRand()*6.25;         // random energy
        G4double rand = G4UniformRand();                // random value

        G4int i=0;
        while(Edistrib[i][1]>= energy)
        {
            i++;
        }

        if (energy == 6.25)
            i--;                                        // dont leave array

        G4double chance =  (Edistrib[i][0]-Edistrib[i-1])/(Edistrib[i][i]-Edistrib[i-1][i])
        if(rand<=chance)
            return energy;
    }
}
