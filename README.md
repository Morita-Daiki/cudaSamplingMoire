# cuda_cv_test

## Sampling Moire: サンプリングモアレのopencv_cuda実装版
### ダウンサンプリング＆内挿補完(モアレ化)を重み付け線形フィルターとして実装

https://github.com/Morita-Daiki/cudaSamplingMoire/blob/e81830b98de431b9ad3644200a59ea09cce99225/SamplingMoire/src/main.cpp#L136-L137

$$ moire(x)=\sum_{k=-n}^{n} Image(x+k) \bullet w(k) \bullet \exp\left(\frac{-2\pi k i}{n}\right) $$
ただし、
$$ w(k)=(n-|k|)/{n^2}\rightarrow  w(\pm n)=0$$
だからフィルタサイズを削れる。

### モアレを位相解析

https://github.com/Morita-Daiki/cudaSamplingMoire/blob/e81830b98de431b9ad3644200a59ea09cce99225/SamplingMoire/src/main.cpp#L147

$$ phase(x)=\arg({moire(x)}) $$


## DsiplayImage
表示のテスト
