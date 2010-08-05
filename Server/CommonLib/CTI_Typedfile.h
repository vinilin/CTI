//CTI_Typedfile.h
// LFQ-定义 - 2010-03-18 内容：cti-base模块外发数据包结构；通道基础类；回调函数全局类型定义
#ifndef CTI_SYSTEM_NEWTYPE
#define CTI_SYSTEM_NEWTYPE
#include "stdafx.h"
#define MAX_DTMF_LEN 33
#define MAX_TEL_LEN 30
#define MAX_PATH_LEN 250
#define MAX_LINE_BUFF_LEN 4000
#define MAX_DBRESULT_LEN 1000
#define MAX_OBJ_LEN		512
#define MAX_SQL_LEN		1000
#define MAX_FIELD_LEN  20
#define MAX_DATA_SIZE  0x10000
#define MAX_ERROR_LEN  1000

enum TASK_CLASS{//总线任务类型
	T_INITBASE =	1,		// 主程序发送：语音基础模块初始化
	T_INITBASE_INFO,		//基础模块初始化完成+所有模块接收处理该任务
	T_INIT_COMP,			//模块初始化完成：所有模块回送总线报告异常
	//
	T_BASE_CALLIN,			//base模块+语音通道来电：送达cti-node
	T_BASE_LINECHANGE,		//base模块：语音通道状态事件变迁；送达cti-node；cti-ivr；cti-server；cti-conf
	T_BASE_OFFHOOK,			//base模块：语音通道拆线、挂机：送达cti-node；cti-ivr；
	//
	T_NODE_STEP_IVR,		//node模块+流程节点对象+送达ivr
	T_NODE_STEP_CONF,		//node模块+流程节点对象+送达会议模块
	T_NODE_STEP_SERVER,		//node模块+流程节点对象+送达cti-server
	T_NODE_STEP_DBRESULT,	//node模块+数据库访问对象+送达 数据库访问模块
	//
	T_IVR_CTRL,				//ivr模块：ivr对基础模块的控制指令
	T_IVR_NODE,				//ivr模块	ivr模块发送到ctinode的流程节点对象执行完成指令
	T_CONF_CTRL,			//会议模块：会议模块对base模块的控制命令
	T_SERVER_CTRL,			//服务器模块：服务器模块对base模块的控制命令
	T_SYS_CTRL,				//系统对基础模块的控制
	T_SYS_CONF,				//系统对会议组的控制
	T_SYS_SERVER,			//系统对cti-srver中的控制
	T_SYS_GETWAY,			//系统发送到网关的控制
	T_SYS_LINE,				//系统对总线的加载任务控制
	//在此扩展任务类型
	T_SERVER_DB,			//
	T_NODE_DB,				//
	T_SYS_DB,				//
	T_DB_NODE,				//
	T_DB_SERVER,			//
	T_DB_SYS,				//
	
	T_EXIT,					//
	T_UNUSERED				//
};

enum datatype{//数据类型
	D_BASE_INIT_COMP = 1,	//base基础模块初始化完成数据
	D_BASE_CALLIN,			//base基础模块来电数据
	D_BASE_TRUNK_INFO,		//base基础模块通道信息变迁
	D_BASE_DTMF_CHANGE,		//base基础模块DTMF同步数据
	D_BASE_PLAY,			//base基础模块放音控制数据
	D_BASE_RECORD,			//base基础模块录音控制数据

	D_DB_CONNECT,			//
	D_DB_RESULT,			//
	D_DB_FIELD,				//

	D_EXIT,
	D_UNUSERED
};
enum Modetype{
	M_BASE = 1,
		M_CONF,
		M_IVR,
		M_SERVER,
		M_DB,
		M_NODE,
		M_GW,
		M_SYSTEM
};

enum Table
{
	T_Line_AgentNo = 1,
	T_Switch_Group,
	T_Call_Log,
	T_Sys_option
};
typedef struct _Line_QueueHead{//总线接口转换类型
	UINT 			unitid;			// 单元编号ID
	unsigned short 	taskclass;		// 任务类别
	unsigned short 	moduleid;		//	模块类型
	UINT			datatype;		//	数据类型
	char 			databuff[4001];	//	数据空间
	unsigned long	datalen;		//	数据长度
	UINT			leave0;			//	预留
	UINT			leave1;			//	预留
	char 			leaveV[41];		//	预留
}LINE_HEAD, *P_LINE_HEAD;

//typedef CDataQueue<_Line_QueueHead,MAX_DATA_SIZE,200> LINE_QUEUE;//模块缓存队列

typedef int (*ModuleSend)(unsigned long param1);//回调函数全局类型定义

/* 应用简例
ModuleSend WINAPI ModuleOutputHandle(unsigned long param1)//总线上的函数定义
{
	_Line_QueueHead * _Lineinfo = NULL;
	
	_Lineinfo = (_Line_QueueHead * ) param1;
	
	switch(_Lineinfo->taskclass){
	case 0:
		break;
	default:
		break;
	}
	return 0 ;
};

ModuleSend Sendinfo = NULL;//DLL中的 全局回调函数句柄

int	ModuleOutputEcs(ModuleSend Func,unsigned long param1)//发送接口定义
{
	if (Func == NULL)	{
		return -1;
	}
	Sendinfo = Func;
	/***模块内部线程启动**********************
	return 0 ;
	
}
_Line_QueueHead SendData;
…………
unsigned long param1;
param1 = (unsigned long)(&(SendData));
Sendinfo(param1);等价于总线线程 ModuleOutputHandle( param1)的操作
*/

class TrunkBase //通道数据基础类
{
public:
	UINT 	Line;//逻辑通道号
	int		Trunkid;//物理通道编号
	int		Cardid;//DSP编号（内部通道为0-127）；模拟卡为空；数字卡为PCM编号（内部通道为0-29）；
	int		chktype;//通道类型
	int		calltype;// 1-呼入；2呼出
	char 	caller[MAX_TEL_LEN+1];//主叫号码
	char 	callee[MAX_TEL_LEN+1];//被叫号码
	char 	oracallee[MAX_TEL_LEN+1];//原被叫号码
	char 	dtmfbuff[MAX_DTMF_LEN+1];//DTMF按键缓存
	time_t	callbegin;//拨入时间
	time_t	callend;//结束时间
	time_t 	offhookTime;//摘机时间
	int		calllen;//呼叫时长
	int		talklen;//通话时长
	int		LinkLine;
	int		Linktype;
	TrunkBase(){
		Line=-1;//逻辑通道号
		Trunkid=-1;//物理通道编号
		Cardid=-1;//DSP编号（内部通道为0-127）；模拟卡为空；数字卡为PCM编号（内部通道为0-29）；
		chktype=-1;//通道类型
		ReSetMember();
	}
	~TrunkBase(){
		Line=-1;//逻辑通道号
		Trunkid=-1;//物理通道编号
		Cardid=-1;//DSP编号（内部通道为0-127）；模拟卡为空；数字卡为PCM编号（内部通道为0-29）；
		chktype=-1;//通道类型
		ReSetMember();
	}
	void ReSetMember(){
		calltype=0;// 1-呼入；2呼出
		caller[0]=0;//主叫号码
		callee[0]=0;//被叫号码
		oracallee[0]=0;//原被叫号码
		dtmfbuff[0]=0;//DTMF按键缓存
		callbegin=0;//拨入时间
		callend = 0;//结束时间
		offhookTime = 0;//摘机时间
		calllen = 0;//呼叫时长
		talklen = 0;//通话时长
		LinkLine = -1;
		Linktype = -1;
	}
};

//----------------------------------数据包定义---------------------------------
//*************************************cti-base 模块 发送数据结构定义*************************************
//cti-base模块初始化完成送出结构；交换机初始化获取整个通道的个数比较慢需要将所有设备打开完成成功之后才会发送数据
struct struBASE_INIT_COMP{
	int	 Baseid;
	UINT TUPE1TrunkTotal;//语音卡TUP中继通道个数；无则为0
	UINT CardNo;//板卡数量：交换机为DSP数量
	UINT ISUPE1TrunkTotal;//语音卡ISUP中继通道个数；无则为0
	UINT PBXTrunkTotal;//交换机数字通道个数；无则为0
	UINT PBXsimuTotal;//交换机模拟通道个数
	UINT VisualTrunkTotal;//虚拟通道个数；（模拟语音卡的声卡驱动；SIP虚拟通道应用）
	UINT simuTrunkTotal;//模拟通道个数【内外线】
};
//-----------------通道状态迁移初始化结构------------------------
/****************************************************************
*具体应用为：初始化；摘机动作；挂机动作
*1、数字卡为【发送ANC/ANN】信号
*2、模拟卡为摘机
*3、内线无摘挂机操作
*****************************************************************
*/
struct struBase_Trunk_Info{
	UINT Line;//线路通道号【通道逻辑编号】
	int  Trunkid;//通道实际编号
	int	 Cardid;//DSP编号；模拟卡为空；数字卡为PCM编号
	int  Linetype;//线路类型【1:TUP数字；2：ISUP数字；3：PBXTUP数字；4：PBXISUP数字；5；模拟外线；6：模拟内线：7：PBX模拟外线；8：PBX模拟内线；9以后的参数预留】
	int  LineState;//线路状态【统一使用标准表示 1：不可用 2：摘机；3：挂机（模拟通道使用）；4：空闲（数字通道使用）】
};
//-----------------来电信息结构------------------------
/****************************************************************
*具体应用为来电处理
*1、数字卡为接收到IAM/IAI就能收完主叫被叫
*2、模拟卡为首声振铃；这个时候主叫数据；2声振铃后结构中有主叫号码
*3、内线操作
*4、交换机收需要进行2次操作；
*****************************************************************
*/
struct struBase_Trunk_Callin{
	UINT Line;						//线路通道号[逻辑编号]
	int Trunkid;					//线路实际编号
	int Cardid;						//DSP编号；模拟卡为空；数字卡为PCM编号
	char Caller[MAX_TEL_LEN+1];		//主叫号码
	char Callee[MAX_TEL_LEN+1];		//被叫号码
	char oraCallee[MAX_TEL_LEN+1];	//原被叫号码
	time_t Calltime;				//呼入时间
};
//该数据用来同步DTMF buff。
struct struBase_DTMF_change{
	UINT Line;//线路通道号[逻辑编号]
	int Trunkid;//线路实际编号
	int Cardid;//DSP编号；模拟卡为空；数字卡为PCM编号;
	char dtmfbuff[MAX_DTMF_LEN+1];//DTMF按键缓存区
};
//通道放音同步
struct struPlay{
	UINT Line;//线路通道号[逻辑编号]
	int Trunkid;//线路实际编号
	int Cardid;//DSP编号；模拟卡为空；数字卡为PCM编号;
	char PlayClass;//0无效；1文件放音；2内存索引放音；3文件列表放音
	int StepId;// 动态分配；用于标识一次放音的句柄
	char PlayFlag;// 1-开始放音成功；2-开始放音结束
	char info;//失败原因：预定义类型 256种
};
//通道录音数据同步
struct struRecord{
	UINT Line;//线路通道号[逻辑编号]
	int Trunkid;//线路实际编号
	int Cardid;//DSP编号；模拟卡为空；数字卡为PCM编号;
	char RecordClass;//0，无效，1文件录音；2内存录音；需要提取buff中的语音文件
	int stepid;//动态分配；用于标识一次成功的录音句柄
	char recordflag;//0-录音失败 1，录音成功，2结束录音
	char RecordBuff[512];//内存录音中的录音数据缓存
	char info;//失败原因；预定义类型 256种
};
//******************cti-base接收数据组*******************************************************************************
struct stru_Command_PlayFile{//匹配command Playfile
	UINT Line;
	int Trunkid;//线路实际编号
	int Cardid;//DSP编号；模拟卡为空；数字卡为PCM编号;
	char Filename[100];//语音文件名
	bool sFlag;//是否允许按键打断
	bool ifDtmf;//是否接收DTMF
	int StepId;//放音ID；
};
//------------------------------------------------------------------
struct stru_Command_Playprompt{//内存索引放音Playprompt
	UINT Line;
	int Trunkid;//线路实际编号
	int Cardid;//DSP编号；模拟卡为空；数字卡为PCM编号;
	char vocstr[100];//文件索引字符串
	bool sFlag;//是否允许按键打断
	bool ifDtmf;//是否接收DTMF
	int StepId;//放音ID；
};
//------------------------------------------------------------------
struct stru_Command_InitTrunk{//通道初始化指令集（无内容返回）包括DTMF缓存；列表放音缓存
	UINT Line;		//逻辑通道号
	int Trunkid;	//线路实际编号
	int Cardid;		//DSP编号；模拟卡为空；数字卡为PCM编号;
};
//------------------------------------------------------------------
struct stru_Command_AddtoPlaylist{ //Addplaylist
	UINT Line;		//逻辑通道号
	int Trunkid;	//线路实际编号
	int Cardid;		//DSP编号；模拟卡为空；数字卡为PCM编号;
	char Filename[100];//语音文件名
	int nResult;
};
//------------------------------------------------------------------
struct stru_Command_VocCardPlaylistFile{ //Playlistfile
	UINT Line;		//线路通道号[逻辑编号]
	int Trunkid;	//线路实际编号
	int Cardid;		//DSP编号；模拟卡为空；数字卡为PCM编号;
	int StepId;		// 动态分配；用于标识一次放音的句柄
	char PlayFlag;	// 1-开始放音成功；2-开始放音结束
	char info;		//失败原因：预定义类型 256种
};
//------------------------------------------------------------------
struct stru_Command_Playpbxlistfile{//Playpbxlistfile
	UINT Line;		//线路通道号[逻辑编号]
	int Trunkid;	//线路实际编号
	int Cardid;		//DSP编号；模拟卡为空；数字卡为PCM编号;
	char vocstr[200];	//文件索引字符串
	bool sFlag;			//是否允许按键打断
	bool ifDtmf;		//是否接收DTMF
	int StepId;			//放音ID；
};
//------------------------------------------------------------------
struct stru_Command_RecordFile{//RecordFile
	UINT Line;		//线路通道号[逻辑编号]
	int Trunkid;	//线路实际编号
	int Cardid;		//DSP编号；模拟卡为空；数字卡为PCM编号;
	char RecordFile[200];	//录音文件符串
	bool sFlag;			//是否允许按键打断
	bool ifDtmf;		//是否接收DTMF
	int StepId;			//录音ID；
};
//------------------------------------------------------------------
struct stru_Command_JionConf{
	UINT Line;		//线路通道号[逻辑编号]
	int Trunkid;	//线路实际编号
	int Cardid;		//DSP编号；模拟卡为空；数字卡为PCM编号;
	UINT Groupid;	//会议组编号
	UINT chType;	//通道类型
	UINT JionModel;	//加入模式
} ;
//------------------------------------------------------------------
struct stru_Command_PlayConffile{
	UINT confid;//（会议组号，交换机为会议资源数组下标）
	UINT line;//（用来放音的语音资源ID）
	char filename[100] ;//		文件名；
	unsigned long len;//放音时长
	int Stepid;
};

//------------------------------------------------------------------
//*****************************数据库结构定义******************************************
//连接对象定义：

struct struConnectinfo{
	int		conid;//数据库连接标签编号
	int		DBtype;//访问的数据库类型：1:ORACLE;2MYSQL;3SQLSERVER;
	char	Server[50];//服务器：ORACEL的NET服务名；mysql的服务器ip；sqlserver的服务器IP;
	char	database[50];//；//仅2，3类数据库使用；数据库名
	char	user[20];//；数据库用户名
	char	pwd[20];//；密码
	int		connecttype;//；连接模式：1：短连接；2：长连接
	int		conNumber;
};

struct struDBinfo{
	UINT	Line;
	UINT	baseid;
	int		tableflag;
	UINT	nodeid;//节点对象ID
	int		conid;//连接对象ID
	int		dbtype;//数据库类型
	UINT	nodeObjid;
	int		sqltype;//sqltype = 1标识该字段保存的为一sql语句；sqltype=2标识为该字段存储的为一存储过程名。仿SQL语句调用过程
    int     datalen;
	char	strsql[MAX_SQL_LEN];
	char	DBresult[MAX_DBRESULT_LEN];
	int		ResultFlag;//1;99
};
class Trunk_Fieldinfo//具体的根据实际的解析协议定义指针分配内存；关键是整个结构要能塞入一个连续地址内
{
public:
	UINT	Line;
	UINT	baseid;
	UINT	nodeid;
	UINT	nodeObjid;//节点对象ID
	int		conid;//连接对象ID
	int		dbtype;//数据库类型
	char	strsql[MAX_SQL_LEN];
	int		sqltype;
	int		Fieldclass[MAX_FIELD_LEN];//数据列参数类型
	int		Fieldnamelen[MAX_FIELD_LEN];//列名长度
	int 	ContentLen[MAX_FIELD_LEN];//数据长度
	int     contentclass[MAX_FIELD_LEN];
	char *	pFieldname[MAX_FIELD_LEN];//数据库列名
	char *	pFieldcontent[MAX_FIELD_LEN];//数据库结果
	Trunk_Fieldinfo()
	{
		Line = 0;
		baseid = 0;
		nodeid = 0;
		nodeObjid = 0;
		conid = 0;
		dbtype = 0;
		sqltype = 0;
		for (int i = 0;i<MAX_FIELD_LEN;i++)
		{
			pFieldname[i]=NULL;
			pFieldcontent[i] = NULL;
			Fieldclass[i] = -1;
			Fieldnamelen[i] = 0;
			ContentLen[i] = 0;
			contentclass[i] = -1;
		}
	}
	virtual ~Trunk_Fieldinfo(){
		for (int i = 0;i<MAX_FIELD_LEN;i++)
		{
			if (pFieldname[i])
			{
				free(pFieldname[i]);
				pFieldname[i] = NULL;
				Fieldclass[i] = -1;
				Fieldnamelen[i] = 0;
			}
			if(pFieldcontent[i]){
				free(pFieldcontent[i]) ;
				pFieldcontent[i] = NULL;
				ContentLen[i] = 0;
				contentclass[i] = -1;
			}
		}

	}
	operator = (Trunk_Fieldinfo tempdata){
		Line = tempdata.Line;
		baseid = tempdata.baseid;
		nodeid = tempdata.nodeid;
		nodeObjid = tempdata.nodeObjid;
		conid = tempdata.conid;
		dbtype = tempdata.dbtype;
		sqltype = tempdata.sqltype;
		strcpy(strsql,tempdata.strsql);
		for (int i = 0;i<MAX_FIELD_LEN;i++)
		{
			if (tempdata.Fieldclass[i] > -1&&tempdata.Fieldnamelen[i] >0)
			{
				Fieldclass[i] = tempdata.Fieldclass[i];//取字段类型
				pFieldname[i] = (char *)malloc(tempdata.Fieldnamelen[i]);//分配内存长度
				if (pFieldname[i] != NULL)
				{
					Fieldnamelen[i] = tempdata.Fieldnamelen[i];//复制长度
					memcpy(pFieldname,tempdata.pFieldname,tempdata.Fieldnamelen[i]);//复制内容
				}
			}
			//
			if (tempdata.contentclass[i] > -1 && tempdata.ContentLen[i] >0)
			{
				contentclass[i] = tempdata.contentclass[i];//取内容类型
				pFieldcontent[i] = (char *)malloc(tempdata.ContentLen[i]);//分配内存
				if (pFieldcontent[i] != NULL)
				{
					Fieldnamelen[i] = tempdata.ContentLen[i];//复制长度
					memcpy(pFieldcontent,tempdata.pFieldcontent,tempdata.ContentLen[i]);//复制内容
				}
			}
		}
	}
};

struct stru_ErrorInfo{
	UINT Line;		//逻辑通道号
	int Trunkid;	//线路实际编号
	int Cardid;		//DSP编号；模拟卡为空；数字卡为PCM编号;
	int moduletype;//enum Modetype{ M_DB
	char Errorinfo[MAX_ERROR_LEN];
};

struct stru_Line_AgentNo{
	UINT ID;
	UINT Line;
	char Phone[22];
	int Groupid;
};
struct stru_Switch_Group{
	UINT ID;
	int CallLaw;
	int limit;
	int ringlen;
};
struct stru_Call_Log{
	UINT ID;
	char Caller[22];
	char Callee[22];
	char CallBegin[22];
	char CallEnd[22];
	int CallLen;
};

struct stru_Sys_option{
	char TitleName[51];
	char IniValue[51];
	char OpText[101];
};
#endif