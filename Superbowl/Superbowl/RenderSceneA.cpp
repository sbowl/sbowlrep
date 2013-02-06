/* extra stuff from dooda */
#include "stdafx.h"

RenderSceneA::RenderSceneA()
{}

void RenderSceneA::Refinement()
{
#if 0
	int m_iNoVerticesOld;
	float afVertices[NO_VERTICES_MAX*3];
	int auiIndices[NO_VERTICES_MAX];
	m_iNoVerticesOld = m_iNoVertices;
	//alte arrays kopieren
	//
#endif
}

void RenderSceneA::TextureTest()
{
	//TEXTURTEST
    GLuint textureNumber; // Eine Textur in Karte erzeugen
    glGenTextures(1, &textureNumber);
    glBindTexture(GL_TEXTURE_2D, textureNumber); // Mit unserer erzeugten Textur arbeiten
    // Lineare Interpolation der Texturpixel zum Vergrößern und
    // Verkleinern verwenden (andere Parameter auf Standard belasen)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    GLubyte buffer[TEXTURE_WIDTH*TEXTURE_HEIGHT]; // Puffer initialisieren
    for (unsigned int j = 0; j < TEXTURE_HEIGHT; j++)
    {
        for (unsigned int i = 0; i < TEXTURE_WIDTH; i++)
        {
            //buffer[j*TEXTURE_WIDTH+i] = (i*j)%256;
			buffer[j*TEXTURE_WIDTH+i] = i;
        }
    }
    // Textur in die Grafikkarte hochladen
    glTexImage2D(GL_TEXTURE_2D,     // 2D Textur
                 0,                 // Detailsstufe (für Mipmaps)
                 1,                 // Farbkomponenten (1 für Grauwerte)
                 TEXTURE_WIDTH,     // Breite
                 TEXTURE_HEIGHT,    // Höhe
                 0,                 // Rand
                 GL_LUMINANCE,      // Pixel-Format (Grauwerte)
                 GL_UNSIGNED_BYTE,  // Datentyp der Komponenten (0 bis 255)
                 buffer);           // Pixel-Puffer

	glBegin(GL_QUADS);   
		glTexCoord2f(0.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  0.0f);                  
		glTexCoord2f(1.0f, 0.0f); glVertex3f(-1.0f, -1.0f,  1.0f);                 
		glTexCoord2f(1.0f, 1.0f); glVertex3f( 0.0f, -1.0f,  1.0f);                 
		glTexCoord2f(0.0f, 1.0f); glVertex3f( 0.0f, -1.0f,  0.0f);                  
    glEnd(); 
}
