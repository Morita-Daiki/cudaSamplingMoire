# cuda_cv_test

## Sampling Moire
サンプリングモアレのopencv_cuda実装版 \
ダウンサンプリング＆内挿補完(モアレ化)を重み付け線形フィルターとして実装 \
<image src="https://latex.codecogs.com/svg.image?moire(x)=\sum_{k=-n}^{n}&space;image(x&plus;k)\bullet&space;w(k)\bullet&space;\exp\left&space;(&space;\frac{-2\pi&space;k}{n}i&space;\right&space;)&space;\\"/>

<image src="https://latex.codecogs.com/svg.image?moire(x)_{re}=\sum_{k=-n}^{n}&space;image(x&plus;k)\bullet&space;w(k)\bullet&space;\cos\left&space;(&space;\frac{-2\pi&space;k}{n}&space;\right&space;)&space;\\"/>

<image src="https://latex.codecogs.com/svg.image?moire(x)_{im}=\sum_{k=-n}^{n}&space;image(x&plus;k)\bullet&space;w(k)\bullet&space;\sin\left&space;(&space;\frac{-2\pi&space;k}{n}&space;\right&space;)&space;\\"/>

<image src="https://latex.codecogs.com/svg.image?w(k)=n-|k|"/>

ただし、
<image src="https://latex.codecogs.com/svg.image?w(n)=w(-n)=0&space;&space;"/>
よりフィルタサイズを削れる。

## DsiplayImage
表示のテスト
