# Microsoft Developer Studio Project File - Name="ProtocalParse" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Static Library" 0x0104

CFG=ProtocalParse - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "ProtocalParse.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "ProtocalParse.mak" CFG="ProtocalParse - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "ProtocalParse - Win32 Release" (based on "Win32 (x86) Static Library")
!MESSAGE "ProtocalParse - Win32 Debug" (based on "Win32 (x86) Static Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
RSC=rc.exe

!IF  "$(CFG)" == "ProtocalParse - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_MBCS" /D "_LIB" /YX /FD /c
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo

!ELSEIF  "$(CFG)" == "ProtocalParse - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 2
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /YX /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_MBCS" /D "_LIB" /D "_AFXDLL" /FR /YX /FD /GZ /c
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LIB32=link.exe -lib
# ADD BASE LIB32 /nologo
# ADD LIB32 /nologo /out:"..\libs\ProtocalParse.lib"

!ENDIF 

# Begin Target

# Name "ProtocalParse - Win32 Release"
# Name "ProtocalParse - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\ConnectionInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\DbInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\FieldInfo.cpp
# End Source File
# Begin Source File

SOURCE=.\GenericRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\IRecord.cpp
# End Source File
# Begin Source File

SOURCE=.\MessageChunk.cpp
# End Source File
# Begin Source File

SOURCE=.\RecordAgentNo.cpp
# End Source File
# Begin Source File

SOURCE=.\RecordCallLog.cpp
# End Source File
# Begin Source File

SOURCE=.\RecordSwitchGroup.cpp
# End Source File
# Begin Source File

SOURCE=.\RecordSysOption.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\ConnectionInfo.h
# End Source File
# Begin Source File

SOURCE=.\DbInfo.h
# End Source File
# Begin Source File

SOURCE=.\FieldInfo.h
# End Source File
# Begin Source File

SOURCE=.\GenericRecord.h
# End Source File
# Begin Source File

SOURCE=.\IRecord.h
# End Source File
# Begin Source File

SOURCE=.\MessageChunk.h
# End Source File
# Begin Source File

SOURCE=.\RecordAgentNo.h
# End Source File
# Begin Source File

SOURCE=.\RecordCallLog.h
# End Source File
# Begin Source File

SOURCE=.\RecordSwitchGroup.h
# End Source File
# Begin Source File

SOURCE=.\RecordSysOption.h
# End Source File
# Begin Source File

SOURCE=.\stdafx.h
# End Source File
# End Group
# End Target
# End Project
