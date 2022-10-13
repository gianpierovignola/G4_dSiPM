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

    auto gr = new TGraph(101,xpos,nHits);
    gr->SetTitle("2 mm");
    gr->SetMarkerColor(6);
    gr->SetLineColor(6);
    gr->SetMarkerStyle(20);
    gr->GetXaxis()->SetTitle("position [um]");
    gr->GetYaxis()->SetTitle("Detected Photons");
    gr->Draw("ALP");

    TFile f("output.root","RECREATE");
    gr->Write();


}
