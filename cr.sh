file="$1"
filename=${file%.*}
cpp_ext=${file##*.}
obj_ext="o"

#g++ -save-temps -std=c++11 -o $filename.$obj_ext $filename.$cpp_ext && ./$filename.$obj_ext
g++ -std=c++17 -O3 -o $filename.$obj_ext $filename.$cpp_ext -lpthread && /usr/bin/time -f%U ./$filename.$obj_ext $2
