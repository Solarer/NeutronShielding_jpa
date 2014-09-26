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

#include "NSDetectorConstruction.hh"
#include "NSDetectorMessenger.hh"

#include "NSSD.hh"
#include "G4SDManager.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"

#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"

#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"

#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4VisAttributes.hh"

#include "G4RunManager.hh"

#include <string.h>
#include <stdio.h>

NSDetectorConstruction::NSDetectorConstruction()
: G4VUserDetectorConstruction(),
  worldMat   (0), shieldMat (0),  detMat(0),
  solidWorld  (0), logicWorld  (0), physWorld  (0),
  solidShield(0), logicShield(0),
  solidDet    (0), logicDet    (0), physDet    (0)
{
  // Default parameters
  
    worldSizeXY = 5*m;
		worldSizeZ = 5*m;
		shieldSizeXY = 1*m;
		shieldSizeZ	= 1*m;
		holeSizeXY = 0.4572*m;
		holeSizeZ = 0.625475*m;
    detSizeXY = detSizeZ = 0.4064*m;
		detLowerPart = 0.1524*m;
  	scinRadIn1 = 0. *m;
  	scinRadIn2 = 0. *m;
  	scinRadOut1 = 0.05*m;
  	scinRadOut2 = 0.075*m;
  	scinHeight = 0.16*m;



	// ComputeParameters();  not used right now, because detector size does not change

  // Default materials
  DefineMaterials();
  SetWorldMat("G4_Galactic");
  SetShieldMat("G4_Galactic");
  SetDetMat("G4_Pb");
  SetScinMat("EJ301");

  // Commands for interactive definition of detector
  fMessenger = new NSDetectorMessenger(this);
}

NSDetectorConstruction::~NSDetectorConstruction()
{
  delete fMessenger;
}

G4VPhysicalVolume* NSDetectorConstruction::Construct()
{
  return ConstructDetector();
}

G4VPhysicalVolume* NSDetectorConstruction::ConstructDetector()
{
  // Clean old geometry, if any
  G4GeometryManager::GetInstance()->OpenGeometry();
  G4PhysicalVolumeStore::GetInstance()->Clean();
  G4LogicalVolumeStore::GetInstance()->Clean();
  G4SolidStore::GetInstance()->Clean();

  // Complete parameters defintion
  ComputeParameters();

  // Option to switch on/off checking of volumes overlaps
  G4bool checkOverlaps = true;

  // World
  solidWorld =
    new G4Box("World",                          // name
              0.5*worldSizeXY,                 // size x
              0.5*worldSizeXY,                 // size y
              0.5*worldSizeZ);                 // size z

  logicWorld =
    new G4LogicalVolume(solidWorld,             // solid
                        worldMat,              // material
                        "World");               // name

  physWorld = 
    new G4PVPlacement(0,                        // no rotation
                      G4ThreeVector(),          // at (0,0,0)
                      logicWorld,               // logical volume
                      "World",                  // name
                      0,                        // mother  volume
                      false,                    // no boolean operation
                      0,                        // copy number
                      checkOverlaps);           // overlaps checking

  // Water Shield
  solidShield =
    new G4Box("ShieldBox",                      // name
              0.5*shieldSizeXY, 								// size x
              0.5*shieldSizeXY, 								// size y
              0.5*shieldSizeZ); 								// size z

  logicShield =
    new G4LogicalVolume(solidShield,           	// solid
                        shieldMat,            	// material
                        "Shield");             	// name




	physShield = 
		new G4PVPlacement(0,															// no rotation
                    G4ThreeVector(),  								// at (0, 0, 0)
                    logicShield,               				// logical volume
                    "Shield",                  				// name
                    logicWorld,                 			// mother volume
                    false,                      			// no boolean operation
                    0,                          			// copy number
                    checkOverlaps);             			// overlaps checking    

		
  G4Box* solidAir=
    new G4Box("ShieldBox",                    // name
              holeSizeXY/4, 									// size x
              holeSizeXY/4, 									// size y 
              0.5*holeSizeZ); 								// size z

  G4LogicalVolume* logicAir =
    new G4LogicalVolume(solidAir,           	// solid
                        worldMat,            	// material
                        "Shield");             	// name

  // Detector
  G4VSolid* leadBox =
    new G4Box("Lead",                    				// name
              detSizeXY/4,      										// size x
              detSizeXY/4,      										// size y
              0.5*detSizeZ);      										// size z
	G4VSolid* airHole =
		new G4Tubs("AirHole",
							0.,										// inner radius
							scinRadOut2,		// outer radius
							0.5*(detSizeZ-detLowerPart),						// heigth
							0.,										// beginn degree
							360*deg);							// end degree

	G4VSolid* solidDetQuarter = new G4SubtractionSolid("DetQuarter", leadBox, airHole, new G4RotationMatrix(), G4ThreeVector(0,0,0.5*detLowerPart));

  logicDet =
    new G4LogicalVolume(solidDetQuarter,               // solid
                        detMat,              	// material
                        "Det");            // name

  // Scintillator 
	G4double x,y;
  solidScin =
    new G4Cons("Scin",                  // name
               scinRadIn2,              // small radius 2
               scinRadOut2,             // big radius 2
               scinRadIn1,              // small radius 1
               scinRadOut1,             // big radius 1
               0.5*scinHeight,          // height
               0,                       // start cut (radians)
               360*deg);                // end cut (radians)

  logicScin =
    new G4LogicalVolume(solidScin,              // solid
                        scinMat,               // material
                        "Scin");                // name

	// Placements for detector
	G4int copyAir = 0;
	G4PVPlacement* physAir = 
		new G4PVPlacement(0,															// no rotation
                    G4ThreeVector(-holeSizeXY/4,-holeSizeXY/4,0),  								// at (0, 0, 0)
                    logicAir,     	          				// logical volume
                    "AirQuarter",     		             				// name
                    logicShield,                 			// mother volume
                    false,                      			// no boolean operation
                    copyAir++,                          			// copy number
                    checkOverlaps);             			// overlaps checking    

   		physDet= new G4PVPlacement(0,	    // no rotation
                        G4ThreeVector(holeSizeXY/4-detSizeXY/4,holeSizeXY/4-detSizeXY/4, -0.5*holeSizeZ+0.5*detSizeZ),        // at position
                        logicDet,       // logical volume
                        "Det",          // name
                        logicAir,       // mother volume
                        false,          // no boolean operation
                        0,			        // copy number
                        checkOverlaps); // overlaps checking

   		physScin = new G4PVPlacement(0,   // no rotation
                        G4ThreeVector(holeSizeXY/4-detSizeXY/4,holeSizeXY/4-detSizeXY/4, -0.5*holeSizeZ+detLowerPart+0.5*scinHeight),        // at position
                        logicScin,      // logical volume
                        "Scin",         // name
                        logicAir,       // mother volume
                        false,          // no boolean operation
                        0,       				// copy number
                        checkOverlaps); // overlaps checking

	// Place 3 remaining Detector quarters
	G4RotationMatrix* rm[3];
 	rm[0] = new G4RotationMatrix;
 	rm[1] = new G4RotationMatrix;
 	rm[2] = new G4RotationMatrix;

	rm[0]->rotateZ(90*deg);
	rm[1]->rotateZ(270*deg);
	rm[2]->rotateZ(180*deg);

	G4RotationMatrix* ret = new G4RotationMatrix;
	ret->rotateZ(90*deg);

	for (G4int i = -1; i < 2; i+=2)
  {
		for (G4int j = -1; j < 2; j+=2)
  	{
			if( i == -1 && j == -1)
				continue;
    	x = i*holeSizeXY/4;
    	y = j*holeSizeXY/4;

			physAir = 
				new G4PVPlacement(rm[copyAir-1],															// no rotation
                    G4ThreeVector(x,y,0),  								// at (0, 0, 0)
                    logicAir,     	          				// logical volume
                    "AirQuarter",     		             				// name
                    logicShield,                 			// mother volume
                    false,                      			// no boolean operation
                    copyAir,                          			// copy number
                    checkOverlaps);             			// overlaps checking    
		copyAir++;
		}
	}
	
  // Print volumes
  G4cout << "volumes: " << logicWorld << " " << logicDet << " " << logicShield << " " << logicScin << G4endl;

  // Make world box invisible and scintillator solid
  logicWorld->SetVisAttributes (G4VisAttributes::Invisible);
	G4VisAttributes solid;
	solid.SetForceSolid(true);
	solid.SetColor(1,0,0);
  logicScin->SetVisAttributes (solid);
  // Always return the physical World
  return physWorld;
}

void NSDetectorConstruction::ConstructSDandField()
{
  // Create new sensitive detector
  cennsSD = new NSSD("cennsSD", "CennsHitsCollection");

  // Assign sensitive detector to Det volume
  SetSensitiveDetector("Scin", cennsSD);
}

void NSDetectorConstruction::SetWorldMat(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial) worldMat = pttoMaterial;
}

void NSDetectorConstruction::SetShieldMat(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial) shieldMat = pttoMaterial;
}

void NSDetectorConstruction::SetDetMat(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial) detMat = pttoMaterial;
}

void NSDetectorConstruction::SetScinMat(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial) scinMat = pttoMaterial;
}

void NSDetectorConstruction::UpdateGeometry()
{
  // Completely reconstruct detector
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructDetector());

  // Reset sensitive detector
  SetSensitiveDetector("Scin", cennsSD);
}

void NSDetectorConstruction::ComputeParameters()
{
  // These parameters are dependent upon other parameters and
  // must therefore be recalculated when the geometry is changed.
  worldSizeXY   = 20.0*m;
  worldSizeZ    = 20.0*m;
}

