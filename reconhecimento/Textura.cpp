#include "Textura.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int Textura::qtdTexturasEmUso = 0;

Textura::Textura(string caminhoArquivo)
{
	int width, height;
	unsigned char* image = stbi_load(caminhoArquivo.c_str(), &width, &height, 0, 0);
	glGenTextures(1, &this->textura);
	glBindTexture(GL_TEXTURE_2D, this->textura);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	glGenerateMipmap(GL_TEXTURE_2D);
	stbi_image_free(image);
	this->indiceTextura = Textura::qtdTexturasEmUso;
	Textura::qtdTexturasEmUso++;
}

void Textura::usar()
{
	switch (this->indiceTextura)
	{
	case 0: glActiveTexture(GL_TEXTURE0);
	case 1: glActiveTexture(GL_TEXTURE1);
	case 2: glActiveTexture(GL_TEXTURE2);
	case 3: glActiveTexture(GL_TEXTURE3);
	case 4: glActiveTexture(GL_TEXTURE4);
	case 5: glActiveTexture(GL_TEXTURE5);
	case 6: glActiveTexture(GL_TEXTURE6);
	case 7: glActiveTexture(GL_TEXTURE7);
	case 8: glActiveTexture(GL_TEXTURE8);
	case 9: glActiveTexture(GL_TEXTURE9);
	case 10: glActiveTexture(GL_TEXTURE10);
	case 11: glActiveTexture(GL_TEXTURE11);
	case 12: glActiveTexture(GL_TEXTURE12);
	case 13: glActiveTexture(GL_TEXTURE13);
	case 14: glActiveTexture(GL_TEXTURE14);
	case 15: glActiveTexture(GL_TEXTURE15);
	default:
		break;
	}
	glBindTexture(GL_TEXTURE_2D, this->textura);
}

GLuint Textura::getTextura()
{
	return this->textura;
}

int Textura::getIndiceTextura()
{
	return this->indiceTextura;
}


Textura::~Textura()
{
}
