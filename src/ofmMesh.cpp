//
//  ofmMesh.cpp
//
//  Created by Martin Froehlich on 06.07.12.
//  Copyright (c) 2012 maybites.ch. All rights reserved.
//

#include <iostream>
#include "ofmMesh.h"
#include "ofMesh.h"

#define FACE_POINT1 0
#define FACE_POINT2 1
#define FACE_POINT3 2

ofmMesh::ofmMesh() :ofMesh(){
}

void ofmMesh::loadobj(string modelpath){
  	modelpath = ofToString(ofFilePath::getAbsolutePath(modelpath));
	
	GLMmodel* m;
	
	m = glmReadOBJ((char*)modelpath.c_str());
	
	glmFacetNormals(m);
	glmVertexNormals(m, 90);
    
    clear();
    
    //cout << "got face with vertices: " << m-> << " - " << (int)face.y << " - " << (int)face.z << endl; 	
    
    for (int i = 1; i <= m->numvertices; i++)
	{
        GLfloat *v;
        v = &m->vertices[i*3];
		addVertex(ofVec3f(ofmRound(v[FACE_POINT1],5), ofmRound(v[FACE_POINT2],5), ofmRound(v[FACE_POINT3],5)));
    }
    if (m->numnormals > 0)
    {
        for (int i = 1; i <= m->numnormals; i++)
        {
            GLfloat *n;
            n = &m->normals[i*3];
            addNormal(ofVec3f(n[FACE_POINT1], n[FACE_POINT2], n[FACE_POINT3]));
        }
    }
    if (m->numtexcoords > 0)
    {
        for (int i = 1; i <= m->numtexcoords; i++)
        {
            GLfloat *t;
            t = &m->texcoords[i*3];
            addTexCoord(ofVec3f(t[FACE_POINT1], t[FACE_POINT2], t[FACE_POINT3]));
        }
    }
	for (int i = 0; i < m->numtriangles; i++)
	{
        GLMtriangle &t = m->triangles[i];
        
        addTriangle(t.vindices[FACE_POINT1]-1, t.vindices[FACE_POINT2]-1, t.vindices[FACE_POINT3]-1);
    }
    
	glmDelete(m);
    
    updatePolyFaces();
}

void ofmMesh::updatePolyFaces(){
    int n = getNumTriFaces();
    vector<int> faces;
    polyFaces.clear();
    faces.resize(getNumTriFaces());
    for (int i = 0; i < n; i++) {
        faces[i] = i;
    }
    // sorting the faces accroding to their normals
    for (int i = 0; i < n-1;){ // i++){
        ofVec3f norm = getTriFaceNormal(faces[i]);
        ofmPolyFace newFace;
        newFace.addFace(getTriFaceVIndex(faces[i], FACE_POINT1), 
                        getTriFaceVIndex(faces[i], FACE_POINT2), 
                        getTriFaceVIndex(faces[i], FACE_POINT3));
        //cout << "face normal : " << i << " " << norm.x << " - " << norm.y << " - " << norm.z << endl;         
        //int nextindex = i+1;
        for (int j = i+1; j < n; j++){
            ofVec3f comp = getTriFaceNormal(faces[j]);
            //check if both faces are looking in the same direction
            if(ofmIsSimilar(comp,norm,3)){
                /*
                 ofVec3f face = getFace(faces[i]);
                 cout << "face : " << i << " " << (int)face.x << " - " << (int)face.y << " - " << (int)face.z << endl; 	
                 face = getFace(faces[j]);
                 cout << " -> match : " << j << " " << (int)face.x << " - " << (int)face.y << " - " << (int)face.z << endl; 	
                 */
                int equalface = faces[j];
                faces[j] = faces[++i];
                faces[i] = equalface;
                newFace.addFace(getTriFaceVIndex(faces[i], FACE_POINT1), 
                                getTriFaceVIndex(faces[i], FACE_POINT2), 
                                getTriFaceVIndex(faces[i], FACE_POINT3));
                //                faces[j] = faces[nextindex];
                //                faces[nextindex] = equalface;
                //nextindex++;
            }
        }
        polyFaces.push_back(newFace);
        i++;
    }
    
    /* for debugging only:
    for (int i = 0; i < n; i++) {
        cout << "got face with vertice: "   << getTriFaceVIndex(faces[i], 0) << " - " 
        << getTriFaceVIndex(faces[i], 1) << " - " 
        << getTriFaceVIndex(faces[i], 2) << endl; 	
    }
    
    n = polyFaces.size();
    for (int i = 0; i < n; i++) {
        ofmPolyFace face = polyFaces[i];
        cout << "got polyface with : " << face.getNumLines() << " lines" << endl; 	
        for(int j = 0; j < face.getNumLines(); j++){
            cout << "     line: " << j << " | " << face.getLine(j).p1 << " - " << face.getLine(j).p2 << endl; 	
        }
    }
    */
}

int ofmMesh::getNumPolyFaces(){
    return polyFaces.size();
}

ofmPolyFace ofmMesh::getPolyFace(int index){
    return polyFaces[index];
}

int ofmMesh::getNumTriFaces(){
    return getNumIndices()/3;
}

int ofmMesh::getTriFaceVIndex(int faceNum, int vertex){  
    return getIndex(faceNum*3+vertex);
}

ofVec3f ofmMesh::getTriFaceNormal(int faceNum){  
    ofVec3f vertice1 = getVertex(getTriFaceVIndex(faceNum, FACE_POINT1));
    ofVec3f vertice2 = getVertex(getTriFaceVIndex(faceNum, FACE_POINT2));
    ofVec3f vertice3 = getVertex(getTriFaceVIndex(faceNum, FACE_POINT3));
    ofVec3f edge1 = vertice1 - vertice2;
    ofVec3f edge2 = vertice2 - vertice3;
    ofVec3f norm = edge1.cross(edge2);
    return norm.getNormalized();
}
