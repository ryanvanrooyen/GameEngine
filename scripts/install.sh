
echo "Fetching all submodules"
git submodule update --init --recursive

echo "Premaking project files"
premake5 gmake2
