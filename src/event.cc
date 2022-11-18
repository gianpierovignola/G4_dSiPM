#include "event.hh"
#include "generator.hh"

MyEventAction::MyEventAction(MyRunAction*)
{
    fEdep = 0.;
    evID = 0;
}

MyEventAction::~MyEventAction()
{}

void MyEventAction::BeginOfEventAction(const G4Event* anEvent)
{
    fEdep = 0.;
    evID = 0;

}

void MyEventAction::EndOfEventAction(const G4Event* anEvent)
{
    //G4cout << "Energy deposition: " << fEdep << G4endl;

    G4AnalysisManager *man = G4AnalysisManager::Instance();

    G4ThreeVector vtx=anEvent->GetPrimaryVertex()->GetPosition();
    evID =anEvent->GetEventID();
    //std::cout << "---> End of event: " << evID << std::endl;

    man->FillNtupleIColumn(2, 0, evID);
    man->FillNtupleDColumn(2, 1, fEdep);
    man->FillNtupleDColumn(2, 2, vtx[0]);
    man->FillNtupleDColumn(2, 3, vtx[1]);
    man->AddNtupleRow(2);

}
