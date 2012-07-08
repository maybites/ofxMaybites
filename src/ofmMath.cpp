//
//  ofmMath.cpp
//
//  Created by Martin Froehlich on 06.07.12.
//  Copyright (c) 2012 maybites.ch. All rights reserved.
//

#include <iostream>
#include "ofmMath.h"

float ofmRound(float value, float dec){
    int sign = ofSign(value);
    float power = pow(10, dec);
    return (int)(value * power + 0.5f * sign)/power;
}

bool ofmIsSimilar(ofVec3f v1, ofVec3f v2, float dec){
    float rd = dec;
    v1.x = ofmRound(v1.x, rd);
    v1.y = ofmRound(v1.y, rd);
    v1.z = ofmRound(v1.z, rd);
    v2.x = ofmRound(v2.x, rd);
    v2.y = ofmRound(v2.y, rd);
    v2.z = ofmRound(v2.z, rd);
    return v1 == v2;
}
