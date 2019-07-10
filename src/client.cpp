#include "client.h"

using namespace std;

bool Client::add(const int id, set<string> db, Server* server)
{
    int cnt = 0;
    vector<AddToken> *addTokens = new vector<AddToken>();
    string k_doc = Util::f2_sha(k_s, id);

    // -1 to solve empty string
    for (set<string>::iterator it = db.begin(); it!=db.end(); ++it) {
        if (*it == "") continue;
        string w = *it;
        string k_w = Util::f1_sha(k_s, w);
        string tau, r;
        if (A.find(w) == A.end()) {
            tau = Util::prf_ran();
            r = Util::set(0);
        } else {
            tau = A[w];
            r = Util::prf_ran();
            tau = Util::xor_string(tau, r);
        }
        A[w] = tau;
        //if (w == "Path\r") cout << "id:\t" << id << "\ttau:\t" << tau << endl;
        string loc = Util::f1_sha(k_w, tau);
        string coat = Util::h2_sha(k_w, tau+"2");
        string coatp = Util::h2_sha(k_w, tau+"4");
        ++cnt;
        string pos = Util::f1_sha(k_doc, Util::set(cnt));
        string datap = Util::xor_string(Util::set(id), coatp);
        string data = Util::xor_string(coat, pos+r);
        addTokens->push_back(AddToken(loc, data, pos, datap));
    }
    server->add(addTokens);
    return true;
}

vector<string> Client::search(const string keyword, Server *server) 
{
    if (debug) cout << keyword << endl;
    if (A.find(keyword) != A.end()) {
        string k_w = Util::f1_sha(k_s, keyword);
        SearchToken *stk = new SearchToken(k_w, A[keyword]);
        return server->search(stk);
    } else {
        return server->search(NULL);
    }
}