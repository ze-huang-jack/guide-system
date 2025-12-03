c++统一使用大驼峰命名	


详细设计
（1）数据结构体设计
	为了实现武汉东湖学院导游系统的管理，采用的主要数据结构为邻接矩阵、邻接表两种存储结构。
①符号常量的定义
#define INFINITY 32767			     //定义无穷大 
#define MAXVEXNUM 10	             //最大顶点个数
②以下定义图的邻接矩阵类型
typedef struct
{	
    char SpotId[2];				//景点编号
    char Name[20];               //景点名称
    char Introduction[256];         //景点简介 
} VertexType;					    //景点类型
typedef struct
{	
    int u;           //边的起始顶点 
    int v;           //边的终止顶点 
	int  Weight;                      //边的权重 
} EdgeType;                         	//边的类型
typedef struct
{	
    int VexNum,EdgeNum;	                 //顶点数，边数
    VertexType Vexs[MAXVEXNUM];	    	//存放顶点信息
	int Edges[MAXVEXNUM][MAXVEXNUM];	//邻接矩阵数组	
} MatrixGraph;					       //完整的图邻接矩阵类型

③以下定义邻接表类型
typedef struct ANode
{	int adjvex;					//该边的邻接点编号
	struct ANode *nextarc;		//指向下一条边的指针
	int weight;					//该边的相关信息，如权值（用整型表示）
} ArcNode;						//边节点类型
typedef struct Vnode
{	VertexType VexData;			//顶点数据 
	int count;					//存放顶点入度,仅仅用于拓扑排序
	ArcNode *firstarc;			//指向第一条边
} VertexNode;	  			//邻接表头节点类型
typedef struct 
{	VertexNode adjlist[MAXVEXNUM];		//邻接表头节点数组
	int n,e;				    	      //图中顶点数n和边数e
} AdjGraph;					    	//完整的图邻接表类型

（2）系统界面设计
①主界面设计
	***********************************************
	       武汉东湖学院校园导游信息系统主菜单      
	***********************************************
         1  景点地图整体管理             
	     2  校园景点数据管理             
	     3  景点交通数据管理             
	     4  校园景点信息查询             
         5  游览线路查询规划             
	     6  景点最短路径查询             
	     7  管道系统最优布设             
	     0  退出校园导游系统             
	***********************************************
	              请选择(0~7):
②景点地图整体管理界面设计
&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
校园景点地图整体数据管理        
&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
                       1 初始化景点地图数据 
	                   2 保存景点地图数据 
    	               3 读取景点地图数据 
0  返回主菜单 
&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
③校园景点数据管理界面设计
		============================================
		               校园景点数据管理            
		============================================
		               1  增加景点数据              
		               2  删除景点数据              
		               3  修改景点数据             
		               4  显示景点数据             
		               0   返回主菜单             
		============================================
④景点交通数据管理界面设计
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		               校园景点交通数据管理         
		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		               1  增加景点交通数据           
		               2  删除景点交通数据           
		               3  修改景点交通数据           
		               4  显示景点交通数据          
		               0   返回主菜单                
		~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
⑤校园景点信息查询
⑥游览线路查询规划界面设计
		@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		              校园景点游览线路查询规划       
		@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
		           1  深度优先游览线路查询规划     
		           2  广度优先游览线路查询规划    
		                0   返回主菜单         
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
⑦景点最短路径查询界面设计
		^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		              校园景点景点最短路径查询   
		^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
		            1  迪杰斯特拉(Dijkstra)算法    
		            2  弗 洛 伊 德 (Floyd) 算法   
		            0      返回主菜单            
		^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
管道系统最优布设界面设计
		#############################################
		                 校园管道系统最优布设       
		#############################################
		            1  普  里  姆(  Prim )算法       
		            2  克鲁斯卡尔(Kruskal)算法      
		            0   返回主菜单                 
		#############################################


函数及调用关系
主程序main()函数，在其中定义MatrixGraph 类型变量g，调用void ShowMainMenu()函数，显示武汉东湖学院导游系统程序主菜单函数，用户选择程序主菜单编号，调用相应的函数实现对应功能；
（1）用户选择程序主菜单编号1，主程序调用景点地图整体管理函数，
void ManaMapData(MatrixGraph &g)，通过显示“校园景点地图整体数据管理”菜单界面，实现景点地图整体管理功能。在这个菜单界面中，①调用void InitSpotsData(MatrixGraph &g) 函数，完成初始化学校景点数据，调用void SaveToMapFile(MatrixGraph g)函数，保存景点地图数据到文件“CampusSpotsData.dat”，调用void LoadFromMapFile(MatrixGraph &g) 函数从文件“CampusSpotsData.dat”中读取景点地图数据。
（2）用户选择程序主菜单编号2，主程序调用校园景点数据管理函数，
void ManaVertexData(MatrixGraph &g)，通过显示“校园景点数据管理”菜单界面，实现校园景点数据管理功能。在这个菜单界面中，①调用void InMultSpotsData(MatrixGraph &g,int n)函数，完成输入多个景点信息功能，其中，该函数调用void InOneSpotsData(MatrixGraph &g,int i)，输入一个景点信息，调用void InDeleteSpotsData(MatrixGraph &g) 函数，删除一个景点信息，调用void InModifySpotsData(MatrixGraph &g) 函数，修改景点信息，④调用void ShowAllSpotsData(MatrixGraph g)函数显示全部景点信息。
（3）用户选择程序主菜单编号3，主程序调用景点交通数据管理函数，
void ManaRoadData(MatrixGraph &g)，通过显示“校园景点交通数据管理”菜单界面，实现校园景点交通数据管理功能。在这个菜单界面中，
①调用void AddEdge(MatrixGraph &g)函数，增加一个景点交通数据，其中该函数调用int LocateSpotPos(MatrixGraph g , char SpotName[])函数，完成按景点名称定位存储下标的功能；
调用void DeleteEdge(MatrixGraph &g)函数，删除一个景点交通数据，其中该函数调用int LocateSpotPos(MatrixGraph g , char SpotName[])函数，完成按景点名称定位存储下标的功能；
调用void ModifyEdge(MatrixGraph &g)函数，修改景点交通数据，其中该函数调用int LocateSpotPos(MatrixGraph g , char SpotName[])函数，完成按景点名称定位存储下标的功能；
④调用void DispAllEdge(MatrixGraph g) 函数，显示所有景点交通数据。
（4）用户选择程序主菜单编号4，主程序调用校园景点信息查询函数，
void SearchSpotInfor(MatrixGraph g)，完成游览线路查询，其中该函数调用int LocateSpotPos(MatrixGraph g , char SpotName[])函数，按景点名称定位存储下标，调用void ShowOneSpotsData(MatrixGraph g,int i)函数显示一个景点的信息。
（5）用户选择程序主菜单编号5，主程序调用景点交通数据管理函数，
void VisitPathPlan(MatrixGraph &g)，该函数首先调用bool MatrixToAdjList(MatrixGraph g, AdjGraph *&G) 函数，通过图的邻接矩阵创建图的邻接表，并调用void DispAdj(AdjGraph *G)函数显示邻接表，以验证创建邻接表是否成功；在提示“请输入游览线路起点景点名称”后，调用int LocateSpotPos(MatrixGraph g , char SpotName[])函数，按景点名称定位存储下标，判断起点景点正确的前提下，通过显示“游览线路查询规划”菜单界面，实现校园景点游览线路查询规划功能，在这个菜单界面中，
①调用void DFS(AdjGraph *G,int v) 函数	，按照深度优先遍历算法，完成校园景点游览线路查询规划的功能；
调用void BFS(AdjGraph *G,int v)函数，按照广度优先遍历算法，完成校园景点游览线路查询规划的功能；
 调用void DestroyAdj(AdjGraph *&G)函数，在销毁图的邻接表后返回主菜单。
（6）用户选择程序主菜单编号6，主程序调用景点最短路径查询函数，
void ShortestPathQuery(MatrixGraph g)，通过显示“景点最短路径查询”菜单界面，实现校园景点游览线路查询规划功能，在这个菜单界面中， 
①调用void Dijkstra(MatrixGraph g, int v) 函数，按照迪杰斯特拉算法，在“请输入游览线路起点景点名称：”后，调用int LocateSpotPos(MatrixGraph g , char SpotName[])函数，按景点名称定位存储下标，判断起点景点正确的前提下，完成校园景点最短路径查询的功能，其最后该函数调用void Disppath(MatrixGraph g , int dist[], int path[], int S[] , int v) 函数输出最短路径；
调用void Floyd(MatrixGraph g) 函数，按照Floyd算法，完成校园景点最短路径查询的功能，其间该函数调用void Dispath(MatrixGraph g, int A[][MAXVEXNUM], int path[][MAXVEXNUM])函数输出最短路径；
（7）用户选择程序主菜单编号7，主程序调用void PipelineSystemOptimal(MatrixGraph g) 函数，通过显示“管道系统最优布设”菜单界面，实现校园景点管道系统最优布设功能，在这个菜单界面中， 
①调用void Prim(MatrixGraph g ,int v) 函数，按照求顶点v出发的最小生成树Prim算法，在“请输入管道系统最优布设起点景点名称：”后，调用int LocateSpotPos(MatrixGraph g , char SpotName[])函数，按景点名称定位存储下标，判断起点景点正确的前提下，完成校园景点管道系统最优布设的功能；
调用void Kruskal(MatrixGraph g) 函数，按照求最小生成树的Kruskal算法，完成校园景点管道系统最优布设的功能，其间该函数调用冒泡排序函数void BubbleSort(EdgeType R[], int n) ，按边的权重进行了升序排序；
（0）用户选择程序菜单编号0，主程序退出管理系统。