
@echo off
pushd %~dp0\..\

echo "Fetching all submodules"
git submodule update --init --recursive

call vendor\premake\windows\premake5.exe vs2019
popd
PAUSE
