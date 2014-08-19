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

#ifndef NSHit_h
#define NSHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"

class NSHit : public G4VHit
{
  public:
    NSHit();
    NSHit(const NSHit&);
    virtual ~NSHit();

    // operators
    const NSHit& operator=(const NSHit&);
    G4int operator==(const NSHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // methods from base class
    virtual void Draw() {}
    virtual void Print();

    // methods to handle data
    void SetEntSD(G4int entSD) { fEntSD = entSD; };
    void Add(G4double de);

    // get methods
    G4double GetEdep()  const { return fEdep; };
    G4int    GetEntSD() const { return fEntSD; };
      
  private:
    G4double fEdep;
    G4int    fEntSD;
};

typedef G4THitsCollection<NSHit> NSHitsCollection;

extern G4ThreadLocal G4Allocator<NSHit>* NSHitAllocator;

inline void* NSHit::operator new(size_t)
{
  if(!NSHitAllocator)
      NSHitAllocator = new G4Allocator<NSHit>;
  void *hit;
  hit = (void *) NSHitAllocator->MallocSingle();
  return hit;
}

inline void NSHit::operator delete(void *hit)
{
  if(!NSHitAllocator)
      NSHitAllocator = new G4Allocator<NSHit>;
  NSHitAllocator->FreeSingle((NSHit*) hit);
}


inline void NSHit::Add(G4double de)
{
  fEdep += de;
}


#endif
