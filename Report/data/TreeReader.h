//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Sep  4 16:27:41 2014 by ROOT version 5.28/00c
// from TTree singleRun/Event info from one run
// found on file: singleRun_sav3.root
//////////////////////////////////////////////////////////

#ifndef TreeReader_h
#define TreeReader_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <string>
#include <iostream>

class TreeReader {
public :
  	TTree          	*fChain;   //!pointer to the analyzed TTree or TChain
  	Int_t           fCurrent; //!current Tree number in a TChain
		TFile* 					f;			// root file

    // Declaration of leaf types
    Int_t           EventID;
    Int_t           EntInner;
    Double_t        Edep;
    Double_t        primx;
    Double_t        primy;
    Double_t        primz;
    Double_t        primEnergy;
    Double_t        primdx;
    Double_t        primdy;
    Double_t        primdz;

    Double_t        Photons;
    Double_t        firstContact;

    // List of branches
    TBranch        *b_EventID;  	//!
    TBranch        *b_EntInner;   //!
    TBranch        *b_Edep;   		//!
    TBranch        *b_primx;   		//!
    TBranch        *b_primy;   		//!
    TBranch        *b_primEnergy; //!
    TBranch        *b_primz;   		//!
    TBranch        *b_primdx;   	//!
    TBranch        *b_primdy;   	//!
    TBranch        *b_primdz;   	//!

    TBranch        *b_Photons;   	//!
    TBranch        *b_firstContact;   	//!

    TreeReader();
    virtual ~TreeReader();
    virtual Int_t    Cut(Long64_t entry);
    virtual Int_t    GetEntry(Long64_t entry);
    virtual Long64_t LoadTree(Long64_t entry);
    virtual void     Init(TTree *tree);
    virtual void     Loop();
    virtual Bool_t   Notify();
    virtual void     Show(Long64_t entry = -1);
};
#endif
