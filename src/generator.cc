#include "generator.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);

    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4String particleName="e-";
    G4ParticleDefinition *particle = particleTable->FindParticle("e-");

    G4ThreeVector pos(0.,0.,0.);

    //G4ThreeVector pos(0.5*mm,0.5*mm,0.);

    //G4ThreeVector pos(1.10*mm,1.2*mm,0.);

    G4ThreeVector mom(0.,0.,1.);

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleMomentum(4*GeV);
    fParticleGun->SetParticleDefinition(particle);
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
    delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    fParticleGun->GeneratePrimaryVertex(anEvent);
    /*
    G4double gunx = fParticleGun->GetParticlePosition().x();
    G4double guny = fParticleGun->GetParticlePosition().y();
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->FillNtupleDColumn(1, 4, gunx);
    man->FillNtupleDColumn(1, 5, guny);
    man->AddNtupleRow(1);
    */
}
