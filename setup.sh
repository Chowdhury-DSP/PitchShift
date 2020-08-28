#!/bin/bash

plugin_name=$1
echo "Creating plugin ${plugin_name}..."

echo "Copying source files..."
mv src/TempPlugin.h src/${plugin_name}.h
mv src/TempPlugin.cpp src/${plugin_name}.cpp

echo "Setting up source files..."

if [[ "$OSTYPE" == "darwin"* ]]; then
    sed_cmd="sed -i \'\' -e"
else
    sed_cmd="sed -i"
fi

declare -a source_files=("validate.sh" "win_builds.sh" "CMakeLists.txt" "src/CMakeLists.txt" "src/${plugin_name}.h" "src/${plugin_name}.cpp")
for file in "${source_files[@]}"; do
    $sed_cmd "s/TempPlugin/${plugin_name}/g" $file
done
