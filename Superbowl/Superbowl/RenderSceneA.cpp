/* extra stuff from dooda */
#include "stdafx.h"

RenderSceneA::RenderSceneA()
{
	TextureMode = 1;
}

void RenderSceneA::Plane()
{
	glLoadIdentity();                                  
    glColor3f(0.5f,0.5f,1.0f);                         
    glBegin(GL_QUADS);                         
        glVertex3f(-1.0f, -1.0f, -1.0f);                  
        glVertex3f( 0.0f, -1.0f, -1.0f);                 
        glVertex3f( 0.0f, -1.0f, 0.0f);                 
        glVertex3f(-1.0f, -1.0f, 0.0f);                  
    glEnd();  
	glBegin(GL_QUADS);                         
        glVertex3f( 0.0f, -1.0f, -1.0f);                  
        glVertex3f( 1.0f, -1.0f, -1.0f);                 
        glVertex3f( 1.0f, -1.0f,  0.0f);                 
        glVertex3f( 0.0f, -1.0f,  0.0f);                  
    glEnd(); 
	glBegin(GL_QUADS);                         
        glVertex3f( 0.0f, -1.0f,  0.0f);                  
        glVertex3f( 1.0f, -1.0f,  0.0f);                 
        glVertex3f( 1.0f, -1.0f,  1.0f);                 
        glVertex3f( 0.0f, -1.0f,  1.0f);                  
    glEnd(); 

	//TEXTURTEST
	
	// Data read from the header of the BMP file
	unsigned char header[54]; // Each BMP file begins by a 54-bytes header
	unsigned int dataPos;     // Position in the file where the actual data begins
	unsigned int width, height;
	unsigned int imageSize;   // = width*height*3
	// Actual RGB data
	unsigned char * data;
	// Open the file
	FILE * file = fopen("bricks2.bmp","rb");
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
	width = 128; //TODO header might be corrupt.. adjusted for bricks.bmp
	height = 128;
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
    GLubyte buffer[TEXTURE_WIDTH*TEXTURE_HEIGHT*3]; // Puffer initialisieren
    for (unsigned int j = 0; j < TEXTURE_HEIGHT; j++)
    {
        for (unsigned int i = 0; i < TEXTURE_WIDTH; i++)
        {
			buffer[(j*TEXTURE_WIDTH+i)*3] = i;
			buffer[(j*TEXTURE_WIDTH+i)*3+1] = i;
			buffer[(j*TEXTURE_WIDTH+i)*3+2] = i;
        }
    }
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


	//glVertexPointer( 3, GL_FLOAT, 0, afVertices );

	//glDrawElements(GL_QUADS, 1, GL_UNSIGNED_INT);
	glBegin(GL_QUADS);   
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);                  
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);                 
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f, -1.0f,  1.0f);                 
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f, -1.0f,  0.0f);                  
    glEnd(); 
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