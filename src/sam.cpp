#include<map>
#include<sstream>
#include<vector>

using namespace std;

class SAM {

    struct state {
        size_t id, val;
        state *pare;
        map<char, state*> trans;
        state(size_t id, size_t val) {
            this->id = id;
            this->val = val;
            this->pare = NULL;
        }
    };

    state *last;
    vector<state*> pool;

public:

    typedef const state* iterator;

    SAM() { pool.push_back(last = new state(0, 0)); }

    ~SAM() { for_each(pool.begin(), pool.end(), [](state *i) { delete i; }); }

    inline void clear() {
        for_each(pool.begin(), pool.end(), [](state *i) { delete i; });
        pool.push_back(last = new state(0, 0));
    }

    inline void insert(char x) {
        state *p = last, *np = new state(pool.size(), last->val+1);
        for(; p && p->trans[x]==NULL; p = p->pare)
            p->trans[x] = np;
        pool.push_back(last = np);
        if(p==NULL) {
            np->pare = pool[0];
            return;
        }
        state *q = p->trans[x];
        if(p->val+1 == q->val)
            np->pare = q;
        else {
            state *nq = new state(pool.size(), p->val+1);
            pool.push_back(nq);
            nq->trans = q->trans;
            nq->pare = q->pare;
            q->pare = np->pare = nq;
            for(; p && p->trans[x]==q; p = p->pare)
                p->trans[x] = nq;
        }
    }

    inline string to_dot() const {
        stringstream ss;
        ss << "digraph {" << endl;
        ss << "  node[shape=circle];" << endl;
        ss << "  edge[arrowhead=vee];" << endl;
        ss << "  START[shape=point, color=white];" << endl;
        ss << "  START -> 0 [label=start];" << endl;
        for(state *i = last; i; i = i->pare)
            ss << "  " << i->id << " [shape=doublecircle];" << endl;
        for_each(pool.begin(), pool.end(), [&](state *s) {
            for_each(s->trans.begin(), s->trans.end(), [&](pair<const char, state*> i) {
                ss << "  " << s->id << " -> " << i.second->id << " [label=\"" << i.first << "\"];" << endl;
            });
        });
        ss << "  edge[color=indianred,arrowhead=none];" << endl;
        for_each(pool.begin()+1, pool.end(), [&](state *s) {
            ss << "  " << s->pare->id << " -> " << s->id << endl;
        });
        ss << "}" << endl;
        string res(ss.str());
        return res;
    }

};
