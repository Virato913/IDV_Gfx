#include <IDVParser.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include <iomanip>




Parser::Parser()
{
}

void Parser::CargarVertices()
{
	std::fstream vertexFile;
	std::vector<Vertex>::iterator vertexIterator;
	std::string fileName, word, textureName;

	char ans;
	do
	{
		std::cout << "Por favor introduzca el nombre del archivo. \n";
		getline(std::cin, fileName);
		std::string path = "Models/";

		vertexFile.open(path + fileName + ".X", std::ios_base::in, std::ios::binary);

		if (vertexFile.is_open())
		{
			ans = 'l';

			while (getline(vertexFile, word) && !vertexFile.eof())
			{
				if (!word.find(" Mesh mesh_"))
				{
					meshCount++;
				}
			}
			vertexFile.clear();
			vertexFile.seekg(0, vertexFile.beg);

			for (int meshNum = 0; meshNum < meshCount; meshNum++)
			{
				std::vector<Vertex> tempVec;
				std::vector<unsigned short> indexCoordinates;
				Mesh mesh;
				int txts = 0;
				mesh.totalVertex = 0;
				mesh.totalIndexes = 0;
				bool  done = false;
				while (getline(vertexFile, word) && !done)
				{
					if (!word.find(" Mesh mesh_"))
					{
						vertexFile >> mesh.totalVertex;
						vertexFile >> ans;
						for (int i = 0; i < mesh.totalVertex; i++)
						{
							Vertex vertxCoordinates;
							vertexFile >> vertxCoordinates.x;
							vertexFile >> ans;
							vertexFile >> vertxCoordinates.y;
							vertexFile >> ans;
							vertexFile >> vertxCoordinates.z;
							vertexFile >> ans;
							vertexFile >> ans;

							tempVec.push_back(vertxCoordinates);
						}
						vertexFile >> mesh.totalIndexes;
						vertexFile >> ans;

						for (int i = 0; i < mesh.totalIndexes; i++)
						{
							unsigned short x, y, z;
							vertexFile >> ans;
							vertexFile >> ans;
							vertexFile >> x;
							vertexFile >> ans;
							vertexFile >> y;
							vertexFile >> ans;
							vertexFile >> z;
							vertexFile >> ans;
							vertexFile >> ans;

							mesh.indexCoordinatesMesh.push_back(x);
							mesh.indexCoordinatesMesh.push_back(y);
							mesh.indexCoordinatesMesh.push_back(z);
						}
					}

					if (!word.find("  MeshNormals n"))
					{
						vertexFile >> mesh.totalVertex;
						vertexFile >> ans;
						for (int i = 0; i < mesh.totalVertex; i++)
						{
							vertexFile >> tempVec[i].xn;
							vertexFile >> ans;
							vertexFile >> tempVec[i].yn;
							vertexFile >> ans;
							vertexFile >> tempVec[i].zn;
							vertexFile >> ans;
							vertexFile >> ans;
						}
					}

					if (!word.find("  MeshTextureCoords t"))
					{
						vertexFile >> mesh.totalVertex;
						vertexFile >> ans;
						for (int i = 0; i < mesh.totalVertex; i++)
						{
							vertexFile >> tempVec[i].u;
							vertexFile >> ans;
							vertexFile >> tempVec[i].v;
							vertexFile >> ans;
							vertexFile >> ans;
						}
					}

					if (!word.find("  DeclData {"))
					{
						vertexFile >> mesh.totalMaterials;
						vertexFile >> ans;
						mesh.meshMetaInfo.resize(mesh.totalMaterials);
						for (int i = 0; i < mesh.totalMaterials; i++)
						{
							unsigned short matType;
							vertexFile >> ans;
							vertexFile >> ans;
							vertexFile >> ans;
							vertexFile >> ans;
							vertexFile >> matType;
							vertexFile >> ans;
							vertexFile >> ans;
							vertexFile >> ans;
							vertexFile >> ans;
							mesh.MaterialType.push_back(matType);
						}
						vertexFile >> mesh.totalMeta;
						vertexFile >> ans;
						mesh.meshMetaInfo.resize(mesh.totalMeta);
						for (int i = 0; i < mesh.totalVertex; i++)
						{
							for (int j = 0; j < mesh.totalMaterials; j++)
							{
								MetaObject metaObject;
								unsigned int x, y, z;
								vertexFile >> x;
								vertexFile >> ans;
								vertexFile >> y;
								vertexFile >> ans;
								vertexFile >> z;
								vertexFile >> ans;

								metaObject.mx = reinterpret_cast<float&>(x);
								metaObject.my = reinterpret_cast<float&>(y);
								metaObject.mz = reinterpret_cast<float&>(z);

								mesh.meshMetaInfo[j].submeta.push_back(metaObject);
							}
						}
					}


					if (!word.find("  MeshMaterialList"))
					{
						vertexFile >> mesh.totalMaterialsInMesh;
						vertexFile >> ans;
						vertexFile >> mesh.totalMaterials;
						vertexFile >> ans;

						mesh.totalMeshMaterials.resize(mesh.totalMaterialsInMesh);
						int matID = -1;
						for (int i = 0; i < mesh.totalIndexes; i++)
						{
							vertexFile >> matID;
							vertexFile >> ans;

							mesh.totalMeshMaterials[matID].mtlBuffer.push_back(mesh.indexCoordinatesMesh[(i * 3) + 0]);
							mesh.totalMeshMaterials[matID].mtlBuffer.push_back(mesh.indexCoordinatesMesh[(i * 3) + 1]);
							mesh.totalMeshMaterials[matID].mtlBuffer.push_back(mesh.indexCoordinatesMesh[(i * 3) + 2]);
						}
					}

					if (!word.find("    TextureFilename Diffuse"))
					{
						vertexFile >> quoted(textureName);


						mesh.nombresTexturas.push_back(textureName);
						mesh.totaltext++;
						txts++;
					}

					if (txts >= mesh.totalMaterialsInMesh)
					{
						done = true;
					}
				}

				mesh.TotalVertex = tempVec;
				totalMeshes.push_back(mesh);
			}
			vertexFile.close();
		}
		else
		{
			std::cout << "ERROR: No se pudo cargar el archivo. Revise que el nombre del archivo este escrito correctamente, o que el archivo se encuentre en la carpeta del programa.\n\nDesea intentarlo de nuevo?\ny/n" << std::endl;
			std::cin >> ans;
			std::cin.ignore();
		}
		std::cout << "Modelo cargado con exito." << std::endl;
	} while (ans == 'Y' || ans == 'y');
}