
echo "Fetching all submodules"
git submodule update --init --recursive

echo "Premaking project files"
vendor/premake/mac/premake5 gmake2

echo "Building project"
make -j 4
