#!/bin/bash

filelist=`(find . -name \*.ps)`

for i in $filelist; do

        ps2pdf $i

        echo "Converted $i into pdf."

done
