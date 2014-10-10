#include "MeshData.h"

using namespace std;

MeshData::MeshData(void){
}


MeshData::~MeshData(void){
}

void MeshData::AddVertexUnit(VertexUnit unit){
	bool add = true;
	int i = 0;
	const int count = data.size();

	while (add && i < count)
	{
		if (data[i] == unit)
		{
			add = false;
			indices.push_back(uint(i));
		}

		i++;
	}

	if (add)
	{
		data.push_back(unit);
		indices.push_back(count - 1);
	}
}