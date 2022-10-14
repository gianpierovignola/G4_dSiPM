#include "run.hh"

MyRunAction::MyRunAction()
{
    fMessenger = new G4GenericMessenger(this, "/run/", "run prop");
    fMessenger->DeclareProperty("fname", fname, "fname");
    fMessenger->DeclareProperty("fxpos", fxpos, "file_namexpos");
    fMessenger->DeclareProperty("fypos", fypos, "file_nameypos");

    fname = "temp";
    fxpos = "temp";
    fypos = "temp";

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->CreateNtuple("Photons", "Photons");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->CreateNtupleDColumn("fWlen");
    man->FinishNtuple(0);

    man->CreateNtuple("Hits", "Hits");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    //man->CreateNtupleDColumn("xGun");
    //man->CreateNtupleDColumn("yGun");
    man->FinishNtuple(1);

    man->CreateNtuple("Scoring", "Scoring");
    man->CreateNtupleDColumn("fEdep");
    man->FinishNtuple(2);
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run* run)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    G4int runID = run->GetRunID();

    std::stringstream strRunID;
    strRunID << runID;

    man->OpenFile(fname+"_"+fxpos+"_"+fypos+".root");

}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->Write();
    man->CloseFile();
}
