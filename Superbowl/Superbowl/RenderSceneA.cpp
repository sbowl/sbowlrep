/* extra stuff from dooda */
#include "stdafx.h"

RenderSceneA::RenderSceneA()
{
	TextureMode = 1;
	intProjMode = 0;
}

void RenderSceneA::CreateScene()
{
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	unsigned char * data;
	// Open the file
	FILE * file = fopen("Mercator.bmp","rb");
	if (!file)
	{
		printf("Image could not be opened\n"); 
		exit(0);
	}
	if ( fread(header, 1, 54, file)!=54 ){ // If not 54 bytes read : problem
		printf("Not a correct BMP file\n");
		exit(0);
	}
	// Read ints from the byte array
	dataPos    = *(int*)&(header[0x0A]);
	imageSize  = *(int*)&(header[0x22]);
	imageSize = 0; //header broken? guess below with width and height
	width      = *(int*)&(header[0x12]);
	height     = *(int*)&(header[0x16]);
	width = 256; //TODO header might be corrupt.. adjusted for bricks.bmp
	height = 256;
	// Some BMP files are misformatted, guess missing information
	if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos==0)      dataPos=54; // The BMP header is done that way

	data = new unsigned char [imageSize]; // Create a buffer
	fread(data,1,imageSize,file); // Read the actual data from the file into the buffer
	fclose(file); //Everything is in memory now, the file can be closed



    GLuint textureNumber; // Eine Textur in Karte erzeugen
    glGenTextures(1, &textureNumber);
    glBindTexture(GL_TEXTURE_2D, textureNumber); // Mit unserer erzeugten Textur arbeiten
    // Lineare Interpolation der Texturpixel zum Vergrößern und
    // Verkleinern verwenden (andere Parameter auf Standard belasen)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Textur in die Grafikkarte hochladen
    glTexImage2D(GL_TEXTURE_2D,     // 2D Textur
                 0,                 // Detailsstufe (für Mipmaps)
                 GL_RGB,                 // Farbkomponenten (1 für Grauwerte)
                 width,     // Breite
                 height,    // Höhe
                 0,                 // Rand
                 GL_BGR,      // Pixel-Format (Grauwerte)
                 GL_UNSIGNED_BYTE,  // Datentyp der Komponenten (0 bis 255)
                 data);           // Pixel-Puffer


	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f( 1.0f, 1.0f, 1.0f );

    glVertexPointer( 3, GL_FLOAT, 0, afVertices ); // set pointer to vertex data
    glNormalPointer( GL_FLOAT, 0, afVertices ); // set pointer to normal data
    glEnableClientState( GL_VERTEX_ARRAY ); // enable vertex and normal pointer
    glEnableClientState( GL_NORMAL_ARRAY );
	float *auiTextureCoord = new float[2*m_iNoVertices];
	UpdateTextureCoord(auiTextureCoord);

	glTexCoordPointer(2, GL_FLOAT, 0, auiTextureCoord);
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glDrawElements( GL_TRIANGLES, m_iNoFaces*3, GL_UNSIGNED_INT, auiIndices ); // draw polygons


	//rotating Sphere
	memcpy(afVerticesSphere,afVerticesSphereStart, sizeof(float) * NO_VERTICES_SPHERE*3);
	memcpy(auiIndicesSphere,auiIndicesSphereStart,sizeof(int) * NO_FACES_SPHERE*3);
	
    //glDrawElements( GL_TRIANGLES, NO_FACES_SPHERE*3, GL_UNSIGNED_INT, auiIndicesSphere);     

	
}

void RenderSceneA::RenderScene()
{
	//big sphere
	glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glColor3f( 1.0f, 1.0f, 1.0f );
    glVertexPointer( 3, GL_FLOAT, 0, afVertices ); // set pointer to vertex data
    glNormalPointer( GL_FLOAT, 0, afVertices ); // set pointer to normal data
    glEnableClientState( GL_VERTEX_ARRAY ); // enable vertex and normal pointer
    glEnableClientState( GL_NORMAL_ARRAY );
	float *auiTextureCoord = new float[2*m_iNoVertices];
	UpdateTextureCoord(auiTextureCoord);
	glTexCoordPointer(2, GL_FLOAT, 0, auiTextureCoord);
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glDrawElements( GL_TRIANGLES, m_iNoFaces*3, GL_UNSIGNED_INT, auiIndices );
	
	//small sphere
	glPolygonMode(GL_FRONT,GL_FILL);
	glPolygonMode(GL_BACK,GL_FILL);
	glVertexPointer( 3, GL_FLOAT, 0, afVerticesSphere );
	glMatrixMode(GL_MODELVIEW);
	float RadiusSphere = 2.0f;
	float vx = RadiusSphere * sin(SphereMove);
	float vz = RadiusSphere * cos(SphereMove);
	glTranslatef(vx,0.0f,vz);
	float radiusSphere = 0.3f;
	float multMatrix[16] =
	{
		radiusSphere,0.0f,0.0f,0.0f,
		0.0f,radiusSphere,0.0f,0.0f,
		0.0f,0.0f,radiusSphere,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};
	glMultMatrixf(multMatrix);
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );
    glDrawElements( GL_TRIANGLES, NO_FACES_SPHERE*3, GL_UNSIGNED_INT, auiIndicesSphere);

	 //Simple Plane by 4 Quads
	glPolygonMode(GL_FRONT,GL_LINE); // wireframe for the front side of the polygone
	glPolygonMode(GL_BACK,GL_LINE); //and for the back side
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();                                  
    glColor3f(0.5f,0.5f,1.0f);  
	glDisableClientState( GL_TEXTURE_COORD_ARRAY );

	/* quads generieren [4x4] */
	int qx,qy;
	for (qx = -2; qx < 2; qx++) {
		for (qy = -2; qy < 2; qy++) {
			glBegin(GL_QUADS);                         
				glVertex3f(1.0f * qx, -1.0f, 1.0f * qy);
				glVertex3f(1.0f * (qx + 1), -1.0f, 1.0f * qy);
				glVertex3f(1.0f * (qx + 1), -1.0f, 1.0f * (qy + 1));
				glVertex3f(1.0f * qx, -1.0f, 1.0f * (qy + 1));
			glEnd();
		}
	}

	//go back to the previous Texture Mode stored in TextureMode
	if (TextureMode == 1)
	{
		glDisable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT,GL_FILL); // fill the front side of the polygone
		glPolygonMode(GL_BACK,GL_FILL); // and use wireframe for back side
	}
	else if (TextureMode == 2)
	{
		glEnable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT,GL_FILL); // fill the front side of the polygone
		glPolygonMode(GL_BACK,GL_FILL); // and use wireframe for back side
	}
	else 
	{
		glDisable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT,GL_LINE); // fill the front side of the polygone
		glPolygonMode(GL_BACK,GL_LINE); // and use wireframe for back side
	}
}


void RenderSceneA::SwitchTexture()
{
	if (TextureMode == 1)
	{
		glDisable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT,GL_FILL); // fill the front side of the polygone
		glPolygonMode(GL_BACK,GL_FILL); // and use wireframe for back side
		TextureMode = 2;
	}
	else if (TextureMode == 2)
	{
		glEnable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT,GL_FILL); // fill the front side of the polygone
		glPolygonMode(GL_BACK,GL_FILL); // and use wireframe for back side
		TextureMode = 3;
	}
	else 
	{
		glDisable(GL_TEXTURE_2D);
		glPolygonMode(GL_FRONT,GL_LINE); // fill the front side of the polygone
		glPolygonMode(GL_BACK,GL_LINE); // and use wireframe for back side
		TextureMode = 1;
	}
}

void RenderSceneA::UpdateTextureCoord(float *auiTextureCoord)
{	
	//FILE * file = fopen("Debug.log","w");//TODO ENTFERNEN DEBUG
	for(int i = 0; i < m_iNoVertices; i=i+1)
	{
		auiTextureCoord[2*i]=CalculateTextureCoordX(i); //x-Value
		auiTextureCoord[2*i+1]=CalculateTextureCoordY(i); //y-Value
		//fprintf(file,"Vertex Nr.: %d. Koordinaten: %f, %f, %f. TexX: %f, TexY: %f, \n", i, afVertices[3*i],afVertices[3*i+1],afVertices[3*i+2], auiTextureCoord[2*i], auiTextureCoord[2*i+1]);//TODO ENTFERNEN DEBUG
	}
	//fclose(file);//TODO ENTFERNEN DEBUG
}

float RenderSceneA::CalculateTextureCoordX(int VertexIndex)
{
	return CalculateLongitude(VertexIndex)/pi;
}

float RenderSceneA::CalculateTextureCoordY(int VertexIndex)
{
	float breitenGrad = CalculateLatitude(VertexIndex);
	if (intProjMode == 1) breitenGrad = log((1+ sin(breitenGrad))/(1-sin(breitenGrad)))/2;//vlt sogar ohne?
	breitenGrad = breitenGrad + 1.57079f;
	breitenGrad = breitenGrad / pi;
	return breitenGrad;
}

float RenderSceneA::CalculateLongitude(int VertexIndex)
{
	float vx = afVertices[3*VertexIndex + 0];
	float vy = afVertices[3*VertexIndex + 1];
	float vz = afVertices[3*VertexIndex + 2];
	if (vy==1.0f)//TODO wie geht or?
	{
		return pi;
	}
	else if (vy==-1.0f)
	{
		return pi;
	}
	float vxneu = vx/2;
	float vzneu = (sqrt(vx*vx + vz*vz)+vz)/2;
	float lengthA1 = sqrt(vx*vx + vz*vz);
	float lengthA3 = sqrt(vxneu*vxneu + vzneu*vzneu);
	float laengenGrad = 2*acos(lengthA3/lengthA1)/2;
	if(vx < 0)
	{
		laengenGrad = -laengenGrad;
	}
	return laengenGrad +pi;
}

float RenderSceneA::CalculateLatitude(int VertexIndex)
{
	float vy = afVertices[3*VertexIndex + 1];
	if (vy==1.0f) 
	{
		vy = 0.9999f;
	}
	else if (vy == -1.0f)
	{
		vy= -0.9999f;
	}
	return asin(vy);//+pi;
}

void RenderSceneA::SwitchProjection()
{
	if (intProjMode == 0) intProjMode = 1;
	else intProjMode = 0;
}