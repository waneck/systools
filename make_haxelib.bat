del systools
mkdir systools
copy haxelib.xml systools
mkdir systools\systools
xcopy api\systools systools\systools
mkdir systools\ndll
mkdir systools\ndll\Windows
copy bin\win\systools.ndll systools\ndll\Windows
mkdir systools\ndll\Mac
copy bin\mac\systools.ndll systools\ndll\Mac