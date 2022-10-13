void analyze() {

    double nPhotons[101]={0};
    double nHits[101]={0};
    double xpos[101];
    xpos[0]=-2500;

    for(int i=0; i<=100; i++){
      if(i>0){xpos[i]=xpos[i-1]+50;}
      TFile *f = new(TFile)(Form("output%i.root",i), "read");
      auto Photons = f->Get<TTree>("Photons");
      auto Hits = f->Get<TTree>("Hits");
      nPhotons[i] = (double)Photons->GetEntries()/1000;
      nHits[i] = (double)Hits->GetEntries()/1000;
      f->Close();
    }

    auto c = new TCanvas("c", "c", 1000, 700);
    auto gr = new TGraph(101,xpos,nHits);
    gr->SetTitle("2.5 mm");
    gr->SetMarkerColor(1);
    gr->SetLineColor(1);
    gr->SetMarkerStyle(20);
    gr->GetXaxis()->SetTitle("position [um]");
    gr->GetYaxis()->SetTitle("Detected Photons");
    gr->Draw("ALP");

    TLine *l = new TLine(-500,0,-500,10.6);
    TLine *l1 = new TLine(500,0,500,10.6);
    l->Draw("same");
    l1->Draw("same");

    TFile f("output.root","RECREATE");
    c->Write();

}
