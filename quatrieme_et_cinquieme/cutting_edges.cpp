#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int numberOfVertices, numberOfEdges;
vector<vector<int>> graph, copyGraph;
vector<int> vertices;
vector<pair<int, int>> cuttingEdges;
vector<bool> visited;

void displayGraphMatrix (vector<vector<int>> matrix)
{
  int i, j;

  for (i = 0; i < matrix.size (); ++i)
    {
      for (j = 0; j < matrix[i].size (); ++j)
        cout << matrix[i][j] << " ";
      cout << "\n";
    }
}

void getGraphMatrix ()
{
  int i, u, v;

  cout << "Input the number of vertices and the number of edges: ";
  cin >> numberOfVertices >> numberOfEdges;
  graph.assign (numberOfVertices, vector<int> (numberOfVertices, 0));

  cout << "Now input your edges:\n";
  for (i = 0; i < numberOfEdges; ++i)
    {
      cin >> u >> v;
      graph[--u][--v] = 1;
    }
  copyGraph = graph;
}

bool inGraph (int vertex)
{
  int sumRow = 0, sumColumn = 0, i, negSize = graph.size () - 2 * graph.size ();

  for (i = 0; i < graph.size (); ++i)
    sumRow += graph[vertex][i], sumColumn += graph[i][vertex];

  return (!((sumRow == sumColumn) && (sumColumn == negSize)));
}

int extractSink (vector<vector<int>> matrix)
{
  int i, j;
  bool has_sink;

  for (i = 0; i < matrix.size (); ++i)
    {
      has_sink = true;
      for (j = 0; j < matrix[i].size (); ++j)
        if (matrix[i][j] == 1)
          {
            has_sink = false;
            break;
          }
      if (has_sink && inGraph (i))
        return (i);
    }
  return (-1);
}

void reduceMatrix (int vertex)
{
  int i;

  for (i = 0; i < graph.size (); ++i)
    graph[vertex][i] = graph[i][vertex] = -1;
}

int extractSource (vector<vector<int>> matrix)
{
  int i, j;
  bool has_source;

  for (i = 0; i < matrix.size (); ++i)
    {
      has_source = true;
      for (j = 0; j < matrix[i].size (); ++j)
        if (matrix[j][i] == 1)
          {
            has_source = false;
            break;
          }
      if (has_source && inGraph (i))
        return (i);
    }
  return (-1);
}

int getDelta (int vertex)
{
  int outdegree = 0, indegree = 0, i;

  for (i = 0; i < graph.size (); ++i)
    {
      if (graph[vertex][i] == 1)
        ++outdegree;
      if (graph[i][vertex] == 1 && vertex != i)
        ++indegree;
    }
  return (outdegree - indegree);
}

int getMaxDeltaVertex ()
{
  int maxDeltaVertex = 0, maxDelta = getDelta (0), i;

  for (i = 1; i < graph.size (); ++i)
    {
      int curDelta = getDelta (i);
      if (curDelta >= maxDelta && inGraph (i))
        maxDelta = curDelta, maxDeltaVertex = i;
    }
  return (maxDeltaVertex);
}

int adjacencySum ()
{
  int sum = 0, i, j;

  for (i = 0; i < graph.size (); ++i)
    for (j = 0; j < graph[i].size (); ++j)
      sum += graph[i][j];

  return (sum);
}

void feedbackArcSetProblem ()
{
  vector<int> seqOne, seqTwo;
  int vertexPlaceholder;
  getGraphMatrix ();
  visited.assign (false, numberOfVertices);
  int grSize = graph.size ();
  int negGrSizeSq = -(grSize * grSize);

  while (adjacencySum () != negGrSizeSq)
    {
      while ((vertexPlaceholder = extractSink (graph)) != -1)
        {
          seqTwo.push_back (vertexPlaceholder);
          reduceMatrix (vertexPlaceholder);
        }

      if (adjacencySum () == negGrSizeSq)
        break;

      while ((vertexPlaceholder = extractSource (graph)) != -1)
        {
          seqOne.push_back (vertexPlaceholder);
          reduceMatrix (vertexPlaceholder);
        }

      if (adjacencySum () == negGrSizeSq)
        break;

      vertexPlaceholder = getMaxDeltaVertex ();
      seqOne.push_back (vertexPlaceholder);
      reduceMatrix (vertexPlaceholder);
    }

  reverse (seqTwo.begin (), seqTwo.end ());

  cout << "\nThis is the first sequence (s_1): ";
  for (int vertex : seqOne)
    {
      vertices.push_back (vertex);
      cout << ++vertex << " ";
    }
  cout << "\n";

  cout << "This is the second sequence (s_2): ";
  for (int vertex : seqTwo)
    {
      vertices.push_back (vertex);
      cout << ++vertex << " ";
    }
  cout << "\n";

  cout << "This is the required sequence (s = s_1 + s_2): ";
  for (int vertex : seqOne)
    cout << ++vertex << " ";
  for (int vertex : seqTwo)
    cout << ++vertex << " ";
  cout << "\n";

  for (int i = 0; i < copyGraph.size (); ++i)
    for (int j = 0; j < copyGraph[i].size (); ++j)
      if (copyGraph[i][j] == 1)
        if (vertices[i] > vertices[j])
          cuttingEdges.push_back (make_pair (i, j));
  cout << "Cutting edges are: ";
  for (int i = 0; i < cuttingEdges.size (); ++i)
    cout << ++cuttingEdges[i].first << "-" << ++cuttingEdges[i].second << (i == cuttingEdges.size () - 1 ? "\n" : ", ");
}

int main ()
{
  feedbackArcSetProblem ();

  return (EXIT_SUCCESS);
}

/*
5 5
1 2
2 3
3 4
4 2
4 5
*/

/*
10 12
1 2
2 3
3 7
7 2
3 4
4 5
5 6
6 4
7 8
8 9
9 10
10 8
*/



