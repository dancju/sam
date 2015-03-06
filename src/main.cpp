#include<iostream>
#include<map>
#include<sstream>
#include<vector>

using namespace std;

class SAM {

    struct State {
        size_t id, val;
        State *pare;
        map<char, State*> trans;
        State(size_t id, size_t val) {
            this->id = id;
            this->val = val;
            this->pare = NULL;
        }
    };

    State *last;
    vector<State*> pool;

    public:

    typedef const State* iterator;

    SAM() { pool.push_back(last = new State(0, 0)); }

    ~SAM() { for_each(pool.begin(), pool.end(), [](State *i) { delete i; }); }

    inline void clear() {
        for_each(pool.begin(), pool.end(), [](State *i) { delete i; });
        pool.push_back(last = new State(0, 0));
    }

    inline void insert(char x) {
        State *p = last, *np = new State(pool.size(), last->val+1);
        pool.push_back(last = np);
        for(; p && p->trans[x]==NULL; p = p->pare)
            p->trans[x] = np;
        if(p==NULL) {
            np->pare = pool[0];
            return;
        }
        State *q = p->trans[x];
        if(p->val+1 == q->val)
            np->pare = q;
        else {
            State *nq = new State(pool.size(), p->val+1);
            pool.push_back(nq);
            nq->pare = q->pare;
            q->pare = np->pare = nq;
            for(; p && p->trans[x]==q; p = p->pare)
                p->trans[x] = nq;
        }
    }

    inline string toDot() const {
        stringstream ss;
        ss << "digraph {" << endl;
        ss << "  node[shape=circle];" << endl;
        ss << "  edge[arrowhead=vee];" << endl;
        ss << "  START[shape=point, color=white];" << endl;
        ss << "  START -> 0 [label=start];" << endl;
        for(State *i = last; i; i = i->pare)
            ss << "  " << i->id << " [shape=doublecircle];" << endl;
        for_each(pool.begin(), pool.end(), [&](State *s) {
            for_each(s->trans.begin(), s->trans.end(), [&](pair<const char, State*> i) {
                ss << "  " << s->id << " -> " << i.second->id << " [label=\"" << i.first << "\"];" << endl;
            });
        });
        ss << "  edge[color=indianred,arrowhead=none];" << endl;
        for_each(pool.begin()+1, pool.end(), [&](State *s) {
            ss << "  " << s->pare->id << " -> " << s->id << endl;
        });
        ss << "}" << endl;
        string res(ss.str());
        return res;
    }

};

int main() {
    SAM sam;
    string s;
    cin >> s;
    for_each(s.begin(), s.end(), [&](char i) { sam.insert(i); });
    cout << sam.toDot();
    return 0;
}

extern "C" {
    const char* sam(char* s) {
        SAM sam;
        for(char *i = s; *i; i++)
            sam.insert(*i);
        return sam.toDot().c_str();
    }
}
