{
//=========Macro generated from canvas: c1/c1
//=========  (Fri Oct  3 14:24:23 2014) by ROOT version5.28/00c
   TCanvas *c1 = new TCanvas("c1", "c1",7,23,584,873);
   c1->Range(-1.3125,-2.355263,11.8125,18.03947);
   c1->SetFillColor(10);
   c1->SetBorderSize(2);
   c1->SetBottomMargin(0.14);
   
   TH2F *htemp__1 = new TH2F("htemp__1","percent:primaryEnergy",40,0,10.5,40,0.5,16);
   htemp__1->SetDirectory(0);
   htemp__1->SetStats(0);
   htemp__1->GetXaxis()->SetTitle("primaryEnergy");
   htemp__1->GetYaxis()->SetTitle("percent");
   htemp__1->Draw("");
   
   TPaveText *pt = new TPaveText(0.01,0.9434849,0.3673083,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   TText *text = pt->AddText("percent:primaryEnergy");
   pt->Draw();
   
   TGraph *graph4 = new TGraph(40);
   graph4->SetName("Graph");
   graph4->SetTitle("Graph");
   graph4->SetMarkerColor(3);
   graph4->SetMarkerStyle(21);
   graph4->SetPoint(0,10,14.85);
   graph4->SetPoint(1,9.75,14.11);
   graph4->SetPoint(2,9.5,14.09);
   graph4->SetPoint(3,9.25,13.64);
   graph4->SetPoint(4,9,14.14);
   graph4->SetPoint(5,8.75,13.62);
   graph4->SetPoint(6,8.5,13.85);
   graph4->SetPoint(7,8.25,13.65);
   graph4->SetPoint(8,8,13.89);
   graph4->SetPoint(9,7.75,12.96);
   graph4->SetPoint(10,7.5,13.09);
   graph4->SetPoint(11,7.25,13.04);
   graph4->SetPoint(12,7,13.99);
   graph4->SetPoint(13,6.75,13.57);
   graph4->SetPoint(14,6.5,13.1);
   graph4->SetPoint(15,6.25,13.98);
   graph4->SetPoint(16,6,13.1);
   graph4->SetPoint(17,5.75,13.45);
   graph4->SetPoint(18,5.5,13.29);
   graph4->SetPoint(19,5.25,12.15);
   graph4->SetPoint(20,5,11.83);
   graph4->SetPoint(21,4.75,11.47);
   graph4->SetPoint(22,4.5,12.01);
   graph4->SetPoint(23,4.25,12.38);
   graph4->SetPoint(24,4,13.14);
   graph4->SetPoint(25,3.75,12.6);
   graph4->SetPoint(26,3.5,12.22);
   graph4->SetPoint(27,3.25,13.29);
   graph4->SetPoint(28,3,13.62);
   graph4->SetPoint(29,2.75,13.25);
   graph4->SetPoint(30,2.5,14.65);
   graph4->SetPoint(31,2.25,13.98);
   graph4->SetPoint(32,2,13.93);
   graph4->SetPoint(33,1.75,13.2);
   graph4->SetPoint(34,1.5,12.62);
   graph4->SetPoint(35,1.25,11.45);
   graph4->SetPoint(36,1,2.2);
   graph4->SetPoint(37,0.75,1.4);
   graph4->SetPoint(38,0.5,1.7);
   graph4->SetPoint(39,0.25,1.98);
   
   TH1F *Graph_Graph1 = new TH1F("Graph_Graph1","Graph",100,0,10.975);
   Graph_Graph1->SetMinimum(0.055);
   Graph_Graph1->SetMaximum(16.195);
   Graph_Graph1->SetDirectory(0);
   Graph_Graph1->SetStats(0);
   graph4->SetHistogram(Graph_Graph1);
   
   graph4->Draw("p");
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
