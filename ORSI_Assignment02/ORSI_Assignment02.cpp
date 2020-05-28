#include <iostream>
#include <fstream>
#include <vector>
#include "pipe.hpp"
#include <thread>

//UNUSED/RENDUNDANT ----Prints out the inputs, it was used to print the matrices and vectors to test the correctness of input handling
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
//Applies a transformation, passes parameter BY REFERENCE watch out for that
std::vector<int> Transform(std::vector<std::vector<int>> matrix, std::vector<int> vector)
{
	std::vector<int> tempvector(4);
	for (int i = 0; i < 4;i++)
	{
		tempvector[i] = 0;
		for (int j = 0; j < 4; j++)
		{
			tempvector[i] += matrix[i][j] * vector[j];
		}
	}
	return tempvector;
}
void ThreadFunction(std::vector<std::vector<int>> ThreadMatrix, Pipe<std::vector<int>>* MyPipe,Pipe<std::vector<int>>* NextPipe, const int n)
{
	for (int i = 0; i < n; i++)
	{
		std::vector<int> vectorfrompipe = MyPipe->pop(); //Takes out from his pipe and waits for next
		std::vector<int> vectortopipe = Transform(ThreadMatrix, vectorfrompipe); //Applies the transformation
		NextPipe->push(vectortopipe);	//Puts the vector into the next threads pipe
	}
}
//Reads the matrices from the input files
//Starts M threads
//Receives results
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
	//Creating a Pipeline using Pipe.hpp
	std::vector<Pipe<std::vector<int>>*> PipeLine; //Last pipe is the main's
	for (int i = 0; i < m+1; i++)
	{
		PipeLine.push_back(new Pipe<std::vector<int>>);
	}
	//Creating Threads
	std::vector<std::thread> threads(m);
	for (int i = 0; i < m; i++)
	{
		threads.push_back(std::thread(ThreadFunction,matrices[i],PipeLine[i],PipeLine[i+1],n));
	}
	
	//Starting the Dataflow and writing finished products to output.txt
	std::ofstream oFile("output.txt");
	std::vector<int> x;
	for (int i = 0; i < n; i++)
	{
		PipeLine[0]->push(vectors[i]);
		x = PipeLine[m]->pop();
		oFile << x[0] << " " << x[1] << " " << x[2] << std::endl;
	}
	oFile.close();
	//Join Threads
	for (int i = 0; i < threads.size(); i++)
	{
		if (threads[i].joinable())
		{
			threads[i].join();
		}
	}
	return 0;
}