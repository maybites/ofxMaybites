//
//  ofmMesh.h
//
//  Created by Martin Froehlich on 06.07.12.
//  Copyright (c) 2012 maybites.ch. All rights reserved.
//

#include "ofMain.h"
#include "ofmMath.h"
#include "glm.h"
#include "ofmPolyFace.h"

#ifndef of_elSantoGrial_ofmMesh_h
#define of_elSantoGrial_ofmMesh_h

class ofmMesh: public ofMesh{
public:    
    ofmMesh();
    
    void loadobj(string modelpath);
    
    int         getNumPolyFaces();
    ofmPolyFace getPolyFace(int index);

private:
    int     getTriFaceVIndex(int faceNum, int vertex);
    ofVec3f getTriFaceNormal(int faceNum);  
    int     getNumTriFaces();
    void    updatePolyFaces();

    vector<ofmPolyFace> polyFaces;
};
#endif
