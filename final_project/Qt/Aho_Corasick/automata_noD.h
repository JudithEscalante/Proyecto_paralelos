using namespace std;

#include <algorithm>
#include <iostream>
#include <iterator>
#include <numeric>
#include <sstream>
#include <fstream>
#include <cassert>
#include <climits>
#include <cstdlib>
#include <cstring>
#include <string>
#include <cstdio>
#include <vector>
#include <cmath>
#include <queue>
#include <deque>
#include <stack>
#include <list>
#include <map>
#include <set>





template <class V,class D>
class automata_noD
{
   public:
    automata_noD();
    map<V, map<D,V> > grafito;
    void insertar(const V &v1,const D &dis,const V &v2);
    vector<string> limpiar_texto();
    string resultado;

    int out[27550];
    int f[27550];
    int g[27550][26];
    int states = 1;
    int construir_automata(string arr[], int k,automata_noD& grafo1);
    int sig_estado(int currentState, char nextInput);
    void buscar_palbras(string arr[], int k, string text,automata_noD& grafo1);
    void generar_dot(automata_noD & automata1);

};

template <class V,class D>
automata_noD<V,D>::automata_noD()
{
    //grafito=new map<V,map<D,V> >();
}
template <class V,class D>
int automata_noD<V,D>::construir_automata(string arr[], int k,automata_noD& grafo1)
{
    int MAXC=26;
    memset(out, 0, sizeof out);

    memset(g, -1, sizeof g);




    for (int i = 0; i < k; ++i)
    {
        const string &word = arr[i];
        int currentState = 0;

        for (int j = 0; j < word.size(); ++j)
        {

            int ch = word[j] - 'a';



            /*if (g[currentState][ch] == -1)
            {
                g[currentState][ch] = states++;
                states--;
            }*/
                //currentState = g[currentState][ch];

            if (grafo1.grafito.find(currentState)==grafo1.grafito.end()){
                grafo1.grafito[currentState][ch]=states++;
            }
            else{
                if (grafo1.grafito[currentState].find(ch)==grafo1.grafito[currentState].end()){
                    grafo1.grafito[currentState][ch]=states++;

                }
            }
            currentState=grafo1.grafito[currentState][ch];
            /************************/

            //cout<<"ffshg "<<grafo1.grafito.size()<<endl;

        }


        out[currentState] |= (1 << i);
    }



    for (int ch = 0; ch < MAXC; ++ch)
        if (g[0][ch] == -1)
            g[0][ch] = 0;

    memset(f, -1, sizeof f);

    queue<int> q;

    for (int ch = 0; ch < MAXC; ++ch)
    {

        if (g[0][ch] != -1 && g[0][ch]!=0)
        {
            f[g[0][ch]] = 0;
            q.push(g[0][ch]);
        }
    }

    for (int ch = 0; ch < MAXC; ++ch)
    {

        if (g[0][ch] != 0)
        {
            f[g[0][ch]] = 0;
            q.push(g[0][ch]);
        }
    }

    // Now queue has states 1 and 3
    while (q.size())
    {
        int state = q.front();
        q.pop();

        for (int ch = 0; ch <= MAXC; ++ch)
        {

            if (g[state][ch] != -1)
            {
                int failure = f[state];

                while (g[failure][ch] == -1)
                      failure = f[failure];

                failure = g[failure][ch];
                f[g[state][ch]] = failure;

                out[g[state][ch]] |= out[failure];

                q.push(g[state][ch]);
            }
        }
    }
    cout<<"numero estados"<<endl;
    cout<<states<<endl;
    return states;
}
template <class V,class D>
int automata_noD<V,D>::sig_estado(int currentState, char nextInput)
{
    int answer = currentState;
    int ch = nextInput - 'a';

    while (g[answer][ch] == -1)
        answer = f[answer];

    return g[answer][ch];

}

template <class V,class D>
void automata_noD<V,D>::buscar_palbras(string arr[], int k, string text,automata_noD& grafo1)
{

       construir_automata(arr, k,grafo1);

       int currentState = 0;
        //recorremos el texto en nuestro automta para buscar todas las apariciones de las palabras de arr[]
       for (int i = 0; i < text.size(); ++i)
       {
           currentState = sig_estado(currentState, text[i]);
           // si no se encuentra coincidencia se pasa al siguente estado
           if (out[currentState] == 0)
           {
                continue;
           }
           // Coincidencia encontrada, imprimir todas las palabras coincidentes de matriz [] // utilizando la función de out.
           for (int j = 0; j < 3000; ++j)
           {
               if (out[currentState] & (1 << j))
               {

                   //cout<<"siiii"<<endl;
                   string pala;
                   for(int k=0;k<text.size();k++)
                   {
                        pala=pala+text[k];
                        if(k==i - arr[j].size() || k==i)
                        {
                            pala=pala+'-';
                        }
                   }
                   //string final="La palabra \""+arr[j]+"\"aparece en el texto en: "+pala;
                   //resultado=resultado+final+"\n";

                        //cout << "La palabra " <<"\""<<arr[j] <<"\""<< " aparece en el texto en: "<<pala<<endl;
                        //cout << "La palabra " << arr[j] << "aparece en el texto en:"
                        //<< i - arr[j].size() + 1 << " to " << i << endl;*/


                       //cout << "Word " << arr[j] << " appears from "
                         //   << i - arr[j].size() + 1 << " to " << i << endl;


               }
           }
       }

}

template <class V, class D>
void automata_noD<V,D> ::insertar(const V &v1,const D &dis,const V &v2)
{
    pair<D,V> arista=make_pair(dis,v2);// =(dis,v2) ;
    grafito.insert(make_pair(v1,arista));
}

template <class V,class D>
void automata_noD<V,D>::generar_dot(automata_noD & automata1)
{
    /*for(int i=0;i<states;i++)
    {
        for(int j=0;j<26;j++)
        {
            int temp=g[i][j];
            if(temp!=-1 && temp!=0)
            {
                char peso=j+97;
                automata1.insertar(i,peso,temp);

            }
        }
    }
*/


    if(grafito.empty())
       return;
    else{
        ofstream fi("grafo.dot");
        fi<<"digraph dfa {"<<endl;
        fi<<"  rankdir=LR;"<<endl;
        fi<<"  \"\""<< "   [shape=none]"<<endl;
        fi<<"  \"\"  -> \""<<0<<"\""<<endl;
        typename map<V, map<D,V> > ::iterator it;
        it =grafito.begin();
        while(it!= grafito.end()){
            typename map<D,V> ::iterator it2;
            it2=(*it).second.begin();
            while(it2!=(*it).second.end()){
                char pala=it2->first+97;
                fi<<"  \""<<it->first<<"\""<<" -> "<<"\""<<it2->second<<"\"  [label=\""<<pala<<"\"]"<<endl;
            it2++;
            }
            ++it;
        }
        fi<<"}"<<endl;
    }
    //system("dot -Tpdf grafo.dot -o automata.pdf");
    //system("evince automata.pdf");
    system("dot grafo.dot -Tpng -o grafo.png");

    cout<<"termino doc"<<endl;


}

template <class V,class D>

vector<string> automata_noD<V,D>::limpiar_texto()
{

        vector<string> v;
        ifstream file_;
        file_.open("ejemplo.txt");
        while (!file_.eof()){
            string linea,buf;
            getline(file_, linea);

            transform(buf.begin(), buf.end(), buf.begin(), ::tolower);
            stringstream ss(linea);
            while (ss >> buf){
                string temp="";
                replace(buf.begin(),buf.end(),'\'',' ');
                for (int i=0;i<buf.length();++i){
                        transform(buf.begin(), buf.end(), buf.begin(), ::tolower);
                        if (isalpha(buf[i])){
                            temp=temp+buf[i];
                        }
                }
                v.push_back(temp);
            }
        }
        return v;

}








