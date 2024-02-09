#include"graphio.h"

using namespace std;


vector<std::pair<int,int>> getEdges(char fname[50])
{
    vector<std::pair<int,int>> edgeList;
    std::ifstream file;
    int u,v;
    bool flag;
    std::string line;
    file.open(fname);
    if (!file.is_open()){
        std::cout<<"File Open Error";
        return edgeList;
    }
    while(getline(file,line))
    {
        std::stringstream   linestream(line);
        std::string         value;
        flag=true;
        while(getline(linestream,value,' '))
        {
            if (flag==true)
            {
                u=stoi(value);
                flag=false;
            }
            else{
                v=stoi(value);
            }
        }
        //std::cout<<u<<","<<v<<std::endl;
        edgeList.push_back(std::make_pair(u,v));
    }

    file.close();
    return edgeList;
}

void addToFile(char fname[50],int lb,int ub,int pb)
{
    std::ofstream file;
    file.open(fname,ios_base::app);
    file<<to_string(lb)<<","<<to_string(ub)<<","<<to_string(pb)<<endl;
    file.close();
}

void printEdges(vector<std::pair<int,int>> edges)
{
    vector<std::pair<int,int>>::iterator it;
    int u,v;
    for (it=edges.begin();it!=edges.end();it++)
    {
        u=it->first;
        v=it->second;
        std::cout<<u<<","<<v<<std::endl;
    }
}

