#ifndef CANDIDATE_H
#define CANDIDATE_H

class Candidate {
    public:
    string candName, party;
    int numVotes = 0;
    

    void setVotingData (string vCandidate = "", string vParty = "", int votes = 0) {
        candName = vCandidate;
        party = vParty;
        numVotes = votes;
    }

    bool operator<(const Candidate& other) const {
        return numVotes < other.numVotes;
    }

};

#endif