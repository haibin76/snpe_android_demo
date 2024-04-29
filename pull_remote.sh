cd distribution/snpe/

rm -rf distribution/snpe/lib
rm -rf distribution/snpe/libs
rm -rf distribution/snpe/libs.zip

scp ubuntu@117.50.187.18:/home/ubuntu/libs.zip .

unzip libs.zip
mv libs lib

cd ../../../
