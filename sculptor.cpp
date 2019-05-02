#include "sculptor.h"
#include <iostream>
#include <fstream>
using namespace std;

Sculptor::Sculptor(int _nx, int _ny, int _nz){
    nx = _nx;
    ny = _ny;
    nz = _nz;

    if(nx < 0 || ny < 0 || nz < 0){
        nx = 0;
        ny = 0;
        nz = 0;
    }
    //aloca no voxel v
    v = new Voxel**[nx];
    if(v == nullptr){
        cout<<endl<<"ERRO #01: Ocorreu um problema durante a alocação de linhas na matrix de voxel"<<endl;
        exit(0);
    }
    v[0] = new Voxel*[nx*ny];
    if(v[0] == nullptr){
        cout<<endl<<"ERRO #02: Ocorreu um problema durante a alocação de colunas na matrix de voxel"<<endl;
        exit(0);
    }


    v[0][0] = new Voxel[nx*ny*nz];
    if(v[0][0] == nullptr){
        cout<<endl<<"ERRO #03: Ocorreu um problema durante a alocação dos planos da matrix de voxel"<<endl;
        exit(0);
    }

    for(int i = 1; i<nx; i++){
        v[i] = v[i-1] + ny;
    }


    for(int i = 1; i<nx*ny; i++){
        v[0][i] = v[0][i-1] + nz;
    }

    /*
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                v[i][j][k].isOn = false;
                v[i][j][k].r = 255;
                v[i][j][k].g = 255;
                v[i][j][k].b = 255;
            }
        }
    }*/
}

Sculptor::~Sculptor(){
    if(nx == 0 || ny == 0 || nz == 0){
            return;
        }
        delete [] v[0][0];
        delete [] v[0];
        delete [] v;
}

void Sculptor::setColor(float r, float g, float b, float alpha){
    if(r >1){
        red = 1;
    }else if(r <0){
        red = 0;
    }else{
        red = r;
    }
    if(g >1){
        green = 1;
    }else if(g <0){
        green = 0;
    }else{
        green = g;
    }
    if(b >1){
        blue = 1;
    }else if(b <0){
        blue = 0;
    }else{
        blue = b;
    }
    if(alpha >1){
        a = 1;
    }else if(alpha <0){
        a = 0;
    }else{
        a = alpha;
    }
}

void Sculptor::putVoxel(int x, int y, int z){
    v[x][y][z].isOn = true;
    v[x][y][z].r = red;
    v[x][y][z].g = green;
    v[x][y][z].b = blue;
    v[x][y][z].a = a;
}

void Sculptor::cutVoxel(int x, int y, int z){
    v[x][y][z].isOn = false;
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(i>=x0 && i<=x1 && j>=y0 && j<=y1 && k>=z0 && k<=z1){
                    v[i][j][k].isOn = true;
                    v[i][j][k].r = red;
                    v[i][j][k].g = green;
                    v[i][j][k].b = blue;
                    v[i][j][k].a = a;
                }
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(i>=x0 && i<=x1 && j>=y0 && j<=y1 && k>=z0 && k<=z1){
                    v[i][j][k].isOn = false;
                    v[i][j][k].r = red;
                    v[i][j][k].g = green;
                    v[i][j][k].b = blue;
                    v[i][j][k].a = a;
                }
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    for(int i=0; i< xcenter; i++){
            for(int j=0; j< ycenter; j++){
                for(int k=0; k< zcenter; k++){
                    if ((pow((i-xcenter),2)) + (pow((j-ycenter),2)) + (pow((k-zcenter),2)) <= (pow(radius,2))){
                        v[i][j][k].isOn = true;
                        v[i][j][k].r = red;
                        v[i][j][k].g = green;
                        v[i][j][k].b = blue;
                        v[i][j][k].a = a;
                    }
                }
            }
        }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    for(int i=0; i< xcenter; i++){
        for(int j=0; j< ycenter; j++){
            for(int k=0; k< zcenter; k++){
                if ((pow((i-xcenter),2)) + (pow((j-ycenter),2)) + (pow((k-zcenter),2)) <= (pow(radius,2))){
                    v[i][j][k].isOn = false;
                    v[i][j][k].r = red;
                    v[i][j][k].g = green;
                    v[i][j][k].b = blue;
                    v[i][j][k].a = a;
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    for(int i=0; i< rx; i++){
        for(int j=0; j< ry; j++){
            for(int k=0; k< rz; k++){
                if ((pow((i-xcenter),2)/(float)(pow(xcenter,2))) + ((pow((j-ycenter),2))/(float)(pow(ycenter,2))) + ((pow((k-zcenter),2))/(float)(pow(zcenter,2))) <=1.0){
                    v[i][j][k].isOn = true;
                    v[i][j][k].r = red;
                    v[i][j][k].g = green;
                    v[i][j][k].b = blue;
                    v[i][j][k].a = a;
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    for(int i=0; i< rx; i++){
        for(int j=0; j< ry; j++){
            for(int k=0; k< rz; k++){
                if ((pow((i-xcenter),2)/(float)(pow(xcenter,2))) + ((pow((j-ycenter),2))/(float)(pow(ycenter,2))) + ((pow((k-zcenter),2))/(float)(pow(zcenter,2))) <=1.0){
                    v[i][j][k].isOn = false;
                    v[i][j][k].r = red;
                    v[i][j][k].g = green;
                    v[i][j][k].b = blue;
                    v[i][j][k].a = a;
                }
            }
        }
    }
}

void Sculptor::writeOFF(string filename){

    ofstream file;

    file.open("./"+filename+".off");

    if(file.is_open()==false){
        cout << "ERRO #04: O arquivo não pôde ser aberto.";
        exit(1);
    }

    file << "OFF" << endl;

    int n_voxels = 0;
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(v[i][j][k].isOn){
                    n_voxels = n_voxels+1;
                }
            }
        }
    }

    file << 8*n_voxels << " " << 6*n_voxels << " 0" << endl;

    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(v[i][j][k].isOn){
                    file << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                    file << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                    file << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                    file << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                    file << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
                    file << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
                    file << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
                    file << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
                }
            }
        }
    }

    for(int i = 0; i < nx; i++){
        for(int j = 0; j < ny; j++){
            for(int k = 0; k < nz; k++){
                if (v[i][j][k].isOn){
                    file << 4 << " " << 0 + 8*i << " " << 3 + 8*i << " " << 2 + 8*i << " " << 1 + 8*i << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << " " << endl;
                    file << 4 << " " << 4 + 8*i << " " << 5 + 8*i << " " << 6 + 8*i << " " << 7 + 8*i << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << " " << endl;
                    file << 4 << " " << 0 + 8*i << " " << 1 + 8*i << " " << 5 + 8*i << " " << 4 + 8*i << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << " " << endl;
                    file << 4 << " " << 0 + 8*i << " " << 4 + 8*i << " " << 7 + 8*i << " " << 3 + 8*i << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << " " << endl;
                    file << 4 << " " << 3 + 8*i << " " << 7 + 8*i << " " << 6 + 8*i << " " << 2 + 8*i << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << " " << endl;
                    file << 4 << " " << 1 + 8*i << " " << 2 + 8*i << " " << 6 + 8*i << " " << 5 + 8*i << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << " " << endl;
                }
            }
        }
    }

    file.close();

}

void Sculptor::writeVECT(string filename){

    ofstream file;

    file.open("./"+filename+".vect");

    if(file.is_open()==false){
        cout << "ERRO #04: O arquivo não pôde ser aberto.";
        exit(1);
    }

    file << "VECT" << endl;

    int n_voxels = 0;
    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(v[i][j][k].isOn){
                    n_voxels = n_voxels + 1;
                }
            }
        }
    }
    file << n_voxels << " " << n_voxels << " " << n_voxels << endl;

    for(int i = 1; i<n_voxels; i++){
        file << "1 ";
    }
    file << "1" << endl;

    for(int i = 1; i<n_voxels; i++){
        file << "1 ";
    }
    file << "1" << endl;

    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(v[i][j][k].isOn){
                    file << i << " " << j << " " << k << endl;
                }
            }
        }
    }

    for(int i = 0; i<nx; i++){
        for(int j = 0; j<ny; j++){
            for(int k = 0; k<nz; k++){
                if(v[i][j][k].isOn){
                    file << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
                }
            }
        }
    }
}
