#!/bin/bash
set -ex

src=/mnt/aviation/airline_ontime/
dest=s3://tcolartransportation/gz/aviation/airline_ontime/
tmp=./tmp

for f in $src/*/*.zip
do
    echo $f
    rm -rf $tmp
    mkdir -p $tmp
    cd tmp
    unzip -o "$f"
    gzip *.csv
    aws s3 cp *.gz $dest
    cd ..
done
