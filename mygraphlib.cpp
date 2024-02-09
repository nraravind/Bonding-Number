#include"mygraphlib.hpp"

coloredGraph::coloredGraph()
{
    n=0;
    m=0;
    numColors=0;
    //cout<<"Empty Colored graph created!"<<std::endl;
}

coloredGraph::coloredGraph(const coloredGraph& G)
{
    n=G.n;
    m=G.m;
    numColors=G.numColors;
    adjList=G.adjList;
    degree=G.degree;
    demand=G.demand;
    parent=G.parent;
    next=G.next;
    prev=G.prev;
    setSize=G.setSize;
    border=G.border;
}

void coloredGraph::printStats()
{
    int counter=0,mindeg=n+1,maxdeg=-1,iso=0;
    int u;
    int d;
    cout<<"#Vertices: "<<n<<"#Edges: "<<m<<"#Colors: "<<numColors<<endl;
    for (auto it=adjList.begin();it!=adjList.end();it++)
    {
        u=it->first;
        d=(it->second).size();
        auto degu=degree.find(it->first);
        if (degu==degree.end())
        {
            cout<<"Alarm 1: "<<u<<"#Size "<<d<<" #Degree "<<endl;
            break;
        }
        if (degu->second!=d)
        {
            cout<<"Alarm 2: "<<u<<"#Size "<<d<<" #Degree "<<degu->second<<endl;
            break;
        }
        counter=counter+d;
        mindeg=(mindeg<d)?mindeg:d;
        maxdeg=(maxdeg>d)?maxdeg:d;
        if (d==0)
            iso++;
        //if (d==1) cout<<it->first;

    }
    cout<<"Isolated: "<<iso;
    cout<<"Min degree: "<<mindeg<<"Max degree: "<<maxdeg<<endl;

}

void coloredGraph::printAdjList()
{
    unordered_map<int,unordered_set<int>>::iterator it;
    cout<<"Adjacency List"<<endl;

    int u;
    unordered_set<int>neighborList;
    unordered_set<int>::iterator v;
    for (it=adjList.begin();it!=adjList.end();it++)
    {
        u=it->first;
        cout<<u<<": ";
        neighborList=it->second;
        for (v=neighborList.begin();v!=neighborList.end();v++)
            cout<<*v<<" ";
        cout<<endl;
    }

}

void coloredGraph::printDegrees()
{
    unordered_map<int,int>::iterator it;
    int u,d;
    for (it=degree.begin();it!=degree.end();it++)
    {
        u=it->first;
        d=it->second;
        cout<<"Degree of "<<u<<" is: "<<d<<endl;
    }
}

void coloredGraph::printDemands()
{
    unordered_map<int,int>::iterator it;
    int d;
    int u,r;
    int sat=0,unsat=0,gunsat=0;;
    for (it=demand.begin();it!=demand.end();it++)
    {
        d=it->second;
        if (d==0)
            sat++;
        else
        {
            unsat++;
            u=it->first;
            r=findRoot(u);
            auto s=setSize.find(r);
            if (s->second>5000)
                gunsat++;
        }

    }
    cout<<"Saturated: "<<sat<<"  "<<"Unsaturated: "<<unsat<<"Giant unsat: "<<gunsat<<endl;
}


void coloredGraph::printSetSizes()
{
    map<int,int>::iterator it;
    int u,s;
    int unitcount=0;
    int counter=0;
    int maxsize=0;
    cout<<"#Vertices: "<<n<<endl;
    for (it=setSize.begin();it!=setSize.end();it++)
    {
        u=it->first;
        s=it->second;
        if (s>maxsize){
            maxsize=s;}

        if (s>1)
        {
            cout<<" "<<s;
            counter++;
            if (counter%20==0)
            cout<<endl;
        }
        else
        {
            unitcount++;
        }
        //cout<<"Size of "<<u<<" is: "<<s<<endl;


    }
    cout<<endl;
    cout<<"Max set size: "<<maxsize<<endl;
    cout<<"Unit count: "<<unitcount<<endl;
}

void coloredGraph::printSet(int u)
{
    int v;
    auto nextu=next.find(u);
    if (nextu==next.end())
    {
        cout<<"Bad vertex "<<u<<endl;
        return;
    }

    v=nextu->second;
    cout<<" "<<u;
    while (v!=u)
    {
        cout<<" "<<v;
        nextu=next.find(v);
        v=nextu->second;
    }
    cout<<"Border: "<<border.find(u)->second;
}

void coloredGraph::printSets()
{
    map<int,int>::iterator it;
    int u;
    for (it=setSize.begin();it!=setSize.end();it++)
    {
        u=it->first;
        printSet(u);
        cout<<endl;
    }
}


void coloredGraph::printBorders()
{
    unordered_map<int,int>::iterator it;
    for (it=border.begin();it!=border.end();it++)
    {
        cout<<"Root: "<<it->first<<" Border: "<<it->second<<endl;
    }
}

// Checks if v is in u's adjacency list
bool coloredGraph::isEdge(const int u,const int v)
{
    auto it=adjList.find(u);
    if (it==adjList.end())
        return false;
    auto neighbors=it->second;
    if (neighbors.find(v)!=neighbors.end())
        return true;

    return false;
}


void coloredGraph::addVertex(const int vertexID)
{
    unordered_set<int>neighbors;
    unordered_set<int>neighborList;

    adjList.insert(std::make_pair(vertexID,neighbors));
    degree.insert(std::make_pair(vertexID,0));
    demand.insert(std::make_pair(vertexID,0));
    parent.insert(std::make_pair(vertexID,vertexID));
    next.insert(std::make_pair(vertexID,vertexID));
    prev.insert(std::make_pair(vertexID,vertexID));
    setSize.insert(std::make_pair(vertexID,1));
    border.insert(std::make_pair(vertexID,vertexID));

    n=n+1;
    numColors++;
}

void coloredGraph::addEdge(const int u,const int v)
{
    auto eltu=adjList.find(u);
    auto eltv=adjList.find(v);
    if (eltu==adjList.end()){
        addVertex(u);
    }
    if (eltv==adjList.end()){
        addVertex(v);
    }
    eltu=adjList.find(u);
    eltv=adjList.find(v);

    if (eltu->second.find(v)==eltu->second.end())
    {
        eltu->second.insert(v);
        degree[u]++;
    }
    if (eltv->second.find(u)==eltv->second.end())
    {
        eltv->second.insert(u);
        degree[v]++;
        m++;
    }
}

void coloredGraph::addEdges(vector<std::pair<int,int>> edges)
{
    vector<std::pair<int,int>>::iterator it;
    int u,v;
    for (it=edges.begin();it!=edges.end();it++)
    {
        u=it->first;
        v=it->second;
        addEdge(u,v);
    }
}

void coloredGraph::removeEdge(const int u,const int v)
{
    if (isEdge(u,v)==false)
        return;
    auto itu=adjList.find(u);
    auto itv=adjList.find(v);

    auto neighborsu=itu->second;
    neighborsu.erase(v);

    auto neighborsv=itv->second;
    neighborsv.erase(u);

    auto degu=degree.find(u);
    auto degv=degree.find(v);
    if (degu->second>0)
        degu->second=degu->second-1;
    if (degv->second>0)
        degv->second=degv->second-1;

    m=m-1;
}


void coloredGraph::removeIsolatedVertex(const int u)
{
    auto degu=degree.find(u);
    if (degu->second>0)
        return;
    degree.erase(degu);
    auto demu=demand.find(u);
    demand.erase(demu);
    auto neighborList=adjList.find(u);
    adjList.erase(neighborList);
}




void coloredGraph::setDemand(int d)
{
    unordered_map<int,int>::iterator it;
    unordered_map<int,int>::iterator demIt;
    int u,deg;
    for (it=degree.begin();it!=degree.end();it++)
    {
        u=it->first;
        deg=it->second;
        auto eltu=demand.find(u);
        eltu->second=(deg<d)?deg:d;
    }
}

coloredGraph::findRoot(const int v)
{
    if (parent[v]==v)
        return v;
    parent[v]=findRoot(parent[v]);
    return parent[v];
}

coloredGraph::mergePair(const int u,const int v)
{
    int x,y,z,sizex,sizey;
    int valx,valy;
    x=findRoot(u);
    y=findRoot(v);
    if (x==y)
        return x;
    auto itx=setSize.find(x);
    auto ity=setSize.find(y);
    auto nextx=next.find(x);
    auto nexty=next.find(y);
    auto bx=border.find(x);
    auto by=border.find(y);

    sizex=itx->second;
    sizey=ity->second;
    if (sizex<sizey){
        parent[x]=y;
        z=y;
        ity->second=sizex+sizey;
        setSize.erase(itx);
        border.erase(bx);
    }
    else{
        parent[y]=x;
        z=x;
        itx->second=sizex+sizey;
        setSize.erase(ity);
        border.erase(by);
    }
    valx=nextx->second;
    valy=nexty->second;
    nextx->second=valy;
    nexty->second=valx;

    auto prevx=prev.find(valx);
    auto prevy=prev.find(valy);
    prevx->second=y;
    prevy->second=x;

    numColors=numColors-1;
    return z;
}



coloredGraph coloredGraph::mergeSaturated()
{
    coloredGraph G;
    G.n=n;
    G.m=m;

    G.adjList=adjList;
    G.degree=degree;
    G.demand=demand;

    G.parent=parent;
    G.next=next;
    G.prev=prev;
    G.setSize=setSize;
    G.border=border;

    G.numColors=numColors;
    unordered_map<int,unordered_set<int>>::iterator it;
    int u,v;
    unordered_set<int>neighborList;
    unordered_set<int>::iterator w;
    for (it=G.adjList.begin();it!=G.adjList.end();it++)
    {
        u=it->first;
        auto eltu1=G.demand.find(u);
        auto eltu2=G.degree.find(u);
        if (eltu2->second>eltu1->second)
            continue;
        //Merge u's class with each of its neighbors' classes
        neighborList=it->second;
        for (w=neighborList.begin();w!=neighborList.end();w++)
        {
            v=*w;
            G.mergePair(u,v);
            //cout<<"Merging "<<u<<" and "<<v<<endl;
        }
    }
    return G;
}

//Deletes edges within a set from adjacency lists.
//Updates deg, dem and sets a border vertex for each set.
void coloredGraph::cleanEdges()
{
    unordered_map<int,unordered_set<int>>::iterator it;
    int u,v,r,s;
    unordered_set<int>neighborList;
    unordered_set<int>::iterator w;
    for (it=adjList.begin();it!=adjList.end();it++)
    {
        u=it->first;
        r=findRoot(u);
        auto deg=degree.find(u);
        auto dem=demand.find(u);
        for (w=it->second.begin();w!=it->second.end();)
        {
            v=*w;
            s=findRoot(v);
            if (r==s)
            {
                w=it->second.erase(w);
                if (deg->second>0)
                    deg->second=deg->second-1;
                if (dem->second>0)
                    dem->second=dem->second-1;
                if (u<v)
                    m=m-1;
            }
            else
            {
                w++;
            }
        }
        if (deg->second>0)
        {
            auto b=border.find(r);
            b->second=u;
        }
    }
}

// Remove all vertices of degree zero
void coloredGraph::cleanVertices()
{
    int u,v,w;
    if (numColors==1)
        return;
    unordered_map<int,unordered_set<int>>::iterator it;
    it=adjList.begin();
    while(it!=adjList.end())
    {
        u=it->first;
        auto deg=degree.find(u);

        if (deg->second>0)
        {
            it++;
            continue;
        }

        auto dem=demand.find(u);
        auto prevu=prev.find(u);
        auto nextu=next.find(u);

        degree.erase(deg);
        demand.erase(dem);

        auto rootu=findRoot(u);
        auto sv=setSize.find(rootu);
        if (sv->second==1)
        {
            it++;
            continue;
        }
        sv->second=sv->second-1;

        if (rootu==u)
        {
            // Change parent of each node in set to the border vertex
            auto b=border.find(u);
            w=b->second;
            v=nextu->second;
            while (v!=u)
            {
                auto pv=parent.find(v);
                pv->second=w;
                auto nextv=next.find(v);
                v=nextv->second;
            }
            border.erase(b);
            border.insert(std::make_pair(w,w));

            int s=sv->second;
            setSize.erase(sv);
            setSize.insert(std::make_pair(w,s));
        }
        auto parentu=parent.find(u);
        parent.erase(parentu);
        //Delete links of u
        v=prevu->second;
        w=nextu->second;
        auto nextv=next.find(v);
        auto prevw=prev.find(w);
        nextv->second=w;
        prevw->second=v;
        prev.erase(prevu);
        next.erase(nextu);

        n=n-1;
        it=adjList.erase(it);
    }
}



int coloredGraph::colorDegree(int u, int v)
{
    int w,s,counter=0;
    int r=findRoot(v);
    auto st=setSize.find(r);
    auto degu=degree.find(u);
    if (st->second<degu->second)
    {
        w=v;
        do
        {
            if (isEdge(u,w))
            counter++;
            auto nextw=next.find(w);
            w=nextw->second;
        }while (w!=v);
    }
    else
    {
        auto neighbors=adjList.find(u);
        for (auto it=neighbors->second.begin();it!=neighbors->second.end();it++)
        {
            w=*it;
            s=findRoot(w);
            if (s==r)
                counter++;
        }
    }
    return counter;
}

bool coloredGraph::reduceOnce()
{
    int u,v,x,w,s;
    int diff;
    bool flag;
    unordered_map<int,int> colDegree;
    if (numColors<=1)
        return false;

    flag=false;
    for (auto it1=adjList.begin();it1!=adjList.end();it1++)
    {
        colDegree.clear();
        u=it1->first;
        x=findRoot(u);
        auto degu=degree.find(u);
        auto demu=demand.find(u);
        diff=degu->second-demu->second;
        // Find the color degrees of u
        for (auto it=it1->second.begin();it!=it1->second.end();it++)
        {
            w=*it;
            s=findRoot(w);
            auto col=colDegree.find(s);
            if (col==colDegree.end())
                colDegree.insert(std::make_pair(s,1));
            else
                col->second=col->second+1;
        }
        // Merge u,v if color degree of u in v is large.
        for (auto it2=setSize.begin();it2!=setSize.end();it2++)
        {
            v=it2->first;

            if (x==v)
                continue;

            auto col=colDegree.find(v);
            if (col==colDegree.end())
                continue;
            if (col->second>diff)
            {
                mergePair(u,v);
                flag=true;
                //return true;
            }
        }
    }
    return flag;
}


coloredGraph coloredGraph::chooseLowDegree(int d,bool flag)
{
    int u,v;
    int weight;
    coloredGraph G2=*this;

    // Phase 1: For each u, find list of v such that v's degree is larger than dth smallest in N(v).
    unordered_map<int,unordered_set<int>> badNeighbors;
    for (auto it=G2.adjList.begin();it!=G2.adjList.end();it++)
    {
        unordered_set<int>neighbors;
        vector<int>ndegrees;
        int u=it->first;
        badNeighbors.insert(std::make_pair(u,neighbors));
        auto eltu=badNeighbors.find(u);
        neighbors=it->second;
        if (neighbors.size()<=d)
            continue;

        for (auto it2=neighbors.begin();it2!=neighbors.end();it2++)
        {
            v=*it2;
            auto degv=G2.degree.find(v);
            ndegrees.push_back(degv->second);
        }

        if (flag==true)
        {
            std::sort(ndegrees.begin(),ndegrees.end());
        }
        else
        {
            std::sort(ndegrees.rbegin(),ndegrees.rend());
        }


        weight=ndegrees.at(d-1);

        if (flag==true)
        {
            for (auto it2=neighbors.begin();it2!=neighbors.end();it2++)
            {
            v=*it2;
            auto degv=G2.degree.find(v);
            if ((degv->second>weight) && (degv->second>d))
                eltu->second.insert(v);
            }
        }
        else
        {
            for (auto it2=neighbors.begin();it2!=neighbors.end();it2++)
            {
            v=*it2;
            auto degv=G2.degree.find(v);
            if ((degv->second<weight) && (degv->second>d))
                eltu->second.insert(v);
            }
        }

    }

    // Phase 2: Remove edges uv if v is bad for u and u is bad for u
    for (auto it=badNeighbors.begin();it!=badNeighbors.end();it++)
    {
        u=it->first;
        auto deg=G2.degree.find(u);
        auto eltu=G2.adjList.find(u);
        for (auto it2=it->second.begin();it2!=it->second.end();it2++)
        {
            v=*it2;
            auto eltv=badNeighbors.find(v);
            auto neighborsv=eltv->second;
            auto elv=eltu->second.find(v);
            if (neighborsv.find(u)!=neighborsv.end())
            {
                eltu->second.erase(elv);
                if (deg->second>0)
                    deg->second=deg->second-1;
                if (u<v)
                    G2.m=G2.m-1;
            }
        }
    }
    return G2;
}

coloredGraph coloredGraph::reduceGraph(int d)
{
    coloredGraph G2;
    bool flag;
    int counter;

    setDemand(d);
    G2=mergeSaturated();
    G2.cleanEdges();
    G2.cleanVertices();

    flag=true;

    counter=0;
    do
    {
        flag=G2.reduceOnce();
        G2.cleanEdges();
        G2.cleanVertices();

        //if (G2.numColors<=5)
        //    G2.printStats();

        counter++;
    }while(flag);

    return G2;
}


bool coloredGraph::isAttached(int d)
{
    coloredGraph G1=*this,G2;
    G1.setDemand(d);
    G2=G1.mergeSaturated();
    if (G2.numColors==1)
        return true;
    return false;
}

int coloredGraph::findAN()
{
    coloredGraph G1=*this;
    int l=1,r=1,m;
    bool flag=false;

    while (!flag)
    {
        flag=G1.isAttached(r);
        r=2*r;
    }
    r=r/2;
    l=r/4;

    while (r>l)
    {
        m=(l+r)/2;
        flag=G1.isAttached(m);
        if (flag==true)
            r=m;
        else
            l=m+1;
    }
    return l;
}

//Finds root of giant component
int coloredGraph::giant()
{
    int m=1,u=1;
    for (auto it=setSize.begin();it!=setSize.end();it++)
    {
        if (it->second>m)
        {
            m=it->second;
            u=it->first;
        }
    }
    return u;
}

//Assumes that the initial demand is d
//Finds bondedness of partition with giant on one-side
int coloredGraph::lowerBound(int d)
{
    // If there's only one set, no non-trivial lower bound is found.
    if (numColors==1)
        return 0;
    int r,s,t;
    int u,w;
    int lb=0;
    int m1=0,m2=0;
    int deg;

    r=giant();
    auto st=setSize.find(r);
    //cout<<"Root "<<r<<"Size "<<st->second<<endl;

    for (auto it=adjList.begin();it!=adjList.end();it++)
    {
        u=it->first;
        auto neighbors=it->second;
        s=findRoot(u);
        auto dem=demand.find(u);
        // Update largest demand in giant
        if (s==r)
        {
            if (dem->second>m1)
                m1=dem->second;
            continue;
        }
        deg=0;
        for (auto v=neighbors.begin();v!=neighbors.end();v++)
        {
            w=*v;
            t=findRoot(w);
            if ((t!=r)&&(t!=s))
                deg++;
        }
        //Update largest demand in non-giant, accounting for neighbors in other components
        if (dem->second-deg>m2)
            m2=dem->second-deg;
    }

    //cout<<"$ "<<m1<<"$ "<<m2<<endl;
    if (m1>m2)
        lb=d-m1+1;
    else
        lb=d-m2+1;

    return lb;
}

pair<int,int> coloredGraph::findBounds(int d)
{
    int nc,D,u,l;
    D=d;
    coloredGraph G2=reduceGraph(D);
    nc=G2.numColors;
    while (nc==1)
    {
        D--;
        G2=reduceGraph(D);
        nc=G2.numColors;
    }
    u=D+1;
    l=G2.lowerBound(D);
    return std::make_pair(l,u);
}


int coloredGraph::numConnected()
{
    coloredGraph G2=*this;
    int u,v;
    for (auto it=G2.adjList.begin();it!=G2.adjList.end();it++)
    {
        u=it->first;
        auto Nlist=it->second;
        for (auto x=Nlist.begin();x!=Nlist.end();x++)
        {
            v=*x;
            G2.mergePair(u,v);
        }
    }
    return G2.numColors;
}


pair<int,int> coloredGraph::findlowdegBounds(int D, bool flag)
{
    int l,r,u;
    pair<int,int> bounds;

    coloredGraph G2;

    l=1;
    r=D;

    while (r>l)
    {
        m=(l+r)/2;
        G2=chooseLowDegree(m,flag);
        if (G2.numConnected()>1)
        {
            l=m+1;
        }
        else
        {
            bounds=G2.findBounds(m);
            if (bounds.second<=m)
                r=m;
            else
                l=m+1;
        }

    }
    u=l;

    /*
    do
    {
        u=u-1;
        G2=chooseLowDegree(u,flag);
        bounds=G2.findBounds(u);
    }while (bounds.second<=u);

    u=u+1;*/
    G2=chooseLowDegree(u-1,flag);
    if (G2.numConnected()>1)
    {
        l=u;
    }
    else
    {
        bounds=G2.findBounds(u-1);
        l=bounds.first;
    }


    return std::make_pair(l,u);
}
