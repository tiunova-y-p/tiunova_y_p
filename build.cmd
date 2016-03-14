set PATH="C:\Program Files (x86)\CMake\bin\";%PATH%
call "%VS140COMNTOOLS%..\..\VC\vcvarsall.bat"

pushd build.x86.vc14

call cmake.exe -G "Visual Studio 14 2015" -DOpenCV_DIR="C:\opencv\build" ..

msbuild tiunova_y_p.sln /property:Configuration=Debug /m

popd