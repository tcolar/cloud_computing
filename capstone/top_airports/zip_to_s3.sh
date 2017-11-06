#!/bin/bash
set -ex

src=/mnt/aviation/airline_origin_destination/
dest=s3://tcolartransportation/raw/aviation/airline_origin_destination/
tmp=./tmp

for f in $src/*.zip
do
    echo $f
    rm -rf $tmp
    mkdir -p $tmp
    cd tmp
    unzip -o "$f"
    aws s3 cp *.csv $dest
    cd ..
done
