//
//  ofmPolyFace.cpp
//
//  Created by Martin Froehlich on 06.07.12.
//  Copyright (c) 2012 maybites.ch. All rights reserved.
//

#include <iostream>
#include "ofmPolyFace.h"

ofmPolyFace::ofmPolyFace(){
}

int ofmPolyFace::getNumLines(){
    return lines.size();
}

ofmPolyFace::Line ofmPolyFace::getLine(int index){
    return lines[index];
}

void ofmPolyFace::addFace(int _p1, int _p2, int _p3){
    Face face;
    face.p1 = _p1;
    face.p2 = _p2;
    face.p3 = _p3;
    faces.push_back(face);
    
    addLine(_p1, _p2);
    addLine(_p2, _p3);
    addLine(_p3, _p1);
    
    addIndex(_p1);
    addIndex(_p2);
    addIndex(_p3);
}

void ofmPolyFace::addLine(int _p1, int _p2){
    int n = lines.size();
    
    //check if line alread exists
    for(int i = 0; i < n; i++) {
        if((lines[i].p1 == _p1 && lines[i].p2 == _p2) ||
           (lines[i].p1 == _p2 && lines[i].p2 == _p1)){
            //if so remove it from list
            lines.erase(lines.begin()+i);
            return;
        }
    }
    Line line;
    line.p1 = _p1;
    line.p2 = _p2;
    
    lines.push_back(line);
}


void  ofmPolyFace::addIndex(int _p1){
    int n = indices.size();
    
    for(int i = 0; i < n; i++) {
        if(indices[i] == _p1){
            return;
        }
    }
    
    indices.push_back(_p1);
}
