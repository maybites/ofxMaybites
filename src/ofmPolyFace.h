//
//  ofmPolyFace.h
//
//  Created by Martin Froehlich on 06.07.12.
//  Copyright (c) 2012 maybites.ch. All rights reserved.
//

#include "ofMain.h"

#ifndef of_elSantoGrial_ofmPolyFace_h
#define of_elSantoGrial_ofmPolyFace_h

class ofmPolyFace{
public:
	struct Face {
        int p1;
        int p2;
        int p3;
	};
	struct Line {
        int p1;
        int p2;
	};

    ofmPolyFace();
    
    void addFace(int _p1, int _p2, int _p3);
    
    int getNumLines();
    Line getLine(int index);

private:
    void addLine(int _p1, int _p2);
    void addIndex(int _p1);

    vector<int> indices;
    vector<Line> lines;
    vector<Face> faces;
};

#endif
