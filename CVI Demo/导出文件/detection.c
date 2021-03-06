#include <utility.h>
#include <ansi_c.h>
#include <userint.h>
#include <formatio.h>
/**********************************************/
/*作用：	添加历史记录					
/*panel: 	面板句柄
/*control: 	控件名
/*...: 		需要记录的信息 
/**********************************************/
void AddRecordToTable(int panel, int control, float temperature, float ponding)
{
	char current_time[30] = {0};
	int day, year, month;
	int minutes, hours, seconds;

	GetSystemDate(&month, &day, &year);
	GetSystemTime(&hours, &minutes, &seconds);
	sprintf(current_time, "%d/%02d/%02d %02d:%02d:%02d", year, month, day, hours, minutes, seconds);
	
	InsertTableRows(panel, control, 1, 1, VAL_USE_MASTER_CELL_TYPE);
	SetTableCellVal(panel, control, MakePoint(1, 1), current_time);
	SetTableCellVal(panel, control, MakePoint(2, 1), temperature);
	SetTableCellVal(panel, control, MakePoint(3, 1), ponding);
}

/**********************************************/
/*作用：	导出历史记录					
/*panel: 	面板句柄
/*control: 	控件名
/*...: 		需要记录的信息 
/**********************************************/
void ExportHistory(int panel, int control, int record_num, int other)
{
	int FileHandle = 0;			// 被打开文件的句柄
	int i = 0;
	char date[50] = {0};		// 记录当前日期时间
	double temperature = 0;		
	double ponding = 0;
	char histroy[100] = {0};
	char fileName[500] = "历史记录.txt";
	
	#if OTHER
		FileSelectPopupEx("", "*.txt", "", "导出到指定目录", VAL_OK_BUTTON, 0, 0, fileName);
	#endif	
		FileHandle = OpenFile(fileName, VAL_READ_WRITE, VAL_TRUNCATE, VAL_ASCII);
		// 从控件中读取历史记录并存储在相应的变量中
		for( i = 1; i <= record_num; ++i )
		{
			GetTableCellVal(panel, control, MakePoint(1, i), date);
			GetTableCellVal(panel, control, MakePoint(2, i), &ponding);
			GetTableCellVal(panel, control, MakePoint(3, i), &temperature);
			sprintf(histroy, "%s %0.2f %0.2f\n", date, ponding, temperature);
			WriteFile(FileHandle, histroy, strlen(histroy));
		}
		
		CloseFile(FileHandle);
}
