{
//=========Macro generated from canvas: c1/c1
//=========  (Thu Oct  2 22:08:56 2014) by ROOT version5.28/00c
   TCanvas *c1 = new TCanvas("c1", "c1",7,23,1393,873);
   gStyle->SetOptFit(1);
   gStyle->SetOptStat(0);
   c1->Range(-2.27027,-4.236842,11.91892,26.02632);
   c1->SetFillColor(10);
   c1->SetBorderMode(0);
   c1->SetBorderSize(2);
   c1->SetTickx(1);
   c1->SetTicky(1);
   c1->SetLeftMargin(0.16);
   c1->SetBottomMargin(0.14);
   c1->SetFrameLineWidth(2);
   c1->SetFrameBorderMode(0);
   c1->SetFrameLineWidth(2);
   c1->SetFrameBorderMode(0);
   
   TH2F *htemp__1__2__1 = new TH2F("htemp__1__2__1","percent:primaryEnergy",40,0,10.5,40,0,23);
   htemp__1__2__1->SetDirectory(0);
   htemp__1__2__1->SetStats(0);

   Int_t ci;   // for color index setting
   ci = TColor::GetColor("#0000ff");
   htemp__1__2__1->SetLineColor(ci);
   htemp__1__2__1->SetLineWidth(2);
   htemp__1__2__1->GetXaxis()->SetTitle("neutron energy [MeV]");
   htemp__1__2__1->GetXaxis()->SetNdivisions(506);
   htemp__1__2__1->GetXaxis()->SetLabelFont(42);
   htemp__1__2__1->GetXaxis()->SetLabelSize(0.06);
   htemp__1__2__1->GetXaxis()->SetTitleSize(0.07);
   htemp__1__2__1->GetXaxis()->SetTitleFont(42);
   htemp__1__2__1->GetYaxis()->SetTitle("efficiency [%]");
   htemp__1__2__1->GetYaxis()->CenterTitle(true);
   htemp__1__2__1->GetYaxis()->SetNdivisions(506);
   htemp__1__2__1->GetYaxis()->SetLabelFont(42);
   htemp__1__2__1->GetYaxis()->SetLabelSize(0.06);
   htemp__1__2__1->GetYaxis()->SetTitleSize(0.07);
   htemp__1__2__1->GetYaxis()->SetTitleOffset(0.9);
   htemp__1__2__1->GetYaxis()->SetTitleFont(42);
   htemp__1__2__1->GetZaxis()->SetLabelFont(42);
   htemp__1__2__1->GetZaxis()->SetLabelSize(0.06);
   htemp__1__2__1->GetZaxis()->SetTitleSize(0.07);
   htemp__1__2__1->GetZaxis()->SetTitleFont(42);
   htemp__1__2__1->Draw("");
   
   TPaveText *pt = new TPaveText(0.01,0.9434849,0.3673083,0.995,"blNDC");
   pt->SetName("title");
   pt->SetBorderSize(0);
   pt->SetFillColor(0);
   pt->SetTextFont(42);
   pt->Draw();
   
   TGraph *graph = new TGraph(40);
   graph->SetName("Graph");
   graph->SetTitle("Graph");
   graph->SetFillColor(1);
   graph->SetMarkerColor(2);
   graph->SetMarkerStyle(21);
   graph->SetPoint(0,10,15.26);
   graph->SetPoint(1,9.75,14.6);
   graph->SetPoint(2,9.5,14.44);
   graph->SetPoint(3,9.25,14.08);
   graph->SetPoint(4,9,14.41);
   graph->SetPoint(5,8.75,13.93);
   graph->SetPoint(6,8.5,14.05);
   graph->SetPoint(7,8.25,14.02);
   graph->SetPoint(8,8,14.2);
   graph->SetPoint(9,7.75,13.19);
   graph->SetPoint(10,7.5,13.35);
   graph->SetPoint(11,7.25,13.23);
   graph->SetPoint(12,7,14.16);
   graph->SetPoint(13,6.75,13.93);
   graph->SetPoint(14,6.5,13.46);
   graph->SetPoint(15,6.25,13.99);
   graph->SetPoint(16,6,13.31);
   graph->SetPoint(17,5.75,13.66);
   graph->SetPoint(18,5.5,13.55);
   graph->SetPoint(19,5.25,12.52);
   graph->SetPoint(20,5,12.12);
   graph->SetPoint(21,4.75,11.62);
   graph->SetPoint(22,4.5,12.5);
   graph->SetPoint(23,4.25,12.62);
   graph->SetPoint(24,4,13.46);
   graph->SetPoint(25,3.75,12.77);
   graph->SetPoint(26,3.5,12.77);
   graph->SetPoint(27,3.25,13.62);
   graph->SetPoint(28,3,13.9);
   graph->SetPoint(29,2.75,13.72);
   graph->SetPoint(30,2.5,14.97);
   graph->SetPoint(31,2.25,14.61);
   graph->SetPoint(32,2,14.28);
   graph->SetPoint(33,1.75,13.93);
   graph->SetPoint(34,1.5,12.68);
   graph->SetPoint(35,1.25,10.94);
   graph->SetPoint(36,1,5.87);
   graph->SetPoint(37,0.75,1.38);
   graph->SetPoint(38,0.5,1.69);
   graph->SetPoint(39,0.25,1.98);
   
   TH1F *Graph_Graph_Graph_Graph131 = new TH1F("Graph_Graph_Graph_Graph131","Graph",100,0,10.975);
   Graph_Graph_Graph_Graph131->SetMinimum(0);
   Graph_Graph_Graph_Graph131->SetMaximum(16.648);
   Graph_Graph_Graph_Graph131->SetDirectory(0);
   Graph_Graph_Graph_Graph131->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   Graph_Graph_Graph_Graph131->SetLineColor(ci);
   Graph_Graph_Graph_Graph131->SetLineWidth(2);
   Graph_Graph_Graph_Graph131->GetXaxis()->SetNdivisions(506);
   Graph_Graph_Graph_Graph131->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph131->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph_Graph_Graph131->GetXaxis()->SetTitleSize(0.07);
   Graph_Graph_Graph_Graph131->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph_Graph131->GetYaxis()->SetNdivisions(506);
   Graph_Graph_Graph_Graph131->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph131->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph_Graph_Graph131->GetYaxis()->SetTitleSize(0.07);
   Graph_Graph_Graph_Graph131->GetYaxis()->SetTitleOffset(1.05);
   Graph_Graph_Graph_Graph131->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph_Graph131->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph131->GetZaxis()->SetLabelSize(0.06);
   Graph_Graph_Graph_Graph131->GetZaxis()->SetTitleSize(0.07);
   Graph_Graph_Graph_Graph131->GetZaxis()->SetTitleFont(42);
   graph->SetHistogram(Graph_Graph_Graph_Graph131);
   
   graph->Draw("p");
   
   graph2 = new TGraph(40);
   graph2->SetName("Graph");
   graph2->SetTitle("Graph");
   graph2->SetFillColor(1);
   graph2->SetMarkerColor(4);
   graph2->SetMarkerStyle(23);
   graph2->SetPoint(0,10,0.66);
   graph2->SetPoint(1,9.75,0.56);
   graph2->SetPoint(2,9.5,0.54);
   graph2->SetPoint(3,9.25,0.54);
   graph2->SetPoint(4,9,0.49);
   graph2->SetPoint(5,8.75,0.45);
   graph2->SetPoint(6,8.5,0.47);
   graph2->SetPoint(7,8.25,0.64);
   graph2->SetPoint(8,8,0.6);
   graph2->SetPoint(9,7.75,0.38);
   graph2->SetPoint(10,7.5,0.43);
   graph2->SetPoint(11,7.25,0.49);
   graph2->SetPoint(12,7,0.62);
   graph2->SetPoint(13,6.75,0.38);
   graph2->SetPoint(14,6.5,0.48);
   graph2->SetPoint(15,6.25,0.45);
   graph2->SetPoint(16,6,0.33);
   graph2->SetPoint(17,5.75,0.45);
   graph2->SetPoint(18,5.5,0.44);
   graph2->SetPoint(19,5.25,0.36);
   graph2->SetPoint(20,5,0.33);
   graph2->SetPoint(21,4.75,0.41);
   graph2->SetPoint(22,4.5,0.28);
   graph2->SetPoint(23,4.25,0.4);
   graph2->SetPoint(24,4,0.33);
   graph2->SetPoint(25,3.75,0.41);
   graph2->SetPoint(26,3.5,0.31);
   graph2->SetPoint(27,3.25,0.26);
   graph2->SetPoint(28,3,0.28);
   graph2->SetPoint(29,2.75,0.3);
   graph2->SetPoint(30,2.5,0.36);
   graph2->SetPoint(31,2.25,0.19);
   graph2->SetPoint(32,2,0.17);
   graph2->SetPoint(33,1.75,0.13);
   graph2->SetPoint(34,1.5,0.14);
   graph2->SetPoint(35,1.25,0.11);
   graph2->SetPoint(36,1,0.06);
   graph2->SetPoint(37,0.75,0);
   graph2->SetPoint(38,0.5,0);
   graph2->SetPoint(39,0.25,0.01);
   
   TH1F *Graph_Graph_Graph_Graph242 = new TH1F("Graph_Graph_Graph_Graph242","Graph",100,0,10.975);
   Graph_Graph_Graph_Graph242->SetMinimum(0);
   Graph_Graph_Graph_Graph242->SetMaximum(0.726);
   Graph_Graph_Graph_Graph242->SetDirectory(0);
   Graph_Graph_Graph_Graph242->SetStats(0);

   ci = TColor::GetColor("#0000ff");
   Graph_Graph_Graph_Graph242->SetLineColor(ci);
   Graph_Graph_Graph_Graph242->SetLineWidth(2);
   Graph_Graph_Graph_Graph242->GetXaxis()->SetNdivisions(506);
   Graph_Graph_Graph_Graph242->GetXaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph242->GetXaxis()->SetLabelSize(0.06);
   Graph_Graph_Graph_Graph242->GetXaxis()->SetTitleSize(0.07);
   Graph_Graph_Graph_Graph242->GetXaxis()->SetTitleFont(42);
   Graph_Graph_Graph_Graph242->GetYaxis()->SetNdivisions(506);
   Graph_Graph_Graph_Graph242->GetYaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph242->GetYaxis()->SetLabelSize(0.06);
   Graph_Graph_Graph_Graph242->GetYaxis()->SetTitleSize(0.07);
   Graph_Graph_Graph_Graph242->GetYaxis()->SetTitleOffset(1.05);
   Graph_Graph_Graph_Graph242->GetYaxis()->SetTitleFont(42);
   Graph_Graph_Graph_Graph242->GetZaxis()->SetLabelFont(42);
   Graph_Graph_Graph_Graph242->GetZaxis()->SetLabelSize(0.06);
   Graph_Graph_Graph_Graph242->GetZaxis()->SetTitleSize(0.07);
   Graph_Graph_Graph_Graph242->GetZaxis()->SetTitleFont(42);
   graph2->SetHistogram(Graph_Graph_Graph_Graph242);
   
   graph2->Draw("p");

   TGraph *graph3 = new TGraph(37);
   graph3->SetName("Graph");
   graph3->SetTitle("Graph");
   graph3->SetFillColor(0);
   graph3->SetMarkerColor(1);
   graph3->SetMarkerStyle(21);


double value_orig2[37][2]={
{0.49, 0.00},{0.75, 0.0},{0.99, 0.20},{1.23, 6.74},
{1.48, 7.63},{1.74, 8.33},{2.00, 8.54},{2.25, 8.68},
{2.50, 8.75},{2.75, 8.34},{3.00, 7.90},{3.25, 7.40},
{3.50, 6.82},{3.74, 6.83},{4.00, 6.83},{4.49, 5.95},
{4.74, 5.97},{4.98, 5.96},{5.26, 6.57},{5.50, 7.16},
{5.75, 6.89},{6.00, 6.57},{6.25, 6.35},{6.50, 6.23},
{6.74, 6.16},{7.00, 5.90},{7.24, 5.76},{7.49, 5.63},
{7.74, 5.64},{7.98, 5.51},{8.24, 5.64},{8.50, 5.65},
{8.76, 5.76},{9.00, 5.90},{9.25, 5.96},{9.50, 6.24},
{10.00, 6.62}
};

for(int i =0; i<37 ;i++)
   graph3->SetPoint(i,value_orig2[i][0],value_orig2[i][1]);
	
   graph3->SetHistogram(Graph_Graph_Graph_Graph242);
	graph3->Draw("p");
	

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
   
   graph3->SetHistogram(Graph_Graph_Graph_Graph242);
   graph4->Draw("p");

   
   TLegend *leg = new TLegend(0.5805627,0.3098592,0.8994032,0.528169,NULL,"brNDC");
   leg->SetBorderSize(1);
   leg->SetTextFont(62);
   leg->SetLineColor(1);
   leg->SetLineStyle(1);
   leg->SetLineWidth(1);
   leg->SetFillColor(10);
   leg->SetFillStyle(1001);
   leg->AddEntry(graph3,"MCNP once scintillator","p");
   leg->AddEntry(graph,"Geant4 one scintillator","p");
   leg->AddEntry(graph4,"Geant4 linear energy deposition","p");
   leg->AddEntry(graph2,"Geant4 two scintillators","p");
   leg->Draw();
   c1->Modified();
   c1->cd();
   c1->SetSelected(c1);
}
