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

#ifndef NSSteppingAction_h
#define NSSteppingAction_h 1

#include "G4UserSteppingAction.hh"



#include "globals.hh"

#include <fstream>

class NSEventAction;
class G4LogicalVolume;
class NSVerboseMessenger;


class NSSteppingAction : public G4UserSteppingAction
{
  public:
    NSSteppingAction(NSEventAction* eventAction);
    virtual ~NSSteppingAction();

    // method from the base class
    virtual void UserSteppingAction(const G4Step*);
		void SetStepFileName(G4String fileName);
		void SetFileOutput(G4bool output);

  private:
    NSEventAction*  fEventAction;

    // Output file for step information
    // Do not use unless needed; very large file
    G4String outfileName;
    std::ofstream outfile;

		NSVerboseMessenger* fMessenger;
};

#endif

