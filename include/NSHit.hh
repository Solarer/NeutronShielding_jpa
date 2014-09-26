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
  private:
    G4double fEdep[4];
    G4double fPhoton[4];
    G4bool 	 fEntSD[4];
    G4double fFirstContact;
	G4int	fGamma, fElec, fProt, fDeut, fAlpha, fCarbon, fOther, fTotal;


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
    void SetEntSD(G4bool entSD, G4int scinID) { fEntSD[scinID] = entSD; };
    void SetFirstContact(G4double contact) { fFirstContact = contact; };
    inline void AddEdep(G4double dE, G4int scinID) {fEdep[scinID] += dE; };
    inline void AddPhoton(G4double dPh, G4int scinID) {fPhoton[scinID] += dPh; };
	inline void AddGamma(G4int gamma) {fGamma += gamma; fTotal+=gamma; };
	inline void AddElectron(G4int elec) {fElec += elec; fTotal+=elec; };
	inline void AddProton(G4int prot) {fProt += prot; fTotal+=prot; };
	inline void AddDeuteron(G4int deut) {fDeut += deut; fTotal+=deut; };
	inline void AddAlpha(G4int alpha) {fAlpha += alpha; fTotal+=alpha; };
	inline void AddCarbon(G4int carbon) {fCarbon += carbon; fTotal+=carbon; };
	inline void AddOther(G4int other) {fOther += other; fTotal+=other; };

    // get methods
    G4double GetEdep(G4int scinID)  const { return fEdep[scinID]; };
    G4double GetPhoton(G4int scinID)  const { return fPhoton[scinID]; };
    G4bool   GetEntSD(G4int scinID) const { return fEntSD[scinID]; };      
    G4double GetFirstContact()  const { return fFirstContact; };
	G4int GetGamma() const { return fGamma; };
	G4int GetElectron() const { return fElec; };
	G4int GetProton() const { return fProt; };
	G4int GetDeuteron() const { return fDeut; };
	G4int GetAlpha() const { return fAlpha; };
	G4int GetCarbon() const { return fCarbon; };
	G4int GetOther() const { return fOther; };
	G4int GetTotal() const { return fTotal; };
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

#endif

