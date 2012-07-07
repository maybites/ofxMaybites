//
//  ofmMesh.cpp
//  of_elSantoGrial
//
//  Created by Martin Froehlich on 06.07.12.
//  Copyright (c) 2012 maybites.ch. All rights reserved.
//

#include <iostream>
#include "ofmMesh.h"
#include "ofMesh.h"

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
		addVertex(ofVec3f(ofmRound(v[0],5), ofmRound(v[1],5), ofmRound(v[2],5)));
    }
    if (m->numnormals > 0)
    {
        for (int i = 1; i <= m->numnormals; i++)
        {
            GLfloat *n;
            n = &m->normals[i*3];
            addNormal(ofVec3f(n[0], n[1], n[2]));
        }
    }
    if (m->numtexcoords > 0)
    {
        for (int i = 1; i <= m->numtexcoords; i++)
        {
            GLfloat *t;
            t = &m->texcoords[i*3];
            addTexCoord(ofVec3f(t[0], t[1], t[2]));
        }
    }
	for (int i = 0; i < m->numtriangles; i++)
	{
        GLMtriangle &t = m->triangles[i];
        
        addTriangle(t.vindices[0]-1, t.vindices[1]-1, t.vindices[2]-1);
    }
    
	glmDelete(m);
    
}
