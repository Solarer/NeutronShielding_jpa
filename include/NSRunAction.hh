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

#ifndef NSRunAction_h
#define NSRunAction_h 1

#include "G4UserRunAction.hh"
#include "globals.hh"
#include <vector>

class G4Run;
class G4LogicalVolume;
class NSRunMessenger;

class NSRunAction : public G4UserRunAction
{
	private:
		NSRunMessenger* fMessenger;

		std::vector<G4int> eventIDs;
		std::vector<G4String> outputFiles;
		G4bool doCollectEvents, doProcessEvents;

  public:
    NSRunAction();
    virtual ~NSRunAction();
	
    // Get-Methods
		G4int GetEventID(){ return eventIDs.empty() ? -1 : eventIDs.front(); };
    inline G4String GetOutputFile(){ return outputFiles.front(); };
		inline G4bool GetDoCollectEvents(){ return doCollectEvents; };

    // Set-Methods
    void SetCollectEvents(G4bool collect){ doCollectEvents = collect; };
    void SetProcessEvents(G4bool process){ doProcessEvents = process; };
    
    // Other-Methods
		void FillVec();
		G4bool PopEvent();
		inline G4bool IsNextEvent(G4int eventID){ return (GetEventID() == eventID); };

    virtual G4Run* GenerateRun();
    virtual void BeginOfRunAction(const G4Run*);
    virtual void EndOfRunAction(const G4Run*);
};

#endif

