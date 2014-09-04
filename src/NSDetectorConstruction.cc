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
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"

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
  world_mat   (0), shield_mat (0),  det_mat(0),
  solidWorld  (0), logicWorld  (0), physWorld  (0),
  solidShield(0), logicShield(0),
  solidDet    (0), logicDet    (0), physDet    (0)
{
  // Default parameters
  detRatio       = 0.5;
	shield_layer	 = 0;
  shieldBox_size[0] = 0.55*m;
  shieldBox_size[1] = 0.27*m;
  shieldBox_size[2] = 0.20*m;
	hSpace = 0.02*m; 
	vSpace = 0.02*m; 
	scin_heightRatio = 0.9;
	scin_radiusRatio=0.10;
  ComputeParameters();

  // Default materials
  DefineMaterials();
  SetWorldMat("G4_AIR");
  SetShieldMat("G4_WATER");
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
              0.5*world_sizeXY,                 // size x
              0.5*world_sizeXY,                 // size y
              0.5*world_sizeZ);                 // size z

  logicWorld =
    new G4LogicalVolume(solidWorld,             // solid
                        world_mat,              // material
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

  // Shield1
  solidShield =
    new G4Box("ShieldBox",                      // name
              0.5*shieldBox_size[0],            // size x
              0.5*shieldBox_size[1],            // size y 
              0.5*shieldBox_size[2]);           // size z

  logicShield =
    new G4LogicalVolume(solidShield,           	// solid
                        shield_mat,            	// material
                        "Shield");             	// name



	// Prepare for turning boxes
	G4RotationMatrix* doRot = new G4RotationMatrix; 
	doRot->rotateZ(90*deg);
	G4RotationMatrix* doNotRot = new G4RotationMatrix; 
	doNotRot->rotateZ(0*deg);
	G4RotationMatrix* rotMat;


	// Place and turn them
	for (int shield_cnt=0 ; shield_cnt<shieldBox_number ; shield_cnt++)
		{
				if(shield_cnt%6 == 1 || shield_cnt%6 == 4 || shield_cnt>=shieldBox_number-4)
					rotMat=doRot;
				else
					rotMat=doNotRot;

				physShield[shield_cnt] = 
					new G4PVPlacement(
										rotMat,                    				// rotation
                    shieldBox_position[shield_cnt],  	// at (0, 0, 0)
                    logicShield,               				// logical volume
                    "Shield",                  				// name
                    logicWorld,                 			// mother volume
                    false,                      			// no boolean operation
                    0,                          			// copy number
                    checkOverlaps);             			// overlaps checking    
		}


  // Detector
  solidDet =
    new G4Box("Det",                    				// name
              detRatio*det_sizeXY,      				// size x
              detRatio*det_sizeXY,      				// size y
              detRatio*det_sizeZ);      				// size z

  logicDet =
    new G4LogicalVolume(solidDet,               // solid
                        det_mat,                // material
                        "Det");                 // name

  physDet =
    new G4PVPlacement(0,                        // no rotation
                      G4ThreeVector(),          // at (0, 0, 0)
                      logicDet,                 // logical volume
                      "Det",                    // name
                      logicWorld,            		// mother volume
                      false,                    // no boolean operation
                      0,                        // copy number
                      checkOverlaps);           // overlaps checking


  // Szintillator 
  solidScin =
    new G4Tubs(	"Scin",                    			// name
								0,															// inner radius
								scin_radius,										// outer radius
								0.5*scin_height,								// heigth
								0,															// start angle
								360*deg);												// end angle
  logicScin =
    new G4LogicalVolume(solidScin,              // solid
                        scin_mat,               // material
                        "Scin");                // name

  physScin=
    new G4PVPlacement(0,                        // no rotation
                      G4ThreeVector(),          // at (0, 0, 0)
                      logicScin,                // logical volume
                      "Scin",                   // name
                      logicDet,            			// mother volume
                      false,                    // no boolean operation
                      0,                        // copy number
                      checkOverlaps);           // overlaps checking


	// prepare and set visuable attributes
	G4VisAttributes visShield, visDet, visScin;
	visShield.SetColour(0,0,1);
	visDet.SetColour(1,1,0);
	visScin.SetColour(1,1,0);
	visScin.SetForceSolid(true);
 
	logicShield->SetVisAttributes(visShield);
	logicDet->SetVisAttributes(visDet);
	logicScin->SetVisAttributes(visScin);

  // Print volumes
  G4cout << "volumes: " << logicDet << " " << logicShield << " " << logicWorld << G4endl;

  // Make world box invisible
  logicWorld->SetVisAttributes (G4VisAttributes::Invisible);

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

void NSDetectorConstruction::SetDetRatio(G4double ratio)
{
  // Check that detector has been constructed
  if (!solidDet) 
  {
    G4cerr << "Detector has not yet been constructed." << G4endl;
    return;
  }

  // Check that new detector ratio is between 0 and 1
  if (ratio < 0. || ratio > 1.)
  {
    G4cout << "Invalid detector ratio " << ratio
           << "!  No change to geometry." << G4endl;
    return;
  }

  // Set new detector ratio
  detRatio = ratio;

  G4cout << "Detector ratio set: " << detRatio << G4endl;
}

void NSDetectorConstruction::SetWorldMat(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial) world_mat = pttoMaterial;
}

void NSDetectorConstruction::SetShieldMat(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial) shield_mat = pttoMaterial;
}

void NSDetectorConstruction::SetDetMat(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial) det_mat = pttoMaterial;
}

void NSDetectorConstruction::SetScinMat(G4String materialChoice)
{
  // search the material by its name   
  G4Material* pttoMaterial = G4Material::GetMaterial(materialChoice);     
  if (pttoMaterial) scin_mat = pttoMaterial;
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
  world_sizeXY   = 20.0*m;
  world_sizeZ    = 20.0*m;
  det_sizeXY     = 1.0*m*detRatio;
  det_sizeZ      = 1.0*m*detRatio;
	shieldBox_number = shield_layer == 0 ? 0:shield_layer*6+4;
	shieldSize[0]	 = 2*shieldBox_size[0]+hSpace;
	shieldSize[1]	 = shieldBox_size[0]+2*shieldBox_size[1]+2*hSpace;
	shieldSize[2]	 = shield_layer == 0 ? 0 : shield_layer*shieldBox_size[2]+(shield_layer-1)*hSpace;

	scin_radius = det_sizeXY*scin_radiusRatio;
	scin_height= det_sizeZ*scin_heightRatio;

	physShield = new G4VPhysicalVolume*[shieldBox_number];
  shieldBox_position = new G4ThreeVector[shieldBox_number];
	
	// Positions and rotation of the shield boxes (first layer) 
	if(shieldBox_number!=0)		// don't do this if there is no water shielding at all
	{
		shieldBox_position[0].setX(0.5*hSpace+0.5*shieldBox_size[0]);
		shieldBox_position[0].setY(0.5*shieldBox_size[0]+hSpace+0.5*shieldBox_size[1]);
		shieldBox_position[0].setZ(0.5*shieldBox_size[2]-0.5*shieldSize[2]);
	
		shieldBox_position[1].setX(0.5*hSpace+shieldBox_size[0]-0.5*shieldBox_size[1]);
		shieldBox_position[1].setY(0.0);
		shieldBox_position[1].setZ(0.5*shieldBox_size[2]-0.5*shieldSize[2]);

		shieldBox_position[2].setX(shieldBox_position[0].getX());
		shieldBox_position[2].setY(-shieldBox_position[0].getY());
		shieldBox_position[2].setZ(0.5*shieldBox_size[2]-0.5*shieldSize[2]);

		shieldBox_position[3].setX(-shieldBox_position[0].getX());
		shieldBox_position[3].setY(-shieldBox_position[0].getY());
		shieldBox_position[3].setZ(0.5*shieldBox_size[2]-0.5*shieldSize[2]);

		shieldBox_position[4].setX(-shieldBox_position[1].getX());
		shieldBox_position[4].setY(0.0);
		shieldBox_position[4].setZ(0.5*shieldBox_size[2]-0.5*shieldSize[2]);

		shieldBox_position[5].setX(-shieldBox_position[0].getX());
		shieldBox_position[5].setY(shieldBox_position[0].getY());
		shieldBox_position[5].setZ(0.5*shieldBox_size[2]-0.5*shieldSize[2]);

		// top and bottom position
		// first box bottom
		shieldBox_position[shieldBox_number-4].setX(0.25*hSpace+0.5*shieldBox_size[1]);
		shieldBox_position[shieldBox_number-4].setY(0.0);
		shieldBox_position[shieldBox_number-4].setZ(-0.5*shieldSize[2]+0.5*shieldBox_size[2]);
		// second box bottom
		shieldBox_position[shieldBox_number-3].setX(-0.25*hSpace-0.5*shieldBox_size[1]);
		shieldBox_position[shieldBox_number-3].setY(0.0);
		shieldBox_position[shieldBox_number-3].setZ(-0.5*shieldSize[2]+0.5*shieldBox_size[2]);
		// first box top
		shieldBox_position[shieldBox_number-2]=shieldBox_position[shieldBox_number-4];
		shieldBox_position[shieldBox_number-2].setZ(0.5*shieldSize[2]-0.5*shieldBox_size[2]);
		// second box top
		shieldBox_position[shieldBox_number-1]=shieldBox_position[shieldBox_number-3];
		shieldBox_position[shieldBox_number-1].setZ(0.5*shieldSize[2]-0.5*shieldBox_size[2]);
	}


	// calculate missing layers
	for (int currentLayer=1 ; currentLayer<shield_layer ; currentLayer++)
		for (int currentBox=0 ; currentBox<6 ; currentBox++)
			{
					shieldBox_position[currentBox+currentLayer*6]=shieldBox_position[currentBox];
					shieldBox_position[currentBox+currentLayer*6].setZ(shieldBox_position[0].getZ()+currentLayer*(shieldBox_size[2]+vSpace));
			}
}

