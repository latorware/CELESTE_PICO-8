#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "TileMap.h"

#define POSXBLOC1LVL4 142
#define POSYBLOC1LVL4 495
#define POSXBLOC2LVL4 174
#define POSYBLOC2LVL4 495

#define POSXBLOC3LVL4 270
#define POSYBLOC3LVL4 463
#define POSXBLOC4LVL4 302
#define POSYBLOC4LVL4 463

#define POSXBLOC5LVL4 398
#define POSYBLOC5LVL4 431
#define POSXBLOC6LVL4 430
#define POSYBLOC6LVL4 431

#define POSXBLOC7LVL4 462
#define POSYBLOC7LVL4 367
#define POSXBLOC8LVL4 494
#define POSYBLOC8LVL4 367

#define POSXBLOC9LVL4 366
#define POSYBLOC9LVL4 303
#define POSXBLOC10LVL4 398
#define POSYBLOC10LVL4 303

#define POSXBLOC11LVL4 398
#define POSYBLOC11LVL4 207
#define POSXBLOC12LVL4 430
#define POSYBLOC12LVL4 207

#define POSXCLAULVL5 245
#define POSYCLAULVL5 460
#define POSXTRESORLVL5 470
#define POSYTRESORLVL5 400
#define POSXMADUIXALVL5 485
#define POSYMADUIXALVL5 380
#define POSXMADUIXALVL7 330
#define POSYMADUIXALVL7 120


#define POSXBLOC1LVL8 230
#define POSYBLOC1LVL8 460
#define POSXBLOC2LVL8 262
#define POSYBLOC2LVL8 460
#define POSXBLOC3LVL8 294
#define POSYBLOC3LVL8 460

#define POSXBLOC1LVL10 180
#define POSYBLOC1LVL10 460
#define POSXBLOC2LVL10 212
#define POSYBLOC2LVL10 460
#define POSXBLOC3LVL10 340
#define POSYBLOC3LVL10 460
#define POSXBLOC4LVL10 372
#define POSYBLOC4LVL10 460


#define OFFSET 20


using namespace std;


TileMap* TileMap::createTileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program, int levell, vector<bool>* spriteShouldBeRenderedd)
{
	TileMap* map = new TileMap(levelFile, minCoords, program, levell, spriteShouldBeRenderedd);

	return map;
}


TileMap::TileMap(const string& levelFile, const glm::vec2& minCoords, ShaderProgram& program, int levell, vector<bool>* spriteShouldBeRenderedd)
{
	loadLevel(levelFile);
	prepareArrays(minCoords, program);
	level = levell;
	spriteShouldBeRendered = spriteShouldBeRenderedd;

}

TileMap::~TileMap()
{
	if (map != NULL)
		delete map;
}


void TileMap::render() const
{
	glEnable(GL_TEXTURE_2D);
	tilesheet.use();
	glBindVertexArray(vao);
	glEnableVertexAttribArray(posLocation);
	glEnableVertexAttribArray(texCoordLocation);
	glDrawArrays(GL_TRIANGLES, 0, 6 * mapSize.x * mapSize.y);
	glDisable(GL_TEXTURE_2D);
}

void TileMap::free()
{
	glDeleteBuffers(1, &vbo);
}

bool TileMap::loadLevel(const string& levelFile)
{
	ifstream fin;
	string line, tilesheetFile;
	stringstream sstream;
	int tile;

	fin.open(levelFile.c_str());
	if (!fin.is_open())
		return false;
	getline(fin, line);
	if (line.compare(0, 7, "TILEMAP") != 0)
		return false;
	getline(fin, line);
	sstream.str(line);
	sstream >> mapSize.x >> mapSize.y;
	getline(fin, line);
	sstream.str(line);
	sstream >> tileSize >> blockSize;
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetFile;
	tilesheet.loadFromFile(tilesheetFile, TEXTURE_PIXEL_FORMAT_RGBA);
	tilesheet.setWrapS(GL_CLAMP_TO_EDGE);
	tilesheet.setWrapT(GL_CLAMP_TO_EDGE);
	tilesheet.setMinFilter(GL_NEAREST);
	tilesheet.setMagFilter(GL_NEAREST);
	getline(fin, line);
	sstream.str(line);
	sstream >> tilesheetSize.x >> tilesheetSize.y;
	tileTexSize = glm::vec2(1.f / tilesheetSize.x, 1.f / tilesheetSize.y);

	map = new int[mapSize.x * mapSize.y];
	for (int j = 0; j < mapSize.y; j++)
	{
		for (int i = 0; i < mapSize.x; i++)
		{
			fin >> tile;
			map[j * mapSize.x + i] = tile;
		}
	}
	fin.close();

	return true;
}

void TileMap::prepareArrays(const glm::vec2& minCoords, ShaderProgram& program)
{
	int tile, nTiles = 0;
	glm::vec2 posTile, texCoordTile[2], halfTexel;
	vector<float> vertices;

	halfTexel = glm::vec2(0.5f / tilesheet.width(), 0.5f / tilesheet.height());
	for (int j = 0; j < mapSize.y; j++)
	{
		for (int i = 0; i < mapSize.x; i++)
		{
			tile = map[j * mapSize.x + i];
			if (tile != 0)
			{
				// Non-empty tile
				nTiles++;
				posTile = glm::vec2(minCoords.x + i * tileSize, minCoords.y + j * tileSize);
				texCoordTile[0] = glm::vec2(float((tile - 1) % tilesheetSize.x) / tilesheetSize.x, float((tile - 1) / tilesheetSize.x) / tilesheetSize.y);
				texCoordTile[1] = texCoordTile[0] + tileTexSize;
				//texCoordTile[0] += halfTexel;
				texCoordTile[1] -= halfTexel;
				// First triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				// Second triangle
				vertices.push_back(posTile.x); vertices.push_back(posTile.y);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[0].y);
				vertices.push_back(posTile.x + blockSize); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[1].x); vertices.push_back(texCoordTile[1].y);
				vertices.push_back(posTile.x); vertices.push_back(posTile.y + blockSize);
				vertices.push_back(texCoordTile[0].x); vertices.push_back(texCoordTile[1].y);
			}
		}
	}

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 24 * nTiles * sizeof(float), &vertices[0], GL_STATIC_DRAW);
	posLocation = program.bindVertexAttribute("position", 2, 4 * sizeof(float), 0);
	texCoordLocation = program.bindVertexAttribute("texCoord", 2, 4 * sizeof(float), (void*)(2 * sizeof(float)));
}

// Collision tests for axis aligned bounding boxes.
// Method collisionMoveDown also corrects Y coordinate if the box is
// already intersecting a tile below.

bool TileMap::collisionMoveLeft(const glm::ivec2& pos, const glm::ivec2& size) const
{
	int x, y0, y1;

	x = pos.x / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if (map[y * mapSize.x + x] != 0)
			return true;
	}

	return false;
}

bool TileMap::collisionMoveRight(const glm::ivec2& pos, const glm::ivec2& size/*, int* posX*/) const
{
	int x, y0, y1;

	x = (pos.x + size.x - 1) / tileSize;
	y0 = pos.y / tileSize;
	y1 = (pos.y + size.y - 1) / tileSize;
	for (int y = y0; y <= y1; y++)
	{
		if (map[y * mapSize.x + x] != 0)
		{
			/*	Necesario para comprobar las colisiones hacia la derecha si aumentamos la velocidad a 4
			if (*posX - tileSize * x + size.x <= 8)
			{
				*posX = tileSize * x - size.x;
				return true;
			}*/
			return true;
		}
	}

	return false;
}

bool TileMap::collisionMoveDown(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = (pos.y + size.y - 1) / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if (map[y * mapSize.x + x] != 0)
		{
			if (*posY - tileSize * y + size.y <= 8)
			{
				*posY = tileSize * y - size.y;
				cout << "posx " << pos.x << "        posy " << pos.y << endl;
				return true;
			}
		}
	}

	//Cas que sigui level 4, analitzar els blocs flotants
	if (level == 4)
	{

		int y = pos.y + 14;
		int x = pos.x + 14;
		if ((((y >= ((POSYBLOC1LVL4-16) - OFFSET)) && (y <= ((POSYBLOC1LVL4-16) + OFFSET))) && ((x >= (POSXBLOC1LVL4 - OFFSET)) && (x <= (POSXBLOC1LVL4 + OFFSET)))))
		{
			if ((*spriteShouldBeRendered)[3])
			{
				//cout << "topat amb mur" << endl;
				if (*posY - tileSize * ((pos.y + size.y - 1) / tileSize) + size.y <= 8)
				{
					*posY = tileSize * ((pos.y + size.y - 1) / tileSize) - size.y;
					return true;
				}

				return true;
			}
		}
		else if ((((y >= ((POSYBLOC2LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC2LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC2LVL4 - OFFSET)) && (x <= (POSXBLOC2LVL4 + OFFSET)))))
		{
			if ((*spriteShouldBeRendered)[4])
			{
				//cout << "topat amb mur" << endl;
				if (*posY - tileSize * ((pos.y + size.y - 1) / tileSize) + size.y <= 8)
				{
					*posY = tileSize * ((pos.y + size.y - 1) / tileSize) - size.y;
					return true;
				}

				return true;
			}
		}
		else if ((((y >= ((POSYBLOC3LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC3LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC3LVL4 - OFFSET)) && (x <= (POSXBLOC3LVL4 + OFFSET)))))
		{
			if ((*spriteShouldBeRendered)[5])
			{
				//cout << "topat amb mur" << endl;
				if (*posY - tileSize * ((pos.y + size.y - 1) / tileSize) + size.y <= 8)
				{
					*posY = tileSize * ((pos.y + size.y - 1) / tileSize) - size.y;
					return true;
				}

				return true;
			}
		}
		else if ((((y >= ((POSYBLOC4LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC4LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC4LVL4 - OFFSET)) && (x <= (POSXBLOC4LVL4 + OFFSET)))))
		{
			if ((*spriteShouldBeRendered)[6])
			{
				//cout << "topat amb mur" << endl;
				if (*posY - tileSize * ((pos.y + size.y - 1) / tileSize) + size.y <= 8)
				{
					*posY = tileSize * ((pos.y + size.y - 1) / tileSize) - size.y;
					return true;
				}

				return true;
			}
		}
		else if ((((y >= ((POSYBLOC5LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC5LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC5LVL4 - OFFSET)) && (x <= (POSXBLOC5LVL4 + OFFSET)))))
		{
			if ((*spriteShouldBeRendered)[7])
			{
				//cout << "topat amb mur" << endl;
				if (*posY - tileSize * ((pos.y + size.y - 1) / tileSize) + size.y <= 8)
				{
					*posY = tileSize * ((pos.y + size.y - 1) / tileSize) - size.y;
					return true;
				}

				return true;
			}
		}
		else if ((((y >= ((POSYBLOC6LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC6LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC6LVL4 - OFFSET)) && (x <= (POSXBLOC6LVL4 + OFFSET)))))
		{
			if ((*spriteShouldBeRendered)[8])
			{
				//cout << "topat amb mur" << endl;
				if (*posY - tileSize * ((pos.y + size.y - 1) / tileSize) + size.y <= 8)
				{
					*posY = tileSize * ((pos.y + size.y - 1) / tileSize) - size.y;
					return true;
				}

				return true;
			}
		}
		else if ((((y >= ((POSYBLOC7LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC7LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC7LVL4 - OFFSET)) && (x <= (POSXBLOC7LVL4 + OFFSET)))))
		{
			if ((*spriteShouldBeRendered)[9])
			{
				//cout << "topat amb mur" << endl;
				if (*posY - tileSize * ((pos.y + size.y - 1) / tileSize) + size.y <= 8)
				{
					*posY = tileSize * ((pos.y + size.y - 1) / tileSize) - size.y;
					return true;
				}

				return true;
			}
		}
		else if ((((y >= ((POSYBLOC8LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC8LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC8LVL4 - OFFSET)) && (x <= (POSXBLOC8LVL4 + OFFSET)))))
		{
			if ((*spriteShouldBeRendered)[10])
			{
				//cout << "topat amb mur" << endl;
				if (*posY - tileSize * ((pos.y + size.y - 1) / tileSize) + size.y <= 8)
				{
					*posY = tileSize * ((pos.y + size.y - 1) / tileSize) - size.y;
					return true;
				}

				return true;
			}
		}
		else if ((((y >= ((POSYBLOC9LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC9LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC9LVL4 - OFFSET)) && (x <= (POSXBLOC9LVL4 + OFFSET)))))
		{
			if ((*spriteShouldBeRendered)[11])
			{
				//cout << "topat amb mur" << endl;
				if (*posY - tileSize * ((pos.y + size.y - 1) / tileSize) + size.y <= 8)
				{
					*posY = tileSize * ((pos.y + size.y - 1) / tileSize) - size.y;
					return true;
				}

				return true;
			}
		}
		else if ((((y >= ((POSYBLOC10LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC10LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC10LVL4 - OFFSET)) && (x <= (POSXBLOC10LVL4 + OFFSET)))))
		{
			if ((*spriteShouldBeRendered)[12])
			{
				//cout << "topat amb mur" << endl;
				if (*posY - tileSize * ((pos.y + size.y - 1) / tileSize) + size.y <= 8)
				{
					*posY = tileSize * ((pos.y + size.y - 1) / tileSize) - size.y;
					return true;
				}

				return true;
			}
		}
		else if ((((y >= ((POSYBLOC11LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC11LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC11LVL4 - OFFSET)) && (x <= (POSXBLOC11LVL4 + OFFSET)))))
		{
			if ((*spriteShouldBeRendered)[13])
			{
				//cout << "topat amb mur" << endl;
				if (*posY - tileSize * ((pos.y + size.y - 1) / tileSize) + size.y <= 8)
				{
					*posY = tileSize * ((pos.y + size.y - 1) / tileSize) - size.y;
					return true;
				}

				return true;
			}
		}
		else if ((((y >= ((POSYBLOC12LVL4 - 16) - OFFSET)) && (y <= ((POSYBLOC12LVL4 - 16) + OFFSET))) && ((x >= (POSXBLOC12LVL4 - OFFSET)) && (x <= (POSXBLOC12LVL4 + OFFSET)))))
		{
			if ((*spriteShouldBeRendered)[14])
			{
				//cout << "topat amb mur" << endl;
				if (*posY - tileSize * ((pos.y + size.y - 1) / tileSize) + size.y <= 8)
				{
					*posY = tileSize * ((pos.y + size.y - 1) / tileSize) - size.y;
					return true;
				}

				return true;
			}
		}
	}

	//Cas que sigui level 8, analitzar els blocs flotants
	if (level == 8)
	{

		int y = pos.y + 14;
		int x = pos.x + 14;
		if ((((y >= ((POSYBLOC1LVL8 - 16) - OFFSET)) && (y <= ((POSYBLOC1LVL8 - 16) + OFFSET))) && ((x >= (POSXBLOC1LVL8 - OFFSET)) && (x <= (POSXBLOC1LVL8 + OFFSET)))))
		{
			if ((*spriteShouldBeRendered)[0])
			{
				//cout << "topat amb mur" << endl;
				if (*posY - tileSize * ((pos.y + size.y - 1) / tileSize) + size.y <= 8)
				{
					*posY = tileSize * ((pos.y + size.y - 1) / tileSize) - size.y;
					return true;
				}

				return true;
			}
		}
		else if ((((y >= ((POSYBLOC2LVL8 - 16) - OFFSET)) && (y <= ((POSYBLOC2LVL8 - 16) + OFFSET))) && ((x >= (POSXBLOC2LVL8 - OFFSET)) && (x <= (POSXBLOC2LVL8 + OFFSET)))))
		{
			if ((*spriteShouldBeRendered)[1])
			{
				//cout << "topat amb mur" << endl;
				if (*posY - tileSize * ((pos.y + size.y - 1) / tileSize) + size.y <= 8)
				{
					*posY = tileSize * ((pos.y + size.y - 1) / tileSize) - size.y;
					return true;
				}

				return true;
			}
		}
		else if ((((y >= ((POSYBLOC3LVL8 - 16) - OFFSET)) && (y <= ((POSYBLOC3LVL8 - 16) + OFFSET))) && ((x >= (POSXBLOC3LVL8 - OFFSET)) && (x <= (POSXBLOC3LVL8 + OFFSET)))))
		{
			if ((*spriteShouldBeRendered)[2])
			{
				//cout << "topat amb mur" << endl;
				if (*posY - tileSize * ((pos.y + size.y - 1) / tileSize) + size.y <= 8)
				{
					*posY = tileSize * ((pos.y + size.y - 1) / tileSize) - size.y;
					return true;
				}

				return true;
			}
		}
	}

	//Cas que sigui level 10, analitzar els blocs flotants
	if (level == 10)
	{

		int y = pos.y + 14;
		int x = pos.x + 14;
		if ((((y >= ((POSYBLOC1LVL10 - 16) - OFFSET)) && (y <= ((POSYBLOC1LVL10 - 16) + OFFSET))) && ((x >= (POSXBLOC1LVL10 - OFFSET)) && (x <= (POSXBLOC1LVL10 + OFFSET)))))
		{
			if ((*spriteShouldBeRendered)[0])
			{
				//cout << "topat amb mur" << endl;
				if (*posY - tileSize * ((pos.y + size.y - 1) / tileSize) + size.y <= 8)
				{
					*posY = tileSize * ((pos.y + size.y - 1) / tileSize) - size.y;
					return true;
				}

				return true;
			}
		}
		else if ((((y >= ((POSYBLOC2LVL10 - 16) - OFFSET)) && (y <= ((POSYBLOC2LVL10 - 16) + OFFSET))) && ((x >= (POSXBLOC2LVL10 - OFFSET)) && (x <= (POSXBLOC2LVL10 + OFFSET)))))
		{
			if ((*spriteShouldBeRendered)[1])
			{
				//cout << "topat amb mur" << endl;
				if (*posY - tileSize * ((pos.y + size.y - 1) / tileSize) + size.y <= 8)
				{
					*posY = tileSize * ((pos.y + size.y - 1) / tileSize) - size.y;
					return true;
				}

				return true;
			}
		}
		else if ((((y >= ((POSYBLOC3LVL10 - 16) - OFFSET)) && (y <= ((POSYBLOC3LVL10 - 16) + OFFSET))) && ((x >= (POSXBLOC3LVL10 - OFFSET)) && (x <= (POSXBLOC3LVL10 + OFFSET)))))
		{
			if ((*spriteShouldBeRendered)[2])
			{
				//cout << "topat amb mur" << endl;
				if (*posY - tileSize * ((pos.y + size.y - 1) / tileSize) + size.y <= 8)
				{
					*posY = tileSize * ((pos.y + size.y - 1) / tileSize) - size.y;
					return true;
				}

				return true;
			}
		}
		else if ((((y >= ((POSYBLOC4LVL10 - 16) - OFFSET)) && (y <= ((POSYBLOC4LVL10 - 16) + OFFSET))) && ((x >= (POSXBLOC4LVL10 - OFFSET)) && (x <= (POSXBLOC4LVL10 + OFFSET)))))
		{
			if ((*spriteShouldBeRendered)[3])
			{
				//cout << "topat amb mur" << endl;
				if (*posY - tileSize * ((pos.y + size.y - 1) / tileSize) + size.y <= 8)
				{
					*posY = tileSize * ((pos.y + size.y - 1) / tileSize) - size.y;
					return true;
				}

				return true;
			}
		}
	}

	return false;
}

bool TileMap::collisionMoveUp(const glm::ivec2& pos, const glm::ivec2& size, int* posY) const
{
	int x0, x1, y;

	x0 = pos.x / tileSize;
	x1 = (pos.x + size.x - 1) / tileSize;
	y = pos.y / tileSize;
	for (int x = x0; x <= x1; x++)
	{
		if (map[y * mapSize.x + x] != 0)
		{
			//if (*posY - tileSize * y <= 8)
			//{
				//*posY = tileSize * y + size.y;
				//return true;
			//}
			//*posY = tileSize * y + size.y;
			//cout << "posy" << pos.y  << endl; 
			return true;
		}
	}

	return false;
}









