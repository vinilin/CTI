//CTI_Typedfile.h
// LFQ-���� - 2010-03-18 ���ݣ�cti-baseģ���ⷢ���ݰ��ṹ��ͨ�������ࣻ�ص�����ȫ�����Ͷ���
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

enum TASK_CLASS{//������������
	T_INITBASE =	1,		// �������ͣ���������ģ���ʼ��
	T_INITBASE_INFO,		//����ģ���ʼ�����+����ģ����մ��������
	T_INIT_COMP,			//ģ���ʼ����ɣ�����ģ��������߱����쳣
	//
	T_BASE_CALLIN,			//baseģ��+����ͨ�����磺�ʹ�cti-node
	T_BASE_LINECHANGE,		//baseģ�飺����ͨ��״̬�¼���Ǩ���ʹ�cti-node��cti-ivr��cti-server��cti-conf
	T_BASE_OFFHOOK,			//baseģ�飺����ͨ�����ߡ��һ����ʹ�cti-node��cti-ivr��
	//
	T_NODE_STEP_IVR,		//nodeģ��+���̽ڵ����+�ʹ�ivr
	T_NODE_STEP_CONF,		//nodeģ��+���̽ڵ����+�ʹ����ģ��
	T_NODE_STEP_SERVER,		//nodeģ��+���̽ڵ����+�ʹ�cti-server
	T_NODE_STEP_DBRESULT,	//nodeģ��+���ݿ���ʶ���+�ʹ� ���ݿ����ģ��
	//
	T_IVR_CTRL,				//ivrģ�飺ivr�Ի���ģ��Ŀ���ָ��
	T_IVR_NODE,				//ivrģ��	ivrģ�鷢�͵�ctinode�����̽ڵ����ִ�����ָ��
	T_CONF_CTRL,			//����ģ�飺����ģ���baseģ��Ŀ�������
	T_SERVER_CTRL,			//������ģ�飺������ģ���baseģ��Ŀ�������
	T_SYS_CTRL,				//ϵͳ�Ի���ģ��Ŀ���
	T_SYS_CONF,				//ϵͳ�Ի�����Ŀ���
	T_SYS_SERVER,			//ϵͳ��cti-srver�еĿ���
	T_SYS_GETWAY,			//ϵͳ���͵����صĿ���
	T_SYS_LINE,				//ϵͳ�����ߵļ����������
	//�ڴ���չ��������
	T_SERVER_DB,			//
	T_NODE_DB,				//
	T_SYS_DB,				//
	T_DB_NODE,				//
	T_DB_SERVER,			//
	T_DB_SYS,				//
	
	T_EXIT,					//
	T_UNUSERED				//
};

enum datatype{//��������
	D_BASE_INIT_COMP = 1,	//base����ģ���ʼ���������
	D_BASE_CALLIN,			//base����ģ����������
	D_BASE_TRUNK_INFO,		//base����ģ��ͨ����Ϣ��Ǩ
	D_BASE_DTMF_CHANGE,		//base����ģ��DTMFͬ������
	D_BASE_PLAY,			//base����ģ�������������
	D_BASE_RECORD,			//base����ģ��¼����������

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
typedef struct _Line_QueueHead{//���߽ӿ�ת������
	UINT 			unitid;			// ��Ԫ���ID
	unsigned short 	taskclass;		// �������
	unsigned short 	moduleid;		//	ģ������
	UINT			datatype;		//	��������
	char 			databuff[4001];	//	���ݿռ�
	unsigned long	datalen;		//	���ݳ���
	UINT			leave0;			//	Ԥ��
	UINT			leave1;			//	Ԥ��
	char 			leaveV[41];		//	Ԥ��
}LINE_HEAD, *P_LINE_HEAD;

//typedef CDataQueue<_Line_QueueHead,MAX_DATA_SIZE,200> LINE_QUEUE;//ģ�黺�����

typedef int (*ModuleSend)(unsigned long param1);//�ص�����ȫ�����Ͷ���

/* Ӧ�ü���
ModuleSend WINAPI ModuleOutputHandle(unsigned long param1)//�����ϵĺ�������
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

ModuleSend Sendinfo = NULL;//DLL�е� ȫ�ֻص��������

int	ModuleOutputEcs(ModuleSend Func,unsigned long param1)//���ͽӿڶ���
{
	if (Func == NULL)	{
		return -1;
	}
	Sendinfo = Func;
	/***ģ���ڲ��߳�����**********************
	return 0 ;
	
}
_Line_QueueHead SendData;
��������
unsigned long param1;
param1 = (unsigned long)(&(SendData));
Sendinfo(param1);�ȼ��������߳� ModuleOutputHandle( param1)�Ĳ���
*/

class TrunkBase //ͨ�����ݻ�����
{
public:
	UINT 	Line;//�߼�ͨ����
	int		Trunkid;//����ͨ�����
	int		Cardid;//DSP��ţ��ڲ�ͨ��Ϊ0-127����ģ�⿨Ϊ�գ����ֿ�ΪPCM��ţ��ڲ�ͨ��Ϊ0-29����
	int		chktype;//ͨ������
	int		calltype;// 1-���룻2����
	char 	caller[MAX_TEL_LEN+1];//���к���
	char 	callee[MAX_TEL_LEN+1];//���к���
	char 	oracallee[MAX_TEL_LEN+1];//ԭ���к���
	char 	dtmfbuff[MAX_DTMF_LEN+1];//DTMF��������
	time_t	callbegin;//����ʱ��
	time_t	callend;//����ʱ��
	time_t 	offhookTime;//ժ��ʱ��
	int		calllen;//����ʱ��
	int		talklen;//ͨ��ʱ��
	int		LinkLine;
	int		Linktype;
	TrunkBase(){
		Line=-1;//�߼�ͨ����
		Trunkid=-1;//����ͨ�����
		Cardid=-1;//DSP��ţ��ڲ�ͨ��Ϊ0-127����ģ�⿨Ϊ�գ����ֿ�ΪPCM��ţ��ڲ�ͨ��Ϊ0-29����
		chktype=-1;//ͨ������
		ReSetMember();
	}
	~TrunkBase(){
		Line=-1;//�߼�ͨ����
		Trunkid=-1;//����ͨ�����
		Cardid=-1;//DSP��ţ��ڲ�ͨ��Ϊ0-127����ģ�⿨Ϊ�գ����ֿ�ΪPCM��ţ��ڲ�ͨ��Ϊ0-29����
		chktype=-1;//ͨ������
		ReSetMember();
	}
	void ReSetMember(){
		calltype=0;// 1-���룻2����
		caller[0]=0;//���к���
		callee[0]=0;//���к���
		oracallee[0]=0;//ԭ���к���
		dtmfbuff[0]=0;//DTMF��������
		callbegin=0;//����ʱ��
		callend = 0;//����ʱ��
		offhookTime = 0;//ժ��ʱ��
		calllen = 0;//����ʱ��
		talklen = 0;//ͨ��ʱ��
		LinkLine = -1;
		Linktype = -1;
	}
};

//----------------------------------���ݰ�����---------------------------------
//*************************************cti-base ģ�� �������ݽṹ����*************************************
//cti-baseģ���ʼ������ͳ��ṹ����������ʼ����ȡ����ͨ���ĸ����Ƚ�����Ҫ�������豸����ɳɹ�֮��Żᷢ������
struct struBASE_INIT_COMP{
	int	 Baseid;
	UINT TUPE1TrunkTotal;//������TUP�м�ͨ������������Ϊ0
	UINT CardNo;//�忨������������ΪDSP����
	UINT ISUPE1TrunkTotal;//������ISUP�м�ͨ������������Ϊ0
	UINT PBXTrunkTotal;//����������ͨ������������Ϊ0
	UINT PBXsimuTotal;//������ģ��ͨ������
	UINT VisualTrunkTotal;//����ͨ����������ģ��������������������SIP����ͨ��Ӧ�ã�
	UINT simuTrunkTotal;//ģ��ͨ�������������ߡ�
};

//-----------------ͨ��״̬Ǩ�Ƴ�ʼ���ṹ------------------------
/****************************************************************
*����Ӧ��Ϊ����ʼ����ժ���������һ�����
*1�����ֿ�Ϊ������ANC/ANN���ź�
*2��ģ�⿨Ϊժ��
*3��������ժ�һ�����
*****************************************************************
*/
struct struBase_Trunk_Info{
	UINT Line;//��·ͨ���š�ͨ���߼���š�
	int  Trunkid;//ͨ��ʵ�ʱ��
	int  Cardid;//DSP��ţ�ģ�⿨Ϊ�գ����ֿ�ΪPCM���
	int  Linetype;//��·���͡�1:TUP���֣�2��ISUP���֣�3��PBXTUP���֣�4��PBXISUP���֣�5��ģ�����ߣ�6��ģ�����ߣ�7��PBXģ�����ߣ�8��PBXģ�����ߣ�9�Ժ�Ĳ���Ԥ����
	int  LineState;//��·״̬��ͳһʹ�ñ�׼��ʾ 1�������� 2��ժ����3���һ���ģ��ͨ��ʹ�ã���4�����У�����ͨ��ʹ�ã���
};
//-----------------������Ϣ�ṹ------------------------
/****************************************************************
*����Ӧ��Ϊ���紦��
*1�����ֿ�Ϊ���յ�IAM/IAI�����������б���
*2��ģ�⿨Ϊ�������壻���ʱ���������ݣ�2�������ṹ�������к���
*3�����߲���
*4������������Ҫ����2�β�����
*****************************************************************
*/
struct struBase_Trunk_Callin{
	UINT Line;						//��·ͨ����[�߼����]
	int Trunkid;					//��·ʵ�ʱ��
	int Cardid;						//DSP��ţ�ģ�⿨Ϊ�գ����ֿ�ΪPCM���
	char Caller[MAX_TEL_LEN+1];		//���к���
	char Callee[MAX_TEL_LEN+1];		//���к���
	char oraCallee[MAX_TEL_LEN+1];	//ԭ���к���
	time_t Calltime;				//����ʱ��
};
//����������ͬ��DTMF buff��
struct struBase_DTMF_change{
	UINT Line;//��·ͨ����[�߼����]
	int Trunkid;//��·ʵ�ʱ��
	int Cardid;//DSP��ţ�ģ�⿨Ϊ�գ����ֿ�ΪPCM���;
	char dtmfbuff[MAX_DTMF_LEN+1];//DTMF����������
};
//ͨ������ͬ��
struct struPlay{
	UINT Line;//��·ͨ����[�߼����]
	int Trunkid;//��·ʵ�ʱ��
	int Cardid;//DSP��ţ�ģ�⿨Ϊ�գ����ֿ�ΪPCM���;
	char PlayClass;//0��Ч��1�ļ�������2�ڴ�����������3�ļ��б����
	int StepId;// ��̬���䣻���ڱ�ʶһ�η����ľ��
	char PlayFlag;// 1-��ʼ�����ɹ���2-��ʼ��������
	char info;//ʧ��ԭ��Ԥ�������� 256��
};
//ͨ��¼������ͬ��
struct struRecord{
	UINT Line;//��·ͨ����[�߼����]
	int Trunkid;//��·ʵ�ʱ��
	int Cardid;//DSP��ţ�ģ�⿨Ϊ�գ����ֿ�ΪPCM���;
	char RecordClass;//0����Ч��1�ļ�¼����2�ڴ�¼������Ҫ��ȡbuff�е������ļ�
	int stepid;//��̬���䣻���ڱ�ʶһ�γɹ���¼�����
	char recordflag;//0-¼��ʧ�� 1��¼���ɹ���2����¼��
	char RecordBuff[512];//�ڴ�¼���е�¼�����ݻ���
	char info;//ʧ��ԭ��Ԥ�������� 256��
};
//******************cti-base����������*******************************************************************************
struct stru_Command_PlayFile{//ƥ��command Playfile
	UINT Line;
	int Trunkid;//��·ʵ�ʱ��
	int Cardid;//DSP��ţ�ģ�⿨Ϊ�գ����ֿ�ΪPCM���;
	char Filename[100];//�����ļ���
	bool sFlag;//�Ƿ����������
	bool ifDtmf;//�Ƿ����DTMF
	int StepId;//����ID��
};
//------------------------------------------------------------------
struct stru_Command_Playprompt{//�ڴ���������Playprompt
	UINT Line;
	int Trunkid;//��·ʵ�ʱ��
	int Cardid;//DSP��ţ�ģ�⿨Ϊ�գ����ֿ�ΪPCM���;
	char vocstr[100];//�ļ������ַ���
	bool sFlag;//�Ƿ����������
	bool ifDtmf;//�Ƿ����DTMF
	int StepId;//����ID��
};
//------------------------------------------------------------------
struct stru_Command_InitTrunk{//ͨ����ʼ��ָ��������ݷ��أ�����DTMF���棻�б��������
	UINT Line;		//�߼�ͨ����
	int Trunkid;	//��·ʵ�ʱ��
	int Cardid;		//DSP��ţ�ģ�⿨Ϊ�գ����ֿ�ΪPCM���;
};
//------------------------------------------------------------------
struct stru_Command_AddtoPlaylist{ //Addplaylist
	UINT Line;		//�߼�ͨ����
	int Trunkid;	//��·ʵ�ʱ��
	int Cardid;		//DSP��ţ�ģ�⿨Ϊ�գ����ֿ�ΪPCM���;
	char Filename[100];//�����ļ���
	int nResult;
};
//------------------------------------------------------------------
struct stru_Command_VocCardPlaylistFile{ //Playlistfile
	UINT Line;		//��·ͨ����[�߼����]
	int Trunkid;	//��·ʵ�ʱ��
	int Cardid;		//DSP��ţ�ģ�⿨Ϊ�գ����ֿ�ΪPCM���;
	int StepId;		// ��̬���䣻���ڱ�ʶһ�η����ľ��
	char PlayFlag;	// 1-��ʼ�����ɹ���2-��ʼ��������
	char info;		//ʧ��ԭ��Ԥ�������� 256��
};
//------------------------------------------------------------------
struct stru_Command_Playpbxlistfile{//Playpbxlistfile
	UINT Line;		//��·ͨ����[�߼����]
	int Trunkid;	//��·ʵ�ʱ��
	int Cardid;		//DSP��ţ�ģ�⿨Ϊ�գ����ֿ�ΪPCM���;
	char vocstr[200];	//�ļ������ַ���
	bool sFlag;			//�Ƿ����������
	bool ifDtmf;		//�Ƿ����DTMF
	int StepId;			//����ID��
};
//------------------------------------------------------------------
struct stru_Command_RecordFile{//RecordFile
	UINT Line;		//��·ͨ����[�߼����]
	int Trunkid;	//��·ʵ�ʱ��
	int Cardid;		//DSP��ţ�ģ�⿨Ϊ�գ����ֿ�ΪPCM���;
	char RecordFile[200];	//¼���ļ�����
	bool sFlag;			//�Ƿ����������
	bool ifDtmf;		//�Ƿ����DTMF
	int StepId;			//¼��ID��
};
//------------------------------------------------------------------
struct stru_Command_JionConf{
	UINT Line;		//��·ͨ����[�߼����]
	int Trunkid;	//��·ʵ�ʱ��
	int Cardid;		//DSP��ţ�ģ�⿨Ϊ�գ����ֿ�ΪPCM���;
	UINT Groupid;	//��������
	UINT chType;	//ͨ������
	UINT JionModel;	//����ģʽ
} ;
//------------------------------------------------------------------
struct stru_Command_PlayConffile{
	UINT confid;//��������ţ�������Ϊ������Դ�����±꣩
	UINT line;//������������������ԴID��
	char filename[100] ;//		�ļ�����
	unsigned long len;//����ʱ��
	int Stepid;
};

//------------------------------------------------------------------
//*****************************���ݿ�ṹ����******************************************
//���Ӷ����壺

struct struConnectinfo{
	int		conid;//���ݿ����ӱ�ǩ���
	int		DBtype;//���ʵ����ݿ����ͣ�1:ORACLE;2MYSQL;3SQLSERVER;
	char	Server[50];//��������ORACEL��NET��������mysql�ķ�����ip��sqlserver�ķ�����IP;
	char	database[50];//��//��2��3�����ݿ�ʹ�ã����ݿ���
	char	user[20];//�����ݿ��û���
	char	pwd[20];//������
	int		connecttype;//������ģʽ��1�������ӣ�2��������
	int		conNumber;
};

struct struDBinfo{
	UINT	Line;
	UINT	baseid;
	int		tableflag;
	UINT	nodeid;//�ڵ����ID
	int		conid;//���Ӷ���ID
	int		dbtype;//���ݿ�����
	UINT	nodeObjid;
	int		sqltype;//sqltype = 1��ʶ���ֶα����Ϊһsql��䣻sqltype=2��ʶΪ���ֶδ洢��Ϊһ�洢����������SQL�����ù���
    int     datalen;
	char	strsql[MAX_SQL_LEN];
	char	DBresult[MAX_DBRESULT_LEN];
	int		ResultFlag;//1;99
};
class Trunk_Fieldinfo//����ĸ���ʵ�ʵĽ���Э�鶨��ָ������ڴ棻�ؼ��������ṹҪ������һ��������ַ��
{
public:
	UINT	Line;
	UINT	baseid;
	UINT	nodeid;
	UINT	nodeObjid;//�ڵ����ID
	int		conid;//���Ӷ���ID
	int		dbtype;//���ݿ�����
	char	strsql[MAX_SQL_LEN];
	int		sqltype;
	int		Fieldclass[MAX_FIELD_LEN];//�����в�������
	int		Fieldnamelen[MAX_FIELD_LEN];//��������
	int 	ContentLen[MAX_FIELD_LEN];//���ݳ���
	int     contentclass[MAX_FIELD_LEN];
	char *	pFieldname[MAX_FIELD_LEN];//���ݿ�����
	char *	pFieldcontent[MAX_FIELD_LEN];//���ݿ���
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
				Fieldclass[i] = tempdata.Fieldclass[i];//ȡ�ֶ�����
				pFieldname[i] = (char *)malloc(tempdata.Fieldnamelen[i]);//�����ڴ泤��
				if (pFieldname[i] != NULL)
				{
					Fieldnamelen[i] = tempdata.Fieldnamelen[i];//���Ƴ���
					memcpy(pFieldname,tempdata.pFieldname,tempdata.Fieldnamelen[i]);//��������
				}
			}
			//
			if (tempdata.contentclass[i] > -1 && tempdata.ContentLen[i] >0)
			{
				contentclass[i] = tempdata.contentclass[i];//ȡ��������
				pFieldcontent[i] = (char *)malloc(tempdata.ContentLen[i]);//�����ڴ�
				if (pFieldcontent[i] != NULL)
				{
					Fieldnamelen[i] = tempdata.ContentLen[i];//���Ƴ���
					memcpy(pFieldcontent,tempdata.pFieldcontent,tempdata.ContentLen[i]);//��������
				}
			}
		}
	}
};

struct stru_ErrorInfo{
	UINT Line;		//�߼�ͨ����
	int Trunkid;	//��·ʵ�ʱ��
	int Cardid;		//DSP��ţ�ģ�⿨Ϊ�գ����ֿ�ΪPCM���;
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
