CFLAGS := PRINT(.\build\Release\${c}.lst) OMF2 TABS(4) CODE NOCOND SYMBOLS OPTIMIZE(8,SPEED) SMALL ROM(LARGE) INCDIR(D:\Chipenvironment\keilC51\C51\INC;.\src;.\libraries) DEFINE(__UVISION_VERSION='526')
CXXFLAGS := PRINT(.\build\Release\${cpp}.lst) OMF2 TABS(4) CODE NOCOND SYMBOLS OPTIMIZE(8,SPEED) SMALL ROM(LARGE) INCDIR(D:\Chipenvironment\keilC51\C51\INC;.\src;.\libraries) DEFINE(__UVISION_VERSION='526')
ASMFLAGS := PRINT(.\build\Release\${asm}.lst) SET(SMALL) INCDIR(D:\Chipenvironment\keilC51\C51\INC;.\src;.\libraries)
LDFLAGS :=  PRINT(.\build\Release\80C51.map) REMOVEUNUSED
LDLIBS := 
