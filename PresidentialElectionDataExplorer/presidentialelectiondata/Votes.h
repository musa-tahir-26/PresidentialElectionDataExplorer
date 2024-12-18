#ifndef VOTES_H
#define VOTES_H

class Votes {
    public:
    void setVotingData (string vState = "", string vCounty = "", string vCandidate = "", string vParty = "", int votes = 0) {
        state = vState;
        county = vCounty;
        candidate = vCandidate;
        party = vParty;
        numVotes = votes;  
    }

    string getVoteState() const {return state;};
    string getVoteCounty() const {return county;};
    string getVoteCandidate() const {return candidate;};
    string getVoteParty() const {return party;};
    int getNumVotes() const {return numVotes;};

    void setVoteState(string st) {state = st;};
    void setVoteCounty(string ct) {county = ct;};
    void setVoteCandidate(string nm) {candidate = nm;};
    void setVoteParty(string pt) {party = pt;};
    void setNumVotes(int input) {numVotes = input;};
    
    bool operator<(const Votes& other) const {
        return numVotes < other.numVotes;
    }

    
    private:
    string state, county, candidate, party = "";
    int numVotes = 0;
    
};

#endif