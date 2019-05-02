#include <iostream>
#include "sculptor.h"

using namespace std;

int main()
{
    //float r = 0, g = 0, b = 0, a = 0;
    //int nx, ny, nz;

    //cout<<"Digite, em sequencia, as dimensoes do seu canvas (x, y, z): "<<endl;
    //cin>>nx>>ny>>nz;

    Sculptor escultor(10, 5, 2);

    //cout<<"Digite, em sequencia, os valores rgb e o alpha: "<<endl;
    //cin>>r>>g>>b>>a;

    escultor.setColor(255, 255, 255, 1);
    //escultor.print();
    //cout<<"---------------------"<<endl;
    //escultor.putEllipsoid(4,4,4,2,4,2);
    //escultor.print();
    //cout<<"---------------------"<<endl;
    //escultor.cutEllipsoid(4,4,4,1,2,1);
    //escultor.print();

    escultor.putBox(0,10,0,10,0,5);
    escultor.putVoxel(0,0,0);
    //escultor.cutVoxel(1,1,1);
    escultor.setColor(0, 1, 0, 1);
    escultor.putVoxel(1,1,1);


//    Sculptor escultor2(2, 2, 2);
//    escultor2.setColor(1, 0, 0, 1);
//    escultor2.putVoxel(0,0,0);
//    escultor2.setColor(0, 1, 0, 1);
//    escultor2.putVoxel(0,1,0);
//    escultor2.setColor(0, 0, 1, 1);
//    escultor2.putVoxel(0,0,1);
//    escultor2.setColor(0.85f, 0, 0.85f, 0.85f);
//    escultor2.putVoxel(1,0,1);
//    escultor2.print();

    Sculptor escultor2(13,13,13);
    escultor2.setColor(0,1,0,0.7);
    escultor2.putSphere(6,6,6,4);
    escultor2.cutSphere(6,6,6,3);
    escultor2.cutBox(0,4,0,13,0,13);

    string vect_scr("VECT_file");
    string off_scr("OFF_file");

    escultor.writeVECT(vect_scr);
    escultor2.writeOFF(off_scr);

    return 0;
}
