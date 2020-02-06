#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

struct bricks {
    int type;
    int color;
    int angle;
    float x;
    float y;
    float z;
    int t;
};

struct colors {
    int type;
    vector<int> color;
};

//////////////////////////////////////////HELPFUL

void write(vector<bricks>& list){
    
    for(int i=0; i<list.size(); i++)
    {
        if(list[i].type == 3022)
        {
            cout << list[i].type << ": ";
            //        cout << list[i].color << " ";
            cout << list[i].angle << " ";
            //        cout << list[i].x << " ";
            //        cout << list[i].z;
            cout << endl;
        }
    }
}

void changeY(vector<bricks>& list,int brick){
    for(int i=0; i<list.size(); i++)
        if(list[i].type == brick)
            list[i].y=1;
}

void swapElements(vector<bricks>& list,int i, int j){
    int type=list[i].type;
    int color=list[i].color;
    int angle=list[i].angle;
    float x=list[i].x;
    float z=list[i].z;
    
    list[i].type=list[j].type;
    list[i].color=list[j].color;
    list[i].angle=list[j].angle;
    list[i].x=list[j].x;
    list[i].z=list[j].z;
    
    list[j].type=type;
    list[j].color=color;
    list[j].angle=angle;
    list[j].x=x;
    list[j].z=z;
}

bool distanceBetween(float i,float j,float range){
    
    if(abs(i-j) < range)
        return true;
    return false;
}

bool colorCheck(vector<colors>& allColors,int type,int color){
    
    int n=-1;
    for(int i=0; i < allColors.size(); i++)
        if(allColors[i].type == type)
            n=i;
    if(n==-1) return false;
    
    bool flag=false;
    for(int i=0; i < allColors[n].color.size(); i++)
        if(allColors[n].color[i] == color)
            flag=true;
            
    return flag;
}

//////////////////////////////////////////Load&Save

void loadFromFile(vector<bricks>& list){
    fstream input;
    input.open( "/Users/blazejkustra/Desktop/lego/input.lxfml", ios::in);
    
    if( !input.good() )
    {
        cout << "plik input.lxfml nie istnieje" << endl;
        exit(2);
    }
    
    int n=-1;
    while( !input.eof() )
    {
        list.push_back(bricks());
        n++;
        list[n].y=0;
        
        string line;
        getline( input, line );
        int k=0;
        int left=0;
        int right=0;
        int flag=true;
        int mode=0;
        
        for(int i=0 ; i<line.length() ; i++)
        {
            if(line[i]=='"')
            {
                if(flag)
                {
                    flag=false;
                    left=i+1;
                }
                else
                {
                    flag=true;
                    right=i;
                    k++;
                    switch( k )
                    {
                        case 2:
                            list[n].type=stoi( line.substr(left,right-left) );
                            break;
                            
                        case 3:
                            list[n].color=stoi( line.substr(left,right-left) );
                            break;
                    
                        case 4:
                            list[n].angle=stoi( line.substr(left,right-left) );
                            break;
                            
                        case 6:
                            mode=stoi( line.substr(left,right-left) );
                            break;
                            
                        case 8:
                            list[n].x=stof( line.substr(left,10) );
                            break;
                            
                        case 10:
                            list[n].z=stof( line.substr(left,10) );
                            break;
                            
                        default:
                            break;
                    }
                }
            }
        }
        if(mode==1 and list[n].angle==270) list[n].angle=90;
        //if(mode==1 and list[n].angle==180) list[n].angle=0;
    }
    
    for( int i = 0; i < list.size(); i++)
        if(list[i].type==0)
            list.erase(list.begin()+i);
    
    input.close();
}

void saveToFile(vector<bricks>& list){
    fstream outFile;
    outFile.open( "/Users/blazejkustra/Desktop/lego/output.lxfml", ios::out );
    
    outFile << "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\" ?>" << endl;
    outFile << "<LXFML versionMajor=\"4\" versionMinor=\"0\" name=\"Luther 6D v5\">" << endl;
    outFile << "<Meta>" << endl;
    outFile << "<Application name=\"LEGO Digital Designer\" versionMajor=\"4\" versionMinor=\"3\"/>" << endl;
    outFile << "<Brand name=\"LDDExtended\"/>" << endl;
    outFile << "<BrickSet version=\"2248.1\"/>" << endl;
    outFile << "</Meta>" << endl;
    outFile << "<Cameras>" << endl;
    outFile << "<Camera refID=\"0\" fieldOfView=\"80\" distance=\"451.90847778320312\" angle=\"103.36917877197266\" ax=\"-0.43417870998382568\" ay=\"-0.78949820995330811\" az=\"-0.43379896879196167\" tx=\"-239.97007751464844\" ty=\"366.20095825195312\" tz=\"7.8004298210144043\"/>" << endl;
    outFile << "</Cameras>" << endl;
    outFile << "<Scene cameraRefID=\"0\">" << endl;
    outFile << "<Model>" << endl;
    outFile << "<Group refID=\"0\" angle=\"0\" ax=\"0\" ay=\"1\" az=\"0\" tx=\"0\" ty=\"0\" tz=\"0\">" << endl;
    
    
    for(int i = 0; i < list.size(); i++)
    {
        //if(list[i].type == 3023 or list[i].type == 3022 or list[i].type==3021)
        outFile << "<Part refID=\"" << i << "\" designID=\"" << list[i].type << "\" materialID=\"" << list[i].color << "\" angle=\"" << list[i].angle << "\" ax=\"0\" ay=\"-1\" az=\"0\" tx=\"" << list[i].x << "\" ty=\"" << list[i].y << "\" tz=\"" << list[i].z << "\"/>" << endl;
    }
    
    outFile << "</Group>" << endl;
    outFile << "</Model>" << endl;
    outFile << "</Scene>" << endl;
    outFile << "<BuildingInstructions>" << endl;
    outFile << "</BuildingInstructions>" << endl;
    outFile << "</LXFML>" << endl;
    outFile.close();
}

void loadColors(vector<colors>& allColors){
    fstream input;
    input.open( "/Users/blazejkustra/Desktop/lego/colors.txt", ios::in );
    
    if( input.fail() )
    {
        cout << "plik colors.txt nie istnieje" << endl;
        exit(3);
    }
    
    
    for(int i=0; i<16; i++)
        allColors.push_back(colors());
    
    allColors[0].type=3623;
    allColors[1].type=63864;
    allColors[2].type=3068;
    allColors[3].type=3022;
    allColors[4].type=2431;
    allColors[5].type=3710;
    allColors[6].type=3020;
    allColors[7].type=87079;
    allColors[8].type=3021;
    allColors[9].type=3795;
    allColors[10].type=3023;
    allColors[11].type=3069;
    allColors[12].type=3070;
    allColors[13].type=3024;
    allColors[14].type=2420;
    allColors[15].type=14719;
    
    while( !input.eof() )
    {
        string line;
        getline( input, line );
        
        if(line.length()<4) continue;
        
        int left=0;
        int right=0;
        int type=0;
        int color;
        int k=0;
        
        for(int i=0 ; i<line.length() ; i++)
        {
            if(line[i]==',')
            {
                right=i;
                k++;
                switch( k )
                {
                    case 1:
                        type=stoi( line.substr(left,right-left) );
                        break;
                        
                    case 2:
                        color=stoi( line.substr(left,right-left) );
                        break;
                        
                    default:
                        break;
                }
                left=right+1;
            }
        }

        int n=-1;
        for(int i=0; i < allColors.size(); i++)
            if(allColors[i].type == type) n=i;
        
        if(n != -1) allColors[n].color.push_back(color);
    }
    
    bool flag=true;
    for(int i=0; i < allColors.size(); i++)
    {
        flag=true;
        if(allColors[i].color.empty() and allColors[i].type != 3070 and allColors[i].type != 3024 )
        {
            cout << "brak kolorow klocka " << allColors[i].type << endl;
            flag=false;
        }
    }
    
    input.close();
}

//////////////////////////////////////////normalize&changing

void normalize(vector<bricks>& list){
    for(int i=0; i < list.size(); i++)
    {
        switch( list[i].type )
        {
            case 3023:
                if(list[i].angle == 180)
                {
                    list[i].angle = 0;
                    list[i].x -=0.8;
                }
                if(list[i].angle == 270)
                {
                    list[i].angle = 90;
                    list[i].z +=0.8;
                }
                break;
                
            case 3069:
                if(list[i].angle == 180)
                {
                    list[i].angle = 0;
                    list[i].x -=0.8;
                }
                if(list[i].angle == 270)
                {
                    list[i].angle = 90;
                    list[i].z +=0.8;
                }
                break;
                
            case 3070:
                if(list[i].angle == 180)
                    list[i].angle = 0;
                
                if(list[i].angle == 270)
                    list[i].angle = 90;
                break;
            case 3024:
                if(list[i].angle == 180)
                    list[i].angle = 0;
                
                if(list[i].angle == 270)
                    list[i].angle = 90;
                break;
                
            case 3623:
                if(list[i].angle == 180)
                {
                    list[i].angle = 0;
                    list[i].x -=1.6;
                }
                if(list[i].angle == 270)
                {
                    list[i].angle = 90;
                    list[i].z +=1.6;
                }
                break;
            case 3022:
                if(list[i].angle == 180)
                {
                    list[i].angle = 0;
                    list[i].x -=0.8;
                    list[i].z +=0.8;
                }
                if(list[i].angle == 270)
                {
                    list[i].angle = 0;
                    list[i].z +=0.8;
                }
                if(list[i].angle == 90)
                {
                    list[i].angle = 0;
                    list[i].z +=0.8;
                }
                break;
                
            case 3068:
                if(list[i].angle == 180)
                {
                    list[i].angle = 0;
                    list[i].x -=0.8;
                    list[i].z +=0.8;
                }
                if(list[i].angle == 270)
                {
                    list[i].angle = 90;
                    list[i].x +=0.8;
                    list[i].z +=0.8;
                }
                if(list[i].angle == 90)
                {
                    list[i].angle = 0;
                    list[i].z +=0.8;
                }
                break;
                
            case 2431:
                if(list[i].angle == 180)
                {
                    list[i].angle = 0;
                    list[i].x -=2.4;
                }
                if(list[i].angle == 270)
                {
                    list[i].angle = 90;
                    list[i].z += 2.4;
                }
                break;
            case 3710:
                if(list[i].angle == 180)
                {
                    list[i].angle = 0;
                    list[i].x -=2.4;
                }
                if(list[i].angle == 270)
                {
                    list[i].angle = 90;
                    list[i].z += 2.4;
                }
                break;
                
            case 63864:
                if(list[i].angle == 180)
                {
                    list[i].angle = 0;
                    list[i].x -=1.6;
                }
                if(list[i].angle == 270)
                {
                    list[i].angle = 90;
                    list[i].z +=1.6;
                }
                break;
            case 3020:
                if(list[i].angle == 180)
                {
                    list[i].angle = 0;
                    list[i].x -=2.4;
                    list[i].z +=0.8;
                }
                if(list[i].angle == 270)
                {
                    list[i].angle = 90;
                    list[i].x +=0.8;
                    list[i].z +=2.4;
                }
                break;
                
            case 87079:
                if(list[i].angle == 180)
                {
                    list[i].angle = 0;
                    list[i].x -=2.4;
                    list[i].z +=0.8;
                }
                if(list[i].angle == 270)
                {
                    list[i].angle = 90;
                    list[i].x +=0.8;
                    list[i].z +=2.4;
                }
                break;
                
            case 3795:
                if(list[i].angle == 180)
                {
                    list[i].angle = 0;
                    list[i].x -=4;
                    list[i].z +=0.8;
                }
                if(list[i].angle == 270)
                {
                    list[i].angle = 90;
                    list[i].x +=0.8;
                    list[i].z +=4;
                }
                break;
            case 3021:
                if(list[i].angle == 180)
                {
                    list[i].angle = 0;
                    list[i].x -=1.6;
                    list[i].z +=0.8;
                }
                if(list[i].angle == 270)
                {
                    list[i].angle = 90;
                    list[i].x +=0.8;
                    list[i].z +=1.6;
                }
                break;
                
            default:
                break;
        }
    }
}

void change1x1Into1x2(vector<bricks>& list,vector<colors>& allColors){
    
    int type=3024;
    int typeChanged=3023;
    
    for(int i=0; i < list.size(); i++)
    {
        for(int j=i+1; j < list.size() and list[i].type==type; j++) // jesli i nie jest type to nawet nie am co odpalac 2 petli
        {
            if(list[j].type == type and list[i].color == list[j].color and colorCheck(allColors, typeChanged, list[i].color)) //ten sam typ oraz kolor
            {
                bool flag = true;
                if( distanceBetween(list[i].x, list[j].x, 0.2) and distanceBetween(list[i].z,list[j].z,0.9) ) // na tej samej wspolrzednej i blizej niz jedna kratka
                {
                    list[i].type=typeChanged;
                    list[i].angle=90;
                    if(list[j].z < list[i].z)
                        list[i].z=list[j].z;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                    
                }
                
                if( flag and distanceBetween(list[i].z, list[j].z, 0.2) and distanceBetween(list[i].x, list[j].x, 0.9) )
                {
                    list[i].type=typeChanged;
                    list[i].angle=0;
                    if(list[j].x < list[i].x)
                        list[i].x=list[j].x;
                    
                    list.erase(list.begin() + j);
                }
            }
        }
    }
}
void change1x1Into1x2_Tile(vector<bricks>& list,vector<colors>& allColors){
    
    int type=3070;
    int typeChanged=3069;
    
    for(int i=0; i < list.size(); i++)
    {
        for(int j=i+1; j < list.size() and list[i].type==type; j++) // jesli i nie jest type to nawet nie am co odpalac 2 petli
        {
            if(list[j].type == type and list[i].color == list[j].color and colorCheck(allColors, typeChanged, list[i].color)) //ten sam typ oraz kolor
            {
                bool flag = true;
                if( distanceBetween(list[i].x, list[j].x, 0.2) and distanceBetween(list[i].z,list[j].z,0.9) ) // na tej samej wspolrzednej i blizej niz jedna kratka
                {
                    list[i].type=typeChanged;
                    list[i].angle=90;
                    if(list[j].z < list[i].z)
                        list[i].z=list[j].z;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                }
                
                if( flag and distanceBetween(list[i].z, list[j].z, 0.2) and distanceBetween(list[i].x, list[j].x, 0.9) )
                {
                    list[i].type=typeChanged;
                    list[i].angle=0;
                    if(list[j].x < list[i].x)
                        list[i].x=list[j].x;
                    
                    list.erase(list.begin() + j);
                }
            }
        }
    }
}

void change1x2Into2x2(vector<bricks>& list,vector<colors>& allColors){
    int type=3023;
    int typeChanged=3022;
    
    for(int i=0; i < list.size(); i++)
    {
        for(int j=i+1; j < list.size() and list[i].type==type; j++) // jesli i nie jest type to nawet nie am co odpalac 2 petli
        {
            if(list[j].type == type and list[i].color == list[j].color and colorCheck(allColors, typeChanged, list[i].color)) //ten sam typ oraz kolor
            {
                bool flag = true;
                if( distanceBetween(list[i].x, list[j].x, 0.2) and distanceBetween(list[i].z,list[j].z,0.9) and list[i].angle == list[j].angle) // na tej samej wspolrzednej i blizej niz jedna kratka
                {
                    list[i].type=typeChanged;
                    list[i].angle=0;
                    if(list[j].z > list[i].z)
                        list[i].z=list[j].z;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                }
                
                if( flag and distanceBetween(list[i].z, list[j].z, 0.2) and distanceBetween(list[i].x, list[j].x, 0.9) and list[i].angle == list[j].angle)
                {
                    list[i].type=typeChanged;
                    list[i].angle=0;
                    if(list[j].x < list[i].x)
                        list[i].x=list[j].x;
                    
                    list[i].z+=0.8;
                    
                    list.erase(list.begin() + j);
                }
            }
        }
    }
}
void change1x2Into2x2_Tile(vector<bricks>& list,vector<colors>& allColors){
    int type=3069;
    int typeChanged=3068;
    
    for(int i=0; i < list.size(); i++)
    {
        for(int j=i+1; j < list.size() and list[i].type==type; j++) // jesli i nie jest type to nawet nie am co odpalac 2 petli
        {
            if(list[j].type == type and list[i].color == list[j].color and colorCheck(allColors, typeChanged, list[i].color)) //ten sam typ oraz kolor
            {
                bool flag = true;
                if( distanceBetween(list[i].x, list[j].x, 0.2) and distanceBetween(list[i].z,list[j].z,0.9) and list[i].angle == list[j].angle) // na tej samej wspolrzednej i blizej niz jedna kratka
                {
                    list[i].type=typeChanged;
                    list[i].angle=0;
                    if(list[j].z > list[i].z)
                        list[i].z=list[j].z;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                }
                
                if( flag and distanceBetween(list[i].z, list[j].z, 0.2) and distanceBetween(list[i].x, list[j].x, 0.9) and list[i].angle == list[j].angle)
                {
                    list[i].type=typeChanged;
                    list[i].angle=0;
                    if(list[j].x < list[i].x)
                        list[i].x=list[j].x;
                    
                    list[i].z+=0.8;
                    
                    list.erase(list.begin() + j);
                }
            }
        }
    }
}

void change2x2Into2x4(vector<bricks>& list,vector<colors>& allColors){
    int type=3022;
    int typeChanged=3020;
    
    for(int i=0; i < list.size(); i++)
    {
        for(int j=i+1; j < list.size() and list[i].type==type; j++) // jesli i nie jest type to nawet nie am co odpalac 2 petli
        {
            if(list[j].type == type and list[i].color == list[j].color and colorCheck(allColors, typeChanged, list[i].color)) //ten sam typ oraz kolor
            {
                bool flag = true;
                if( distanceBetween(list[i].x, list[j].x, 0.2) and distanceBetween(list[i].z,list[j].z,1.8)) // na tej samej wspolrzednej i blizej niz jedna kratka
                {
                    list[i].type=typeChanged;
                    list[i].angle=90;
                    if(list[j].z < list[i].z)
                        list[i].z=list[j].z;
                    list[i].z-=0.8;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                }
                
                if( flag and distanceBetween(list[i].z, list[j].z, 0.2) and distanceBetween(list[i].x, list[j].x, 1.8))
                {
                    list[i].type=typeChanged;
                    list[i].angle=0;
                    if(list[j].x < list[i].x)
                        list[i].x=list[j].x;
                    
                    list.erase(list.begin() + j);
                }
            }
        }
    }
}
void change2x2Into2x4_Tile(vector<bricks>& list,vector<colors>& allColors){
    int type=3068;
    int typeChanged=87079;
    
    for(int i=0; i < list.size(); i++)
    {
        for(int j=i+1; j < list.size() and list[i].type==type; j++) // jesli i nie jest type to nawet nie am co odpalac 2 petli
        {
            if(list[j].type == type and list[i].color == list[j].color and colorCheck(allColors, typeChanged, list[i].color)) //ten sam typ oraz kolor
            {
                bool flag = true;
                if( distanceBetween(list[i].x, list[j].x, 0.2) and distanceBetween(list[i].z,list[j].z,1.8)) // na tej samej wspolrzednej i blizej niz jedna kratka
                {
                    list[i].type=typeChanged;
                    list[i].angle=90;
                    if(list[j].z < list[i].z)
                        list[i].z=list[j].z;
                    list[i].z-=0.8;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                }
                
                if( flag and distanceBetween(list[i].z, list[j].z, 0.2) and distanceBetween(list[i].x, list[j].x, 1.8))
                {
                    list[i].type=typeChanged;
                    list[i].angle=0;
                    if(list[j].x < list[i].x)
                        list[i].x=list[j].x;
                    
                    list.erase(list.begin() + j);
                }
            }
        }
    }
}

void change1x1And1x2Into1x3(vector<bricks>& list,vector<colors>& allColors){
    int type1=3024;
    int type2=3023;
    int typeChanged=3623;
    
    for(int i=0; i < list.size(); i++)
    {
        for(int j=0; j < list.size() and list[i].type==type1; j++)
        {
            if(list[j].type == type2 and list[i].color == list[j].color and colorCheck(allColors, typeChanged, list[i].color))
            {
                bool flag = true;
                
                if( distanceBetween(list[i].x, list[j].x, 0.2) and distanceBetween(list[i].z,list[j].z,1.8) and list[j].angle == 90 and list[i].z > list[j].z)
                {
                    list[i].type=typeChanged;
                    list[i].angle=90;
                    list[i].z=list[j].z;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                }
                if( flag and distanceBetween(list[i].x, list[j].x, 0.2) and distanceBetween(list[i].z,list[j].z,0.9) and list[j].angle == 90)
                {
                    list[i].type=typeChanged;
                    list[i].angle=90;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                }
                
                if( flag and distanceBetween(list[i].z, list[j].z, 0.2) and distanceBetween(list[i].x, list[j].x, 1.8) and list[j].angle == 0 and list[i].x > list[j].x)
                {
                    list[i].type=typeChanged;
                    list[i].angle=0;
                    list[i].x=list[j].x;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                }
                
                if( flag and distanceBetween(list[i].z, list[j].z, 0.2) and distanceBetween(list[i].x, list[j].x, 0.9) and list[j].angle == 0)
                {
                    list[i].type=typeChanged;
                    list[i].angle=0;
                    
                    list.erase(list.begin() + j);
                }
            }
        }
    }
}
void change1x1And1x2Into1x3_Tile(vector<bricks>& list,vector<colors>& allColors){
    int type1=3070;
    int type2=3069;
    int typeChanged=63864;
    
    for(int i=0; i < list.size(); i++)
    {
        for(int j=0; j < list.size() and list[i].type==type1; j++)
        {
            if(list[j].type == type2 and list[i].color == list[j].color and colorCheck(allColors, typeChanged, list[i].color))
            {
                bool flag = true;
                
                if( distanceBetween(list[i].x, list[j].x, 0.2) and distanceBetween(list[i].z,list[j].z,1.8) and list[j].angle == 90 and list[i].z > list[j].z)
                {
                    list[i].type=typeChanged;
                    list[i].angle=90;
                    list[i].z=list[j].z;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                }
                if( flag and distanceBetween(list[i].x, list[j].x, 0.2) and distanceBetween(list[i].z,list[j].z,0.9) and list[j].angle == 90)
                {
                    list[i].type=typeChanged;
                    list[i].angle=90;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                }
                
                if( flag and distanceBetween(list[i].z, list[j].z, 0.2) and distanceBetween(list[i].x, list[j].x, 1.8) and list[j].angle == 0 and list[i].x > list[j].x)
                {
                    list[i].type=typeChanged;
                    list[i].angle=0;
                    list[i].x=list[j].x;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                }
                
                if( flag and distanceBetween(list[i].z, list[j].z, 0.2) and distanceBetween(list[i].x, list[j].x, 0.9) and list[j].angle == 0)
                {
                    list[i].type=typeChanged;
                    list[i].angle=0;
                    
                    list.erase(list.begin() + j);
                }
            }
        }
    }
}

void change1x1And1x2Into1x3Triangle(vector<bricks>& list,vector<colors>& allColors){
    int type1=3024;
    int type2=3023;
    int typeChanged=2420;
    
    for(int i=0; i < list.size(); i++)
    {
        for(int j=0; j < list.size() and list[i].type==type1 and i >= 0; j++)
        {
            if(list[j].type == type2 and list[i].color == list[j].color and colorCheck(allColors, typeChanged, list[i].color))
            {
                bool flag = true;
                
                if( flag and distanceBetween(list[i].z+0.8, list[j].z, 0.2) and distanceBetween(list[i].x, list[j].x, 0.2) and list[j].angle == 0)
                {
                    list[i].type=typeChanged;
                    list[i].angle=180;
                    list[i].z+=0.8;
                    list[i].x+=0.8;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                    i--;
                }
                
                if( flag and distanceBetween(list[i].z+0.8, list[j].z, 0.2) and distanceBetween(list[i].x-0.8, list[j].x, 0.2) and list[j].angle == 0)
                {
                    list[i].type=typeChanged;
                    list[i].angle=90;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                    i--;
                }
                
                if( flag and distanceBetween(list[i].z-0.8, list[j].z, 0.2) and distanceBetween(list[i].x, list[j].x, 0.2) and list[j].angle == 0)
                {
                    list[i].type=typeChanged;
                    list[i].angle=270;
                    
                    list.erase(list.begin() + j);
    
                    flag = false;
                    i--;
                }
                
                if( flag and distanceBetween(list[i].z-0.8, list[j].z, 0.2) and distanceBetween(list[i].x-0.8, list[j].x, 0.2) and list[j].angle == 0)
                {
                    list[i].type=typeChanged;
                    list[i].angle=0;
                    list[i].z=list[j].z;
                    list[i].x=list[j].x;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                    i--;
                }
                
                if( flag and distanceBetween(list[i].z, list[j].z, 0.2) and distanceBetween(list[i].x+0.8, list[j].x, 0.2) and list[j].angle == 90)
                {
                    list[i].type=typeChanged;
                    list[i].angle=0;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                    i--;
                }
                
                if( flag and distanceBetween(list[i].z-0.8, list[j].z, 0.2) and distanceBetween(list[i].x+0.8, list[j].x, 0.2) and list[j].angle == 90)
                {
                    list[i].type=typeChanged;
                    list[i].angle=90;
                    list[i].z=list[j].z;
                    list[i].x=list[j].x;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                    i--;
                }
                
                if( flag and distanceBetween(list[i].z, list[j].z, 0.2) and distanceBetween(list[i].x-0.8, list[j].x, 0.2) and list[j].angle == 90)
                {
                    list[i].type=typeChanged;
                    list[i].angle=270;
                    list[i].z+=0.8;
                    list[i].x-=0.8;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                    i--;
                }
                
                if( flag and distanceBetween(list[i].z-0.8, list[j].z, 0.2) and distanceBetween(list[i].x-0.8, list[j].x, 0.2) and list[j].angle == 90)
                {
                    list[i].type=typeChanged;
                    list[i].angle=180;
                    
                    list.erase(list.begin() + j);
                    i--;
                }
            }
        }
    }
}
void change1x1And1x2Into1x3Triangle_Tile(vector<bricks>& list,vector<colors>& allColors){
    int type1=3070;
    int type2=3069;
    int typeChanged=14719;
    
    for(int i=0; i < list.size(); i++)
    {
        for(int j=0; j < list.size() and list[i].type==type1 and i >= 0; j++)
        {
            if(list[j].type == type2 and list[i].color == list[j].color and colorCheck(allColors, typeChanged, list[i].color))
            {
                bool flag = true;
                
                if( flag and distanceBetween(list[i].z+0.8, list[j].z, 0.2) and distanceBetween(list[i].x, list[j].x, 0.2) and list[j].angle == 0)
                {
                    list[i].type=typeChanged;
                    list[i].angle=180;
                    list[i].z+=0.8;
                    list[i].x+=0.8;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                    i--;
                }
                
                if( flag and distanceBetween(list[i].z+0.8, list[j].z, 0.2) and distanceBetween(list[i].x-0.8, list[j].x, 0.2) and list[j].angle == 0)
                {
                    list[i].type=typeChanged;
                    list[i].angle=90;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                    i--;
                }
                
                if( flag and distanceBetween(list[i].z-0.8, list[j].z, 0.2) and distanceBetween(list[i].x, list[j].x, 0.2) and list[j].angle == 0)
                {
                    list[i].type=typeChanged;
                    list[i].angle=270;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                    i--;
                }
                
                if( flag and distanceBetween(list[i].z-0.8, list[j].z, 0.2) and distanceBetween(list[i].x-0.8, list[j].x, 0.2) and list[j].angle == 0)
                {
                    list[i].type=typeChanged;
                    list[i].angle=0;
                    list[i].z=list[j].z;
                    list[i].x=list[j].x;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                    i--;
                }
                
                if( flag and distanceBetween(list[i].z, list[j].z, 0.2) and distanceBetween(list[i].x+0.8, list[j].x, 0.2) and list[j].angle == 90)
                {
                    list[i].type=typeChanged;
                    list[i].angle=0;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                    i--;
                }
                
                if( flag and distanceBetween(list[i].z-0.8, list[j].z, 0.2) and distanceBetween(list[i].x+0.8, list[j].x, 0.2) and list[j].angle == 90)
                {
                    list[i].type=typeChanged;
                    list[i].angle=90;
                    list[i].z=list[j].z;
                    list[i].x=list[j].x;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                    i--;
                }
                
                if( flag and distanceBetween(list[i].z, list[j].z, 0.2) and distanceBetween(list[i].x-0.8, list[j].x, 0.2) and list[j].angle == 90)
                {
                    list[i].type=typeChanged;
                    list[i].angle=270;
                    list[i].z+=0.8;
                    list[i].x-=0.8;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                    i--;
                }
                
                if( flag and distanceBetween(list[i].z-0.8, list[j].z, 0.2) and distanceBetween(list[i].x-0.8, list[j].x, 0.2) and list[j].angle == 90)
                {
                    list[i].type=typeChanged;
                    list[i].angle=180;
                    
                    list.erase(list.begin() + j);
                    i--;
                }
            }
        }
    }
}

void change1x2Into1x4(vector<bricks>& list,vector<colors>& allColors){
    int type=3023;
    int typeChanged=3710;
    
    for(int i=0; i < list.size(); i++)
    {
        for(int j=i+1; j < list.size() and list[i].type==type; j++)
        {
            if(list[j].type == type and list[i].color == list[j].color and colorCheck(allColors, typeChanged, list[i].color))
            {
                bool flag = true;
                if( distanceBetween(list[i].x, list[j].x, 0.2) and distanceBetween(list[i].z,list[j].z,1.8) and list[i].angle == 90 and list[j].angle == 90)
                {
                    list[i].type=typeChanged;
                    list[i].angle=90;
                    if(list[j].z < list[i].z)
                        list[i].z=list[j].z;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                }
                
                if( flag and distanceBetween(list[i].z, list[j].z, 0.2) and distanceBetween(list[i].x, list[j].x, 1.8) and list[i].angle == 0 and list[j].angle == 0)
                {
                    list[i].type=typeChanged;
                    list[i].angle=0;
                    if(list[j].x < list[i].x)
                        list[i].x=list[j].x;
                    
                    list.erase(list.begin() + j);
                }
            }
        }
    }
    
    
}
void change1x2Into1x4_Tile(vector<bricks>& list,vector<colors>& allColors){
    int type=3069;
    int typeChanged=2431;
    
    for(int i=0; i < list.size(); i++)
    {
        for(int j=i+1; j < list.size() and list[i].type==type; j++)
        {
            if(list[j].type == type and list[i].color == list[j].color and colorCheck(allColors, typeChanged, list[i].color))
            {
                bool flag = true;
                if( distanceBetween(list[i].x, list[j].x, 0.2) and distanceBetween(list[i].z,list[j].z,1.8) and list[i].angle == 90 and list[j].angle == 90)
                {
                    list[i].type=typeChanged;
                    list[i].angle=90;
                    if(list[j].z < list[i].z)
                        list[i].z=list[j].z;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                }
                
                if( flag and distanceBetween(list[i].z, list[j].z, 0.2) and distanceBetween(list[i].x, list[j].x, 1.8) and list[i].angle == 0 and list[j].angle == 0)
                {
                    list[i].type=typeChanged;
                    list[i].angle=0;
                    if(list[j].x < list[i].x)
                        list[i].x=list[j].x;
                    
                    list.erase(list.begin() + j);
                }
            }
        }
    }
    
    
}

void change2x2And1x2Into2x3(vector<bricks>& list,vector<colors>& allColors){
    int type1=3022;
    int type2=3023;
    int typeChanged=3021;
    
    for(int i=0; i < list.size(); i++)
    {
        for(int j=0; j < list.size() and list[i].type==type1 and i >= 0; j++)
        {
            if(list[j].type == type2 and list[i].color == list[j].color and colorCheck(allColors, typeChanged, list[i].color))
            {
                bool flag = true;
                
                if( distanceBetween(list[i].x, list[j].x, 0.2) and distanceBetween(list[i].z-1.6,list[j].z,0.2) and list[j].angle == 0)
                {
                    list[i].type=typeChanged;
                    list[i].angle=90;
                    list[i].z=list[j].z;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                    i--;
                }
                
                if( flag and distanceBetween(list[i].x, list[j].x, 0.2) and distanceBetween(list[i].z+0.8,list[j].z,0.2) and list[j].angle == 0)
                {
                    list[i].type=typeChanged;
                    list[i].angle=90;
                    list[i].z-=0.8;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                    i--;
                }
                
                if( flag and distanceBetween(list[i].z-0.8, list[j].z, 0.2) and distanceBetween(list[i].x+1.6, list[j].x, 0.2) and list[j].angle == 90)
                {
                    list[i].type=typeChanged;
                    list[i].angle=0;
                    
                    list.erase(list.begin() + j);
                    
                    flag = false;
                    i--;
                }
                
                if( flag and distanceBetween(list[i].z-0.8, list[j].z, 0.2) and distanceBetween(list[i].x-0.8, list[j].x, 0.2) and list[j].angle == 90)
                {
                    list[i].type=typeChanged;
                    list[i].angle=0;
                    list[i].x-=0.8;
                    
                    list.erase(list.begin() + j);
                    
                    i--;
                }
            }
        }
    }
}

//////////////////////////////////////////

int main()
{
    vector<bricks> list;
    loadFromFile(list);
    
    vector<colors> allColors;
    loadColors(allColors);
    
    normalize(list);
    
    unsigned long int firstAmount=list.size();
    
    change1x1Into1x2(list,allColors);
    change1x1Into1x2_Tile(list,allColors);

    change1x2Into2x2(list,allColors);
    change1x2Into2x2_Tile(list,allColors);
    
    change2x2Into2x4(list,allColors);
    change2x2Into2x4_Tile(list,allColors);
    
    change1x1And1x2Into1x3(list,allColors);
    change1x1And1x2Into1x3_Tile(list,allColors);
    
    change1x1And1x2Into1x3Triangle(list,allColors);
    change1x1And1x2Into1x3Triangle_Tile(list,allColors);
    
    change1x2Into1x4(list,allColors);
    change1x2Into1x4_Tile(list,allColors);
    
    change2x2And1x2Into2x3(list,allColors);
    
    saveToFile(list);
    
    cout << firstAmount << " klocków przed uruchomieniem programu, zaoszczędzone: " <<  firstAmount-list.size() << endl;
    return 0;
}
