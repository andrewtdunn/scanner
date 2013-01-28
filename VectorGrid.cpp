#include<vector>
#include<cstdio>
using namespace std;

int main()
{
    vector<int> dyarray;

    int a=7;
    dyarray.push_back(a);
    dyarray.push_back(8);
    dyarray.push_back(a+2);

    for (a=0;a<dyarray.size();a++)
        printf("%d ",dyarray[a]);
    printf("\n");

    //delete second element
    a=1; //second element
    dyarray.erase(dyarray.begin()+a);
    printf("size %d\n",dyarray.size());
    for (a=0;a<dyarray.size();a++)
        printf("%d ",dyarray[a]);
    printf("\n");

    //insert at position 2
    dyarray.insert(dyarray.begin()+1,3);
    printf("size %d\n",dyarray.size());
    for (a=0;a<dyarray.size();a++)
        printf("%d ",dyarray[a]);
    printf("\n");

    //delete all
    dyarray.clear();
    printf("size %d\n",dyarray.size());

    return 1;
}
