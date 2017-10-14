//
//  export.c
//  libtess
//
//  Created by renan jegouzo on 31/03/2016.
//  Copyright © 2016 aestesis. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "export.h"
#include "gl.h"
#include "glu.h"

// sample:  http://www.flipcode.com/archives/Polygon_Tessellation_In_OpenGL.shtml

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void callbackError(int error) {
    printf("Tessellation Error: %d\n", error);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
void callbackCombine(GLdouble coords[3], TessVertex *data[4], GLfloat weight[4], void **dataOut) {
    TessVertex *o=(TessVertex*)malloc(sizeof(TessVertex));
    o->x = coords[0];
    o->y = coords[1];
    o->z = coords[2];
    if (data[3]) {
        o->u = data[0]->u * weight[0] + data[1]->u * weight[1] + data[2]->u * weight[2] + data[3]->u * weight[3];
        o->v = data[0]->v * weight[0] + data[1]->v * weight[1] + data[2]->v * weight[2] + data[3]->v * weight[3];
    } else if(data[2]) {
        o->u = data[0]->u * weight[0] + data[1]->u * weight[1] + data[2]->u * weight[2];
        o->v = data[0]->v * weight[0] + data[1]->v * weight[1] + data[2]->v * weight[2];
    } else {
        o->u = data[0]->u * weight[0] + data[1]->u * weight[1];
        o->v = data[0]->v * weight[0] + data[1]->v * weight[1];
    }
    *dataOut=o;
    //printf("%s\n","combine...");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
extern void * tessInit(TessBegin *begin, TessDraw *draw, TessEnd *end) {
    void *tess=gluNewTess();
    gluTessProperty(tess,GLU_TESS_WINDING_RULE,GLU_TESS_WINDING_ODD);
    gluTessCallback(tess, GLU_TESS_COMBINE, (GLvoid (*) ( )) &callbackCombine);
    gluTessCallback(tess, GLU_TESS_BEGIN, (GLvoid (*) ( )) begin);
    gluTessCallback(tess, GLU_TESS_VERTEX, (GLvoid (*) ( )) draw);
    gluTessCallback(tess, GLU_TESS_END, (GLvoid (*) ( )) end);
    gluTessCallback(tess, GLU_TESS_ERROR, (GLvoid (*) ( )) callbackError);
    return tess;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
extern void tessDelete(void *tess) {
    gluDeleteTess(tess);
}
extern void tessBeginPolygon(void *tess) {
    gluTessBeginPolygon(tess, NULL);
}
extern void tessEndPolygon(void *tess) {
    gluTessEndPolygon(tess);
}
extern void tessBeginContour(void *tess) {
    gluTessBeginContour(tess);
}
extern void tessEndContour(void *tess) {
    gluTessEndContour(tess);
}
extern void tessSendVertex(void *tess, TessVertex* vertex, int count) {
    int i=0;
    for(i=0; i<count; i++) {
        gluTessVertex(tess, (double *)vertex, vertex);
        vertex++;
    }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////
