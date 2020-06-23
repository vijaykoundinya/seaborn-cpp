# Seaborn-cpp  
Welcome to Seaborn-CPP, an attempt to create Seaborn as a C++ Library.  
  
## Prerequisites  
* Python  
* Matplotlib  
* Seaborn  
* Pandas  
  
## Ubuntu  
***TESTED ON PYTHON2.x***  
  
**To Compile:**  
1) g++ filename.cpp -I/usr/lib/python2.7/Python.h -lpython2.7.  
2) You can replace python2.7 with your installed version.  
  
  
## Windows  
***TESTED ON PYTHON3.x***  

**To Compile:**  
1) Add Python3.x Lib folder path to Libraries.  
2) Add Python3.x Include folder path to C++ Includes.  
3) Add libpythonxy.a path to linker.  
  
NOTE: Python3.8 has dropped libpython38.a file from the main distribution. The previous versions should contain a libpythonxy.a in /libs folder. Incase, libpython does not exist, it can be generated.  
  
Steps to generate libpython:  
1) gendef python38.dll > tmp.def  
2) dlltool --dllname python38.dll --def tmp.def --output-lib libpython38.a  
  
