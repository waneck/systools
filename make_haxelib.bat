REM -- main folder
del systools
mkdir systools
copy haxelib.xml systools

REM -- api:
cd api\systools
svn export . ..\..\systools\systools
cd ..\..

REM -- samples
cd samples
svn export . ..\systools\samples
cd ..

REM -- sources
cd src
svn export . ..\systools\src
cd ..

REM -- ndll's:
mkdir systools\ndll
mkdir systools\ndll\Windows
copy bin\win\systools.ndll systools\ndll\Windows
mkdir systools\ndll\Mac
copy bin\mac\systools.ndll systools\ndll\Mac