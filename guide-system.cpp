#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <queue>
#include <vector>

using namespace std;

#ifdef INFINITY
#undef INFINITY
#endif
#define INFINITY 32767
#define MAXVEXNUM 10

struct VertexType { char SpotId[2]; char Name[20]; char Introduction[256]; };
struct EdgeType { int u; int v; int Weight; };
struct MatrixGraph { int VexNum; int EdgeNum; VertexType Vexs[MAXVEXNUM]; int Edges[MAXVEXNUM][MAXVEXNUM]; };
struct ArcNode { int adjvex; ArcNode *nextarc; int weight; };
struct VertexNode { VertexType VexData; int count; ArcNode *firstarc; };
struct AdjGraph { VertexNode adjlist[MAXVEXNUM]; int n; int e; };

void InitMatrixGraph(MatrixGraph &g);
void ResetEdgeRow(MatrixGraph &g, int idx);
void ShowMenu();
void ManaMapData(MatrixGraph &g);
void InitSpotsData(MatrixGraph &g);
bool SaveToMapFile(MatrixGraph g);
bool LoadFromMapFile(MatrixGraph &g);
void ManaVertexData(MatrixGraph &g);
void InOneSpotData(MatrixGraph &g, int i);
void InMultiSpotsData(MatrixGraph &g, int n);
void InDeleteSpotsData(MatrixGraph &g);
void InModifySpotsData(MatrixGraph &g);
void ManaRoadData(MatrixGraph &g);
void AddEdge(MatrixGraph &g);
void SeleteEdge(MatrixGraph &g);
void ModifyEdge(MatrixGraph &g);
void DispAllEdge(MatrixGraph g);
void ShowOneSpotData(MatrixGraph g, int i);
void ShowAllSpotsData(MatrixGraph g);
void SearchSpotInfor(MatrixGraph g);
int LocateSpotPos(MatrixGraph g, const char SpotName[]);
void VisitPathPlan(MatrixGraph &g);
bool MatrixToAdjList(MatrixGraph g, AdjGraph *&G);
void DispAdj(AdjGraph *G);
void DFS(AdjGraph *G, int v);
void DFSInternal(AdjGraph *G, int v, bool visited[]);
void BFS(AdjGraph *G, int v);
void DestroyAdj(AdjGraph *&G);
void ShortestPathQuery(MatrixGraph g);
void Dijkstra(MatrixGraph g, int v);
void Disppath(MatrixGraph g, int dist[], int path[], int S[], int v);
void Floyd(MatrixGraph g);
void Dispath(MatrixGraph g, int A[][MAXVEXNUM], int path[][MAXVEXNUM]);
void PrintFloydPath(MatrixGraph g, int path[][MAXVEXNUM], int i, int j);
void PipelineSystemOptimal(MatrixGraph g);
void Prim(MatrixGraph g, int v);
void Kruskal(MatrixGraph g);
void BubbleSort(EdgeType R[], int n);
int CountEdges(MatrixGraph g);

void InitMatrixGraph(MatrixGraph &g)
{
	g.VexNum = 0;
	g.EdgeNum = 0;
	for (int i = 0; i < MAXVEXNUM; i++)
	{
		memset(g.Vexs[i].SpotId, 0, sizeof(g.Vexs[i].SpotId));
		memset(g.Vexs[i].Name, 0, sizeof(g.Vexs[i].Name));
		memset(g.Vexs[i].Introduction, 0, sizeof(g.Vexs[i].Introduction));
		for (int j = 0; j < MAXVEXNUM; j++)
		{
			g.Edges[i][j] = (i == j ? 0 : INFINITY);
		}
	}
}

void ResetEdgeRow(MatrixGraph &g, int idx)
{
	for (int j = 0; j < MAXVEXNUM; j++)
	{
		if (j == idx)
		{
			g.Edges[idx][j] = 0;
		}
		else
		{
			g.Edges[idx][j] = INFINITY;
			g.Edges[j][idx] = INFINITY;
		}
	}
}

void ShowMenu()
{
	static const char *lines[] = {
		"***********************************************",
		"       武汉东湖学院校园导游信息系统主菜单       ",
		"***********************************************",
		"     1  景点地图整体管理                        ",
		"     2  校园景点数据管理                        ",
		"     3  景点交通数据管理                        ",
		"     4  校园景点信息查询                        ",
		"     5  游览线路查询规划                        ",
		"     6  景点最短路径查询                        ",
		"     7  管道系统最优布设                        ",
		"     0  退出校园导游系统                        ",
		"***********************************************"
	};
	for (const char *line : lines)
	{
		cout << line << endl;
	}
	cout << "             请输入功能编号(0~7): ";
}

void ManaMapData(MatrixGraph &g)
{
	int choice = -1;
	do
	{
		static const char *menu[] = {
			"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&",
			"        校园景点地图整体数据管理   ",
			"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&",
			" 1 初始化景点地图数据               ",
			" 2 保存景点地图数据                 ",
			" 3 读取景点地图数据                 ",
			" 0 返回主菜单                       ",
			"&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&"
		};
		for (const char *line : menu)
		{
			cout << line << endl;
		}
		cout << "请选择: ";
		cin >> choice;
		switch (choice)
		{
		case 1: InitSpotsData(g); break;
		case 2: cout << (SaveToMapFile(g) ? "景点地图数据保存成功。" : "景点地图数据保存失败，请检查文件权限。") << endl; break;
		case 3: cout << (LoadFromMapFile(g) ? "景点地图数据读取成功。" : "景点地图数据读取失败，当前可能没有保存文件。") << endl; break;
		case 0: cout << "返回主菜单。" << endl; break;
		default: cout << "功能编号无效，请重新选择。" << endl; break;
		}
	} while (choice != 0);
}

void InitSpotsData(MatrixGraph &g)
{
	InitMatrixGraph(g);
	cout << "已完成系统初始化，可开始录入景点信息。" << endl;
}

bool SaveToMapFile(MatrixGraph g)
{
	ofstream ofs("CampusSpotsData.dat", ios::binary | ios::out);
	if (!ofs) { return false; }
	ofs.write(reinterpret_cast<char *>(&g), sizeof(MatrixGraph));
	return true;
}

bool LoadFromMapFile(MatrixGraph &g)
{
	ifstream ifs("CampusSpotsData.dat", ios::binary | ios::in);
	if (!ifs) { return false; }
	ifs.read(reinterpret_cast<char *>(&g), sizeof(MatrixGraph));
	return true;
}

void ManaVertexData(MatrixGraph &g)
{
	int choice = -1;
	do
	{
		static const char *menu[] = {
			"============================================",
			"               校园景点数据管理             ",
			"============================================",
			" 1 增加景点数据                               ",
			" 2 删除景点数据                               ",
			" 3 修改景点数据                               ",
			" 4 显示景点数据                               ",
			" 0 返回主菜单                                 ",
			"============================================"
		};
		for (const char *line : menu)
		{
			cout << line << endl;
		}
		cout << "请选择: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			int remain = MAXVEXNUM - g.VexNum;
			if (remain <= 0)
			{
				cout << "景点容量已满，无法继续添加。" << endl;
				break;
			}
			cout << "当前可再添加的景点数量为 " << remain << "，请输入需要新增的数量: ";
			int n;
			cin >> n;
			if (n <= 0 || n > remain)
			{
				cout << "输入数量超出限制。" << endl;
			}
			else
			{
				InMultiSpotsData(g, n);
			}
			break;
		}
		case 2: InDeleteSpotsData(g); break;
		case 3: InModifySpotsData(g); break;
		case 4: ShowAllSpotsData(g); break;
		case 0: cout << "返回主菜单。" << endl; break;
		default: cout << "功能编号无效。" << endl; break;
		}
	} while (choice != 0);
}

void InOneSpotData(MatrixGraph &g, int i)
{
	char buffer[256];
	cout << "请输入景点编号(单字符即可): ";
	cin >> buffer;
	g.Vexs[i].SpotId[0] = buffer[0];
	g.Vexs[i].SpotId[1] = '\0';
	cout << "请输入景点名称(不含空格，<=19字符): ";
	cin >> setw(20) >> g.Vexs[i].Name;
	cout << "请输入景点简介(不含空格，<=255字符): ";
	cin >> setw(256) >> g.Vexs[i].Introduction;
	ResetEdgeRow(g, i);
}

void InMultiSpotsData(MatrixGraph &g, int n)
{
	int start = g.VexNum;
	for (int i = 0; i < n; i++)
	{
		if (start + i >= MAXVEXNUM)
		{
			cout << "达到最大容量，停止录入。" << endl;
			break;
		}
		cout << "---- 输入第 " << start + i + 1 << " 个景点信息 ----" << endl;
		InOneSpotData(g, start + i);
	}
	g.VexNum += n;
	if (g.VexNum > MAXVEXNUM)
	{
		g.VexNum = MAXVEXNUM;
	}
}

void InDeleteSpotsData(MatrixGraph &g)
{
	if (g.VexNum == 0)
	{
		cout << "暂无景点，无法删除。" << endl;
		return;
	}
	char name[20];
	cout << "请输入要删除的景点名称: ";
	cin >> setw(20) >> name;
	int pos = LocateSpotPos(g, name);
	if (pos == -1)
	{
		cout << "未找到指定景点。" << endl;
		return;
	}
	for (int i = pos; i < g.VexNum - 1; i++)
	{
		g.Vexs[i] = g.Vexs[i + 1];
		for (int j = 0; j < g.VexNum; j++)
		{
			g.Edges[i][j] = g.Edges[i + 1][j];
		}
	}
	for (int i = 0; i < g.VexNum - 1; i++)
	{
		for (int j = pos; j < g.VexNum - 1; j++)
		{
			g.Edges[i][j] = g.Edges[i][j + 1];
		}
	}
	g.VexNum--;
	g.EdgeNum = CountEdges(g);
	cout << "景点删除成功。" << endl;
}

void InModifySpotsData(MatrixGraph &g)
{
	if (g.VexNum == 0)
	{
		cout << "暂无景点数据可修改。" << endl;
		return;
	}
	char name[20];
	cout << "请输入要修改的景点名称: ";
	cin >> setw(20) >> name;
	int pos = LocateSpotPos(g, name);
	if (pos == -1)
	{
		cout << "未找到指定景点。" << endl;
		return;
	}
	cout << "当前景点信息如下:" << endl;
	ShowOneSpotData(g, pos);
	cout << "请重新录入该景点信息。" << endl;
	InOneSpotData(g, pos);
}

void ManaRoadData(MatrixGraph &g)
{
	int choice = -1;
	do
	{
		static const char *menu[] = {
			"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
			"             校园景点交通数据管理               ",
			"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~",
			" 1 增加景点交通数据                             ",
			" 2 删除景点交通数据                             ",
			" 3 修改景点交通数据                             ",
			" 4 显示景点交通数据                             ",
			" 0 返回主菜单                                   ",
			"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
		};
		for (const char *line : menu)
		{
			cout << line << endl;
		}
		cout << "请选择: ";
		cin >> choice;
		switch (choice)
		{
		case 1: AddEdge(g); break;
		case 2: SeleteEdge(g); break;
		case 3: ModifyEdge(g); break;
		case 4: DispAllEdge(g); break;
		case 0: cout << "返回主菜单。" << endl; break;
		default: cout << "功能编号无效。" << endl; break;
		}
	} while (choice != 0);
}

void AddEdge(MatrixGraph &g)
{
	if (g.VexNum < 2)
	{
		cout << "至少需要两个景点才能添加路径。" << endl;
		return;
	}
	char from[20];
	char to[20];
	cout << "请输入路径起点景点名称: ";
	cin >> setw(20) >> from;
	int p1 = LocateSpotPos(g, from);
	if (p1 == -1)
	{
		cout << "未找到起点景点。" << endl;
		return;
	}
	cout << "请输入路径终点景点名称: ";
	cin >> setw(20) >> to;
	int p2 = LocateSpotPos(g, to);
	if (p2 == -1)
	{
		cout << "未找到终点景点。" << endl;
		return;
	}
	if (p1 == p2)
	{
		cout << "起点和终点不能相同。" << endl;
		return;
	}
	cout << "请输入路径权值(正整数): ";
	int w;
	cin >> w;
	if (w <= 0)
	{
		cout << "权值必须为正整数。" << endl;
		return;
	}
	g.Edges[p1][p2] = w;
	g.Edges[p2][p1] = w;
	g.EdgeNum = CountEdges(g);
	cout << "路径添加成功。" << endl;
}

void SeleteEdge(MatrixGraph &g)
{
	if (g.VexNum < 2)
	{
		cout << "暂无路径可删除。" << endl;
		return;
	}
	char from[20];
	char to[20];
	cout << "请输入要删除路径的起点: ";
	cin >> setw(20) >> from;
	int p1 = LocateSpotPos(g, from);
	if (p1 == -1)
	{
		cout << "未找到起点景点。" << endl;
		return;
	}
	cout << "请输入要删除路径的终点: ";
	cin >> setw(20) >> to;
	int p2 = LocateSpotPos(g, to);
	if (p2 == -1)
	{
		cout << "未找到终点景点。" << endl;
		return;
	}
	if (g.Edges[p1][p2] == INFINITY)
	{
		cout << "两景点之间尚未建立路径。" << endl;
		return;
	}
	g.Edges[p1][p2] = INFINITY;
	g.Edges[p2][p1] = INFINITY;
	g.EdgeNum = CountEdges(g);
	cout << "路径删除成功。" << endl;
}

void ModifyEdge(MatrixGraph &g)
{
	if (g.VexNum < 2)
	{
		cout << "暂无路径可修改。" << endl;
		return;
	}
	char from[20];
	char to[20];
	cout << "请输入要修改路径的起点: ";
	cin >> setw(20) >> from;
	int p1 = LocateSpotPos(g, from);
	if (p1 == -1)
	{
		cout << "未找到起点。" << endl;
		return;
	}
	cout << "请输入要修改路径的终点: ";
	cin >> setw(20) >> to;
	int p2 = LocateSpotPos(g, to);
	if (p2 == -1)
	{
		cout << "未找到终点。" << endl;
		return;
	}
	if (g.Edges[p1][p2] == INFINITY)
	{
		cout << "两景点之间尚无路径，请先添加。" << endl;
		return;
	}
	cout << "请输入新的权值: ";
	int w;
	cin >> w;
	if (w <= 0)
	{
		cout << "权值必须为正整数。" << endl;
		return;
	}
	g.Edges[p1][p2] = w;
	g.Edges[p2][p1] = w;
	cout << "路径权值修改成功。" << endl;
}

void DispAllEdge(MatrixGraph g)
{
	if (g.EdgeNum == 0)
	{
		cout << "当前地图无任何路径数据。" << endl;
		return;
	}
	cout << left << setw(15) << "起点" << left << setw(15) << "终点" << left << setw(10) << "权值" << endl;
	cout << "----------------------------------------------" << endl;
	for (int i = 0; i < g.VexNum; i++)
	{
		for (int j = i + 1; j < g.VexNum; j++)
		{
			if (g.Edges[i][j] != INFINITY && g.Edges[i][j] > 0)
			{
				cout << left << setw(15) << g.Vexs[i].Name << left << setw(15) << g.Vexs[j].Name << left << setw(10) << g.Edges[i][j] << endl;
			}
		}
	}
}

void ShowOneSpotData(MatrixGraph g, int i)
{
	cout << "景点编号: " << g.Vexs[i].SpotId << endl;
	cout << "景点名称: " << g.Vexs[i].Name << endl;
	cout << "景点简介: " << g.Vexs[i].Introduction << endl;
}

void ShowAllSpotsData(MatrixGraph g)
{
	if (g.VexNum == 0)
	{
		cout << "暂无景点信息可展示。" << endl;
		return;
	}
	for (int i = 0; i < g.VexNum; i++)
	{
		cout << "----------------------------------------" << endl;
		cout << "第 " << i + 1 << " 个景点信息" << endl;
		ShowOneSpotData(g, i);
	}
	cout << "----------------------------------------" << endl;
}

void SearchSpotInfor(MatrixGraph g)
{
	if (g.VexNum == 0)
	{
		cout << "暂无景点可查询。" << endl;
		return;
	}
	char name[20];
	cout << "请输入要查询的景点名称: ";
	cin >> setw(20) >> name;
	int pos = LocateSpotPos(g, name);
	if (pos == -1)
	{
		cout << "未找到该景点。" << endl;
	}
	else
	{
		ShowOneSpotData(g, pos);
	}
}

int LocateSpotPos(MatrixGraph g, const char SpotName[])
{
	for (int i = 0; i < g.VexNum; i++)
	{
		if (strcmp(g.Vexs[i].Name, SpotName) == 0)
		{
			return i;
		}
	}
	return -1;
}

void VisitPathPlan(MatrixGraph &g)
{
	if (g.VexNum == 0)
	{
		cout << "请先录入景点数据。" << endl;
		return;
	}
	AdjGraph *G = nullptr;
	if (!MatrixToAdjList(g, G))
	{
		cout << "邻接表创建失败，无法进行游览线路规划。" << endl;
		return;
	}
	cout << "邻接表创建成功，内容如下:" << endl;
	DispAdj(G);
	char startName[20];
	cout << "请输入游览线路起点景点名称: ";
	cin >> setw(20) >> startName;
	int start = LocateSpotPos(g, startName);
	if (start == -1)
	{
		cout << "未找到该起点。" << endl;
		DestroyAdj(G);
		return;
	}
	int choice = -1;
	do
	{
		static const char *menu[] = {
			"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
			"        校园景点游览线路查询规划     ",
			"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@",
			" 1 深度优先游览线路查询规划         ",
			" 2 广度优先游览线路查询规划         ",
			" 0 返回主菜单                       ",
			"@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@"
		};
		for (const char *line : menu)
		{
			cout << line << endl;
		}
		cout << "请选择: ";
		cin >> choice;
		switch (choice)
		{
		case 1: cout << "深度优先遍历结果: "; DFS(G, start); cout << endl; break;
		case 2: cout << "广度优先遍历结果: "; BFS(G, start); cout << endl; break;
		case 0: cout << "返回主菜单。" << endl; break;
		default: cout << "功能编号无效。" << endl; break;
		}
	} while (choice != 0);
	DestroyAdj(G);
}

bool MatrixToAdjList(MatrixGraph g, AdjGraph *&G)
{
	G = new AdjGraph;
	G->n = g.VexNum;
	G->e = g.EdgeNum;
	for (int i = 0; i < g.VexNum; i++)
	{
		G->adjlist[i].VexData = g.Vexs[i];
		G->adjlist[i].count = 0;
		G->adjlist[i].firstarc = nullptr;
	}
	for (int i = 0; i < g.VexNum; i++)
	{
		for (int j = g.VexNum - 1; j >= 0; j--)
		{
			if (g.Edges[i][j] != INFINITY && g.Edges[i][j] > 0)
			{
				ArcNode *p = new ArcNode;
				p->adjvex = j;
				p->weight = g.Edges[i][j];
				p->nextarc = G->adjlist[i].firstarc;
				G->adjlist[i].firstarc = p;
			}
		}
	}
	return true;
}

void DispAdj(AdjGraph *G)
{
	for (int i = 0; i < G->n; i++)
	{
		cout << setw(15) << left << G->adjlist[i].VexData.Name << ": ";
		for (ArcNode *p = G->adjlist[i].firstarc; p != nullptr; p = p->nextarc)
		{
			cout << G->adjlist[p->adjvex].VexData.Name << "(" << p->weight << ") ";
		}
		cout << endl;
	}
}

void DFSInternal(AdjGraph *G, int v, bool visited[])
{
	visited[v] = true;
	cout << G->adjlist[v].VexData.Name << " ";
	for (ArcNode *p = G->adjlist[v].firstarc; p != nullptr; p = p->nextarc)
	{
		if (!visited[p->adjvex])
		{
			DFSInternal(G, p->adjvex, visited);
		}
	}
}

void DFS(AdjGraph *G, int v)
{
	bool visited[MAXVEXNUM];
	memset(visited, false, sizeof(visited));
	DFSInternal(G, v, visited);
	for (int i = 0; i < G->n; i++)
	{
		if (!visited[i])
		{
			DFSInternal(G, i, visited);
		}
	}
}

void BFS(AdjGraph *G, int v)
{
	bool visited[MAXVEXNUM];
	memset(visited, false, sizeof(visited));
	queue<int> q;
	visited[v] = true;
	q.push(v);
	while (!q.empty())
	{
		int u = q.front();
		q.pop();
		cout << G->adjlist[u].VexData.Name << " ";
		for (ArcNode *p = G->adjlist[u].firstarc; p != nullptr; p = p->nextarc)
		{
			if (!visited[p->adjvex])
			{
				visited[p->adjvex] = true;
				q.push(p->adjvex);
			}
		}
	}
	for (int i = 0; i < G->n; i++)
	{
		if (!visited[i])
		{
			visited[i] = true;
			q.push(i);
			while (!q.empty())
			{
				int u2 = q.front();
				q.pop();
				cout << G->adjlist[u2].VexData.Name << " ";
				for (ArcNode *p = G->adjlist[u2].firstarc; p != nullptr; p = p->nextarc)
				{
					if (!visited[p->adjvex])
					{
						visited[p->adjvex] = true;
						q.push(p->adjvex);
					}
				}
			}
		}
	}
}

void DestroyAdj(AdjGraph *&G)
{
	if (!G)
	{
		return;
	}
	for (int i = 0; i < G->n; i++)
	{
		ArcNode *p = G->adjlist[i].firstarc;
		while (p)
		{
			ArcNode *tmp = p;
			p = p->nextarc;
			delete tmp;
		}
		G->adjlist[i].firstarc = nullptr;
	}
	delete G;
	G = nullptr;
}

void ShortestPathQuery(MatrixGraph g)
{
	if (g.VexNum == 0)
	{
		cout << "暂无景点可进行最短路径计算。" << endl;
		return;
	}
	int choice = -1;
	do
	{
		static const char *menu[] = {
			"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^",
			"             校园景点最短路径查询               ",
			"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^",
			" 1 迪杰斯特拉(Dijkstra)算法                    ",
			" 2 弗洛伊德(Floyd)算法                         ",
			" 0 返回主菜单                                  ",
			"^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^"
		};
		for (const char *line : menu)
		{
			cout << line << endl;
		}
		cout << "请选择: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			char name[20];
			cout << "请输入起点景点名称: ";
			cin >> setw(20) >> name;
			int pos = LocateSpotPos(g, name);
			if (pos == -1)
			{
				cout << "起点不存在。" << endl;
			}
			else
			{
				Dijkstra(g, pos);
			}
			break;
		}
		case 2: Floyd(g); break;
		case 0: cout << "返回主菜单。" << endl; break;
		default: cout << "功能编号无效。" << endl; break;
		}
	} while (choice != 0);
}

void Dijkstra(MatrixGraph g, int v)
{
	int dist[MAXVEXNUM];
	int path[MAXVEXNUM];
	int S[MAXVEXNUM];
	for (int i = 0; i < g.VexNum; i++)
	{
		dist[i] = g.Edges[v][i];
		S[i] = 0;
		path[i] = (g.Edges[v][i] < INFINITY && i != v) ? v : -1;
	}
	dist[v] = 0;
	S[v] = 1;
	for (int i = 0; i < g.VexNum - 1; i++)
	{
		int min = INFINITY;
		int u = v;
		for (int j = 0; j < g.VexNum; j++)
		{
			if (!S[j] && dist[j] < min)
			{
				u = j;
				min = dist[j];
			}
		}
		S[u] = 1;
		for (int k = 0; k < g.VexNum; k++)
		{
			if (!S[k] && g.Edges[u][k] < INFINITY && dist[u] + g.Edges[u][k] < dist[k])
			{
				dist[k] = dist[u] + g.Edges[u][k];
				path[k] = u;
			}
		}
	}
	Disppath(g, dist, path, S, v);
}

void PrintPath(MatrixGraph g, int path[], int start, int end)
{
	if (start == end)
	{
		cout << g.Vexs[start].Name;
		return;
	}
	if (path[end] == -1)
	{
		cout << "不存在路径";
		return;
	}
	PrintPath(g, path, start, path[end]);
	cout << " -> " << g.Vexs[end].Name;
}

void Disppath(MatrixGraph g, int dist[], int path[], int S[], int v)
{
	cout << "以景点 " << g.Vexs[v].Name << " 为起点的最短路径结果如下:" << endl;
	for (int i = 0; i < g.VexNum; i++)
	{
		if (i == v)
		{
			continue;
		}
		cout << "到景点 " << g.Vexs[i].Name << " 的最短距离: ";
		if (dist[i] >= INFINITY)
		{
			cout << "不可达" << endl;
		}
		else
		{
			cout << dist[i] << "  路径: ";
			PrintPath(g, path, v, i);
			cout << endl;
		}
	}
}

void Floyd(MatrixGraph g)
{
	int A[MAXVEXNUM][MAXVEXNUM];
	int path[MAXVEXNUM][MAXVEXNUM];
	for (int i = 0; i < g.VexNum; i++)
	{
		for (int j = 0; j < g.VexNum; j++)
		{
			A[i][j] = g.Edges[i][j];
			path[i][j] = (i != j && g.Edges[i][j] < INFINITY) ? j : -1;
		}
	}
	for (int k = 0; k < g.VexNum; k++)
	{
		for (int i = 0; i < g.VexNum; i++)
		{
			for (int j = 0; j < g.VexNum; j++)
			{
				if (A[i][k] < INFINITY && A[k][j] < INFINITY && A[i][k] + A[k][j] < A[i][j])
				{
					A[i][j] = A[i][k] + A[k][j];
					path[i][j] = path[i][k];
				}
			}
		}
	}
	Dispath(g, A, path);
}

void PrintFloydPath(MatrixGraph g, int path[][MAXVEXNUM], int i, int j)
{
	cout << g.Vexs[i].Name;
	int current = i;
	while (current != j)
	{
		current = path[current][j];
		if (current == -1)
		{
			cout << " -> 不可达";
			return;
		}
		cout << " -> " << g.Vexs[current].Name;
	}
}

void Dispath(MatrixGraph g, int A[][MAXVEXNUM], int path[][MAXVEXNUM])
{
	for (int i = 0; i < g.VexNum; i++)
	{
		for (int j = 0; j < g.VexNum; j++)
		{
			if (i == j)
			{
				continue;
			}
			cout << g.Vexs[i].Name << " 到 " << g.Vexs[j].Name << " 的最短距离: ";
			if (A[i][j] >= INFINITY)
			{
				cout << "不可达" << endl;
			}
			else
			{
				cout << A[i][j] << "  路径: ";
				PrintFloydPath(g, path, i, j);
				cout << endl;
			}
		}
	}
}

void PipelineSystemOptimal(MatrixGraph g)
{
	if (g.VexNum == 0)
	{
		cout << "暂无景点数据，无法进行管道系统布设。" << endl;
		return;
	}
	int choice = -1;
	do
	{
		static const char *menu[] = {
			"#############################################",
			"             校园管道系统最优布设               ",
			"#############################################",
			" 1  普里姆(Prim)算法                           ",
			" 2  克鲁斯卡尔(Kruskal)算法                    ",
			" 0  返回主菜单                                 ",
			"#############################################"
		};
		for (const char *line : menu)
		{
			cout << line << endl;
		}
		cout << "请选择: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			char name[20];
			cout << "请输入管道系统最优布设起点景点名称: ";
			cin >> setw(20) >> name;
			int pos = LocateSpotPos(g, name);
			if (pos == -1)
			{
				cout << "起点不存在。" << endl;
			}
			else
			{
				Prim(g, pos);
			}
			break;
		}
		case 2: Kruskal(g); break;
		case 0: cout << "返回主菜单。" << endl; break;
		default: cout << "功能编号无效。" << endl; break;
		}
	} while (choice != 0);
}

void Prim(MatrixGraph g, int v)
{
	if (g.VexNum == 0)
	{
		cout << "图为空，无法执行Prim算法。" << endl;
		return;
	}
	int lowcost[MAXVEXNUM];
	int closest[MAXVEXNUM];
	for (int i = 0; i < g.VexNum; i++)
	{
		lowcost[i] = g.Edges[v][i];
		closest[i] = v;
	}
	closest[v] = -1;
	cout << "Prim算法生成的最小生成树边如下:" << endl;
	for (int i = 1; i < g.VexNum; i++)
	{
		int min = INFINITY;
		int k = -1;
		for (int j = 0; j < g.VexNum; j++)
		{
			if (closest[j] != -1 && lowcost[j] < min)
			{
				min = lowcost[j];
				k = j;
			}
		}
		if (k == -1)
		{
			cout << "图可能不连通，Prim算法提前结束。" << endl;
			return;
		}
		cout << g.Vexs[closest[k]].Name << " -- " << g.Vexs[k].Name << " : " << lowcost[k] << endl;
		closest[k] = -1;
		for (int j = 0; j < g.VexNum; j++)
		{
			if (closest[j] != -1 && g.Edges[k][j] < lowcost[j])
			{
				lowcost[j] = g.Edges[k][j];
				closest[j] = k;
			}
		}
	}
}

void Kruskal(MatrixGraph g)
{
	if (g.VexNum == 0)
	{
		cout << "图为空，无法执行Kruskal算法。" << endl;
		return;
	}
	vector<EdgeType> edges;
	for (int i = 0; i < g.VexNum; i++)
	{
		for (int j = i + 1; j < g.VexNum; j++)
		{
			if (g.Edges[i][j] != INFINITY && g.Edges[i][j] > 0)
			{
				edges.push_back({i, j, g.Edges[i][j]});
			}
		}
	}
	if (edges.empty())
	{
		cout << "图中无有效路径，无法执行Kruskal算法。" << endl;
		return;
	}
	BubbleSort(edges.data(), static_cast<int>(edges.size()));
	int parent[MAXVEXNUM];
	for (int i = 0; i < g.VexNum; i++)
	{
		parent[i] = -1;
	}
	cout << "Kruskal算法生成的最小生成树边如下:" << endl;
	int count = 0;
	for (size_t i = 0; i < edges.size() && count < g.VexNum - 1; i++)
	{
		int u = edges[i].u;
		int v = edges[i].v;
		int fu = u;
		while (parent[fu] != -1) { fu = parent[fu]; }
		int fv = v;
		while (parent[fv] != -1) { fv = parent[fv]; }
		if (fu != fv)
		{
			parent[fv] = fu;
			cout << g.Vexs[u].Name << " -- " << g.Vexs[v].Name << " : " << edges[i].Weight << endl;
			count++;
		}
	}
	if (count != g.VexNum - 1)
	{
		cout << "图不连通，未能生成完整的生成树。" << endl;
	}
}

void BubbleSort(EdgeType R[], int n)
{
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - 1 - i; j++)
		{
			if (R[j].Weight > R[j + 1].Weight)
			{
				EdgeType tmp = R[j];
				R[j] = R[j + 1];
				R[j + 1] = tmp;
			}
		}
	}
}

int CountEdges(MatrixGraph g)
{
	int count = 0;
	for (int i = 0; i < g.VexNum; i++)
	{
		for (int j = i + 1; j < g.VexNum; j++)
		{
			if (g.Edges[i][j] != INFINITY && g.Edges[i][j] > 0)
			{
				count++;
			}
		}
	}
	return count;
}

int main()
{
	MatrixGraph g;
	InitMatrixGraph(g);
	int choice = -1;
	do
	{
		ShowMenu();
		cin >> choice;
		switch (choice)
		{
		case 1: ManaMapData(g); break;
		case 2: ManaVertexData(g); break;
		case 3: ManaRoadData(g); break;
		case 4: SearchSpotInfor(g); break;
		case 5: VisitPathPlan(g); break;
		case 6: ShortestPathQuery(g); break;
		case 7: PipelineSystemOptimal(g); break;
		case 0: cout << "感谢使用武汉东湖学院校园导游系统，再见！" << endl; break;
		default: cout << "输入错误，请重新选择(0~7)。" << endl; break;
		}
	} while (choice != 0);
	return 0;
}

