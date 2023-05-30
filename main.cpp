#include <iostream>
#include <vector>
#include <list>
using namespace std;

class regex{
public:
    vector <vector<string>> graf;
    string stare_finala;
    int iterator;
    //creez regex de la prima litera a alfabetului
    regex(string litera)
    {
        if(litera == "§")
        {
            graf = {{"q0", "§", "q0"}};
            stare_finala = "q0";
            iterator = 0;
        }
        else
        {
            graf = {{"q0", "§", "q1"}};
            graf.push_back({"q1", litera, "q2"});
            stare_finala = "q2";
            iterator = 2;
        }
    }
    //creez regex de la un anumit nod
    regex(int iterator)
    {
        string nod = "q" + to_string(iterator);
        string nod1 = "q" + to_string(iterator + 1);
        graf = {{nod, "§", nod1}};
        stare_finala = nod1;
        this->iterator = iterator;
    }
    //operator de atribuiere
    regex& operator = (const regex& r)
    {
        this->graf = r.graf;
        this->stare_finala = r.stare_finala;
        this->iterator = r.iterator;
        return *this;
    }
    //constructor neparametrizat
    regex()
    {
        graf = {{"q0", "§", "q1"}};
        stare_finala = "q1";
        iterator = 1;
    }
    //operatia de concatenare pt litera
    regex& operator * (string litera)
    {
        iterator ++;
        string nod = "q";
        nod += to_string(iterator);
        graf.push_back({stare_finala, litera, nod});
        stare_finala = nod;
        return *this;
    }
    //operatia de concatenare pt regex
    regex& operator * (regex& r)
    {
        string s = "";
        s = r.graf[0][2][1];
        int j = stoi(s) + iterator;
        graf.push_back({stare_finala, "§", "q" + to_string(j)});
        for(int i = 1; i<r.graf.size(); i++)
        {
            string s = "";
            s = r.graf[i][0][1];
            int j = stoi(s) + iterator;
            r.graf[i][0] = r.graf[i][0][0] + to_string(j);
            s = r.graf[i][2][1];
            j = stoi(s) + iterator;
            r.graf[i][2] = r.graf[i][2][0] + to_string(j);
            graf.push_back(r.graf[i]);
        }
        iterator += r.iterator;
        stare_finala = graf.back()[2];
        return *this;
    }
    //operatia de reuniune pentru o litera din alfabet
    regex& operator + (string litera)
    {
        iterator ++;
        string nod = "q";
        nod += to_string(iterator);
        graf.push_back({"q0", "§", nod});
        
        iterator ++;
        string nod1 = "q" + to_string(iterator);
        graf.push_back({nod, litera, nod1});
        
        iterator ++;
        nod = "q" + to_string(iterator);
        graf.push_back({nod1, "§", nod});
        graf.push_back({stare_finala, "§", nod});
        stare_finala = nod;
        return *this;
    }
    //reuniune intre doua regexuri pt cazul cu paranteza
    regex& operator + (regex& r)
    {
        for(int i = 0; i<r.graf.size(); i++)
        {
            iterator ++;
            string s = "";
            s = r.graf[i][0][1];
            int j = stoi(s) + iterator;
            r.graf[i][0] = r.graf[i][0][0] + to_string(j);
            s = r.graf[i][2][1];
            j = stoi(s) + iterator;
            r.graf[i][2] = r.graf[i][2][0] + to_string(j);
            graf.push_back(r.graf[i]);
        }
        graf.push_back({"q0", "§", r.graf[0][0]});
        string nod = "q" + to_string(iterator);
        iterator ++;
        string nod1 = "q" + to_string(iterator);
        graf.push_back({stare_finala, "§", nod1});
        graf.push_back({nod, "§", nod1});
        stare_finala = nod1;
        
        return *this;
    }
    //operatorul pt stelare preincrementare
    regex & operator ++()
    {
        graf.push_back({stare_finala, "§", "q1"});
        iterator ++;
        string nod = "q" + to_string(iterator);
        graf.push_back({"q0", "§", nod});
        graf.push_back({stare_finala, "§", nod});
        stare_finala = nod;
        return *this;
    }
    regex operator ++ (int a)
    {
        regex aux(*this);
        graf.push_back({stare_finala, "§", "q1"});
        iterator ++;
        string nod = "q" + to_string(iterator);
        graf.push_back({"q0", "§", nod});
        graf.push_back({stare_finala, "§", nod});
        stare_finala = nod;
        return *this;
        return aux;
    }
    
    
    void afis(){
        for(int i = 0; i< graf.size(); i++)
            cout << "nod de plecare: " << graf[i][0] << " ->  muchie: " << graf[i][1] << " -> nod final: " << graf[i][2] << endl;
        cout << "stare finala: " << stare_finala << endl;
    }
};

int main()
{
    regex a("a");
    regex b("b");
    regex d("d");
    (a++ + b*"c");
    b.afis();
}
