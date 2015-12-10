#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdlib.h>
#define EPSILONE "#"

using namespace std;

// Structure d'une règle
typedef struct s_regle
{
    string g, d;
} t_regle;

// Structure d'un non Terminal
typedef struct s_nT
{
    string v, w; // valeur
    bool recur; // récursivité gauche directe
    int nb; // nombre
} t_nT;

// Lecture de fichier
vector<t_regle> lecture(string url)
{
    ifstream fichier(url.c_str(), ios::in);
    vector<t_regle> grammaire;

    if(fichier)
    {
        string memoire = "";
        vector<t_regle> grammaire;
        char input;
        bool first = true;
        t_regle temp;

        while(fichier.get(input))
        {
            if(input == ' ' && first)
            {
                first = false;
                temp.g = memoire;
                memoire = "";
            }
            else if(input == '\n' && !first)
            {
                first = true;
                temp.d = memoire;
                grammaire.push_back(temp);
                memoire = "";
            }
            else
            {
                memoire += input;
            }
        }

        fichier.close();
        return grammaire;
    }
    else
    {
        cout << "ERREUR : Fichier " << url << " inexistant" << endl;
        fichier.clear();
        return grammaire;
    }
    return grammaire;
}

// Ecriture dans un fichier
bool ecrire(string url, vector<t_regle> const& grammaire)
{
    ofstream fichier(url.c_str());

    if(fichier)
    {
        for(vector<t_regle>::const_iterator i = grammaire.begin(); i != grammaire.end(); i++)
        {
            fichier << i->g << " " << i->d << "\n";
        }
        fichier << "\n";
    }
    else
    {
        cout << "Erreur d'ecriture dans le fichier " << url << endl;
        fichier.clear();
        return false;
    }
    fichier.close();
    return true;
}

// Vérifie si un non-terminal est dans la liste
bool nonTerminalExist(vector<t_nT> const& grammaire, string e)
{
    for(vector<t_nT>::const_iterator it = grammaire.begin(); it != grammaire.end(); it++)
    {
        if(it->v == e) return true;
    }
    return false;
}

// Vérifie si une règle contient une récursivité gauche directe
bool matchRecursiviteDirecte(t_regle regle)
{
    if(regle.g > regle.d) return false;
    for(unsigned int i = 0; i < regle.g.size(); i++)
    {
        if(regle.g[i] != regle.d[i]) return false;
    }
    return true;
}

// Renvoie une liste d'alphabet non terminal
vector<t_nT> alphabetNonTerminal(vector<t_regle> const& grammaire)
{
    vector<t_nT> nonTerminaux;
    for(vector<t_regle>::const_iterator it = grammaire.begin(); it != grammaire.end(); it++)
    {
        if(!nonTerminalExist(nonTerminaux, it->g))
        {
            t_nT temp;
            temp.v = it->g;
            temp.w = temp.v + "'";
            temp.recur = false;
            nonTerminaux.push_back(temp);
        }
    }
    return nonTerminaux;
}

// Vérifie pour chaque non-terminal de la liste s'il y a une récursivité gauche directe
bool remplirRecursionNonTerminal(vector<t_regle> const& grammaire, vector<t_nT> &nonTerminaux)
{
    int nb = 0;
    bool recursion = false;
    for(vector<t_nT>::iterator i = nonTerminaux.begin(); i != nonTerminaux.end(); i++)
    {
        nb = 0;
        for(vector<t_regle>::const_iterator j = grammaire.begin(); j != grammaire.end(); j++)
        {
            if(i->v == j->g)
            {
                if(matchRecursiviteDirecte(*j)) { i->recur = true; recursion = true; }
                nb++;
            }
        }
        i->nb = nb;
    }
    return recursion;
}

// Afficher la grammaire
string Afficher(vector<t_regle> const& grammaire)
{
    /*
    // Sous linux
    for(vector<t_regle>::const_iterator it = grammaire.begin(); it != grammaire.end(); it++)
    {
        cout << it->g << " -> " << it->d << endl;
    }
    */
    // Sous Windows
    vector<t_nT> nonTerminaux = alphabetNonTerminal(grammaire);
    remplirRecursionNonTerminal(grammaire, nonTerminaux);
    int nb = 0;
    string out = "";
    for(vector<t_nT>::iterator i = nonTerminaux.begin(); i != nonTerminaux.end(); i++)
    {
        nb = 0;
        //cout << i->v << ((i->v.size() > 1) ? "" : " ") << " -> ";
        out += i->v + ((i->v.size() > 1) ? "" : " ") + " -> ";
        for(vector<t_regle>::const_iterator j = grammaire.begin(); j != grammaire.end(); j++)
        {
            if(i->v == j->g)
            {
                //cout << j->d;
                out += j->d;
                nb++;
                if(nb < i->nb)
                {
                    //cout << " | ";
                    out += " | ";
                }
            }
        }
        //cout << endl;
        out += "\n";
    }
    return out;
}

// Afficher les non-terminaux
string AfficherNonTerminaux(vector<t_nT> const& nonTerminaux)
{
    string out = "";
    for(vector<t_nT>::const_iterator it = nonTerminaux.begin(); it != nonTerminaux.end(); it++)
    {
        //cout << it->v << " ";
        out += it->v + " ";
    }
    return out;
}

// Tri la grammaire par ordre des symboles gauches
vector<t_regle> triSymboles(vector<t_regle> const& grammaire, vector<t_nT> const& nonTerminaux)
{
    vector<t_regle> grammaire_triee;
    for(vector<t_nT>::const_iterator i = nonTerminaux.begin(); i != nonTerminaux.end(); i++)
    {
        for(vector<t_regle>::const_iterator j = grammaire.begin(); j != grammaire.end(); j++)
        {
            if(i->v == j->g) grammaire_triee.push_back(*j);
        }
        for(vector<t_regle>::const_iterator j = grammaire.begin(); j != grammaire.end(); j++)
        {
            if(i->recur && i->w == j->g) grammaire_triee.push_back(*j);
        }
    }
    return grammaire_triee;
}

// Renvoie une grammaire équivalente qui contenait une récursivité gauche directe
void RecursiviteGaucheDirecteA(vector<t_regle> &grammaire, t_nT regle)
{
    vector<t_regle> grammaire2;

    for(vector<t_regle>::iterator j = grammaire.begin(); j != grammaire.end(); j++)
    {
        if(regle.recur && regle.v == j->g)
        {
            t_regle temp;
            if(matchRecursiviteDirecte(*j))
            {
                temp.g = regle.w;
                temp.d = j->d + temp.g;
                temp.d.erase(0, j->g.size());
            }
            else
            {
                temp.g = j->g;
                temp.d = j->d + regle.w;
            }
            grammaire2.push_back(temp);
        }
        else grammaire2.push_back(*j);
    }

    if(regle.recur)
    {
        t_regle temp;
        temp.g = regle.w;
        temp.d = EPSILONE;
        grammaire2.push_back(temp);
    }
    grammaire.clear();
    grammaire = grammaire2;
}

// Renvoie une grammaire équivalente qui contenait une récursivité gauche directe
vector<t_regle> RecursiviteGaucheDirecte(vector<t_regle> &grammaire)
{
    vector<t_nT> nonTerminaux = alphabetNonTerminal(grammaire);
    remplirRecursionNonTerminal(grammaire, nonTerminaux);

    vector<t_regle> grammaire2;

    for(vector<t_nT>::iterator i = nonTerminaux.begin(); i != nonTerminaux.end(); i++)
    {
        RecursiviteGaucheDirecteA(grammaire, *i);
    }
    vector<t_regle> grammaire_triee = triSymboles(grammaire, nonTerminaux);
    nonTerminaux.clear();
    grammaire2.clear();
    return grammaire_triee;
}

// Remplacer Ai -> b1a | ... où Aj -> b1 | ...
vector<t_regle> RemplacementAiAj(vector<t_regle> const& grammaire, string Ai, string Aj, bool *remplacement)
{
    vector<t_regle> grammaire2;
    for(vector<t_regle>::const_iterator i = grammaire.begin(); i != grammaire.end(); i++)
    {
        if(Ai != Aj)
        {
            t_regle temp;
            temp.g = Aj;
            temp.d = i->d;
            if(i->g == Ai && matchRecursiviteDirecte(temp))
            {
                for(vector<t_regle>::const_iterator j = grammaire.begin(); j != grammaire.end(); j++)
                {
                    if(i->g != j->g && i->d != j->d && j->g == Aj)
                    {
                        temp.g = i->g;
                        temp.d = i->d;
                        temp.d.replace(0, Ai.size(), j->d);
                        grammaire2.push_back(temp);
                        *remplacement = true;
                    }
                }
            }
            else
            {
                grammaire2.push_back(*i);
            }
        }
        else grammaire2.push_back(*i);
    }
    return grammaire2;

}

// Renvoie une grammaire équivalente qui contenait une récursivité gauche (algo générale)
vector<t_regle> RecursiviteGauche(vector<t_regle> & grammaire)
{
    vector<t_nT> nonTerminaux = alphabetNonTerminal(grammaire);
    remplirRecursionNonTerminal(grammaire, nonTerminaux);

    vector<t_regle> grammaire2;
    bool remplacement = false;
    for(vector<t_nT>::iterator i = nonTerminaux.begin(); i != nonTerminaux.end(); i++)
    {
        for(unsigned int j = 0; j < grammaire.size(); j++)
        {
            remplacement = false;
            for(unsigned int k = 0; k <= j; k++)
            {
                if(i->v == grammaire[j].g)
                {
                    t_regle temp;
                    temp.g = grammaire[k].g;
                    temp.d = grammaire[j].d;
                    if(matchRecursiviteDirecte(temp))
                    {
                        grammaire = RemplacementAiAj(grammaire, grammaire[j].g, grammaire[k].g, &remplacement);
                    }
                }
            }
            if(remplacement)
            {
                RecursiviteGaucheDirecteA(grammaire, *i);
            }
        }
    }

    vector<t_regle> grammaire_triee = triSymboles(grammaire, nonTerminaux);

    return grammaire_triee;
}

// Retourne le plus grand préfix entre deux strings
string RetournerPrefix(string a, string b)
{
    unsigned int size;
    if(a.size() < b.size()) size = a.size();
    else size = b.size();

    string prefix = "";

    for(unsigned int i = 0; i < size; i++)
    {
        if(a[i] != b[i]) return prefix;
        prefix += a[i];
    }
    return prefix;
}

// Trouver un prefix commun
string TrouverPrefix(vector<t_regle> const& grammaire, t_nT nonTerminal)
{
    string prefix = "";
    unsigned int size = 0;
    int k = 0;
    for(vector<t_regle>::const_iterator i = grammaire.begin(); i != grammaire.end(); i++)
    {
        for(vector<t_regle>::const_iterator j = grammaire.begin(); j != grammaire.end(); j++)
        {
            if(i->g == j->g && i->d != j->d && i->g == nonTerminal.v)
            {
                string temp = RetournerPrefix(i->d, j->d);
                if(size < temp.size())
                {
                    prefix = temp;
                    size = prefix.size();
                }
                k++;
            }
        }
    }

    if(k > 1) return prefix;
    return "";
}

// Vérifie si a contient prefix
bool contientPrefix(string prefix, string a)
{
    if(prefix.size() > a.size()) return false;
    for(unsigned int i = 0; i < prefix.size(); i++)
    {
        if(prefix[i] != a[i]) return false;
    }
    return true;
}

// Vérifie si une règle existe dans la grammaire
bool regleExist(vector<t_regle> const& grammaire, t_regle e)
{
    for(vector<t_regle>::const_iterator i = grammaire.begin(); i != grammaire.end(); i++)
    {
        if(i->g == e.g && i->d == e.d) return true;
    }
    return false;
}

// Tri la grammaire
vector<t_regle> trier(vector<t_regle> const& grammaire, vector<t_nT> const& nonTerminaux, vector<t_nT> const& nonTerminauxInit)
{
    vector<t_nT> nonTerminauxTries;
    // Tri des non-terminaux
    for(vector<t_nT>::const_iterator i = nonTerminauxInit.begin(); i != nonTerminauxInit.end(); i++)
    {
        nonTerminauxTries.push_back(*i);
        for(vector<t_nT>::const_iterator j = nonTerminaux.begin(); j != nonTerminaux.end(); j++)
        {
            if(i->v != j->v && contientPrefix(i->v, j->v)) nonTerminauxTries.push_back(*j);
        }
    }
    vector<t_regle> grammaire_triee;
    // Tri des règles
    for(vector<t_nT>::const_iterator i = nonTerminauxTries.begin(); i != nonTerminauxTries.end(); i++)
    {
        for(vector<t_regle>::const_iterator j = grammaire.begin(); j != grammaire.end(); j++)
        {
            if(i->v == j->g && !regleExist(grammaire_triee, *j)) grammaire_triee.push_back(*j);
        }
    }
    return grammaire_triee;
}

// Factorisation gauche
void FactorisationGauche(vector<t_regle> &grammaire)
{
    vector<t_nT> nonTerminaux = alphabetNonTerminal(grammaire);
    vector<t_nT> nonTerminauxInit = nonTerminaux;
    remplirRecursionNonTerminal(grammaire, nonTerminaux);

    string prefix;
    bool prefixAdd = false;
    vector<t_regle> grammaire2;
    for(unsigned int i = 0; i < nonTerminaux.size(); i++)
    {
        while((prefix = TrouverPrefix(grammaire, nonTerminaux[i])) != "")
        {
            if(prefix != EPSILONE)
            {
                prefixAdd = false;
                nonTerminaux = alphabetNonTerminal(grammaire);
                for(unsigned int j = 0; j < grammaire.size(); j++)
                {
                    if(nonTerminaux[i].v == grammaire[j].g)
                    {
                        if(contientPrefix(prefix, grammaire[j].d))
                        {
                            string temp = grammaire[j].g + "'";
                            if(nonTerminalExist(nonTerminaux, temp))
                            {
                                grammaire[j].g = temp + "'";
                            }
                            else grammaire[j].g = temp;

                            if((grammaire[j].d.size() - prefix.size()) > 0) grammaire[j].d.erase(0, prefix.size());
                            else grammaire[j].d = EPSILONE;

                            prefixAdd = true;
                        }
                    }
                }

                if(prefixAdd)
                {
                    t_regle temp;
                    temp.g = nonTerminaux[i].v;
                    temp.d = prefix + nonTerminaux[i].v + "'";
                    if(nonTerminalExist(nonTerminaux, nonTerminaux[i].v + "'"))
                    {
                        temp.d = temp.d + "'";
                    }
                    grammaire.push_back(temp);
                }
            }
        }
    }
    nonTerminaux = alphabetNonTerminal(grammaire);
    grammaire = trier(grammaire, nonTerminaux, nonTerminauxInit);
}

int main()
{
    string url = "";
    vector<t_regle> grammaire;
    bool recursionDirecte = false;
    bool input = true;
    do
    {
        cout << "Entrez le nom du fichier a traiter : ";
        cin >> url;
        cin.clear();
        grammaire = lecture(url);
        if(grammaire.size() > 0) input = false;
    } while(input);

    string out = "Fichier : " + url;

    vector<t_nT> nonTerminaux = alphabetNonTerminal(grammaire);

    //cout << "\nGrammaire G :" << endl;
    out += "\nGrammaire G :\n";
    out += Afficher(grammaire);

    recursionDirecte = remplirRecursionNonTerminal(grammaire, nonTerminaux);

    //cout << "\nSymboles non-terminaux : ";
    out += "\nSymboles non-terminaux : ";
    out += AfficherNonTerminaux(nonTerminaux);
    //cout << endl;
    out += "\n";

    if(recursionDirecte)
    {
        //cout << "\nG contient au moins une recursion gauche directe" << endl;
        out += "\nG contient au moins une recursion gauche directe\n";

        grammaire = RecursiviteGaucheDirecte(grammaire);
        //cout << "\nGrammaire G' (apres elimination de la recursivite gauche directe) :" << endl;
        out += "\nGrammaire G' (apres elimination de la recursivite gauche directe) :\n";
        out += Afficher(grammaire);
    }
    else
    {
        //cout << "\nG ne contient pas de recursion gauche directe" << endl;
        out += "\nG ne contient pas de recursion gauche directe\n";
    }

    grammaire = RecursiviteGauche(grammaire);
    //cout << "\nGrammaire G' (apres elimination de toutes recursivites, si presente) :" << endl;
    out += "\nGrammaire G' (apres elimination de toutes recursivites, si presente) :\n";
    out += Afficher(grammaire);

    FactorisationGauche(grammaire);
    //cout << "\nGrammaire G'' (apres factorisation gauche, si possible) : " << endl;
    out += "\nGrammaire G'' (apres factorisation gauche, si possible) : \n";
    out += Afficher(grammaire);

    do
    {
        url = "";
        cout << "\nNom du fichier genere : ";
        cin >> url;
        cin.clear();
    } while(url == "");

    if(ecrire(url, grammaire))
    {
        //cout << "\nGrammaire equivalente ecrite dans le fichier '" << url << "' avec succes." << endl;
        out += "\nGrammaire equivalente ecrite dans le fichier '" + url + "' avec succes.\n";
    }

    cout << "\n" << out;

    ofstream traces("traces.txt");
    if(traces) traces << out;

    return 0;
}
