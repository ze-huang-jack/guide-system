#include <iostream>
using namespace std;

#define INFINITY 32767 // 定义无穷大
#define MAXVEXNUM 10   // 最大顶点个数
// 以下定义图的邻接矩阵类型
typedef struct
{
	char SpotId[2];			// 景点编号
	char Name[20];			// 景点名称
	char Introduction[256]; // 景点简介
} VertexType;				// 景点类型

typedef struct
{
	int u;		// 边的起始顶点
	int v;		// 边的终止顶点
	int Weight; // 边的权重
} EdgeType;		// 边的类型

typedef struct
{
	int VexNum;						 // 顶点数，边数
	int EdgeNum;					 // 边数
	VertexType Vexs[MAXVEXNUM];		 // 存放顶点信息
	int Edges[MAXVEXNUM][MAXVEXNUM]; // 邻接矩阵数组
} MatrixGraph;						 // 完整的图邻接矩阵类型

// 以下定义邻接表类型

typedef struct ANode
{
	int adjvex;			   // 该边的邻接点编号
	struct ANode *nextarc; // 指向下一条边的指针
	int weight;			   // 该边的相关信息，如权值（用整型表示）
} ArcNode;				   // 边节点类型

typedef struct Vnode
{
	VertexType VexData; // 顶点数据
	int count;			// 存放顶点入度,仅仅用于拓扑排序
	ArcNode *firstarc;	// 指向第一条边
} VertexNode;			// 邻接表头节点类型

typedef struct
{
	VertexNode adjlist[MAXVEXNUM]; // 邻接表头节点数组
	int n, e;					   // 图中顶点数n和边数e
} AdjGraph;						   // 完整的图邻接表类型

void ShowMenu()
{
	cout << "***********************************************" << endl;
	cout << "       武汉东湖学院校园导游信息系统主菜单   " << endl;
	cout << "***********************************************" << endl;
	cout << " 	  1  景点地图整体管理 " << endl;
	cout << "     2  校园景点数据管理          " << endl;
	cout << "     3  景点交通数据管理          " << endl;
	cout << "     4  校园景点信息查询             " << endl;
	cout << "     5  游览线路查询规划          " << endl;
	cout << "     6  景点最短路径查询             " << endl;
	cout << "     7  管道系统最优布设              " << endl;
	cout << "     0  退出校园导游系统              " << endl;
	cout << "***********************************************" << endl;
	cout << "          请选择(0~7): " << endl;
}

// 2 校园景点数据管理

// 显示“校园景点数据管理”菜单界面
void ManaVertexData(MatrixGraph &g)
{
	cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
	cout << "校园景点地图整体数据管理        " << endl;
	cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
	cout << "      1 初始化景点地图数据 " << endl;
	cout << "      2 保存景点地图数据 " << endl;
	cout << "      3 读取景点地图数据 " << endl;
	cout << "		0  返回主菜单 " << endl;
	cout << "&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&" << endl;
}

// 输入一个景点数据
void InOneSpotData(MatrixGraph &g, int i)
{

	cout << "景点编号（限两个字符）" << endl;
	cin >> g.Vexs[i].SpotId;

	cout << "景点名称（先10个汉子）" << endl;
	cin >> g.Vexs[i].Name;

	cout << "景点简介（先128个汉子）" << endl;
	cin >> g.Vexs[i].Introduction;

	return;
}

// 输入多个景点信息
void InMultiSpotsData(MatrixGraph &g, int n)
{
	int i;
	int VexNum = g.VexNum;
	for (i = 0; i < n; i++)
	{
		cout << "请输入第" << VexNum + i + 1 << "个景点数据" << endl;
		inOneSpotData(g, VexNum + i);
	}
	g.VexNum += n;
	return;
}

// 删除一个景点消息
void InDeleteSpotsData(MatrixGraph &g)
{
}

// 修改景点信息
void InModifySpotsData(MatrixGraph &g)
{
}

// 3 校园景点交通数据管理
void ManaRoadData(MatrixGraph &g)
{
	int n, select;
	do
	{
		cout << " ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "               校园景点交通数据管理         " << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
		cout << "               1  增加景点交通数据           " << endl;
		cout << "              2  删除景点交通数据           " << endl;
		cout << "             3  修改景点交通数据           " << endl;
		cout << "             4  显示景点交通数据          " << endl;
		cout << "            0   返回主菜单                " << endl;
		cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	}
}

// 增加校园景点交通数据
void AddEdge(MatrixGraph &g)
{
	int p1 = -1;
	int p2 = -1;
	char from[20];
	char to[20];

	do
	{
		cout << "请输入该套校园道路的第一个景点名称" << endl;
		cin >> from;
		p1 = locateSpotPos(g, from); //
		if (p1 != -1)
		{
			break;
		}
		else
		{
			cout << "在校园地图中未找到景点名称为 " << from << " 的景点！" << endl;
		}
	} while (p1 == -1);

	do
	{
		cout << "请输入该套校园道路的第二个景点名称" << endl;
		cin >> in;
		p2 = LocateSpotPos(g, to);
		if (p2 != -1)
		{
			break;
		}
		else
		{
			cout << "在校园地图中未找到景点名称为 " << to << " 的景点！" << endl;
		}
	} while (p2 == -1);

	cout << "请输入从 " << from << " 到 " << to << " ， 该条校园景点道路的里程： " << endl;
	cin >> g.Edges[p1][p2];
	g.Edges[p2][p1] = g.Edges[p1][p2];
	g.EdgeNum++;
	cout << "从 " << from << " 到 " << to << " ， 景点道路的里程为 " << g.Edges[p1][p2] << "的道路添加成功！" << endl;
	return;
}

// 删除校园景点交通数据
void SeleteEdge(MatrixGraph &g)
{
}

// 修改景点交通数据
void ModifyEdge(MatrixGraph &g)
{
}

//  显示所有景点交通数据
void DispAllEdge(MatrixGraph g)
{
}

// 4 校园景点信息查询

// 显示一个景点信息
void ShowOneSpotData(MatrixGraph g, int i)
{
	cout << "景点编号：" << g.Vexs[i].SpotId << endl;
	cout << "景点名称：" << g.Vexs[i].Name << endl;
	cout << "景点简介：" << g.Vexs[i].Introduction << endl;
}

// 显示所有景点数据
void ShowAllSpotsData(MatrixGraph g)
{
	for (int i = 0; i < g.VexNum; i++)
	{
		cout << "武汉东湖学院第" << i + 1 << "个景点信息: " << endl;
		ShowOneSpotData(g, i);
	}
	return;
}

// 校园景点信息查询函数
void SearchSpotInfor(MatrixGraph g)
{

	LocateSpotPos(g, SpotName);
}

// 景点名称定位存储下标的功能
int locateSpotPos(MatrixGraph g, char SpotName[])
{
}

// 5  游览线路查询规划

// 景点交通数据管理函数
void VisitPathPlan(MatrixGraph &g)
{

	MatrixToAdjList(g, G);
	//	验证创建邻接表是否成功
	DispAdj(G);

	cout << "请输入游览线路起点景点名称" << endl;

	cout << "	@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ " << endl;
	cout << "		       校园景点游览线路查询规划       " << endl;
	cout << "		@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ " << endl;
	cout << "		       1  深度优先游览线路查询规划      " << endl;
	cout << "		       2  广度优先游览线路查询规划     " << endl;
	cout << "		       0   返回主菜单          " << endl;
	cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ " << endl;
}

// 图的邻接矩阵创建图的邻接表
bool MatrixToAdjList(MatrixGraph g, AdjGraph *&G)
{
}

// 显示邻接表
void DispAdj(AdjGraph *G)
{
}
// 深度优先遍历算法
void DFS(AdjGraph *G, int v)
{
}
// 广度优先遍历算法
void BFS(AdjGraph *G, int v)
{
}

// 销毁图的邻接表
void DestroyAdj(AdjGraph *&G)
{
}

// 6

// 景点最短路径查询函数
void ShortestPathQuery(MatrixGraph g)
{
}

// 迪杰斯特拉算法
void Dijkstra(MatrixGraph g, int v)
{
}

// 输出最短路径
void Disppath(MatrixGraph g, int dist[], int path[], int S[], int v)
{
}

// Floyd算法，完成校园景点最短路径查询的功能
void Floyd(MatrixGraph g)
{
}

// 7 ）管道系统最优布设
void PipelineSystemOptimal(MatrixGraph g)
{
}

void Prim(MatrixGraph g, int v)
{
}

void Kruskal(MatrixGraph g)
{
}

void BubbleSort(EdgeType R[], int n)
{
}

int main()
{
	MatrixGraph g;
	int choice = 0;
	do
	{
		ShowMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			//
			break;
		case 2:
			// 校园景点数据管理
			cout << "校园景点数据管理" << endl;
			cout << "请输入要输入景点数据的个数" << endl;
			int n;
			cin >> n;
			InMultiSpotsData(g, n);
			break;
		case 3:
			// 景点交通数据管理
			cout << "景点交通数据管理" << endl;

			break;
		case 4:
			// 校园景点信息查询
			cout << "校园景点信息查询" << endl;
			ShowAllSpotsData(g);
			break;
		case 0:
			cout << "退出系统" << endl;
			break;
		default:
			cout << "输入错误，请选择(0~7)" << endl;
			break;
		}
	} while (choice != 0);
	return 0;
}
