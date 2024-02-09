#include"mygraphlib.hpp"
#include"graphio.h"

using namespace std;


int main()
{
    int d;
    int l,u,an;
    int l2,u2,l3,u3;

    vector<pair<int,int>> edges;
    pair<int,int> bounds;
    coloredGraph G1,G2;

    //string s;

    char fname1[50]="FF1/FF", fname2[50]="HRG/hrg";
    char outname1[30]="FF1-bounds.csv",outname2[30]="HRG-bounds.csv";
    char socnets[8][30]=
    {"karateClub.txt","facebook_combined.txt","twitch_DE.txt","twitch_ENG.txt","twitch_ES.txt","twitch_FR.txt","deezer_europe_edges.txt","Gowalla_edges.txt"};

    cout<<"***Program to compute bounds on bonding number***"<<endl;

    edges=getEdges(socnets[1]);
    G1.addEdges(edges);

    if (G1.numConnected()>1)
    {
        cout<<"Graph is disconnected."<<endl;
        return 0;
    }


    //Find attachment number
    an=G1.findAN();
    cout<<"Attachment Number: "<<an<<endl;

    // Find upper and lower bounds.
    d=an;
    G1.setDemand(d);
    bounds=G1.findBounds(d);
    l=bounds.first;
    u=bounds.second;
    cout<<l<<","<<u<<endl;


    // Limit choices to low-degree neighbors.
    bounds=G1.findlowdegBounds(u,true);
    l2=bounds.first;
    u2=bounds.second;
    cout<<"Low degree: ";
    cout<<l2<<","<<u2<<endl;

    // Limit choices to high-degree neighbors.
    bounds=G1.findlowdegBounds(u,false);
    l3=bounds.first;
    u3=bounds.second;
    cout<<"High degree: ";
    cout<<l3<<","<<u3<<endl;




    return 0;
}
