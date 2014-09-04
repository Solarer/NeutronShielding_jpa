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

class TreeReader {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           EventID;
   Int_t           EntInner;
   Double_t        Edep;
   Double_t        primx;
   Double_t        primy;
   Double_t        primz;
   Double_t        primdx;
   Double_t        primdy;
   Double_t        primdz;

   // List of branches
   TBranch        *b_EventID;   //!
   TBranch        *b_EntInner;   //!
   TBranch        *b_Edep;   //!
   TBranch        *b_primx;   //!
   TBranch        *b_primy;   //!
   TBranch        *b_primz;   //!
   TBranch        *b_primdx;   //!
   TBranch        *b_primdy;   //!
   TBranch        *b_primdz;   //!

   TreeReader(TTree *tree=0);
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

#ifdef TreeReader_cxx
TreeReader::TreeReader(TTree *tree)
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("singleRun_sav3.root");
      if (!f) {
         f = new TFile("singleRun_sav3.root");
      }
      tree = (TTree*)gDirectory->Get("singleRun");

   }
   Init(tree);
}

TreeReader::~TreeReader()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TreeReader::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t TreeReader::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (!fChain->InheritsFrom(TChain::Class()))  return centry;
   TChain *chain = (TChain*)fChain;
   if (chain->GetTreeNumber() != fCurrent) {
      fCurrent = chain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void TreeReader::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("EventID", &EventID, &b_EventID);
   fChain->SetBranchAddress("EntInner", &EntInner, &b_EntInner);
   fChain->SetBranchAddress("Edep", &Edep, &b_Edep);
   fChain->SetBranchAddress("primx", &primx, &b_primx);
   fChain->SetBranchAddress("primy", &primy, &b_primy);
   fChain->SetBranchAddress("primz", &primz, &b_primz);
   fChain->SetBranchAddress("primdx", &primdx, &b_primdx);
   fChain->SetBranchAddress("primdy", &primdy, &b_primdy);
   fChain->SetBranchAddress("primdz", &primdz, &b_primdz);
   Notify();
}

Bool_t TreeReader::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TreeReader::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TreeReader::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TreeReader_cxx
