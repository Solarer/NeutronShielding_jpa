{
  // Open the file.  Now, fin is a pointer to this file, if we need it.
  // Also, the contents of the file are now in memory.
  TFile * fin = TFile::Open("./example2cout.root");
  
  // Draw the histogram histo with no special options
  TCanvas c1("c1", "First canvas", 400, 300);
  histo->Draw();
  TCanvas c2("c2", "Second canvas", 400, 300);
  histo_time->Draw();
  TCanvas c3("c3", "Third canvas", 400, 300);
gStyle->SetPalette(1);
  histo_ct->Draw("LEGO2Z 0");

  // And we're good!  We won't close the file, so it can be used further in
  // the interpreter.

}

