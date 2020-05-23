#include <iostream>
#include <fstream>
#include <vector>
#include "pipe.hpp"
#include <future>

//Prints out the inputs
void PrintM(std::vector<std::vector<std::vector<int>>> argmatrices, std::vector<std::vector<int>> argvectors)
{
	std::cout << argmatrices.size() << std::endl;
	for (int i = 0; i < argmatrices.size(); i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				std::cout << argmatrices[i][j][k] << " ";
			}
			std::cout << std::endl;
		}
	}
	std::cout << argvectors.size() << std::endl;
	for (int i = 0; i < argvectors.size(); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			std::cout << argvectors[i][j] << " ";
		}
		std::cout << argvectors[i][3] << std::endl;
	}
}
//Reads the matrices from the input files
//Starts M threads
int main()
{
	int m,n;
	std::ifstream iFile("input_matrices.txt");
	iFile >> m;
	std::vector<std::vector<std::vector<int>>> matrices(m, std::vector<std::vector<int>>(4,std::vector<int>(4)));
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			for (int k = 0; k < 4; k++)
			{
				iFile >> matrices[i][j][k];
			}
		}
	}
	iFile.close();
	std::ifstream iFile2("input_points.txt");
	iFile2 >> n;
	std::vector<std::vector<int>> vectors(n, std::vector<int>(4));
	for (int i = 0; i < n; i++)
	{
		vectors[i][3] = 1; //The Task suggested it this way
		for (int j = 0; j < 3; j++)
		{
			iFile2 >> vectors[i][j];
		}
	}
	iFile2.close();
	PrintM(matrices, vectors);
	//Starting M threads
	/*for (int i = 0; i < m; i++)
	{

	}*/
}