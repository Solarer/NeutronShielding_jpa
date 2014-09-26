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

#include "NSHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include <iomanip>

G4ThreadLocal G4Allocator<NSHit>* NSHitAllocator=0;

NSHit::NSHit()
 : G4VHit(),
    fFirstContact(-1),
		fGamma(0), fElec(0), fProt(0),
 		fDeut(0), fAlpha(0), fCarbon(0), 
		fOther(0),fTotal(0)
{ 
	for(G4int i=0; i<4; i++)
	{
    fEdep[i] = 0;
		fPhoton[i] = 0;
		fEntSD[i] = 0;
	}
}

NSHit::~NSHit()
{ }

NSHit::NSHit(const NSHit& right)
  : G4VHit()
{
	for(G4int i=0; i<4; i++)
	{
    fEdep[i]  = right.fEdep[i];
    fPhoton[i]= right.fPhoton[i];
    fEntSD[i] = right.fEntSD[i];
	}
    fFirstContact= right.fFirstContact;
    fGamma = right.fGamma;
    fElec= right.fElec;
	fProt = right.fProt;
	fDeut = right.fDeut;
	fAlpha = right.fAlpha;
	fCarbon = right.fCarbon;
	fOther = right.fOther;
	fTotal = right.fTotal;
}

const NSHit& NSHit::operator=(const NSHit& right)
{
	for(G4int i=0; i<4; i++)
	{
    fEdep[i]  = right.fEdep[i];
    fPhoton[i]= right.fPhoton[i];
    fEntSD[i] = right.fEntSD[i];
	}
    fFirstContact= right.fFirstContact;
    fGamma = right.fGamma;
    fElec= right.fElec;
	fProt = right.fProt;
	fDeut = right.fDeut;
	fAlpha = right.fAlpha;
	fCarbon = right.fCarbon;
	fOther = right.fOther;
	fTotal = right.fTotal;
  return *this;
}

G4int NSHit::operator==(const NSHit& right) const
{
  return ( this == &right ) ? 1 : 0;
}

void NSHit::Print()
{
  G4cout
     //<< "Edep: " 
     //<< std::setw(7) << G4BestUnit(fEdep,"Energy")
     << "\tEntered Detector? "<< fEntSD
     << G4endl;
}

