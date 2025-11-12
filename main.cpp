#include "main.h"
#include "graph.h"
#include "stack.h"
#include <iostream>
#include <fstream>
#include <cstring>

// main driver, reads args + commands
int main(int argc, char* argv[]) {

    if (argc != 4 ||
        (std::string(argv[2]) != "DirectedGraph" && std::string(argv[2]) != "UndirectedGraph") ||
        (std::string(argv[3]) != "0" && std::string(argv[3]) != "1")) {
        std::cerr << "Usage: ./PJ3 <InputFile> <GraphType> <Flag>" << std::endl;
        return 0;
    }

    bool directed = std::string(argv[2]) == "DirectedGraph";
    bool toFront = std::string(argv[3]) == "0";

    std::ifstream fin(argv[1]);
    int n,m;
    fin>>n>>m;
    Graph G(n);

    for(int i=0;i<m;i++){
        int idx,u,v; double w;
        fin>>idx>>u>>v>>w;
        G.AddEdge(u,v,idx,w,toFront);
        if(!directed) G.AddEdge(v,u,idx,w,toFront); // reverse edge for undirected
    }
    fin.close();

    pSTACK stack = CreateStack(n);
    std::string cmd;

    // read commands until Stop
    while(std::cin>>cmd){
        if(cmd=="Stop") break;
        else if(cmd=="PrintADJ") G.PrintADJ();
        else if(cmd=="SinglePair") {
            int s,t; std::cin>>s>>t;
            G.DijkstraSinglePair(s,t);
        }
        else if(cmd=="SingleSource") {
            int s; std::cin>>s;
            G.DijkstraSingleSource(s);
        }
        else if(cmd=="PrintLength") {
            int s,t; std::cin>>s>>t;
            G.PrintLength(s,t);
        }
        else if(cmd=="PrintPath") {
            int s,t; std::cin>>s>>t;
            G.PrintPath(s,t,stack);
        }
        else {
            // invalid command, print error
            std::cerr << "Invalid instruction." << std::endl;
            std::string line;
            std::getline(std::cin, line); // clear rest of line
        }
    }

    FreeStack(stack);
    return 0;
}
