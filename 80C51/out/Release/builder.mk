EIDE_UNIFY_BUILDER := 1
CFLAGS := PRINT(.\out\Release\${c}.lst) OMF2 TABS(4) CODE NOCOND SYMBOLS OPTIMIZE(8,SPEED) SMALL ROM(LARGE) INCDIR(D:\Chipenvironment\keilC51\C51\INC;.\libraries;.\src) DEFINE(__UVISION_VERSION='526')
CXXFLAGS := PRINT(.\out\Release\${cpp}.lst) OMF2 TABS(4) CODE NOCOND SYMBOLS OPTIMIZE(8,SPEED) SMALL ROM(LARGE) INCDIR(D:\Chipenvironment\keilC51\C51\INC;.\libraries;.\src) DEFINE(__UVISION_VERSION='526')
ASMFLAGS := PRINT(.\out\Release\${asm}.lst) SET(SMALL) INCDIR(D:\Chipenvironment\keilC51\C51\INC;.\libraries;.\src)
LDFLAGS :=  PRINT(.\out\Release\mcs51.map) REMOVEUNUSED
LDLIBS := 
