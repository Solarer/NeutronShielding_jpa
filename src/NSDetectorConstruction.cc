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
	shield_layer	 = 6;
  shieldBox_size[0] = 0.50*m;
  shieldBox_size[1] = 0.25*m;
  shieldBox_size[2] = 0.25*m;
	hSpace = vSpace = 0.05*m; 
  ComputeParameters();

  // Default materials
  DefineMaterials();
  SetWorldMat("G4_AIR");
  SetShieldMat("G4_WATER");
  SetDetMat("lXe");

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

void NSDetectorConstruction::DefineMaterials()
{
  // Get NIST manager
  G4NistManager* nistManager = G4NistManager::Instance();

  // Generic Materials defined from NIST database
  nistManager->FindOrBuildMaterial("G4_AIR");
  nistManager->FindOrBuildMaterial("G4_Galactic");

  // Shielding Materials

  // Materials defined from NIST database
  nistManager->FindOrBuildMaterial("G4_Pb");
  nistManager->FindOrBuildMaterial("G4_Fe");
  nistManager->FindOrBuildMaterial("G4_Cu");
  nistManager->FindOrBuildMaterial("G4_WATER");
  G4Material* polyethylene = nistManager->FindOrBuildMaterial("G4_POLYETHYLENE");

  // Boron defined as an element from isotopes
  G4double percentB10 = 19.9;
  G4Isotope* B10 = new G4Isotope("B10", 5, 10, 10.012937*g/mole);
  G4Isotope* B11 = new G4Isotope("B11", 5, 11, 11.009305*g/mole);
  G4Element* boron = new G4Element("boron", "B", 2);
  boron->AddIsotope(B10, percentB10*perCent);
  boron->AddIsotope(B11, (100-percentB10)*perCent);

  // Boron-doped polyethylene (BdP) defined as a material
  G4double densityBdP = 1.01*g/cm3;

  //generate a list of different dopes
  const double max_percentBdP=5.1;			// stepping: 0.1 , insert one step higher than required 	
  G4Material* BdP_List[int(max_percentBdP*10)]; 		

  for(double percentBdP = 0.0 ; percentBdP<max_percentBdP ; percentBdP+=0.1){
		char str[20];	
		sprintf(str,"%i_%i",int(percentBdP),int(percentBdP*10)%10);
  	BdP_List[int(percentBdP*10)] = new G4Material(std::string("BdP"+std::string(str)), densityBdP, 2);
  	BdP_List[int(percentBdP*10)]->AddElement(boron, percentBdP*perCent);
  	BdP_List[int(percentBdP*10)]->AddMaterial(polyethylene, (100-percentBdP)*perCent);
  }

  // Detector Materials

  // Liquid xenon defined as a material
  new G4Material("lXe", 54, 131.293*g/mole, 3*g/cm3);

  // Germanium defined from NIST database
  nistManager->FindOrBuildMaterial("G4_Ge");

  // Cesium iodide defined from elements
  G4Element* cesium = new G4Element("cesium", "Cs", 55, 132.90545*g/mole);
  G4Element* iodine = new G4Element("iodine", "I", 53, 126.90447*g/mole);
  G4double densityCsI = 4.510*g/cm3;
  G4Material* CsI = new G4Material("CsI", densityCsI, 2);
  CsI->AddElement(cesium, 1);
  CsI->AddElement(iodine, 1);

  // Liquid argon defined as a material
  new G4Material("lAr", 18, 39.948*g/mole, 1.40*g/cm3);
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
              0.5*shieldBox_size[2]);            // size z

  logicShield =
    new G4LogicalVolume(solidShield,           // solid
                        shield_mat,            // material
                        "Shield");             // name

 
	for (int shield_cnt=0 ; shield_cnt<shieldBox_number-4 ; shield_cnt++)
		{
    		new G4PVPlacement(
										0,                    		// no rotation
                    shieldBox_position[shield_cnt],  	// at (0, 0, 0)
                    logicShield,               // logical volume
                    "Shield",                  // name
                    logicWorld,                 // mother volume
                    false,                      // no boolean operation
                    0,                          // copy number
                    checkOverlaps);             // overlaps checking    
		}


  // Detector
  solidDet=0; logicDet=0; physDet=0;
  solidDet =
    new G4Box("Det",                            // name
              0.5*det_sizeXY,      // size x
              0.5*det_sizeXY,      // size y
              0.5*det_sizeZ);      // size z

  logicDet =
    new G4LogicalVolume(solidDet,               // solid
                        det_mat,                // material
                        "Det");                 // name

  physDet =
    new G4PVPlacement(0,                        // no rotation
                      G4ThreeVector(),          // at (0, 0, 0)
                      logicDet,                 // logical volume
                      "Det",                    // name
                      logicShield,             // mother volume
                      false,                    // no boolean operation
                      0,                        // copy number
                      checkOverlaps);           // overlaps checking

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
  SetSensitiveDetector("Det", cennsSD);
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

void NSDetectorConstruction::UpdateGeometry()
{
  // Completely reconstruct detector
  G4RunManager::GetRunManager()->DefineWorldVolume(ConstructDetector());

  // Reset sensitive detector
  SetSensitiveDetector("Det", cennsSD);
}

void NSDetectorConstruction::ComputeParameters()
{
  // These parameters are dependent upon other parameters and
  // must therefore be recalculated when the geometry is changed.
  world_sizeXY   = 2.0*m;
  world_sizeZ    = 2.0*m;
  det_sizeXY     = 1.0*m;
  det_sizeZ      = 1.0*m;
	shieldBox_number = shield_layer*6+4;

  shieldBox_position = new G4ThreeVector[shieldBox_number];
	shieldBox_rotation = new G4RotationMatrix[shieldBox_number];
	
	// Positions and rotation of the shield boxes (first layer) 
	shieldBox_position[0].setX(0.5*hSpace+0.5*shieldBox_size[0]);
	shieldBox_position[0].setY(0.5*shieldBox_size[0]+hSpace+0.5*shieldBox_size[1]);
	shieldBox_position[0].setZ(0.5*shieldBox_size[2]);
	shieldBox_rotation[0].rotateZ(90*deg);
	
	shieldBox_position[1].setX(0.5*hSpace+shieldBox_size[0]-0.5*shieldBox_size[1]);
	shieldBox_position[1].setY(0.0);
	shieldBox_position[1].setZ(0.5*shieldBox_size[2]);
	shieldBox_rotation[0].rotateZ(90*deg);

	shieldBox_position[2].setX(shieldBox_position[0].getX());
	shieldBox_position[2].setY(-shieldBox_position[0].getY());
	shieldBox_position[2].setZ(0.5*shieldBox_size[2]);
	shieldBox_rotation[0].rotateZ(90*deg);

	shieldBox_position[3].setX(-shieldBox_position[0].getX());
	shieldBox_position[3].setY(-shieldBox_position[0].getY());
	shieldBox_position[3].setZ(0.5*shieldBox_size[2]);
	shieldBox_rotation[0].rotateZ(90*deg);

	shieldBox_position[4].setX(-shieldBox_position[1].getX());
	shieldBox_position[4].setY(0.0);
	shieldBox_position[4].setZ(0.5*shieldBox_size[2]);
	shieldBox_rotation[0].rotateZ(90*deg);

	shieldBox_position[5].setX(-shieldBox_position[0].getX());
	shieldBox_position[5].setY(shieldBox_position[0].getY());
	shieldBox_position[5].setZ(0.5*shieldBox_size[2]);
	shieldBox_rotation[0].rotateZ(90*deg);


	// calculate missing layers
	for (int currentLayer=1 ; currentLayer<shield_layer ; currentLayer++)
		for (int currentBox=0 ; currentBox<6 ; currentBox++)
			{
					shieldBox_position[currentBox+currentLayer*6]=shieldBox_position[currentBox];
					shieldBox_position[currentBox+currentLayer*6].setZ(0.5*shieldBox_size[2]+currentLayer*(shieldBox_size[2]+vSpace));
					shieldBox_rotation[currentBox+currentLayer*6]=shieldBox_rotation[currentBox];
			}

	// top and bottom position
	// first box bottom
	shieldBox_position[shieldBox_number-4].setX(0.25*hSpace+0.5*shieldBox_size[1]);
	shieldBox_position[shieldBox_number-4].setY(0.0);
	shieldBox_position[shieldBox_number-4].setZ(0.5*shieldBox_size[2]);
	// second box bottom
	shieldBox_position[shieldBox_number-3].setX(-0.25*hSpace-0.5*shieldBox_size[1]);
	shieldBox_position[shieldBox_number-3].setY(0.0);
	shieldBox_position[shieldBox_number-3].setZ(0.5*shieldBox_size[2]);
	// first box top
	shieldBox_position[shieldBox_number-2]=shieldBox_position[shieldBox_number-4];
	shieldBox_position[shieldBox_number-2].setZ(0.5*shieldBox_size[2] + (shield_layer-1)*(vSpace + shieldBox_size[2]));
	// second box top
	shieldBox_position[shieldBox_number-1]=shieldBox_position[shieldBox_number-3];
	shieldBox_position[shieldBox_number-1].setZ(0.5*shieldBox_size[2] + (shield_layer-1)*(vSpace + shieldBox_size[2]));

	// and rotation
	shieldBox_rotation[shieldBox_number-4].rotateZ(90*deg);
	shieldBox_rotation[shieldBox_number-3].rotateZ(90*deg);
	shieldBox_rotation[shieldBox_number-2].rotateZ(90*deg);
	shieldBox_rotation[shieldBox_number-1].rotateZ(90*deg);
}

