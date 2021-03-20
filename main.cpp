#include <iostream>
#include <fstream>
#include <vector>
#include <list>

using namespace std;

class Vertex{
public:
	int idOfVertex;
	int indegreeNumb;
	int outdegreeNumb;
	vector<int> adjacentVertexes;
	vector<int> nonUsedEdge;

	Vertex(int idOfVertex, int outdegreeNumb, vector<int>& adjacentVertexes){
		this->idOfVertex = idOfVertex;
		this->outdegreeNumb = outdegreeNumb;
		this->adjacentVertexes = adjacentVertexes; 
		this->indegreeNumb = 0;
		for(int i = outdegreeNumb-1; i >=0; i--){
			this->nonUsedEdge.push_back(adjacentVertexes[i]);
		}
	};
};

bool isEulerian(vector<Vertex>& vertexes){
	for(int i = 0; i < vertexes.size(); i++){
		for(int j = 0; j < vertexes[i].adjacentVertexes.size(); j++){
			vertexes[vertexes[i].adjacentVertexes[j]].indegreeNumb++;
		}
	}

	for(int i = 0; i < vertexes.size(); i++){
		if(vertexes[i].indegreeNumb != vertexes[i].outdegreeNumb){
			return false;
		}
	}
	return true;
}


int main(int argc, char const *argv[]) {

	string input_file = argv[1];
	string output_file = argv[2];

	ifstream infile;
	infile.open(input_file);
	ofstream outfile;
	outfile.open(output_file);

	int vertexNumb;
	infile >> vertexNumb;

	vector<Vertex> vertexes;
	int totNumbOfEdges = 0;
	for(int i = 0;  i < vertexNumb; i++){
		int idOfVertex, outdegreeNumb;
		infile >> idOfVertex >> outdegreeNumb;
		totNumbOfEdges += outdegreeNumb;

		vector<int> adjacentVertexes;
		for(int i = 0; i < outdegreeNumb; i++){
			int adjacentVertexNo;
			infile >> adjacentVertexNo;
			adjacentVertexes.push_back(adjacentVertexNo);
		}
		vertexes.push_back(Vertex(idOfVertex, outdegreeNumb, adjacentVertexes));
	}

	int startVertexNo;
	infile >> startVertexNo;

	if(isEulerian(vertexes)){
		list<int> eulerianCircuit;
		eulerianCircuit.push_back(startVertexNo);
		list<int>::iterator it;
		it = eulerianCircuit.begin();
		list<int> tour;

		while(eulerianCircuit.size() <= totNumbOfEdges){
			while(vertexes[startVertexNo].nonUsedEdge.size() > 0){
				int firstNonUsedEdge = vertexes[startVertexNo].nonUsedEdge.back();
				vertexes[startVertexNo].nonUsedEdge.pop_back();
				startVertexNo = firstNonUsedEdge;
				tour.push_back(startVertexNo);
			}
			eulerianCircuit.splice(++it, tour);

			for(it = eulerianCircuit.begin(); it != eulerianCircuit.end(); it++){
				if(vertexes[*it].nonUsedEdge.size() > 0){
					break;
				}
			}
			startVertexNo = *it;
		}

		for(it = eulerianCircuit.begin(); it != eulerianCircuit.end(); it++){
			outfile << *it << " ";
		}

	}
	else{
		outfile << "no path";
	}

	infile.close();
	outfile.close();

	return 0;
}