#include <fstream>
#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>
#include <queue>
#include <deque>
#include <string>
#include <vector>
#include <locale>
using namespace std;
vector<string> read_file_human()
{
   vector<string> word;
   ifstream start("genoma/human.fasta");
   string line;
   locale loc;
   while(! start.eof())
   {
       start>>line;
       for(int g=0;g<line.length();++g)
       {
          line[g]=tolower(line[g],loc);
       }
       word.push_back(line);
   }
   return word;
}
vector<string> read_file_alpaca()
{
   vector<string> word;
   ifstream start("genoma/Alpaca.faa");
   string line;
   locale loc;
    while(! start.eof())
   {
       start>>line;
       for(int g=0;g<line.length();++g)
       {
          line[g]=tolower(line[g],loc);
       }
       word.push_back(line);
   }
   return word;
}
vector<string> read_file_anoleLizard()
{
   vector<string> word;
   ifstream start("genoma/AnoleLizard.faa");
   string line;
   locale loc;
    while(! start.eof())
   {
       start>>line;
       for(int g=0;g<line.length();++g)
       {
          line[g]=tolower(line[g],loc);
       }
       word.push_back(line);
   }
   return word;
}
vector<string> read_file_armadillo()
{
   vector<string> word;
   ifstream start("genoma/armadillo.faa");
   string line;
   locale loc;
    while(! start.eof())
   {
       start>>line;
       for(int g=0;g<line.length();++g)
       {
          line[g]=tolower(line[g],loc);
       }
       word.push_back(line);
   }
   return word;
}
vector<string> read_file_mouse()
{
   vector<string> word;
   ifstream start("genoma/Mouse.faa");
   string line;
   locale loc;
    while(! start.eof())
   {
       start>>line;
       for(int g=0;g<line.length();++g)
       {
          line[g]=tolower(line[g],loc);
       }
       word.push_back(line);
   }
   return word;
}

vector<string> read_file_zebra()
{
   vector<string> word;
   ifstream start("genoma/Zebrafish.faa");
   string line;
   locale loc;
    while(! start.eof())
   {
       start>>line;
       for(int g=0;g<line.length();++g)
       {
          line[g]=tolower(line[g],loc);
       }
       word.push_back(line);
   }
   return word;
}

int dimension(vector<string> & list_words)
{
   int num_state=0;
   for (int g=0;g<list_words.size();++g)
   {
      num_state+=list_words[g].size();
   }
   return num_state;
}
int serial_aho_corasik(const vector<string> &words, char min = 'a',char max = 'z',int tam)
{

        const int letter = 26;
        int out[nodos];
        int f[nodos];
        int g[nodos][letter];
        memset(out, 0, sizeof out);
        memset(f, -1, sizeof f);
        memset(g, -1, sizeof g);
        int states = 1;
        for (int i = 0; i < words.size(); ++i)
        {

            const string &keyword = words[i];
            int currentState = 0;
            for (int j = 0; j < keyword.size(); ++j)
            {
                int c = keyword[j] - min;
                if (g[currentState][c] == -1)
                {
                    g[currentState][c] = states++;

                }
                currentState = g[currentState][c];
            }
            out[currentState] |= (1 << i);
        }



        for (int c = 0; c < letter; ++c)
        {
            if (g[0][c] == -1)
            {
                g[0][c] = 0;
            }
        }

        queue<int> q;

        for (int c = 0; c <= max - min; ++c)
        {
            if (g[0][c] != -1 and g[0][c] != 0)
            {
                f[g[0][c]] = 0;
                q.push(g[0][c]);
            }
        }

        while (q.size())
        {
            int state = q.front();
            q.pop();
            for (int c = 0; c <= max - min; ++c)
            {
                if (g[state][c] != -1)
                {
                    int failure = f[state];
                    while (g[failure][c] == -1)
                    {
                        failure = f[failure];
                    }
                    failure = g[failure][c];
                    f[g[state][c]] = failure;
                    out[g[state][c]] |= out[failure]; // Merge out values
                    q.push(g[state][c]);
                }
            }

        }
    return states;

}

int findNextState(int currentState, char nextInput, char min = 'a')

{
    const int nodos =45;
    const int letter = 26;
    int out[nodos];
    int f[nodos];
    int g[nodos][letter];
    int answer = currentState;
    int c = nextInput - min;
    while (g[answer][c] == -1)
        answer = f[answer];
    return g[answer][c];

}
void original_aho(vector<string> &words)
{
    serial_aho_corasik(words, 'a', 'z');
    int currentState = 0;
    int thread;
    string text = "ahishers";
    omp_set_num_threads(nthreads);
    #pragma omp parallel private(thread)
    {
        thread = omp_get_thread_num();
        for (int i = 0; i < text.size(); ++i)
        {
        currentState = findNextState(currentState, text[i], 'a');
        if (out[currentState] == 0)
            continue;
        #pragma omp for
        for (int j = 0; j < keywords.size(); ++j)
        {
            if (out[currentState] & (1 << j))
            { // Matched keywords[j]
                cout << "Keyword " << keywords[j] << " appears from " << i
                        - keywords[j].size() + 1 << " to " << i << endl;
            }
        }
        }

    }
}
int openmp_aho_corasik(const vector<string> &words, char min = 'a',char max = 'z',int tam)
{
        const int nodos = tam;
        const int letter = 26;
        int out[nodos];
        int f[nodos];
        int g[nodos][letter];
        memset(out, 0, sizeof out);
        memset(f, -1, sizeof f);
        memset(g, -1, sizeof g);
        int states = 1;
        #pragma omp parallel private(thread)
        {
           #pragma omp for
           for (int i = 0; i < words.size(); ++i)
           {

            const string &keyword = words[i];
            int currentState = 0;
            for (int j = 0; j < keyword.size(); ++j)
            {
                int c = keyword[j] - min;
                if (g[currentState][c] == -1)
                {
                    g[currentState][c] = states++;

                }
                currentState = g[currentState][c];
            }
            out[currentState] |= (1 << i);
            }


        }

        for (int c = 0; c < letter; ++c)
        {
            if (g[0][c] == -1)
            {
                g[0][c] = 0;
            }
        }

        queue<int> q;

        for (int c = 0; c <= max - min; ++c)
        {
            if (g[0][c] != -1 and g[0][c] != 0)
            {
                f[g[0][c]] = 0;
                q.push(g[0][c]);
            }
        }

        while (q.size())
        {
            int state = q.front();
            q.pop();
            for (int c = 0; c <= max - min; ++c)
            {
                if (g[state][c] != -1)
                {
                    int failure = f[state];
                    while (g[failure][c] == -1)
                    {
                        failure = f[failure];
                    }
                    failure = g[failure][c];
                    f[g[state][c]] = failure;
                    out[g[state][c]] |= out[failure]; // Merge out values
                    q.push(g[state][c]);
                }
            }

        }
    return states;

}
void  modified_aho(vector<string> &words)
{
    serial_aho_corasik(words, 'a', 'z');
    int currentState = 0;
    int thread;
    string text = "ahishers";
    omp_set_num_threads(nthreads);
    #pragma omp parallel private(thread)
    {
        thread = omp_get_thread_num();
        #pragma omp for
        for (int i = 0; i < text.size(); ++i)
        {
            currentState = findNextState(currentState, text[i], 'a');
            if (out[currentState] == 0)
             continue;

             #pragma omp for
             for (int j = 0; j < keywords.size(); ++j)
             {
               if (out[currentState] & (1 << j))
               { // Matched keywords[j]
                  cout << "Keyword " << keywords[j] << " appears from " << i- keywords[j].size() + 1 << " to " << i << endl;
               }
            }
        }

    }

}

void  modified_aho_openmp(vector<string> &words)
{
    openmp_aho_corasik(words, 'a', 'z');
    int currentState = 0;
    int thread;
    string text = "ahishers";
    omp_set_num_threads(nthreads);
    #pragma omp parallel private(thread)
    {
        thread = omp_get_thread_num();
        #pragma omp for
        for (int i = 0; i < text.size(); ++i)
        {
            currentState = findNextState(currentState, text[i], 'a');
            if (out[currentState] == 0)
             continue;

             #pragma omp for
             for (int j = 0; j < keywords.size(); ++j)
             {
               if (out[currentState] & (1 << j))
               { // Matched keywords[j]
                  cout << "Keyword " << keywords[j] << " appears from " << i- keywords[j].size() + 1 << " to " << i << endl;
               }
            }
        }

    }

}




int main()
{

    //vector<string> keywords=read_file_human(); //36324438 //lineas 59846
    //vector<string> keywords=read_file_alpaca(); // 20293078  //33209
    //vector<string> keywords=read_file_anoleLizard(); //22664306 //34827
    //vector<string> keywords=read_file_armadillo(); // 20882544 //38202
    //vector<string> keywords=read_file_zebra(); //31797807 //46452
    vector<string> keywords=read_file_mouse(); //18204103 //45438
    int c=dimension(keywords);
    //cout<<c<<"lineas: "<< keywords.size()<<endl;
    /*string text = "ahishers";

    return 0;
}