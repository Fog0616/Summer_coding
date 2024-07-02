#include<cstdio>
#include<vector>
#include<algorithm> 
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<string>
#include<ctype.h>
#define min(a,b) (a < b ? a : b)
const int DIR_X[8] = {-1,-1,0,1,1,1,0,-1};//ICE_BARRAGE 操作时的 方向改变量 
const int DIR_Y[8] = {0,-1,-1,-1,0,1,1,1};
const int EXX[6] = {0,0,1,-1,0,0};//立体空间内 相邻的冰砖 位置改变量 
const int EXY[6] = {0,0,0,0,1,-1};
const int EXZ[6] = {-1,1,0,0,0,0};
//=============================================================
struct alternative_position//门的候选位置 
{
	int x, y, z, h, wall;//位置信息, 
	int corner, corner_pos; //可看到的柱子残缺数
	int mid1, mid2;//此面墙 中间位置的坐标 
};
int N,HM,HR,HC,HX,HY,M;//输入的各常量 
int inventory;//库存冰砖数 
bool ice_block[17][17][30];//三维空间内某点 是否有冰砖存在 
int ground_freeze[17][17];//地面冰冻度 ,当地面有冰砖时为-1 
bool vis[17][17][30];//在dfs求 联通块时使用 
int max_high;//墙壁最高高度 
int doorx, doory, doorz, door_high, door_dis;
int corner_x[20], corner_y[20];
//=========子函数列表:==========================================
inline int read()
{
    int s=1, w=0; char ch=getchar();
    for(; !isdigit(ch);ch=getchar()) if(ch=='-') s =-1;
    for(; isdigit(ch);ch=getchar()) w = w*10+ch-'0';
    return s*w;
}
int abs(int x) {return x > 0? x : -x; }
bool cmp(alternative_position fir, alternative_position sec)
{
	if(fir.corner - fir.h == sec.corner - sec.h)//第一优先级, 消耗冰砖数 升序排序 
	{
	  if(fir.h == sec.h)//第二优先级 门的大小 降序排序 
	  {
	    int minfir = min(abs(fir.wall - fir.mid1), abs(fir.wall - fir.mid2));
		int minsec = min(abs(sec.wall - sec.mid1), abs(sec.wall - sec.mid2));
		return minfir < minsec;	//第三优先级, 与墙中央位置的距离 升序排序 
	  }
	  return fir.h > sec.h;
	}
	return fir.corner - fir.h < sec.corner - sec.h;
}
void ICE_BARRAGE();//操作1,释放弹幕 
void MAKE_ICE_BLOCK();//操作2,收集冰砖
 
void PUT_ICE_BLOCK();//操作3,放置冰砖 
bool JUDGE_PUT(int R,int C,int H);//判断 某位置 是否可以放置冰砖

int DFS1(int R,int C,int H,int FR,int FC,int FH);//dfs 判断某联通块是否悬空 
int DFS2(int R,int C,int H,int FR,int FC,int FH);//dfs 将某联通块 删除 
void REMOVE_ICE_BLOCK();//操作4,移除冰砖 

void MAKE_ROOF(); //操作5, 建造房顶, 移除多余,修补残缺,检查房屋 
int find_max_high();//寻找 墙壁最高处 
void remove_excess(int&,int&);

bool judge_outside(int,int,int);//判断某冰砖 是否位于 房屋内/外 
bool judge_inside(int,int,int);

bool fill_high_wall(int);//填补 高度>2的墙壁 
int judge_corner(int,int);//判断 一个位置否开在 墙角,并判断 开在哪个墙角 
void corner_could_see(int,int,int,int,int&,int&);//计算一个位置 能看到的墙角的残缺数 
bool find_door();//在 高度<2的位置 找门 ,并填补非门区域 
void check()//调试使用, 输出地图 , 以检查合法性 
{
	printf("%d \n",inventory); 
	for(int x=0; x<N; putchar('\n'),x++) 
	  for(int y=0; y<N; y++)
	  {
	  	long long sum=0;//使用 状压思想 , 对每一个二维的 坐标上的冰砖进行状压 
	    for(int z=0; z<=HM; z++) sum+= (ice_block[x][y][z]) * (1<<z);
	    printf("%lld ",sum);
	  }
	printf("\n\n\n");
}
//=============================================================
signed main()//sb main函数 
{
//	freopen("1.in","r",stdin);
//	freopen("koishi.txt","w",stdout);
	N=read(), HM=read(), HR=read(), HC=read(), HX=read(), HY=read(), M=read();
	corner_x[1] = corner_x[2] = HR, corner_x[4] = corner_x[8] = HR + HX - 1;//获得各墙角位置 
	corner_y[2] = corner_y[8] = HC + HY - 1, corner_y[1] = corner_y[4] = HC;
	while(M --)
	{
	  std::string order;
	  std::cin >> order;
	  if(order == "ICE_BARRAGE") ICE_BARRAGE();
	  if(order == "MAKE_ICE_BLOCK") MAKE_ICE_BLOCK();
	  if(order == "PUT_ICE_BLOCK") PUT_ICE_BLOCK();
	  if(order == "REMOVE_ICE_BLOCK") REMOVE_ICE_BLOCK();
	  if(order == "MAKE_ROOF") MAKE_ROOF(); 
	}
}
//=============================================================
void ICE_BARRAGE()
{
	int R=read(), C=read(), D=read(), S=read();
	int freeze_num = 0, pass_num = 0;//冰冻度改变的格子数 和 经过的格子数(距离 
	
	for(int x = R, y = C; ;x += DIR_X[D], y += DIR_Y[D])//枚举射线经过的格子 
	{
	  if(x < 0 || x >= N || y < 0 || y >= N || ground_freeze[x][y] == -1) break;//直线不可延伸
	  if(ground_freeze[x][y] < 4) ground_freeze[x][y]++ , freeze_num ++;//更新 变量 
	  pass_num ++;
	  if(pass_num > S) break;//直线不可延伸 
	}
	printf("CIRNO FREEZED %d BLOCK(S)\n",freeze_num);
}
void MAKE_ICE_BLOCK()
{
	int collect_num = 0;//收集 的冰砖数 
	for(int x = 0; x < N; x ++)
	  for(int y = 0; y < N; y ++)
	    if(ground_freeze[x][y] == 4)//可以进行收集 
	      inventory ++, collect_num ++, //加入库存 
		  ground_freeze[x][y] = 0;//冰冻度清零 
	printf("CIRNO MADE %d ICE BLOCK(S),NOW SHE HAS %d ICE BLOCK(S)\n",collect_num,inventory);
}
bool JUDGE_PUT(int R,int C,int H)//判断 某位置 是否可以放置冰砖 
{
	if(ice_block[R][C][H]) return 1;//此位置已被占用 
	if(H == 0) return 0;//冰砖与地面接触 
	for(int i = 0; i < 6; i ++) //枚举立体空间内相邻的 位置 
	  if(R + EXX[i] >= 0 && C + EXY[i] >= 0 && H + EXZ[i] >= 0)
	    if(R + EXX[i] < N && C + EXY[i] < N && H + EXZ[i] < HM)
		  if(ice_block[R + EXX[i]][C + EXY[i]][H + EXZ[i]]) //有相邻冰砖 
		    return 0; //放置位置合法 
	return 1;//冰砖悬空 
}
void PUT_ICE_BLOCK() 
{
	int R=read(),C=read(),H=read();
	if(! inventory) {printf("CIRNO HAS NO ICE_BLOCK\n"); return ;}//不合法情况 
	if(JUDGE_PUT(R,C,H)) {printf("BAKA CIRNO,CAN'T PUT HERE\n"); return ;}
	
	ice_block[R][C][H] = 1,inventory --;//放置冰砖 
	if(H == 0) ground_freeze[R][C] = -1;//与地面接触 ,更改地面冰冻值 
	if(R < HR || R > HR + HX - 1 || C < HC || C > HC + HY - 1) printf("CIRNO MISSED THE PLACE\n");//按照放置位置 输出 
	else if(HR + 1 <= R && R <= HR + HX - 2 && HC + 1 <= C && C <= HC + HY - 2) printf("CIRNO PUT AN ICE_BLOCK INSIDE THE HOUSE\n");
	else printf("CIRNO SUCCESSFULLY PUT AN ICE_BLOCK,NOW SHE HAS %d ICE_BLOCK(S)\n",inventory);
//	check();
}
int DFS1(int R,int C,int H,int FR,int FC,int FH)//dfs 判断某联通块是否悬空 
{
	vis[R][C][H] = 1;//访问过,打标记 
	if(H == 0) return 1;//此冰砖 与地面接触 , 说明此连通块合法 
	for(int i = 0; i < 6; i ++)//枚举相邻的 冰砖 
	  if(R + EXX[i] >= 0 && R + EXX[i] <N && C + EXY[i] >= 0) //位置合法 
	    if(C + EXY[i] < N && H + EXZ[i] >= 0 && H + EXZ[i] <=HM)
	      if(R + EXX[i] != FR || C + EXY[i] != FC || H + EXZ[i] != FH)//不与 上一块冰砖位置相同 
	  	    if(ice_block[R + EXX[i]][C + EXY[i]][H + EXZ[i]])//有冰砖 
	  	      if(!vis[R + EXX[i]][C + EXY[i]][H + EXZ[i]])//转移 
	  	        if(DFS1(R + EXX[i],C + EXY[i],H + EXZ[i],R,C,H)) return 1;//连通块 与地面接触 
	return 0;//悬空 
}
int DFS2(int R,int C,int H,int FR,int FC,int FH)//dfs 将某联通块 删除 
{
	int ret = 0;//计算 删除的个数 
	for(int i = 0; i < 6; i ++)
	  if(R + EXX[i] >= 0 && R + EXX[i] < N && C + EXY[i] >= 0) //枚举 合法的相邻冰砖 
	    if(C + EXY[i] < N && H + EXZ[i] >= 0 && H + EXZ[i] <= HM)
	      if(R + EXX[i] != FR || C + EXY[i] != FC || H + EXZ[i] != FH)
	  	    if(ice_block[R + EXX[i]][C + EXY[i]][H + EXZ[i]])
	  	      ret += DFS2(R + EXX[i],C + EXY[i],H + EXZ[i],R,C,H);//dfs深入 
	return ice_block[R][C][H] = 0, ret + 1;//更新冰砖存在情况,更新删除个数 
}
void REMOVE_ICE_BLOCK()
{
	int R = read(), C = read(), H = read(); 
	if(!ice_block[R][C][H]) {printf("BAKA CIRNO,THERE IS NO ICE_BLOCK\n"); return ;}//不合法情况
	
	ice_block[R][C][H] = 0, inventory ++;//移除冰砖, 并 加入库存 
	if(H == 0) ground_freeze[R][C] = 0;//将地面 冰砖移走,冰冻度置零 
	
	int sum_break = 0;//碎掉冰砖个数 
	for(int i = 0; i < 6; i ++)//枚举被删除位置 相邻的 存在的 冰砖 
	  if(R + EXX[i] >= 0 && R + EXX[i] < N && C + EXY[i] >= 0) 
	    if(C + EXY[i] < N && H + EXZ[i] >= 0 && H + EXZ[i] <= HM)
	      if(ice_block[R + EXX[i]][C + EXY[i]][H + EXZ[i]]) 
	  	  {
	  	  	memset(vis,0,sizeof(vis));//dfs判断 相邻冰砖 连通块是否与 地面接触 
	  	    if(!DFS1(R + EXX[i],C + EXY[i],H + EXZ[i],-1,-1,-1))
	  	      sum_break += DFS2(R + EXX[i],C + EXY[i],H + EXZ[i],-1,-1,-1);	
		  }
	
	printf("CIRNO REMOVED AN ICE_BLOCK");//按情况输出 
	if(sum_break) printf(",AND %d BLOCK(S) ARE BROKEN",sum_break);
	printf("\n");
}
void MAKE_ROOF()
{
	int remove = 0, filled = 0, corner_filled = 0;//判断 是否移除多余 , 填补残缺 , 墙角残缺 
	max_high = find_max_high() + 1;//找到 墙壁最高高度 
	//搭建 房顶:
	{
		for(int x = HR; x < HR + HX; x ++)//枚举 最高高度处 所有位置 
		  for(int y = HC; y < HC + HY; y ++)
		  {
		  	inventory -= (!ice_block[x][y][max_high]);//更新
		  	ice_block[x][y][max_high] = 1;
		  }
		if(inventory < 0) {printf("SORRY CIRNO,NOT ENOUGH ICE_BLOCK(S) TO MAKE ROOF\n"); return ;}//不合法情况 
		if(max_high < 2 || (HX - 2)*(HY - 2)*max_high < 2) {printf("SORRY CIRNO,HOUSE IS TOO SMALL\n"); return ;}
	}
	//移除 多余冰砖:
	{
		int inside = 0, outside = 0;
		remove_excess(outside,inside);// 移除多余 
		remove = (inside || outside);//判断是否 移除 
		
		printf("%d ICE_BLOCK(S) INSIDE THE HOUSE NEED TO BE REMOVED\n",inside);//按情况输出 
		printf("%d ICE_BLOCK(S) OUTSIDE THE HOUSE NEED TO BE REMOVED\n",outside);
		if(!DFS1(HR + 1,HC + 1,max_high,-1,-1,-1)) {printf("SORRY CIRNO,HOUSE IS BROKEN WHEN REMOVING BLOCKS\n"); return ;}//判断 屋顶连通块是否悬空 
	}
	//填补 墙壁残缺:
	{
		filled = fill_high_wall(max_high);//填补 高度>=2处 
		filled += find_door();//在高度 <2处寻找门,并填补 
		if(inventory < 0) {printf("SORRY CIRNO,NOT ENOUGH ICE_BLOCKS TO FIX THE WALL\n"); return ;}//不合法情况 
	}
	//检查小屋: 
	{
		printf("GOOD JOB CIRNO,SUCCESSFULLY BUILT THE HOUSE\n");
		if(door_high == 2) printf("DOOR IS OK\n");//有 高为2的门 
		else inventory += (2 - door_high), printf("HOUSE HAS NO DOOR\n");//移除冰块建门,库存增加 
		
		if(filled) printf("WALL NEED TO BE FIXED\n");//填补过残缺 
		else printf("WALL IS OK\n");
		
		for(int z = 0; z <= max_high; z ++) //判断 墙角的完整性 
		  for(int x = HR; x < HR + HX; x += HX - 1)
		    for(int y = HC; y < HC + HY; y += HY - 1)
		      if(!ice_block[x][y][z]) corner_filled = 1, inventory --;
		if(corner_filled) printf("CORNER NEED TO BE FIXED\n");
		else printf("CORNER IS OK\n");
		
		printf("CIRNO FINALLY HAS %d ICE_BLOCK(S)\n",inventory >= 0?inventory:0);//最后的冰砖数 (若修复过墙角,会导致 库存<=0,此时还会再制造冰砖并补齐空缺 
		if((!remove) && (!filled) && door_high == 2 && (!corner_filled) && (!door_dis)) //不愧是琪露诺! 轻易就做到了我们做不到的事
		  printf("CIRNO IS PERFECT!");
	}
}
//MAKE_ROOF 子操作 
int find_max_high()//寻找 墙壁最高处 
{ 
	for(int i = HM; i >= 0; i --)//自上往下枚举 高度 
	{
	  for(int j = HC; j < HC + HY; j ++)//枚举每一面墙 
	    if(ice_block[HR][j][i]) return i;
	  for(int j = HC; j < HC + HY; j ++)
	    if(ice_block[HR + HX - 1][j][i]) return i;
	  for(int j = HR; j < HR + HX; j ++)
	    if(ice_block[j][HC][i]) return i;
	  for(int j = HR; j < HR + HX; j ++)
	    if(ice_block[j][HC + HY - 1][i]) return i;
	}
	return -1; 
}
bool judge_outside(int x,int y,int z)//判断 某位置 是否在房外 
{
	if(HR <= x && x < HR + HX)
	  if(HC <= y && y < HC + HY)
	    if(z <= max_high) return 0;
	return 1;
}
bool judge_inside(int x,int y,int z)//判断 某位置 是否在房内 
{
	if(HR < x && x < HR + HX - 1)
	  if(HC < y && y < HC + HY - 1)
	    if(z < max_high) return 1;
	return 0;
}
void remove_excess(int &outside,int &inside)//移除 多余方块 
{
	for(int x = 0; x < N; x ++)//枚举 立体空间内 每一个位置 
	  for(int y = 0; y < N; y ++)
		for(int z = 0; z <= HM; z ++)
		  if(ice_block[x][y][z])//存在冰块 
		  {
		    if(judge_outside(x,y,z)) inventory ++, outside ++, ice_block[x][y][z] = 0;//在屋外 
		    if(judge_inside(x,y,z)) inventory ++, inside ++, ice_block[x][y][z] = 0;//在屋内 
			if(!ice_block[x][y][z])//冰块被移除后 
			  for(int i = 0; i < 6; i ++)
	  			if(x + EXX[i] >= 0 && x + EXX[i] < N && y + EXY[i] >= 0) //枚举相邻合法位置的 的 存在的 冰砖 
	    		  if(y + EXY[i] < N && z + EXZ[i] >= 0 && z + EXZ[i] <= HM)
	      			if(ice_block[x + EXX[i]][y + EXY[i]][z + EXZ[i]])
					  if(!judge_outside(x + EXX[i],y + EXY[i],z + EXZ[i]) && (!judge_inside(x + EXX[i],y + EXY[i],z + EXZ[i])))//如果在 墙壁上 
						{
						  memset(vis,0,sizeof(vis));	
						  if(!DFS1(x + EXX[i],y + EXY[i],z + EXZ[i],-1,-1,-1)) //如果 移除此位置后 墙壁上的 冰砖会摔碎 
						    inventory ++, ice_block[x + EXX[i]][y + EXY[i]][z + EXZ[i]] = 0;//将其移除 ,加入库存 
						}
		  }
}
bool fill_high_wall(int max_high)//填补 高度 >= 2处的墙 
{
	bool filled = 0;
	for(int x = HR; x < HR + HX; x ++)//枚举每一个位置 
	  for(int y = HC; y < HC + HY; y ++)
		for(int z = 2; z <= max_high; z ++)
		  if(!judge_outside(x,y,z))//判断 在墙上 
			if(!judge_inside(x,y,z))
			  if(!ice_block[x][y][z]) 
		      {
		      	if(x == HR && y == HC) continue;//在墙角,则 跳过 
		  		if(x == HR && y == HC + HY - 1) continue;
		  		if(x == HR + HX - 1 && y == HC) continue;
		  		if(x == HR + HX - 1 && y== HC + HY - 1) continue;
		  		inventory --, filled = 1, ice_block[x][y][z] = 1;//填补 
			  }
	return filled;//返回 是否填补过 
}
int judge_corner(int x,int y)//判断位置 (x,y) 是否与墙角相邻
{
	int ret = 0; //表示 一门的候选位置相邻的墙角 的 状态 
	if(x == HR)//枚举并判断 ,  
	{
	  if(y == HC + 1) ret += 1;
	  else if(y == HC + HY - 2) ret += 2;
	}
	if(x == HR + 1)
	{
	  if(y == HC) ret += 1;
	  else if(y == HC + HY - 1) ret += 2;
	}
	if(x == HR + HX - 2)
	{
	  if(y == HC) ret += 4;
	  else if(y == HC + HY - 1) ret += 8;
	}
	if(x == HR + HX - 1)
	{
	  if(y == HC + 1) ret += 4;
	  else if(y == HC + HY - 2) ret += 8;
	}
	return ret;
}
void corner_could_see(int x,int y,int z,int h,int &corner,int &corner_pos)//计算一个位置(x,y,z) 能看到的墙角的残缺数 
{
	corner_pos = judge_corner(x, y);//判断 是否哪个墙角, 并获得 此位置相邻的墙角 的 状态  
	corner = 0;
	if(!corner_pos) return;//不与墙角相邻 
	for(int i = 0; i < 4; i ++)//枚举墙角 
	  if((1 << i )& corner_pos)
	  {
	    int x1 = corner_x[1 << i], y1 = corner_y[1 << i];//计算残缺 
	    corner += (!ice_block[x1][y1][z]) + (!ice_block[x1][y1][!z])*(h == 2);
	  }
} 
bool find_door()//在 高度<2的位置 找门 ,并填补非门区域
{
	std:: vector <alternative_position> pos;//门的候选位置 
	int incomplete = 0, filled_sum = 0, corner_filled = 0;//残缺数, 填补数, 墙角位置的填补数 
	int midX1 = (HX + 1) /2 + HR - 1, midX2 = (HX + 2) /2 + HR - 1;//两墙壁中间位置 
	int midY1 = (HY + 1) /2 + HC - 1, midY2 = (HY + 2) /2 + HC - 1;

	for(int x = HR + 1, corner, corner_pos; x < HR + HX - 1; x ++)//枚举 墙上位置 
	  for(int y = HC; y < HC + HY; y += HY - 1)
	  	if(!ice_block[x][y][0])//根据 残缺的存在情况 进行判断 ,并加入候选位置 
	  	{
	  	  int z = 0, h = 1 + (!ice_block[x][y][1]);  incomplete += h;
	  	  corner_could_see(x,y,z,h,corner,corner_pos);
	  	  pos.push_back((alternative_position) {x,y,0,h,x,corner,corner_pos,midX1,midX2});
		}
		else if(!ice_block[x][y][1])
		{
	  	  corner_could_see(x,y,1,1,corner,corner_pos);  incomplete += 1;
	  	  pos.push_back((alternative_position) {x,y,1,1,x,corner,corner_pos,midX1,midX2});
		}
		
	for(int y = HC + 1, corner, corner_pos; y < HC + HY - 1; y ++)//枚举 墙上位置 
	  for(int x = HR; x < HR + HX; x += HX - 1)
	  	if(!ice_block[x][y][0])//根据 残缺的存在情况 进行判断 ,并加入候选位置 
	  	{
	  	  int z = 0, h = 1 + (!ice_block[x][y][1]); incomplete += h;
	  	  corner_could_see(x,y,z,h,corner,corner_pos);
	  	  pos.push_back((alternative_position) {x,y,0,h,y,corner,corner_pos,midY1,midY2});
		}
		else if(!ice_block[x][y][1])
		{
		  corner_could_see(x,y,1,1,corner,corner_pos); incomplete += 1;
	  	  pos.push_back((alternative_position) {x,y,1,1,y,corner,corner_pos,midY1,midY2});
		}
	
	std::sort(pos.begin(), pos.end(), cmp);//排序估值 
	if(pos.size()) //若有候选位置 可以选择 ,选择 最优的 位置 
	{
	  filled_sum = incomplete - pos[0].h + pos[0].corner; 
	  doorx = pos[0].x, doory = pos[0].y, doorz =  pos[0].z, door_high =pos[0].h;
	  door_dis = min(abs(pos[0].wall - pos[0].mid1), abs(pos[0].wall - pos[0].mid2));
	}
	if(door_high == 1 && filled_sum < inventory) //已选择的残缺大小为1, 库存冰块足够选择更大的残缺 
	  for(int i = 1, size = pos.size(); i < size; i ++)//找到 最优的 高度为2的残缺 
	    if(pos[i].h == 2) 
	    {
	      filled_sum = incomplete - pos[i].h + pos[i].corner;
	  	  doorx = pos[i].x, doory = pos[i].y, doorz =  pos[i].z, door_high = pos[i].h;
	  	  door_dis = min(abs(pos[i].wall - pos[i].mid1), abs(pos[i].wall - pos[i].mid2));
	  	  break;
		}
	inventory -= filled_sum;//更新库存 
	
	for(int i = 0, size = pos.size(); i < size; i ++)//填补 非门空缺 
	  if(pos[i].x != doorx && pos[i].y != doory && pos[i].z != doorz)//空缺 不为门 
	  {
	  	int x = pos[i].x, y = pos[i].y, z = pos[i].z;
		if(pos[i].h == 2) ice_block[x][y][1] = 1;
		ice_block[x][y][z] = 1;
	  }
	  else if(pos[i].x == doorx && pos[i].y == doory && pos[i].z == doorz && pos[i].corner_pos)
	  {
	  	for(int j = 0; j < 4; j ++) //空缺为门 , 填补 可以看到的墙角空缺 
		  if((1 << j) & pos[i].corner_pos)//枚举墙角 
		  {
		  	int x = corner_x[1 << j], y = corner_y[1 << j];//计算答案 
	  		corner_filled += (!ice_block[x][y][doorz]);
			ice_block[x][y][doorz] = 1;
	  		if(door_high == 2) corner_filled +=(!ice_block[x][y][!doorz]), ice_block[x][y][!doorz] = 1;
		  }
	  }
	return filled_sum;
}
//copied，not coding by myself