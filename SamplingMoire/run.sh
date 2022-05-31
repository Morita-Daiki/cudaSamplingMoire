cmake .
make

# for index in {1..2}
# do
#   time ./SamplingMoire  --s i0-1.mp4 --o out-$index.mp4 --n $index --d 1
# done
time ./SamplingMoire --s i0-1.mp4 --o out-10.mp4 --n 15 --d 1