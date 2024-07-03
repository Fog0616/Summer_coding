#include<bits/stdc++.h>

using namespace std;

char _getc() { //一个可以吞掉注释的getchar()
	char ch = getchar();
	if(ch == '#') while(ch != '\n' && ch != EOF) ch = getchar();
	return ch; 
}

struct arr {	//数组的储存结构
	int *val, start;	//需要有数组空间和起始地址
	arr(int s, int t): start(s) { val = new int[t - s + 5]; }
	void aset(int i, int v) { val[i - start] = v; }	//赋值
	int aget(int i) { return val[i - start]; }	//取值
};

map<std::string, int> inttable;	//储存整数变量
map<std::string, arr*> arrtable;	//储存数组变量

struct Initer {	//变量声明储存结构
	int type;	//变量类型（0为整数，1为数组）
	std::string name;	//变量名
	int begin, end;	//（数组专用）起始值与终止值
	Initer *nxt;	//下一条变量声明（我们使用链表结构储存一整串变量声明）
};

struct Expression {	//表达式储存结构
	int type;	//表达式类型（0为常数，1为整数变量，2为数组变量）
	int symbol;	//正负
	Expression *arre;	//（数组专用）数组下标的表达式
	std::string val;	//表达式的形态（常数为数字串，变量为变量名，常数不需要带符号，数组不需要带下标）
	Expression *nxt;	//下一条表达式（我们使用链表结构储存一整个表达式）
	
	int eget() {	//表达式取值
		int num = 0;
		if(type == 0) {	//如果是常数
			for(int i = 0; i < val.size(); ++i) num = num * 10 + val[i] - '0';	//获取数值
		} else if(type == 1) {	//如果是整数变量
			num = inttable[val];	//从内存中找到变量的值
		} else if(type == 2) {	//如果是数组
			num = arrtable[val]->aget(arre->eget());	//从内存中找数组并根据下标表达式计算出下标并访问
		} else {	//其他情况
			throw("RE");	//是不存在的如果真的存在说明程序出BUG了
		}
		num *= symbol;	//带上符号
		if(nxt != NULL) return num + nxt->eget();	//如果后面还有表达式，计算后面的表达式并加上
		return num;
	}
};

struct Instruction {	//指令的储存结构
	int type;	//指令类型（0为var，1为set，2为yosoro，3为ihu，4为hor，5为while）
	Initer *init;	//（var专用）初始化变量列表
	Expression *exp1, *exp2, *exp3;	//exp1：set被赋值项，yosoro被输出表达式，ihu左值，hor循环变量，while左值
									//exp2：ihu右值，hor结束值，while右值
									//exp3：set源赋值表达式，hor初始值
	int judgetype;	//ihu、while、hor专用，比较类型（0为lt，1为gt，2为le，3为ge，4为eq，5为neq），hor需要始终设置为2（le）
	Instruction *subins;	//ihu、hor、while专用，子指令块
	Instruction *nxt;	//下一条指令（我们用链表结构储存一整串指令）
};

void Run(Instruction *ins);

void _vars(Instruction *ins)	//处理var语句
{
	for(Initer *i = ins->init; i != NULL; i = i->nxt) //遍历每一条变量声明
	{
		if(i->type == 0) inttable[i->name] = 0;	//如果是整数，直接在整数内存中设置为0
		else if(i->type == 1) {	//如果是数组
			arrtable[i->name] = new arr(i->begin, i->end);	//在数组内存中插入一个新的数组
		} else {	//其他情况
			throw("RE: Something wrong with the type of a Initer.");	//不可能有其他情况如果有就说明程序出BUG了
		}
	}
}

void _set(Instruction *ins)	//处理set语句
{
	Expression *exp1 = ins->exp1, *exp3 = ins->exp3;	//为了方便操作把链表换个名字（因为是指针所以指向的结构是不会变的）
	if(exp1->type == 1) {	//如果被赋值项是整数变量
		inttable[exp1->val] = exp3->eget();	//直接在内存中改变值
	} else if(exp1->type == 2) {	//如果被赋值项是数组
		arrtable[exp1->val]->aset(exp1->arre->eget(), exp3->eget());	//获取数组下标并根据下标设置数组的值
	} else {	//其他情况
		throw("CE: exp1 is not a variable");	//不可能有其他情况，如果有可能是输入时表达式就不正确
	}
}

void _yosoro(Instruction *ins)	//处理yosoro语句
{
	printf("%d ", ins->exp1->eget());	//计算表达式的值并输出，后跟一个空格
}

bool _ihu(Instruction *ins)	//处理ihu语句
{
	Expression *exp1 = ins->exp1, *exp2 = ins->exp2;	//为了方便操作把链表换个名字（因为是指针所以指向的结构是不会变的）
	switch(ins->judgetype)	//对于每一种判断，如果不符合就返回false
	{
	case 0:	//lt
		if(exp1->eget() >= exp2->eget()) return false;
		break;
	case 1:	//gt
		if(exp1->eget() <= exp2->eget()) return false;
		break;
	case 2:	//le
		if(exp1->eget() > exp2->eget()) return false;
		break;
	case 3:	//ge
		if(exp1->eget() < exp2->eget()) return false;
		break;
	case 4:	//eq
		if(exp1->eget() != exp2->eget()) return false;
		break;
	case 5: //neq
		if(exp1->eget() == exp2->eget()) return false;
		break;
	default:
		throw("RE: Something wrong with the type of a judge");
	}
	Run(ins->subins);	//如果符合结果就执行子指令块
	return true;	//返回true
}

void _hor(Instruction *ins)	//处理hor语句
{
	Expression *exp1 = ins->exp1, *exp2 = ins->exp2, *exp3 = ins->exp3;	//为了方便操作把链表换个名字（因为是指针所以指向的结构是不会变的）
	_set(ins);	//把exp3赋值给exp1
	while(_ihu(ins)) {	//利用ihu语句反复执行
		if(exp1->type == 1) {	//+1操作，循环变量如果是整数变量
			++inttable[exp1->val];	//直接加
		} else if(exp1->type == 2) {	//如果是数组
			int i = exp1->arre->eget();	//获得下标
			arrtable[exp1->val]->aset(i, arrtable[exp1->val]->aget(i) + 1); //加上去
		} else {	//如果其他类型
			throw("CE: exp1 is not a variable");	//不可能
		}
	}
}

void _while(Instruction *ins)	//处理while语句
{
	while(_ihu(ins));	//利用ihu反复执行
}

void Run(Instruction *ins)	//处理指令
{
	while(ins != NULL) //一条一条执行下去下去
	{
		switch(ins->type)	//分清指令类型
		{
		case 0:
			_vars(ins);
			break;
		case 1:
			_set(ins);
			break;
		case 2:
			_yosoro(ins);
			break;
		case 3:
			_ihu(ins);
			break;
		case 4:
			_hor(ins);
			break;
		case 5:
			_while(ins);
			break;
		default:
			throw("RE: Something wrong with the type of a instruction.");
		}
		ins = ins->nxt;	//下一条
	}
}

Instruction *Main;	//主指令串
char c;	//用来保存当前字符

void ReadInstruction(char endc, Instruction *ins);

void readiniter(Initer *init)	//读取变量声明
{
	while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();	//吞掉空字符
	if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) throw("CE: Unexpected character. "); //非字母不可以作变量名
	std::string name;
	while((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {	//读取变量名
		name.push_back(c);
		c = _getc();
	}
	init->name = name;
	while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc(); //允许变量名和冒号之间有空字符
	if(c != ':') throw("CE");	//非法字符
	c = _getc();
	while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();	//允许冒号和类型之间有空字符
	name.clear();
	if(!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))) throw("CE: Unexpected character. TT"); //非字母不可以作类型名
	while((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
		name.push_back(c);
		c = _getc();
	}
	if(name == "int") {	//int
		init->type = 0;
	} else if(name == "array") {	//array
		init->type = 1;
		if(c != '[') throw("CE: Unexpected character. ");	//array后面紧跟的不是"["就不行（我规定的）
		name.clear();
		c = _getc();
		while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();	//允许方括号后面有空字符
		while((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {	//读取类型名
			name.push_back(c);
			c = _getc();
		}
		if(name != "int") throw("CE: Unknow type. ");	//不是int肯定不行
		while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();	//允许类型名后面有空字符
		if(c != ',') throw("CE: Unexpected character. ");	//不是"，"也不行
		c = _getc();
		while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();
		int num = 0;
		while(c >= '0' && c <= '9') {	//读取起始下标
			num = num * 10 + c - '0';
			c = _getc();
		}
		init->begin = num;
		if(c == '.') {	//".."必须与两个值紧凑的挨在一起（我规定的）
			c = _getc();
			if(c != '.') throw("CE: Unexpected character. ");
		} else throw("CE");
		c = _getc();
		num = 0;
		while(c >= '0' && c <= '9') { //读取终止下标
			num = num * 10 + c - '0';
			c = _getc();
		}
		init->end = num;
		c = _getc();
	} else throw("CE: Unknow type. ");
}

void readexpression(char endc, Expression *&expr)	//读取表达式，endc为表达式终止的标志
{
	expr = new Expression();
	while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc(); //先把前面的空字符吞了
	if(c == '-') {	//如果是"-"，那就是负的
		expr->symbol = -1; 
		c = _getc(); while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();	//因为读到了符号，所以主体还在后面
	}
	else if(c == '+') {	//如果是"+"，那就是正的
		expr->symbol = 1;
		c = _getc(); while(c == ' ' || c == '\n' || c == '\t' || c == '\r')	c = _getc();	//理由同上
	} else {
		expr->symbol = 1;	//没指明正负也是正的，只是不用继续往下读了
	}
	
	if(c >= '0' && c <= '9') {	//如果是常数
		expr->type = 0;
		std::string num;	//直接把数字读成字符串，解析扔给执行那边，读入这里就不管了
		while(c >= '0' && c <= '9') {
			num.push_back(c);
			c = _getc();
		}
		expr->val = num;
	} else if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {	//如果是变量
		std::string name;
		while((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {	//读完变量名
			name.push_back(c);
			c = _getc();
		}
		expr->val = name;
		if(c == '[') {	//如果是array
			expr->type = 2;
			c = _getc();
			readexpression(']', expr->arre);	//以"]"为终止标志读取数组下标表达式
		} else expr->type = 1;
	}
	while(c != endc && (c == ' ' || c == '\n' || c == '\t' || c == '\r')) c = _getc();	//一直吞空字符，直到读到结束标志或其他字符为止（这里结束标志也可能是四大空字符之一）
	if(c == '+' || c == '-') readexpression(endc, expr->nxt);	//如果是正负（加减）号就读下一个表达式
	else if(c == endc) c = _getc();	//终止符就再读一个字符走人
	else throw("CE: Unexpected character. ");	//不可能是别的字符，如果是就CE
}

int readjudge()
{
	while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();
	if(c == 'l') {	//读取比教的类型，不符合6个类型之一的CE掉
		c = _getc();
		if(c == 't') {
			c = _getc();
			return 0;	//lt
		} else if(c == 'e') {
			c = _getc();
			return 2;	//le
		} else throw("CE: Unexpected character. ");
	} else if(c == 'g') {
		c = _getc();
		if(c == 't') {
			c = _getc();
			return 1;	//gt
		} else if(c == 'e') {
			c = _getc();
			return 3;	//ge
		} else throw("CE: Unexpected character. ");
	} else if(c == 'e') {
		c = _getc();
		if(c == 'q') {
			c = _getc();
			return 4;	//eq
		} else throw("CE: Unexpected character. ");
	} else if(c == 'n') {
		c = _getc();
		if(c == 'e') {
			c = _getc();
			if(c == 'q') {
				c = _getc();
				return 5;	//neq
			} else throw("CE: Unexpected character. ");
		} else throw("CE: Unexpected character. ");
	} else throw("CE: Unexpected character. ");
	c = _getc();
}

void readvars(Instruction *ins)	//读取vars
{
	ins->init = new Initer();
	Initer *init = ins->init;
	while(c != '}') {
		readiniter(init);
		init->nxt = new Initer();
		init = init->nxt;
		while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc();
	}
	ins->type = 0;
	c = _getc();
}

void readset(Instruction *ins)	//读取set
{
	ins->type = 1;
	readexpression(',', ins->exp1);	//以逗号为结束标志读取exp1
	readexpression('\n', ins->exp3); //以换行为结束标志读取exp2
}

void readyosoro(Instruction *ins)	//读取yosoro
{
	ins->type = 2;
	readexpression('\n', ins->exp1);	//以换行为结束标志读取exp1
}

void readihu(Instruction *ins)	//读取ihu
{
	ins->type = 3;
	ins->judgetype = readjudge();	//读取比较类型
	c = _getc();
	readexpression(',', ins->exp1);	//以逗号为结束标志读取exp1
	readexpression('\n', ins->exp2);	//以换行为结束标志读取exp2
	ins->subins = new Instruction();
	ReadInstruction('}', ins->subins);	//以有括号为结束标志读取subins 
}

void readhor(Instruction *ins)	//读取hor
{
	ins->type = 4;
	ins->judgetype = 2;	//比较类型天然为le
	readexpression(',', ins->exp1);	//以=为结束标志读取循环变量
	readexpression(',', ins->exp3);	//以t为结束标志读取初值
	readexpression('\n', ins->exp2);	//以换行为结束标志读取终止值
	ins->subins = new Instruction();
	ReadInstruction('}', ins->subins);
}

void readwhile(Instruction *ins)	//读取while
{
	readihu(ins);	//因为内部是相同的直接很赖皮的用ihu读入
	ins->type = 5;	//然后把类型改过来就行了
}

void ReadInstruction(char endc, Instruction *ins)
{
	while(c != endc) 
	{
		while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc(); //读到不是空字符为止
		if(c == '{' || c == ':')	//指令
		{
			std::string opt;
			c = _getc();
			while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc(); //读到不是空字符为止
			while(c >= 'a' && c <= 'z') { //获取指令名称
				opt.push_back(c);
				c = _getc();
			}
			if(c != ' ' && c != '\t' && c != '\n' && c != '\r') throw("CE: Unexpected character. ");	//不是以空字符结尾的直接CE
			
			if(opt == "vars")
				readvars(ins);
			else if(opt == "set")
				readset(ins);
			else if(opt == "yosoro")
				readyosoro(ins);
			else if(opt == "ihu")
				readihu(ins);
			else if(opt == "hor")
				readhor(ins);
			else if(opt == "while")
				readwhile(ins);
			else	//未定义的指令
				throw("CE: Unknow Instruciton. ");
				
			ins->nxt = new Instruction();
			ins = ins->nxt;
			
			while(c == ' ' || c == '\n' || c == '\t' || c == '\r') c = _getc(); //读到不是空字符为止
		} else {	//非法字符
			throw("CE: Unexpected character. ");
		}
	}
	c = _getc();
}

int main()
{
	c = _getc();	//先读一个字符
	Main = new Instruction();
	try {
		ReadInstruction(EOF, Main);	//以EOF为结束标志读取Main
		Run(Main);
		printf("\n");
	} catch (const char* e) {
		cerr << e << endl;
	}
	return 0;
}